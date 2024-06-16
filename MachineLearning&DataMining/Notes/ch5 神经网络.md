# ch5 神经网络



# A. 神经网络基础

**神经网络**是由具有适应性的**简单单元**组成的广泛并行互联的网络, 它的组织能够模拟生物神经系统对真实世界物体所作出的反应。



## I. 神经元模型

### M-P神经元模型

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529212509.png" style="zoom:50%;" />

**输入**：来自其他 $n$ 个神经元传递过来的输入信号 $(x_1, x_2, ..., x_n)$

**处理**：输入信号通过带权重 $(w_1, w_2, ..., w_n)$ 的连接进行传递，神经元接收到总输入值 $\sum_{i=1}^n w_i x_i$ 将与神经元的阈值 $\eta$ 进行比较

**输出**：通过**激活函数 (activation function)** 的处理以得到神经元的输出

### 激活函数

典型的神经元激活函数

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529212313.png" style="zoom: 50%;" />



## II. 多层神经网络

### 多层前馈神经网络

- **定义**：每层神经元与下一层神经元全互联，神经元之间不存在同层连接也不存在跨层连接

- **前馈**：输入层接受外界输入，隐含层与输出层神经元对信号进行加工，最终结果由输出层神经元输出

- **学习**：根据训练数据来调整神经元之间的“连接权”以及每个功能神经元的“阈值”

### 多层网络
包含隐层的神经网络

- **浅层神经网络**：仅含有一个隐含层 (shallow neural network)

- **深度神经网络**：至少含有三个隐含层 (deep neural network)

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529212809.png" style="zoom:50%;" />

> 深度意味着含有很多隐藏层

多层网络的要素：

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529213702.png" style="zoom:50%;" />



## III. Softmax函数

Softmax函数作为**输出层**激活函数，一般用于<u>多分类任务</u>。

Softmax 函数将一个含任意实数的 K 维向量压缩成另一个 K 维实向量，其中每个元素的范围都是 (0,1)，并且所有元素的和为1。
$$
\text{Softmax}(z_i) = \frac{e^{z_i}}{\sum_{j=1}^K e^{z_j}}
$$
其中：

- $\mathbf{z}$ 是输入向量
- $z_i$ 是输入向量中的第 $i$ 个元素
- $K$ 是类别的总数
- 分母是对所有输入向量的元素进行指数函数运算后的结果的总和。



## IV. 代价函数 cost function

**代价(损失)函数** 是网络实际输出和目标值之间的**欧几里得距离**或**交叉熵**

### 损失函数

定义样例损失函数： 
$$
C(\theta) = \sum_{k} \| \hat{y}_k - f(x_k;\theta) \|^2
$$
“好的”函数： $f^*(x;\theta) \sim \hat{y}$  $\longrightarrow \| \hat{y} - f^*(x;\theta) \|^2 \approx 0$

### 总代价函数

对所有训练样例的误差进行求和
$$
C(\theta) = \sum_{r=1}^{R} L^r(\theta)
$$

求使得代价函数最小时的参数 $\theta^*$

$$
\theta^* = \arg \min_{\theta} C(\theta)
$$

### 优化：梯度降方法

梯度下降法的主要思想：**每次朝着与当前梯度相反的方向搜索解**

梯度降方法从来不能保证获得<u>全局最小解</u>。

不同的初始点 $\theta^0$，达到不同的最小值，因此有不同的结果。
$$
\min_\theta C(\theta) \xrightarrow{\text{梯度下降}} \text{最佳网络参数 } \theta^*
$$
<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529215251.png" style="zoom:50%;" />



## V. 神经网络中的Batch Size, Iteration, Epoch

- **Batch size(批量大小)**: 即1次迭代使用的样本量
- **Iteration(迭代)**: 1次iteration, 即使用1个batch size样本训练网络参数1次
- **Epoch (期、轮)**: 1个epoch表示遍历了1遍训练集中的所有样本

计算公式：
$$
\text{one epoch} = \text{number of iterations} = N = \text{训练样本的数量} \ / \ \text{batch\_size}
$$

<details>
    <summary>例子</summary>
    <p>
        <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/image-20240530120908080.png" style="zoom:67%;" />
    </p>
</details>




## VI. 偏置(bias)在神经网络中的作用

改变权重 w0 本质上只改变了S形的“陡度”。**偏置(bias)** 可将激活函数向左或向右移动，这对于模型学习至关重要。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530122154.png" style="zoom: 67%;" />

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530122434.png" style="zoom: 33%;" />



## VII. 非线性激活函数

神经网络中使用**非线性函数**作为激活函数

### 常见的非线性激活函数

- **Sigmoid**
  $$
  \text{sigmoid}(x) = \frac{1}{1 + e^{-x}}
  $$

- **双曲正切函数 Tanh**
  $$
  \text{tanh}(x) = \frac{\sinh(x)}{\cosh(x)} = \frac{e^x - e^{-x}}{e^x + e^{-x}}
  $$

- **Rectified Linear Unit (ReLU)**
  $$
  \text{ReLU}(x) = \max(x, 0)
  $$

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530122039.png" style="zoom:67%;" />

