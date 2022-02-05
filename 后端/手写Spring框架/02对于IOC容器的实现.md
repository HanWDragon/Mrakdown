# 了解反射

<img src="image/image-20220126112555645.png" alt="image-20220126112555645" style="zoom:50%;" />

<img src="image/image-20220126112615801.png" alt="image-20220126112615801" style="zoom:50%;" />

<img src="image/image-20220126112636946.png" alt="image-20220126112636946" style="zoom:50%;" />



 

<img src="image/image-20220126112801411.png" alt="image-20220126112801411" style="zoom:50%;" />

<img src="image/image-20220126112835611.png" alt="image-20220126112835611" style="zoom:50%;" />

<img src="image/image-20220126113313677.png" alt="image-20220126113313677" style="zoom:50%;" />

<img src="image/image-20220126113401285.png" alt="image-20220126113401285" style="zoom:50%;" />

```java
package demo.reflect;

public class ReflectTarget extends ReflectTargetOrigin{
    //---------构造函数-----------
    //(默认的带参数构造函数)
    ReflectTarget(String str) {
        System.out.println("(默认)的构造方法 s = " + str);
    }

    //无参构造函数
    public ReflectTarget() {
        System.out.println("调用了公有的无参构造方法 。。。");
    }

    //有一个参数的构造函数
    public ReflectTarget(char name) {
        System.out.println("调用了带有一个参数的构造方法，参数值为 " + name);
    }

    //有多个参数的构造函数
    public ReflectTarget(String name, int index) {
        System.out.println("调用了带有多个参数的构造方法，参数值为【目标名】： " + name + " 【序号】" + index);
    }
    //受保护的构造函数
    protected ReflectTarget(boolean n){
        System.out.println("受保护的构造方法 n :" + n);
    }
    //私有的构造函数
    private ReflectTarget(int index){
        System.out.println("私有的构造方法 序号：" + index);
    }

    //**************字段*******************//
    public String name;
    protected int index;
    char type;
    private String targetInfo;
    @Override
    public String toString(){
        return "ReflectTarget [name=" + name + ", index=" + index + ", type=" + type
                + ", targetInfo=" + targetInfo + "]";
    }
    //***************成员方法***************//
    public void show1(String s){
        System.out.println("调用了公有的，String参数的show1(): s = " + s);
    }
    protected void show2(){
        System.out.println("调用了受保护的，无参的show2()");
    }
    void show3(){
        System.out.println("调用了默认的，无参的show3()");
    }
    private String show4(int index){
        System.out.println("调用了私有的，并且有返回值的，int参数的show4(): index = " + index);
        return "show4result";
    }

    public static void main(String[] args) throws ClassNotFoundException {
        //第一种方式获取Class对象
        ReflectTarget reflectTarget = new ReflectTarget();
        Class reflectTargetClass1 = reflectTarget.getClass();
        System.out.println("1st : " + reflectTargetClass1.getName());
        //第二种方式获取Class对象
        Class reflectTargetClass2 = ReflectTarget.class;
        System.out.println("2nd: " + reflectTargetClass2.getName());
        //判断第一种方式获取的class对象和第二种方式获取的是否是同一个
        System.out.println(reflectTargetClass1 == reflectTargetClass2);
        //第三种方式来获取Class对象
        Class reflectTargetClass3 = Class.forName("demo.reflect.ReflectTarget");
        System.out.println("3rd: " + reflectTargetClass3.getName());
        System.out.println(reflectTargetClass2 == reflectTargetClass3);
    }
}

```

# 反射的主要用法

<img src="image/image-20220126113739271.png" alt="image-20220126113739271" style="zoom:50%;" />

