# 数据类型

## 常用数据类型及适用场景

![](image/Pasted%20image%2020241213023436.png)

## 几乎所有的数据都用 string 去存储

![](image/Pasted%20image%2020241213022714.png)

### 弊端

![](image/Pasted%20image%2020241213022827.png)

## Key 的命名策略

![](image/Pasted%20image%2020241213023249.png)

# 事务

## Redis 事务

![](image/Pasted%20image%2020241213051747.png)
## 两类错误

![](image/Pasted%20image%2020241213052158.png)

## 为什么不支持回滚

![](image/Pasted%20image%2020241213052517.png)
# BigKey

![](image/Pasted%20image%2020241213052651.png)

## 如何产生

![](image/Pasted%20image%2020241213052835.png)
## 如何发现

![](image/Pasted%20image%2020241213052948.png)

## 动 BigKey，想好再删

![](image/Pasted%20image%2020241213053238.png)

# 内存耗尽

![](image/Pasted%20image%2020241213053422.png)

## 设置过期时间

![](image/Pasted%20image%2020241213053533.png)

## 过期删除策略

![](image/Pasted%20image%2020241213053910.png)

## 设置过期还是 OOM

![](image/Pasted%20image%2020241213054103.png)

## 内存淘汰策略

![](image/Pasted%20image%2020241213054130.png)

![](image/Pasted%20image%2020241213054400.png)

# 频繁请求造成性能瓶颈

## 交互模型

### CS

![](image/Pasted%20image%2020241213054535.png)

## pipeline

![](image/Pasted%20image%2020241213054653.png)

## pipeline 和 原生批量命令对比

![](image/Pasted%20image%2020241213055224.png)

## 使用 pipeline 注意事项

![](image/Pasted%20image%2020241213055339.png)

# 持久化

![](image/Pasted%20image%2020241213055447.png)
## RDB 持久化配置选项

![](image/Pasted%20image%2020241213055543.png)

## 触发原理

![](image/Pasted%20image%2020241213055805.png)

![](image/Pasted%20image%2020241213055823.png)

## AOF 持久化配置选项

![](image/Pasted%20image%2020241213055919.png)

## AOF 重写

![](image/Pasted%20image%2020241213060120.png)

## 从持久化中恢复

![](image/Pasted%20image%2020241213060325.png)
## 企业使用策略

![](image/Pasted%20image%2020241213060438.png)

# 缓存

## 通用架构存取方案

![](image/Pasted%20image%2020241213060653.png)

## 缓存穿透

### 含义和影响

![](image/Pasted%20image%2020241213060747.png)

### 如何解决

![](image/Pasted%20image%2020241213060831.png)


## 缓存雪崩

![](image/Pasted%20image%2020241213061147.png)
## 影响

![](image/Pasted%20image%2020241213061234.png)

## 解决

![](image/Pasted%20image%2020241213061254.png)

