import os
import random
import shutil
import argparse

from glob import glob
from pathlib import Path
from tqdm import tqdm


def get_arguments():
    """用于定义数据集划分时需要用到的参数，包括数据集存放的路径以及训练集划分的比例。

    Returns:
        Namespace: 设定好的参数
    """
    arg_parser = argparse.ArgumentParser(description='数据集划分参数设置')
    arg_parser.add_argument('--dataset_root',
                            default=r'I:\临时拷贝\20230526 上课\老师的代码\data',
                            type=str,
                            help='数据集根目录，默认情况下为\'data\'文件夹的路径')
    arg_parser.add_argument('--train_ratio',
                            default=0.8,
                            type=float,
                            help='训练集比例，默认情况下为0.8，对应测试集比例为0.2')
    return arg_parser.parse_args()


def processor(dataset_root: str,
              train_ratio: float = 0.8):
    """
    Process data and split them into trainset and testset.
    :param dataset_root: Directory to the dataset.
    :param train_ratio: Ratio of the train set regarding to the entire dataset.
    :return: None
    """

    
    '''确保所有输入的路径和训练集比例没有问题'''
    assert os.path.exists(dataset_root) and os.path.isdir(dataset_root), \
        'Invalid dataset root directory!'
    assert 0.5 < train_ratio < 1, 'Invalid trainset ratio!'  # 训练集的比例不能大于1，且不要小于0.5

    
    '''获取所有的正负样本。正样本即船舶图像，负样本即非船舶图像。'''
    neg_samples = glob(os.path.join(dataset_root, 'sea/*.png'), recursive=False)  # 获取所有负样本的相对路径
    random.shuffle(neg_samples)  # 打乱读取的负样本的顺序，增加随机性
    pos_samples = glob(os.path.join(dataset_root, 'ship/*.png'), recursive=False)  # 获取所有正样本的相对路径
    random.shuffle(pos_samples)  # 打乱读取的正样本的顺序，增加随机性
    num_neg_samples = len(neg_samples)  # 获取负样本的数量
    num_pos_samples = len(pos_samples)  # 获取正样本的数量

    
    '''根据训练集的比例，计算要从负样本中抽取的用于训练的负样本数量。
    根据这个数量，随机从负样本中采样作为训练集，然后剩下的样本作为负样本的测试集。'''
    num_neg_training_samples = round(num_neg_samples * train_ratio)  # 计算负样本用于训练的样本数量
    neg_training_samples = random.sample(neg_samples, num_neg_training_samples)  # 对负样本训练集进行随机采样
    neg_testing_samples = [x for x in neg_samples if x not in neg_training_samples]  # 剩下的负样本作为测试集

    '''同理可对正样本做训练集和测试集的采样'''
    num_pos_training_samples = round(num_pos_samples * train_ratio)
    pos_training_samples = random.sample(pos_samples, num_pos_training_samples)
    pos_testing_samples = [x for x in pos_samples if x not in pos_training_samples]

    
    '''完成正负样本的训练集测试集采样后，我们需要将原始没有划分好的数据组织成为一个划分好的结构。'''
    '''即需要在data文件夹下新建一个train文件夹和一个val文件夹，前者存储划分为训练集的图像，后者存储划分为测试集的图像'''
    '''首先对训练集进行组织'''
    train_dir = os.path.join(dataset_root, 'train/')  # 首先确定训练集文件夹的路径
    if os.path.exists(train_dir):  # 防止重复存入文件，每次划分数据集的时候，清除之前建立的训练集文件夹
        shutil.rmtree(train_dir)
    os.makedirs(os.path.join(train_dir, 'sea/'))  # 在train文件夹下新建两个代表不同类别的文件夹，用于存储两类图像数据
    os.makedirs(os.path.join(train_dir, 'ship/'))
    for neg_train_sample in neg_training_samples:  # 将非船舶类别的训练图像数据复制到训练集中的sea文件夹中
        shutil.copyfile(
            src=neg_train_sample,
            dst=os.path.join(dataset_root, f'train/sea/{Path(neg_train_sample).name}')
        )
    for pos_train_sample in pos_training_samples:  # 将船舶类别的训练图像数据复制到训练集中的ship文件夹中
        shutil.copyfile(
            src=pos_train_sample,
            dst=os.path.join(dataset_root, f'train/ship/{Path(pos_train_sample).name}')
        )

    '''完成对训练集的组织后，对测试集进行组织，方法与训练集的组织方式相似'''
    test_dir = os.path.join(dataset_root, 'val/')  # 同样首先确定测试集文件夹的路径
    if os.path.exists(test_dir):  # 确保文件夹为空
        shutil.rmtree(test_dir)
    os.makedirs(os.path.join(test_dir, 'sea/'))  # 同样代表两个类的文件夹
    os.makedirs(os.path.join(test_dir, 'ship/'))
    for neg_test_sample in neg_testing_samples:
        shutil.copyfile(
            src=neg_test_sample,
            dst = os.path.join(dataset_root, f'val/sea/{Path(neg_test_sample).name}')
        )
    for pos_test_sample in pos_testing_samples:
        shutil.copyfile(
            src=pos_test_sample,
            dst=os.path.join(dataset_root, f'val/ship/{Path(pos_test_sample).name}')
        )

    '''完成以上数据组织之后，数据集的划分任务即完成'''
    '''可以到data文件夹下，此时可以发现出现了两个新建的文件夹train和val，其中分别存储着两类图像'''


def arbitrary_processor(dataset_root: str):
    # neg_samples = glob(os.path.join(dataset_root, 'sea/*.png'), recursive=False)
    # num_neg = len(neg_samples)
    # pos_samples = glob(os.path.join(dataset_root, 'ship/*.png'), recursive=False)
    # num_pos = len(pos_samples)
    #
    # random_neg_train_num = random.randint(num_neg // 10, num_neg)
    # random_pos_train_num = random.randint(num_pos // 10, num_pos)
    # neg_trainset, net_testset = [], []
    # for i in range(random_neg_train_num):
    #     neg_trainset.append()
    pass




if __name__ == "__main__":
    arguments = get_arguments()
    processor(dataset_root=arguments.dataset_root,
              train_ratio=arguments.train_ratio)