### 为什么使用非线性激活函数？

- 如果**激活函数是线性的**，则神经网络的工作原理与**线性变换**相同。

  - 假设 $ a^l $ 是全连接前馈神经网络的第 $ l $ 层的输出($ a^0 $ 是输入层), 则其可表示为 $ a^l = \sigma(W^l a^{l-1}), l > 1 $, $ \sigma $ 为激活函数。如果 $ \sigma $ 是线性的, 不妨设 $ \sigma(x) = x $, 则最后一层输出
    $$
    \begin{aligned}
    a^L &= \sigma(W^L a^{L-1}) = W^L a^{L-1} = W^L W^{L-1} a^{L-2} = \cdots \\
        &= (W^L W^{L-1} \cdots W^1) a_0 \\
        &= \mathbf{W} a^0,
    \end{aligned}
    $$
    其中 $ \mathbf{W} = W^L W^{L-1} \cdots W^1 $

  - 这意味着深度神经网络(DNN) 退化成一个**线性模型**，DNN将失去其大部分表示学习能力(对于全连接网络和卷积神经网络)，因此，没有足够的能力去建模许多复杂类型的数据。

- 用**非线性**激活函数，多层神经网络可以逼近更复杂的函数





# B. 全连接多层神经网络与反向传播算法



## I. 记号定义

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529215701.png" style="zoom:67%;" />

### 层与层之间输出关系：$\mathbf{a}$ - $\mathbf{z}$

带权输入
$$
\mathbf{z}^l=\mathbf{W}^l\mathbf{a}^{l-1}+\mathbf{b}^l
$$

<details>
    <summary>推导</summary>
    <p>
        <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529215945.png" style="zoom:67%;" />
    </p>
</details>

### 同层之间输出关系：$\mathbf{z}$ - $\mathbf{a}$

$$
\mathbf{a}^l = \sigma(\mathbf{z}^l)
$$

$\sigma(*)$ 为sigmoid激活函数

### 层输出关系

$$
\mathbf{a}^l = \sigma(\mathbf{W}^l\mathbf{a}^{l-1}+\mathbf{b}^l)
$$



## II. 全连接前馈神经网络

### 1 网络构造

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529221440.png" style="zoom: 67%;" />

$$ f : \mathbb{R}^N \rightarrow \mathbb{R}^M $$

全连接前馈神经网络的参数 $\theta = \{W^1, b^1, W^2, b^2, ..., W^L, b^L\}$

神经网络表示函数：
$$
y = f(x) = \sigma (W^L \cdots \sigma (W^2 \sigma (W^1 x + b^1) + b^2) \cdots + b^L)
$$

### 2 网络参数求解的梯度降方法

#### 损失函数与梯度

损失函数：
$$
C(\theta) = \sum_{k} \| \hat{y}_k - f(x_k;\theta) \|^2
$$
梯度：
$$
\nabla C(\theta) = \begin{bmatrix}
\vdots \\
\frac{\partial C(\theta)}{\partial w_{ij}^l} \\
\vdots \\
\frac{\partial C(\theta)}{\partial b_i^l}
\end{bmatrix}
$$

#### 梯度降方法

梯度降方法迭代求网络参数 θ 算法：

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529222351.png" style="zoom:67%;" />

$$
(w_{ij}^l)^{k+1} = (w_{ij}^l)^k - \eta \frac{\partial C((w_{ij}^l)^k)}{\partial w_{ij}^l}
$$

$$
(b_{i}^l)^{k+1} = (b_{i}^l)^k - \eta \frac{\partial C((b_{i}^l)^k)}{\partial b_{i}^l}
$$


<details>
    <summary>3个参数的简单情况</summary>
    <p>
        均方误差损失函数
        <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529222804.png"/>
    </p>
    <p>
        更新第t次迭代的三个参数
        <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529222613.png"/>
    </p>
</details>

### 3 反向传播

计算的梯度可能包括数百万个参数，为了有效地计算梯度, 使用**反向传播算法**

#### 前向传播 vs 反向传播算法

在前馈神经网络中

- 前向传播
  - 从输入 $\mathbf{x}$ 到输出 $\mathbf{y}$，信息通过网络<u>前向传播</u>
  - 在训练阶段, 前向传播可以持续向前传递，直到产生代价函数 $C(θ)$
- 反向传播
  - 允许来自代价函数的信息通过网络<u>反向流动</u>, 以便计算**梯度**
  - 可以被应用到任何函数

#### 链式法则

假设 $f, g: \mathbb{R} \rightarrow \mathbb{R}$ 并且 $y = f(x), z = g(y)$，我们可以写为：$x \xrightarrow{f} y \xrightarrow{g} z$

链式法则为：
$$
\frac{\partial z}{\partial x} = \frac{\partial z}{\partial y} \frac{\partial y}{\partial x}
$$

则
$$
\Delta x \rightarrow \Delta y = \frac{\partial y}{\partial x} \Delta x \rightarrow \Delta z = \frac{\partial z}{\partial y} \Delta y = \frac{\partial z}{\partial y} \frac{\partial y}{\partial x} \Delta x
$$
链式法则在前馈神经网络中的应用：

