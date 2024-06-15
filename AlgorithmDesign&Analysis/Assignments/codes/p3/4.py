def floyd_warshall(matrix):
    n = len(matrix)
    distance = [[float('inf')] * n for _ in range(n)]

    for i in range(n):
        for j in range(n):
            if matrix[i][j] is not None:
                distance[i][j] = matrix[i][j]
        distance[i][i] = 0

    for k in range(n):
        for i in range(n):
            for j in range(n):
                distance[i][j] = min(distance[i][j], distance[i][k] + distance[k][j])

    return distance


adj_matrix = [
    [float('inf'), -1, 3, float('inf'), float('inf')],
    [float('inf'), float('inf'), 3, 2, 2],
    [float('inf'), float('inf'), float('inf'), float('inf'), float('inf')],
    [float('inf'), 1, 5, float('inf'), float('inf')],
    [float('inf'), float('inf'), float('inf'), -3, float('inf')]
]

distances = floyd_warshall(adj_matrix)
for row in distances:
    print(row)
