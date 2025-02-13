# ch3 线性模型





# A. 线性回归

## 1 回归

- 给定一组数据点 $(x_1, y_1), \ldots, (x_n, y_n)$，根据这些数据点研究 $x$ 和 $y$ 之间关系的分析方法就是**回归**。

- **线性回归 (Linear Regression)** 是利用数理统计中回归分析，来确定<u>两种或两种以</u>上变量间相互依赖的定量关系的一种统计分析方法。

- 如果以一个线性函数 $f(\mathbf{x}) = \mathbf{w}^T \mathbf{x} + b$ 来描述两者之间的关系，则称为**线性回归**。如果以一个逻辑函数来描述两者之间的关系，则称为**逻辑回归**。



## 2 线性模型

- 线性模型一般形式

$$
f(\mathbf{x}) = w_1 x_1 + w_2 x_2 + \cdots + w_d x_d + b
$$

$\mathbf{x} = [x_1, x_2, \ldots, x_d]^T$ 是由属性性描述的样本，其中 $x_i$ 是 $\mathbf{x}$ 在第 $i$ 个属性上的取值（即属性值）

- 向量形式

$$
f(\mathbf{x}) = \mathbf{w}^T \mathbf{x} + b
$$

其中 $\mathbf{w} = (w_1; w_2; \ldots; w_d) = [w_1, w_2, \ldots, w_d]^T$

- 线性模型的优点
  - 形式简单、易于建模
  - 可解释性(权重系数$\mathbf{w}$直观地表达了各属性在预测中的重要性)
  - 非线性模型的基础



## 3 一元线性回归

给定数据集 $D = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\}$，其中 $x_i = (x_{i1}; x_{i2}; \ldots; x_{id})$，$y_i \in \mathbb{R}$

线性回归（linear regression）**目的**：学得一个线性模型以尽可能准确地预测实值输出标记

- 离散属性处理
  - 有“序”关系：连续化为连续值
  - 无“序”关系：有k个属性值，则转换为k维向量



## 4 模型/参数估计：最小二乘法

我们使用**代价函数 (cost function)**  $L(y, f(x))$ 来<u>度量误差</u>。

回归任务中，**代价(损失)函数(cost/loss function)** 普遍使用 **<u>均方误差</u>**。基于均方误差最小化进行模型求解的方法称为 **“最小二乘法”** 。

均方误差：
$$
E(w, b) = \sum_{i=1}^{m} (y_i - wx_i - b)^2
$$

最小化均方误差：
$$
\arg \min_{(w,b)}E(w,b) = \arg \min_{(w,b)} \sum_{i=1}^{m} (y_i - wx_i - b)^2
$$
分别对 $w$ 和 $b$ 求偏导，可得
$$
\frac{\partial E(w, b)}{\partial w} = 2 \left( w \sum_{i=1}^{m} x_i^2 - \sum_{i=1}^{m} (y_i - b) x_i \right)
$$

$$
\frac{\partial E(w, b)}{\partial b} = 2 \left( mb - \sum_{i=1}^{m} (y_i - wx_i) \right)
$$

得到封闭形式的解
$$
w = \dfrac{\sum_{i=1}^{m} y_i (x_i - \overline{x})}{\sum_{i=1}^{m} x_i^2 - \frac{1}{m} \left( \sum_{i=1}^{m} x_i \right)^2}
$$

$$
b = \dfrac{1}{m} \sum_{i=1}^{m} (y_i - wx_i)
$$

其中均值

$$
\overline{x} = \frac{1}{m} \sum_{i=1}^{m} x_i
$$



## 5 多元线性回归

给定数据集 (多个属性)：

$$
D = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\}
$$

$$
\begin{aligned}
x_i & = (x_{i1}, x_{i2}, \ldots, x_{id}) \\
    & = (x_{i1}, x_{i2}, \cdots, x_{id})^T \\
    & = [x_{i1}, x_{i2}, \cdots, x_{id}]^T
\end{aligned}
$$


$$
y_i \in \mathbb{R} \quad i = 1, 2, \ldots, m
$$

*(d 为属性维数)*

把 $$ w $$ 和 $$ b $$ 吸收为向量形式 $\hat{w} = (w; b) = [w, b]^T $ 数据集 $D$ 表示为： 