```java
package demo.reflect;

import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;

/*
 * 通过Class对象可以获取某个类中的：构造方法；
 *
 * 获取构造方法：
 *         1).批量的方法：
 *             public Constructor[] getConstructors()：所有"公有的"构造方法
              public Constructor[] getDeclaredConstructors()：获取所有的构造方法(包括私有、受保护、默认、公有)
 *         2).获取单个的方法，并调用：
 *             public Constructor getConstructor(Class... parameterTypes):获取单个的"公有的"构造方法：
 *             public Constructor getDeclaredConstructor(Class... parameterTypes):获取"某个构造方法"可以是私有的，或受保护、默认、公有；
 *
 *             调用构造方法：
 *             Constructor-->newInstance(Object... initargs)
 */
public class ConstructorCollector {
    public static void main(String[] args) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        Class clazz = Class.forName("demo.reflect.ReflectTarget");
        //1.获取所有的公有构造方法
        System.out.println("**********************所有公有构造方法*********************************");
        Constructor[] conArray = clazz.getConstructors();
        for(Constructor c : conArray){
            System.out.println(c);
        }
        //2.获取所有构造方法
        System.out.println("************所有的构造方法(包括：私有、受保护、默认、公有)***************");
        conArray = clazz.getDeclaredConstructors();
        for(Constructor c : conArray){
            System.out.println(c);
        }
        //3.获取单个带参数的公有方法
        System.out.println("*****************获取公有、有两个参数的构造方法*******************************");
        Constructor con = clazz.getConstructor(String.class, int.class);
        System.out.println("con = " + con);
        //4.获取单个私有的构造方法
        System.out.println("******************获取私有构造方法*******************************");
        con = clazz.getDeclaredConstructor(int.class);
        System.out.println("private con = " + con);
        System.out.println("******************调用私有构造方法创建实例*******************************");
        //暴力访问（忽略掉访问修饰符）
        con.setAccessible(true);
        ReflectTarget reflectTarget = (ReflectTarget) con.newInstance(1);
    }
}

```

```java
package demo.reflect;

/*
 * 获取成员变量并调用：
 *
 * 1.批量的
 *      1).Field[] getFields():获取所有的"公有字段"
 *      2).Field[] getDeclaredFields():获取所有字段，包括：私有、受保护、默认、公有；
 * 2.获取单个的：
 *      1).public Field getField(String fieldName):获取某个"公有的"字段；
 *      2).public Field getDeclaredField(String fieldName):获取某个字段(可以是私有的)
 *
 *   设置字段的值：
 *      Field --> public void set(Object obj,Object value):
 *                  参数说明：
 *                  1.obj:要设置的字段所在的对象；
 *                  2.value:要为字段设置的值；
 *
 */

import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;

public class FieldCollector {
    public static void main(String[] args) throws ClassNotFoundException, NoSuchFieldException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        //获取Class对象
        Class reflectTargetClass = Class.forName("demo.reflect.ReflectTarget");
        //1.获取所有公有的字段
        System.out.println("************获取所有公有的字段********************");
        Field[] fieldArray = reflectTargetClass.getFields();
        for (Field f : fieldArray){
            System.out.println(f);
        }
        //2.获取所有的字段
        System.out.println("************获取所有的字段(包括私有、受保护、默认的)********************");
        fieldArray = reflectTargetClass.getDeclaredFields();
        for (Field f : fieldArray){
            System.out.println(f);
        }
        //3.获取单个特定公有的field
        System.out.println("*************获取公有字段并调用***********************************");
        Field f = reflectTargetClass.getField("name");
        System.out.println("公有的field name : " + f);
        ReflectTarget reflectTarget = (ReflectTarget)reflectTargetClass.getConstructor().newInstance();
        //4.给获取到的field赋值
        f.set(reflectTarget, "待反射一号");
        //5.验证对应的值name
        System.out.println("验证name : " + reflectTarget.name);
        //6.获取单个私有的Field
        System.out.println("**************获取私有字段targetInfo并调用********************************");
        f = reflectTargetClass.getDeclaredField("targetInfo");
        System.out.println(f);
        f.setAccessible(true);
        f.set(reflectTarget, "13810592345");
        System.out.println("验证信息" + reflectTarget);
    }
}

```

