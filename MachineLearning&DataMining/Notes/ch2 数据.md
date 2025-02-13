# ch2 数据



# A. 数学基础



## I. 基础概念

### 1 向量

设

$$
\mathbf{x} = \begin{bmatrix}
x_1 \\
x_2 \\
\vdots \\
x_n
\end{bmatrix}
$$

为一个有 $n$ 个元素的**列向量**。

**行向量**与有 $n$ 个元素的**列向量**不同，我们记作：
$$
\mathbf{z} = [ z_1 \, z_2 \, \cdots \, z_n ].
$$

- 两个列向量 $\mathbf{x}$ 和 $\mathbf{y}$ 的点积为

$$
\mathbf{x}^T \mathbf{y} = \sum_{i=1}^{n} x_i y_i
$$

- 当 $\mathbf{x}^T \mathbf{y} = 0$ 时， $\mathbf{x}$ 和 $\mathbf{y}$ 是正交的。

### 2 向量范数

<u>向量的范数度量它的长度。</u>

- 向量的 $p$-范数 由下式给出：

$$
\|\mathbf{x}\|_p = \left( \sum_{i=1}^{n} |x_i|^p \right)^{1/p}
$$

其中 $p \geq 1$。

- **欧几里得范数（2-范数）**也可以写成：

$$
\|\mathbf{x}\|_2 = \sqrt{\mathbf{x}^T \mathbf{x}}
\quad \|\mathbf{x}\|_2^2 = \mathbf{x}^T \mathbf{x}, \mathbf{x} \in \mathbb{R}^n
$$

> 当我们写作 $\|\mathbf{x}\|$ 而没有下标时，它可以默认是欧几里得范数。

- 点积可以写成：

$$
\mathbf{x}^T \mathbf{y} = \|\mathbf{x}\| \|\mathbf{y}\| \cos \theta
$$

其中 $\theta$ 是 $\mathbf{x}$ 和 $\mathbf{y}$ 之间的角度。

### 3 矩阵

设

$$
\mathbf{A} = \begin{bmatrix}
a_{11} & a_{12} & \cdots & a_{1n} \\
a_{21} & a_{22} & \cdots & a_{2n} \\
\vdots & \vdots & \ddots & \vdots \\
a_{m1} & a_{m2} & \cdots & a_{mn}
\end{bmatrix}
$$

为一个 $m \times n$ 矩阵。注意我们有时将 $\mathbf{A}$ 的 $i,j$ 元素记作 $A_{ij}$。对于上述矩阵，$A_{ij} = a_{ij}$。

- 如果矩阵是方阵（即 $m = n$ 且秩为 $n$），则 $\mathbf{A}$ 的逆矩阵 $\mathbf{A}^{-1}$ 满足

$$
\mathbf{A}^{-1} \mathbf{A} = \mathbf{A} \mathbf{A}^{-1} = \mathbf{I}
$$

其中 $\mathbf{I}$ 是一个 $n \times n$ 的单位矩阵。

### 4 矩阵的迹

<u>矩阵的迹，是其对角元素的和。</u>

- 矩阵的迹记作 $\text{tr}(\mathbf{A})$：

$$
\text{tr}(\mathbf{A}) = \sum_{i=1}^{n} a_{ii}
$$

- 迹算子对转置不变。

$$
\text{tr}(\mathbf{A}) = \text{tr}(\mathbf{A}^T)
$$

- 迹算子对输入的循环置换不变。

$$
\text{tr}(\mathbf{ABC}) = \text{tr}(\mathbf{CAB}) = \text{tr}(\mathbf{BCA})
$$

- 迹算子是线性的。

$$
\text{tr}(a\mathbf{X} + b\mathbf{Y}) = a\text{tr}(\mathbf{X}) + b\text{tr}(\mathbf{Y})
$$

### 5 特征分解

- 矩阵 $\mathbf{A} \in \mathbb{R}^{n \times n}$ 的特征向量 $\mathbf{u}_i$ 及其对应的特征值 $\lambda_i$ 满足：

$$
\mathbf{A} \mathbf{u}_i = \lambda_i \mathbf{u}_i
$$

- 如果我们将 $\mathbf{A}$ 的所有特征向量和特征值收集到以下矩阵中，

