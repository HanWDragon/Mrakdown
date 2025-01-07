# 核心异常类

![](image/Pasted%20image%2020241213072514.png)
# Throwable 类的重要方法

![](image/Pasted%20image%2020241213073523.png)

```java
// 四个构造方法

 public Throwable() {  
    fillInStackTrace();  
}

public Throwable(String message) {  
    fillInStackTrace();  
    detailMessage = message;  
}

public Throwable(String message, Throwable cause) {  
    fillInStackTrace();  
    detailMessage = message;  
    this.cause = cause;  
}

public Throwable(Throwable cause) {  
    fillInStackTrace();  
    detailMessage = (cause==null ? null : cause.toString());  
    this.cause = cause;  
}

// 重要方法

public String getMessage() {  
    return detailMessage;  
}

// 这个可以自定义要打印的消息
public String getLocalizedMessage() {  
    return getMessage();  
}

public String toString() {  
    String s = getClass().getName();  
    String message = getLocalizedMessage();  
    return (message != null) ? (s + ": " + message) : s;  
}

public void printStackTrace() {  
    printStackTrace(System.err);  
}  
  
/**  
 * Prints this throwable and its backtrace to the specified print stream. * * @param s {@code PrintStream} to use for output  
 */
 public void printStackTrace(PrintStream s) {  
    printStackTrace(new WrappedPrintStream(s));  
}  
  
private void printStackTrace(PrintStreamOrWriter s) {  
    // Guard against malicious overrides of Throwable.equals by  
    // using a Set with identity equality semantics.   
    Set<Throwable> dejaVu = Collections.newSetFromMap(new IdentityHashMap<>());  
    dejaVu.add(this);  
  
    synchronized (s.lock()) {  
        // Print our stack trace  
        s.println(this);  
        StackTraceElement[] trace = getOurStackTrace();  
        for (StackTraceElement traceElement : trace)  
            s.println("\tat " + traceElement);  
  
        // Print suppressed exceptions, if any  
        for (Throwable se : getSuppressed())  
            se.printEnclosedStackTrace(s, trace, SUPPRESSED_CAPTION, "\t", dejaVu);  
  
        // Print cause, if any  
        Throwable ourCause = getCause();  
        if (ourCause != null)  
            ourCause.printEnclosedStackTrace(s, trace, CAUSE_CAPTION, "", dejaVu);  
    }  
}
public StackTraceElement[] getStackTrace() {  
    return getOurStackTrace().clone();  
}

private synchronized StackTraceElement[] getOurStackTrace() {  
    // Initialize stack trace field with information from  
    // backtrace if this is the first call to this method    
    if (stackTrace == UNASSIGNED_STACK ||  
        (stackTrace == null && backtrace != null) /* Out of protocol state */) {  
        stackTrace = StackTraceElement.of(this, depth);  
    } else if (stackTrace == null) {  
        return UNASSIGNED_STACK;  
    }  
    return stackTrace;  
}
```

# 正确理解 Java 虚拟机堆栈

![](image/Pasted%20image%2020241213075218.png)

## 栈的基本性质

- 默认大小 1MB
- 线程私有

![](image/Pasted%20image%2020241213075311.png)

## 堆的基本性质

![](image/Pasted%20image%2020241213075509.png)

## 可能遇到的异常

- 申请线程过多也会 OOM
- 堆栈是指栈

![](image/Pasted%20image%2020241213075739.png)

# 如何完整打印异常堆栈信息

- 省略是为了节省性能，可以查看 Throwable 的 printEnclosedStackTrace
	- 过程是回调输入堆栈信息，相同的省略了
- 要打印出来实现 UncaughtExceptionHandler 接口，然后注册到线程
- 阅读异常堆栈倒着看
	- 最开始是异常真正发生的地方
	- 往后看 Caused by，后面是异常名，紧接着就是方法名
	- at 开头是路径

![](image/Pasted%20image%2020241213075946.png)

## 代码

```java
/**
 * <h1>想办法打印完整的异常栈信息</h1>
 * */
public class CompleteException {

    private void imooc1() throws Exception {
        throw new Exception("imooc1 has exception...");
    }

    private void imooc2() throws Exception {

        try {
            imooc1();
        } catch (Exception ex) {
            throw new Exception("imooc2 has exception...", ex);
        }
    }

    private void imooc3() {
        try {
            imooc2();
        } catch (Exception ex) {
            throw new RuntimeException("imooc3 has exception...", ex);
        }
    }

    public static void main(String[] args) {

//        try {
//            new CompleteException().imooc3();
//        } catch (Exception ex) {
//            ex.printStackTrace();
//        }

        Thread.setDefaultUncaughtExceptionHandler(new ExceptionHandler());
        new CompleteException().imooc3();
    }
}

```

