# 方法概览

![](image/Pasted%20image%2020220207230756.png)

# wait，notify，notifyAll方法详解

## 普通用法

```java
package threadcoreknowledge.threadobjectclasscommonmethods;

/**
 * 描述：     展示wait和notify的基本用法 1. 研究代码执行顺序 2. 证明wait释放锁
 */
public class Wait {

    public static Object object = new Object();

    static class Thread1 extends Thread {

        @Override
        public void run() {
            synchronized (object) {
                System.out.println(Thread.currentThread().getName() + "开始执行了");
                try {
                    object.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
                System.out.println("线程" + Thread.currentThread().getName() + "获取到了锁。");
            }
        }
    }

    static class Thread2 extends Thread {

        @Override
        public void run() {
            synchronized (object) {
                object.notify();
                System.out.println("线程" + Thread.currentThread().getName() + "调用了notify()");
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread1 thread1 = new Thread1();
        Thread2 thread2 = new Thread2();
        thread1.start();
        Thread.sleep(200);
        thread2.start();
    }
}

```

## 阻塞状态 -> 唤醒（4种）

![](image/Pasted%20image%2020220208005447.png)



# sleep方法详解

# join方法

# yield方法

# 获取当前执行线程的引用：Thread.currentThread()方法

# stop，suspend，resume方法



# 面试题

- 为什么线程通信的方法wait(),notify()和notifyAll()被定义在Object类中，而sleep定义在Thread类中
- 用多种方式实现生产者模式
- Java SE 8 和 Java 1.8 和 JDK 8 是什么关系，是同一个东西吗
- join和sleep和wait期间线程的状态分别是什么，为什么