$$
\mathbf{U} = \begin{bmatrix}
\vert & \vert & & \vert \\
\mathbf{u}_1 & \mathbf{u}_2 & \cdots & \mathbf{u}_n \\
\vert & \vert & & \vert 
\end{bmatrix}
\quad \text{和} \quad
\mathbf{\Lambda} = \begin{bmatrix}
\lambda_1 & 0 & \cdots & 0 \\
0 & \lambda_2 & \cdots & 0 \\
\vdots & \vdots & \ddots & \vdots \\
0 & 0 & \cdots & \lambda_n
\end{bmatrix}
$$

则有 $\mathbf{A} = \mathbf{U} \mathbf{\Lambda} \mathbf{U}^{-1}$。这就是 $\mathbf{A}$ 的**特征分解**。

- 如果 $\mathbf{A}$ 是正规矩阵，则它的特征向量是正交归一的，即 $\mathbf{u}_i^T \mathbf{u}_j = 0$ 对于 $i \ne j$ 且 $\mathbf{u}_i^T \mathbf{u}_i = 1$。

### 6 矩阵的其他性质

- 设 $\mathbf{A} \in \mathbb{R}^{m \times n}$。$\mathbf{A}$ 的 **Frobenius 范数**为

$$
\|\mathbf{A}\|_F = \sqrt{ \sum_{i=1}^{m} \sum_{j=1}^{n} |a_{ij}|^2 }
= \sqrt{ \text{tr}(\mathbf{A}\mathbf{A}^T) }
$$

- 考虑一个对称矩阵 $\mathbf{A}$。

  - 如果 $\mathbf{A}$ 对所有 $\mathbf{x}$ 满足 $\mathbf{x}^T \mathbf{A} \mathbf{x} > 0$，则称 $\mathbf{A}$ 为**正定矩阵**。

  - 如果 $\mathbf{x}^T \mathbf{A} \mathbf{x} \geq 0$，则 $\mathbf{A}$ 是**正半定矩阵**。

  - 负定矩阵和负半定矩阵的定义类似。



## II. 向量与矩阵的导数

### 1 梯度

梯度将标量导数推广到多个维度。假设 $f : \mathbb{R}^n \rightarrow \mathbb{R}$ 将向量 $\mathbf{x} \in \mathbb{R}^n$ 变换为一个标量。如果 $y = f(\mathbf{x})$，那么梯度为：

$$
\nabla_{\mathbf{x}} y = \begin{bmatrix}
\frac{\partial y}{\partial x_1} \\
\frac{\partial y}{\partial x_2} \\
\vdots \\
\frac{\partial y}{\partial x_n}
\end{bmatrix}
$$

换句话说，梯度是：

- 一个与 $\mathbf{x}$ 尺寸相同的向量，即，如果 $\mathbf{x} \in \mathbb{R}^n$，则 $\nabla_{\mathbf{x}} y \in \mathbb{R}^n$。

- $\nabla_{\mathbf{x}} y$ 的每个维度告诉我们 $\mathbf{x}$ 在该维度上的微小变化如何影响 $y$。即，将 $\mathbf{x}$ 的第 $i$ 个维度改变一小部分 $\Delta x_i$，将会使 $y$ 发生变化

$$
\frac{\partial y}{\partial x_i} \Delta x_i
$$

我们也可以将其记作：

$$
(\nabla_{\mathbf{x}} y)_i \Delta x_i
$$

<details>
    <summary>例题</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527202205.png"/>
    </p>
</details>

### 2 标量相对于矩阵的导数

标量 $y$ 相对于矩阵 $\mathbf{A} \in \mathbb{R}^{m \times n}$ 的导数由下式给出：

$$
\nabla_{\mathbf{A}} y = \begin{bmatrix}
\frac{\partial y}{\partial a_{11}} & \frac{\partial y}{\partial a_{12}} & \cdots & \frac{\partial y}{\partial a_{1n}} \\
\frac{\partial y}{\partial a_{21}} & \frac{\partial y}{\partial a_{22}} & \cdots & \frac{\partial y}{\partial a_{2n}} \\
\vdots & \vdots & \ddots & \vdots \\
\frac{\partial y}{\partial a_{m1}} & \frac{\partial y}{\partial a_{m2}} & \cdots & \frac{\partial y}{\partial a_{mn}}
\end{bmatrix}
$$