$$
\mathbf{X} = \begin{pmatrix}
    x_{11} & x_{12} & \cdots & x_{1d} & 1 \\
    x_{21} & x_{22} & \cdots & x_{2d} & 1 \\
    \vdots & \vdots & \ddots & \vdots & \vdots \\
    x_{m1} & x_{m2} & \cdots & x_{md} & 1
\end{pmatrix}
= \begin{pmatrix}
    \mathbf{x}_1^T & 1 \\
    \mathbf{x}_2^T & 1 \\
    \vdots & \vdots \\
    \mathbf{x}_m^T & 1
\end{pmatrix}
= \begin{bmatrix}
    \hat{\mathbf{x}}_1^T \\
    \hat{\mathbf{x}}_2^T \\
    \vdots \\
    \hat{\mathbf{x}}_m^T
\end{bmatrix} \in \mathbb{R}^{m \times (d+1)}
$$

其中：

$$
\hat{\mathbf{x}}_i = \begin{bmatrix}
    x_{i1}, x_{i2}, \cdots, x_{id}, 1
\end{bmatrix}^T
$$
$$
\mathbf{y} = (y_1; y_2; \ldots; y_m)
$$

多元线性回归**目标**：$f(x_i) = \mathbf{w}^T x_i + b$ 使得预测结果 $f(x_i)$ **逼近**标记 $y_i$，即 $f(x_i) \simeq y_i$。其中 $\mathbf{w} \in \mathbb{R}^d$。

### 多元线性回归的最小二乘模型

最小二乘模型
$$
(w^*, b^*) = \arg \min_{w, b} \sum_{i=1}^m (f(x_i) - y_i)^2 = \arg \min_{w, b} \sum_{i=1}^m [(w^T x_i + b) - y_i]^2
$$

$$
\begin{aligned}
\Rightarrow \hat{w}^* & = \arg \min_{\hat{w}} \sum_{i=1}^m (\hat{w}^T \hat{x}_i - y_i)^2 \\
 & = \arg \min_{\hat{w}} \sum_{i=1}^m (\hat{x}_i^T \hat{w} - y_i)^2 \\
 & = \arg \min_{\hat{w}} (X \hat{w} - y)^T (X \hat{w} - y) \\
 \end{aligned}
$$

最小二乘法
$$
\hat{w}^* = \arg \min_{\hat{w}} (X \hat{w} - y)^T (X \hat{w} - y)
$$

$$
= \arg \min_{\hat{w}} \|X \hat{w} - y\|_2^2 \quad (2 范数的平方)
$$

$$
= \arg \min_{\hat{w}} \hat{w}^T X^T X \hat{w} - 2 \hat{w}^T X^T y + y^T y
$$

令 $E_{\hat{w}} = (X \hat{w} - y)^T (X \hat{w} - y)$，对 $\hat{w}$ 求偏导得到：
$$
\frac{\partial E_{\hat{w}}}{\partial \hat{w}} = 2X^T (X \hat{w} - y)
$$
令上式为0可得 $\hat{w}$ 最优解的闭式解。



## 6 对数线性回归

- 有时线性回归模型 $y = w^T x + b$ 可能并不能满足需求。*例如：样本对应标记 $y$ 值并不是线性变化，而是在指数尺度上变化*
- 让模型预测值逼近 $y$ 的衍生物：让线性模型 $w^T x + b$ 去逼近 $\ln y$
- 若令 $\ln y = w^T x + b$，则得<u>对数线性回归</u>
- 实际是在用 $e^{w^T x + b}$ 逼近 $y$

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240528165924.png" style="zoom:50%;" />



## 7 广义线性模型

- 一般形式：$y = g^{-1} (w^T x + b)$
  
  $g(\cdot)$ 称为 **联系函数（link function）**，$g^{-1}$ 称为 $g$ 的反函数，$g$ 单调可微函数（$g(\cdot)$ 连续且充分光滑）
  
- 对数线性回归是 $g(\cdot) = \ln (\cdot)$ 时广义线性模型的特例，即令 $g(\cdot) = \ln (\cdot)$，则得对数线性回归 $\ln y = w^T x + b$





# B. 二分类任务

寻找联系函数将线性回归模型输出与分类标记信息联系起来：单位阶跃函数
$$
y =
\begin{cases}
0, & z < 0; \\
0.5, & z = 0; \\
1, & z > 0,
\end{cases}
$$

