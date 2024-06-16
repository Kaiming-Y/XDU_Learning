from torchvision import transforms, datasets
import torch
import torch.nn as nn
import os
import json
from torch.utils.data import DataLoader
from model import resnet34
from tqdm import tqdm
import sys
import argparse


def main(args):
    """
    训练网络
    :param args: 部分训练要用到的参数。这些参数已经在arguments函数中定义好了。
    :return:
    """

    '''训练网络模型可以使用GPU进行训练，也可以使用CPU进行训练。
    一般而言，如果有可用的GPU资源（一般是英伟达的显卡），我们就倾向于将训练过程放在GPU上运行。
    如果没有可用的GPU资源，那么程序只能在CPU上运行，这会使得训练过程十分耗时。
    下面这行代码调用is_available函数来判断是否有符合环境条件的GPU可用资源，若有则使用GPU，没有则使用CPU'''
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    print("using {} device".format(device))  # 将设备信息输出

    '''数据变换，是对输入网络中的数据进行处理的一个过程定义
    对于train采用了：随机裁剪再缩放到指定大小、随机水平翻转、转变为Tensor格式、标准化'''
    data_transfrom = {
        "train": transforms.Compose([transforms.RandomResizedCrop(224),
                                     transforms.RandomHorizontalFlip(),
                                     transforms.ToTensor(),
                                     transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])]),
        "val": transforms.Compose([transforms.Resize(256),
                                   transforms.CenterCrop(224),
                                   transforms.ToTensor(),
                                   transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])])
    }

    '''---------------------'''
    '''加载数据集（训练集/测试集）'''
    data_root = args.dataset_root  # 定义数据集的主目录
    assert os.path.exists(data_root), "{} path does not exist.".format(data_root)

    # 调用API来加载训练集
    train_data = datasets.ImageFolder(
        root=os.path.join(data_root, "train"),
        transform=data_transfrom["train"]
    )
    train_num = len(train_data)

    # train文件夹下有两个文件夹（sea和ship），程序接口判断该文件夹下的子文件夹数量和名字来构造类别字典
    # 如在本代码中，按照之前的要求组织好数据后，这个类别字典应该是： {"sea": 0, "ship": 1}
    class_idx = train_data.class_to_idx
    # 字典的键值对换一个位置
    class_dict = dict((v, k) for k, v in class_idx.items())
    # 将调换位置后的类别字典存储成一个json文件。这个json文件代表了从类别序号到类别名称的映射
    json_str = json.dumps(class_dict, indent=4)  # indent=4控制格式缩进，一般为4或2
    with open("class_index.json", "w") as json_file:
        json_file.write(json_str)

    # 根据超参数设定，定义批大小
    batch_size = args.batch_size
    # 选择os.cpu_count()、batch_size、8中最小值作为num_workers
    # os.cpu_count()：Python中的方法用于获取系统中的CPU数量。如果系统中的CPU数量不确定，则此方法返回None。
    # 如果想进一步了解num_workers的知识，可以上网查阅
    nw = min([
        os.cpu_count(),
        batch_size if batch_size > 1 else 0,
        8]
    )
    print("Using {} dataloader workers every process".format(nw))  # 打印使用几个进程

    # 设置训练集dataloader。之前的train_data只是定义了整体的数据有哪些，dataloader在此基础上定义了这些数据要如何
    # 按照批大小划分给网络进行训练
    train_dataloader = DataLoader(
        train_data,
        batch_size=batch_size,
        shuffle=True,
        num_workers=nw
    )

    # 定义测试集，用于在每一个epoch训练完毕后测试当时网络的性能
    val_data = datasets.ImageFolder(
        root=os.path.join(data_root, "val"),
        transform=data_transfrom["val"]
    )
    val_num = len(val_data)  # 验证集长度
    # 设置验证集dataloader
    val_dataloader = DataLoader(
        val_data,
        batch_size=batch_size,
        shuffle=False,
        num_workers=nw
    )

    print("Using {} for train,using {} for val".format(train_num, val_num))

    '''-----------------------'''
    '''网络模型定义以及预训练权重加载'''
    net = resnet34()  # 定义ResNet-34的网络架构
    weigth_path = args.pretrained_model  # 获得预训练权重的路径
    assert os.path.exists(weigth_path), "weight file {} is not exists".format(weigth_path)
    net.load_state_dict(torch.load(weigth_path, map_location=device))  # 根据给定的预训练权重路径，加载预训练权重到网络上

    # 原始ResNet做的是1000个类别的分类任务，因此其网络的最后一层是一个有1000个神经元的全连接层
    # 然而我们的问题只有2类，最后一层全连接层的输出维度只需要是2，因此我们要重新定义ResNet-34网络层最后一层全连接层的维度
    inchannels = net.fc.in_features
    net.fc = nn.Linear(inchannels, args.num_classes)
    net.to(device)  # 将模型放入设备（cpu或者GPU）中

    '''定义一些重要的网络训练变量'''
    # 构造优化器，将参数放入优化器中，设置学习率
    params = [p for p in net.parameters() if p.requires_grad]
    learning_rate = args.lr  # 学习率需要用在网络训练优化器中
    optimizer = torch.optim.Adam(params, lr=learning_rate)
    # 损失函数，使用交叉熵损失
    loss_function = nn.CrossEntropyLoss()

    epochs = args.epoch  # 定义训练的二篇epoch数量
    best_acc = 0.0  # 用于记录训练过程中所出现的最佳准确率，进行比较后确定是否保存模型的最优权重
    save_path = "weight/resnet34_best.pth"  # 如果判断某个epoch的网络权重使得测试效果最佳，那么就保存该网络模型到这个路径上
    train_step = len(train_dataloader)  # 相当于一共有多少个batch
    loss_r, acc_r = [], []  # 记录训练时出现的损失以及分类准确度

    '''正式开始训练'''
    for epoch in range(epochs):
        # 训练
        net.train()
        running_loss = 0.0
        train_bar = tqdm(train_dataloader, file=sys.stdout)

        for step, data in enumerate(train_bar):
            images, labels = data
            optimizer.zero_grad()  # 先进行梯度清零
            pre = net(images.to(device))  # 对类别进行预测
            loss = loss_function(pre, labels.to(device))
            loss.backward()
            optimizer.step()
            running_loss += loss.item()

            train_bar.desc = "train epoch[{}/{}] loss:{:.3f}".format(epoch + 1, epochs, loss)

        loss_r.append(running_loss)  # 该损失数值会被保存起来

        # 验证模式
        net.eval()
        acc = 0.0  # 预测正确个数
        with torch.no_grad():
            val_bar = tqdm(val_dataloader, file=sys.stdout)
            for val_d in val_bar:
                val_image, val_label = val_d
                output = net(val_image.to(device))
                # torch.max比较后，第0个是每个最大值，第1个是最大值的下标，所以取第1个
                predict_y = torch.max(output, dim=1)[1]
                acc += torch.eq(predict_y, val_label.to(device)).sum().item()

                val_bar.desc = "valid epoch[{}/{}]".format(epoch + 1,
                                                           epochs)

        val_accurate = acc / val_num  # 计算本次epoch训练得到的网络模型的准确度
        acc_r.append(val_accurate)  # 保存该准确度信息
        print('[epoch %d] train_loss: %.3f  val_accuracy: %.3f' %
              (epoch + 1, running_loss / train_step, val_accurate))

        if val_accurate > best_acc:  # 如果本次epoch训练的模型准确度高于之前的最高准确度，那就保存这一次模型的权重信息
            best_acc = val_accurate
            torch.save(net.state_dict(), save_path)

    print("finished tarining")

    with open('training_statistic.json', 'w+') as f:  # 保存训练过程的损失和准确度数据为一个json文件
        json.dump(dict(loss=loss_r, accuracy=acc_r), f, indent=4)