与梯度类似，$\nabla_{\mathbf{A}} y$ 的第 $i,j$ 元素告诉我们 $a_{ij}$ 的微小变化如何影响 $y$。

注意：

- 如果你查找标量相对于矩阵的导数，可能会发现一些人给出的定义与上述定义是转置的。
- 两者都是有效的，但你必须与自己的符号保持一致并使用正确的规则。我们的符号称为“分母布局”符号；另一种布局称为“分子布局”符号。
- 在分母布局中，$\nabla_{\mathbf{A}} y$ 的维度和 $\mathbf{A}$ 的维度是相同的。对于梯度也是如此，即 $\nabla_{\mathbf{x}} y$ 和 $\mathbf{x}$ 的维度是相同的。在分子布局符号中，维度是转置的。
- 关于这一点的更多内容稍后会提到，但在“分母布局”中，链式法则从右到左适用，而不是从左到右。

### 3 向量相对于向量的导数

设 $\mathbf{y} \in \mathbb{R}^n$ 是 $\mathbf{x} \in \mathbb{R}^m$ 的函数。$\mathbf{y}$ 相对于 $\mathbf{x}$ 的导数应是什么维度呢？

例如，为了查看 $\Delta \mathbf{x}$ 如何修改 $y_i$，我们会计算：

$$
\Delta y_i = \nabla_{\mathbf{x}} y_i \cdot \Delta \mathbf{x}
$$

这表明导数应该是一个 $n \times m$ 的矩阵，记作 $\mathbf{J}$，其形式为：

$$
\mathbf{J} = \begin{bmatrix}
(\nabla_{\mathbf{x}} y_1)^T \\
(\nabla_{\mathbf{x}} y_2)^T \\
\vdots \\
(\nabla_{\mathbf{x}} y_n)^T
\end{bmatrix}
= \begin{bmatrix}
\frac{\partial y_1}{\partial x_1} & \frac{\partial y_1}{\partial x_2} & \cdots & \frac{\partial y_1}{\partial x_m} \\
\frac{\partial y_2}{\partial x_1} & \frac{\partial y_2}{\partial x_2} & \cdots & \frac{\partial y_2}{\partial x_m} \\
\vdots & \vdots & \ddots & \vdots \\
\frac{\partial y_n}{\partial x_1} & \frac{\partial y_n}{\partial x_2} & \cdots & \frac{\partial y_n}{\partial x_m}
\end{bmatrix}
$$

该矩阵会告诉我们 $\Delta \mathbf{x}$ 的微小变化如何根据以下公式导致 $\Delta \mathbf{y}$ 的微小变化：

$$
\Delta \mathbf{y} \approx \mathbf{J} \Delta \mathbf{x}
$$
矩阵 $\mathbf{J}$ 称为**雅可比矩阵**。

关于符号的一句话：

- 在分母布局定义中，分母向量沿行变化。
  $$
  \nabla_{\mathbf{x}} \mathbf{y} = \begin{bmatrix}
  \frac{\partial y_1}{\partial x_1} & \frac{\partial y_2}{\partial x_1} & \cdots & \frac{\partial y_n}{\partial x_1} \\
  \frac{\partial y_1}{\partial x_2} & \frac{\partial y_2}{\partial x_2} & \cdots & \frac{\partial y_n}{\partial x_2} \\
  \vdots & \vdots & \ddots & \vdots \\
  \frac{\partial y_1}{\partial x_m} & \frac{\partial y_2}{\partial x_m} & \cdots & \frac{\partial y_n}{\partial x_m}
  \end{bmatrix}
  \triangleq \frac{\partial \mathbf{y}}{\partial \mathbf{x}}
  $$

- 因此我们使用的雅可比矩阵的符号为：
  $$
  \mathbf{J} = (\nabla_{\mathbf{x}} \mathbf{y})^T
  = \left( \frac{\partial \mathbf{y}}{\partial \mathbf{x}} \right)^T
  $$

