# 04 软件体系结构描述方法

## I. 软件体系结构描述

描述软件体系结构是**理解**体系结构设计思想、**交流**如何使用体系结构指导系统构建的基础。

### 原则

1. 从读者的角度写
2. 避免不必要的重复
3. 避免歧义
4. 使用标准组织结构
5. 记录理由
6. 保持文档时效性但不是频繁更新（有限的稳定性）
7. 审查文档是否符合需求







## II. 软件体系结构建模

### 视图

#### 概念

- **架构元素**：软件或硬件中存在的一组实际元素
- **视图**：由系统相关者编写和读取的一组连贯的架构元素的表示
- 视图是一组架构元素及其关联关系的表示，但并非涵盖所有架构元素。
- 视图绑定了体系结构描述时感兴趣的元素类型和关系类型，并显示了它们。
- 视图是一种复杂的管理方法。
- 每个视图都可以回答有关体系结构的不同问题。

#### 视图的类型

- 分解视图：显示与“关联的子模块”关系相关联的模块
- 使用视图：显示与“使用”关系相关联的模块
- 分层视图：显示被划分为相关和连贯功能的模块组。
- 类/泛化视图：显示称为类的模块，这些模块通过关系的“继承”或“实例”关联
- 进程视图：显示通过通信、同步和排除操作连接的进程或线程
- 并发视图：显示组件和连接器，其中连接器代表“逻辑线程”
- 共享数据（存储库）视图：显示创建、存储和访问持久数据的组件和连接器
- 客户端-服务器视图：显示协作的客户端和服务器以及它们之间的连接器（即它们共享的协议和消息）
- 部署视图：显示软件元素及其对硬件和通信元素的分配
- 实施视图：显示开发、集成和配置控制环境中的软件元素及其到文件结构的映射
- 工作分配视图：显示模块及其如何分配给负责实施和集成它们的开发团队

#### 基于视图的体系结构建模规范  -- “4+1 view”

- **逻辑视图 Logical View**：**支持行为要求**。 关键抽象，是对象或对象类。
  - 描述系统各部分的抽象描述。用于建模系统的组成部分以及各组成部分之间的交互方式。
  - 通常包*括<u>类图，对象图，状态图和协作图</u>*。
- **过程视图 Process View**：解决**并发**和**分发**。 将线程映射到对象
  - 描述系统中的进程。 当可视化系统中一定会发生的事情时，此视图特别有用。
  - 该视图通常包含<u>*活动图*</u>。
- **开发视图 Development View**：**组织**软件模块，库，子系统，开发单元。
  - 描述系统的各部分如何被组织为模块和组件。管理系统体系结构中的层非常有用。
  - 该视图通常包含*<u>包图和组件图</u>*。
- **物理视图 Physical View**：将其他元素映射到**处理**和**通信节点**。
  - 描述如何将前三个视图中所述的系统设计实现为一组现实世界的实体。该视图中的图表展示了抽象部分如何映射到最终部署的系统中。
  - 该视图通常包含*<u>部署图</u>*。
- **用例视图（场景）Scenarios**：将其他视图映射到重要的**用例**（这些用例被称作场景）上对体系结构加以说明，它们构成了第5个视图。
  - 从外部世界的角度描述正在建模的系统的功能。
  - 需要使用此视图来描述系统应该执行的操作。 所有其他视图都依靠用例视图（场景）来指导它们，这就是将模型称为4 + 1的原因。
  - 该视图通常包含用<u>*例图，描述和概述图*</u>。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612171457.png" style="zoom:67%;" />

### UML

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173651.png" style="zoom: 50%;" />



#### 用例图 Use Case

用例是帮助**理解系统功能需求**的宝贵工具，是系统提供的功能的描述。
用例代表了**系统的外部视图**，不要期望用例与系统内部的类之间存在任何关联。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612172928.png" style="zoom:80%;" />

#### 类图 Class Diagram

类图表示系统中的类和类与类之间的关系，它是对**系统静态结构**的描述。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173151.png" style="zoom:67%;" />

#### 对象图 Object Diagram

对象图是某个时间点系统中对象的快照，因为它显示的是实例而不是类，所以通常称为**实例图**。
对象图对于**显示连接在一起的对象的示例**很有用。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173351.png" style="zoom:80%;" /><img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173501.png" style="zoom:80%;" />

#### 状态图 State Diagram

状态图是描述类的对象所有可能的**状态**以及事件发生时**状态的转移条件**。通常，状态图是<u>对类图的补充</u>。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173450.png" style="zoom:67%;" />

#### 协作（通信）图 Communication Diagram

协作图是一种交互图，强调的是**发送和接收消息的对象之间的组织结构**。
一个协作图显示了一系列的对象及对象之间的**联系**以及对象间发送和接收的**消息**。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173823.png" style="zoom:67%;" />

#### 序列图 Sequence Diagram

软件工程中，序列图是**对象交互**的一种表现方式。主要用于按照交互发生的一系列顺序，显示对象之间的这些交互。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612173938.png" style="zoom:80%;" />

#### 活动图 Activity Diagram

描述**满足用例要求**所要进行的**活动**以及**活动间**的**约束关系**，有利于识别**并行活动**。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174004.png" style="zoom: 67%;" />

#### 包图 Package Diagram

包是在UML中用类似于文件夹的符号表示的**模型元素的组合**，允许从UML中获取任何结构，并将其元素分组到更高级别的单元中。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174052.png" style="zoom:80%;" />

#### 组件图 Component Diagram

组件图描述**代码构件**的**物理结构**及**各构件之间**的**依赖关系**。将系统划分为组件并希望通过接口或组件细分为较低级别的结构来显示其相互关系。

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174233.png" style="zoom:67%;" />

#### 部署图 Deployment Diagram

部署图定义系统中**软硬件的物理体系结构**。描述了一个运行时的硬件结点，以及在这些结点上运行的软件组件的静态视图。 显示了系统的硬件，安装在硬件上的软件，以及用于连接异构的机器之间的中间件。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174227.png" style="zoom: 80%;" />

#### 复合结构 Composite Structures

复合结构是UML 2的新增功能。即能够分层地将类**分解为内部结构**。这可以将一个复杂的对象**分解**为多个部分。

  <img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174404.png" style="zoom:80%;" /><img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174417.png" style="zoom:67%;" />

#### 交互概述图 Interaction Diagram

交互概述图是**活动图和序列图的结合**。 可以将其视为活动图，其中将活动替换为小的顺序图，或者将其视为用活动图表示法分解以显示控制流的顺序图。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174517.png" style="zoom:80%;" />

#### 时序图 Timing Diagram

时序图是交互图的另一种形式，其中重点在于**时序约束**。一般针对单个对象或多个对象描述。对显示不同对象的状态变化之间的时序约束很有用。  

<img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174638.png" style="zoom:80%;" /><img src="https://raw.githubusercontent.com/Kaiming-Y/picgo_images/master/img/20240612174654.png" style="zoom:80%;" />
