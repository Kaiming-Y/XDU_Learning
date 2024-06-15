import math
import pandas as pd
import numpy as np
from numpy.linalg import inv
import matplotlib.pyplot as plt
from utils import sigmoid, compute_cost


def compute_newton_update(X, y, w, b):
    m = X.shape[0]
    Z = np.dot(X, w) + b
    A = sigmoid(Z)
    error = A - y

    # 计算梯度
    gradient_w = (1 / m) * np.dot(X.T, error)
    gradient_b = (1 / m) * np.sum(error)

    # 计算Hessian矩阵
    S = np.diag(A * (1 - A))
    H = np.dot(np.dot(X.T, S), X) / m

    # 更新参数
    w_update = np.dot(inv(H), gradient_w)
    b_update = gradient_b

    return w_update, b_update


def newton_method(X, y, initial_w, initial_b, num_iterations):
    w = initial_w
    b = initial_b
    cost_history = []

    for i in range(num_iterations):
        w_update, b_update = compute_newton_update(X, y, w, b)
        w -= w_update
        b -= b_update

        cost = compute_cost(X, y, w, b)
        cost_history.append((i, cost))

        if i % math.ceil(num_iterations / 10) == 0 or i == (num_iterations-1):
            print(f"[Newton Method] Iteration {i:4}: cost {float(cost):.4f}")

    return w, b, cost_history


def train_newton_method(X, y, num_iterations):
    m, n = X.shape

    # 初始化参数
    initial_w = np.zeros(n)
    initial_b = 0

    # 训练模型
    w, b, cost_history = newton_method(X, y, initial_w, initial_b, num_iterations)

    return w, b, cost_history


if __name__ == '__main__':
    df = pd.read_csv('../data/watermelon3.0alpha.csv')
    X = df[['density', 'Sugar_content']].values
    y = df['label'].values
    m, n = X.shape

    # 训练模型
    w, b = train_newton_method(X, y, num_iterations=500)

    # 绘制原始数据的散点图
    plt.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='red', label='Class 0')
    plt.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='blue', label='Class 1')

    # 绘制决策边界
    x_values = np.array([np.min(X[:, 0] - 0.1), np.max(X[:, 0] + 0.1)])
    y_values = - (b + np.dot(w[0], x_values)) / w[1]
    plt.plot(x_values, y_values, label='Newton Method')

    plt.xlabel('Density')
    plt.ylabel('Sugar Content')
    plt.title("Logistic Regression")
    plt.legend()
    plt.show()
