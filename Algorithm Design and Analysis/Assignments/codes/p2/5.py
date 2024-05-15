# Shortest path in multistage graphs.

def get_min_distance_node(distances, visited):
    min_distance = float('inf')
    min_distance_node = None
    for node in distances:
        if node not in visited and distances[node] < min_distance:
            min_distance = distances[node]
            min_distance_node = node
    return min_distance_node


# 图
graph = {
    0: {1: 5, 2: 3},
    1: {3: 1, 4: 3},
    2: {4: 8, 5: 7},
    3: {6: 6, 7: 8},
    4: {7: 3, 8: 5},
    5: {8: 6},
    6: {9: 3},
    7: {9: 2, 10: 2},
    8: {10: 1, 11: 2, 12: 3},
    9: {13: 3},
    10: {13: 3, 14: 5},
    11: {14: 2},
    12: {14: 6},
    13: {15: 4},
    14: {15: 3},
    15: {}
}
# 每个节点到起点的最短路径长度
distances = {node: float('inf') for node in graph}
distances[0] = 0
# 前驱节点
predecessors = {node: None for node in graph}
# 访问过的节点
visited = set()
# 当前节点
current_node = 0
# 终点
target = 15
# 最短路径
shortest_path = []

while current_node is not None:
    visited.add(current_node)
    for neighbor, weight in graph[current_node].items():
        if neighbor not in visited:
            new_distance = distances[current_node] + weight
            if new_distance < distances[neighbor]:
                distances[neighbor] = new_distance
                predecessors[neighbor] = current_node
    current_node = get_min_distance_node(distances, visited)

while target is not None:
    shortest_path.insert(0, target)
    target = predecessors[target]

shortest_path_length = distances[15]

print(shortest_path, shortest_path_length)
