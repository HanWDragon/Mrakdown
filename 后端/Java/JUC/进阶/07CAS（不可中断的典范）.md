# 什么是CAS

![](image/Pasted%20image%2020220205094355.png)

![](image/Pasted%20image%2020220205094432.png)

![](image/Pasted%20image%2020220205094513.png)

```java
package cas;

/**
 * 描述：     模拟CAS操作，等价代码
 */
public class SimulatedCAS {
    private volatile int value;

    public synchronized int compareAndSwap(int expectedValue, int newValue) {
        int oldValue = value;
        if (oldValue == expectedValue) {
            value = newValue;
        }
        return oldValue;
    }
}

```

# 案例演示

![](image/Pasted%20image%2020220205094915.png)

```java
package cas;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.atomic.AtomicIntegerArray;

/**
 * 描述：     模拟CAS操作，等价代码
 */
public class TwoThreadsCompetition implements Runnable {

    private volatile int value;

    public synchronized int compareAndSwap(int expectedValue, int newValue) {
        int oldValue = value;
        if (oldValue == expectedValue) {
            value = newValue;
        }
        return oldValue;
    }

    public static void main(String[] args) throws InterruptedException {
        TwoThreadsCompetition r = new TwoThreadsCompetition();
        r.value = 0;
        Thread t1 = new Thread(r,"Thread 1");
        Thread t2 = new Thread(r,"Thread 2");
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(r.value);
    }

    @Override
    public void run() {
        compareAndSwap(0, 1);
    }
}

```

# 应用场景

![](image/Pasted%20image%2020220205101301.png)

# Java如何使用CAS实现原子类

![](image/Pasted%20image%2020220205101607.png)

![](image/Pasted%20image%2020220205101822.png)

![](image/Pasted%20image%2020220205101904.png)

![](image/Pasted%20image%2020220205101939.png)

![](image/Pasted%20image%2020220205102529.png)

# Unsafe类

![](image/Pasted%20image%2020220205102212.png)

## Unsafe类中的compareAndSwapInt

![](image/Pasted%20image%2020220205102410.png)

# CAS也有不好的问题

![](image/Pasted%20image%2020220205102702.png)



