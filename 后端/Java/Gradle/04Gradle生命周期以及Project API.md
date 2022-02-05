# Gradle组成部分

<img src="image/image-20220130222421436.png" alt="image-20220130222421436" style="zoom:50%;" />

<img src="image/image-20220130222427400.png" alt="image-20220130222427400" style="zoom:50%;" />

# 生命周期

<img src="image/image-20220130222722781.png" alt="image-20220130222722781" style="zoom:50%;" />

<img src="image/image-20220130223524052.png" alt="image-20220130223524052" style="zoom:50%;" />

<img src="image/image-20220130223732723.png" alt="image-20220130223732723" style="zoom:50%;" />

# 任务关系

![image-20220130224021869](image/image-20220130224021869.png)

# Gradle Project讲解

每个 Project 都要有自己的 build.gradle

根 Project 的作用就是管理子 Project，使用对应的 API 来进行管理

<img src="image/image-20220130225244097.png" alt="image-20220130225244097" style="zoom:50%;" />

- Project 相关 API 就是管理父和子 Project
- task 相关 AP I就是为我们当前的 Project 定义 task 和使用 task
- 属性相关 API 为 Project 添加额外属性的能力
- file相关 API  为 Project 提供文件处理功能
- 生命周期 API ，在对应的时间触发对应的函数
- 其他 APi 添加依赖，引入外部 project

## 相关API讲解

只要是执行 Gradle 中的任何命令，都会执行Project的配置代码

<img src="image/image-20220130230200820.png" alt="image-20220130230200820" style="zoom:50%;" />

<img src="image/image-20220130230519561.png" alt="image-20220130230519561" style="zoom:50%;" />

<img src="image/image-20220130230743596.png" alt="image-20220130230743596" style="zoom:50%;" />

<img src="image/image-20220130230834174.png" alt="image-20220130230834174" style="zoom:50%;" />

## 管理相应的 Project

<img src="image/image-20220130231142373.png" alt="image-20220130231142373" style="zoom:50%;" />

### Project API

<img src="image/image-20220130231503189.png" alt="image-20220130231503189" style="zoom:50%;" />

<img src="image/image-20220130231654386.png" alt="image-20220130231654386" style="zoom:50%;" />

<img src="image/image-20220130232402634.png" alt="image-20220130232402634" style="zoom:50%;" />

<img src="image/image-20220130234343638.png" alt="image-20220130234343638" style="zoom:50%;" />

<img src="image/image-20220130234535876.png" alt="image-20220130234535876" style="zoom:50%;" />

### 属性 API

<img src="image/image-20220130235104121.png" alt="image-20220130235104121" style="zoom:50%;" />

<img src="image/image-20220130235550160.png" alt="image-20220130235550160" style="zoom:50%;" />

<img src="image/image-20220131000141964.png" alt="image-20220131000141964" style="zoom:50%;" />

### 可以分出一个新文件来扩展属性

<img src="image/image-20220131001305706.png" alt="image-20220131001305706" style="zoom:50%;" />

### 通过这句话引入对应的文件

<img src="image/image-20220131001328950.png" alt="image-20220131001328950" style="zoom:50%;" />

### 通过gradle.properties来添加 

<img src="image/image-20220131001903730.png" alt="image-20220131001903730" style="zoom:50%;" />

### 这样就能手动控制 Project 导入

<img src="image/image-20220131001934337.png" alt="image-20220131001934337" style="zoom:50%;" />

## 文件 API

### Gradle 简化了文件操作，都是基于当前 Project 的根目录开始，无法与系统的文件系统进行交互

<img src="image/image-20220131002204439.png" alt="image-20220131002204439" style="zoom:50%;" />

### 拿到 Project 路径

<img src="image/image-20220131002533350.png" alt="image-20220131002533350" style="zoom:50%;" />

### 得到文件内容

<img src="image/image-20220131002801838.png" alt="image-20220131002801838" style="zoom:50%;" />

### 拷贝文件

<img src="image/image-20220131002957774.png" alt="image-20220131002957774" style="zoom:50%;" />

<img src="image/image-20220131003159901.png" alt="image-20220131003159901" style="zoom:50%;" />

<img src="image/image-20220131003443072.png" alt="image-20220131003443072" style="zoom:50%;" />

## 依赖相关

### compile 打包还在

### provided 打包不会引入

<img src="image/image-20220131004121702.png" alt="image-20220131004121702" style="zoom:50%;" />

## 其他 API

## 执行外部命令

### 我们写脚本会不可避免的遇到使用系统命令，所以需要执行外部命令

<img src="image/image-20220131004843530.png" alt="image-20220131004843530" style="zoom:50%;" />