预测值大于零就判为正例，小于零就判为反例，预测值为临界值零则可任意判别。

单位阶跃函数的缺点：不连续（x=0时导数不存在）



## I. 对数几率回归

### 1 对数几率函数

对数几率函数，简称“对率函数”，也称 **sigmoid函数**。单调可微、任意阶可导。
$$
y = \frac{1}{1 + e^{-z}}
$$
将 $z$ 转化为一个接近 0 或 1 的 $y$ 值。对数几率函数定义域 $(-∞, +∞)$, 值域 $(0, 1)$。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240528215629.png" style="zoom: 33%;" />

- **几率(odds)定义**：几率是指该事件发生的概率与该事件不发生的概率的比值。如果事件发生概率是 $p$，那么该事件的几率为 $\dfrac{p}{1-p}$。
  - 当几率大于 $1$ 时，说明该事件发生的概率大；

  - 几率小于 $1$ 时，说明该事件发生的概率小；

  - 几率变化范围为 $(0, +\infty)$。

- 几率的概念推广叫 **对数几率(log odds)** 或 **logit函数**： $\log \frac{p}{1-p}$
  - 当对数几率大于 $0$ 时，说明该事件发生的概率大；
  - 对数几率小于 $0$ 时，说明该事件发生的概率小。


### 2 对数几率回归

#### 对数几率的定义与公式

把对数几率函数作为联系函数 $g^{-1}(\cdot)$
$$
y = \frac{1}{1+e^{-z}} \quad \text{其中} \quad z = w^Tx + b
$$

$$
y = \frac{1}{1+e^{-(w^Tx+b)}}
$$

**对数几率 (log odds)**：样本作为正例的相对可能性的对数。

- 将 $y$ 视为样本 $x$ 作为正例的可能性

- $1-y$ 是看作样本为反例的概率

$$
\ln \left( \frac{y}{1-y} \right) = w^Tx + b
$$

上式实际上是用**线性回归模型的预测结果**来逼近真实标记的**对数几率**，因此这个模型被称为**对数几率回归**。

#### 对数几率回归优点

- 无需事先假设数据分布
- 可得到“类别”的近似概率预测
- 可直接应用现有数值优化算法求取最优解

#### 对数几率回归的概率解释

把样本 $x$ 的类别 $y$ 看作有 $0$ 和 $1$ 两种取值的随机变量。
$$
\ln \frac{y}{1-y} = w^T x + b \quad \text{可写为} \quad \ln \frac{p(y=1 \mid x)}{p(y=0 \mid x)} = w^T x + b
$$

则由 $p(y=1 \mid x) + p(y=0 \mid x) = 1$ 可得

$$
p(y=1 \mid x) = \frac{e^{w^T x + b}}{1+e^{w^T x + b}} \quad \text{记为} \quad h_\beta(x)
$$

$$
p(y=0 \mid x) = \frac{1}{1+e^{w^T x + b}} \quad \text{记为} \quad 1 - h_\beta(x)
$$

其中 $\beta = (w; b) = [w, b]^T$

### 3 对数几率回归模型 - 最大似然法

最大似然估计中采样需满足一个很重要的**假设**: 所有的采样都是**独立同分布**的。

**最大似然估计思想**: 找到一组参数使得所有观测样本的联合概率最大化

#### 似然函数

$x_1, x_2, \cdots, x_m$ 为独立同分布的采样，定义 **似然函数 L** 为混合密度函数（m个样本同时出现）：
$$
L(\beta) = p(y_1 \mid x_1; \beta) \times p(y_2 \mid x_2; \beta) \times \cdots \times p(y_m \mid x_m; \beta)
$$

$$
= \prod_{i=1}^m p(y_i \mid x_i; \beta) = \prod_{i=1}^m \left( h_\beta(x_i) \right)^{y_i} \left( 1 - h_\beta(x_i) \right)^{1 - y_i}
$$

#### 对数似然函数

$$
\ln L(\beta) = \sum_{i=1}^m \left[ y_i \ln h_\beta(x_i) + (1 - y_i) \ln (1 - h_\beta(x_i)) \right]
$$

#### 最大似然法

- 给定数据集 $\{(x_i, y_i)\}_{i=1}^m$，最大化样本属于其真实标记的概率

