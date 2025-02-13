# ch6 SVM



# A. 间隔与支持向量



## I. 超平面

> LDA 适用于满足高斯分布（正态分布）的数据集。那么对于不满足高斯分布的数据集（第二组），如何找到最合理的分割**超平面**？

### 平面

- 我们最常见的**平面**概念是在三维空间中定义的：
  $$
  ax + by + cz + d = 0
  $$
  如果记 $\mathbf{w} = [a, b, c]^T$, $\mathbf{x} = [x, y, z]^T$，则 $\mathbf{w}^T \mathbf{x} + d = 0$

- 它有两个性质：
  1. 方程是线性的：是空间点的各分量的线性组合
  2. 方程数目为 1

### 超平面

- 若抛弃维度“3”的限制，就得到了**超平面**的定义。二维空间里的超平面为一条直线。一维空间里超平面为数轴上的一个点。

- $n$维空间中的**超平面**由下面的方程确定
  $$
  \mathbf{w}^T \mathbf{x} + b = 0
  $$

  其中，$\mathbf{w} = [w_1, w_2, ..., w_n]^T$ 和 $\mathbf{x} = [x_1, x_2, ..., x_n]^T$ 都是$n$维列向量，$\mathbf{x}$为平面上的点；$\mathbf{w}$为平面的法向量，决定了超平面的方向；$b$是一个实数，代表超平面到原点的距离。**超平面模型**可写为
  $$
  f(x) = \mathbf{w}^T \mathbf{x} + b
  $$



## II. 支持向量

- 使得边界点距离分类超平面最大，这个方法就是**支持向量机 (SVM)**
- SVM 就是寻找一个最优的决策边界，距离两个类别最近的样本最远，其中最近的样本点称为**支持向量**。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531143024.png" style="zoom:50%;" />



## III. 间隔

- **间隔（margin）**是指从分类超平面到最接近它的训练样本之间的距离。
- 转化成数学问题， 就是使得中间的直线距离两边的直线的间隔（margin） 最大（这两边的直线的斜率是一样的） ， 即SVM算法就是 **最大化间隔 (margin)**。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531143510.png" style="zoom: 50%;" />



## IV. 分类问题

- 给定训练集
  $$
  \mathbf{D} = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\} \subseteq (\mathbb{R}^d \times \mathcal{Y})^m
  $$

  其中 $x_i \in \mathbb{R}^d, y_i \in \mathcal{Y} = \{1, -1\}, i = 1, \ldots, m$。据此寻找 $\mathbb{R}^d$ 空间上的一个实值函数 $g(x)$，以便用**决策函数**
  $$
  f(x) = \text{sgn}(g(x))
  $$
  推断任一输入 $x$ 对应的输出 $f(x)$（正类或负类）。

  $$
  \text{sgn}(a) = 
  \begin{cases} 
  1, & \text{if } a \ge 0, \\
  -1, & \text{if } a < 0.
  \end{cases}
  $$
  
- 由此可见，求解分类问题，实质上是找到一个把 $\mathbb{R}^d$ 空间分成两部分的规则。我们把解决上述分类问题的方法称为**分类机**。

- 当 $g(x)$ 为线性函数 $g(x) = \mathbf{w}^T \mathbf{x} + b$ 时，决策函数对应着用超平面 $\mathbf{w}^T \mathbf{x} + b = 0$ 将 $\mathbb{R}^d$ 空间分成两部分，此时称为**线性划分的分类机**或**线性分类机**。



## V. 最大间隔法的导出与支持向量

假设训练数据集 $ D = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\} $，考虑二分类问题， $ y_i \in \{-1, +1\} $。在样本空间中，划分的超平面可以表示为： 
$$
 \mathbf{w}^T \mathbf{x} + b = 0 
$$
其中 $ \mathbf{w} = [w_1, w_2, \ldots, w_d]^T $ 为超平面的法向量，$ b $ 为位移，决定超平面与原点之间的距离。

### 超平面空间的划分