```java
package demo.reflect;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/*
 * 获取成员方法并调用：
 *
 * 1.批量的：
 *      public Method[] getMethods():获取所有"公有方法"；（包含了父类的方法也包含Object类）
 *      public Method[] getDeclaredMethods():获取所有的成员方法，包括私有的(不包括继承的)
 * 2.获取单个的：
 *      public Method getMethod(String name,Class<?>... parameterTypes):
 *                  参数：
 *                      name : 方法名；
 *                      Class ... : 形参的Class类型对象
 *      public Method getDeclaredMethod(String name,Class<?>... parameterTypes)
 *
 *   调用方法：
 *      Method --> public Object invoke(Object obj,Object... args):
 *                  参数说明：
 *                  obj : 要调用方法的对象；
 *                  args:调用方式时所传递的实参；
):
 */
public class MethodCollector {
    public static void main(String[] args) throws ClassNotFoundException, NoSuchMethodException, IllegalAccessException, InvocationTargetException, InstantiationException {
        //1、获取Class对象
        Class reflectTargetClass = Class.forName("demo.reflect.ReflectTarget");
        //2、获取所有公有方法
        System.out.println("***************获取所有的public方法，包括父类和Object*******************");
        Method[] methodArray = reflectTargetClass.getMethods();
        for(Method m : methodArray){
            System.out.println(m);
        }
        //3、获取该类的所有方法
        System.out.println("***************获取所有的方法，包括私有的*******************");
        methodArray = reflectTargetClass.getDeclaredMethods();
        for(Method m : methodArray){
            System.out.println(m);
        }
        //4、获取单个公有方法
        System.out.println("***************获取公有的show1()方法*******************");
        Method m = reflectTargetClass.getMethod("show1", String.class);
        System.out.println(m);
        //5、调用show1并执行
        ReflectTarget reflectTarget = (ReflectTarget)reflectTargetClass.getConstructor().newInstance();
        m.invoke(reflectTarget, "待反射方法一号");
        //6、获取一个私有的成员方法
        System.out.println("***************获取私有的show4()方法******************");
        m = reflectTargetClass.getDeclaredMethod("show4", int.class);
        System.out.println(m);
        m.setAccessible(true);
        String result = String.valueOf(m.invoke(reflectTarget, 20));
        System.out.println("返回值 ： " + result);
    }
}

```

```java
package demo.reflect;

public class ReflectTargetOrigin {
    String defaultMember = "default";
    public String publicMember = "public";
    protected String protectedMember = "protected";
    private String privateMember = "private";
}
```

# 反射的获取源

![image-20220126120404995](image/image-20220126120404995.png)

<img src="image/image-20220126120417975.png" alt="image-20220126120417975" style="zoom:50%;" />

#  注解

<img src="image/image-20220126120450412.png" alt="image-20220126120450412" style="zoom:50%;" />

<img src="image/image-20220126120531300.png" alt="image-20220126120531300" style="zoom:50%;" />

 

<img src="image/image-20220126125710448.png" alt="image-20220126125710448" style="zoom:50%;" />

<img src="image/image-20220126125932841.png" alt="image-20220126125932841" style="zoom:50%;" />

<img src="image/image-20220126125957368.png" alt="image-20220126125957368" style="zoom:50%;" />

<img src="image/image-20220126130452696.png" alt="image-20220126130452696" style="zoom:50%;" />

<img src="image/image-20220126130519062.png" alt="image-20220126130519062" style="zoom:50%;" />

<img src="image/image-20220126132930650.png" alt="image-20220126132930650" style="zoom:50%;" />

<img src="image/image-20220126133007990.png" alt="image-20220126133007990" style="zoom:50%;" />

<img src="image/image-20220126133104524.png" alt="image-20220126133104524" style="zoom:50%;" />

<img src="image/image-20220126133235838.png" alt="image-20220126133235838" style="zoom:50%;" />

# 解析对应的注解