<details>
    <summary>例子</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527204818.png"/>
    </p>
</details>

### 4 Hessian 矩阵

函数 $f(\mathbf{x})$ 的 **Hessian 矩阵**是由 $f(\mathbf{x})$ 的**二阶偏导数**组成的方阵。它由以下元素组成：

$$
\mathbf{H} = \begin{bmatrix}
\frac{\partial^2 f}{\partial x_1^2} & \frac{\partial^2 f}{\partial x_1 \partial x_2} & \cdots & \frac{\partial^2 f}{\partial x_1 \partial x_n} \\
\frac{\partial^2 f}{\partial x_2 \partial x_1} & \frac{\partial^2 f}{\partial x_2^2} & \cdots & \frac{\partial^2 f}{\partial x_2 \partial x_n} \\
\vdots & \vdots & \ddots & \vdots \\
\frac{\partial^2 f}{\partial x_m \partial x_1} & \frac{\partial^2 f}{\partial x_m \partial x_2} & \cdots & \frac{\partial^2 f}{\partial x_m^2}
\end{bmatrix}
$$

我们可以将此矩阵记作 $\nabla_{\mathbf{x}} (\nabla_{\mathbf{x}} f(\mathbf{x}))$。我们通常简记为 $\nabla_{\mathbf{x}}^2 f(\mathbf{x})$。

### 5 向量值函数的链式规则

在“分母”布局中，链式法则从右到左运行。我们不会推导这一点，但我们会检查其维度和直觉。

设 $\mathbf{x} \in \mathbb{R}^m$，$\mathbf{y} \in \mathbb{R}^n$，且 $\mathbf{z} \in \mathbb{R}^p$。进一步设 $\mathbf{y} = f(\mathbf{x})$ 对于 $f : \mathbb{R}^m \rightarrow \mathbb{R}^n$ 且 $\mathbf{z} = g(\mathbf{y})$ 对于 $g : \mathbb{R}^n \rightarrow \mathbb{R}^p$。则

$$
\nabla_{\mathbf{x}} \mathbf{z} = \nabla_{\mathbf{x}} \mathbf{y} \nabla_{\mathbf{y}} \mathbf{z}
$$

同样地：

$$
\frac{\partial \mathbf{z}}{\partial \mathbf{x}} = \frac{\partial \mathbf{y}}{\partial \mathbf{x}} \frac{\partial \mathbf{z}}{\partial \mathbf{y}}
$$

- 注意 $\nabla_{\mathbf{x}} \mathbf{z}$ 应该有 $\mathbb{R}^{m \times p}$ 的维度。

- 由于 $\nabla_{\mathbf{x}} \mathbf{y} \in \mathbb{R}^{m \times n}$ 和 $\nabla_{\mathbf{y}} \mathbf{z} \in \mathbb{R}^{n \times p}$，这些操作是维度一致的。

<details>
    <summary>证明</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527210101.png"/>
    </p>
</details>



## III. 张量的导数

在这门课中，我们有时需要求超过二维的导数。例如，我们可能想要求一个向量相对于一个矩阵的导数。这将是一个三维张量。其定义如预期。特别地，如果 $\mathbf{z} \in \mathbb{R}^p$ 且 $\mathbf{W} \in \mathbb{R}^{m \times n}$，那么 $\nabla_{\mathbf{W}} \mathbf{z}$ 是一个形状为 $\mathbb{R}^{m \times n \times p}$ 的三维张量。每一个 $m \times n$ 切片（总共有 $p$ 个）是矩阵导数 $\nabla_{\mathbf{W}} z_i$。

注意，这些有时操作起来很麻烦。我们通常可以找到一种捷径来执行操作，而不必计算和存储这些高维张量导数。

<details>
    <summary><b>多元链式法则和张量导数的例子</b></summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527210757.png"/>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527210820.png"/>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527211007.png"/>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527211100.png"/>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527211117.png"/>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527211130.png"/>
    </p>
</details>

