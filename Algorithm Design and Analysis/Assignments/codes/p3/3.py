# 3 Single-source shortest paths

import heapq


def bellman_ford(matrix, source):
    distance = [float('inf')] * len(matrix)
    distance[source] = 0

    for _ in range(len(matrix) - 1):
        for u in range(len(matrix)):
            for v in range(len(matrix)):
                if matrix[u][v] and distance[u] != float('inf') and distance[u] + matrix[u][v] < distance[v]:
                    distance[v] = distance[u] + matrix[u][v]

    # 负循环检测
    for u in range(len(matrix)):
        for v in range(len(matrix)):
            if matrix[u][v] and distance[u] != float('inf') and distance[u] + matrix[u][v] < distance[v]:
                print("负循环！")
                return None

    return distance


def dijkstra(matrix, start):
    distances = {vertex: float('infinity') for vertex in range(len(matrix))}
    distances[start] = 0
    priority_queue = [(0, start)]

    while priority_queue:
        current_distance, current_vertex = heapq.heappop(priority_queue)

        if current_distance > distances[current_vertex]:
            continue

        for neighbor, weight in enumerate(matrix[current_vertex]):
            if weight is not None and weight >= 0:
                distance = current_distance + weight

                if distance < distances[neighbor]:
                    distances[neighbor] = distance
                    heapq.heappush(priority_queue, (distance, neighbor))

    return distances


adj_matrix = [
    [None, -1, 3, None, None],
    [None, None, 3, 2, 2],
    [None, None, None, None, None],
    [None, 1, 5, None, None],
    [None, None, None, -3, None]
]

distances = bellman_ford(adj_matrix, 0)
print(distances)
