# 前提知识

## 父子进程

![](image/Pasted%20image%2020220215155848.png)

它们之间会有进程隔离，看不到对应的数据，可以使用`export` 命令来导出，就可以将某个变量变成环境变量，让子进程也知道有这个变量，这个就是我们书写  `/etc/profile` 要加入`export` 的原因

![](image/Pasted%20image%2020220215160048.png)

![](image/Pasted%20image%2020220215160356.png)



# VFS（virtual File System）

VFS 的作用就是采用标准的 Unix 系统调用读写位于不同物理介质上的不同文件系统,即为各类文件系统提供了一个统一的操作界面和应用编程接口。

VFS是一个可以让`open()、read()、write()` 等系统调用不用关心底层的存储介质和文件系统类型就可以工作的粘合层。

就像在 Java 开发中我们要去操作数据库，如果直接去操作对我们来说是非常痛苦的，需要了解不同数据库的特点，但是有了 JDBC 后，就不用担心使用的数据库是什么，统一了 API ，简化了开发，访问不同的数据库

如果一个文件想读取数据，首先就去访问内核，去 VFS 树中找到对应的文件，文件都是我们内核去读取，读到内存里面 PageCache 默认是 4K 的大小，如果有多个程序，想打开的是同一个文件，也就意味着它们操作的是同一个 PageCache ，这个是它们共享的。

还有一个知识点就是 dirty ，当我的程序对 PageCache 中的数据进行了修改，那么内核就会把这个 PageCache 标记为 dirty ，那么就会有一个 flush 的过程，将数据写到磁盘上面去，但是什么时候写入就是 IO 做的事情，但是这样就会造成一个问题，就是有的时候数据量过大，在设置的参数都没有被触发的情况下，可能会丢失数据

对于很多进程操纵同一个文件去读取，就很像 Java集合中的迭代器模式，每个线程自己干自己的

**对应图片**

![](image/Pasted%20image%2020220214222816.png)

## 实际操作

文件系统就是一个树状结构，在用户前面的数字，就是这个文件被硬链接的次数，比如 Applicantions 就被硬链接了 72 次

硬链接使用的命令是 `ln` 软连接则是加上 `-s`

![](image/Pasted%20image%2020220214223144.png)

df 命令可以看到内存中的目录树结构，可以看到文件挂载的位置和情况

![](image/Pasted%20image%2020220214223351.png)

![](image/Pasted%20image%2020220215003408.png)

使用到的命令

`ld` 命令分析程序需要用到哪些动态库
`lsof` 显示当前进程打开了哪些文件

![](image/Pasted%20image%2020220215003645.png)

# FD

对应概念

- cwd：current work dir 当前工作目录
- txt：文本域
- 0u：标准输入
- 1u：标准输出
- 2u：报错输出

任何程序都有 0、1、2 三个描述符，可以用不同的文件描述符，来表示不同的文件，内核为不同的进程维护自己的 FD

![](image/Pasted%20image%2020220215010133.png)

![](image/Pasted%20image%2020220215010232.png)

![](image/Pasted%20image%2020220215151214.png)

## 重定向机制讲解

![](image/Pasted%20image%2020220215151951.png)

![](image/Pasted%20image%2020220215152315.png)

![](image/Pasted%20image%2020220215153503.png)

上面的这些演示都是针对重定向操作符的，任何进程都有自己的输入输出 FD，我们可以通过重定向来改变流的指向，就像在Java中改变标准输入输出流的指向来完成不同的需求

Tips：
- 重定向操作符左边一定是文件描述符（FD），右边放的基本是文件，但是像 `2> 1` ，这个语法就有歧义，因为输出到另外一个 FD，所以人为规定像 `2> 1` 这样强制需要加上`&`来标示 `2>& 1`
- 重定向绑定是有顺序的，是一个一个去绑定的，所以`ls ./ 2.o 2>& 1 1> 3.out`所以 FD 2 重定向的是标准输出流 FD 1 重定向的是 3.out 这个文件

## 管道讲解

![](image/Pasted%20image%2020220215155052.png)

