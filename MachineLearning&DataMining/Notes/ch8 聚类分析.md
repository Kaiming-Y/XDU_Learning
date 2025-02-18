# ch8 聚类分析



# A. 无监督学习



## 无监督学习的定义

**无监督学习**—— 根据没有标记的样本，学习数据中的信息



## 监督学习 *vs* 无监督学习

- **监督学习（Supervised Learning）**：
  - 利用**带有标签**的数据集进行训练，学习输入到输出的**映射关系**。
  - 目标是对新数据进行**预测**或**分类**。
  - 主要任务：
    - 分类（Classification）：如邮件分类为垃圾邮件或正常邮件。
    - 回归（Regression）：如预测房价。
  - 优缺点：
    - **优点**：预测性能较好，能够处理复杂的任务。
    - **缺点**：需要大量标注数据，数据标注成本高。
- **无监督学习（Unsupervised Learning）**：
  - 利用**不带标签**的数据集进行训练，发现数据的**内在结构**或**模式**。**数据驱动**。
  - 目标是数据的**分组**或**特征提取**。
  - 主要任务：
    - 聚类（Clustering）：如客户分群。
    - 降维（Dimensionality Reduction）：如主成分分析（PCA）。
    - 异常检测（Anomaly Detection)：检测不正常的数据点。
  - 优缺点：
    - **优点**：无需标注数据，适用于探索性数据分析。
    - **缺点**：结果的解释性较弱，难以验证模型效果。





# B. 聚类的基础知识



## 什么是“类”

直观上：

- 一个类是一组个体（对象、点等），这些个体离这个类的中心个体比较“近”（在合适的度量下）；
- 不同类的成员之间的距离“比较远”。

<u>**“类”可能仅仅是一个聚类方法的结果。**</u>



## 聚类与分类

- 分类
  - 有**类别标记**信息, 因此是一种**监督学习**
  - 根据训练样本获得**分类器**，然后把每个数据归结到某个<u>已知的类</u>，进而也可以<u>预测</u>未来数据的归类。
- 聚类
  - **无类别标记**，因此是一种**无监督学习**
  - 无类别标记样本，根据**信息相似度**原则进行聚类
  - 通过聚类，人们能够识别密集的和稀疏的区域，因而发现<u>全局的分布模式</u>，以及<u>数据属性之间的关系</u>



## 聚类分析的定义

- **聚类分析**：把数据对象<u>划分成子集</u>的过程。 每个子集为一个 **簇（cluster）**。

- 求对象组（簇）：
  - <u>同一簇</u>的样本尽可能彼此<u>相似</u>
  - <u>不同簇</u>的样本尽可能<u>不同</u>



## 簇 Cluster

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601171229.png" style="zoom:50%;" />

- 期望聚类后不同**簇间**的样本距离要**越远越好**，同一**簇内**的样本距离**越近越好**

- 聚类为**无监督的**，没有严格意义的聚类对与错，希望聚类后同一类样本尽量接近



## 相异性与相似性度量

聚类就是发现数据中具有 **“相似性”(similarity)** 的个体

### 相似性

选择合适的“相似性”度量是进行聚类的关键，相似性度量函数 $s(\cdot,\cdot)$ 一般满足：

1. $0 \leq s(x,y) \leq 1$
2. $s(x,x) = 1$
3. $s(x,y) = s(y,x)$

### 相异性

相异性度量多为某种“距离”度量。 样本点之间的相异性(距离)函数 $d(\cdot,\cdot)$ 一般满足：

1. $d(x,y) \geq 0$，等号成立当且仅当 $x = y$
2. $d(x,x) = 0$
3. $d(x,y) = d(y,x)$
4. $d(x,y) \leq d(x,z) + d(z,y)$

相似度的度量并无统一的标准，实际中常用**欧式距离**。





# C. 聚类方法



## I. K-means 聚类

### K-means 聚类质量评价的目标函数

**误差平方和（Sum of the squared error, SSE）**
$$
\text{SSE} = \sum_{i=1}^{K} \sum_{x \in C_{i}} \| x - c_{i} \|_{2}^{2}, \quad c_{i} = \frac{1}{n_{i}} \sum_{x \in C_{i}} x
$$
其中 $K$ 是簇的总个数。$C_{i}$ 表示第 $i$ 个簇，$c_{i}$ 表示第 $i$ 个簇的质心（均值），$x$ 表示第 $i$ 个簇的任一样本，第 $i$ 个簇 $C_{i}$ 的样本数为 $n_{i}$。

* 误差平方和SSE通过计算每个样本和它到其类均值的距离平方，最后求和得到最后的数值。
* 样本集给定情况下，SSE的值取决于 $K$ 个聚合中心。
* SSE 刻画了簇内样本围绕簇均值的紧密程度，其值越小，则簇内样本相似度越高。
* 适用于各类样本比较密集（球状分布）且样本数目悬殊不大的样本分布。

### K-means 算法的流程

