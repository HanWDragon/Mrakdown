# 为什么使用Channel，而不是共享内存


## Channel 声明方法

![](image/Pasted%20image%2020250318135607.png)

## Channel 基本用法

![](image/Pasted%20image%2020250318140450.png)

## 错误示例

死锁

```go
package main  
  
import "fmt"  
  
func main() {  
    c := make(chan string, 5)  
    c <- "hello"  
    s := <-c  
    fmt.Println(s)  
}
```

修改后

```go
package main  
  
import "fmt"  
  
func main() {  
    c := make(chan string)  
  
    go func() {  
       s := <-c  
       fmt.Println(s)  
    }()  
  
    c <- "hello"  
    }
```

## 内存与通信

![](image/Pasted%20image%2020250318161521.png)

这个代码就是典型的通过共享内存来通信

```go
package main

import (
	"fmt"
	"time"
)

func watch(p *int) {
	for {
		if *p == 1 {
			fmt.Println("hello")
			break
		}
	}
}

func main() {
	i := 0
	go watch(&i)
	time.Sleep(time.Second)
	i = 1
	time.Sleep(time.Second)
}

```

可以通过管道来优化，这样就不会死循环

```go
package main

import (
	"fmt"
	"time"
)

func watch(c chan int) {
	for {
		if <-c == 1 {
			fmt.Println("hello")
			break
		}
	}
}

func main() {
	c := make(chan int)
	go watch(c)
	c <- 1
	time.Sleep(time.Second)
}
```

## 为什么使用通信来共享内存

![](image/Pasted%20image%2020250318163457.png)

# Channel 数据结构

![](image/Pasted%20image%2020250318165453.png)

![](image/Pasted%20image%2020250318165525.png)

![](image/Pasted%20image%2020250318165557.png)

## 源码

```go
type hchan struct {

	qcount   uint           // total data in the queue
	dataqsiz uint           // size of the circular queue
	buf      unsafe.Pointer // points to an array of dataqsiz elements
	elemsize uint16
	synctest bool // true if created in a synctest bubble
	closed   uint32
	timer    *timer // timer feeding this chan
	elemtype *_type // element type

	sendx    uint   // send index
	recvx    uint   // receive index
	
	recvq    waitq  // list of recv waiters
	sendq    waitq  // list of send waiters

	// lock protects all fields in hchan, as well as several
	// fields in sudogs blocked on this channel.
	//
	// Do not change another G's status while holding this lock
	// (in particular, do not ready a G), as this can deadlock
	// with stack shrinking.
	lock mutex
}
```

## 缓存区

![](image/Pasted%20image%2020250318171808.png)

## 两个队列

![](image/Pasted%20image%2020250318172021.png)

## 互斥锁

![](image/Pasted%20image%2020250318192323.png)

## 状态值

![](image/Pasted%20image%2020250318192652.png)

## 总结

![](image/Pasted%20image%2020250318192754.png)

# Channel 发送数据原理

## c <- 关键字

![](image/Pasted%20image%2020250318193439.png)

## Channel 发送的情况

对应 chansend 方法的三种情况

### 直接发送

#### 原理

![](image/Pasted%20image%2020250318194237.png)

![](image/Pasted%20image%2020250318194257.png)

#### 实现

![](image/Pasted%20image%2020250318195004.png)

### 放入缓存

#### 原理

![](image/Pasted%20image%2020250318200356.png)

#### 实现

![](image/Pasted%20image%2020250318200421.png)

### 休眠等待

#### 原理

![](image/Pasted%20image%2020250318202434.png)

#### 实现

![](image/Pasted%20image%2020250318202535.png)

## 总结

![](image/Pasted%20image%2020250318204438.png)

# Channel 接收数据原理

## <- c 关键字

![](image/Pasted%20image%2020250318204726.png)

## Channel 接收的情况

主要看 chanrecv 相关函数

### 有等待的G，从G接收

就是上文 Channel 发送的最后一种情况，没有缓存，此时有发送协程休眠在队列

#### 原理

![](image/Pasted%20image%2020250318225052.png)

#### 实现

![](image/Pasted%20image%2020250318225659.png)

### 用等待的G，从缓存接收

#### 原理

![](image/Pasted%20image%2020250318231044.png)

#### 实现

![](image/Pasted%20image%2020250318231055.png)

### 接收缓存

#### 原理

![](image/Pasted%20image%2020250318233835.png)

#### 实现

![](image/Pasted%20image%2020250318233853.png)

### 阻塞接收

#### 原理

![](image/Pasted%20image%2020250318233957.png)

#### 实现

![](image/Pasted%20image%2020250318234058.png)

## 总结

![](image/Pasted%20image%2020250318234151.png)

# 非阻塞的 Channel 如何实现