要是我想显示中间的某一行咋办，我们就需要使用管道，其实就是使用到了重定向，将前一个的输入重定向到后一个的输出

### 指令块

指令块中的命令都是在同一进程下执行

![](image/Pasted%20image%2020220215162920.png)

![](image/Pasted%20image%2020220215163242.png)

看到这个结果是不是很疑惑，不是在同一个进程执行的，这个问题就出现在管道的执行机制上面，因为 Bash 是解释执行，检测到有管道符，会在管道的两边启动子进程，并重定向它们的输入输出，这就是一个坑

第二个坑就是,要注意解释执行带来的优先级问题，比如`echo $$（参数扩展）` 的优先级是大于 `|` 但是`echo $BASHPID` 不是，所以就出现了这种情况。

![](image/Pasted%20image%2020220215164148.png)

看到了这些坑，我们又可以愉快的看到 IO 上面了

![](image/Pasted%20image%2020220215165206.png)

![](image/Pasted%20image%2020220215165014.png)

![](image/Pasted%20image%2020220215165017.png)

此时我们就看到父进程产生的两个子进程，我们去查看对应的 FD ，就可以看到对应的 FD 1 重定向到了管道

![](image/Pasted%20image%2020220215165444.png)

![](image/Pasted%20image%2020220215165702.png)

![](image/Pasted%20image%2020220215165954.png)

![](image/Pasted%20image%2020220215170018.png)

到这里我们就知道管道的本质了

# PageCache



![](image/Pasted%20image%2020220215172740.png)

![](image/Pasted%20image%2020220215174840.png) 

## 代码测试

```java
package com.bjmashibing.system.io;

import org.junit.Test;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

public class OSFileIO {

    static byte[] data = "123456789\n".getBytes();
    static String path =  "/root/testfileio/out.txt";


    public static void main(String[] args) throws Exception {


        switch ( args[0]) {
            case "0" :
                testBasicFileIO();
                break;
            case "1":
                testBufferedFileIO();
                break;
            case "2" :
                testRandomAccessFileWrite();
            case "3":
//                whatByteBuffer();
            default:

        }
    }


    //最基本的file写

    public static  void testBasicFileIO() throws Exception {
        File file = new File(path);
        FileOutputStream out = new FileOutputStream(file);
        while(true){
            Thread.sleep(10);
            out.write(data);

        }

    }

    //测试buffer文件IO
    //  jvm  8kB   syscall  write(8KBbyte[])

    public static void testBufferedFileIO() throws Exception {
        File file = new File(path);
        BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(file));
        while(true){
            Thread.sleep(10);
            out.write(data);
        }
    }



    //测试文件NIO


        public static void testRandomAccessFileWrite() throws  Exception {


        RandomAccessFile raf = new RandomAccessFile(path, "rw");

        raf.write("hello mashibing\n".getBytes());
        raf.write("hello seanzhou\n".getBytes());
        System.out.println("write------------");
        System.in.read();

        raf.seek(4);
        raf.write("ooxx".getBytes());

        System.out.println("seek---------");
        System.in.read();

        FileChannel rafchannel = raf.getChannel();
        //mmap  堆外  和文件映射的   byte  not  objtect
        MappedByteBuffer map = rafchannel.map(FileChannel.MapMode.READ_WRITE, 0, 4096);


        map.put("@@@".getBytes());  //不是系统调用  但是数据会到达 内核的pagecache
            //曾经我们是需要out.write()  这样的系统调用，才能让程序的data 进入内核的pagecache
            //曾经必须有用户态内核态切换
            //mmap的内存映射，依然是内核的pagecache体系所约束的！！！
            //换言之，丢数据
            //你可以去github上找一些 其他C程序员写的jni扩展库，使用linux内核的Direct IO
            //直接IO是忽略linux的pagecache
            //是把pagecache  交给了程序自己开辟一个字节数组当作pagecache，动用代码逻辑来维护一致性/dirty。。。一系列复杂问题

        System.out.println("map--put--------");
        System.in.read();

//        map.force(); //  flush



        raf.seek(0);

        ByteBuffer buffer = ByteBuffer.allocate(8192);
//        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);

        int read = rafchannel.read(buffer);   //buffer.put()
        System.out.println(buffer);
        buffer.flip();
        System.out.println(buffer);

        for (int i = 0; i < buffer.limit(); i++) {
            Thread.sleep(200);
            System.out.print(((char)buffer.get(i)));
        }


    }


    @Test
    public  void whatByteBuffer(){

//        ByteBuffer buffer = ByteBuffer.allocate(1024);
        ByteBuffer buffer = ByteBuffer.allocateDirect(1024);


        System.out.println("postition: " + buffer.position());
        System.out.println("limit: " +  buffer.limit());
        System.out.println("capacity: " + buffer.capacity());
        System.out.println("mark: " + buffer);

        buffer.put("123".getBytes());

        System.out.println("-------------put:123......");
        System.out.println("mark: " + buffer);

        buffer.flip();   //读写交替

        System.out.println("-------------flip......");
        System.out.println("mark: " + buffer);

        buffer.get();

        System.out.println("-------------get......");
        System.out.println("mark: " + buffer);

        buffer.compact();

        System.out.println("-------------compact......");
        System.out.println("mark: " + buffer);

        buffer.clear();

        System.out.println("-------------clear......");
        System.out.println("mark: " + buffer);

    }


}

```