1. 输入训练数据和聚类数目$K$;
2. 执行下面二者之一：
   * 随机将数据分为$K$个类$C_{1}, \ldots, C_{K}$，计算每个类的中心$c_{i}$，$i = 1, \ldots, K$;
   * 指定$K$个类的中心$c_{i}$，$i = 1, \ldots, K$，将所有数据点划分到离其最近的类中心所在的类;
3. 计算每个数据点到其所属类的中心的平方距离

$$
  \text{SSE} = \sum_{i=1}^{K} \sum_{x \in C_{i}} \| x - c_{i} \|_{2}^{2}, \quad c_{i} = \frac{1}{n_{i}} \sum_{x \in C_{i}} x
$$

4. 重新将每个数据点划分到离其最近的类中心所在的类，使得SSE减少。完成后重新计算各类的中心$c_{i}$，$i = 1, \ldots, K$;
5. 重复3和4，直到没有样本点需要调整（即SSE不能再减少）;

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601173937.png" style="zoom:50%;" />

### 总结

- 优点
  - 简单，适用于常规不相交的簇。
  - 收敛相对较快。
  - 相对有效和可扩展。时间复杂度 $O(I \times K \times n \times m)$。
    - $I$: 收敛所需迭代次数；$K$: 中心数；$n$: 数据点数；$m$: 类别数
  - 假设数据是呈球形分布。实际任务中很少有这种情况。


- 缺点

  - 需要提前指定 $K$ 的值。
    - 很难确定，领域知识可能会有所帮助。
  - 可能会收敛到局部最优点。
    - 在实践中，需要尝试不同的初始中心点。
  - 可能对噪声数据和异常值敏感。
    - 因为簇的中心是取 **平均**，因此聚类簇很远的地方的噪声会导致簇的中心点偏移。

  - 不适合非凸和不规则形状的簇，普遍对球形分布样本聚类较好。



## II. 层次聚类

产生层次聚类的两种基本方法：

- **凝聚的（自下而上）**。从点作为个体簇开始, 每一步合并**两个最接近**的簇。这需要定义簇的邻近性概念。
- **分裂的（自上而下）**。从包含所有点的某个簇开始，每一步分裂一个簇，直到仅剩下单点簇。在这种情况下, 需要确定每一步分裂哪个簇，以及如何分裂。

 一般而言，凝聚式聚类更为常见

层次聚类的图显示有两种表示方式：

- 树状图 (dendrogram)
- 嵌套簇图 (nested cluster diagram)

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601201140.png" style="zoom:60%;" /><img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601201205.png" style="zoom:60%;" />

### 凝聚方法

自下而上的方法: 从个体点作为簇开始, 相继合并两个最接近的簇, 直到只剩下一个簇

- 将每个数据点看作一个簇；
- 计算邻近度矩阵；
- 合并最近的一对簇；
- 重复直到只剩下一个簇；

### 邻近性度量

簇之间的邻近性通常用特定的簇类型定义，主要有三种定义方式:

- **单链 (single link或MIN)**。MIN定义簇的邻近度为**不同簇的两个最近的点之间的邻近度**，或者说不同的结点子集中两个节点之间的最短边。
- **全链 (complete link或MAX)**。MAX取**不同簇中两个最远点之间的邻近度**作为簇的邻近度, 或者说不同结点子集中两个结点之间的最长边。
- **组平均 (group average)**。定义簇邻近度为取自**不同簇的所有点对邻近度的平均值**(平均边长)。

如果两个点之间的邻近度度量是**距离(相异度)**，则MIN和MAX两个名字有提示作用，即**值越小表示点越接近(单链“小中取小”，全链“大中取小”)**。

如果两个点之间的邻近度度量是**相似度**，则**值越大表示点越接近(单链“大中取大”，全链“小中取大”) 。**

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601204237.png" style="zoom: 25%;" />

### 单链和全链层次聚类步骤

#### 基于距离（相异度）的层次聚类

- **单链**层次聚类步骤（小中取小）

  1. 计算不同簇的两个最近的点之间的距离，再找出距离最小的两个簇，第一个合并；

  2. 按照**“小中取小”**的原则依次合并剩余点，直至合并完所有点。

- **全链**层次聚类步骤（大中取小）
  1. 计算不同簇的两个最远的点之间的距离，再找出距离最小的两个簇，第一个合并；
  2. 按照**“大中取小”**的原则依次合并剩余的点，直至所有点合并完成。

#### 基于相似度矩阵的层次聚类

- **单链**层次聚类步骤（大中取大）
  1. 找出所有点**相似度最大**的两个点，第一个合并；
  2. 按照**“大中取大”**的原则进行合并剩余的点，直至所有点合并完成为止。
- **全链**层次聚类步骤（小中取大）
  1. 找出所有点**相似度最大**的两个点，第一个合并；
  2. 按照**“小中取大”**的原则进行合并剩余的点，直至所有点合并完成为止。

### 层次聚类例子

#### 单链层次聚类

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601210252.png" style="zoom:50%;" />

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601210307.png" style="zoom:50%;" />

