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

# 为什么需要ConcurrentHashMap

![](image/Pasted%20image%2020220205135423.png)

![](image/Pasted%20image%2020220205135449.png)

![](image/Pasted%20image%2020220205135603.png)

## HashMap源码分析 Java1.7

![](image/Pasted%20image%2020220205143838.png)

 ![](image/Pasted%20image%2020220205143857.png)

# HashMapJava8

![](image/Pasted%20image%2020220205143938.png)

![](image/Pasted%20image%2020220205143949.png)

![](image/Pasted%20image%2020220205144028.png)

# 红黑树

![](image/Pasted%20image%2020220205144413.png)

# HashMap关于并发的特点

![](image/Pasted%20image%2020220205144545.png)

# JDK1.7ConcurrentHashMap的实现和分析

![](image/Pasted%20image%2020220205144648.png)

![](image/Pasted%20image%2020220205144713.png)

![](image/Pasted%20image%2020220205144814.png)

# JDK1.8ConcurrentHashMap的实现和分析

![](image/Pasted%20image%2020220205144947.png)

# putVal流程

![](image/Pasted%20image%2020220205201919.png)

# get流程

![](image/Pasted%20image%2020220205202013.png)

# 为什么要改变结构

![](image/Pasted%20image%2020220205202339.png)

![](image/Pasted%20image%2020220205202454.png)

# ConcurrentHashMap可能会线程不安全

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

# 组合操作

![](image/Pasted%20image%2020220205204536.png)

# 实际生产案例



# CopyOnWriteArrayList

# 并发队列Queue（阻塞队列、非阻塞队列）

# 并发容器总结