"""
这份代码是用来检查分类问题的。整体代码流程与test.py十分相近，相似代码的注释可以参考test.py
代码有两个功能：1.将错误分类的图片标记出来；2.将分类置信度低于阈值的图片标记出来。
"""
import os
import json
import argparse
import shutil
import torch
from PIL import Image
from torchvision import transforms
from glob import glob
from pathlib import Path

from model import resnet34


def main(args):
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")

    data_transform = transforms.Compose(
        [transforms.Resize(256),
         transforms.CenterCrop(224),
         transforms.ToTensor(),
         transforms.Normalize([0.485, 0.456, 0.406], [0.229, 0.224, 0.225])])

    
    '''获取所有测试集图片的路径'''
    test_paths = args.img_paths
    img_path_list = glob(test_paths, recursive=True)

    
    '''将所需要分类的类别定义好。类别信息是存储在根目录下的class_index.json文件中'''
    json_path = args.cls_index
    assert os.path.exists(json_path), f"file: '{json_path}' dose not exist."
    json_file = open(json_path, "r")
    class_indict = json.load(json_file)
    class_indict_reverse = {v: k for k, v in class_indict.items()}
    ground_truths = [int(class_indict_reverse[x.split('/')[-2]])
                     for x in img_path_list]

    '''定义ResNet-34网络模型'''
    model = resnet34(num_classes=args.num_classes).to(device)

    '''为模型加载指定的权重'''
    weight_path = args.weight_path
    assert os.path.exists(weight_path), f"file: '{weight_path}' dose not exist."
    model.load_state_dict(torch.load(weight_path, map_location=device))

    model.eval()
    batch_size = args.batch_size

    '''这里使用一个lower_conf_preds列表存储低于置信度阈值的图像信息'''
    '''这里还有一个新定义的集合变量wrong_preds，用于存储分类错误的图像路径'''
    lower_conf_preds, wrong_preds = [], set()
    with torch.no_grad():
        for ids in range(0, round(len(img_path_list) / batch_size)):
            img_list = []
            start = ids * batch_size
            end = -1 if (ids + 1) * batch_size >= len(img_path_list) else (ids + 1) * batch_size
            for img_path in img_path_list[start: end]:
                assert os.path.exists(img_path), f"file: '{img_path}' dose not exist."
                img = Image.open(img_path)
                img = data_transform(img)
                img_list.append(img)
            batch_ground_truths = ground_truths[start: end]

            batch_img = torch.stack(img_list, dim=0)

            output = model(batch_img.to(device)).cpu()
            predict = torch.softmax(output, dim=1)
            probs, classes = torch.max(predict, dim=1)

            for idx, (pro, cla) in enumerate(zip(probs, classes)):
                print("image: {}  class: {}  prob: {:.3}".format(img_path_list[ids * batch_size + idx],
                                                                 class_indict[str(cla.numpy())],
                                                                 pro.numpy()))

                '''加入预测图片的置信度低于设置的阈值，将这个图片的路径、预测的类别以及预测的置信度保存到lower_conf_preds列表中'''
                if pro < args.conf_thr:
                    lower_conf_preds.append([
                        img_path_list[ids * batch_size + idx],
                        class_indict[str(cla.numpy())],
                        float(pro.numpy())
                    ])

            '''由于我们想找出分类错误的图像，因此我们需要确定FP/FN的样本。由FP/FN样本的下标我们可以从数据列表中找到这些图片的路径'''
            batch_predicted_clses = classes.numpy().tolist()
            FP = [i for i, (g, p) in enumerate(zip(batch_ground_truths, batch_predicted_clses))
                  if g == 0 and p == 1]
            FN = [i for i, (g, p) in enumerate(zip(batch_ground_truths, batch_predicted_clses))
                  if g == 1 and p == 0]
            for i in FP + FN:
                wrong_preds.add(img_path_list[start + i])  # 将分类错误的图片路径添加到集合中

    '''将置信度低的图片单独复制到一个根目录下新建的low_probs文件夹中。在这个文件夹中，所有图像的名称都会在后面加上
    模型预测的类别以及预测的置信度。在代码中我默认保留小数点后4位、阈值为1.0，因此可能在文件名中出现1.0000的预测置
    信度情况，出现这种情况的原因很有可能是因为小数点保留问题造成的（实际置信度可能是0.9999999...。阈值可以调整）'''
    if os.path.exists('low_probs/'):
        shutil.rmtree('low_probs/')
    os.makedirs('low_probs/')
    for low_conf_pred in lower_conf_preds:
        shutil.copyfile(
            low_conf_pred[0],
            os.path.join('low_probs',
                         f'{Path(low_conf_pred[0]).stem}_{low_conf_pred[1]}_{low_conf_pred[2]:.4f}.png')
        )
    print(f"所有置信度低于{args.conf_thr}的图片都被保存到\'low_probs\'目录中。")

    '''打印所有分类错误的图片路径'''
    print(f'以下图片出现了分类错误：')
    for wrong_pred in wrong_preds:
        print(wrong_pred)


def arguments():
    parser = argparse.ArgumentParser()

    parser.add_argument(
        '--num_classes',
        type=int,
        default=2,
        help='网络需要分类的类别数量'
    )
    parser.add_argument(
        '--img_paths',
        type=str,
        default='data/val/*/*.png',
        help='测试集图片的路径'
    )
    parser.add_argument(
        '--cls_index',
        type=str,
        default='class_index.json',
        help='定义类别信息的json文件的路径'
    )
    parser.add_argument(
        '--weight_path',
        type=str,
        default='weight/resnet34_best.pth',
        help='需要加载的权重文件路径。此处应当使用经过网络训练后得到的权重文件'
    )
    parser.add_argument(
        '--conf_thr',
        type=float,
        default=1.,
        help='用于筛选低于这个阈值的图像分类结果，建议设定范围为0.5~1.0'
    )
    parser.add_argument(
        '--batch_size',
        type=int,
        default=8,
        help='批量大小。可以根据自己电脑的硬件/软件条件动态调整为2的指数倍（如2/4/8/16...）'
    )

    return parser.parse_args()


if __name__ == '__main__':
    args = arguments()
    main(args)
