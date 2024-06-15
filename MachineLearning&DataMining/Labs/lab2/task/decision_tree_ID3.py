##### 实现基于信息增益作为属性划分准则来构造决策树，并在测试数据测试

import pandas as pd
import numpy as np

#计算信息熵
def cal_information_entropy(data):
    data_label = data.iloc[:,-1]
    label_class =data_label.value_counts() #总共有多少类
    Ent = 0
    for k in label_class.keys():
        p_k = label_class[k]/len(data_label)
        Ent += -p_k*np.log2(p_k)
    return Ent

#计算给定数据属性a的信息增益
def cal_information_gain(data, a):
    Ent = cal_information_entropy(data)
    feature_class = data[a].value_counts() #特征有多少种可能
    gain = 0
    for v in feature_class.keys():
        weight = feature_class[v]/data.shape[0]
        Ent_v = cal_information_entropy(data.loc[data[a] == v])
        gain += weight*Ent_v
    return Ent - gain

#获取标签最多的那一类
def get_most_label(data):
    data_label = data.iloc[:,-1]
    label_sort = data_label.value_counts(sort=True)
    return label_sort.keys()[0]

#挑选最优特征，即信息增益最大的特征
def get_best_feature(data):
    features = data.columns[:-1]
    res = {}
    for a in features:
        temp = cal_information_gain(data, a)
        res[a] = temp
    res = sorted(res.items(),key=lambda x:x[1],reverse=True)
    return res[0][0]

##将数据转化为（属性值：数据）的元组形式返回，并删除之前的特征列
def drop_exist_feature(data, best_feature):
    attr = pd.unique(data[best_feature])
    new_data = [(nd, data[data[best_feature] == nd]) for nd in attr]
    new_data = [(n[0], n[1].drop([best_feature], axis=1)) for n in new_data]
    return new_data

#创建决策树
def create_tree(data):
    data_label = data.iloc[:,-1]
    if len(data_label.value_counts()) == 1: #只有一类
        return data_label.values[0]
    if all(len(data[i].value_counts()) == 1 for i in data.iloc[:,:-1].columns): #所有数据的特征值一样，选样本最多的类作为分类结果
        return get_most_label(data)
    best_feature = get_best_feature(data) #根据信息增益得到的最优划分特征
    Tree = {best_feature:{}} #用字典形式存储决策树
    exist_vals = pd.unique(data[best_feature]) #当前数据下最佳特征的取值
    if len(exist_vals) != len(column_count[best_feature]): #如果特征的取值相比于原来的少了
        no_exist_attr = set(column_count[best_feature]) - set(exist_vals) #少的那些特征
        for no_feat in no_exist_attr:
            Tree[best_feature][no_feat] = get_most_label(data) #缺失的特征分类为当前类别最多的

    for item in drop_exist_feature(data,best_feature): #根据特征值的不同递归创建决策树
        Tree[best_feature][item[0]] = create_tree(item[1])
    return Tree

#{'纹理': {'清晰': {'根蒂': {'蜷缩': 1, '稍蜷': {'色泽': {'青绿': 1, '乌黑': {'触感': {'硬滑': 1, '软粘': 0}}}}, '硬挺': 0}}, '稍糊': {'触感': {'软粘': 1, '硬滑': 0}}, '模糊': 0}}
def predict(Tree , test_data):
    first_feature = list(Tree.keys())[0]
    second_dict = Tree[first_feature]
    input_first = test_data.get(first_feature)
    input_value = second_dict[input_first]
    if isinstance(input_value , dict): #判断分支还是不是字典
        class_label = predict(input_value, test_data)
    else:
        class_label = input_value
    return class_label

if __name__ == '__main__':
    #读取数据
    data = pd.read_csv('西瓜数据集2.0.csv')

    #统计每个特征的取值情况作为全局变量
    column_count = dict([(ds, list(pd.unique(data[ds]))) for ds in data.iloc[:, :-1].columns])

    #创建决策树
    decision_Tree = create_tree(data)
    print('Decision_Tree Model:', decision_Tree)

    #测试数据
    test_data_1 = {'色泽':'青绿','根蒂':'蜷缩','敲声':'浊响','纹理':'稍糊','脐部':'凹陷','触感':'硬滑'}
    test_data_2 = {'色泽': '乌黑', '根蒂': '稍蜷', '敲声': '浊响', '纹理': '清晰', '脐部': '凹陷', '触感': '硬滑'}
    result1 = predict(decision_Tree,test_data_1)
    result2 = predict(decision_Tree, test_data_2)

    # 输出决策树分类结果
    print('测试数据:', f'{test_data_1 = }') #针对测试数据 test_data_1
    print('分类结果: ' '好瓜' if result1 == 1 else '分类结果: ''坏瓜')

    print('测试数据:', f'{test_data_2 = }') #针对测试数据 test_data_1
    print('分类结果: ' '好瓜' if result2 == 1 else '分类结果: ''坏瓜')