```java
/**
 * <h1>异常捕捉</h1>
 * */
public class ExceptionHandler implements Thread.UncaughtExceptionHandler {

    @Override
    public void uncaughtException(Thread t, Throwable e) {

        StackTraceElement[] ses = e.getStackTrace();
        System.err.println("Exception in thread \"" + t.getName() + "\" " + e.toString());

        for (StackTraceElement se : ses) {
            System.err.println("\tat " + se);
        }

        Throwable ec = e.getCause();
        if (null != ec) {
            uncaughtException(t, ec);
        }
    }
}

```

# 异常处理的两种方式

## 声明异常

![](image/Pasted%20image%2020241213082032.png)

### 代码

```java
/**
 * <h1>方式一: 声明异常</h1>
 * throw, throws
 * */
public class DeclareException {

    /**
     * <h2>使用 throw 关键字抛出运行时异常</h2>
     * */
    private static boolean validate01(String name) {

        if (null == name) {
            throw new NullPointerException("name is null...");
        }

        return "qinyi".equals(name);
    }

    /**
     * <h2>编译期异常, 必须处理这个异常, 或者是由 throws 继续抛出给上层调用者处理</h2>
     * */
    private static void validate02(String name) throws EOFException,
            FileNotFoundException {

        if (null == name) {
            throw new EOFException("name is null...");
        }

        if (!"qinyi".equals(name)) {
            throw new FileNotFoundException("name is not qinyi...");
        }
    }
}

```

## 捕获异常

![](image/Pasted%20image%2020241213082605.png)

### 代码

```java
/**
 * <h1>方式2: 捕获异常</h1>
 * try...catch...finally
 * */
@SuppressWarnings("all")
public class CatchException {

    /**
     * <h2>validate01 抛出单个异常</h2>
     * */
    private static boolean validate01(String name) {

        if (null == name) {
            throw new NullPointerException("name is null...");
        }

        return "qinyi".equals(name);
    }

    /**
     * <h2>validate02 抛出多个异常</h2>
     * */
    private static boolean validate02(String name) {

        if (null == name) {
            throw new NullPointerException("name is null...");
        }

        if ("".equals(name)) {
            throw new IllegalArgumentException("name is blank...");
        }

        if (!"qinyi".equals(name)) {
            throw new RuntimeException("name is not qinyi...");
        }

        return true;
    }

    /**
     * <h2>打开并关闭 Stream</h2>
     * */
    private static void openAndCloseStream() {

        Stream<Path> pathStream = null;

        try {
            pathStream = Files.list(Paths.get("/tmp"));
            List<Path> paths = pathStream.collect(Collectors.toList());
            System.out.println(paths.size());
            // ....
        } catch (IOException ex) {
            ex.printStackTrace();
        } finally {
            if (null != pathStream) {
                pathStream.close();
            }
        }
    }

    public static void main(String[] args) {

        // 1. 捕获单个异常
        try {
            validate01(null);
        } catch (Throwable th) {
            System.out.println(th.getMessage());
            th.printStackTrace();
        }

        // 2.1 捕获多个异常 -- 第一种方法, 多一个异常一次捕获多次处理
        try {
            validate02("");
        } catch (NullPointerException ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        } catch (IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        } catch (RuntimeException ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        }

        // 2.2 捕获多个异常 -- 第二种方式, 一个 try, 一个 catch
        try {
            validate02("");
        } catch (NullPointerException | IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        }

        // 2.3 捕获多个异常 -- 第三种方式, 定义一个范围更大的父类异常对象
        try {
            validate02("");
        } catch (RuntimeException ex) {
            System.out.println(ex.getMessage());
            ex.printStackTrace();
        }
    }
}

```

# 只有在必要时才使用异常

## 什么是不必要

![](image/Pasted%20image%2020241213083214.png)

## 代码

```java
/**
 * <h1>只有在必要的时候才使用异常</h1>
 * */
public class EssentialException {

    // 第一种情况
    public static class Imooc {

        private final String[] courses = {"广告", "优惠券"};

        public String course(int index) {

//            try {
//                return courses[index - 1];
//            } catch (ArrayIndexOutOfBoundsException ex) {
//                return null;
//            }
            return index > courses.length ? null : courses[index - 1];
        }
    }

    // 第二种情况
    public static void sum(int[] nums) {

        int _sum = 0;

//        try {
//            int i = 0;
//            while (true) {
//                _sum += nums[i++];
//            }
//        } catch (ArrayIndexOutOfBoundsException ex) {
//            System.out.println("_sum is: " + _sum);
//        }

        for (int i = 0; i != nums.length; ++i) {
            _sum += nums[i];
        }

        System.out.println("_sum is: " + _sum);
    }

    // 第三种情况
    public static void printCourseLen(int index) {

        String course = new Imooc().course(index);

        try {
            System.out.println(course.length());
        } catch (NullPointerException ex) {
            System.out.println(0);
        }

        // 两种方式去对待这样的问题
        // 1. 与第一种情况类似, 判断 course
        // 2. 直接使用 course, 不做任何判断, 让异常尽早抛出
        // 3. 捕获住，编写自定义异常，让异常尽早抛出
    }
}

```

