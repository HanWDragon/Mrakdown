# 并发容器概览

![](image/Pasted%20image%2020220205131016.png)

![](image/Pasted%20image%2020220205131204.png)

# 集合类的历史-古老和过时的同步容器

![](image/Pasted%20image%2020220205131421.png)

```java
package collections.predecessor;

import java.util.Vector;

/**
 * 描述：     演示Vector，主要是看Vector源码
 */
public class VectorDemo {

    public static void main(String[] args) {
        Vector<String> vector = new Vector<>();
        vector.add("test");
        System.out.println(vector.get(0));
    }

}

```

![](image/Pasted%20image%2020220205131840.png)

```java
package collections.predecessor;

import java.util.Hashtable;

/**
 * 描述：     TODO
 */
public class HashtableDemo {
    public static void main(String[] args) {
        Hashtable<String, String> hashtable = new Hashtable<>();
        hashtable.put("学完以后跳槽涨薪幅度", "80%");
        System.out.println(hashtable.get("学完以后跳槽涨薪幅度"));
    }

}

```

![](image/Pasted%20image%2020220205132104.png)

![](image/Pasted%20image%2020220205132154.png)

![](image/Pasted%20image%2020220205132221.png)

```java
package collections.predecessor;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * 描述：     演示Collections.synchronizedList(new ArrayList<E>())
 */
public class SynList {
    public static void main(String[] args) {
        List<Integer> list = Collections.synchronizedList(new ArrayList<Integer>());
        list.add(5);
        System.out.println(list.get(0));

        Map<Object, Object> objectObjectMap = Collections.synchronizedMap(new HashMap<>());
    }
}

```

![](image/Pasted%20image%2020220205132420.png)

![](image/Pasted%20image%2020220205132531.png)

# ConcurrentHashMap（重点、面试常考）

## Map简介

![](image/Pasted%20image%2020220205134327.png)

![](image/Pasted%20image%2020220205134349.png)

![](image/Pasted%20image%2020220205134514.png)

## Map常用方法

![](image/Pasted%20image%2020220205134713.png)

```java
package collections.predecessor;

import java.util.HashMap;
import java.util.Map;

/**
 * 描述：     演示Map的基本用法
 */
public class MapDemo {
    public static void main(String[] args) {
        Map<String, Integer> map = new HashMap<>();
        System.out.println(map.isEmpty());
        map.put("东哥", 38);
        map.put("西哥", 28);
        System.out.println(map.keySet());
        System.out.println(map.get("西哥"));
        System.out.println(map.size());
        System.out.println(map.containsKey("东哥"));
        map.remove("东哥");
        System.out.println(map.containsKey("东哥"));

    }
}

```

## 为什么需要ConcurrentHashMap

![](image/Pasted%20image%2020220205135423.png)

![](image/Pasted%20image%2020220205135449.png)

![](image/Pasted%20image%2020220205135603.png)

## HashMap源码分析 Java1.7

![](image/Pasted%20image%2020220205143838.png)

 ![](image/Pasted%20image%2020220205143857.png)

## HashMapJava8

![](image/Pasted%20image%2020220205143938.png)

![](image/Pasted%20image%2020220205143949.png)

![](image/Pasted%20image%2020220205144028.png)

## 红黑树

![](image/Pasted%20image%2020220205144413.png)

## HashMap关于并发的特点

![](image/Pasted%20image%2020220205144545.png)

## JDK1.7ConcurrentHashMap的实现和分析

![](image/Pasted%20image%2020220205144648.png)

![](image/Pasted%20image%2020220205144713.png)

![](image/Pasted%20image%2020220205144814.png)

## JDK1.8ConcurrentHashMap的实现和分析

![](image/Pasted%20image%2020220205144947.png)

## putVal流程

![](image/Pasted%20image%2020220205201919.png)

## get流程

![](image/Pasted%20image%2020220205202013.png)

## 为什么要改变结构

![](image/Pasted%20image%2020220205202339.png)

![](image/Pasted%20image%2020220205202454.png)

## ConcurrentHashMap可能会线程不安全

![](image/Pasted%20image%2020220205204139.png)

```java
package collections.concurrenthashmap;

import java.util.concurrent.ConcurrentHashMap;

/**
 * 描述：     组合操作并不保证线程安全
 */
public class OptionsNotSafe implements Runnable {

    private static ConcurrentHashMap<String, Integer> scores = new ConcurrentHashMap<String, Integer>();

    public static void main(String[] args) throws InterruptedException {
        scores.put("小明", 0);
        Thread t1 = new Thread(new OptionsNotSafe());
        Thread t2 = new Thread(new OptionsNotSafe());
        t1.start();
        t2.start();
        t1.join();
        t2.join();
        System.out.println(scores);
    }


    @Override
    public void run() {
        for (int i = 0; i < 1000; i++) {
            while (true) {
                Integer score = scores.get("小明");
                Integer newScore = score + 1;
                boolean b = scores.replace("小明", score, newScore);
                if (b) {
                    break;
                }
            }
        }

    }
}

```

## 组合操作

![](image/Pasted%20image%2020220205204536.png)

# CopyOnWriteArrayList

## 诞生的历史和原因

![](image/Pasted%20image%2020220205224840.png)


## 适用场景