- **<u>最大化对数似然函数</u>**
  $$
  \ell(w, b) = \ln L(\beta) = \sum_{i=1}^m \ln p(y_i|x_i; w, b)
  $$
  概率中分号表示分号后的 $w, b$ 是待估参数，它们是确定的，只是当前未知。它们<u>不是随机变量</u>。

- 对率回归模型最大化“对数似然” 等价于 **最小化负对数似然**
  $$
  \max_{\beta} \ln L(\beta) \iff \min_{\beta} - \ln L(\beta) \quad
  $$

- 转化为最小化负对数似然函数求解

  令 $\beta = (w; b), \hat{x} = (x; 1)$，则 $w^T x + b$ 可简写为 $\beta^T \hat{x}$
  
  $$
  \begin{align*}
  \ell(\beta) &= -\ln L(\beta) \\
  &= -\sum_{i=1}^{m} \left[ y_i \ln h_{\beta}(x_i) + (1 - y_i) \ln (1 - h_{\beta}(x_i)) \right] \\
  &= \sum_{i=1}^{m} \left[ -y_i \beta^T \hat{x}_i + \ln \left( 1 + e^{\beta^T \hat{x}_i} \right) \right] \quad
  \end{align*}
  $$

### 4 对数几率回归模型求解

#### 牛顿法

- 求解
$$
\beta^* = \arg \min_{\beta} \ell(\beta)
$$

- 牛顿法第 $t+1$ 轮迭代解的更新公式
$$
\beta^{t+1} = \beta^t - \left( \frac{\partial^2 \ell(\beta)}{\partial \beta \partial \beta^T} \right)^{-1} \frac{\partial \ell(\beta)}{\partial \beta}
$$

其中关于 $\beta$ 的一阶、二阶导数分别为
$$
\frac{\partial \ell(\beta)}{\partial \beta} = -\sum_{i=1}^{m} \hat{x}_i (y_i - p_1 (\hat{x}_i; \beta)) \quad
$$
$$
\frac{\partial^2 \ell(\beta)}{\partial \beta \partial \beta^T} = \sum_{i=1}^{m} \hat{x}_i \hat{x}_i^T p_1 (\hat{x}_i; \beta) (1 - p_1 (\hat{x}_i; \beta)) \quad
$$

#### 梯度下降法

- 关于参数 $\beta$ 的更新公式
$$
\beta^{t+1} = \beta^t - \alpha \frac{\partial \ell(\beta)}{\partial \beta}
$$

其中 $\alpha$ 是学习率。关于 $\beta$ 的一阶偏导数为
$$
\frac{\partial \ell(\beta)}{\partial \beta} = -\sum_{i=1}^{m} \hat{x}_i (y_i - p_1 (\hat{x}_i; \beta))
$$

高等数学基本结论：多元函数的值沿其<u>梯度</u>的**负方向**下降最快

<u>梯度</u>: 损失函数的等高线的法线方向

**梯度下降法在二维空间示意图**

- 初始点：可以人为的设定，也可以随机设定。初始点选取影响全局收敛性。需要考虑全局收敛性，最好是多设几个初始值迭代。
- 初始点离最优点越近，收敛越快。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240529163143.png" style="zoom: 50%;" />



## II. 线性判别分析

### 线性判别分析的思想

线性判别分析 (Linear Discriminant Analysis, LDA) 的**基本思想**：给定训练样例集，设法将样例投影到一条**适当选择**的直线上，使得同类样例的投影点尽可能接近、异类样例的投影点中心尽可能远离。

*“投影后类内方差小，类间距离大”*

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240529171320.png" style="zoom:50%;" />

我们将这个最佳的投影向量称为 $w$，那么样例 $x$ 到方向向量 $w$ 上的投影可以用下式来计算：
$$
y = w^T x
$$

### LDA的目标函数

<u>LDA的**目标**：在保留尽可能多的类区分信息的同时进行降维。</u>

我们有一组 $m$ 个 $d$ 维的样本 $x_1, \cdots, x_m$，它们分属于示例集合 $X_i$ 中两个不同的类别 $\omega_0$ 和 $\omega_1$，即$X_0 = \{ x_i | \omega(x_i) = \omega_0 \}, X_1 = \{ x_i | \omega(x_i) = \omega_1 \}$，且 $|X_0| = n_0, |X_1| = n_1$。

