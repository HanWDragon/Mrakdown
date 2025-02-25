# 三个问题

![](image/Pasted%20image%2020250131070005.png)

- 2 倍 CPU 核心数，调用 execute 方法
- 计算阻塞时间，出问题创建新的 selector
- 让本线程执行，外部线程请求就封装成任务

# 创建

![](image/Pasted%20image%2020250131070835.png)

## ThreadPreTaskExecutor

![](image/Pasted%20image%2020250131071104.png)

## newChild

![](image/Pasted%20image%2020250131071612.png)

## chooseFactory

- 给新连接绑定 NioEventLoop

![](image/Pasted%20image%2020250131072229.png)

![](image/Pasted%20image%2020250131072317.png)

![](image/Pasted%20image%2020250131072548.png)

# 启动

![](image/Pasted%20image%2020250131074627.png)

![](image/Pasted%20image%2020250131074733.png)

# 执行逻辑

![](image/Pasted%20image%2020250131075250.png)

![](image/Pasted%20image%2020250131075319.png)

## select

### 执行逻辑

![](image/Pasted%20image%2020250131080846.png)

## ProcessSelectedKey

### 执行逻辑

![](image/Pasted%20image%2020250131082400.png)

## runAllTasks

### 执行逻辑

![](image/Pasted%20image%2020250131083604.png)