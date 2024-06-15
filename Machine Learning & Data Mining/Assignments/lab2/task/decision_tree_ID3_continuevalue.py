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

#对于离散特征a，计算给定数据属性a的信息增益
def cal_information_gain(data, a):
    Ent = cal_information_entropy(data)
    feature_class = data[a].value_counts() #特征有多少种可能
    gain = 0
    for v in feature_class.keys():
        weight = feature_class[v]/data.shape[0]
        Ent_v = cal_information_entropy(data.loc[data[a] == v])
        gain += weight*Ent_v
    return Ent - gain

#对于连续特征b，计算给定数据属性b的信息增益
def cal_information_gain_continuous(data, a):
    n = len(data) #总共有n条数据，会产生n-1个划分点，选择信息增益最大的作为最优划分点
    data_a_value = sorted(data[a].values) #从小到大排序
    Ent = cal_information_entropy(data) #原始数据集的信息熵Ent(D)
    select_points = []
    for i in range(n-1):
        val = (data_a_value[i] + data_a_value[i+1]) / 2 #两个值中间取值为划分点
        data_left = data.loc[data[a]<val]
        data_right = data.loc[data[a]>val]
        ent_left = cal_information_entropy(data_left)
        ent_right = cal_information_entropy(data_right)
        result = Ent - len(data_left)/n * ent_left - len(data_right)/n * ent_right
        select_points.append([val, result])
    select_points.sort(key = lambda x : x[1], reverse= True) #按照信息增益排序
    return select_points[0][0], select_points[0][1] #返回信息增益最大的点, 以及对应的信息增益

#获取标签最多的那一类
def get_most_label(data):
    data_label = data.iloc[:,-1]
    label_sort = data_label.value_counts(sort=True)
    return label_sort.keys()[0]

#获取最佳划分特征
def get_best_feature(data):
    features = data.columns[:-1]
    res = {}
    for a in features:
        if a in continuous_features:
            temp_val, temp = cal_information_gain_continuous(data, a)
            res[a] = [temp_val, temp]
        else:
            temp = cal_information_gain(data, a)
            res[a] = [-1, temp] #离散值没有划分点，用-1代替

    res = sorted(res.items(),key=lambda x:x[1][1],reverse=True)
    return res[0][0],res[0][1][0]

#将数据转化为（属性值：数据）的元组形式返回，并删除之前的特征列，只针对离散数据
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
    best_feature, best_feature_val = get_best_feature(data) #根据信息增益得到的最优划分特征
    if best_feature in continuous_features: #连续值
        node_name = best_feature + '<' + str(best_feature_val)
        Tree = {node_name:{}} #用字典形式存储决策树
        Tree[node_name]['是'] = create_tree(data.loc[data[best_feature] < best_feature_val])
        Tree[node_name]['否'] = create_tree(data.loc[data[best_feature] > best_feature_val])
    else:
        Tree = {best_feature:{}}
        exist_vals = pd.unique(data[best_feature])  # 当前数据下最佳特征的取值
        if len(exist_vals) != len(column_count[best_feature]):  # 如果特征的取值相比于原来的少了
            no_exist_attr = set(column_count[best_feature]) - set(exist_vals)  # 少的那些特征
            for no_feat in no_exist_attr:
                Tree[best_feature][no_feat] = get_most_label(data)  # 缺失的特征分类为当前类别最多的
        for item in drop_exist_feature(data, best_feature):  # 根据特征值的不同递归创建决策树
            Tree[best_feature][item[0]] = create_tree(item[1])
    return Tree

#根据创建的决策树进行分类
def predict(Tree , test_data):
    first_feature = list(Tree.keys())[0]
    if (feature_name:= first_feature.split('<')[0]) in continuous_features:
        second_dict = Tree[first_feature]
        val = float(first_feature.split('<')[-1])
        input_first = test_data.get(feature_name)
        if input_first < val:
            input_value = second_dict['是']
        else:
            input_value = second_dict['否']
    else:
        second_dict = Tree[first_feature]
        input_first = test_data.get(first_feature)
        input_value = second_dict[input_first]
    if isinstance(input_value , dict): #判断分支还是不是字典
        class_label = predict(input_value, test_data)
    else:
        class_label = input_value
    return class_label

if __name__ == '__main__':
    data = pd.read_csv('西瓜数据集3.0.csv')
    # 统计每个特征的取值情况作为全局变量
    column_count = dict([(ds, list(pd.unique(data[ds]))) for ds in data.iloc[:, :-1].columns])

    test = cal_information_gain_continuous(data, '密度')
    continuous_features = ['密度', '含糖率']  #先标注连续值

    #构建决策树
    decision_tree = create_tree(data)
    print('决策树模型:', decision_tree)

    # 输出决策树分类结果
    test_data =  {'色泽':'青绿','根蒂':'蜷缩','敲声':'浊响','纹理':'清晰','脐部':'凹陷','触感':'硬滑','密度':0.51,'含糖率':0.3}
    result = predict(decision_tree, test_data)
    print('分类预测结果:{}'.format('好瓜' if result == 1 else '坏瓜'))