$$
x = f(w), \ y = f(x), \ z = f(y)
$$

$$
\Delta w \rightarrow \Delta x \rightarrow \Delta y \rightarrow \Delta z
$$

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240529223918.png" style="zoom: 50%;" />

#### 定义误差 $\delta_i^l$

- 反向传播其实是对权重和偏置变化影响代价函数过程的理解
- **中间量**：第 $l$ 层第 $i$ 个神经元上的误差 $\delta_i^l$
- 反向传播将给出计算误差 $\delta_i^l$ 的流程，然后将其关联到计算 $\dfrac{\partial C}{\partial w_{ij}^l}$ 和 $\dfrac{\partial C}{\partial b_i^l}$
- 定义第 $l$ 层第 $i$ 个神经元上的误差 $\delta_i^l$ 为
  $$
  \delta_i^l \equiv \frac{\partial C}{\partial z_i^l}
  $$

#### 计算误差 $\delta_i^l$

思路：从第 $L$ 层 （输出层）到第 $1$ 层（输入层）

1. 计算 $\delta^L$
   $$
   \delta^L = \nabla C(a) \odot \sigma'(z^L)
   $$

   > $\odot$ 表示逐元素相乘

   <details>
       <summary>推导</summary>
       <p>
           <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530111140.png" style="zoom:50%;" />
       </p>
   </details>

2. 由 $\delta^{l+1}$ 计算 $\delta^l$

   <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530110720.png" style="zoom:50%;" />
   $$
   \delta_i^l = \sigma'(z_i^l) \sum_k w_{ki}^{l+1} \delta_k^{l+1}
   $$
   矩阵-向量式表示：
   $$
   \delta^l = \sigma'(z^l) \odot \left( \mathbf{W}^{l+1} \right)^\mathrm{T} \delta^{l+1}
   $$

   <details>
       <summary>推导</summary>
       <p>
           <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530113912.png" style="zoom:50%;" />
           <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530114011.png" style="zoom:50%;" />
       </p>
   </details>

#### 计算权重的导数 $\dfrac{\partial C}{\partial w_{ij}^l}$ 

$$
\begin{aligned}
\frac{\partial C}{\partial w_{ij}^l} &= \frac{\partial C}{\partial z_i^l} \frac{\partial z_i^l}{\partial w_{ij}^l} \\
&= 
\begin{cases} 
a_j^{l-1} \delta_i^l, & l > 1 \\ 
x_j \delta_i, & l = 1 
\end{cases}
\end{aligned}
$$

当 $l > 1$ 时（至少2个隐藏层），$\dfrac{\partial z_i^l}{\partial w_{ij}^l} = a_j^{l-1}$

当 $l = 1$ 时（只有输入层与输出层），$\dfrac{\partial z_i^l}{\partial w_{ij}^l} = x_j$

#### 计算偏置的导数 $\dfrac{\partial C}{\partial b_j^l}$

$$
\frac{\partial C}{\partial b_i^l} = \frac{\partial C}{\partial z_i^l} \frac{\partial z_i^l}{\partial b_i^l} = \delta_i^l
$$

#### 反向传播理解

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530115754.png" style="zoom: 50%;" />


#### 反向传播算法

1. **输入样本 $x$**：为输入层设置对应的激活值 $a^1$。

2. **前向传播**：对每个 $l = 2, 3, ..., L$ 计算相应的 $z^l = w^l a^{l-1} + b^l$ 和 $a^l = \sigma(z^l)$

3. **输出层误差 $\delta^L$**：计算向量 $\delta^L = \nabla_a C \odot \sigma'(z^L)$

4. **反向误差传播**：对每个 $l = L-1, L-2, ..., 2$，计算 $\delta^l = ((\mathbf{w}^{l+1})^T \delta^{l+1}) \odot \sigma'(z^l)$

5. **输出**：代价函数的梯度由 $\dfrac{\partial C}{\partial w_{jk}^l} = a_k^{l-1} \delta_j^l$ 和 $\dfrac{\partial C}{\partial b_j^l} = \delta_j^l$ 得出  

## III. 梯度降优化求解

### a. 批量（batch）梯度降

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530120351.png" style="zoom:67%;" />

### b. 随机梯度降（SGD)

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530120422.png" style="zoom:67%;" />

### c. 小批量（Mini-batch）梯度降优化

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530120507.png" style="zoom:67%;" />





# C. 卷积神经网络



## I. 卷积操作

### 1 滤波 filter

**滤波**也称**卷积核**、**特征提取器**

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530135015.png" style="zoom:50%;" />

### 2 步幅 stride & 特征图 feature map

**步幅 (strides)** 为控制图像宽高尺寸的方式之一。

下图中的 **滤波核(Kernel)** 的移动步幅分别为1和2，可以观察到输出的 **特征图 (Feature map)** 大小也不同，虽然通常宽高上的步幅会设为相等，但我们也可以<u>通过不同的长宽步幅控制特征图 (Feature map)不同尺度的变化</u>。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530135212.png" style="zoom: 67%;" />