#### 全链层次聚类

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601210351.png" style="zoom:50%;" />



## III. DBSCAN 聚类

### 基于密度的方法（Density Based Methods, DBS）

#### 1 定义

**基于密度的方法**：根据密度完成样本数据的聚类，一般假定**类别**可以通过**样本分布的紧密程度**确定。

- 基本假设：只有达到一定密度，才足以成为一个簇
- 密度：指定样本一定半径的样本数量
- 密度聚类算法从样本密度的角度来考察样本之间的可连接性，并基于可连接样本不断扩展聚类簇以获得最终的聚类结果。
- 典型的基于密度方法 - **DBSCAN（Density-based Spatial Clustering of Application with Noise）**：该算法通过不断生长足够高密度区域来进行聚类；它能从含有噪声的空间数据库中发现任意形状的聚类。此方法将一个聚类定义为一组“密度连接”的点集。

#### 2 基于密度的方法的样本点分类

- **核心点** (Core point, 稠密区域内部的点)：核心点的定义为：如果该点的给定邻域内的点的个数超过给定的阈值MinPts (MinPts由用户指定)，则这些点为核心点。
- **边界点** (Border point, 稠密区域边缘上的点)：边界点不是核心点，但它落在某个核心点的邻域内。边界点可能落在多个核心点的邻域内。
- **噪声点**或**背景点** (Noise point, 稀疏区域中的点)：噪声点是即非核心点也非边界点的任何点。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601211501.png" style="zoom:50%;" />

#### 3 重要参数与相关定义

DBSCAN算法中有两个重要参数：

- **邻域半径 Eps**：定义密度时的邻域半径。
- **阈值 MinPts**：定义核心点时的阈值。

DBSCAN中的几个定义：

- **Eps邻域**: 给定样本点 $p$，其半径为 Eps 内的区域称为该样本的 Eps 邻域。
- **核心点**: 如果给定点 Eps 邻域内的样本数大于等于 MinPts，则该点为核心点。
- **直接密度可达**: 对于样本集合 $D$，如果样本点 $q$ 在 $p$ 的 Eps 邻域内，并且 $p$ 为核心点，那么 $q$ 从 $p$ 直接密度可达（又称密度直接达）。
- **密度可达**: 对于样本集合 $D$，给定一串样本点 $p_1, p_2, \ldots, p_n$，$p=p_1, q=p_n$，假定样本 $p_i$ 从 $p_{i-1}$ 直接密度可达，那么点 $q$ 从点 $p$ 密度可达。
- **密度相连**: 对于样本集合 $D$ 中的任意一点 $o$，如果存在点 $p$ 到点 $o$ 密度可达，并且点 $q$ 到点 $o$ 密度可达，那么点 $q$ 到点 $p$ 密度相连。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240601212430.png" style="zoom:50%;" />

### DBSCAN 算法

> [DBSCAN 聚类可视化](https://www.naftaliharris.com/blog/visualizing-dbscan-clustering/)

#### DBSCAN 聚类算法流程

**输入**: 样本集合 $D$，聚类半径 $Eps$，密度阈值 $MinPts$

**输出**: 目标类簇集

**方法**:

1. 随机选取<u>未被处理</u>的点 $p$，判断输入点是否为**核心点**。
2. 找出核心点的 $Eps$ 领域中的**所有密度可达点**，形成一个新的簇。
    - 遍历数据集 $D$，直到所有输入点都判断完毕；
3. 针对该核心点的 $Eps$ 领域内所有密度可达点找到最大密度相连的样本点集合，产生最终的簇结果。
4. 重复执行第 2 步和第 3 步，直到数据集 $D$ 中所有点都为“已处理”状态。

### DBSCAN 算法总结

- DBSCAN将“簇”被定义为由密度可达关系导出的**最大密度相连的样本集合** (从核心点出发) ，即为我们最终聚类的一个类别，或者说一个簇；
- 如果P是核心点，则通过逐渐将密度可达的所有点添加到当前点集来构建簇；
- **噪声点被丢弃**（稀疏的暗色点，未被标记）;
- 产生任意形状的簇;
- 对噪声鲁棒;
- 不需要事先指定类别 K 值， 可根据形状自动确定。

### DBSCAN 的优缺点

#### 优点

- **能发现任意形状的簇**。可对任意形状的稠密数据集进行聚类，相对地，K-means之类的聚类算法一般只适用于凸数据集。

- **对噪点不敏感**。可以在聚类的同时发现异常点，对数据集中的异常点不敏感。

#### 缺点

- **对两个参数的设置敏感**，即邻域半径 eps 、阈值 MinPts。调参相对于传统的K-means之类的聚类算法稍复杂，主要需要对邻域半径Eps，邻域样本数阈值MinPts联合调参，不同的参数组合对最后的聚类效果有较大影响。
- **DBSCAN 使用固定的参数识别聚类**。如果样本集的密度不均匀、聚类间距差相差很大时，聚类质量较差，这时用DBSCAN聚类一般不适合。
- **如果数据样本集越大，则收敛时间越长**。