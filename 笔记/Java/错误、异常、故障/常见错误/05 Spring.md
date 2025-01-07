# Bean 默认名称生成策略导致空指针

## 名称生成策略

- 在 AnnotationBeanNameGenerator 下的 GenerateBeanName

![](image/Pasted%20image%2020241211222640.png)

## 建议

1. 修改名称首字母前两个不要都大写
2. 通过正确的名称获取
3. 主动指定名称
4. 使用具体的类型获取

# Autowired

## 不理解装配规则，错误的 new

![](image/Pasted%20image%2020241211223919.png)

## 不理解包扫描机制，没扫描到

- 扫描启动类当前包和子包 Bean
- 可以使用 ComponentScan 定义要扫描的包

![](image/Pasted%20image%2020241211223955.png)

## @ComponentScan

![](image/Pasted%20image%2020241211225241.png)

# 不使用自动注入获取应用上下文

## 容器理解

![](image/Pasted%20image%2020241211225421.png)

## Spring核心是容器，但容器并不唯一

![](image/Pasted%20image%2020241211225617.png)

## 获取 ApplicationContext 四种方式

- 第一种编写完成后需要在启动类添加进去

```java
SpringApplication application = new SpringApplication(
                SpringEscapeApplication.class
        );
        application.addInitializers(new UseIntitiallizer());
        application.run(args);
```

![](image/Pasted%20image%2020241211225740.png)

![](image/Pasted%20image%2020241212002312.png)

![](image/Pasted%20image%2020241212002510.png)
## 代码

```java
/**
 * <h1>保存应用上下文</h1>
 * */
@Slf4j
public class ApplicationContextStore {

    private static ApplicationContext applicationContext;

    public static void setApplicationContext(ApplicationContext applicationContext) {
        log.info("Coming In ApplicationContextStore!");
        ApplicationContextStore.applicationContext = applicationContext;
    }

    public static ApplicationContext getApplicationContext() {
        return ApplicationContextStore.applicationContext;
    }
}

```

```java
/**
 * <h1>第一种方式获取应用上下文</h1>
 * */
@Slf4j
public class UseIntitiallizer implements
        ApplicationContextInitializer<ConfigurableApplicationContext> {

    @Override
    public void initialize(ConfigurableApplicationContext applicationContext) {

        assert ApplicationContextStore.getApplicationContext() == null;
        ApplicationContextStore.setApplicationContext(applicationContext);
        assert ApplicationContextStore.getApplicationContext() != null;
        log.info("UseIntitiallizer Done.");
    }
}

```

```java
@Slf4j
@Component
public class UseListener implements ApplicationListener<ApplicationContextEvent> {

    @Override
    public void onApplicationEvent(ApplicationContextEvent event) {

        assert ApplicationContextStore.getApplicationContext() == null;
        ApplicationContextStore.setApplicationContext(
                event.getApplicationContext()
        );
        assert ApplicationContextStore.getApplicationContext() != null;
        log.info("UseListener Done.");
    }
}
```

```java
// 第三种方式获取应用上下文
       ApplicationContextStore.setApplicationContext(
                SpringApplication.run(SpringEscapeApplication.class, args)
        );
```

```java
@Slf4j
@Component
public class UseAware implements ApplicationContextAware {

    @Override
    public void setApplicationContext(ApplicationContext applicationContext)
            throws BeansException {
        assert ApplicationContextStore.getApplicationContext() == null;
        ApplicationContextStore.setApplicationContext(
                applicationContext
        );
        assert ApplicationContextStore.getApplicationContext() != null;
        log.info("UseAware Done.");
    }
}
```

# 多线程 Bean 数据不符合预期

- 多线程操作单例的 Bean，导致数据不符合预期
- 有状态的 Bean 最好不要使用单例，@Scope(BeanDefinition.SCOPE_PROTOTYPE)

## Spring 提供的 Bean Scope

![](image/Pasted%20image%2020241212003127.png)

![](image/Pasted%20image%2020241212003939.png)

## 思考

![](image/Pasted%20image%2020241212004131.png)

## 代码

```java
@Slf4j
@Service
@Scope(BeanDefinition.SCOPE_PROTOTYPE)
public class DefaultImoocerManagerService {

    private List<String> imoocers = null;

    @PostConstruct
    public void init() {
        log.info("Coming In DefaultImoocerManagerService init!");
        this.imoocers = new ArrayList<>(100);
    }

    public void addImoocer(String imoocer) {
        this.imoocers.add(imoocer);
    }

    public int imoocerCount() {
        return this.imoocers.size();
    }

    public List<String> getImoocers() {
        return this.imoocers;
    }
}

```