<details>
    <summary><b>关于张量导数的一些注释</b></summary>
    <p>
        <ul>
            <li>通常，通过模式直觉或查看矩阵的维度可以推断出更简单的规则，而这些张量导数不需要明确推导出来。</li>
            <li>确实，实际上计算这些张量导数、存储它们，然后进行例如张量-向量乘法，通常对内存和计算来说都不是一个好主意。在这个例子中，存储所有这些零并执行乘法是没有必要的。</li>
            <li>如果我们知道最终结果只是两个向量的外积，那么在反向传播的这一步中，我们甚至不需要计算额外的导数，也不需要存储额外的值（假设输入已经被缓存）。</li>
    	</ul>
    </p>
</details>







# B. 数据



## I. 数据

### 1 什么是数据？

- **数据集**：一组含有特征（属性）的数据对象（样本）的集合
- **样本**：由一组特征（属性）所描述的一个对象
- **特征（属性）**：描述样本或对象在某方面的表现或性质的事项

### 2 数据的数学表示

一般地，令 $D = \{ x_1, x_2, \ldots, x_m \}$ 表示 $m$ 个样本的数据集，每个样本由 $d$ 个属性描述，则每个样本 $x_i = (x_{i1}; x_{i2}; \ldots; x_{id})$ 是 $d$ 维样本空间 $\mathcal{X}$ 中的一个向量，$x_i \in \mathcal{X}$，其中 $x_{ij}$ 是 $x_i$ 在第 $j$ 个属性上的取值，$d$ 称为样本 $x_i$ 的维数。$(x_i, y_i)$ 表示第 $i$ 个样例，$y_i$ 是样本 $x_i$ 的标记（有时也称标签或标注）。



## II. 特征（属性）的类型

### 1 特征的取值

<u>**特征的取值**是指派给一个特征的数字或符号</u>

- 相同的特征可以有不同的取值
- 不同的特征可以有相同的取值

### 2 特征的类型

#### 定性属性：不具有数的大部分性质

- **标称类型**：只能区分样本之间的不同。 *例如：学号、籍贯、邮政编*  
- **序数类型**：能够对样本之间的顺序进行区分。 *例如：排名、年级、衣服的号码 {S, M, L, XL, XXL}*

#### 定量属性：用数表示，并且具有数的大部分性质，可以是连续值或整数值

- **区间类型**：能够对样本在坐标系上的相对距离进行度量。*例如：日历上的日期、摄氏或华氏温度等*

- **比率类型**：能够对样本在坐标系上的绝对位置进行标定。*例如：开尔文温度、 长度、时间、质量、货币单位等*

<details>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527213002.png"/>
    </p>
</details>
==特征类型的本质区别是其所对应的**操作**不同==

<details>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527213747.png"/>
    </p>
</details>

### 特征类型的其他方式：离散与连续

用值的个数描述属性

- 离散特征：具有有限或无限可数个值，可以是定性的也可以是定量的，常使用整数变量表示
- 连续特征：取实数值的特征，连续特征常常用浮点变量表示
- 二元特征：仅仅具有两个值的特征，常常使用0或1表示
- 非对称特征：状态的结果不是同等重要，只有非0值才重要的二元特征称为非对称二元特征

### 3 数据质量的重要性

==<u>**调优数据**比**调优模型**更有效</u>：调优模型的效果提升 < 调优数据质量的效果提升==

**好的数据 **是指：

- 标签定义的一致性
- 覆盖所有的代表性案例
- 生产环境数据分布变化的及时反馈
- 合适的数据集大小



## III. 样本的相似性和相异性

### 1 相似度和相异度的基本概念

#### 相似度

- 两个样本之间<u>相似程度</u>的**数值化**度量
- 两个样本越相似，他们之间的相似性就越高
- 相似度是**非负的**，通常取值范围在[0, 1]

#### 相异度

- 两个样本之间<u>差异程度</u>的**数值化**度量
- 两个样本越相似，他们之间的相异性越低
- 相异度是**非负的**，取值在[0,1]和[0, ∞)均有

通常术语**距离（distance）**用作**相异度**的同义词

<details>
    <summary>简单属性（单一特征）的相似度与相异度</summary>
    <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527215233.png"/>
</details>

### 2 距离

#### 闵氏距离 Minkowski Distance

> *闵氏距离的欧式距离的一种**泛化**， 欧式距离是闵氏距离的一种特例*

