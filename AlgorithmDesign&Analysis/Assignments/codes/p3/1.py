# Fractional Knapsack Problem & 0/1 Knapsack Problem

from typing import List, Tuple


def fractional_knapsack(value_weight_pairs: List[Tuple[int]], max_weight: int) -> float:
    items = sorted(value_weight_pairs, key=lambda x: x[0] / x[1], reverse=True)

    total_value = 0
    for value, weight in items:
        if max_weight - weight >= 0:
            max_weight -= weight
            total_value += value
        else:
            total_value += value * (max_weight / weight)
            break

    return total_value


def knapsack_01(value_weight_pairs: List[Tuple[int]], max_weight: int) -> int:
    n = len(value_weight_pairs)
    values = [v for v, w in value_weight_pairs]
    weights = [w for v, w in value_weight_pairs]

    dp = [[0 for _ in range(max_weight + 1)] for _ in range(n + 1)]

    for i in range(n + 1):
        for w in range(max_weight + 1):
            if i == 0 or w == 0:
                dp[i][w] = 0
            elif weights[i - 1] <= w:
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w])
            else:
                dp[i][w] = dp[i - 1][w]

    return dp[n][max_weight]


value_weight_pairs = [(20, 10), (30, 20), (65, 30), (40, 40), (60, 50)]
max_weight = 80

max_fractional_value = fractional_knapsack(value_weight_pairs, max_weight)
print(max_fractional_value)

max_01_value = knapsack_01(value_weight_pairs, max_weight)
print(max_01_value)
