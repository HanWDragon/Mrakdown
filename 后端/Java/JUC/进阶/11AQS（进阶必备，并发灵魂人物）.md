# 学习AQS的思路

![](image/Pasted%20image%2020220206152652.png)

# 为什么需要AQS

![](image/Pasted%20image%2020220206152835.png)

![](image/Pasted%20image%2020220206152926.png)

# Semaphore和AQS的关系

![](image/Pasted%20image%2020220206153028.png)

![](image/Pasted%20image%2020220206153115.png)

![](image/Pasted%20image%2020220206153134.png)

![](image/Pasted%20image%2020220206153155.png)

# AQS的比喻

![](image/Pasted%20image%2020220206153641.png)

![](image/Pasted%20image%2020220206153740.png)

# 如果没有AQS

![](image/Pasted%20image%2020220206153917.png)

# AQS的作用

![](image/Pasted%20image%2020220206154011.png)

# AQS的重要性、地位

![](image/Pasted%20image%2020220206154119.png)

![](image/Pasted%20image%2020220206154137.png)

# AQS内部原理解析

- AQS最核心的三个部分

## state

![](image/Pasted%20image%2020220206154544.png)

![](image/Pasted%20image%2020220206154710.png)

![](image/Pasted%20image%2020220206154801.png)
	
## 控制线程抢锁和配合的FIFO队列

![](image/Pasted%20image%2020220206154858.png)

![](image/Pasted%20image%2020220206154915.png)

## 期望协作工具类去实现的获取/释放等重要方法

![](image/Pasted%20image%2020220206154953.png)

### 获取方法

![](image/Pasted%20image%2020220206155049.png)

### 释放方法

![](image/Pasted%20image%2020220206155127.png)

### 需要重写tryAcquire和tryReleases等方法

![](image/Pasted%20image%2020220206155305.png)

# 应用实例、源码解析

## AQS用法

![](image/Pasted%20image%2020220206160439.png)

![](image/Pasted%20image%2020220206160507.png)

## AQS在CountDownLatch的应用

![](image/Pasted%20image%2020220206160548.png)

### 构造函数

![](image/Pasted%20image%2020220206160729.png)

### getCount

![](image/Pasted%20image%2020220206160809.png)

### countDown

![](image/Pasted%20image%2020220206161135.png)

![](image/Pasted%20image%2020220206163227.png)

![](image/Pasted%20image%2020220206163150.png)

### await

![](image/Pasted%20image%2020220206160901.png)

![](image/Pasted%20image%2020220206160924.png)

### 总结

![](image/Pasted%20image%2020220206163310.png)

## AQS在Semaphore的应用

![](image/Pasted%20image%2020220206185738.png)

![](image/Pasted%20image%2020220206185822.png)

![](image/Pasted%20image%2020220206190046.png)

## AQS在ReentrantLock的应用

![](image/Pasted%20image%2020220206190411.png)

![](image/Pasted%20image%2020220206190428.png)

![](image/Pasted%20image%2020220206190447.png)

![](image/Pasted%20image%2020220206190513.png)

![](image/Pasted%20image%2020220206191001.png)

# 利用AQS实现自己的Latch门闩

## 代码实现

```java
package aqs;

import java.util.concurrent.locks.AbstractQueuedSynchronizer;

/**
 * 描述：     自己用AQS实现一个简单的线程协作器
 */
public class OneShotLatch {

    private final Sync sync = new Sync();

    public void signal() {
        sync.releaseShared(0);
    }
    public void await() {
        sync.acquireShared(0);
    }

    private class Sync extends AbstractQueuedSynchronizer {

        @Override
        protected int tryAcquireShared(int arg) {
            return (getState() == 1) ? 1 : -1;
        }

        @Override
        protected boolean tryReleaseShared(int arg) {
           setState(1);

           return true;
        }
    }


    public static void main(String[] args) throws InterruptedException {
        OneShotLatch oneShotLatch = new OneShotLatch();
        for (int i = 0; i < 10; i++) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    System.out.println(Thread.currentThread().getName()+"尝试获取latch，获取失败那就等待");
                    oneShotLatch.await();
                    System.out.println("开闸放行"+Thread.currentThread().getName()+"继续运行");
                }
            }).start();
        }
        Thread.sleep(5000);
        oneShotLatch.signal();

        new Thread(new Runnable() {
            @Override
            public void run() {
                System.out.println(Thread.currentThread().getName()+"尝试获取latch，获取失败那就等待");
                oneShotLatch.await();
                System.out.println("开闸放行"+Thread.currentThread().getName()+"继续运行");
            }
        }).start();
    }
}

```
