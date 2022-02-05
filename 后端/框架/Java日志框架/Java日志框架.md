# 日志简介

## 日志概述

只要程序员投身在实际的学习和生产环境中，就会对日志的重要性有着充分的认知，尤其是对于Web以及更高级的应用。在很多情况下，日志可能是我们了解应用如何执行的唯一方式。

但是现实是很多程序员对于日志的记录的认知比较肤浅，认为日志的记录输出是一件很简单而且会自动发生的事情，所以会经常忽略和日志相关的问题。

所以本课程主要就是针对于对于日志概念以及日志的框架不太熟悉的这类开发人群，更加详细且真实的体会日志为我们在开发和生产环境当中所带来的好处。

Java语言的强大之处就是因为它强大而且成熟的生态体系。其中包括日志框架，就有很多成熟的开源资源可以直接使用。

## 日志文件

日志文件是用于记录系统操作事件的文件集合。

日志文件它具有处理历史数据、诊断问题的追踪以及理解系统的活动等重要的作用。

## 调试日志

在软件开发中，我们要去经常的调试程序，或者做一些状态的输出，便于我们查询程序的运行状况。为了让我们能够更加灵活且方便的控制这些调试信息，我们肯定是需要更加专业的日志技术。我们平时在调试程序的过程中所使用的肯定就是专业开发工具自带的debug功能，可以实时查看程序运行情况，不能够有效保存运行情况的信息。调试日志是能够更加方便的去“重现”这些问题。

###  系统日志

系统日志是用来记录系统中硬件、软件和系统相关问题的信息。同时还可以监视系统中发生的事件。用户可以通过它来检查错误发生的原因，或者寻找收到攻击是留下的痕迹。

系统日志包括系统日志、应用日志和安全日志这几种分类。

## 日志框架

### 日志框架的作用

1. 控制日志输出的内容和格式。

2. 控制日志输出的位置。

3. 日志文件相关的优化，如异步操作、归档、压缩..

4. 日志系统的维护

5. 面向接口开发 – 日志的门面

### 日志框架的价值

因为软件系统发展到了今天非常的复杂，特别是服务器的软件，涉及到的知识和内容问题非常的多。对于日志记录来讲，在某些方面使用别人研发好的成熟的框架，这就相当于让别人帮你完成一些基础的工作。你只需要集中精力去完成业务逻辑就可以了。

比如事务处理，日志记录等一些安全性的问题，我们使用框架去做，不会影响业务的开发效率。

同时框架也是在不断升级的，我们可以不断的享受框架为我们带来的好处。

### 市面流行的日志框架

JUL  java util logging

​    Java原生日志框架，亲儿子

 

Log4j

​    Apache的一个开源项目

 

Logback

​    由Log4j之父做的另一个开源项目

​    业界中称作log4j后浪

​    一个可靠、通用且灵活的java日志框架

 

Log4j2

​    Log4j官方的第二个版本，各个方面都是与Logback及其相似

​    具有插件式结构、配置文件优化等特征

​    Spring Boot1.4版本以后就不再支持log4j，所以第二个版本营运而生

 

JCL

SLF4j

 

### 日志门面和日志框架的区别

日志框架技术 JUL、Logback、Log4j、Log4j2

用来方便有效地记录日志信息

 

日志门面技术 JCL、SLF4j

为什么要使用日志门面技术：

每一种日志框架都有自己单独的API，要使用对应的框架就要使用对应的API，这就大大的增加了应用程序代码对于日志框架的耦合性。

我们使用了日志门面技术之后，对于应用程序来说，无论底层的日志框架如何改变，应用程序不需要修改任意一行代码，就可以直接上线了。

# JUL

## JUL简介

JUL全程 Java Util Logging，它是java原生的日志框架，使用时不需要另外引用第三方的类库，相对其他的框架使用方便，学习简单，主要是使用在小型应用中。 

## JUL组件介绍

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image001.png)

Logger：被称为记录器，应用程序通过获取Logger对象，抵用其API来发布日志信息。Logger通常被认为是访问日志系统的入口程序。

Handler：处理器，每个Logger都会关联一个或者是一组Handler，Logger会将日志交给关联的Handler去做处理，由Handler负责将日志做记录。Handler具体实现了日志的输出位置，比如可以输出到控制台或者是文件中等等。

Filter：过滤器，根据需要定制哪些信息会被记录，哪些信息会被略过。

Formatter：格式化组件，它负责对日志中的数据和信息进行转换和格式化，所以它决定了我们输出日志最终的形式。

Level：日志的输出级别，每条日志消息都有一个关联的级别。我们根据输出级别的设置，用来展现最终所呈现的日志信息。根据不同的需求，去设置不同的级别。

## 实战案例