超平面将 $ n $ 维空间划分为三部分： 

1. 点在超平面上：$ \mathbf{w}^T \mathbf{x} + b = 0 $
2. 点在超平面的“上方”：$ \mathbf{w}^T \mathbf{x} + b > 0 $
3. 点在超平面的“下方”：$ \mathbf{w}^T \mathbf{x} + b < 0 $

### 间隔的定义

样本空间中每个样本点 $ x_i $ 到分类超平面 $ \mathbf{w}^T \mathbf{x} + b = 0 $ 的距离可以写为：

$$
\gamma_i = \frac{|\mathbf{w}^T \mathbf{x}_i + b|}{\|\mathbf{w}\|_2} = \frac{y_i (\mathbf{w}^T \mathbf{x}_i + b)}{\|\mathbf{w}\|_2}
$$

定义 **间隔** $ \gamma $ 为整个数据集 $ D $ 中所有样本到分类超平面的**最短距离**：

$$
\gamma = \min_i \gamma_i
$$

<u>间隔 $ \gamma $ 越大，其分类超平面对两个数据集的划分越稳定。</u>

### SVM目标

SVM 的目标是寻找一个超平面 $ \mathbf{w}^T \mathbf{x} + b = 0 $ 使得 $ \gamma $ 最大：

$$
\max_{\mathbf{w}, b} \gamma \quad \text{s.t.} \quad \dfrac{y_i (\mathbf{w}^T \mathbf{x}_i + b)}{\| \mathbf{w} \|} \geq \gamma, \quad i = 1, 2, \ldots, m
$$

令 $ \|\mathbf{w}\| \cdot \gamma = 1 $ (即 $ \mathbf{w} $ 和 $ b $ 等比例缩放并不改变几何间隔)，则上述等价于：

$$
\max_{\mathbf{w}, b} \frac{1}{\|\mathbf{w}\|} \quad \text{s.t.} \quad y_i (\mathbf{w}^T \mathbf{x}_i + b) \geq 1, \quad i = 1, 2, \ldots, m
$$

其中，令 $\|w\| \cdot \gamma = 1$ （$w$ 和 $b$ 等比例缩放并不改变几何间距）。

数据集中所有满足 $y_i(w^Tx_i+b)=1$ 的样本点，都称为**支持向量**。

### 约束条件

- 对于正类 ($y_i = +1$) 样本，有
  $$
  \mathbf{w}^T \mathbf{x}_i + b \ge 1
  $$

- 对于负类 ($y_i = -1$) 样本，有
  $$
  \mathbf{w}^T \mathbf{x}_i + b \le -1
  $$


综合起来可以将**约束条件**写为
$$
y_i (\mathbf{w}^T \mathbf{x}_i + b) \ge 1
$$
<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531150714.png" style="zoom:50%;" />

### 原始SVM

通过求解上述模型中的 $ \mathbf{w}, b $，就可以获得划分超平面，也是支持向量机的原始形式：

$$
\min_{\mathbf{w}, b} \|\mathbf{w}\|^2_2 \quad \text{s.t.} \quad y_i (\mathbf{w}^T \mathbf{x}_i + b) \geq 1, \quad i = 1, 2, \ldots, m
$$
因为现在的目标函数是二次的，约束条件是线性的，所以它是一个凸二次规划问题 (convex quadratic programming)。可以直接用一些二次规划优化软件计算包来求解（如 CVX），但该问题可以有更为高效的求解方法。



## 6 线性可分问题的最大间隔法

1. 设已知训练集 $\mathbf{D} = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\}$，其中 $x_i \in \mathbb{R}^d$，$y_i \in \mathcal{Y} = \{1, -1\}$，$i = 1, 2, \ldots, m$

2. 构造并求解凸二次规划
$$
\min_{\mathbf{w}, b} \|\mathbf{w}\|^2_2 \quad \text{s.t.} \quad y_i (\mathbf{w}^T \mathbf{x}_i + b) \ge 1, \quad i = 1, 2, \ldots, m
$$
  求得解 $\mathbf{w}^*, b^*$

