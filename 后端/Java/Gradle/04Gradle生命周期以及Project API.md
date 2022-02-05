# Gradle组成部分

![](image/image-20220130222421436.png)

![](image/image-20220130222427400.png)

# 生命周期

![](image/image-20220130222722781.png)

![](image/image-20220130223524052.png)

![](image/image-20220130223732723.png)

# 任务关系

![image-20220130224021869](image/image-20220130224021869.png)

# Gradle Project讲解

每个 Project 都要有自己的 build.gradle

根 Project 的作用就是管理子 Project，使用对应的 API 来进行管理

![](image/image-20220130225244097.png)

- Project 相关 API 就是管理父和子 Project
- task 相关 AP I就是为我们当前的 Project 定义 task 和使用 task
- 属性相关 API 为 Project 添加额外属性的能力
- file相关 API  为 Project 提供文件处理功能
- 生命周期 API ，在对应的时间触发对应的函数
- 其他 APi 添加依赖，引入外部 project

## 相关API讲解

只要是执行 Gradle 中的任何命令，都会执行Project的配置代码

![](image/image-20220130230200820.png)

![](image/image-20220130230519561.png)

![](image/image-20220130230743596.png)

![](image/image-20220130230834174.png)

## 管理相应的 Project

![](image/image-20220130231142373.png)

### Project API

![](image/image-20220130231503189.png)

![](image/image-20220130231654386.png)

![](image/image-20220130232402634.png)

![](image/image-20220130234343638.png)

![](image/image-20220130234535876.png)

### 属性 API

![](image/image-20220130235104121.png)

![](image/image-20220130235550160.png)

![](image/image-20220131000141964.png)

### 可以分出一个新文件来扩展属性

![](image/image-20220131001305706.png)

### 通过这句话引入对应的文件

![](image/image-20220131001328950.png)

### 通过gradle.properties来添加 

![](image/image-20220131001903730.png)

### 这样就能手动控制 Project 导入

![](image/image-20220131001934337.png)

## 文件 API

### Gradle 简化了文件操作，都是基于当前 Project 的根目录开始，无法与系统的文件系统进行交互

![](image/image-20220131002204439.png)

### 拿到 Project 路径

![](image/image-20220131002533350.png)

### 得到文件内容

![](image/image-20220131002801838.png)

### 拷贝文件

![](image/image-20220131002957774.png)

![](image/image-20220131003159901.png)

![](image/image-20220131003443072.png)

## 依赖相关

### compile 打包还在

### provided 打包不会引入

![](image/image-20220131004121702.png)

## 其他 API

## 执行外部命令

### 我们写脚本会不可避免的遇到使用系统命令，所以需要执行外部命令

![](image/image-20220131004843530.png)