![](image/Pasted%20image%2020220205225445.png)

## 读写规则

![](image/Pasted%20image%2020220205230006.png)

```java
package collections.copyonwrite;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * 描述：演示CopyOnWriteArrayList可以在迭代的过程中修改数组内容，但是ArrayList不行，对比
 */
public class CopyOnWriteArrayListDemo1 {

    public static void main(String[] args) {
        ArrayList<String> list = new ArrayList<>();
//        CopyOnWriteArrayList<String> list = new CopyOnWriteArrayList<>();

        list.add("1");
        list.add("2");
        list.add("3");
        list.add("4");
        list.add("5");

        Iterator<String> iterator = list.iterator();

        while (iterator.hasNext()) {
            System.out.println("list is" + list);
            String next = iterator.next();
            System.out.println(next);

            if (next.equals("2")) {
                list.remove("5");
            }
            if (next.equals("3")) {
                list.add("3 found");
            }
        }
    }
}

```

## 实现原理

![](image/Pasted%20image%2020220205230953.png)

```java
package collections.copyonwrite;

import java.util.Iterator;
import java.util.concurrent.CopyOnWriteArrayList;

/**
 * 描述：     对比两个迭代器
 */
public class CopyOnWriteArrayListDemo2 {

    public static void main(String[] args) throws InterruptedException {
        CopyOnWriteArrayList<Integer> list = new CopyOnWriteArrayList<>(new Integer[]{1, 2, 3});

        System.out.println(list);

        Iterator<Integer> itr1 = list.iterator();

        list.remove(2);
        Thread.sleep(1000);
        System.out.println(list);

        Iterator<Integer> itr2 = list.iterator();

        itr1.forEachRemaining(System.out::println);
        itr2.forEachRemaining(System.out::println);

    }
}

```

## 缺点

![](image/Pasted%20image%2020220205231449.png)

## 源码分析

![](image/Pasted%20image%2020220205231819.png)

![](image/Pasted%20image%2020220205231909.png)

![](image/Pasted%20image%2020220205232341.png)

![](image/Pasted%20image%2020220205232542.png)



# 并发队列Queue（阻塞队列、非阻塞队列）

## 为什么要使用队列

![](image/Pasted%20image%2020220205233224.png)

## 并发队列简介

![](image/Pasted%20image%2020220205234103.png)

# 并发队列关系图

![](image/Pasted%20image%2020220205234117.png)

## 阻塞队列 BlockingQueue

### 什么是阻塞队列

![](image/Pasted%20image%2020220205235019.png)

![](image/Pasted%20image%2020220205235058.png)

![](image/Pasted%20image%2020220205235137.png)

![](image/Pasted%20image%2020220205235214.png)

![](image/Pasted%20image%2020220206000311.png)

### 主要方法介绍

 ![](image/Pasted%20image%2020220206001350.png)

### ArrayBlockingQueue

 ![](image/Pasted%20image%2020220206001727.png)

 ![](image/Pasted%20image%2020220206002957.png)

 ```java
package collections.queue;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;

/**
 * 描述：     TODO
 */
public class ArrayBlockingQueueDemo {


    public static void main(String[] args) {

        ArrayBlockingQueue<String> queue = new ArrayBlockingQueue<String>(3);

        Interviewer r1 = new Interviewer(queue);
        Consumer r2 = new Consumer(queue);
        new Thread(r1).start();
        new Thread(r2).start();
    }
}

class Interviewer implements Runnable {

    BlockingQueue<String> queue;

    public Interviewer(BlockingQueue queue) {
        this.queue = queue;
    }

    @Override
    public void run() {
        System.out.println("10个候选人都来啦");
        for (int i = 0; i < 10; i++) {
            String candidate = "Candidate" + i;
            try {
                queue.put(candidate);
                System.out.println("安排好了" + candidate);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        try {
            queue.put("stop");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}

class Consumer implements Runnable {

    BlockingQueue<String> queue;

    public Consumer(BlockingQueue queue) {

        this.queue = queue;
    }

    @Override
    public void run() {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        String msg;
        try {
            while(!(msg = queue.take()).equals("stop")){
                System.out.println(msg + "到了");
            }
            System.out.println("所有候选人都结束了");
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
} 
```

![](image/Pasted%20image%2020220206003009.png)

![](image/Pasted%20image%2020220206003030.png)

### LinkedBlockingQueue

![](image/Pasted%20image%2020220206003119.png)

![](image/Pasted%20image%2020220206003245.png)

 ![](image/Pasted%20image%2020220206003256.png)

 ![](image/Pasted%20image%2020220206003719.png)

 ![](image/Pasted%20image%2020220206003753.png)

### PriorityBlockingQueue

![](image/Pasted%20image%2020220206003909.png)

### SynchronousQueue

![](image/Pasted%20image%2020220206004112.png)

![](image/Pasted%20image%2020220206004139.png)

#### 注意点

![](image/Pasted%20image%2020220206004331.png)

### DelayQueue

![](image/Pasted%20image%2020220206004433.png)

## 非阻塞队列

![](image/Pasted%20image%2020220206004515.png)

## 如何选择合适自己的队列

![](image/Pasted%20image%2020220206004628.png)

# 并发容器总结

![](image/Pasted%20image%2020220206004725.png)