3. 构造划分超平面 $(\mathbf{w}^*)^T \mathbf{x} + b^* = 0$，由此得到决策函数
$$
  f(x) = \text{sgn}((\mathbf{w}^*)^T \mathbf{x} + b^*)
$$
$$
\text{sgn}(a) = 
  \begin{cases} 
  1, & \text{if } a \ge 0, \\
  -1, & \text{if } a < 0.
  \end{cases}
$$



## 7 求最大间隔分离超平面的例题

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531151315.png" style="zoom: 50%;" />





# B. 对偶问题

对偶问题通常比原问题更容易处理, 因为直接处理原问题中的不等式约束是困难的。



## I. 拉格朗日乘子法

> 通过把拉格朗日函数对于各个原变量的导数置零，并将得到的关系式代入原拉格朗日函数，将原问题转换为对偶问题并去除了原变量的相关性，最终得到的函数只含有对偶变量，并且在最简单的约束条件下最大化。

- 第一步：对每条不等式约束引入拉格朗日乘子 $\alpha_i \ge 0$ 得到拉格朗日函数
  $$
  L(\mathbf{w}, b, \alpha) = \frac{1}{2} \|\mathbf{w}\|^2 - \sum_{i=1}^m \alpha_i (y_i (\mathbf{w}^T \mathbf{x}_i + b) - 1)
  $$
  其中 $\alpha = [\alpha_1, \alpha_2, \ldots, \alpha_m]^T$ 为拉格朗日乘子向量。

- 第二步：固定 $\alpha$，令 $L(\mathbf{w}, b, \alpha)$ 对 $\mathbf{w}$ 和 $b$ 的偏导数为零可得
  $$
  \frac{\partial L(\mathbf{w}, b, \alpha)}{\partial \mathbf{w}} = 0 \Rightarrow \mathbf{w} = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i
  $$
  $$
  \frac{\partial L(\mathbf{w}, b, \alpha)}{\partial b} = 0 \Rightarrow 0 = \sum_{i=1}^m \alpha_i y_i \quad \text{绝大部分（不需要惩罚的样本）} \alpha_i \text{为0}
  $$

- 第三步：回代（将上述第二步中第一式代入第一步的拉格朗日函数中）消去 $\mathbf{w}$ 和 $b$
  $$
  \max_{\alpha} \sum_{i=1}^m \alpha_i - \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \mathbf{x}_i^T \mathbf{x}_j \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
  $$

该问题称为原支撑向量机问题的 **对偶问题 (dual problem)**。在对偶问题中， 训练数据永远不会单独出现， 它们总是以内积 $x_i^Tx_j$ 的形式成对出现。

解出 $\alpha$，求出 $\mathbf{w}$ 和 $b$，即可得**超平面所对应的模型**：
$$
f(x) = \mathbf{w}^T \mathbf{x} + b = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i^T \mathbf{x} + b
$$


## II. 优化：KKT条件

$$
\begin{cases}
\alpha_i \ge 0, \\
y_i f(x_i) - 1 \ge 0, \\
\alpha_i (y_i f(x_i) - 1) = 0.
\end{cases}
$$

- 满足这三个条件的解就是**局部极小值点**。

  1. 如果优化问题是凸优化的话，KKT条件就是极小值点（而且是全局极小）存在的充要条件。
  2. 如果优化问题不是凸优化的话，<u>KKT条件只是在对于有不等式约束和等式约束的最优化问题具有局部最优解的必要条件</u>，不是充分条件。KKT点是驻点，是可能的极值点。也就是说，<u>就算求得的满足KKT条件的点，也不一定是极小值点，只是说极小值点一定满足KKT条件。</u>