```java
package demo.annotation;

import java.lang.annotation.Annotation;
import java.lang.reflect.Field;
import java.lang.reflect.Method;

public class AnnotationParser {
    //解析类的注解
    public static  void  parseTypeAnnotation() throws ClassNotFoundException {
        Class clazz = Class.forName("demo.annotation.ImoocCourse");
        //这里获取的是class对象的注解，而不是其里面的方法和成员变量的注解
        Annotation[] annotations = clazz.getAnnotations();
        for(Annotation annotation : annotations){
            CourseInfoAnnotation courseInfoAnnotation =  (CourseInfoAnnotation) annotation;
            System.out.println("课程名:" + courseInfoAnnotation.courseName() + "\n" +
                    "课程标签：" + courseInfoAnnotation.courseTag() + "\n" +
                    "课程简介：" + courseInfoAnnotation.courseProfile() + "\n" +
                    "课程序号：" + courseInfoAnnotation.courseIndex() );
        }
    }
    //解析成员变量上的标签
    public static void parseFieldAnnotation() throws ClassNotFoundException {
        Class clazz = Class.forName("demo.annotation.ImoocCourse");
        Field[] fields = clazz.getDeclaredFields();
        for(Field f : fields){
            //判断成员变量中是否有指定注解类型的注解
            boolean hasAnnotation = f.isAnnotationPresent(PersonInfoAnnotation.class);
            if(hasAnnotation){
                PersonInfoAnnotation personInfoAnnotation = f.getAnnotation(PersonInfoAnnotation.class);
                System.out.println("名字：" + personInfoAnnotation.name() + "\n" +
                        "年龄：" + personInfoAnnotation.age() + "\n" +
                        "性别：" + personInfoAnnotation.gender() + "\n");
                for(String language : personInfoAnnotation.language()){
                    System.out.println("开发语言：" + language);
                }

            }
        }
    }
    //解析方法注解
    public static void parseMethodAnnotation() throws ClassNotFoundException{
        Class clazz = Class.forName("demo.annotation.ImoocCourse");
        Method[] methods = clazz.getDeclaredMethods();
        for (Method method : methods) {
            /*
             * 判断方法中是否有指定注解类型的注解
             */
            boolean hasAnnotation = method.isAnnotationPresent(CourseInfoAnnotation.class);
            if(hasAnnotation){
                CourseInfoAnnotation courseInfoAnnotation = method.getAnnotation(CourseInfoAnnotation.class);
                System.out.println("课程名：" + courseInfoAnnotation.courseName() + "\n" +
                        "课程标签：" + courseInfoAnnotation.courseTag() + "\n" +
                        "课程简介：" + courseInfoAnnotation.courseProfile() + "\n"+
                        "课程序号：" + courseInfoAnnotation .courseIndex() + "\n");
            }
        }
    }


    public static void main(String[] args) throws ClassNotFoundException {
        //parseTypeAnnotation();
        parseFieldAnnotation();
        //parseMethodAnnotation();
    }
}

```

# 注解获取属性值的底层原理

<img src="image/image-20220126221302749.png" alt="image-20220126221302749" style="zoom:50%;" />

<img src="image/image-20220126221020706.png" alt="image-20220126221020706" style="zoom:50%;" />

<img src="image/image-20220126221047710.png" alt="image-20220126221047710" style="zoom:50%;" />

![image-20220126221341543](image/image-20220126221341543.png)![image-20220126221341891](image/image-20220126221341891.png)

<img src="image/image-20220126221408241.png" alt="image-20220126221408241" style="zoom:50%;" />

# 以上对IOC容器实现的意义

<img src="image/image-20220126221521232.png" alt="image-20220126221521232" style="zoom:50%;" />

# IOC

<img src="image/image-20220126221751832.png" alt="image-20220126221751832" style="zoom:50%;" />

<img src="image/image-20220126221832664.png" alt="image-20220126221832664" style="zoom:50%;" />

# 依赖注入

<img src="image/image-20220126221940511.png" alt="image-20220126221940511" style="zoom:50%;" />

<img src="image/image-20220126222223691.png" alt="image-20220126222223691" style="zoom:50%;" />

<img src="image/image-20220126222044120.png" alt="image-20220126222044120" style="zoom:50%;" />

<img src="image/image-20220126222339434.png" alt="image-20220126222339434" style="zoom:50%;" />

<img src="image/image-20220126222440425.png" alt="image-20220126222440425" style="zoom:50%;" />

<img src="image/image-20220126222549772.png" alt="image-20220126222549772" style="zoom:50%;" />

<img src="image/image-20220126223159219.png" alt="image-20220126223159219" style="zoom:50%;" />

<img src="image/image-20220126223310982.png" alt="image-20220126223310982" style="zoom:50%;" />

<img src="image/image-20220126223352896.png" alt="image-20220126223352896" style="zoom:50%;" />

<img src="image/image-20220126223507037.png" alt="image-20220126223507037" style="zoom:50%;" />

![image-20220126223554216](image/image-20220126223554216.png)

<img src="image/image-20220126223810875.png" alt="image-20220126223810875" style="zoom:50%;" />

