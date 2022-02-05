# 前提

<img src="image/image-20220130002832495.png" alt="image-20220130002832495" style="zoom:50%;" />

入口类的编写

<img src="image/image-20220202101305250.png" alt="image-20220202101305250" style="zoom:50%;" />

<img src="image/image-20220202103640970.png" alt="image-20220202103640970" style="zoom:50%;" />

<img src="image/image-20220202103726295.png" alt="image-20220202103726295" style="zoom:50%;" />

<img src="image/image-20220202103857159.png" alt="image-20220202103857159" style="zoom:50%;" />

<img src="image/image-20220202103945912.png" alt="image-20220202103945912" style="zoom:50%;" />

Class 类用来描述类的信息，BeanDefinition用来描述类的信息

​	<img src="image/image-20220202104043881.png" alt="image-20220202104043881" style="zoom:50%;" />

<img src="image/image-20220202104117698.png" alt="image-20220202104117698" style="zoom:50%;" />	相关配置

<img src="image/image-20220202104220469.png" alt="image-20220202104220469" style="zoom:50%;" />

<img src="image/image-20220202104502240.png" alt="image-20220202104502240" style="zoom:50%;" />

 <img src="image/image-20220202104702846.png" alt="image-20220202104702846" style="zoom:50%;" />

相关的类图

在Spring 2.5 后 GenericBeanDefinition 替代了 RootBeanDefinition、ChildBeanDefinition，通过setParentName 来设置关系

<img src="image/image-20220202104745320.png" alt="image-20220202104745320" style="zoom:50%;" />

# 容器

所有的 IOC 容器都需要实现接口 BeanFactory

<img src="image/image-20220202204826035.png" alt="image-20220202204826035" style="zoom:50%;" />

有时候会问 BeanFactory 和 FactoryBean 的区别

BeanFactory ：定义了 IOC 容器要实现的方法	

FactoryBean ：同样也是接口，用来定义生成普通 Bean 的方法

<img src="image/image-20220202205405575.png" alt="image-20220202205405575" style="zoom:50%;" />

<img src="image/image-20220202205335557.png" alt="image-20220202205335557" style="zoom:50%;" />

<img src="image/image-20220202205440837.png" alt="image-20220202205440837" style="zoom:50%;" />

<img src="image/image-20220202205718936.png" alt="image-20220202205718936" style="zoom:50%;" />

通过这种方式就可以得到对应的工厂生成的对象，但是需要加入对应的分割符号

<img src="image/image-20220202205824767.png" alt="image-20220202205824767" style="zoom:50%;" />

## BeanFactory中的方法

<img src="image/image-20220202210017161.png" alt="image-20220202210017161" style="zoom:50%;" />

<img src="image/image-20220202210053480.png" alt="image-20220202210053480" style="zoom:50%;" />

<img src="image/image-20220202210120905.png" alt="image-20220202210120905" style="zoom:50%;" />

<img src="image/image-20220202210138775.png" alt="image-20220202210138775" style="zoom:50%;" />

<img src="image/image-20220202210153032.png" alt="image-20220202210153032" style="zoom:50%;" />

<img src="image/image-20220202210203211.png" alt="image-20220202210203211" style="zoom:50%;" />

### 设置别名

<img src="image/image-20220202210222578.png" alt="image-20220202210222578" style="zoom:50%;" />

## 架构体系

![image-20220202210312135](image/image-20220202210312135.png)

 **Spring 的容器设计可以分为两个部分，一个是简单容器，一个是高级容器**

**简单容器是以BeanFactory为主**

**高级容器以 ApplicationContext为主，简化了一些开发流程**

## 高级容器

高级容器通常被称为上下文，所以听到上下文其实就是一种容器，容纳了开发者需要的数据

如果将 Spring容器比作一辆汽车，BeanFactory就是发动机，而 ApplicationContext 就是汽车操纵台

![image-20220202210544645](image/image-20220202210544645.png)

<img src="image/image-20220202215822363.png" alt="image-20220202215822363" style="zoom:50%;" />

<img src="image/image-20220202215903496.png" alt="image-20220202215903496" style="zoom:50%;" />

<img src="image/image-20220202215947361.png" alt="image-20220202215947361" style="zoom:50%;" />

### 当我们看到 ApplicationContext 你会发现并没有相应的设置方法，全是读取相关的信息

<img src="image/image-20220202220213047.png" alt="image-20220202220213047" style="zoom:50%;" />

### 但是我们在实际编程的时候是可以设置相关内容的，于是我们需要其他的接口来扩展 ApplicationContext 的方法

<img src="image/image-20220202220525641.png" alt="image-20220202220525641" style="zoom:50%;" />

### 来到configurableApplicationContext

<img src="image/image-20220202220554617.png" alt="image-20220202220554617" style="zoom:50%;" />

### 后面的接口或者抽象类，可以自己去阅读

<img src="image/image-20220202221333817.png" alt="image-20220202221333817" style="zoom:50%;" />

<img src="image/image-20220202221350733.png" alt="image-20220202221350733" style="zoom:50%;" />

<img src="image/image-20220202221439808.png" alt="image-20220202221439808" style="zoom:50%;" />

在 AbstractApplicationContext 中的抽象类在 refresh 方法就使用了模板方法

![image-20220202221820003](image/image-20220202221820003.png)

<img src="image/image-20220202221849507.png" alt="image-20220202221849507" style="zoom:50%;" />



## 简单容器接口设计中的单一职责

<img src="image/image-20220202213050977.png" alt="image-20220202213050977" style="zoom:50%;" />

以列表的方式列出Bean的信息

<img src="image/image-20220202213210143.png" alt="image-20220202213210143" style="zoom:50%;" />

<img src="image/image-20220202213325016.png" alt="image-20220202213325016" style="zoom:50%;" />

自动装配需要都在Spring管理中

<img src="image/image-20220202213436498.png" alt="image-20220202213436498" style="zoom:50%;" />

#  弄清Resource、ResourceLoader、容器之间的关系

![image-20220202223214416](image/image-20220202223214416.png)

### Spring将对应物理资源的方式抽象成 Resource 

![image-20220202224252448](image/image-20220202224252448.png)

<img src="image/image-20220202224406948.png" alt="image-20220202224406948" style="zoom:50%;" />

### 这就是 Spring 对 Resource 相关的类图，可以看到要是想实现自己的 Resource 需要定义自己的 Resource 需要继承 AbstractResource 这个类

### 我们可以在不启动Spring的情况下使用对应的Spring工具类

<img src="image/image-20220202225546649.png" alt="image-20220202225546649" style="zoom:50%;" />

![image-20220202225624866](image/image-20220202225624866.png)

<img src="image/image-20220202225638228.png" alt="image-20220202225638228" style="zoom:50%;" />

<img src="image/image-20220202225852755.png" alt="image-20220202225852755" style="zoom:50%;" />

<img src="image/image-20220202230108904.png" alt="image-20220202230108904" style="zoom:50%;" />

里面使用了策略模式和简单工厂模式

<img src="image/image-20220202231542816.png" alt="image-20220202231542816" style="zoom:50%;" />

<img src="image/image-20220202231609273.png" alt="image-20220202231609273" style="zoom:50%;" />

<img src="image/image-20220202231823557.png" alt="image-20220202231823557" style="zoom:50%;" />

<img src="image/image-20220203001414870.png" alt="image-20220203001414870" style="zoom:50%;" />