- 于是对任意的训练样本 $(x_i, y_i)$，总有 $\alpha_i = 0$ 或者 $y_i f(x_i) = 1$。

  1. 如果 $\alpha_i = 0$，则因为 $\mathbf{w} = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i$，该样本不会在最后求解的超平面模型的式子 $f(x) = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i^T \mathbf{x} + b$ 中出现，所以样本 $(x_i, y_i)$ 对计算分割超平面没有影响。

  2. 如果 $\alpha_i > 0$，则必然 $y_i f(x_i) = 1 \Rightarrow \mathbf{w}^T \mathbf{x}_i + b = 1$ 或者 $-1$，说明样本点出现在最大间隔分割边界上，即训练样本 $x_i$ 的间隔必须为1，该样本对计算分割超平面有影响。这样的数据样本称为**支持向量（support vectors）**。

上面两点说明, 在支撑向量机计算过程中，大部分训练样本都不需要，==<u>最终分类超平面模型仅与**支撑向量**有关</u>==。

<details>
    <summary>例子</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531165819.png" style="zoom:50%;" />
    </p>
</details>

由 $\mathbf{w} = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i$ 我们看到，解向量 $\mathbf{w}$ 由支持点 $\mathbf{x}_i$ 的线性组合定义。



## III. 序贯最小算法 SMO

### 求解方法

- **基本思路**：不断执行如下两个步骤直至收敛。
  
  - 第一步：选取一对需要更新的变量 $\alpha_i$ 和 $\alpha_j$。
  - 第二步：固定 $\alpha_i$ 和 $\alpha_j$ 以外的参数，求解对偶问题更新 $\alpha_i$ 和 $\alpha_j$。
  
- 仅考虑 $\alpha_i$ 和 $\alpha_j$ 时，对偶问题的约束变为
  $$
  \alpha_i y_i + \alpha_j y_j = -\sum_{k \neq i,j} \alpha_k y_k, \quad \alpha_i \ge 0, \quad \alpha_j \ge 0.
  $$
  用一个变量表示另一个变量，回代入对偶问题可得一个单变量的二次规划，该问题具有**闭式解**。
  
- 偏移项 $b$ ：通过支持向量来确定。

### SMO 变量选择策略

- 选择违背 KKT 条件的那些变量先更新。

  由于最终所有计算得到的 $a_i$ 都会满足 KKT 条件, 因此如果存在某个 $a_i$ 不满足 KKT 条件, 那么目标函数会最快衰减。

- 使选取的两变量所对应样本之间的间隔隔最大。

  比较各变量所对应的目标函数值减幅的复杂度过高, 因此 SMO 采用这个启发式。这样的两个变量有很大的差别, 与对两个相似的变量进行更新相比, 对它们进行更新会带给目标函数值更大的变化

步骤：

1. 固定其他变量后优化 $\alpha_i, \alpha_j$，实际上是将约束项 $\sum_{i=1}^m \alpha_i y_i = 0$ 转变成  $\alpha_i y_i + \alpha_j y_j = c$，这里 $c = -\sum_{k \neq i,j} \alpha_k y_k$  而进一步 $\alpha_j = c y_j - \alpha_i y_i$

2. 将 $\alpha_j$ 代入式子
   $$
   \max_{\alpha} \sum_{i=1}^m \alpha_i - \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \mathbf{x}_i^T \mathbf{x}_j \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
   $$
   消去 $\alpha_j$，上式变成关于 $\alpha_i$ 的一个二次规划问题，只有的约束是 $\alpha_i \ge 0$。这样的二次规划存在封闭形式的解，不必调用数值优化算法即可高效地计算更新后的 $\alpha_i$ 和 $\alpha_j$，因此算法效率高。 

最终超平面对应的模型为：
$$
f(x) = \mathbf{w}^T \mathbf{x} + b = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i^T \mathbf{x} + b
$$


## IV. 对偶问题：求解 $\mathbf{w}$ 和 $b$

### $\mathbf{w}$

如果已经求解得到 $\alpha$，那么由 $\mathbf{w} = \sum_{i=1}^m \alpha_i y_i \mathbf{x}_i$，可以计算得到 $\mathbf{w}$