def arguments():
    """
    这个函数的作用就是专门用来定义一些必要的网络训练中要使用到的超参数和变量
    想要修改超参数及变量的值，需要在每个变量的定义里更改default字段的值
    :return:
    """

    parser = argparse.ArgumentParser(description='Arguments for training ResNet-34')

    parser.add_argument(
        '--num_classes',
        type=int,
        default=2,
        help='网络要进行预测的类别数量'
    )
    parser.add_argument(
        '--epoch',
        type=int,
        default=200,
        help='网络训练的Epoch数量，即不断循环迭代训练网络的次数。建议先设置为50~100的值，然后根据测试情况逐步修改'
    )
    parser.add_argument(
        '--lr',
        type=float,
        default=0.01,
        help='网络训练学习率。建议以10的倍数增大或减小'
    )
    parser.add_argument(
        '--batch_size',
        type=int,
        default=2,
        help='批大小，一般设置范围在4~32之间，硬件设备性能足够时可以设置的大一些'
    )
    parser.add_argument(
        '--dataset_root',
        type=str,
        default=r'I:\临时拷贝\20230526 上课\老师的代码\data',
        help='即data文件夹路径'
    )
    parser.add_argument(
        '--pretrained_model',
        type=str,
        default=r'I:\临时拷贝\20230526 上课\老师的代码\weight\resnet34-333f7ec4.pth',
        help='网络预训练权重文件的路径'
    )

    return parser.parse_args()


if __name__ == "__main__":
    args = arguments()
    main(args)