```java
@Slf4j
@SpringBootTest
@RunWith(SpringRunner.class)
public class TestDefaultSingleton {

    @Test
    public void testDefaultSingleton() {

        DefaultImoocerManagerService service01 = ApplicationUtils.getBean(
                DefaultImoocerManagerService.class
        );
        DefaultImoocerManagerService service02 = ApplicationUtils.getBean(
                DefaultImoocerManagerService.class
        );

        service01.addImoocer("KunKun");
        service01.addImoocer("Cousin");
        log.info("Service01 Has Imoocers: {}", service01.getImoocers());

        service02.addImoocer("DaMiao");
        log.info("Service01 Has Imoocers: {}", service01.getImoocers());
    }

    @Test
    public void testDefaultSingleton_() {

        DefaultImoocerManagerService service01 = ApplicationUtils.getBean(
                DefaultImoocerManagerService.class
        );
        DefaultImoocerManagerService service02 = ApplicationUtils.getBean(
                DefaultImoocerManagerService.class
        );

        assert service01.hashCode() == service02.hashCode();
    }
}

```

# 多个可用 Bean 异常

- 通常出现在多数据源

## 相关注解

- 存在很多类型相同，就按名称注入

![](image/Pasted%20image%2020241212004355.png)

## 两类异常

![](image/Pasted%20image%2020241212010523.png)

## 代码

```java
/**
 * <h1>配置多个 Redis 数据源</h1>
 * */
@SuppressWarnings("all")
@Configuration
public class RedisConfig {

    private final RedisConnectionFactory redisConnectionFactory;

    @Autowired
    public RedisConfig(RedisConnectionFactory redisConnectionFactory) {
        this.redisConnectionFactory = redisConnectionFactory;
    }

    @Primary
    @Bean(name = "qinyiRedisTemplate")
    public RedisTemplate<String, Object> getQinyiRedisTemplate(
            RedisConnectionFactory factory) {

        RedisTemplate<String, Object> template = new RedisTemplate<>();

        RedisSerializer<String> stringSerializer = new StringRedisSerializer();

        template.setConnectionFactory(factory);
        template.setKeySerializer(stringSerializer);
        template.setValueSerializer(stringSerializer);

        return template;
    }

    @Bean(name = "imoocRedisTemplate")
    public RedisTemplate<String, Object> getImoocRedisTemplate(
            RedisConnectionFactory factory) {

        RedisTemplate<String, Object> template = new RedisTemplate<>();

        JdkSerializationRedisSerializer redisSerializer =
                new JdkSerializationRedisSerializer();
        RedisSerializer<String> stringSerializer = new StringRedisSerializer();

        template.setConnectionFactory(factory);
        template.setKeySerializer(stringSerializer);
        template.setValueSerializer(redisSerializer);

        return template;
    }
}
```

```java
public interface ITemplateManagerService {

    void print();
}
```

```java
@Service
public class ImoocTemplateManagerService implements ITemplateManagerService {

    @Override
    public void print() {
        System.out.println("ImoocTemplateManagerService");
    }
}

@Service
public class QinyiTemplateManagerService implements ITemplateManagerService {

    @Override
    public void print() {
        System.out.println("QinyiTemplateManagerService");
    }
}

```