### $b$

由于对任意支持向量有 $y_i (\mathbf{w}^T \mathbf{x}_i + b) = 1$，由此可以得到 $b = 1 / y_i - \mathbf{w}^T \mathbf{x}_i$（因为 $y_i$ 仅取 +1 或 -1）。

将所有支持向量计算得到的 $b$ 的均值记为最优值，即 
$$
b = \frac{1}{|S|} \sum_{i \in S} \left( \frac{1}{y_i} - \mathbf{w}^T \mathbf{x}_i \right)
$$
这里 $S \subseteq D$ 为原数据集中所有支持向量组成的子集。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531180035.png" style="zoom: 60%;" />



## V. 转为最小化问题

对偶问题
$$
\max_{\alpha} \sum_{i=1}^m \alpha_i - \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \mathbf{x}_i^T \mathbf{x}_j \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
$$

是一个**最大化问题**。由于在最优化方法的研究中常用等价的最小化问题取代最大化问题，这里也引进与上述对偶问题有相同解集的**最小化问题**：
$$
\min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \mathbf{x}_i^T \mathbf{x}_j - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
$$

可以证明上述最小化问题是凸二次规划。



## 总结

### 1 为什么要从原始问题转换成对偶问题求解？

1. 对偶问题将原始问题中的不等式约束转为了对偶问题中的等式约束。

2. 改变了问题的复杂度。由求特征向量 $\mathbf{w}$ 转化为求比例系数 $\alpha$，在原始问题下，求解的复杂度与样本的维度有关，即 $\mathbf{w}$ 的维度。在对偶问题下，只与样本数量有关（对应为 $m$）。
   1. SVM 原始问题模型严重依赖于数据集的维度 $d$，如果维度 $d$ 太高就会严重提升计算时间。
   2. 对偶问题实际上把 SVM 从依赖 $d$ 个维度转变到依赖 $m$ 个数据点，考虑到在最后计算时只有支持向量才有意义，所以这个计算量实际上比 $m$ 小很多。

3. 求解更高效，因为只用求解 $\alpha$ 系数，而 $\alpha$ 系数只在支持向量才非零，其它全部为 0。

4. 方便核函数的引入，进而推广到非线性分类问题。

### 2  完整的线性可分支撑向量分类的算法流程

1. 设已知训练集 $\mathbf{D} = \{(x_1, y_1), (x_2, y_2), \ldots, (x_m, y_m)\}$，其中 $x_i \in \mathbb{R}^d$，$y_i \in \mathcal{Y} = \{1, -1\}$，$i = 1, 2, \ldots, m$

2. 构造并利用SMO算法求解凸二次规划
   $$
   \min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \mathbf{x}_i^T \mathbf{x}_j - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
   $$
   求得解 $\alpha^* = [\alpha_1^*, \alpha_2^*, \ldots, \alpha_m^*]^T$

3. 使用所有支持向量计算得到的 $b$ 的均值记为最优值，即
   $$
   b^* = \frac{1}{|S|} \sum_{s \in S} \left( \frac{1}{y_s} - \sum_{i \in S} \alpha_i y_i \mathbf{x}_i^T \mathbf{x}_s \right), \quad S = \{i | \alpha_i > 0, i = 1, 2, \ldots, m\}
   $$

4. 构造划分超平面 $(\mathbf{w}^*)^T \mathbf{x} + b^* = 0$，由此得到决策函数
   $$
   f(x) = \text{sgn}(g(x)) \quad \text{sgn}(a) = 
   \begin{cases} 
   1, & \text{if } a \ge 0, \\
   -1, & \text{if } a < 0.
   \end{cases}
   $$
   其中 $g(x) = (\mathbf{w}^*)^T \mathbf{x} + b^* = \sum_{i=1}^m \alpha_i^* y_i \mathbf{x}_i^T \mathbf{x} + b^*$





# C. 核函数

> 非线性问题中，可以将低维空间的问题转为高维空间中的线性问题。