### 3 填充 padding

**填充（padding）**是通过在图像周围<u>补充0的预定值</u>，其与**步幅(stride)**和**卷积核的尺寸**决定输出**特征图的大小**。

下图为*3\*3*的卷积核，*stride* 为*1*，*padding* 也为*1*，可以发现输出的特征图与输入的图像拥有<u>相同的大小</u>。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530135525.png" style="zoom:40%;" />

#### 零加边/零填充 zero padding

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530135327.png" style="zoom: 50%;" />

### 4 通道 channel

彩色图像通常由RGB三色构成，即3个通道。

每个卷积核均与输入的3个通道特征图**分别**作卷积，再将3个通道的处理结果**相加**得到卷积输出特征图。

#### 多通道图像卷积操作的通道一致性

每一个<u>卷积核(滤波)的通道数</u>必须和<u>输入图像的通道数</u> **相同**。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530135923.png" style="zoom: 50%;" />

每次卷积操作后的<u>输出的通道数</u>和<u>滤波的个数</u> **相同**。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530140306.png" style="zoom:55%;" />

### 5 池化 Pooling

**池化**：选取一个输入特征图的某个区域内所有神经元的<u>最大值</u>或<u>平均值</u>作为这个区域的**概括**

#### 最大池化 Max Pooling

选取一个输入特征图的某个区域内所有神经元的<u>最大值</u>作为这个区域的**概括**

将每个特征图划分为2x2(或3x3)大小的 **区域(可重叠)**, 然后再 **下采样**：

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530140957.png" style="zoom: 50%;" />

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530141037.png" style="zoom: 50%;" />



## II. 特征图的计算

- 输入图像大小: $H_{in} \times W_{in} \times n_c$
- 每个滤波器(卷积核)大小: $k \times k \times n_c$
- 滤波器(卷积核)个数: $K$
- 加边填充 padding: $P$
- 卷积核滑动步幅(stride): $S$

### 卷积后输出特征图大小计算

$$
\left( \left\lfloor \frac{H_{in} - k + 2P}{S} \right\rfloor + 1 \right) \times \left( \left\lfloor \frac{W_{in} - k + 2P}{S} \right\rfloor + 1 \right) \times K
$$

计算卷积层输出特征图大小，当除不尽时，一般**向下取整**。

### 池化后输出特征图大小计算

$$
\left( \left\lceil \frac{H_{in} - k + 2P}{S} \right\rceil + 1 \right) \times \left( \left\lceil \frac{W_{in} - k + 2P}{S} \right\rceil + 1 \right) \times K
$$

计算池化层输出特征图大小，当除不尽时，通常**向上取整**。



## III. 为什么使用CNN处理图像

### 1 图像中的一些模式比整个图像小得多

网络中神经元的作用是检测图像中有无某些重要的模式，不需要把整个图像作为输入即可检测图像中某些关键模式。

#### 稀疏连接

非全连接。参数更少。

下一层每一个神经元只关注上一层图像的**局部感受野**区域，即只把上一层的**局部感受野**作为下一层的输入。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530144124.png" style="zoom: 67%;" />

- 不同的神经元可具有**相同的感受野**
- 不同的神经元的感受野可以**重叠**

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530144009.png" style="zoom:67%;" />

### 2 相同的模式出现在图像得不同区域

可使用相同的检测器（滤波），共享相同的参数

#### 参数共享

参数共享：不同感受野的两个不同神经元的权重和偏置共享。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530144357.png" style="zoom:67%;" />

==注意：具有<u>相同感受野</u>的两个神经元**不会**共享参数。==

### 3 下采样图像不改变

下采样图像以使图像更小，但不影响人对图像目标的理解。

**处理图像的<u>网络参数</u>较少**。



## IV. 1×1 卷积

### 1×1 卷积的作用

- 融合不同特征图通道间同一位置的信息并且**减小通道数**

  <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530145539.png" style="zoom: 67%;" />

  <u>如果我们增加**卷积核的数量**， 我们可以控制**输出的深度**。</u> 

  > 例如， 使用<u>2个卷积核</u> (每个深度为3)， 输出特征图的<u>深度为2</u>：
  >
  > <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530145643.png" style="zoom:67%;" />

- 融合不同特征图通道间同一位置的信息并且**增加非线性**

  <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530145719.png" style="zoom:67%;" />

  > 在上图中， 我们使用3个卷积核， 输入和输出数据立方体维度和通道数完全相同。 
  >
  > 这时， 1×1卷积核可作为向输入数据立方体添加非线性的一种手段。

- 作**通道之间的合成**

  1×1卷积可以控制输入**特征图的深度**，可以减小或增大它，或者在不改变深度时仅**添加非线性**。

  下图，利用1×1卷积先增加特征图的深度，再减小特征图的深度：

  <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530150847.png" style="zoom:50%;" />

### 1×1 卷积作用效果



<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530150159.png" style="zoom: 60%;" />

- 若滤波的个数**大于**输入层的深度，那么会起到了**升通道数**的效果；
- 若滤波的个数**小于**输入层的深度，那么就起到了**降通道数**的效果。



