import math
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from utils import sigmoid, compute_cost


def compute_gradient(X, y, w, b, lambda_=0.0):
    m = X.shape[0]
    Z = np.dot(X, w) + b
    A = sigmoid(Z)
    error = A - y
    dj_dw = (1 / m) * np.dot(X.T, error) + (lambda_ / m) * w
    dj_db = (1 / m) * np.sum(error)
    return dj_db, dj_dw


def gradient_descent(X, y, w_in, b_in, cost_function, gradient_function, alpha, num_iterations, lambda_=0.0):
    cost_history = []

    for i in range(num_iterations):
        dj_db, dj_dw = gradient_function(X, y, w_in, b_in, lambda_)
        w_in = w_in - alpha * dj_dw
        b_in = b_in - alpha * dj_db

        cost = cost_function(X, y, w_in, b_in, lambda_)
        cost_history.append((i, cost))

        if i % math.ceil(num_iterations / 10) == 0 or i == (num_iterations - 1):
            print(f"[Gradient Descent] Iteration {i:4}: cost {float(cost):.4f}   ")

    return w_in, b_in, cost_history


def train_gradient_descent(X, y, alpha, num_iterations, lambda_):
    m, n = X.shape

    # 增加一个特征维度以匹配w的形状
    X = np.hstack((X, np.ones((m, 1))))  # 添加偏置项对应的x0=1

    # 初始化参数
    initial_w = np.zeros(n + 1)
    initial_b = 0

    # 训练模型
    w, b, cost_history = gradient_descent(X, y, initial_w, initial_b, compute_cost, compute_gradient, alpha,
                                          num_iterations, lambda_)

    return w, b, cost_history


if __name__ == '__main__':
    df = pd.read_csv('../data/watermelon3.0alpha.csv')
    X = df[['density', 'Sugar_content']].values
    y = df['label'].values
    m, n = X.shape

    # 训练模型
    w, b = train_gradient_descent(X, y, alpha=0.01, num_iterations=100000, lambda_=0.03)

    # 绘制原始数据的散点图
    plt.scatter(X[y == 0][:, 0], X[y == 0][:, 1], color='red', label='Class 0')
    plt.scatter(X[y == 1][:, 0], X[y == 1][:, 1], color='blue', label='Class 1')

    # 绘制决策边界
    x_values = [np.min(X[:, 0] - 0.1), np.max(X[:, 0] + 0.1)]
    y_values = - (b + np.dot(w[0], x_values)) / w[1]
    plt.plot(x_values, y_values, label='Gradient Descent')

    plt.xlabel('Density')
    plt.ylabel('Sugar Content')
    plt.title("Logistic Regression")
    plt.legend()
    plt.show()
