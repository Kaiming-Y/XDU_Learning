from graphviz import Digraph
import pandas as pd
import numpy as np


# 计算信息熵
def cal_information_entropy(data):
    data_label = data.iloc[:, -1]
    label_class = data_label.value_counts()
    Ent = 0
    for k in label_class.keys():
        p_k = label_class[k] / len(data_label)
        Ent += -p_k * np.log2(p_k)
    return Ent


# 计算特征的固有熵
def cal_intrinsic_value(data, a):
    feature_class = data[a].value_counts()
    IV = 0
    for v in feature_class.keys():
        p = feature_class[v] / data.shape[0]
        IV += -p * np.log2(p) if p > 0 else 0
    return IV


# 计算给定数据属性a的信息增益比
def cal_information_gain_ratio(data, a):
    IG = cal_information_gain(data, a)
    IV = cal_intrinsic_value(data, a)
    if IV == 0:  # 避免除以0
        return 0
    return IG / IV


# 计算信息增益
def cal_information_gain(data, a):
    Ent = cal_information_entropy(data)
    feature_class = data[a].value_counts()
    gain = 0
    for v in feature_class.keys():
        weight = feature_class[v] / data.shape[0]
        Ent_v = cal_information_entropy(data.loc[data[a] == v])
        gain += weight * Ent_v
    return Ent - gain


# 挑选最优特征，即信息增益比最大的特征
def get_best_feature(data):
    features = data.columns[:-1]
    res = {}
    for a in features:
        temp = cal_information_gain_ratio(data, a)
        res[a] = temp
    res = sorted(res.items(), key=lambda x: x[1], reverse=True)
    return res[0][0]


# 将数据转化为（属性值：数据）的元组形式返回，并删除之前的特征列
def drop_exist_feature(data, best_feature):
    attr = pd.unique(data[best_feature])
    new_data = [(nd, data[data[best_feature] == nd]) for nd in attr]
    new_data = [(n[0], n[1].drop([best_feature], axis=1)) for n in new_data]
    return new_data


# 获取标签最多的那一类
def get_most_label(data):
    data_label = data.iloc[:, -1]
    label_sort = data_label.value_counts(sort=True)
    return label_sort.keys()[0]


# 创建决策树
def create_tree(data):
    data_label = data.iloc[:, -1]
    if len(data_label.value_counts()) == 1:  # 只有一类
        return data_label.values[0]
    if all(len(data[i].value_counts()) == 1 for i in data.iloc[:, :-1].columns):  # 所有数据的特征值一样，选样本最多的类作为分类结果
        return get_most_label(data)
    best_feature = get_best_feature(data)  # 根据信息增益得到的最优划分特征
    Tree = {best_feature: {}}  # 用字典形式存储决策树
    exist_vals = pd.unique(data[best_feature])  # 当前数据下最佳特征的取值
    if len(exist_vals) != len(column_count[best_feature]):  # 如果特征的取值相比于原来的少了
        no_exist_attr = set(column_count[best_feature]) - set(exist_vals)  # 少的那些特征
        for no_feat in no_exist_attr:
            Tree[best_feature][no_feat] = get_most_label(data)  # 缺失的特征分类为当前类别最多的

    for item in drop_exist_feature(data, best_feature):  # 根据特征值的不同递归创建决策树
        Tree[best_feature][item[0]] = create_tree(item[1])
    return Tree


def predict(Tree, test_data):
    first_feature = list(Tree.keys())[0]
    second_dict = Tree[first_feature]
    input_first = test_data.get(first_feature)
    input_value = second_dict[input_first]
    if isinstance(input_value, dict):  # 判断分支还是不是字典
        class_label = predict(input_value, test_data)
    else:
        class_label = input_value
    return class_label


def plot_decision_tree(tree, parent=None, edge_label='', graph=None):
    if graph is None:
        graph = Digraph('DecisionTree', format='png')
        graph.attr(rankdir='TB', size='10,10')
        graph.attr(dpi='500')
        graph.attr('node', shape='rectangle', style='rounded', fontname='Microsoft YaHei')
        graph.attr('edge', fontname='Microsoft YaHei', fontsize='10')

    if isinstance(tree, dict):
        for node, branches in tree.items():
            node_name = f"{node}"
            if parent is None:
                # 根节点
                graph.node(node_name, label=node_name)
                current_parent = node_name
            else:
                # 决策节点
                current_parent = f"{parent}_{edge_label}"
                graph.node(current_parent, label=node_name)
                graph.edge(parent, current_parent, label=edge_label)

            if isinstance(branches, dict):
                for value, subtree in branches.items():
                    plot_decision_tree(subtree, current_parent, value, graph)
            else:
                # 叶节点
                leaf_label = '好瓜' if branches == 1 else '坏瓜'
                leaf_node = f"{current_parent}_{edge_label}_leaf"
                graph.node(leaf_node, label=leaf_label, shape='ellipse', style='filled', color='lightgreen' if branches == 1 else 'lightcoral')
                graph.edge(current_parent, leaf_node, label=edge_label)
    else:
        # 处理叶节点情况
        leaf_label = '好瓜' if tree == 1 else '坏瓜'
        leaf_node = f"{parent}_{edge_label}_leaf"
        graph.node(leaf_node, label=leaf_label, shape='ellipse', style='filled', color='lightgreen' if tree == 1 else 'lightcoral')
        graph.edge(parent, leaf_node, label=edge_label)

    return graph


if __name__ == '__main__':
    # 读取数据
    data = pd.read_csv('../data/西瓜数据集2.0.csv')

    # 统计每个特征的取值情况作为全局变量
    column_count = dict([(ds, list(pd.unique(data[ds]))) for ds in data.iloc[:, :-1].columns])

    # 创建决策树
    decision_Tree = create_tree(data)
    print('Decision_Tree Model:', decision_Tree)
    tree_graph = plot_decision_tree(decision_Tree)
    tree_graph.render('../output/decision_tree_C45', view=True)

    # 测试数据
    test_data_1 = {'色泽': '青绿', '根蒂': '蜷缩', '敲声': '浊响', '纹理': '稍糊', '脐部': '凹陷', '触感': '硬滑'}
    test_data_2 = {'色泽': '乌黑', '根蒂': '稍蜷', '敲声': '浊响', '纹理': '清晰', '脐部': '凹陷', '触感': '硬滑'}
    result1 = predict(decision_Tree, test_data_1)
    result2 = predict(decision_Tree, test_data_2)

    # 输出决策树分类结果
    print('测试数据:', f'{test_data_1 = }')  # 针对测试数据 test_data_1
    print('分类结果: ' '好瓜' if result1 == 1 else '分类结果: ''坏瓜')

    print('测试数据:', f'{test_data_2 = }')  # 针对测试数据 test_data_2
    print('分类结果: ' '好瓜' if result2 == 1 else '分类结果: ''坏瓜')