## V. 池化（pooling）层

Pooling 的本质，其实是**采样**。Pooling 对于输入的特征图，选择某种方式对其进行**压缩**。

### 池化层的作用

- **保留主要特征的同时减少参数和计算量**

  因为经过MaxPool可以减小卷积核的尺寸，同时又可以保留相应特征，所以主要用来降维。

- **在一定程度上能防止过拟合**

  由于这一层没有参数，不需要学习。

- **提高特征的不变性**

  这种不变性包括**translation(平移)**，**rotation(旋转)**，**scale(尺度)**。这就使网络的鲁棒性增强了，有一定抗扰动的作用。

  <details>
      <summary>不变性详情</summary>
      <p>
          <b>平移不变性</b>
          <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/image-20240530151800126.png" style="zoom:50%;" />
      </p>
      <p>
          <b>旋转不变性</b>
          <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/image-20240530151830959.png" style="zoom:50%;" />
      </p>
      <p>
          <b>尺度不变性</b>
          <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/image-20240530151843984.png" style="zoom:50%;" />
      </p>
  </details>



## VI. 全连接层

**全连接（fully connected，FC）层** 在整个卷积神经网络中起到 “**分类器**” 的作用。

### 全连接层的作用

如果说卷积层、池化层和激活函数等操作是<u>将原始数据映射到隐层特征空间</u>的话，全连接层则起到将学到的<u>“分布式特征表示”映射到样本标记空间</u>的作用。

- 全连接可写成矩阵乘法，相当于一个**特征空间变换**，可以把有用的**信息提取整合**。再加上激活函数的非线性映射，多层全连接层理论上可以模拟任何**非线性变换**。
- 全连接层鉴别与高层特征最相关的类别，最终其权重用于得到不同类别的正确**概率**。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530152356.png"/>



## VII. 激活函数 - ReLU

- 修正线性单元 (ReLU, Rectified Linear Unit)
  $$
  f(x) = \max(0, x) = \begin{cases}
  x & x > 0 \\
  0 & x \leq 0 
  \end{cases}
  $$
  $$
  f'(x) = \begin{cases}
  1 & x > 0 \\
  0 & x \leq 0 
  \end{cases}
  $$

- ReLU 函数其实是**分段线性函数**：把所有的负值都变为 0，而正值不变。这种操作被称为**单侧抑制**。有了这单侧抑制，才使得神经网络中的神经元也具有了稀疏激活性。

- 当训练一个深度分类模型的时候，和目标相关的特征往往也就几个，因此通过 ReLU 实现稀疏后的模型能够更好地挖掘相关特征，拟合训练数据。

- 对于非线性函数而言，ReLU 由于非负区间的梯度为常数，因此**不存在梯度消失问题 (Vanishing Gradient Problem)**，使得模型的收敛速度维持在一个稳定状态。ReLU 的梯度大多数情况下是常数，有助于解决深层网络的收敛问题。ReLU 线性部分功能很好的传播梯度，而<u>置 0 部分本身就是为了稀疏性而牺牲梯度</u>。


<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530152604.png" style="zoom:50%;" />

## VIII. CNN感受野

- 卷积神经网络每一层输出特征图的像素点（或神经元）在原始图像上映射的区域大小定义为感受野，计算公式为
  $$
  RF_l = RF_{l-1} + \left( f_l - 1 \right) \times \prod_{i=1}^{l-1} s_i
  $$
  - 其中 $l$ 为卷积层数； $RF_l$ 为层 $l$ 的感受野，$RF_0 = 1$； $f_l$ 为层 $l$ 的卷积核尺寸； $s_i$ 为层 $i$ 的步幅， $s_0 = 1$。
- 例如：在一个由3层 $3 \times 3$ 卷积核组成的卷积神经网络中，第1层网络输出的像素映射在原始图像的 $3 \times 3$ 区域，故而第1层的感受野为3，字母表示为 $RF_1 = 3$；第2层网络输出的像素映射在第1层输出的 $3 \times 3$ 区域，第1层输出的 $3 \times 3$ 区域映射在原始图像的 $5 \times 5$ 区域，故而第2层的感受野为5，即 $RF_2 = 5$；同理可得，第3层的感受野为7，即 $RF_3 = 7$。





# D. 经典的CNN网络模型

## I. LeNet-5

### 1 LeNet-5 网络架构细节

1. **Input** 
   输入图像统一归一化为 $32 \times 32$。

2. **C1卷积层** 
   经过 $(5 \times 5 \times 1) \times 6$ 卷积核，stride=1, pad=0，生成feature map为 $28 \times 28 \times 6$。

3. **S2池化层**
   经过 $(2 \times 2)$ 池化核，平均池化，stride=2, pad=0，生成feature map为 $14 \times 14 \times 6$。

4. **C3卷积层** 
   经过 $(5 \times 5 \times 6) \times 16$ 卷积核，stride=1, pad=0，生成feature map为 $10 \times 10 \times 16$。

5. **S4池化层** 
   经过 $(2 \times 2)$ 池化核，平均池化，stride=2, pad=0，生成feature map为 $5 \times 5 \times 16$。