```java
@SuppressWarnings("all")
@SpringBootTest
@RunWith(SpringRunner.class)
public class TestMultiUsableBean {

//    @Autowired
//    @Qualifier("qinyiRedisTemplate")
//    @Resource
//    private RedisTemplate redisTemplate;
    @Autowired
    @Qualifier("qinyiRedisTemplate")
    private RedisTemplate imoocRedisTemplate;

    @Autowired
    @Qualifier("qinyiTemplateManagerService")
    private ITemplateManagerService templateManagerService;

    @Test
    public void testAutowire() {

        assert imoocRedisTemplate != null;
        imoocRedisTemplate.getConnectionFactory().getConnection().flushAll();

        imoocRedisTemplate.opsForValue().set("name", "qinyi");
    }

    @Test
    public void testTemplateManagerService() {

//        assert templateManagerService == null;

        templateManagerService.print();
    }

    @Test
    public void testUseRedisPipeline() {

        // 清空 Redis 服务器中的数据, 方便校验测试
        imoocRedisTemplate.getConnectionFactory().getConnection().flushAll();

        List<Object> resultList = imoocRedisTemplate.executePipelined(
                new RedisCallback<Object>() {
                    @Override
                    public Object doInRedis(RedisConnection connection)
                            throws DataAccessException {

                        // 1. 通过 connection 打开 pipeline
                        connection.openPipeline();

                        // 2. 给本次 pipeline 添加一次性要执行的多条命令
                        // 2.1 一个 set key value 的操作
                        byte[] key = "name".getBytes();
                        byte[] value = "qinyi".getBytes();
                        connection.set(key, value);

                        // 2.2 执行一个错误的命令
                        connection.lPop("xyzabc".getBytes());

                        // 2.3 mset 操作
                        Map<byte[], byte[]> tuple = new HashMap<>();
                        tuple.put("id".getBytes(), "1".getBytes());
                        tuple.put("age".getBytes(), "19".getBytes());
                        connection.mSet(tuple);

                        // 3. 关闭 pipeline
//                        connection.closePipeline();

                        return null;
                    }
                }
        );

        resultList.forEach(System.out::println);
    }
}

```

# 循环依赖

- 通过构造方法会报错
- 字段注入和 set 注入，Spring 能解决一部分

![](image/Pasted%20image%2020241212011042.png)

## Bean实例化过程

- 实例化失败，Spring 就没办法解决了
- 能在填充属性解决循环依赖
- 原型模式就不能解决循环依赖

![](image/Pasted%20image%2020241212024021.png)

![](image/Pasted%20image%2020241212024143.png)

# BeanFactoryPostProcessor 和 BeanPostProcessor

![](image/Pasted%20image%2020241212024630.png)

## BeanPostProcessor

![](image/Pasted%20image%2020241212025131.png)
## BeanFactoryPostProcessor

- 这个接口可以修改第三方类库的代码，自定义 Bean 的属性

![](image/Pasted%20image%2020241212030559.png)

## Bean 生命周期

1. 实例化（Instantiation）
    - Spring 使用反射机制创建 Bean 实例。
2. 属性赋值（Populate Properties）
    - Spring 将配置文件中定义的属性值或依赖注入到 Bean 中。
3. BeanNameAware 接口
    - 如果 Bean 实现了 `BeanNameAware` 接口，Spring 调用 `setBeanName(String name)` 方法，传递 Bean 的名称。
4. BeanFactoryAware 接口
    - 如果 Bean 实现了 `BeanFactoryAware` 接口，Spring 调用 `setBeanFactory(BeanFactory beanFactory)` 方法，传递当前的 BeanFactory 实例。
5. ApplicationContextAware 接口
    - 如果 Bean 实现了 `ApplicationContextAware` 接口，Spring 调用 `setApplicationContext(ApplicationContext applicationContext)` 方法，传递当前的 ApplicationContext。
6. BeanPostProcessor 接口 - 前置处理
    - 在初始化之前，Spring 调用 `postProcessBeforeInitialization(Object bean, String beanName)` 方法。
7. InitializingBean 接口
    - 如果 Bean 实现了 `InitializingBean` 接口，Spring 调用 `afterPropertiesSet()` 方法。
8. 自定义初始化方法
    - 如果在配置中指定了自定义的初始化方法，Spring 调用该方法。
9. BeanPostProcessor 接口 - 后置处理
    - 在初始化之后，Spring 调用 `postProcessAfterInitialization(Object bean, String beanName)` 方法。
10. Bean 可用
    - Bean 准备好可以使用。
11. DisposableBean 接口
    - 如果 Bean 实现了 `DisposableBean` 接口，Spring 在容器关闭时调用 `destroy()` 方法。
12. 自定义销毁方法
    - 如果在配置中指定了自定义的销毁方法，Spring 调用该方法。

# 事务

## 关于 Spring 事务

![](image/Pasted%20image%2020241212031725.png)

## 失效和成功


- 主动捕获了异常, 导致事务不能回滚
- 不是 unchecked 异常, 事务不能回滚
- unchecked 异常可以回滚
- 指定 rollbackFor , 事务可以回滚
- 同一个类中, 一个不标注事务的方法去调用标注了事务的方法, 事务会失效

