# Synchronized简介

## 作用

![](image/Pasted%20image%2020220207232338.png)

![](image/Pasted%20image%2020220207232453.png)

![](image/Pasted%20image%2020220207232509.png)

## 地位

![](image/Pasted%20image%2020220207233100.png)

# 两种用法

![](image/Pasted%20image%2020220207233344.png)

### 对象锁

![](image/Pasted%20image%2020220207233409.png)

## 类锁

 ![](image/Pasted%20image%2020220207235033.png)
 ![](image/Pasted%20image%2020220207235230.png)
# 常见情况

## 多线程访问同步方法的七种情况（面试常考）

### 两个线程同时访问一个对象的同步方法

简单的synchronized对象锁

### 两个线程访问的是两个对象的同步方法

`synchronized(this)`

### 两个线程访问的是synchronized的静态方法

类锁

### 同时访问同步方法与非同步方法

同时运行，做好逻辑处理就行

![](image/Pasted%20image%2020220208002112.png)

### 访问同一个对象的不同的普通同步方法

排队运行

### 同时访问同一个类静态synchronized和非静态synchronized方法

要分得清楚拿的那一把锁，两个线程同时运行

### 方法抛出异常后，会释放锁

# 性质

 ## 可重入

 ![](image/Pasted%20image%2020220208002943.png)

 ## 不可中断

 ![](image/Pasted%20image%2020220208003220.png)

 # 原理

 ## 加锁释放锁的底层原理

 ![](image/Pasted%20image%2020220208003829.png)

 反编译看字节码

![](image/Pasted%20image%2020220208004132.png)

![](image/Pasted%20image%2020220208004038.png)

## 可重入原理

![](image/Pasted%20image%2020220208004239.png)

## 保持可见性

![](image/Pasted%20image%2020220208004331.png)

 # 缺陷

 ![](image/Pasted%20image%2020220208004446.png)

 ![](image/Pasted%20image%2020220208004500.png)

# 总结

![](image/Pasted%20image%2020220208004734.png)

 # 面试题

 ![](image/Pasted%20image%2020220208004617.png)