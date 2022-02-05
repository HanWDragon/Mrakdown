# 两大使用场景-ThreadLocal的用途

<img src="image/image-20220203162817660.png" alt="image-20220203162817660" style="zoom:50%;" />

## 典型场景1:每个线程都需要一个独享的对象

<img src="image/image-20220203162924700.png" alt="image-20220203162924700" style="zoom:50%;" />

<img src="image/image-20220203163000292.png" alt="image-20220203163000292" style="zoom:50%;" />

### 两个线程分别用自己的SimpleDateFormat

<img src="image/image-20220203163109191.png" alt="image-20220203163109191" style="zoom:50%;" />

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 描述：     两个线程打印日期
 */
public class ThreadLocalNormalUsage00 {

    public static void main(String[] args) {
        new Thread(new Runnable() {
            @Override
            public void run() {
                String date = new ThreadLocalNormalUsage00().date(10);
                System.out.println(date);
            }
        }).start();
        new Thread(new Runnable() {
            @Override
            public void run() {
                String date = new ThreadLocalNormalUsage00().date(104707);
                System.out.println(date);
            }
        }).start();
    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(date);
    }
}
```

### 但是有很多线程都需要使用SimpleDateFormat，那就有 10 个 SimpleDateFormat 和 10 个线程，写法不优雅

<img src="image/image-20220203163812422.png" alt="image-20220203163812422" style="zoom:50%;" />

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * 描述：     10个线程打印日期
 */
public class ThreadLocalNormalUsage01 {

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 30; i++) {
            int finalI = i;
            new Thread(new Runnable() {
                @Override
                public void run() {
                    String date = new ThreadLocalNormalUsage01().date(finalI);
                    System.out.println(date);
                }
            }).start();
            Thread.sleep(100);
        }

    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(date);
    }
}
```

### 当线程变成 1000 个，我们就得用线程池来改写（要不然性能太差）

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.Executor;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 描述：     1000个打印日期的任务，用线程池来执行
 */
public class ThreadLocalNormalUsage02 {

    public static ExecutorService threadPool = Executors.newFixedThreadPool(10);

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 1000; i++) {
            int finalI = i;
            threadPool.submit(new Runnable() {
                @Override
                public void run() {
                    String date = new ThreadLocalNormalUsage02().date(finalI);
                    System.out.println(date);
                }
            });
        }
        threadPool.shutdown();
    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        return dateFormat.format(date);
    }
}
```

### 但是这个还是有重复创建对象SimpleDateFormat造成了性能浪费

改进后创建成全局变量

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 描述：     1000个打印日期的任务，用线程池来执行
 */
public class ThreadLocalNormalUsage03 {

    public static ExecutorService threadPool = Executors.newFixedThreadPool(10);
    static SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 1000; i++) {
            int finalI = i;
            threadPool.submit(new Runnable() {
                @Override
                public void run() {
                    String date = new ThreadLocalNormalUsage03().date(finalI);
                    System.out.println(date);
                }
            });
        }
        threadPool.shutdown();
    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
        return dateFormat.format(date);
    }
}
```

### 但是我们发现打印的结果不是我们想要的

## 原因就是所有的线程都共用同一个SimpleDateFormat（线程不安全）对象

<img src="image/image-20220203164816748.png" alt="image-20220203164816748" style="zoom:50%;" />

### 遇到线程不安全问题我们首先想到的都是加锁，但是这样会导致效率比较低

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 描述：     加锁来解决线程安全问题
 */
public class ThreadLocalNormalUsage04 {

    public static ExecutorService threadPool = Executors.newFixedThreadPool(10);
    static SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 1000; i++) {
            int finalI = i;
            threadPool.submit(new Runnable() {
                @Override
                public void run() {
                    String date = new ThreadLocalNormalUsage04().date(finalI);
                    System.out.println(date);
                }
            });
        }
        threadPool.shutdown();
    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
        String s = null;
        synchronized (ThreadLocalNormalUsage04.class) {
            s = dateFormat.format(date);
        }
        return s;
    }
}
```

### 更好的解决方法就是ThreadLocal

<img src="image/image-20220203170007598.png" alt="image-20220203170007598" style="zoom:50%;" />

```java
package threadlocal;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

/**
 * 描述：     利用ThreadLocal，给每个线程分配自己的dateFormat对象，保证了线程安全，高效利用内存
 */
public class ThreadLocalNormalUsage05 {

    public static ExecutorService threadPool = Executors.newFixedThreadPool(10);

    public static void main(String[] args) throws InterruptedException {
        for (int i = 0; i < 1000; i++) {
            int finalI = i;
            threadPool.submit(new Runnable() {
                @Override
                public void run() {
                    String date = new ThreadLocalNormalUsage05().date(finalI);
                    System.out.println(date);
                }
            });
        }
        threadPool.shutdown();
    }

    public String date(int seconds) {
        //参数的单位是毫秒，从1970.1.1 00:00:00 GMT计时
        Date date = new Date(1000 * seconds);
//        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        SimpleDateFormat dateFormat = ThreadSafeFormatter.dateFormatThreadLocal2.get();
        return dateFormat.format(date);
    }
}

class ThreadSafeFormatter {

    public static ThreadLocal<SimpleDateFormat> dateFormatThreadLocal = new ThreadLocal<SimpleDateFormat>() {
        @Override
        protected SimpleDateFormat initialValue() {
            return new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
        }
    };

