
## IOC 容器

- 核心是 IOC 容器，理解容器是理解 Spring 的重要基础

### 为什么需要 IOC

- 解决工程中对 Object 的管理

![](image/Pasted%20image%2020241202234300.png)

![](image/Pasted%20image%2020241202234329.png)

### 核心设计：依赖注入

![](image/Pasted%20image%2020241202234500.png)

### 思考和应用

#### 使用什么数据结构来储存 Bean

- 来到 BeanDefinitionRegistry ，找到 getBeanDefinitionCount ，看到实现的接口，下面两个实现类都很相似，这里进入 Default ，发现了是 `ConcurrentHashMap`  定义是 `Map<String, BeanDefinition>`

![](image/Pasted%20image%2020241203003849.png)

![](image/Pasted%20image%2020241203003949.png)

![](image/Pasted%20image%2020241203004004.png)

#### 如何获取 Spring 容器

- 2种

![](image/Pasted%20image%2020241203010953.png)

![](image/Pasted%20image%2020241203011026.png)

#### 从这个设计得到什么启发

- 合适高效
- 学会封装

# Spring Bean

## Bean 与 IOC 的关系

![](image/Pasted%20image%2020241203011335.png)

## 生命周期

![](image/Pasted%20image%2020241203011547.png)