6. **C5卷积层** 
   经过 $(5 \times 5 \times 16) \times 120$ 卷积核，stride=1, pad=0，生成feature map为 $1 \times 1 \times 120$。

7. **F6全连接层** 
   输入为 $1 \times 1 \times 120$，输出为 $1 \times 1 \times 84$，总参数量为 $120 \times 84$。

8. **F7全连接层（输出层）** 
   输入为 $1 \times 1 \times 84$，输出为 $1 \times 1 \times 10$，总参数量为 $84 \times 10$。10就是分类的类别数。输出层激活函数为softmax。

中间层激活函数是ReLU。

### 2 LeNet网络模型的参数量（空间复杂度）

卷积层有参数，池化层无参数。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530203422.png" style="zoom:67%;" />

- 网络权重参数量（仅权重）：
  $$
  5 \times 5 \times 1 \times 6 + 5 \times 5 \times 6 \times 16 + 5 \times 5 \times 16 \times 120 + 120 \times 84 + 84 \times 10
  $$
  
- 网络全部参数量（权重+偏置）：
  $$
  5 \times 5 \times 1 \times 6 \text{(卷积核)} + 6 \text{(偏置)} + 5 \times 5 \times 6 \times 16 \text{(卷积核)} + 16 \text{(偏置)} + 5 \times 5 \times 16 \times 120 \text{(卷积核)} + 120 \text{(偏置)} \\
  + 120 \times 84 \text{(全连接权重)} + 84 \text{(偏置)} + 84 \times 10 \text{(全连接权重)} + 10 \text{(偏置)}
  $$

### 3 LeNet的浮点计算量（时间复杂度）

衡量卷积计算量的指标是 **浮点运算次数**(FLOPs, Floating Point Operations)，**一次乘法和一次加法表示一个浮点运算次数**。

#### CNN浮点计算量

CNN网络：

- 输入图像大小：$H_{in} \times W_{in} \times n_c$
- 输出图像大小：$H_{out} \times W_{out} \times K$
- 每个滤波器（卷积核）大小：$k \times k \times n_c$
- 滤波器（卷积核）个数：$K$
- 加边填充（padding）：$P$
- 卷积滑动步幅（stride）：$S$

CNN网络计算量：

- 卷积核每滑动一次的乘法浮点计算量：$k \times k \times n_c$
- 卷积核每滑动一次的加法浮点计算量：$k \times k \times n_c - 1$
- 输出单个特征图的卷积乘法浮点计算量：$(k \times k \times n_c) \times H_{out} \times W_{out}$
- 输出单个特征图的卷积加法浮点计算量：$(k \times k \times n_c - 1) \times H_{out} \times W_{out}$
- 输出 $K$ 个特征图的卷积乘法浮点计算量：$(k \times k \times n_c) \times H_{out} \times W_{out} \times K$
- 输出 $K$ 个特征图的卷积加法浮点计算量：$(k \times k \times n_c - 1) \times H_{out} \times W_{out} \times K$
- 输出单个特征图的偏置浮点加法计算量：$H_{out} \times W_{out}$
- 输出 $K$ 个特征图的偏置浮点加法计算量：$H_{out} \times W_{out} \times K$

CNN单个卷积层的**乘法**和**加法**的浮点计算量：
$$
\begin{aligned}
FLOPs &= [(k \times k \times n_c) + (k \times k \times n_c - 1) + 1] \times H_{out} \times W_{out} \times K \\ 
&= 2 \times k \times k \times n_c \times H_{out} \times W_{out} \times K
\end{aligned}
$$
在计算机视觉论文中，常常将一个 **'乘-加'** 组合视为一次浮点运算，英文表述为 **'Multi-Add'**，运算量正好是上面的算法减半，此时的运算量为：
$$
FLOPs =  k \times k \times n_c \times H_{out} \times W_{out} \times K
$$

#### 全连接层的参数量和浮点计算量

$N_{in}$ 表示输入层神经元个数，$N_{out}$ 表示输出层神经元个数。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530211641.png" style="zoom:50%;" />

单层全连接层的网络模型**参数量**（权重+偏置）： 
$$
parameters = (N_{in} + 1) \times N_{out}
$$
单个全连接层的乘法和加法**浮点计算量**（权重+偏置）：
$$
FLOPs = [N_{in} + (N_{in} - 1) + 1] \times N_{out} = 2 \times N_{in} \times N_{out}
$$

> 上述公式中第一个 $N_{in}$ 表示乘法运算量，$N_{in} - 1$ 表示加法运算量，+1 表示 $N_{out}$ 个偏置项计算量，$\times N_{out}$ 表示计算 $N_{out}$ 个神经元的值。

如果将一个 **‘乘-加’** 组合视为一次浮点运算，则此时单个全连接层的**浮点运算量**为：
$$
FLOPs = N_{in} \times N_{out}
$$



## II. AlexNet

### 1 AlexNet 网络架构

5个卷积层 + 3个全连接层

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530212618.png" style="zoom: 67%;" />

### 2 AlexNet 网络架构细节