$$
d(\mathbf{x}, \mathbf{y}) = \left( \sum_{k=1}^{n} |x_k - y_k|^r \right)^{\frac{1}{r}}
$$

其中 $n$ 是对象的数据维度（属性的个数），$x_k$ 和 $y_k$ 分别是数据对象 $\mathbf{x}$ 和 $\mathbf{y}$ 的第 $k$ 个属性。

- $r=1$，曼哈顿距离，L1范数，L1-norm

$$
d(\mathbf{x}, \mathbf{y}) = \|\mathbf{x} - \mathbf{y}\|_1 = \sum_{k=1}^{n} |x_k - y_k|
$$

- $r=2$，欧氏距离，L2范数，L2-norm

$$
d(\mathbf{x}, \mathbf{y}) = \|\mathbf{x} - \mathbf{y}\|_2 = \sqrt{ \sum_{k=1}^{n} |x_k - y_k|^2 }
$$

- $r=\infty$，上确界距离，$\infty$范数，L-norm

  - 对象各个属性之间的最大距离，即上确界。

$$
d(\mathbf{x}, \mathbf{y}) = \|\mathbf{x} - \mathbf{y}\|_\infty = \lim_{r \to \infty} \left( \sum_{k=1}^{n} |x_k - y_k|^r \right)^{\frac{1}{r}}
$$

#### 距离的典型特性

距离（如欧几里得距离）满足以下三个特性：  

1. **非负性**：对于任意 $p$ 和 $q$，存在 $d(p, q) \geq 0$；当且仅当 $p = q$ 时 $d(p, q) = 0$。 
2. **对称性**：对于任意 $p$ 和 $q$，$d(p, q) = d(q, p)$。
3. **三角不等式**：对于任意 $p$，$q$ 和 $r$，$d(p, r) \leq d(p, q) + d(q, r)$。

### 3 相似性

#### 相似度的性质

如果 $s(\mathbf{x}, \mathbf{y})$ 是数据点 $\mathbf{x}$ 和 $\mathbf{y}$ 之间的相似度

1. **非负性**：仅当 $\mathbf{x} = \mathbf{y}$ 时 $s(\mathbf{x}, \mathbf{y}) = 1$。($0 \leq s \leq 1$)
2. **对称型**：对于所有 $\mathbf{x}$ 和 $\mathbf{y}$，$s(\mathbf{x}, \mathbf{y}) = s(\mathbf{y}, \mathbf{x})$

#### 二元数据相似度度量

- **简单匹配系数 （SMC）**：处理<u>对称</u>的二值离散型属性
  $$
  \text{SMC} = \frac{\text{值匹配的属性个数}}{\text{属性个数}} 
  = \frac{f_{11} + f_{00}}{f_{01} + f_{10} + f_{11} + f_{00}}
  $$

- **Jaccard 系数**：处理包含<u>非对称</u>的二值离散型属性
  $$
  J = \frac{\text{匹配个数}}{\text{00匹配中不涉及的属性个数}} 
  = \frac{f_{11}}{f_{01} + f_{10} + f_{11}}
  $$

<details>
    <summary>例子</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527221026.png"/>
    </p>
</details>

#### 余弦相似度

如果 $\mathbf{x}$ 和 $\mathbf{y}$ 是两个文档向量，则

