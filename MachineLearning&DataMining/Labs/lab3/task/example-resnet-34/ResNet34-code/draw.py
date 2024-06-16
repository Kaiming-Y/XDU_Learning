"""
这份代码在train.py代码运行完毕（即网络训练完成后）再运行，会生成训练损失函数曲线和训练准确度曲线。
损失函数曲线应当是先快速下降然后逐渐收敛；训练准确度曲线应当是先快速上升然后逐步平稳。
"""
import os
import json
import argparse
import matplotlib.pyplot as plt

def get_arguments():
    parser = argparse.ArgumentParser()
    parser.add_argument('--json_path',
                        default='./training_statistic.json',
                        type=str,
                        help='在训练时生成的training_statistic.json文件的路径。其中存储了网络训练过程中的损失和精度数据')
    parser.add_argument('--save_dir',
                        default='./',
                        type=str,
                        help='存储绘制曲线图的路径')
    return parser.parse_args()

def draw_plots(json_path: str,
               save_dir: str):

    with open(json_path, 'r') as f:
        statistics = json.load(f)

    loss, accuracy = statistics['loss'], statistics['accuracy']

    '''保存损失曲线'''
    plt.figure(1)
    plt.plot(range(len(loss)), loss)
    plt.xlabel('Epoch')
    plt.ylabel('Loss')
    plt.title('Loss curve of training')
    plt.savefig(os.path.join(save_dir, 'train_loss.png'), dpi=600)
    plt.show()

    '''保存精度曲线'''
    plt.figure(2)
    plt.plot(range(len(accuracy)), accuracy)
    plt.xlabel('Epoch')
    plt.ylabel('Accuracy')
    plt.title('Accuracy curve of training')
    plt.savefig(os.path.join(save_dir, 'train_accuracy.png'), dpi=600)
    plt.show()


if __name__ == '__main__':
    args = get_arguments()
    draw_plots(args.json_path, args.save_dir)