当我们运行这个程序，传入参数 0 运行 `testBasicFileIO()`，我们在写入的时候，突然突然关闭虚拟机，会发现刚刚能通过 `ls` 看到文件容量不为 0 的文件，此时容量全都变成了 0，说明了之前写入的都是 PageCache，并没有写入磁盘，没有进行 `flush`

![](image/Pasted%20image%2020220215224746.png)

![](image/Pasted%20image%2020220215230427.png)

相应的参数可以在 `/etc/sysctl.conf` 编辑，Redis
的 AOF ，Mysql 的 binlog 和 redolog ，它们都是日志，它们都有三个级别去调整
1. 每秒写
2. 随内核
3. 每操作就要写
为什么定义出三种，因为你写入时候内核并不会立即写入磁盘，可能发生造成数据丢失，那就是丢一秒，丢一缓冲区，丢一条数据，所以要在这之前权衡了

就像上面的代码测试，因为这个过程不好演示，就直接表述
- 对于输入参数0使用的这个方法，是直接写入内存的 PageCache，但是由于修改了一些系统选项，让系统不要写入磁盘，于是当我们强制关机的时候，就会发现，刚刚写入的文件全都没有数据了，并且是直接与 PageCache 交互，会导致效率低下
- 对于输入参数1使用的这个方法，因为使用了缓冲区，可以避免与内核进行大量的交互，默认JVM会在数据到达 8KB 的时候向 PageCache 写入，这样就减少了与内核进行 IO 的次数

但是我还是没有将数据写入磁盘，也就意味着我的数据依然在内存当中，受系统内核管理，假如此时有一个程序在疯狂的向内存写入，导致内存紧缺或者到达了设定的阈值，由于 LRU 或者 LFU 就会把一些脏页内存块写入磁盘（因为只有脏数据才有向硬盘写入的必要），但是这个过程是不可控的，当发生故障的时候，这样就会造成数据丢失或者损坏，因为内存中还保存着许多数据，程序很多时候都由不得自己，很多东西都是由内核控制，那么在实际生产环境下，要是直接交给操作系统处理，当丢失数据的时候，你想想会丢失多少数据，就像在Redis中都是默认每秒记录

![](image/Pasted%20image%2020220216143556.png)

虽然你能看到自己的文件变大，但是这是 VFS 带来的虚拟

我们常说的4k对齐，就是这个原因，方便寻址

当我们使用 mmap 进行映射，我们就可以直接使用内核管理的 PageCache，这样还不会有用户态和内核态的切换，速度更快（大文件最好不要用），而且我们可以使用 `lsof -p` 命令来知道这个Java进程在背后干了什么
也可以使用 `strace java your_program` 来查看Java用了哪些系统调用

![](image/Pasted%20image%2020220216193433.png)

# Java文件系统

## 文件系统的IO

## 内存和IO关系

## 网络IO