# 回溯法解决0-1背包问题

values = [20, 30, 65, 40, 60]
weights = [10, 20, 30, 40, 50]
max_weight = 100


def cal_weight(taken_list: list) -> int:
    return sum(weights[idx] for idx in taken_list)


def cal_value(taken_list: list) -> int:
    return sum(values[idx] for idx in taken_list)


def knapsack(idx: int, taken_list: list) -> list:
    if idx >= len(values):
        return taken_list.copy()

    # 不拿当前物品
    no_take = knapsack(idx + 1, taken_list.copy())

    # 拿当前物品
    if cal_weight(taken_list) + weights[idx] <= max_weight:
        taken_list.append(idx)
        take = knapsack(idx + 1, taken_list.copy())
        if cal_value(take) > cal_value(no_take):
            return take
        else:
            return no_take
    else:
        return no_take


taken_list = []
taken_list = knapsack(0, taken_list)

print("Maximum Value:", cal_value(taken_list))
print("Current Weight:", cal_weight(taken_list))
print("Taken List:", taken_list)
