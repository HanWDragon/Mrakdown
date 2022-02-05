# Task定义和配置

<img src="image/image-20220131175513863.png" alt="image-20220131175513863" style="zoom:50%;" />

<img src="image/image-20220131175924721.png" alt="image-20220131175924721" style="zoom:50%;" />

## 配置组名和描述信息

<img src="image/image-20220201135909027.png" alt="image-20220201135909027" style="zoom:50%;" />

# Task的执行讲解

<img src="image/image-20220201140724981.png" alt="image-20220201140724981" style="zoom:50%;" />

先执行外部的 doFrist 再来执行内部的 doFirst 

只有在 task 中的 doFirst 和 doLast 中的代码会执行在 Gradle 中的执行周期

<img src="image/image-20220201140750506.png" alt="image-20220201140750506" style="zoom:50%;" />

通过 doFirst 可以在执行 task 之前执行一些逻辑

doLast 同理

![image-20220201141647056](image/image-20220201141647056.png)

可以通过task管理来关闭一些测试task来加快编译速度

我是如何知道有哪些task，可以查看控制台打印的task执行名称

# Task的依赖和执行顺序

<img src="image/image-20220201142408877.png" alt="image-20220201142408877" style="zoom:50%;" />

<img src="image/image-20220201142532233.png" alt="image-20220201142532233" style="zoom:50%;" />

<img src="image/image-20220201142553893.png" alt="image-20220201142553893" style="zoom:50%;" />

配置相关依赖

<img src="image/image-20220201142636854.png" alt="image-20220201142636854" style="zoom:50%;" />

<img src="image/image-20220201142802301.png" alt="image-20220201142802301" style="zoom:50%;" />

相应的依赖关系

![image-20220201142901660](image/image-20220201142901660.png)

动态的指定相关依赖

<img src="image/image-20220201143058781.png" alt="image-20220201143058781" style="zoom:50%;" />

看到 << 等同于 doLast

<img src="image/image-20220201165051288.png" alt="image-20220201165051288" style="zoom:50%;" />

<img src="image/image-20220201165030320.png" alt="image-20220201165030320" style="zoom:50%;" />

## Task输入输出

<img src="image/image-20220201160704963.png" alt="image-20220201160704963" style="zoom:50%;" />

<img src="image/image-20220201164726426.png" alt="image-20220201164726426" style="zoom:50%;" />

![image-20220201164952821](image/image-20220201164952821.png)

<img src="image/image-20220201202322510.png" alt="image-20220201202322510" style="zoom:50%;" />

# Task类型

https://docs.gradle.org/current/dsl/org.gradle.api.plugins.antlr.AntlrTask.html

<img src="image/image-20220201212759039.png" alt="image-20220201212759039" style="zoom:50%;" />

# 挂接到生命周期

记得分文件写完Task后记得引入文件要不然不会解析

<img src="image/image-20220201211628605.png" alt="image-20220201211628605" style="zoom:50%;" />

挂接到生命周期

<img src="image/image-20220201204253247.png" alt="image-20220201204253247" style="zoom:50%;" />



# Task实战

 