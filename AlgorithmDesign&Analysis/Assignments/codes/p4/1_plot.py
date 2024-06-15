import matplotlib.pyplot as plt
import networkx as nx

values = [20, 30, 65, 40, 60]
weights = [10, 20, 30, 40, 50]
max_weight = 100


def cal_weight(taken):
    return sum(weights[i] for i in taken)


def cal_value(taken):
    return sum(values[i] for i in taken)


def knapsack(idx, taken, G, pos, node_id=0, level=0, x=0):
    current_label = f"Node {node_id}"
    G.add_node(current_label, label=f"Item {idx+1}" if idx < len(values) else f"Value: {cal_value(taken)}")

    if idx < len(values):
        pos[current_label] = (x, -level)
    else:
        G.nodes[current_label]['shape'] = 's'
        G.nodes[current_label]['style'] = 'filled'
        G.nodes[current_label]['fillcolor'] = 'lightgreen'
        G.nodes[current_label]['label'] = f"{cal_value(taken)}"

    if idx >= len(values):
        return

    no_take_label = f"Node {node_id*2+1}"
    G.add_node(no_take_label)
    pos[no_take_label] = (x - 2**(5-level), -level-1)
    G.add_edge(current_label, no_take_label, label="no_take")
    knapsack(idx+1, taken, G, pos, node_id*2+1, level+1, x-2**(5-level))

    if sum(weights[i] for i in taken + [idx]) <= max_weight:
        take_label = f"Node {node_id*2+2}"
        G.add_node(take_label)
        pos[take_label] = (x + 2**(5-level), -level-1)
        G.add_edge(current_label, take_label, label="take")
        knapsack(idx+1, taken + [idx], G, pos, node_id*2+2, level+1, x+2**(5-level))


def visualize_decision_tree(G, pos):
    plt.figure(figsize=(20, 12))
    node_labels = nx.get_node_attributes(G, 'label')
    colors = [G.nodes[node].get('fillcolor', 'skyblue') for node in G]
    nx.draw(G, pos, with_labels=True, labels=node_labels, node_color=colors, node_size=2000)
    edge_labels = nx.get_edge_attributes(G, 'label')
    nx.draw_networkx_edge_labels(G, pos, edge_labels=edge_labels)
    plt.show()


G = nx.DiGraph()
pos = {}
knapsack(0, [], G, pos)
visualize_decision_tree(G, pos)