<img src="image/image-20220126223841871.png" alt="image-20220126223841871" style="zoom:50%;" />

# 实现思路

<img src="image/image-20220128001514945.png" alt="image-20220128001514945" style="zoom:50%;" />

# 框架具备的最基本功能

![image-20220128002306962](image/image-20220128002306962.png)

# IOC容器的实现

<img src="image/image-20220128005450916.png" alt="image-20220128005450916" style="zoom:50%;" />

# 定义的四个注解

## @Service

```java
package org.simpleframework.core.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Service {
}

```

## @Controller

```java
package org.simpleframework.core.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Controller {
}

```

## @Componment

```java
package org.simpleframework.core.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Component {
}

```

## @Repository

```java
package org.simpleframework.core.annotation;

import java.lang.annotation.ElementType;
import java.lang.annotation.Retention;
import java.lang.annotation.RetentionPolicy;
import java.lang.annotation.Target;

@Target(ElementType.TYPE)
@Retention(RetentionPolicy.RUNTIME)
public @interface Repository {
}

```

# 提取标记对象

<img src="image/image-20220128135752144.png" style="zoom:50%;" />

## 如何找到范围内的所有类

<img src="image/image-20220128140509317.png" alt="image-20220128140509317" style="zoom:50%;" />

## 获取项目类加载器的目的

<img src="image/image-20220128140646303.png" alt="image-20220128140646303" style="zoom:50%;" />

<img src="image/image-20220128140723354.png" alt="image-20220128140723354" style="zoom:50%;" />

<img src="image/image-20220128140813892.png" alt="image-20220128140813892" style="zoom:50%;" />

<img src="image/image-20220128143225509.png" alt="image-20220128143225509" style="zoom:50%;" />

## 对应的代码

