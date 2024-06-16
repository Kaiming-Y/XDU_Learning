# Resnet

## 说明

本代码来源于 https://github.com/WZMIAOMIAO/deep-learning-for-image-processing/tree/master/pytorch_classification/Test5_resnet

本代码在此基础上写了大量注释，更加便于学习

论文：https://arxiv.org/abs/1512.03385

## 文件结构：

```
  ├── data文件夹: 用于存放图像数据
  ├── weight文件夹: 用于存放预训练权重文件，以及网络训练过程中产生的最优权重文件
  ├── batch_predict.py: 用于检查置信度不高/分类错误图像是哪些的脚本
  ├── model.py: 定义了ResNet网络结构的脚本
  ├── train.py: 用于网络训练的脚本
  ├── draw.py: 用于绘制网络训练时的损失曲线和准确度曲线
  ├── dataset_processor.py: 按照PyTorch的接口要求，将原始数据集划分为训练集/测试集
  └── test.py: 用于测试训练好的网络性能的脚本，计算各种分类评价指标数据
```

## 环境安装：

1. 安装Anaconda，然后创建一个环境：

``` shell
conda create -n new_envn python=3.9
```

2. 创建完毕环境后，激活环境：

``` shell
conda activate new_envn
```

3. 在激活后的环境中安装PyTorch。移步至PyTorch官网下载对应版本：如果所使用的电脑没有适合深度学习的GPU设备，那么运行以下代码：

``` shell
conda install pytorch torchvision torchaudio cpuonly -c pytorch
```

否则，参考[这篇文章](https://blog.csdn.net/m0_57757248/article/details/123484569)来安装适合自己电脑硬件的CUDA、cuDNN和PyTorch环境。

4. 在代码所在的项目文件夹的根目录下打开命令行，输入以下代码：

``` shell
pip install -r requirements.txt
```

5. 安装完毕环境后，即可使用该环境运行训练和测试等脚本。可供参考的基于PyCharm使用本地创建的Conda环境来运行程序的教程[点这里](https://blog.csdn.net/weixin_42641207/article/details/120612850)

### 需要注意的地方：

  - 如果遇到安装conda环境/使用pip安装环境时速度很慢，或者出现HTTP相关的报错问题，可以参考[这篇文章](https://blog.csdn.net/weixin_45755332/article/details/109244461)尝试解决；
  - 要注意安装PyTorch的版本。每一位同学的电脑硬件和软件环境都是不一样的，在安装环境的时候可能会遇到各种各样的问题。建议大家在安装CUDA时选择11.3版本进行安装（如果安装不上的话再考虑安装其他适合电脑的版本），因为11.3版本能够支持本代码成功运行，并且PyTorch官网的1.11.0版本稳定支持该版本的CUDA。
  - 代码在Windows和Linux上运行所需要的环境是不同的，配置的过程也是有区别的，同学们在查阅相关资料的时候需要注意这一点。在Linux上配置环境的情况一般是拥有专用于深度学习的服务器，然后使用该服务器进行远程调试。
    1. SSH连接远程服务器教程 [点这里](https://blog.csdn.net/qq_37665301/article/details/116031615)
    2. 在Linux上安装PyTorch环境的教程 [点这里](https://blog.csdn.net/dunwin/article/details/118193453)
    3. 使用PyCharm配置远程Python解释器 [点这里](https://blog.csdn.net/ft_sunshine/article/details/91894221)

## 使用方法：

根据需要的resnet模型，下载预训练权重，然后运行train.py脚本。在本次实验中我们使用的是ResNet-34网络，且网络预训练权重已经提供并且放在`weight`文件夹中，因此无需重复下载。

model_urls = {
    'resnet18': 'https://download.pytorch.org/models/resnet18-5c106cde.pth',
    'resnet34': 'https://download.pytorch.org/models/resnet34-333f7ec4.pth',
    'resnet50': 'https://download.pytorch.org/models/resnet50-19c8e357.pth',
    'resnet101': 'https://download.pytorch.org/models/resnet101-5d3b4d8f.pth',
    'resnet152': 'https://download.pytorch.org/models/resnet152-b121ed2d.pth',
    'resnext50_32x4d': 'https://download.pytorch.org/models/resnext50_32x4d-7cdf4587.pth',
    'resnext101_32x8d': 'https://download.pytorch.org/models/resnext101_32x8d-8ba56ff5.pth',
    'wide_resnet50_2': 'https://download.pytorch.org/models/wide_resnet50_2-95faca4d.pth',
    'wide_resnet101_2': 'https://download.pytorch.org/models/wide_resnet101_2-32ee1156.pth',
}

## 数据集：

数据集文件是一个压缩包，直接将其中的内容解压到`data`文件夹即可。

## 相关博文：

> 知乎关于resnet的论文笔记——ResNet精读-残差连接使网络大大加深：

https://zhuanlan.zhihu.com/p/478096991

