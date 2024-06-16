"""
这份代码是用来计算训练好模型在测试集上的性能指标的。
计算的指标包括：①准确度（Accuracy）；②精确度（Precision）；③召回率（Recall）；④F1-Score（F1分数）
"""
import os
import json
import argparse
import torch
from PIL import Image
from torchvision import transforms
from glob import glob

from model import resnet34


def main(args):

    # 定义可以使用的设备
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

    # 图像数据转换
    data_transform = transforms.Compose(
        [transforms.Resize(256),
         transforms.CenterCrop(224),
         transforms.ToTensor(),
         transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])])

    # 获取存放测试图像的路径
    test_paths = args.img_paths
    # 通过Python库函数glob读取指定路径下所有符合匹配条件的文件（图片）
    img_path_list = glob(test_paths, recursive=True)

    # 训练的时候在代码的根目录下保存了一份存有类别名称和类别序号对应关系的json文件，这个时候要读取这个文件的内容
    # 方便我们获得图片所对应的类别序号信息，以计算指标
    json_path = args.cls_index  # 获取json文件的路径
    assert os.path.exists(json_path), f"file: '{json_path}' dose not exist."
    json_file = open(json_path, "r")  # 打开json文件
    class_indict = json.load(json_file)  # 读取json文件的内容，存取成一个字典。其内容应该是：{"0": "sea", "1": "ship"}
    class_indict_reverse = {v: k for k, v in class_indict.items()}  # 反转字典的键值对

    # 通过判断图片所在的文件夹类别来获取图片所对应的真实类别编号，存储在ground_truths列表中
    # 这个列表中的内容是一个0/1序列（0代表非船舶类sea，1代表船舶类ship），每一个元素的值都与之前的图像列表中的元素一一对应
    # 例如img_path_list中的第一个元素是一张val/sea/文件夹下的图片，那么ground_truths的第一个元素的值便为0
    ground_truths = [int(class_indict_reverse[x.split('/')[-2]])
                     for x in img_path_list]

    # 建立ResNet-34模型。".to(device)"的意思是将网络模型移动到之前定义的设备上
    model = resnet34(num_classes=args.num_classes).to(device)

    # 通过指定的权重文件路径，向网络模型上加载这个权重
    weight_path = args.weight_path
    assert os.path.exists(weight_path), f"file: '{weight_path}' dose not exist."
    model.load_state_dict(torch.load(weight_path, map_location=device))  # 网络模型加载权重

    model.eval()  # 将模型设定为验证模式
    batch_size = args.batch_size  # 每次预测时将多少张图片打包成一个batch
    TPs, TNs, FPs, FNs = 0, 0, 0, 0  # 统计整个测试过程中的TP/TN/FP/FN样本的总数

    with torch.no_grad():  # 这一句话是PyTorch框架在验证网络性能是常用到的，意思是无需像训练过程中记录网络的梯度数据

        for ids in range(0, round(len(img_path_list) / batch_size)):  # 根据批的划分情况，分批向网络传送数据

            # img_path_list中的元素只是图像的地址，因此下面的代码是将一个批中的图像地址逐一读取为图像
            img_list = []
            # 由于是一次读取一批数据，所以可能存在批大小划分无法刚好划分完全部数据的情况，所以要放置下标越界的错误出现
            start = ids * batch_size
            end = -1 if (ids + 1) * batch_size >= len(img_path_list) else (ids + 1) * batch_size
            for img_path in img_path_list[start: end]:
                assert os.path.exists(img_path), f"file: '{img_path}' dose not exist."
                img = Image.open(img_path)
                img = data_transform(img)
                img_list.append(img)
            batch_ground_truths = ground_truths[start: end]  # 获取该批大小对应图片的类别序号

            # img_list内部即是一个批大小的图像数据，但是在输入网络之前我们需要将列表类型的数据转换为PyTorch支持的张量数据
            batch_img = torch.stack(img_list, dim=0)

            # 将数据输入网络，获得分类结果
            output = model(batch_img.to(device)).cpu()
            predict = torch.softmax(output, dim=1)
            probs, classes = torch.max(predict, dim=1)

            # 打印这一个批大小的数据的分类信息
            for idx, (pro, cla) in enumerate(zip(probs, classes)):
                print("image: {}  class: {}  prob: {:.3}".format(img_path_list[ids * batch_size + idx],
                                                                 class_indict[str(cla.numpy())],
                                                                 pro.numpy()))

            '''以下代码用于一个批大小图像数据分类预测的计算指标'''
            '''由于图片的真实分类情况存储在batch_ground_truths中【类型是列表】，而预测的分类情况存储在
            classes中【类型是PyTorch.Tensor】，因此我们需要将这两个变量转换为同一类型的变量【比如列表】，
            才能去比对预测结果和真是结果。'''
            '''由于0代表负样本，1代表正样本，所以对比的过程就是根据TP/TN/FP/FN的定义，判断真实值和预测值
            的0-1搭配情况即可。'''
            '''由于上述变量是一个批大小的，所以下面计算的TP/TN/FP/FN仅仅是一个批数据的测试结果，因此我们
            需要将TP/TN/FP/FN的值加到之前定义好的TPs/TNs/FPs/FNs上，在处理完所有批数据后再计算整体指标。'''

            batch_predicted_clses = classes.numpy().tolist()  # 对网络预测结果的变量类型做改变，变为列表

            # 计算该批下数据的TP/TN/FP/FN样本数量。如果符合条件的话，就向列表中添加一个1，然后计算整个列表的和值即为样本量
            TP = sum([1 for g, p in zip(batch_ground_truths, batch_predicted_clses) if g == p == 1])
            TN = sum([1 for g, p in zip(batch_ground_truths, batch_predicted_clses) if g == p == 0])
            FP = sum([1 for g, p in zip(batch_ground_truths, batch_predicted_clses) if g == 0 and p == 1])
            FN = sum([1 for g, p in zip(batch_ground_truths, batch_predicted_clses) if g == 1 and p == 0])

            # 一个批的预测结果加到总数上
            TPs += TP
            TNs += TN
            FPs += FP
            FNs += FN

    # 根据定义，计算总数的各项指标
    accuracy = (TNs + TPs) / len(img_path_list)
    precision = TPs / (TPs + FPs)
    recall = TPs / (TPs + FNs)
    f1 = 2 * precision * recall / (precision + recall)
    print(f'Overall performance:\n'
          f'Accuracy: {accuracy:.4f}, Precision: {precision:.4f}, Recall: {recall:.4f}, F1: {f1:.4f}, FPS: {fps:.2f}')


def arguments():
    """
    用于定义各类要用到的超参数和变量。如果要对参数进行改变，只需要在对应的参数内修改default值即可
    :return:
    """

    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--num_classes',
        type=int,
        default=2,
        help='网络要进行预测的类别数量'
    )
    parser.add_argument(
        '--img_paths',
        type=str,
        default='data/val/*/*.png',
        help='所有待测试的图像的匹配地址。星号*代表一个匹配符，程序会根据这个路径去匹配符合的文件，最后加载为一个文件路径列表'
    )
    parser.add_argument(
        '--cls_index',
        type=str,
        default='class_index.json',
        help='在训练阶段生成的class_index.json文件的路径'
    )
    parser.add_argument(
        '--weight_path',
        type=str,
        default='weight/resnet34_best.pth',
        help='保存的最优模型权重'
    )
    parser.add_argument(
        '--batch_size',
        type=int,
        default=8,
        help='批大小，建议设定范围为4~32（2的倍数)'
    )

    return parser.parse_args()


if __name__ == '__main__':
    args = arguments()
    main(args)
