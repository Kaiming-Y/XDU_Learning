from src.LogisticRegression_GradientDescent import train_gradient_descent
from src.LogisticRegression_Newton import train_newton_method
from utils import sigmoid
from datetime import datetime
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np


learning_rate = 0.1
reg_param = 0.0
num_iterations_gd = 200000
num_iterations_nt = 1000


def plot_decision_boundaries(X, y, w_gd, b_gd, w_nt, b_nt):
    # 设置图像大小
    plt.figure(figsize=(10, 8))

    # 生成网格点的坐标矩阵
    x_min, x_max = X[:, 0].min() - 0.1, X[:, 0].max() + 0.1
    y_min, y_max = X[:, 1].min() - 0.1, X[:, 1].max() + 0.1
    xx, yy = np.meshgrid(np.linspace(x_min, x_max, 1000), np.linspace(y_min, y_max, 1000))

    # 预测网格点的值-梯度下降法
    Z_gd = sigmoid(np.dot(np.c_[xx.ravel(), yy.ravel(), np.ones_like(xx.ravel())], w_gd) + b_gd)
    Z_gd = Z_gd.reshape(xx.shape)

    # 预测网格点的值-牛顿法
    Z_nt = sigmoid(np.dot(np.c_[xx.ravel(), yy.ravel()], w_nt) + b_nt)
    Z_nt = Z_nt.reshape(xx.shape)

    # 绘制等高线图-梯度下降法
    plt.contour(xx, yy, Z_gd, levels=[0.5], linestyles="solid", colors='orange', linewidths=2)

    # 绘制等高线图-牛顿法
    plt.contour(xx, yy, Z_nt, levels=[0.5], linestyles="solid", colors='blue', linewidths=2)

    # 绘制原始数据的散点图
    plt.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='red', marker='x', label='Class 0')
    plt.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='green', marker='o', label='Class 1')

    # 为了图例正确显示决策边界
    plt.plot([], [], color='orange', linewidth=2, linestyle="solid", label='Gradient Descent')
    plt.plot([], [], color='blue', linewidth=2, linestyle="solid", label="Newton's Method")

    # 显示图例
    plt.legend()

    # 打印参数
    plt.text(0.15, 0.54, f'Learning Rate(α): {learning_rate}', fontsize=10)
    plt.text(0.15, 0.52, f'Regularization Parameter(λ): {reg_param}', fontsize=10)
    plt.text(0.15, 0.50, f'Gradient Descent Iterations: {num_iterations_gd}', fontsize=10)
    plt.text(0.15, 0.48, f'Newton Method Iterations: {num_iterations_nt}', fontsize=10)

    plt.xlabel('Density')
    plt.ylabel('Sugar Content')
    plt.title("Logistic Regression")
    current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
    plt.savefig(f'../fig/Logistic_Regression_{current_time}.png', dpi=300)
    plt.show()


def plot_cost_history(cost_history_gd, cost_history_nt):
    iterations_gd, costs_gd = zip(*cost_history_gd)
    iterations_nt, costs_nt = zip(*cost_history_nt)

    fig, axs = plt.subplots(1, 2, figsize=(20, 8))

    # 绘制梯度下降法的损失值变化
    axs[0].plot(iterations_gd, costs_gd, label='Gradient Descent', color='blue', linewidth=2)
    axs[0].set_title('Gradient Descent Cost History Over Iterations')
    axs[0].set_xlabel('Iteration')
    axs[0].set_ylabel('Cost')
    axs[0].legend()
    axs[0].grid(True)
    # axs[0].set_yscale('log')

    # 绘制牛顿法的损失值变化
    axs[1].plot(iterations_nt, costs_nt, label="Newton's Method", color='red', linewidth=2)
    axs[1].set_title("Newton's Method Cost History Over Iterations")
    axs[1].set_xlabel('Iteration')
    axs[1].set_ylabel('Cost')
    axs[1].legend()
    axs[1].grid(True)
    # axs[1].set_yscale('log')

    plt.tight_layout()
    current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
    plt.savefig(f'../fig/Cost_History_{current_time}.png', dpi=600)
    plt.show()


def plot_cost_history_gd(cost_history_gd):
    iterations_gd, costs_gd = zip(*cost_history_gd)

    plt.figure(figsize=(10, 8))

    # 绘制梯度下降法的损失值变化
    plt.plot(iterations_gd, costs_gd, label='Gradient Descent', color='blue', linewidth=2)
    plt.title('Gradient Descent Cost History Over Iterations')
    plt.xlabel('Iteration')
    plt.ylabel('Cost')
    plt.legend()
    plt.grid(True)
    # plt.yscale('log')

    current_time = datetime.now().strftime('%Y-%m-%d_%H-%M-%S')
    plt.savefig(f'../fig/Cost_History_Gradient_Descent_{current_time}.png', dpi=300)
    plt.show()


if __name__ == '__main__':
    df = pd.read_csv('../data/watermelon3.0alpha.csv')
    X = df[['density', 'Sugar_content']].values
    y = df['label'].values
    m, n = X.shape

    # 梯度下降法训练模型
    w_gd, b_gd, cost_history_gd = train_gradient_descent(X, y, alpha=learning_rate, num_iterations=num_iterations_gd, lambda_=reg_param)

    # 牛顿法训练模型
    w_nt, b_nt, cost_history_nt = train_newton_method(X, y, num_iterations=num_iterations_nt)

    # 绘制原始数据的散点图以及两种方法的决策边界
    plot_decision_boundaries(X, y, w_gd, b_gd, w_nt, b_nt)

    # 绘制损失函数收敛情况
    plot_cost_history(cost_history_gd, cost_history_nt)
    plot_cost_history_gd(cost_history_gd)
