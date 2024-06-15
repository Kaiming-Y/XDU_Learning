# Matrix-chain product.
# The following are some instances.
# a) <3, 5, 2, 1,10>
# b) <2, 7, 3, 6, 10>
# c) <10, 3, 15, 12, 7, 2>
# d) <7, 2, 4, 15, 20, 5>

def matrix_chain_order(p):
    matrix_count = len(p) - 1
    # m[begin,end] 表示计算矩阵 A[begin]...A[end] 所需的最少乘法次数
    m = [[0 for _ in range(matrix_count)] for _ in range(matrix_count)]

    for chain_len in range(2, matrix_count + 1):
        for begin in range(matrix_count - chain_len + 1):
            end = begin + chain_len - 1
            m[begin][end] = float('inf')
            # 分割点
            for k in range(begin, end):
                # q 是计算 (A[begin]...A[k]) 和 (A[k+1]...A[end]) 乘积以及这两部分相乘的成本
                q = m[begin][k] + m[k + 1][end] + p[begin] * p[k + 1] * p[end + 1]
                if q < m[begin][end]:
                    m[begin][end] = q
    return m[0][matrix_count - 1]


instances = [
    [3, 5, 2, 1, 10],
    [2, 7, 3, 6, 10],
    [10, 3, 15, 12, 7, 2],
    [7, 2, 4, 15, 20, 5]
]

results = [matrix_chain_order(p) for p in instances]

for i in range(len(results)):
    print(results[i])