对 $x$ 中的各个成分作线性组合，得到 $y = w^T x$，这样 $n$ 个样本 $x_1, \cdots, x_m$ 就产生了 $n$ 个投影结果 $y_1, \cdots, y_n$，相应的属于集合 $Y_0$ 和 $Y_1$，即 $Y_i = w^T X_i (i = 0,1)$。

#### a. 样本均值

##### 投影前-样本均值

$$
\mu_i = \frac{1}{n_i} \sum_{x \in X_i} x, \quad i = 0,1,
$$

##### 投影后-样本均值

$$
\tilde{\mu}_i = w^T \mu_i
$$

#### b. 投影前-散度矩阵

##### 类间散度矩阵

$$
S_b = (\mu_0 - \mu_1)(\mu_0 - \mu_1)^T
$$

可证明其为对称半正定的。

##### 类内散度矩阵

$$
\Sigma_0 = \sum_{x \in X_0} (x - \mu_0)(x - \mu_0)^T, \quad \Sigma_1 = \sum_{x \in X_1} (x - \mu_1)(x - \mu_1)^T
$$

##### 总类内散度矩阵

$$
S_w = \Sigma_0 + \Sigma_1
$$

可证明其是对称半正定的。

#### c. 投影后-样本均值之差

$$
| \tilde{\mu}_0 - \tilde{\mu}_1 | = | w^T (\mu_0 - \mu_1) |.
$$

有
$$
|\tilde{\mu_0} - \tilde{\mu_1}|^2 = w^T (\mu_0 - \mu_1)(\mu_0 - \mu_1)^T w = w^T S_b w
$$

#### d. 投影后-散度

##### 投影后-类内散度

$$
\tilde{s}_i^2 = \sum_{y \in Y_i} (y - \tilde{\mu}_i)^2 = w^T \Sigma_i w
$$

##### 投影后-总类内散度

$$
\tilde{s_0}^2 + \tilde{s_1}^2 = w^T S_w w
$$

#### e. 准则函数

$$
J(w) = \frac{|\tilde{\mu_0} - \tilde{\mu_1}|^2}{\tilde{s_0}^2 + \tilde{s_1}^2} = \frac{w^T S_b w}{w^T S_w w}
$$

Fisher 线性可分性准则要求在投影 $y = w^T x$ 下，**最大化**准则函数 $J(w)$（目标函数）

#### f. 拉格朗日优化和特征向量求解

通过将LDA问题表达为一个优化问题，我们引入拉格朗日乘数 $\lambda$ 来解决约束优化问题。

优化的目标是最小化 $-w^T S_b w$，同时满足约束 $w^T S_w w = c$。

运用拉格朗日乘数法得到：
$$
S_b w = \lambda S_w w
$$

#### g. 最优投影向量求解

推导出最优投影向量 $w$ 的表达式为：

$$
w = \lambda'\lambda^{-1} S_w^{-1} (\mu_0 - \mu_1)
$$

投影轴的**最佳方向**：
$$
w^* = S_w^{-1} (\mu_0 - \mu_1)
$$

#### h. J(w) 的计算和决策边界

计算得到的 $J(w)$ 表达为：

$$
J(w) = (\mu_0 - \mu_1)^T S_w^{-1} (\mu_0 - \mu_1)
$$

这个表达式反映了通过最优投影向量 $w$ 使得投影后的类间距**最大化**。分类决策可通过计算新样本 $x$ 投影到 $w$ 上的值来进行：

$$
y = (\mu_0 - \mu_1)^T S_w^{-1} x
$$

这里的 $y$ 表示样本 $x$ 在最优化投影方向上的位置，可用于确定 $x$ 的类别。



### LDA 计算题例题

#### 题目

由两类二维数据计算线性判别分析(LDA)投影向量

第一类采样数据 $ \omega_1 $ ： $\mathbf{X_1} = (\mathbf{x_1}, \mathbf{x_2}) = \{(4,2), (2,4), (2,3), (3,6), (4,4)\} \quad$

第二类采样数据 $ \omega_2 $ ： $\mathbf{X_2} = (\mathbf{x_1}, \mathbf{x_2}) = \{(9,10), (6,8), (9,5), (8,7), (10,8)\} \quad$

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240529203718.png" style="zoom:50%;" />

#### 解