1. **Input** 输入图像为227\*227\*3。

2. **Conv1** 经过(11\*11\*3)\*96卷积核，stride=4，(227-11)/4+1=55，生成feature map为55\*55\*96。

3. **Pool1** 经过3\*3的池化核，stride=2，(55-3)/2+1=27，生成feature map为27\*27\*96。

4. **Norm1** local_size=5，生成feature map为27\*27\*96。

5. **Conv2** 经过(5\*5\*96)\*256的卷积核，pad=2，group=2，(27+2\*2-5)/1+1=27，生成feature map为27\*27\*256。

6. **Pool2** 经过3\*3的池化核，stride=2，(27-3)/2+1=13，生成feature map为13\*13\*256。

7. **Norm2** local_size=5，生成feature map为13\*13\*256。

8. **Conv3** 经过(3\*3\*256)\*384卷积核，pad=1，(13+1\*2-3)/1+1=13，生成feature map为13\*13\*384。

9. **Conv4** 经过(3\*3\*384)\*384卷积核，pad=1，(13+1\*2-3)/1+1=13，生成feature map为13\*13\*384。

10. **Conv5** 经过(3\*3\*384)\*256卷积核，pad=1，(13+1\*2-3)/1+1=13，生成feature map为13\*13\*256。

11. **Pool5** 经过(3\*3)的池化核，stride=2，(13-3)/2+1=6，生成feature map为6\*6\*256。

12. **Fc6** 输入为(6\*6\*256)\*4096全连接，生成feature map为1\*1\*4096。

13. **Dropout6** 在训练的时候以1/2概率使得隐层的某些神经元的输出为0，这样就丢掉了一半节点的输出，BP的时候也不更新这些节点。以下Dropout同理。

14. **Fc7** 输入为1\*1\*4096，输出为1\*1\*4096，总参数量为4096\*4096。

15. **Norm7** 生成feature map为1\*1\*4096。

16. **Fc8** 输入为1\*1\*4096，输出为1000，总参数量为4096\*1000。

### 2 关于AlexNet网络的总结

1. **网络比LeNet更深**，包括5个卷积层和3个全连接层。

2. **隐层使用ReLU激活函数**，收敛很快，解决了Sigmoid在网络较深时出现的梯度消失问题。

3. **加入了Dropout层**，防止过拟合。

4. **使用了LRN归一化层**，对局部神经元的活动创建竞争机制，抑制反应较小的神经元，放大反应大的神经元，增强了模型的泛化能力。

5. **使用裁剪翻转等操作做数据增强**，增强了模型的泛化能力。预测时使用提取图片四个角加中间五个位置并进行左右翻转一共十幅图片的方法求取平均值，这也是后面刷比赛的基本使用技巧。

6. **分块训练**，当年的GPU没有这么强大，AlexNet创新地将图像分为上下两块分别训练，然后在全连接层合并在一起。

7. **总体的参数数量大概为240M**。



## III. ZFNet

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530214805.png"/>

### 网络设计思想

- 使用新颖的可视化技术来一窥中间特征层的功能，以及分类的操作针对可视化的结果，来调整网络结构。
- 可视化是通过反卷积完成的
- 可视化发现的结果：
  - 通过可视化发现AlexNet第一层中有大量的高频（边缘）和低频（非边缘）信息的混合，却几乎没有覆盖到中间的频率信息；
  - 由于第一层卷积用的步长为4，太大，导致了有非常多的混 叠情况，学到的特征不是特别好看，不像是后面的特征能看到一些纹理、颜色等

- 解决：
  - 改变AlexNet的第一层滤波器的大小，由11×11变成7×7
  - 将卷积核移动的步长4变成了2 

### 总结

- 使用更小的卷积核，更小的滑动步长
- 将AlexNet第一层卷积核由11变成7，滑动步长由4变为2



## IV. VGGNet

### VGG16 结构图

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530215209.png" style="zoom:50%;" />

### VGGNet网络架构流程描述

1. 输入224\*224\*3的图片，经64个3\*3的卷积核作两次卷积+ReLU，卷积后的尺寸变为224\*224\*64

2. 作max pooling（最大池化），池化单元尺寸为2\*2（效果为图像尺寸减半），池化后的尺寸变为112\*112\*64

3. 经128个3\*3的卷积核作两次卷积+ReLU，尺寸变为112\*112\*128

4. 作2\*2的max pooling池化，尺寸变为56\*56\*128

5. 经256个3\*3的卷积核作三次卷积+ReLU，尺寸变为56\*56\*256

6. 作2\*2的max pooling池化，尺寸变为28\*28\*256

7. 经512个3\*3的卷积核作三次卷积+ReLU，尺寸变为28\*28\*512

8. 作2\*2的max pooling池化，尺寸变为14\*14\*512

9. 经512个3\*3的卷积核作三次卷积+ReLU，尺寸变为14\*14\*512

10. 作2\*2的max pooling池化，尺寸变为7\*7\*512

11. 与两层1\*1\*4096，一层1\*1\*1000进行全连接+ReLU（共三层）

12. 通过softmax输出1000个预测结果

### VGG16 细节