$$
\cos(\mathbf{x}, \mathbf{y}) = \frac{\langle \mathbf{x}, \mathbf{y} \rangle}{\|\mathbf{x}\| \|\mathbf{y}\|} = \frac{\langle \mathbf{x'}, \mathbf{y} \rangle}{\|\mathbf{x}\| \|\mathbf{y}\|}
$$

其中 $'$ 表示向量或者矩阵的转置，$\langle \mathbf{x}, \mathbf{y} \rangle$ 表示两个向量的内积：

$$
\langle \mathbf{x}, \mathbf{y} \rangle = \sum_{k=1}^{n} x_k y_k = \mathbf{x}^T \mathbf{y}
$$

且 $\|\mathbf{x}\|$ 是向量 $\mathbf{x}$ 的长度，

$$
\|\mathbf{x}\| = \sqrt{ \sum_{k=1}^{n} x_k^2 } = \sqrt{ \langle \mathbf{x}, \mathbf{x} \rangle } = \sqrt{ \mathbf{x}' \mathbf{x} }
$$

- 在向量的点积当中，<u>0-0 匹配是没有贡献的</u>，因此，**余弦相似度** 和 **Jaccard**系数一样，适用于<u>**非对称属性**</u>。同时，余弦相似度还可以处理非二元向量。
- ==欧式距离衡量空间点的**直线距离**，余弦距离衡量点在空间的**方向差异**。==

<details>
    <summary>例子</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527221443.png"/>
    </p>
</details>

### 4 相关性

- 相关性被用于测量两个变量（高度和重量）之间或两个对象之间的关系

- 若两个数据对象中的值来自不同的属性，可使用**相关性来度量属性之间的相似度**。

#### 皮尔森相关系数

度量两个变量之间的**线性相关性**：<u>协方差与标准差之比</u>
$$
\text{corr}(\mathbf{x}, \mathbf{y}) = \frac{\text{covariance}(\mathbf{x}, \mathbf{y})}{\text{standard\_deviation}(\mathbf{x}) \times \text{standard\_deviation}(\mathbf{y})} = \frac{s_{xy}}{s_x s_y}
$$

$$
\text{covariance}(\mathbf{x}, \mathbf{y}) = s_{xy} = \frac{1}{n-1} \sum_{k=1}^{n} (x_k - \overline{x})(y_k - \overline{y})
$$

$$
\text{standard\_deviation}(\mathbf{x}) = s_x = \sqrt{ \frac{1}{n-1} \sum_{k=1}^{n} (x_k - \overline{x})^2 }
$$

$$
\text{standard\_deviation}(\mathbf{y}) = s_y = \sqrt{ \frac{1}{n-1} \sum_{k=1}^{n} (y_k - \overline{y})^2 }
$$

$$
\overline{x} = \frac{1}{n} \sum_{k=1}^{n} x_k \quad \text{是} \quad \mathbf{x} \quad \text{的均值}
$$

$$
\overline{y} = \frac{1}{n} \sum_{k=1}^{n} y_k \quad \text{是} \quad \mathbf{y} \quad \text{的均值}
$$

皮尔森系数的局限性：对于**非线性的相关性**难以建模

<details>
    <summary>例题</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240527223255.png"/>
    </p>
</details>







# C. 特征工程

**特征工程是利用数据领域的相关知识来创建能够使机器学习算法达到最佳性能的特征的过程。**

> *数据和特征决定了机器学习的**上限**，而模型和算法只是逼近这个上限而已。*



## I. 数据清洗

### 1 数据质量

数据质量问题对于数据处理的效果有着非常严重的影响

### 2 数据质量问题

#### a. 噪声

噪声是测量误差的随机部分

#### b. 离群点

离群点是具有**不同于数据集中其他大部分数据**样本特征的数据样本

#### c. 缺失数据

缺失类型：

- 完全随机缺失：指的是数据的缺失是完全随机的，不依赖于任何不完全变量或完全变量，不影响样本的无偏性。
- 随机缺失：指的是数据的缺失不是完全随机的，即该类数据的缺失依赖于其他完全变量。
- 非随机缺失：指的是数据的缺失与不完全变量自身的取值有关。

处理缺失数据：

- 删除相应的数据对象
- 在计算和分析过程中忽略缺失值
- 对缺失数据进行估计

#### d. 数据冗余

数据集可能包含重复或者几乎重复的数据

数据清洗：去重处理

#### e. 数据矛盾

数据样本中存在自相矛盾的特征

处理方式：

- 和数据来源进行确认，评估不同特征的可靠性
- 修正矛盾的数据

### 采样

- 采样是一种选择数据对象子集进行分析的常用方法。

- 进行数据采样<u>成功的关键</u>在于：**采样样本本身能够代表全样本的统计特性**

#### 采样方法

- 简单采样：选取任何特定项的概率相等
  - 简单无放回抽样
  - 简单有放回抽样
- 分层采样：将数据分成几个组; 再分别从各个组中随机采样
- 自适应或渐进采样：从一个小样本开始，然后增加样本容量直至得到足够容量的样本



## II. 数据预处理

### 1 无量纲化

特征不属于同一量纲，即特征的规格不一样，不能够一起比较。

#### a. 归一化

样本除以总样本的均值
$$
\hat{x}_n = \frac{x_n}{\overline{x}}
$$

$$
\text{AM}(x_1, \ldots, x_n) = \frac{1}{n}(x_1 + \cdots + x_n) \quad \text{算数平均}
$$

$$
\text{GM}(x_1, \ldots, x_n) = \sqrt[n]{x_1 \times \cdots \times x_n} \quad \text{几何平均}
$$

$$
\text{HM}(x_1, \ldots, x_n) = \frac{n}{\frac{1}{x_1} + \cdots + \frac{1}{x_n}} \quad \text{调和平均}
$$

$$
\min \leq \text{HM} \leq \text{GM} \leq \text{AM} \leq \max
$$

#### b. Min-Max 标准化

**区间缩放法：**将特征的取值区间缩放到某个特点的范围，例如[0, 1]等。
$$
x' = \frac{x - \text{Min}}{\text{Max} - \text{Min}}
$$

#### c. Z-score 标准化

标准化的前提是特征值服从 **正态分布**，标准化后，其转换成 **标准正态分布**。
$$
z = \frac{x - \mu}{\sigma}
$$

$$
\frac{1}{\sigma \sqrt{2\pi}} \exp \left( - \frac{(x - \mu)^2}{2\sigma^2} \right)
$$

$\mu$ 是总体的均值，$\sigma$ 是总体的标准差。

<details>
    <summary>标准化方法</summary>
    <p>
        <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240528135411.png"/>
    </p>
</details>

### 2 特征离散化

- 定量特征二值化

  设定一个阈值，大于阈值的赋值为1，小于等于阈值的赋值为0，公式表达如下：

  $$
  x' = \begin{cases} 
  1, & x > \text{threshold} \\
  0, & x \leq \text{threshold} 
  \end{cases}
  $$



## III. 特征构建

**特征创建** 指的是从原始数据中人工的构建新的特征，使其能够捕获原来特征所不能够捕获的重要信息

特征创建的三种常用方法

- 特征提取
  - 特征提取算子
  - 提取统计特征
- 将数据投影到一个新的空间
- 构建新的特征
  - 从多个原特征构造新的特征



## IV. 特征提取-降维

- 特征提取是从最初的一组测量数据开始，构建旨在提供信息且非冗余的派生值（特征），以促进后续的学习和泛化过程。

- 特征提取是一个**降维**过程
- 降维的目的
  - 避免维度灾难：当数据的维度增加时，数据将会变得特别**稀疏**
  - 减少数据挖掘所需要的时间和内存要求
  - 使得数据更加方便的被可视化
  - 排除数据中不重要的数据特征以及降低数据噪声
- 降维技术
  - 无监督：主成分分析（PCA）
    - PCA：减少数据集的维度，同时保持数据集中**对方差贡献最大的特征**
    - PCA就是找出数据中最主要的方面，用数据中最重要的方面来代替原始数据。
    - PCA的<u>特点</u>：
      - 主成分对应的基为数据方差贡献最大方向
      - 成分的重要性逐步递减
      - 成分之间相互**正交**
  - 有监督：线性判别分析（LDA）
  - 其它有监督的和非线性技术



## V. 特征选择

- 特征选择，又称变量选择、属性选择或变量子集选择，是选择相关特征（变量、预测器）**子集**用于模型构造的过程。
- 简单地说：检测相关特征，摒弃冗余特征，获得特征子集，从而以最小的性能损失更好地描述给出的问题。



## 特征工程、特征提取、特征选择之间的特点

- **特征工程**：从已有数据中创建新的特征；注入领域知识。
- **特征提取**：将原始数据转换为特征，会创建新特征；降维过程。
- **特征选择**：选择特征子集；不创建新特征。

<u>特征工程</u>和<u>特征提取</u>都是将原始数据转换为适合建模的特征，有些情况下可以互换概念，但**特征提取更注重数据降维**。

<u>特征选择</u>不创建新特征，注重删除无用特征。有时候还会看到<u>特征转换,</u>它属于数据转换，目的是提高算法的精度。