1. 计算**均值**
   $$
   \mu_1 = \frac{1}{N_1} \sum_{\mathbf{x} \in \omega_1} \mathbf{x} = \frac{1}{5} \left[ \left( \begin{array}{c} 4 \\ 2 \end{array} \right) + \left( \begin{array}{c} 2 \\ 4 \end{array} \right) + \left( \begin{array}{c} 2 \\ 3 \end{array} \right) + \left( \begin{array}{c} 3 \\ 6 \end{array} \right) + \left( \begin{array}{c} 4 \\ 4 \end{array} \right) \right] = \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right)
   $$

   $$
   \mu_2 = \frac{1}{N_2} \sum_{\mathbf{x} \in \omega_2} \mathbf{x} = \frac{1}{5} \left[ \left( \begin{array}{c} 9 \\ 10 \end{array} \right) + \left( \begin{array}{c} 6 \\ 8 \end{array} \right) + \left( \begin{array}{c} 9 \\ 5 \end{array} \right) + \left( \begin{array}{c} 8 \\ 7 \end{array} \right) + \left( \begin{array}{c} 10 \\ 8 \end{array} \right) \right] = \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right)
   $$

2. 计算**类内散度矩阵**
   $$
   \begin{aligned}
   S_1 &= \sum_{\mathbf{x} \in \omega_1} (\mathbf{x} - \mu_1)(\mathbf{x} - \mu_1)^T \\
   &= \left[ \left( \begin{array}{c} 4 \\ 2 \end{array} \right) - \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 2 \\ 4 \end{array} \right) - \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 2 \\ 3 \end{array} \right) - \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 3 \\ 6 \end{array} \right) - \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 4 \\ 4 \end{array} \right) - \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) \right]^2 \\
   &= \left( \begin{array}{cc} 4 & -1 \\ -1 & 8.8 \end{array} \right)
   \end{aligned}
   $$

   $$
   \begin{aligned}
   S_2 &= \sum_{\mathbf{x} \in \omega_2} (\mathbf{x} - \mu_2)(\mathbf{x} - \mu_2)^T \\
   &= \left[ \left( \begin{array}{c} 9 \\ 10 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 6 \\ 8 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 9 \\ 5 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 8 \\ 7 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^2 + \left[ \left( \begin{array}{c} 10 \\ 8 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^2 \\
   &= \left( \begin{array}{cc} 9.2 & -0.2 \\ -0.2 & 13.2 \end{array} \right)
   \end{aligned}
   $$

3. 计算**总类内散度矩阵**
   $$
   \begin{aligned}
   S_w &= S_1 + S_2 \\
   &= \left( \begin{array}{cc} 4 & -1 \\ -1 & 8.8 \end{array} \right) + \left( \begin{array}{cc} 9.2 & -0.2 \\ -0.2 & 13.2 \end{array} \right) \\
   &= \left( \begin{array}{cc} 13.2 & -1.2 \\ -1.2 & 22 \end{array} \right)
   \end{aligned}
   $$

4. 计算**类间散度矩阵**
   $$
   \begin{aligned}
   S_b &= (\mu_1 - \mu_2)(\mu_1 - \mu_2)^T \\
   &= \left[ \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right] \left[ \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right]^T \\
   &= \left( \begin{array}{c} -5.4 \\ -3.8 \end{array} \right) \left( \begin{array}{c} -5.4 \ -3.8 \end{array} \right) \\
   &= \left( \begin{array}{cc} 29.16 & 20.52 \\ 20.52 & 14.44 \end{array} \right)
   \end{aligned}
   $$

5. 计算 $\mathbf{w^*}$
   $$
   \begin{aligned}
   w^* &= S_w^{-1} (\mu_1 - \mu_2) \\
   &= \left( \begin{array}{cc} 3.3 & -0.3 \\ -0.3 & 5.5 \end{array} \right)^{-1} \left[ \left( \begin{array}{c} 3 \\ 3.8 \end{array} \right) - \left( \begin{array}{c} 8.4 \\ 7.6 \end{array} \right) \right] \\
   &= \left( \begin{array}{cc} 0.3045 & 0.0166 \\ 0.0166 & 0.1827 \end{array} \right) \left( \begin{array}{c} -5.4 \\ -3.8 \end{array} \right) \\
   &= \left( \begin{array}{c} 0.9088 \\ 0.4173 \end{array} \right)
   \end{aligned}
   $$
   