- 网络架构由**块结构**构成
- 每个小块内部多个连续卷积的操作可以起到和一个大的卷积核同样的作用效果

三次连续3×3卷积的效果等价于一次7×7卷积：

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530215546.png" style="zoom:50%;" />

#### 多个3×3卷积层堆叠的优势

2个3\*3的卷积层级联（叠加）相当于1个5\*5的卷积层，即一个像素会与周围5\*5的像素产生关联，可以说感受野大小为5\*5。

3个3\*3的卷积层相当于1个7\*7的卷积层。

- **更少的参数**：两个3\*3的卷积层的参数比1个 5\*5 的更少，前者为2\*3\*3=18，后者为1\*5\*5=25。
- **更多的非线性变换**：2个3\*3的卷积层比1个5\*5的卷积层有更多的非线性变换 (前者可使用2次ReLU函数，后者只有1次)，这使得CNN对特征的学习能力更强。



## V. GoogLeNet

### 1 Inception

Inception的含义：引入 Inception module 使得网络**深度(depth)更深**，但深度网络在训练时**依然可以很好的收敛**。

#### 原始版本

具有不同感受野大小和操作的并行路径旨在堆积的特征图中捕获稀疏相关模式

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530220238.png" style="zoom: 25%;" />

#### 改进版本

在高计算代价的卷积之前，**使用1x1卷积降低通道维数**

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530220327.png" style="zoom:25%;" />

通过多个大小的卷积核提取图像不同尺度的信息，最后进行融合(通道拼接)，以得到图像更好的表征。

**池化部分加边**：使得池化后保持特征图的高和宽与输入**保持不变**。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530220755.png" style="zoom: 67%;" />

### 2 Inception 模块架构

- 特征图后一共有四条分支
- 其中三条先经过1×1 核的压缩，这样做的意义主要是为了**控制输出通道的深度**，并同时能**增加模型的非线性性**
- 一条则是先通过3×3 池化核，而为了确保输出特征图在长宽上拥有一样尺寸，我们就要借用填充技巧
- 1×1 核输出大小与输入相同，而3×3、5×5 核则分别设定填充值为1、2。

### 3 Inception网络引入瓶颈层

目标是将特征图由 28x28x192→ 28x28x32

左图为原方案，有图为加入瓶颈层的Inception。

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530221258.png" style="zoom:67%;" />

- 应用上述左端架构的问题是浮点**计算代价高**。

  例如，查看5x5卷积核的计算代价，我们得到：32个卷积核，每个卷积核大小为5x5x192。 输出大小为28x28x32。因此，它计算的乘法浮点计算量为：

  $(5 * 5 * 192)*(28 * 28 * 32) = 1.2亿$

- 引入瓶颈层后的乘法浮点计算量：

  <img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530221941.png" style="zoom:40%;" />

  $(1 *1 * 192)*(28*28 *16) + (5*5*16)*(28*28*32)= 1240万$

插入的1x1卷积将浮点计算量减少为单个5*5卷积总计算代价的 **1/10** 。

### 4 GoogLeNet 架构

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530221838.png" style="zoom: 40%;" />



## VI. ResNet

### 1 残差网络原理

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530222412.png" style="zoom: 67%;" />

- **跳转连接**是跳过一层或多层的连接。在我们的情况下，跳转连接仅执行恒等映射，并将它们的输出添加到堆叠层的输出中。

- **恒等跳转连接**既不会增加额外的参数，也不会增加计算复杂性。整个网络仍然可以通过SGD反向传播进行端到端训练，并且可以

  使用公共库轻松实现，而无需修改求解方式。

### 2 Identity Mapping ：跳转，跳层捷径，捷径

#### 1) 残差块输入和输出维数不变

当输入和输出具有相同的维度时，可以直接使用恒等跳转连接（x）。
$$
\mathbf{y} = \mathcal{F}(\mathbf{x}, \{W_i\}) + \mathbf{x}
$$


#### 2) 残差块输入和输出维数改变（空间、维度）

**a. 空间上不一致**

只需要在跳接的部分给输入 $\mathbf{x}$ 加上一个线性映射
$$
\mathbf{y} = \mathcal{F}(\mathbf{x}, \{W_i\}) + W_s \mathbf{x}
$$
**b. 深度上不一致**

两种解决办法：

- 一种是在跳接过程中**加一个1×1的卷积层进行升维**
- 另一种则是直接简单粗暴地**补零**。

### 3 ResNet结构

<img src="https://raw.githubusercontent.com/abecedarian007/picgo_images/master/img/20240530223743.png" style="zoom: 67%;" />





# E. 迁移学习 Transfer Learning

**迁移学习**是将现有训练有素的机器学习模型应用于新的但相关的问题的过程。

**迁移学习的动机**：

- 在大的数据集上训练大型网络花费很长时间，如ImageNet
- 大的训练数据集并不是总是可以获得，标记的代价也将昂贵和费时

**使用与新任务相关的数据训练新层**：

1. **对整个网络进行微调 (fine-tuning)**

2. **将网络的原始部分用作特征提取器，并仅训练新添加的层**