    public static ThreadLocal<SimpleDateFormat> dateFormatThreadLocal2 = ThreadLocal
            .withInitial(() -> new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"));
}
```

## 典型场景2:每个线程内需要保存全局变量

### 当前用户信息需要被线程内所有方法共享

<img src="image/image-20220203171112438.png" alt="image-20220203171112438" style="zoom:50%;" />

<img src="image/image-20220203171708844.png" alt="image-20220203171708844" style="zoom:50%;" />

<img src="image/image-20220203171735376.png" alt="image-20220203171735376" style="zoom:50%;" />

<img src="image/image-20220203171759246.png" alt="image-20220203171759246" style="zoom:50%;" />

### 每个线程内需要保存全局变量，可以让不同方法直接使用，避免参数传递的麻烦

<img src="image/image-20220203171513455.png" alt="image-20220203171513455" style="zoom:50%;" />

### 使用方法

<img src="image/image-20220203171840211.png" alt="image-20220203171840211" style="zoom:50%;" />

```java
package threadlocal;

/**
 * 描述：     演示ThreadLocal用法2：避免传递参数的麻烦
 */
public class ThreadLocalNormalUsage06 {

    public static void main(String[] args) {
        new Service1().process("");

    }
}

class Service1 {

    public void process(String name) {
        User user = new User("超哥");
        UserContextHolder.holder.set(user);
        new Service2().process();
    }
}

class Service2 {

    public void process() {
        User user = UserContextHolder.holder.get();
        ThreadSafeFormatter.dateFormatThreadLocal.get();
        System.out.println("Service2拿到用户名：" + user.name);
        new Service3().process();
    }
}

class Service3 {

    public void process() {
        User user = UserContextHolder.holder.get();
        System.out.println("Service3拿到用户名：" + user.name);
        UserContextHolder.holder.remove();
    }
}

class UserContextHolder {

    public static ThreadLocal<User> holder = new ThreadLocal<>();


}

class User {

    String name;

    public User(String name) {
        this.name = name;
    }
}
```

<img src="image/image-20220203172307084.png" alt="image-20220203172307084" style="zoom:50%;" />

<img src="image/image-20220203172513832.png" alt="image-20220203172513832" style="zoom:50%;" />

## 根据共享对象的生成时机不同，选择initialValue或set来保存对象

### initialValue

<img src="image/image-20220203172832714.png" alt="image-20220203172832714" style="zoom:50%;" />

### set

<img src="image/image-20220203172909491.png" alt="image-20220203172909491" style="zoom:50%;" />

# 使用ThreadLocal带来的好处

<img src="image/image-20220203173058203.png" alt="image-20220203173058203" style="zoom:50%;" />

<img src="image/image-20220203173142019.png" alt="image-20220203173142019" style="zoom:50%;" />

# 原理、源码分析

<img src="image/image-20220203173702321.png" alt="image-20220203173702321" style="zoom:50%;" />

# 主要方法介绍

<img src="image/image-20220203202059532.png" alt="image-20220203202059532" style="zoom:50%;" />

<img src="image/image-20220203202124674.png" alt="image-20220203202124674" style="zoom:50%;" />

<img src="image/image-20220203202135774.png" alt="image-20220203202135774" style="zoom:50%;" />

## T initialValue()

<img src="image/image-20220203201813005.png" alt="image-20220203201813005" style="zoom:50%;" />

<img src="image/image-20220203201949080.png" alt="image-20220203201949080" style="zoom:50%;" />

<img src="image/image-20220203203013515.png" alt="image-20220203203013515" style="zoom:50%;" />

## get 方法

<img src="image/image-20220203202737868.png" alt="image-20220203202737868" style="zoom:50%;" />

<img src="image/image-20220203202848197.png" alt="image-20220203202848197" style="zoom:50%;" />

## ThreadLocalMap类

<img src="image/image-20220203203434584.png" alt="image-20220203203434584" style="zoom:50%;" />

<img src="image/image-20220203203536516.png" alt="image-20220203203536516" style="zoom:50%;" />

## 两种使用场景殊途同归

<img src="image/image-20220203203755068.png" alt="image-20220203203755068" style="zoom:50%;" />

# 注意点

<img src="image/image-20220203203900726.png" alt="image-20220203203900726" style="zoom:50%;" />

<img src="image/image-20220203204351267.png" alt="image-20220203204351267" style="zoom:50%;" />

![image-20220203204054719](image/image-20220203204054719.png) <img src="image/image-20220203204517136.png" alt="image-20220203204517136" style="zoom:50%;" />

<img src="image/image-20220203204655873.png" alt="image-20220203204655873" style="zoom:50%;" />

<img src="image/image-20220203204754898.png" alt="image-20220203204754898" style="zoom:50%;" />

<img src="image/image-20220203204920219.png" alt="image-20220203204920219" style="zoom:50%;" />

<img src="image/image-20220203205403129.png" alt="image-20220203205403129" style="zoom:50%;" />

```java
package threadlocal;

/**
 * 描述：     TODO
 */
public class ThreadLocalNPE {

    ThreadLocal<Long> longThreadLocal = new ThreadLocal<Long>();

    public void set() {
        longThreadLocal.set(Thread.currentThread().getId());
    }

    public long get() {
        return longThreadLocal.get();
    }

    public static void main(String[] args) {
        ThreadLocalNPE threadLocalNPE = new ThreadLocalNPE();
        System.out.println(threadLocalNPE.get());
        Thread thread1 = new Thread(new Runnable() {
            @Override
            public void run() {
                threadLocalNPE.set();
                System.out.println(threadLocalNPE.get());
            }
        });
        thread1.start();
    }
}
```

<img src="image/image-20220203205600170.png" alt="image-20220203205600170" style="zoom:50%;" />

# 实际应用场景-在Spring中的实例分析

<img src="image/image-20220203205903225.png" alt="image-20220203205903225" style="zoom:50%;" />