```java
package com.Han.test;

import org.junit.Test;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.logging.*;

public class JULTest {

    @Test
    public void test01() {

        //入门案例
        /*

            日志入口程序
            java.util.logging.Logger

         */
        //Logger对象的创建方式，不能直接new对象
        //取得对象的方法参数，需要引入当前类的全路径字符串（当前我们先这么用，以后根据包结构有Logger父子关系，以后详细介绍）
        Logger logger = Logger.getLogger("com.bjpowernode.jul.test.JULTest");

        /*

            对于日志的输出，有两种方式

            第一种方式：
                直接调用日志级别相关的方法，方法中传递日志输出信息
                假设现在我们要输出info级别的日志信息


         */
        //logger.info("输出info信息1");
        /*

            第二种方式：
                调用通用的log方法，然后在里面通过Level类型来定义日志的级别参数，以及搭配日志输出信息的参数

         */
        //logger.log(Level.INFO,"输出info信息2");


        /*

            输出学生信息
                姓名
                年龄

         */
        /*String name = "zs";
        int age = 23;
        logger.log(Level.INFO,"学生的姓名为："+name+"；年龄为："+age);*/

        /*

            对于输出消息中，字符串的拼接弊端很多
            1.麻烦
            2.程序效率低
            3.可读性不强
            4.维护成本高

            我们应该使用动态生成数据的方式，生产日志
            我们使用的就是占位符的方式来进行操作

         */

        String name = "zs";
        int age = 23;
        logger.log(Level.INFO, "学生的姓名：{0},年龄:{1}", new Object[]{name, age});


    }

    @Test
    public void test02() {

        /*

            日志的级别（通过源码查看，非常简单）

              SEVERE : 错误 --- 最高级的日志级别
              WARNING : 警告
              INFO : （默认级别）消息
              CONFIG : 配置
              FINE : 详细信息（少）
              FINER : 详细信息（中）
              FINEST : 详细信息 （多） --- 最低级的日志级别

            两个特殊的级别
               OFF 可用来关闭日志记录
               ALL 启用所有消息的日志记录

            对于日志的级别，我们重点关注的是new对象的时候的第二个参数
            是一个数值
            OFF Integer.MAX_VALUE 整型最大值

            SEVERE 1000
            WARNING 900

            ...
            ...

            FINEST 300


            ALL Integer.MIN_VALUE 整型最小值

            这个数值的意义在于，如果我们设置的日志的级别是INFO -- 800
            那么最终展现的日志信息，必须是数值大于800的所有的日志信息
            最终展现的就是
            SEVERE
            WARNING
            INFO


         */

        Logger logger = Logger.getLogger("com.bjpowernode.jul.test.JULTest");

        /*

            通过打印结果，我们看到了仅仅只是输出了info级别以及比info级别高的日志信息
            比info级别低的日志信息没有输出出来
            证明了info级别的日志信息，它是系统默认的日志级别
            在默认日志级别info的基础上，打印比它级别高的信息

         */

        /*

            如果仅仅只是通过以下形式来设置日志级别
            那么不能够起到效果
            将来需要搭配处理器handler共同设置才会生效

         */
        logger.setLevel(Level.CONFIG);

        logger.severe("severe信息");
        logger.warning("warning信息");
        logger.info("info信息");
        logger.config("config信息");
        logger.fine("fine信息");
        logger.finer("finer信息");
        logger.finest("finest信息");

    }

    @Test
    public void test03() {

        /*

            自定义日志的级别

         */
        //日志记录器
        Logger logger = Logger.getLogger("com.bjpowernode.jul.test.JULTest");

        //将默认的日志打印方式关闭掉
        //参数设置为false，我们打印日志的方式就不会按照父logger默认的方式去进行操作
        logger.setUseParentHandlers(false);

        //处理器Handler
        //在此我们使用的是控制台日志处理器，取得处理器对象
        ConsoleHandler handler = new ConsoleHandler();
        //创建日志格式化组件对象
        SimpleFormatter formatter = new SimpleFormatter();

        //在处理器中设置输出格式
        handler.setFormatter(formatter);
        //在记录器中添加处理器
        logger.addHandler(handler);

        //设置日志的打印级别
        //此处必须将日志记录器和处理器的级别进行统一的设置，才会达到日志显示相应级别的效果
        //logger.setLevel(Level.CONFIG);
        //handler.setLevel(Level.CONFIG);

        logger.setLevel(Level.ALL);
        handler.setLevel(Level.ALL);

        logger.severe("severe信息");
        logger.warning("warning信息");
        logger.info("info信息");
        logger.config("config信息");
        logger.fine("fine信息");
        logger.finer("finer信息");
        logger.finest("finest信息");

    }

    @Test
    public void test04() throws IOException {

        /*

            将日志输出到具体的磁盘文件中
            这样做相当于是做了日志的持久化操作

         */
        Logger logger = Logger.getLogger("com.bjpowernode.jul.test.JULTest");
        logger.setUseParentHandlers(false);

        //文件日志处理器
        FileHandler handler = new FileHandler("D:\\test\\myLogTest.log");
        SimpleFormatter formatter = new SimpleFormatter();
        handler.setFormatter(formatter);
        logger.addHandler(handler);

        //也可以同时在控制台和文件中进行打印
        ConsoleHandler handler2 = new ConsoleHandler();
        handler2.setFormatter(formatter);
        logger.addHandler(handler2); //可以在记录器中同时添加多个处理器

        logger.setLevel(Level.ALL);
        handler.setLevel(Level.ALL);
        handler2.setLevel(Level.CONFIG);

        logger.severe("severe信息");
        logger.warning("warning信息");
        logger.info("info信息");
        logger.config("config信息");
        logger.fine("fine信息");
        logger.finer("finer信息");
        logger.finest("finest信息");


        /*

            总结：
                用户使用Logger来进行日志的记录，Logger可以持有多个处理器Handler
                （日志的记录使用的是Logger，日志的输出使用的是Handler）
                添加了哪些handler对象，就相当于需要根据所添加的handler
                将日志输出到指定的位置上，例如控制台、文件..

         */


    }

    @Test
    public void test05() {

        /*

            Logger之间的父子关系
                JUL中Logger之间是存在"父子"关系的
                值得注意的是，这种父子关系不是我们普遍认为的类之间的继承关系
                关系是通过树状结构存储的

                JUL在初始化时会创建一个顶层RootLogger作为所有Logger的父Logger
                查看源码：
                    owner.rootLogger = owner.new RootLogger();
                    RootLogger是LogManager的内部类
                    java.util.logging.LogManager$RootLogger
                    默认的名称为 空串

                以上的RootLogger对象作为树状结构的根节点存在的
                将来自定义的父子关系通过路径来进行关联
                父子关系，同时也是节点之间的挂载关系
                owner.addLogger(owner.rootLogger);
                LoggerContext cx = getUserContext(); //LoggerContext一种用来保存节点的Map关系

                private LogNode               node; //节点

         */

        /*

            从下面创建的两个logger对象看来
            我们可以认为logger1是logger2的父亲

         */

        //父亲是RootLogger，名称默认是一个空的字符串
        //RootLogger可以被称之为所有logger对象的顶层logger
        Logger logger1 = Logger.getLogger("com.bjpowernode.jul.test");

        Logger logger2 = Logger.getLogger("com.bjpowernode.jul.test.JULTest");

        //System.out.println(logger2.getParent()==logger1); //true

        System.out.println("logger1的父Logger引用为:"
                + logger1.getParent() + "; 名称为" + logger1.getName() + "; 父亲的名称为" + logger1.getParent().getName());


        System.out.println("logger2的父Logger引用为:"
                + logger2.getParent() + "; 名称为" + logger2.getName() + "; 父亲的名称为" + logger2.getParent().getName());


        /*

            父亲所做的设置，也能够同时作用于儿子
            对logger1做日志打印相关的设置，然后我们使用logger2进行日志的打印

         */
        //父亲做设置
        logger1.setUseParentHandlers(false);
        ConsoleHandler handler = new ConsoleHandler();
        SimpleFormatter formatter = new SimpleFormatter();
        handler.setFormatter(formatter);
        logger1.addHandler(handler);
        handler.setLevel(Level.ALL);
        logger1.setLevel(Level.ALL);

        //儿子做打印
        logger2.severe("severe信息");
        logger2.warning("warning信息");
        logger2.info("info信息");
        logger2.config("config信息");
        logger2.fine("fine信息");
        logger2.finer("finer信息");
        logger2.finest("finest信息");


    }

    @Test
    public void test06() throws Exception {

        /*

            以上所有的配置相关的操作，都是以java硬编码的形式进行的
            我们可以使用更加清晰，更加专业的一种做法，就是使用配置文件
            如果我们没有自己添加配置文件，则会使用系统默认的配置文件
            这个配置文件：
                owner.readPrimordialConfiguration();
                readConfiguration();
                java.home --> 找到jre文件夹 --> lib --> logging.properties

            做文件日志打印，新日志会覆盖掉原来的日志
            但是我们现在的需求不是覆盖，而是追加


         */

        InputStream input = new FileInputStream("D:\\test\\logging.properties");

        //取得日志管理器对象
        LogManager logManager = LogManager.getLogManager();

        //读取自定义的配置文件
        logManager.readConfiguration(input);

        Logger logger = Logger.getLogger("com.bjpowernode.jul.test.JULTest");

        logger.severe("severe信息");
        logger.warning("warning信息");
        logger.info("info信息");
        logger.config("config信息");
        logger.fine("fine信息");
        logger.finer("finer信息");
        logger.finest("finest信息");

        /*

            JUL日志框架使用方式总结（原理解析）

                1.初始化LogManager
                    LogManager加载logging.properties配置文件
                    添加Logger到LogManager
                2.从单例的LogManager获取Logger
                3.设置日志级别Level，在打印的过程中使用到了日志记录的LogRecord类
                4.Filter作为过滤器提供了日志级别之外更细粒度的控制
                5.Handler日志处理器，决定日志的输出位置，例如控制台、文件...
                6.Formatter是用来格式化输出的


         */


    }


}

```