## I. 核支持向量机

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531202436.png" style="zoom: 50%;" />



## II. 核函数

### 核函数的定义

- 在线性SVM中的对偶形式中，直接计算 $\phi(\mathbf{x}_i)^T \phi(\mathbf{x}_j)$ 非常困难，而且目标函数和分离超平面都只需要计算内积，只关心计算那个高维空间里的内积的值。
  $$
  \min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \phi(\mathbf{x}_i)^T \phi(\mathbf{x}_j) - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
  $$

- 基本想法：不显式地设计核映射 $\phi(\mathbf{x})$，而是设计核函数，可以设想样本之间的内积运算由某个函数定义，即
  $$
  \phi(\mathbf{x}_i)^T \phi(\mathbf{x}_j) = \langle \phi(\mathbf{x}_i), \phi(\mathbf{x}_j) \rangle = k(\mathbf{x}_i, \mathbf{x}_j)
  $$
  其中 $k(\cdot, \cdot)$ 称为**核函数（kernel function）**。$\langle \cdot, \cdot \rangle$ 为内积运算符号。

### 核函数的作用

1. 引入了核函数，把高维向量的内积转变成了求低维向量的内积问题.

2. 核函数是一种表征映射、实现内积逻辑关系且降低计算复杂度的一类特殊函数(满足Mercer’s condition)。这里的内积是一种在高维空间里面度量数据相似度一种手段。

### 支持向量展式

- 有了这样的核函数，我们可以不用去显式的定义非线性映射函数 $\phi$。同时样本 $\mathbf{x}_i, \mathbf{x}_j$ 在高维空间中的内积可以直接由核函数计算得到。于是，下式
  $$
  \min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j \phi(\mathbf{x}_i)^T \phi(\mathbf{x}_j) - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
  $$

  可以转变成
  $$
  \min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j k(\mathbf{x}_i, \mathbf{x}_j) - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
  $$

- 最后计算得到分割超平面 $f(x) = \sum_{i=1}^m \alpha_i y_i k(\mathbf{x}_i, \mathbf{x}) + b$。这里显示出模型最优解可通过训练样本的核函数展开，这一展开式亦称 **“支持向量展开式”（support vector expansion）**。

### 核函数的性质

- 函数 $f(x)$ 可以看做是一个无穷维的向量，具有两个独立变量的函数 $k(x, y)$ 可以看做是一个无穷维矩阵。如果 $k(x, y) = k(y, x)$ 且对任意的函数 $f$ 有
  $$
  \iint f(x) k(x, y) f(y) \, dx \, dy \ge 0
  $$
  那么称函数 $k(x, y)$ 是**对称**的并且**半正定**的，其中 $k(x, y)$ 是一个核函数。

- **Mercer 定理**：任何半正定的函数都可以作为核函数。也就是说只要一个对称函数所对应的核矩阵半正定，它就能作为核函数使用。

- 假设数据集 $\mathbf{D} = \{x_1, x_2, \ldots, x_m\}$，所谓的**核矩阵**即满足下式的矩阵：
  $$
  \mathbf{K} = \begin{bmatrix}
  k(x_1, x_1) & \cdots & k(x_1, x_m) \\
  \vdots & \ddots & \vdots \\
  k(x_m, x_1) & \cdots & k(x_m, x_m)
  \end{bmatrix}
  $$

- 事实上，<u>对于一个半正定核矩阵 $\mathbf{K}$，总能找到一个与之对应的映射 $\phi$</u>。换言之，任何一个核函数都隐式地定义了一个称为**“再生核希尔伯特空间”（Reproducing Kernel Hilbert Space, RKHS）**的特征空间。

- 在不知道特征映射的形式时，我们并不知道什么样的核函数是合适的，而核函数也仅是隐式地定义了这个特征空间。于是，**“核函数选择”成为支持向量机的最大变数**。若核函数选择不合适，则意味着将样本映射到了一个不合适的特征空间，很可能导致 SVM 性能不佳。