```java
package org.simpleframework.util;

import lombok.extern.slf4j.Slf4j;

import java.io.File;
import java.io.FileFilter;
import java.lang.reflect.Constructor;
import java.lang.reflect.Field;
import java.lang.reflect.InvocationTargetException;
import java.net.URL;
import java.util.HashSet;
import java.util.Set;

@Slf4j
public class ClassUtil {

    public static final String FILE_PROTOCOL = "file";

    /**
     * 获取包下类集合
     *
     * @parampackageName包名
     * @return 类集合
     */
    public static Set<Class<?>> extractPackageClass(String packageName){
        //1.获取到类的加载器。
        ClassLoader classLoader = getClassLoader();
        //2.通过类加载器获取到加载的资源
        URL url = classLoader.getResource(packageName.replace(".", "/"));
        if (url == null){
            log.warn("unable to retrieve anything from package: " + packageName);
            return  null;
        }
        //3.依据不同的资源类型，采用不同的方式获取资源的集合
        Set<Class<?>> classSet = null;
        //过滤出文件类型的资源
        if (url.getProtocol().equalsIgnoreCase(FILE_PROTOCOL)){
            classSet = new HashSet<Class<?>>();
            File packageDirectory = new File(url.getPath());
            extractClassFile(classSet, packageDirectory, packageName);
        }
        //TODO 此处可以加入针对其他类型资源的处理

        return classSet;
    }
    /**
     * 递归获取目标package里面的所有class文件(包括子package里的class文件)
     *
     * @param emptyClassSet 装载目标类的集合
     * @param fileSource    文件或者目录
     * @param packageName   包名
     * @return 类集合
     */
    /**
     * 递归获取目标package里面的所有class文件(包括子package里的class文件)
     *
     * @param emptyClassSet 装载目标类的集合
     * @param fileSource    文件或者目录
     * @param packageName   包名
     * @return 类集合
     */
    private static void extractClassFile(Set<Class<?>> emptyClassSet, File fileSource, String packageName) {
        if(!fileSource.isDirectory()){
            return;
        }
        //如果是一个文件夹，则调用其listFiles方法获取文件夹下的文件或文件夹
        File[] files = fileSource.listFiles(new FileFilter() {
            @Override
            public boolean accept(File file) {
                if(file.isDirectory()){
                    return true;
                } else{
                    //获取文件的绝对值路径
                    String absoluteFilePath = file.getAbsolutePath();
                    if(absoluteFilePath.endsWith(".class")){
                        //若是class文件，则直接加载
                        addToClassSet(absoluteFilePath);
                    }
                }
                return false;
            }
            //根据class文件的绝对值路径，获取并生成class对象，并放入classSet中
            private void addToClassSet(String absoluteFilePath) {
                //1.从class文件的绝对值路径里提取出包含了package的类名
                //如/Users/baidu/imooc/springframework/sampleframework/target/classes/com/imooc/entity/dto/MainPageInfoDTO.class
                //需要弄成com.imooc.entity.dto.MainPageInfoDTO
                absoluteFilePath = absoluteFilePath.replace(File.separator, ".");
                String className = absoluteFilePath.substring(absoluteFilePath.indexOf(packageName));
                className = className.substring(0, className.lastIndexOf("."));
                //2.通过反射机制获取对应的Class对象并加入到classSet里
                Class targetClass = loadClass(className);
                emptyClassSet.add(targetClass);
            }
        });
        if(files != null){
            for(File f : files){
                //递归调用
                extractClassFile(emptyClassSet, f, packageName);
            }
        }
    }
    /**
     * 获取Class对象
     *
     * @param className class全名=package + 类名
     * @return Class
     */
    public static Class<?> loadClass(String className){
        try {
            return Class.forName(className);
        } catch (ClassNotFoundException e) {
            log.error("load class error:", e);
            throw new RuntimeException(e);
        }
    }
    /**
     * 实例化class
     *
     * @param clazz Class
     * @param <T>   class的类型
     * @param accessible   是否支持创建出私有class对象的实例
     * @return 类的实例化
     */
    public static <T> T newInstance(Class<?> clazz, boolean accessible){
        try {
            Constructor constructor = clazz.getDeclaredConstructor();
            constructor.setAccessible(accessible);
            return (T)constructor.newInstance();
        } catch (Exception e) {
            log.error("newInstance error", e);
            throw new RuntimeException(e);
        }
    }
    /**
     * 获取classLoader
     *
     * @return 当前ClassLoader
     */
    public static  ClassLoader getClassLoader(){
        return Thread.currentThread().getContextClassLoader();
    }
    /**
     * 设置类的属性值
     *
     * @param field      成员变量
     * @param target     类实例
     * @param value      成员变量的值
     * @param accessible 是否允许设置私有属性
     */
    public static void setField(Field field, Object target, Object value, boolean accessible){
        field.setAccessible(accessible);
        try {
            field.set(target, value);
        } catch (IllegalAccessException e) {
            log.error("setField error", e);
            throw new RuntimeException(e);
        }
    }
    public static void main(String[] args) {
        //extractPackageClass("com.imooc.entity");
        File[] files = null;
        for(File f : files){
            System.out.printf("haha");
        }
        files.getClass().getClassLoader();

    }
}

```

![image-20220128154732476](image/image-20220128154732476.png)

可以使用JAD来查看反编译

# 实现容器

<img src="image/image-20220129144619281.png" alt="image-20220129144619281" style="zoom:50%;" />

# 实现容器的加载

<img src="image/image-20220129145220309.png" alt="image-20220129145220309" style="zoom:50%;" />

# 实现容器的操作方式

<img src="image/image-20220129152022061.png" alt="image-20220129152022061" style="zoom:50%;" />



<img src="image/image-20220129160205416.png" alt="image-20220129160205416" style="zoom:50%;" />

<img src="image/image-20220129160520764.png" alt="image-20220129160520764" style="zoom:50%;" />

# 实现容器的依赖注入

我们现在只支持成员变量级别的注入

像 Spring 的构造函数，工厂方法的注入

<img src="image/image-20220129161131007.png" alt="image-20220129161131007" style="zoom:50%;" />

# 总结

<img src="image/image-20220130001117623.png" alt="image-20220130001117623" style="zoom:50%;" />

<img src="image/image-20220130001141283.png" alt="image-20220130001141283" style="zoom:50%;" />

<img src="image/image-20220130001306655.png" alt="image-20220130001306655" style="zoom:50%;" />

<img src="image/image-20220130001418086.png" alt="image-20220130001418086" style="zoom:50%;" />

<img src="image/image-20220130001450283.png" alt="image-20220130001450283" style="zoom:50%;" />