# Log4j

## Log4j简介

Log4j是[Apache](https://baike.baidu.com/item/Apache/8512995)的一个开源项目，通过使用Log4j，我们可以控制日志信息输送的目的地是[控制台](https://baike.baidu.com/item/控制台/2438626)、文件、[GUI](https://baike.baidu.com/item/GUI)组件，甚至是套接口服务器、[NT](https://baike.baidu.com/item/NT/3443842)的事件记录器、[UNIX](https://baike.baidu.com/item/UNIX) [Syslog](https://baike.baidu.com/item/Syslog)[守护进程](https://baike.baidu.com/item/守护进程/966835)等；我们也可以控制每一条日志的输出格式；通过定义每一条日志信息的级别，我们能够更加细致地控制日志的生成过程。最令人感兴趣的就是，这些可以通过一个[配置文件](https://baike.baidu.com/item/配置文件/286550)来灵活地进行配置，而不需要修改应用的代码。

官方网站： http://logging.apache.org/log4j/1.2/ Log for java

我们使用log4j技术，主要使用的是其配置文件

## Log4j组件介绍

Log4j主要由 Loggers (日志记录器)、Appenders（输出控制器）和 Layout（日志格式化器）组成。其中 Loggers 控制日志的输出以及输出级别(JUL做日志级别Level)；Appenders 指定日志的输出方式（输出到控制台、文件等）；Layout 控制日志信息的输出格式。

- Loggers

	日志记录器，负责收集处理日志记录，实例的命名就是类的全限定名，如com.bjpowernode.log4j.XX， Logger的名字大小写敏感，其命名有继承机制：例如：name为com.bjpowernode.log4j的logger会继承 name为com.bjpowernode。 Log4J中有一个特殊的logger叫做“root”，他是所有logger的根，也就意味着其他所有的logger都会直接 或者间接地继承自root。root logger可以用Logger.getRootLogger()方法获取。自log4j 1.2版以来， Logger 类已经取代了 Category 类。对于熟悉早期版本的log4j的人来说， Logger 类可以被视为 Category 类的别名。

	com.bjpowernode.log4j.XX 儿子

	com.bjpowernode.log4j 父亲

	com.bjpowernode 爷爷

	..

	..

	Root logger

	上辈所做的日志属性设置，会直接的影响到子辈

	关于日志级别信息，例如DEBUG、INFO、WARN、ERROR…级别是分大小的，DEBUG < INFO < WARN < ERROR，分别用来指定这条日志信息的重要程度，Log4j输出日志的规则是：只输出级别不低于设定级别的日志信息，假设Loggers级别设定为INFO，则INFO、WARN、ERROR级别的日志信息都会输出，而级别比INFO低的DEBUG则不会输出。

- Appenders
	记录日志以及定义日志的级别仅仅是Log4j的基本功能，Log4j日志系统还提供许多强大的功能，比如允许把日志输出到不同的地方，如控制台（Console）、文件（Files）等，可以根据天数或者文件大小产生新的文件，可以以流的形式发送到其它地方等等。

	常用Appenders：

	ConsoleAppender 	

	将日志输出到控制台 

	FileAppender 

	将日志输出到文件中 

	DailyRollingFileAppender 

	将日志输出到一个日志文件，并且每天输出到一个新的文件

	RollingFileAppender

	将日志信息输出到一个日志文件，并且指定文件的尺寸，当文件大小达到指定尺寸时，会自动把文件改名，同时产生一个新的文件

	JDBCAppender 

	把日志信息保存到数据库中 

- Layouts

	有时用户希望根据自己的喜好格式化自己的日志输出，Log4j可以在Appenders的后面附加Layouts来完成这个功能。Layouts提供四种日志输出样式，如根据HTML样式、自由指定样式、包含日志级别与信息的样式和包含日志时间、线程、类别等信息的样式。

	常用Layouts:

	HTMLLayout

	格式化日志输出为HTML表格形式 

	SimpleLayout 

	简单的日志输出格式化，打印的日志格式如默认INFO级别的消息

	PatternLayout 

	最强大的格式化组件，可以根据自定义格式输出日志，如果没有指定转换格式， 就是用默认的转换格式

## 日志输出格式说明

使用PatternLayout可以自定义格式输出，是我们最常用的方式

这种格式化输出采用类似于 C 语言的 printf 函数的打印格式格式化日志信息，具体的占位符及其含义如下：

%m 输出代码中指定的日志信息

%p 输出优先级，及 DEBUG、INFO 等

%n 换行符（Windows平台的换行符为 "\n"，Unix 平台为 "\n"）

%r 输出自应用启动到输出该 log 信息耗费的毫秒数

%c 输出打印语句所属的类的全名

%t 输出产生该日志的线程全名

%d 输出服务器当前时间，默认为 ISO8601，也可以指定格式，如：%d{yyyy年MM月dd日 HH:mm:ss}

%l 输出日志时间发生的位置，包括类名、线程、及在代码中的行数。如：Test.main(Test.java:10)

%F 输出日志消息产生时所在的文件名称

%L 输出代码中的行号

%% 输出一个 "%" 字符

可以在 % 与字符之间加上修饰符来控制最小宽度、最大宽度和文本的对其方式。如：

%5c 输出category名称，最小宽度是5，category<5，默认的情况下右对齐

%-5c 输出category名称，最小宽度是5，category<5，"-"号指定左对齐,会有空格

%.5c 输出category名称，最大宽度是5，category>5，就会将左边多出的字符截掉，<5不会有空格

%20.30c category名称<20补空格，并且右对齐，>30字符，就从左边交远销出的字符截掉

## 1.4 案例解析

```java
package com.bjpowernode.log4j.test;

import org.apache.log4j.*;
import org.apache.log4j.helpers.LogLog;
import org.apache.log4j.jdbc.JDBCAppender;
import org.junit.Test;

public class Log4jTest01 {

    @Test
    public void test01() {

        /*

            Log4j入门案例
                注意加载初始化信息：BasicConfigurator.configure();

            日志级别说明：
                Log4j提供了8个级别的日志输出，分别为
                ALL 最低等级 用于打开所有级别的日志记录
                TRACE 程序推进下的追踪信息，这个追踪信息的日志级别非常低，一般情况下是不会使用的
                DEBUG 指出细粒度信息事件对调试应用程序是非常有帮助的，主要是配合开发，在开发过程中打印一些重要的运行信息
                INFO 消息的粗粒度级别运行信息
                WARN 表示警告，程序在运行过程中会出现的有可能会发生的隐形的错误
                        注意，有些信息不是错误，但是这个级别的输出目的就是为了给程序员以提示
                ERROR 系统的错误信息，发生的错误不影响系统的运行
                        一般情况下，如果不想输出太多的日志，则使用该级别即可
                FATAL 表示严重错误，它是那种一旦发生系统就不可能继续运行的严重错误
                        如果这种级别的错误出现了，表示程序可以停止运行了
                OFF 最高等级的级别，用户关闭所有的日志记录

                其中debug是我们在没有进行设置的情况下，默认的日志输出级别



         */

        //加载初始化配置
        BasicConfigurator.configure();
        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }


    @Test
    public void test02() {

        /*

            配置文件的使用
                1.观察源码BasicConfigurator.configure();
                    可以得到两条信息：
                    （1）创建了根节点的对象，Logger root = Logger.getRootLogger();
                    （2）根节点添加了ConsoleAppender对象（表示默认打印到控制台，自定义的格式化输出）

                2.我们这一次，不使用BasicConfigurator.configure();
                    使用自定义的配置文件来实现功能
                    通过我们对于以上第一点的分析
                    我们的配置文件需要提供Logger、Appender、Layout这3个组件信息（通过配置来代替以上的代码）

                    分析：
                    Logger logger = Logger.getLogger(Log4jTest01.class);

                    进入到getLogger方法，会看到代码：
                    LogManager.getLogger(clazz.getName());
                    LogManager：日志管理器

                    点击LogManager，看看这个日志管理器中都实现了什么
                    看到很多常量信息，他们代表的就是不同形式（后缀名不同）的配置文件
                    我们最常使用到的肯定是log4j.properties属性文件（语法简单，使用方便）

                    问题：log4j.properties的加载时机
                    继续观察LogManager，找到其中的静态代码块static
                    在static代码块中，我们找到
                    Loader.getResource("log4j.properties");
                    这行代码给我们最大的一个提示信息就是
                    系统默认要从当前的类路径下找到log4j.properties
                    对于我们当前的项目是maven工程，那么理应在resources路径下去找

                    加载完毕后我们来观察配置文件是如何读取的？
                    继续观察LogManager
                    找到
                    OptionConverter.selectAndConfigure(url, configuratorClassName, getLoggerRepository());
                    作为属性文件的加载，执行相应的properties配置对象：configurator = new PropertyConfigurator();

                    进入到PropertyConfigurator类中，观察到里面的常量信息
                    这些常量信息就是我们在properties属性文件中的各种属性配置项
                    其中，我们看到了如下两项信息，这两项信息是必须要进行配置的
                    static final String ROOT_LOGGER_PREFIX = "log4j.rootLogger";
                    static final String APPENDER_PREFIX = "log4j.appender.";

                    通过代码：
                    String prefix = "log4j.appender." + appenderName;
                    我们需要自定义一个appendername，我们起名叫做console
                    （起名字也需要见名知意，console那么我们到时候的配置应该配置的就是控制台输出）
                    log4j.appender.console
                    取值就是log4j中为我们提供的appender类
                    例如：
                        log4j.appender.console=org.apache.log4j.ConsoleAppender


                    在appender输出的过程中，还可以同时指定输出的格式
                    通过代码：
                    String layoutPrefix = prefix + ".layout";
                    配置：
                    log4j.appender.console.layout=org.apache.log4j.SimpleLayout

                    通过log4j.rootLogger继续在类中搜索
                    找到void configureRootCategory方法
                    在这个方法中执行了this.parseCategory方法
                    观察该方法：
                    找打代码StringTokenizer st = new StringTokenizer(value, ",");
                    表示要以逗号的方式来切割字符串，证明了log4j.rootLogger的取值，其中可以有多个值，使用逗号进行分隔

                    通过代码：
                    String levelStr = st.nextToken();
                    表示切割后的第一个值是日志的级别

                    通过代码：
                    while(st.hasMoreTokens())
                    表示接下来的值，是可以通过while循环遍历得到的
                    第2~第n个值，就是我们配置的其他的信息，这个信息就是appenderName
                    证明了我们配置的方式
                    log4j.rootLogger=日志级别,appenderName1,appenderName2,appenderName3....
                    表示可以同时在根节点上配置多个日志输出的途径

                    通过我们自己的配置文件，就可以将原有的加载代码去除掉了


         */

        //BasicConfigurator.configure();

        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");

    }

    @Test
    public void test03() {

        /*

            通过Logger中的开关
                打开日志输出的详细信息
                查看LogManager类中的方法
                getLoggerRepository()
                找到代码LogLog.debug(msg, ex);
                LogLog会使用debug级别的输出为我们展现日志输出详细信息
                Logger是记录系统的日志，那么LogLog是用来记录Logger的日志

                进入到LogLog.debug(msg, ex);方法中
                通过代码：if (debugEnabled && !quietMode) {
                观察到if判断中的这两个开关都必须开启才行
                !quietMode是已经启动的状态，不需要我们去管
                debugEnabled默认是关闭的
                所以我们只需要设置debugEnabled为true就可以了


         */

        LogLog.setInternalDebugging(true);

        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }

    @Test
    public void test04() {

        /*

            关于log4j.properties layout属性的配置
                其中PatternLayout是日常使用最多的方式
                查看其源码
                setConversionPattern这个方法就是该PatternLayout的核心方法
                conversionPattern

                在log4j.properties中将layout设置为PatternLayout
                我们主要配置的是conversionPattern属性

                %m 输出代码中指定的日志信息
                %p 输出优先级，及 DEBUG、INFO 等
                %n 换行符（Windows平台的换行符为 "\n"，Unix 平台为 "\n"）
                %r 输出自应用启动到输出该 log 信息耗费的毫秒数
                %c 输出打印语句所属的类的全名
                %t 输出产生该日志的线程全名
                %d 输出服务器当前时间，默认为 ISO8601，也可以指定格式，如：%d{yyyy年MM月dd日 HH:mm:ss}
                %l 输出日志时间发生的位置，包括类名、线程、及在代码中的行数。如：Test.main(Test.java:10)
                %F 输出日志消息产生时所在的文件名称
                %L 输出代码中的行号
                %% 输出一个 "%" 字符
                [%p]%r %c%t%d{yyyy-MM-dd HH:mm:ss:SSS} %m%n
                可以在 % 与字符之间加上修饰符来控制最小宽度、最大宽度和文本的对其方式
                [%10p]：[]中必须有10个字符，由空格来进行补齐，信息右对齐
                [%-10p]：[]中必须有10个字符，由空格来进行补齐，信息左对齐，应用较广泛


         */

        LogLog.setInternalDebugging(true);

        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }

    @Test
    public void test05() {

        /*

            将日志信息输出到文件中（以后所有的练习统一使用配置文件（不硬编码））

            之前我们在配置文件中配置的是输出到控制台相关的配置
            那么我们可以直接将输出到控制台改变为输出到文件中
            一般情况下我们也可以做多方向的输出，所以控制台的配置我们保留，但是可以选择不用
            我们可以完全再来一套关于输出到文件的配置

            日志文件要保存到哪个磁盘相关的配置
            查看FileAppender的源码
            看到属性信息
            protected boolean fileAppend; 表示是否追加信息，通过构造方法赋值为true
            protected int bufferSize; 缓冲区的大小，通过构造方法赋值为8192

            继续观察，找到setFile方法，这个方法就是用来指定文件位置的方法
            通过ognl，可以推断setFile方法操作的属性就是file

            如果有输出中文的需求怎么办
            观察FileAppender的父类
            找到protected String encoding;属性


         */
        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }

    @Test
    public void test06() {

        /*

            将日志输出到文件中
               日志太多了，不方便管理和维护怎么办
               FileAppender为我们提供了好用的子类来进一步的对于文件输出进行处理
               RollingFileAppender
               DailyRollingFileAppender


            1.先来学习RollingFileAppender
                这个类表示使用按照文件大小进行拆分的方式进行操作
                配置文件进行RollingFileAppender相关配置

                如何进行拆分，观察RollingFileAppender的源码
                protected long maxFileSize = 10485760L; 表示拆分文件的大小
                protected int maxBackupIndex = 1; 表示拆分文件的数量

                #指定日志文件内容大小
                log4j.appender.rollingFile.maxFileSize=1MB
                #指定日志文件的数量
                log4j.appender.rollingFile.maxBackupIndex=5

                只要文件超过1MB，那么则生成另外一个文件，文件的数量最多是5个
                文件1 记录日志 1MB
                文件2 记录日志 1MB
                ...
                ...
                文件5         1MB

                如果5个文件不够怎么办，作为日志管理来讲，也不可能让日志无休止的继续增长下去
                所以，覆盖文件的策略是，按照时间来进行覆盖，原则就是保留新的，覆盖旧的

            2.DailyRollingFileAppender
                按照时间来进行文件的拆分
                查看源码属性：
                private String datePattern = "'.'yyyy-MM-dd"; 默认是按照天来进行拆分的

                注意：
                    我们在练习的时候，可以根据秒来制定拆分策略
                    但是实际生产环境中，根据秒生成日志文件是绝对不可能的
                    如果是大型的项目，可以根据天进行拆分
                    或者如果是小型的项目，可以根据周，月进行拆分

         */

        Logger logger = Logger.getLogger(Log4jTest01.class);

        for (int i = 0; i < 10000; i++) {

            logger.fatal("fatal信息");
            logger.error("error信息");
            logger.warn("warn信息");
            logger.info("info信息");
            logger.debug("debug信息");
            logger.trace("trace信息");

        }

    }

    @Test
    public void test07() {

        /*

            将日志持久化到数据库表中

                创建表结构：（字段的制定可以根据需求进行调整）

                CREATE TABLE tbl_log(

                    id int(11) NOT NULL AUTO_INCREMENT,
                    name varchar(255) DEFAULT NULL COMMENT '项目名称',
                    createTime varchar(255) DEFAULT NULL COMMENT '创建时间',
                    level varchar(255) DEFAULT NULL COMMENT '日志级别',
                    category varchar(255) DEFAULT NULL COMMENT '所在类的全路径',
                    fileName varchar(255) DEFAULT NULL COMMENT '文件名称',
                    message varchar(255) DEFAULT NULL COMMENT '日志消息',
                    PRIMARY KEY(id)

                )

            对于数据库表的日志输出进行相应配置
            #配置appender输出方式 输出到数据库表
            log4j.appender.logDB=org.apache.log4j.jdbc.JDBCAppender
            log4j.appender.logDB.layout=org.apache.log4j.PatternLayout
            log4j.appender.logDB.Driver=com.mysql.jdbc.Driver
            log4j.appender.logDB.URL=jdbc:mysql://localhost:3306/test
            log4j.appender.logDB.User=root
            log4j.appender.logDB.Password=123456
            log4j.appender.logDB.Sql=INSERT INTO tbl_log(name,createTime,level,category,fileName,message) values('project_log','%d{yyyy-MM-dd HH:mm:ss}','%p','%c','%F','%m')


         */

        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }

    @Test
    public void test08() {

        /*

            Log4j的自定义logger

                我们以前所创建出来的Logger对象，默认都是继承rootLogger的
                我们也可以自定义logger，让其他logger来继承这个logger

                这种继承关系就是按照包结构的关系来进行指定的
                例如我们一直使用的
                Logger logger = Logger.getLogger(Log4jTest01.class);
                路径就是：com.bjpowernode.log4j.test.Log4jTest01
                它的父logger就是上层的路径或者是更上层的路径
                例如：
                    com.bjpowernode.log4j.test
                    com.bjpowernode.log4j
                    ...
                    com

                参照logger是如何加载配置文件的
                查看PropertyConfigurator的源码
                得到信息log4j.logger.
                这个属性值log4j.logger.就是我们在配置文件中对于自定义logger的配置属性

                假设我们现在的配置是这样的：

                #配置根节点logger
                log4j.rootLogger=trace,console

                #配置自定义logger
                log4j.logger.com.bjpowernode.log4j.test=info,file

                观察结果：
                    从输出位置来看，控制台输出了信息，日志文件也输出了信息
                    所以可以得出结论，如果根节点的logger和自定义父logger配置的输出位置是不同的
                    则取二者的并集，配置的位置都会进行输出操作

                    如果二者配置的日志级别不同，以按照我们自定的父logger的级别输出为主


         */

        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");


    }

    @Test
    public void test09() {

        /*

            自定义logger的应用场景

                我们之所以要自定义logger，就是为了针对不同系统信息做更加灵活的输出操作
                例如：
                    我们可以在原有案例的基础之上，加上一个apache的日志输出
                    log4j.logger.org.apache=error,console

                    我们现在在配置文件中配置的logger有如下3项

                    log4j.rootLogger=trace,console
                    log4j.logger.com.bjpowernode.log4j.test=info,file
                    log4j.logger.org.apache=error,console


         */

        /*

            当前的类路径com.bjpowernode.log4j.test.Log4jTest01
            在配置文件中所找到的能够作用的父logger和根logger
            log4j.rootLogger=trace,console
            log4j.logger.com.bjpowernode.log4j.test=info,file

            我们刚才配置的apache的路径和我们的com.bjpowernode.log4j.test.Log4jTest01不相符
            不构成父子关系，所以没有执行apache相关的配置

         */
        Logger logger = Logger.getLogger(Log4jTest01.class);

        logger.fatal("fatal信息");
        logger.error("error信息");
        logger.warn("warn信息");
        logger.info("info信息");
        logger.debug("debug信息");
        logger.trace("trace信息");

        /*

            org.apache.log4j.Logger

                console在根节点中进行了配置
                在apache中也进行了配置
                由于输出的位置appender取的是并集
                所以，既然都配置了，那么就输出了两次

         */
        Logger logger1 = Logger.getLogger(Logger.class);

        logger1.fatal("fatal信息 --");
        logger1.error("error信息 --");
        logger1.warn("warn信息 --");
        logger1.info("info信息 --");
        logger1.debug("debug信息 --");
        logger1.trace("trace信息 --");


    }


}
```

配置文件

```properties
#配置根节点logger
log4j.rootLogger=trace,console

#配置自定义logger
log4j.logger.com.bjpowernode.log4j.test=info,file

#配置apache的logger
log4j.logger.org.apache=error

#配置appender输出方式 输出到控制台
log4j.appender.console=org.apache.log4j.ConsoleAppender
#配置输出到控制台的格式
log4j.appender.console.layout=org.apache.log4j.PatternLayout
log4j.appender.console.layout.conversionPattern=[%-10p]%r %c%t%d{yyyy-MM-dd HH:mm:ss:SSS} %m%n

#配置appender输出方式 输出到文件
log4j.appender.file=org.apache.log4j.FileAppender
#配置输出到文件中的格式
log4j.appender.file.layout=org.apache.log4j.PatternLayout
log4j.appender.file.layout.conversionPattern=[%-10p]%r %c%t%d{yyyy-MM-dd HH:mm:ss:SSS} %m%n
#第一个file是我们自己命名的appenderName，第二个file是用来指定文件位置的属性
log4j.appender.file.file=D://test//log4j.log
#配置输出字符编码
log4j.appender.file.encoding=UTF-8


#RollingFileAppender的配置，我们可以针对于实际含义起名
log4j.appender.rollingFile=org.apache.log4j.RollingFileAppender
log4j.appender.rollingFile.layout=org.apache.log4j.PatternLayout
log4j.appender.rollingFile.layout.conversionPattern=[%-10p]%r %c%t%d{yyyy-MM-dd HH:mm:ss:SSS} %m%n
log4j.appender.rollingFile.file=D://test//log4j.log
log4j.appender.rollingFile.encoding=UTF-8
#指定日志文件内容大小
log4j.appender.rollingFile.maxFileSize=1MB
#指定日志文件的数量
log4j.appender.rollingFile.maxBackupIndex=5


#DailyRollingFileAppender的配置，我们可以针对于实际含义起名
log4j.appender.dailyRollingFile=org.apache.log4j.DailyRollingFileAppender
log4j.appender.dailyRollingFile.layout=org.apache.log4j.PatternLayout
log4j.appender.dailyRollingFile.layout.conversionPattern=[%-10p]%r %c%t%d{yyyy-MM-dd HH:mm:ss:SSS} %m%n
log4j.appender.dailyRollingFile.file=D://test//log4j.log
log4j.appender.dailyRollingFile.encoding=UTF-8
log4j.appender.dailyRollingFile.datePattern='.'yyyy-MM-dd HH-mm-ss

#配置appender输出方式 输出到数据库表
log4j.appender.logDB=org.apache.log4j.jdbc.JDBCAppender
log4j.appender.logDB.layout=org.apache.log4j.PatternLayout
log4j.appender.logDB.Driver=com.mysql.jdbc.Driver
log4j.appender.logDB.URL=jdbc:mysql://localhost:3306/test
log4j.appender.logDB.User=root
log4j.appender.logDB.Password=123456
log4j.appender.logDB.Sql=INSERT INTO tbl_log(name,createTime,level,category,fileName,message) values('project_log','%d{yyyy-MM-dd HH:mm:ss}','%p','%c','%F','%m')

```

# JCL

## JCL简介

全称为Jakarta Commons Logging，是Apache提供的一个**通用日志API**。

用户可以自由选择第三方的日志组件作为具体实现，像log4j，或者jdk自带的jul， common-logging会通过动态查找的机制，在程序运行时自动找出真正使用的日志库。

当然，common-logging内部有一个Simple logger的简单实现，但是功能很弱。所以使用common-logging，通常都是配合着log4j以及其他日志框架来使用。

使用它的好处就是，代码依赖是common-logging而非log4j的API， 避免了和具体的日志API直接耦合，在有必要时，可以更改日志实现的第三方库。

JCL 有两个基本的抽象类：

Log：日志记录器

LogFactory：日志工厂（负责创建Log实例）

## JCL案例

新建maven项目

添加依赖

<dependency>

  <groupId>commons-logging</groupId>

  <artifactId>commons-logging</artifactId>

  <version>1.2</version>

</dependency>

<dependency>
   <groupId>junit</groupId>
   <artifactId>junit</artifactId>
   <version>4.12</version>
 </dependency>

设置jdk版本

<build>

​    <plugins>

​      <!-- 设置编译版本为1.8 -->

​      <plugin>

​        <groupId>org.apache.maven.plugins</groupId>

​        <artifactId>maven-compiler-plugin</artifactId>

​        <version>3.1</version>

​        <configuration>

​          <source>1.8</source>

​          <target>1.8</target>

​          <encoding>UTF-8</encoding>

​        </configuration>

​      </plugin>

​    </plugins>

</build>

</build>

## JCL组件结构

![image-20210727195350075](/Users/hwl/Documents/Markdown/%E6%80%BB%E7%BB%93/%E5%90%8E%E7%AB%AF/%E6%A1%86%E6%9E%B6/Java%E6%97%A5%E5%BF%97%E6%A1%86%E6%9E%B6/image/image-20210727195350075.png)

# SLF4J

## 日志门面概述

### 门面模式（外观模式）

我们先谈一谈GoF23种设计模式其中之一。

门面模式（Facade Pattern），也称之为外观模式，其核心为：外部与一个子系统的通信必须通过一个统一的外观对象进行，使得子系统更易于使用。

外观模式主要是体现了Java中的一种好的封装性。更简单的说，就是对外提供的接口要尽可能的简单。

### 日志门面

前面介绍的几种日志框架，每一种日志框架都有自己单独的API，要使用对应的框架就要使用其对应的API，这就大大的增加应用程序代码对于日志框架的耦合性。

为了解决这个问题，就是在日志框架和应用程序之间架设一个沟通的桥梁，对于应用程序来说，无论底层的日志框架如何变，都不需要有任何感知。只要门面服务做的足够好，随意换另外一个日志框架，应用程序不需要修改任意一行代码，就可以直接上线。

### 常见的日志框架及日志门面

常见的日志实现：JUL、log4j、logback、log4j2

常见的日志门面 ：JCL、slf4j

出现顺序 ：log4j -->JUL-->JCL--> slf4j --> logback --> log4j2

## SLF4J

### SLF4J简介

简单日志门面(Simple Logging Facade For Java) SLF4J主要是为了给Java日志访问提供一套标准、规范的API框架，其主要意义在于提供接口，具体的实现可以交由其他日志框架，例如log4j和logback等。 当然slf4j自己也提供了功能较为简单的实现，但是一般很少用到。对于一般的Java项目而言，日志框架会选择slf4j-api作为门面，配上具体的实现框架（log4j、logback等），中间使用桥接器完成桥接。所以我们可以得出SLF4J最重要的两个功能就是对于日志框架的绑定以及日志框架的桥接。

官方网站： https://www.slf4j.org/

### SLF4J桥接技术

通常，我们依赖的某些组件依赖于SLF4J以外的日志API。我们可能还假设这些组件在不久的将来不会切换到SLF4J。为了处理这种情况，SLF4J附带了几个桥接模块，这些模块会将对log4j，JCL和java.util.logging API的调用重定向为行为，就好像是对SLF4J API进行的操作一样。

### SLF4J案例实现

创建Maven工程，导入依赖

<!--slf4j 核心依赖-->

<dependency>

<groupId>org.slf4j</groupId>

<artifactId>slf4j-api</artifactId>

<version>1.7.25</version>

</dependency>

<!--slf4j 自带的简单日志实现 -->

<dependency>

<groupId>org.slf4j</groupId>

<artifactId>slf4j-simple</artifactId>

<version>1.7.25</version>

</dependency>

设置jdk版本

<build>

​    <plugins>

​      <!-- 设置编译版本为1.8 -->

​      <plugin>

​        <groupId>org.apache.maven.plugins</groupId>

​        <artifactId>maven-compiler-plugin</artifactId>

​        <version>3.1</version>

​        <configuration>

​          <source>1.8</source>

​          <target>1.8</target>

​          <encoding>UTF-8</encoding>

​        </configuration>

​      </plugin>

​    </plugins>

</build>

 

# 第六章 Logback

## Logback简介

Logback是由[log4j](https://baike.baidu.com/item/log4j)创始人设计的又一个开源日志组件。

Logback当前分成三个模块：logback-core,logback- classic和logback-access。

logback-core是其它两个模块的基础模块。

logback-classic是log4j的一个改良版本。此外logback-classic完整实现SLF4J API。使你可以很方便地更换成其它日志系统如log4j或JDK14 Logging。

logback-access访问模块与[Servlet](https://baike.baidu.com/item/Servlet/477555)容器集成提供通过Http来访问日志的功能。

## Logback中的组件

Logger: 日志的记录器，主要用于存放日志对象，也可以定义日志类型、级别。 

Appender:用于指定日志输出的目的地，目的地可以是控制台、文件、数据库等等。

Layout: 负责把事件转换成字符串，格式化的日志信息的输出。

在Logback中Layout对象被封装在encoder中。

也就是说我们未来使用的encoder其实就是Layout

## Logback配置文件

Logback提供了3种配置文件

logback.groovy 

logback-test.xml 

logback.xml

如果都不存在则采用默认的配置

## 日志输出格式

日志输出格式：
   %-10level 级别 案例为设置10个字符，左对齐
   %d{yyyy-MM-dd HH:mm:ss.SSS} 日期
   %c 当前类全限定名
   %M 当前执行日志的方法
   %L 行号
   %thread 线程名称
   %m或者%msg  信息
   %n 换行

## 案例实现

导入依赖

<dependency>
   <groupId>org.slf4j</groupId>
   <artifactId>slf4j-api</artifactId>
   <version>1.7.25</version>
 </dependency>

<dependency>
   <groupId>ch.qos.logback</groupId>
   <artifactId>logback-classic</artifactId>
   <version>1.2.3</version>
 </dependency>

<dependency>
   <groupId>junit</groupId>
   <artifactId>junit</artifactId>
   <version>4.12</version>
 </dependency>

 

设置jdk版本

<build>      <plugins>          <!-- 设置编译版本为1.8 -->          <plugin>              <groupId>org.apache.maven.plugins</groupId>              <artifactId>maven-compiler-plugin</artifactId>              <version>3.1</version>              <configuration>                  <source>1.8</source>                  <target>1.8</target>                  <encoding>UTF-8</encoding>              </configuration>          </plugin>      </plugins>  </build>

 

# Log4j2

## Log4j2简介

Apache Log4j 2是对Log4j的升级，它比其前身Log4j 1.x提供了重大改进，并提供了Logback中可用的许多改进，同时修复了Logback架构中的一些问题。被誉为是目前最优秀的Java日志框架。

## Log4j2特征

**性能提升**

Log4j2包含基于LMAX Disruptor库的下一代异步记录器。在多线程场景中，异步记录器的吞吐量比Log4j 1.x和Logback高18倍，延迟低。

 

**自动重新加载配置**

与Logback一样，Log4j2可以在修改时自动重新加载其配置。与Logback不同，它会在重新配置发生时不会丢失日志事件。

 

**高级过滤**

与Logback一样，Log4j2支持基于Log事件中的上下文数据，标记，正则表达式和其他组件进行过滤。

此外，过滤器还可以与记录器关联。与Logback不同，Log4j2可以在任何这些情况下使用通用的Filter类。

 

**插件架构**

Log4j使用插件模式配置组件。因此，您无需编写代码来创建和配置Appender，Layout，Pattern Converter等。在配置了的情况下，Log4j自动识别插件并使用它们。

 

**无垃圾机制**

在稳态日志记录期间，Log4j2 在独立应用程序中是无垃圾的，在Web应用程序中是低垃圾。这减少了垃圾收集器的压力，并且可以提供更好的响应性能。

目前市面上最主流的日志门面就是SLF4J，虽然Log4j2 也是日志门面，因为它的日志实现功能非常强大，性能优越。所以我们一般情况下还是将 Log4j2 看作是日志的实现

SLF4j + Log4j2 的组合，是市场上最强大的日志功能实现方式，绝对是未来的主流趋势。

## 案例实现

导入依赖

```
<dependency>

    <groupId>org.apache.logging.log4j</groupId>

    <artifactId>log4j-api</artifactId>

    <version>2.12.1</version>

</dependency>

<dependency>

    <groupId>org.apache.logging.log4j</groupId>

    <artifactId>log4j-core</artifactId>

    <version>2.12.1</version>

</dependency>
```

设置jdk版本

<build>      <plugins>          <!-- 设置编译版本为1.8 -->          <plugin>              <groupId>org.apache.maven.plugins</groupId>              <artifactId>maven-compiler-plugin</artifactId>              <version>3.1</version>              <configuration>                  <source>1.8</source>                  <target>1.8</target>                  <encoding>UTF-8</encoding>              </configuration>          </plugin>      </plugins>  </build>

 

## 异步日志

异步日志是log4j2最大的特色，其性能的提升主要也是从异步日志中受益。

Log4j2提供了两种实现日志的方式，一个是通过AsyncAppender，一个是通过AsyncLogger，分别对应前面我们说的Appender组件和Logger组件。

  注意这是两种不同的实现方式，在设计和源码上都是不同的体现。

 

**AsyncAppender方式**

是通过引用别的Appender来实现的，当有日志事件到达时，会开启另外一个线程来处理它们。需要注意的是，如果在Appender的时候出现异常，对应用来说是无法感知的。 AsyncAppender应该在它引用的Appender之后配置，默认使用 java.util.concurrent.ArrayBlockingQueue实现而不需要其它外部的类库。 当使用此Appender的时候，在多线程的环境下需要注意，阻塞队列容易受到锁争用的影响，这可能会对性能产生影响。这时候，我们应该考虑使用无锁的异步记录器（AsyncLogger）。


​    **AsyncLogger方式**

AsyncLogger才是log4j2实现异步最重要的功能体现，也是官方推荐的异步方式。

它可以使得调用Logger.log返回的更快。你可以有两种选择：全局异步和混合异步。

全局异步：所有的日志都异步的记录，在配置文件上不用做任何改动，只需要在jvm启动的时候增加一个参数即可实现。

混合异步：你可以在应用中同时使用同步日志和异步日志，这使得日志的配置方式更加灵活。虽然Log4j2提供以一套异常处理机制，可以覆盖大部分的状态，但是还是会有一小部分的特殊情况是无法完全处理的，比如我们如果是记录审计日志（特殊情况之一），那么官方就推荐使用同步日志的方式，而对于其他的一些仅仅是记录一个程序日志的地方，使用异步日志将大幅提升性能，减少对应用本身的影响。

混合异步的方式需要通过修改配置文件来实现，使用AsyncLogger标记配置。

​    性能对比：

​    ![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image002.png)

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image003.png)

# Spring Boot 日志实现

SpringBoot是现今市场上最火爆用来简化spring开发的框架，springboot日志也是开发中常用的日志系统。

SpringBoot 默认就是使用SLF4J作为日志门面，Logback作为日志实现来记录日志。

​    我们直接创建一个springboot的项目

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image004.png)

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image005.png)

 

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image006.png)

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image007.png)

 

接下来我们来找到项目核心配置文件pom.xml

 

我们会看到有springboot web启动器

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image008.png)

在这个web启动器中间接依赖着日志相关的依赖slf4j和logback

接下来我们来观察maven的依赖关系图

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image009.png)

会观察到

![img](file:////Users/hwl/Library/Group%20Containers/UBF8T346G9.Office/TemporaryItems/msohtmlclip/clip_image010.png)

以此证明日志使用的就是slf4j日志门面技术

 