## III. 常见的核函数

- 常用核函数：

| 名称       | 表达式                                                       | 参数                                       |
| ---------- | ------------------------------------------------------------ | ------------------------------------------ |
| 线性核     | $\kappa(\mathbf{x}_i, \mathbf{x}_j) = \mathbf{x}_i^T \mathbf{x}_j$ |                                            |
| 多项式核   | $\kappa(\mathbf{x}_i, \mathbf{x}_j) = (\mathbf{x}_i^T \mathbf{x}_j)^d$ | $d \ge 1$ 为多项式的次数                   |
| 高斯核     | $\kappa(\mathbf{x}_i, \mathbf{x}_j) = \exp \left( -\frac{\|\mathbf{x}_i - \mathbf{x}_j\|^2}{2\delta^2} \right)$ | $\delta > 0$ 为高斯核的带宽 (width)        |
| 拉普拉斯核 | $\kappa(\mathbf{x}_i, \mathbf{x}_j) = \exp \left( -\frac{\|\mathbf{x}_i - \mathbf{x}_j\|}{\delta} \right)$ | $\delta > 0$                               |
| Sigmoid 核 | $\kappa(\mathbf{x}_i, \mathbf{x}_j) = \tanh(\beta \mathbf{x}_i^T \mathbf{x}_j + \theta)$ | $\beta > 0, \theta < 0$ 为双曲正切函数参数 |

- 此外通过核函数的线性组合、内积运算也能得到新的核函数。
- 特别的：若 $k$ 为核函数，对于任意函数 $g(x), \tilde{k}(x, z) = g(x) k(x, z) g(z)$ 也是核函数。



## IV. 核技巧

- 两个向量 $\mathbf{x}, \mathbf{y} \in \mathbb{R}^d$，一个非线性核函数 $k(\mathbf{x}, \mathbf{y})$。

- 对于满足某些条件的 $k$，一定存在一个映射 $\phi: \mathbb{R}^d \rightarrow \Phi$，使得对任意的 $\mathbf{x}, \mathbf{y}$ 有
  $$
  k(\mathbf{x}, \mathbf{y}) = \langle \phi(\mathbf{x}), \phi(\mathbf{y}) \rangle = \phi(\mathbf{x})^T \phi(\mathbf{y})
  $$

  - 非线性核函数 $k$ 表示两个向量的相似程度，是一种在高维空间里面度量数据相似度的一种手段。
  - 非线性核函数 $k$ 等价于特征空间 $\Phi$ 中的内积。
  - **引入了核函数，把高维向量的内积转变成了求低维向量的内积问题。**非线性核函数 $k$ 往往定义成和 $\mathbf{x}, \mathbf{y}$ 的内积有关的式子，这样在低维空间中计算内积就很简单。

- $\Phi$: 特征空间（feature space）
  - 可以是有限维的空间，也可以是无穷维的空间（infinite dimensional Hilbert space）。



## V. 核函数与内积的转化的例子

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240531204316.png" style="zoom:50%;" />



## 总结

- 优化问题
  $$
  \min_{\alpha} \frac{1}{2} \sum_{i=1}^m \sum_{j=1}^m \alpha_i \alpha_j y_i y_j k(\mathbf{x}_i, \mathbf{x}_j) - \sum_{i=1}^m \alpha_i \quad \text{s.t.} \quad \sum_{i=1}^m \alpha_i y_i = 0, \alpha_i \ge 0, i = 1, 2, \ldots, m
  $$

  使用与之前同样的方法求解凸二次优化问题。

- 决策判别函数
  $$
  f(x) = \text{sgn} \left( \sum_{i=1}^m \alpha_i y_i k(\mathbf{x}_i, \mathbf{x}) + b \right)
  $$
  $$
  \text{sgn}(a) = 
  \begin{cases} 
  1, & \text{if } a \ge 0, \\
  -1, & \text{if } a < 0.
  \end{cases}
  $$