# 如何选择自定义和标准异常

![](image/Pasted%20image%2020241213084138.png)

![](image/Pasted%20image%2020241213084438.png)

# 可以忽略异常，但要有理有据

- 进行复杂且容易报错的处理，通常不会让异常抛出

![](image/Pasted%20image%2020241213084647.png)
## 代码

```java
/**
 * <h1>忽略异常</h1>
 * */
public class IgnoreException {

    @Data
    public static class Imoocer {
        private String name;
        private String gender;
    }

    // 1. for 循环中大批量的处理数据, 一般都不会让异常直接抛出
    public void batchProcess(List<Imoocer> imoocers) {

        int num = 0;
        for (Imoocer imoocer : imoocers) {
            try {
                num += (imoocer.getGender().equals("m") ? 0 : 1);
            } catch (Exception ex) {
                // 记录下异常情况
            }
        }

        System.out.println("female imoocer num is: " + num);
    }

    // 2. 存在网络请求(RPC), 允许一定次数的失败重试, 即忽略掉偶发性的异常
    private static void sendGet() throws Exception {

        URL obj = new URL("www.imooc.com");
        HttpURLConnection con = (HttpURLConnection) obj.openConnection();
        con.setRequestMethod("GET");

        int responseCode = con.getResponseCode();
        System.out.println("Response Code: " + responseCode);
    }

    // 3. 不影响业务的整体逻辑情况, 例如手机验证码发送失败
}
```

# 尽最大努力不让异常影响系统状态

- 在副本上操作，最经典的就是 Collections.sort() 就是将原来的 List 拷贝一份，等副本排序好了再塞回去

## 系统的状态是对象的状态

![](image/Pasted%20image%2020241213085939.png)

## 代码

```java
/**
 * <h1>异常发生时不要影响系统的状态</h1>
 * */
@SuppressWarnings("all")
public class DoNotAffectTheState {

    @Data
    @NoArgsConstructor
    @AllArgsConstructor
    public static class Imoocer {
        private String name;
        private String birthday;  // 接受的是 yyyy-MM-dd 结构
        private int age;

        public Imoocer(String name) {
            this.name = name;
        }
    }

    // 参数是不可变的, 状态就不会变
    public void printImoocer(final Imoocer imoocer) {
        System.out.println(imoocer.getName());
        // 由于参数是 final 的, 所以, 不可改变
//        imoocer = new Imoocer("qinyi");
        imoocer.setAge(19);
    }

    // 如果对象可变, 保持好状态

    // 第一种, 在执行操作之前检查参数的有效性
    public static void append(List<Integer> source, List<Integer> target) {

        assert null != source && null != target;
        source.forEach(s -> {
            if (null != s) {
                target.add(s);      // 参数有效性校验
            }
        });

        // do something
    }

    // 第二种, 调整计算处理过程中的顺序
    public static void computeAge(Imoocer imoocer, String birthday) {

        assert null != imoocer;

        LocalDate today = LocalDate.now();
        LocalDate playerDate =
                LocalDate.from(DateTimeFormatter.ofPattern("yyyy-MM-dd").parse(birthday));
        long years = ChronoUnit.YEARS.between(playerDate, today);

        imoocer.setBirthday(birthday);
        imoocer.setAge((int) years);
    }

    // 第三种, 编写恢复代码, 回滚到之前的状态
    public static void transaction() {

        Connection conn = null;

        try {
            conn.setAutoCommit(false);
            // 执行很多 SQL 语句
            conn.commit();
        } catch (SQLException ex) {
            // 回滚事物
//            conn.rollback();
        } finally {
//            conn.setAutoCommit(true);
//            conn.close();
        }
    }
}

```

# 回顾如何处理异常

![](image/Pasted%20image%2020241213091250.png)

# 为什么 Java 会设计异常

![](image/Pasted%20image%2020241213091533.png)

# 到现在学了啥

![](image/Pasted%20image%2020241213091754.png)

# 合理的处理异常，就需要学会记录

![](image/Pasted%20image%2020241213091848.png)