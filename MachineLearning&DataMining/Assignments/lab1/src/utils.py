import numpy as np


def sigmoid(z):
    return 1 / (1 + np.exp(-z))


def compute_cost(X, y, w, b, lambda_=0.0):
    m = X.shape[0]
    Z = np.dot(X, w) + b
    A = sigmoid(Z)
    loss = -y * np.log(A) - (1 - y) * np.log(1 - A)
    total_cost = (1 / m) * np.sum(loss)
    regularization = (lambda_ / (2 * m)) * np.sum(np.square(w))
    total_cost += regularization

    return total_cost
