# MySQL8.0 新特性

## 窗口函数（Window Function）

![](image/Pasted%20image%2020220310164522.png)

```mysql
 SELECT
	*,
	RANK() OVER (PARTITION BY customer_id ORDER BY amount DESC) AS ranking
FROM
	payment
```

## 隐藏索引

![](image/Pasted%20image%2020220310165118.png)

## 降序索引

![](image/Pasted%20image%2020220310165252.png)

## 通用表表达式（Common Table Expression CTE）

![](image/Pasted%20image%2020220310165551.png)

## UTF-8 编码

![](image/Pasted%20image%2020220310165748.png)

## DDL 事务

![](image/Pasted%20image%2020220310165902.png)

## InnoDB Cluster

![](image/Pasted%20image%2020220310191801.png)

# Percona XtraDB Cluster

![](image/Pasted%20image%2020220310192222.png)

# 数据库有哪些类型

## 按用途分类

![](image/Pasted%20image%2020220310193146.png)

### OLTP

![](image/Pasted%20image%2020220310193324.png)

### OLAP

![](image/Pasted%20image%2020220310193535.png)

### HTAP

![](image/Pasted%20image%2020220310193822.png)

## 按储存形式分类

![](image/Pasted%20image%2020220310193902.png)

![](image/Pasted%20image%2020220310193932.png)

## 按架构分类

![](image/Pasted%20image%2020220310194235.png)

### Shared-Everything
- 家用电脑
![](image/Pasted%20image%2020220310194748.png)

### Shared-Memory
- 超级计算机
![](image/Pasted%20image%2020220310194831.png)

### Shared-Disk
- 网吧
- 阿里的数据库
![](image/Pasted%20image%2020220310194915.png)

### Shared-Notthing
- 数据库集群

![](image/Pasted%20image%2020220310195058.png)

## 总结

![](image/Pasted%20image%2020220310195132.png)

# 谁是单体数据库之王

## PostgreSQL

![](image/Pasted%20image%2020220310195236.png)


![](image/Pasted%20image%2020220310195431.png)

## Postgres-XL（OLTP）

![](image/Pasted%20image%2020220310195711.png)

![](image/Pasted%20image%2020220310195858.png)

## GreenPlum（OLAP）

![](image/Pasted%20image%2020220310200133.png)

# 总结

![](image/Pasted%20image%2020220310200230.png)

# MySQL能魔改成什么样

![](image/Pasted%20image%2020220310200430.png)

## 日志传送VS共享存储

![](image/Pasted%20image%2020220310200950.png)

## 备库如何查询数据

![](image/Pasted%20image%2020220310201156.png)

## 总结

![](image/Pasted%20image%2020220310201531.png)

# 谁在支撑双11

## OceanBase

![](image/Pasted%20image%2020220310201704.png)

![](image/Pasted%20image%2020220310201948.png)

# 谁是国产数据库最闪亮的星

## TiDB 简介

![](image/Pasted%20image%2020220310202335.png)

## TiDB

![](image/Pasted%20image%2020220310202400.png)

![](image/Pasted%20image%2020220310202613.png)

![](image/Pasted%20image%2020220310202827.png)

# 打不死的小强CockroachDB

![](image/Pasted%20image%2020220310203005.png)

![](image/Pasted%20image%2020220310203030.png)

![](image/Pasted%20image%2020220310203016.png)

![](image/Pasted%20image%2020220310203153.png)

# 本章小结

## MySQL8.0 新特性

![](image/Pasted%20image%2020220310203237.png)

![](image/Pasted%20image%2020220310203250.png)

## 数据库分类

![](image/Pasted%20image%2020220310203311.png)

## PostgreSQL

![](image/Pasted%20image%2020220310203349.png)

## PolarDB

 ![](image/Pasted%20image%2020220310203410.png)
## OceanBase

![](image/Pasted%20image%2020220310203443.png)

## TiDB

![](image/Pasted%20image%2020220310203506.png)

## CockroachDB

![](image/Pasted%20image%2020220310203625.png)




