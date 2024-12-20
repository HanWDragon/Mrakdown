## 设计 SpringBoot 工程承载的功能和 JVM 环境配置

### SpringBoot 工程

![](image/Pasted%20image%2020241218004125.png)

![](image/Pasted%20image%2020241218004401.png)
#### 依赖

```xml
<dependencies>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <version>1.18.6</version>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-test</artifactId>
            <scope>test</scope>
        </dependency>
        <!-- aop 依赖, aspectj -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-aop</artifactId>
        </dependency>
        <!-- 引入 redis 的依赖 -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-data-redis</artifactId>
            <exclusions>
                <exclusion>
                    <groupId>io.lettuce</groupId>
                    <artifactId>lettuce-core</artifactId>
                </exclusion>
            </exclusions>
        </dependency>
        <dependency>
            <groupId>redis.clients</groupId>
            <artifactId>jedis</artifactId>
        </dependency>
        <!-- SpringBoot 监控端点 -->
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-actuator</artifactId>
        </dependency>
        <!-- https://mvnrepository.com/artifact/org.apache.commons/commons-lang3 -->
        <dependency>
            <groupId>org.apache.commons</groupId>
            <artifactId>commons-lang3</artifactId>
            <version>3.11</version>
        </dependency>
        <!-- 国货工具类: https://www.hutool.cn/docs/#/ -->
        <dependency>
            <groupId>cn.hutool</groupId>
            <artifactId>hutool-all</artifactId>
            <version>5.4.3</version>
        </dependency>
        <!-- slf4j 日志门面 -->
<!--        <dependency>-->
<!--            <groupId>org.slf4j</groupId>-->
<!--            <artifactId>slf4j-api</artifactId>-->
<!--            <version>1.8.0-beta4</version>-->
<!--        </dependency>-->
        <!-- apache poi -->
        <dependency>
            <groupId>org.apache.poi</groupId>
            <artifactId>poi</artifactId>
            <version>3.10-FINAL</version>
        </dependency>
        <dependency>
            <groupId>org.apache.poi</groupId>
            <artifactId>poi-ooxml</artifactId>
            <version>3.10-FINAL</version>
        </dependency>
    </dependencies>
```

#### 统一响应

```java
/**
 * <h1>统一响应</h1>
 * 定义在 advice 包下
 * RestControllerAdvice: 组合注解, ControllerAdvice + ResponseBody, 是对 RestController 的功能增强
 * ResponseBodyAdvice: 定义对响应处理的接口
 */
@RestControllerAdvice
public class CommonResponseDataAdvice implements ResponseBodyAdvice<Object> {

    /**
     * <h2>判断是否需要对响应进行处理</h2>
     * @return false: 不需要处理; true: 需要处理
     * */
    @Override
    @SuppressWarnings("all")
    public boolean supports(MethodParameter methodParameter,
                            Class<? extends HttpMessageConverter<?>> aClass) {

        // 如果当前方法所在的类标识了 IgnoreResponseAdvice 注解, 则不需要处理
        if (methodParameter.getDeclaringClass().isAnnotationPresent(
                IgnoreResponseAdvice.class
        )) {
            return false;
        }

        // 如果当前方法标识了 IgnoreResponseAdvice 注解, 则不需要处理
        if (methodParameter.getMethod().isAnnotationPresent(
                IgnoreResponseAdvice.class
        )) {
            return false;
        }

        // 对响应进行处理, 执行 beforeBodyWrite 方法
        return true;
    }

    /**
     * <h2>响应返回之前的处理</h2>
     * @param o 响应对象
     * */
    @Nullable
    @Override
    @SuppressWarnings("all")
    public Object beforeBodyWrite(@Nullable Object o,
                                  MethodParameter methodParameter,
                                  MediaType mediaType,
                                  Class<? extends HttpMessageConverter<?>> aClass,
                                  ServerHttpRequest serverHttpRequest,
                                  ServerHttpResponse serverHttpResponse) {

        // 定义最终的返回对象
        CommonResponse<Object> response = new CommonResponse<>(
                0, ""
        );

        // 如果 o 是 null, response 不需要设置 data
        if (null == o) {
            return response;
            // 如果 o 已经是 CommonResponse, 不需要再次处理
        } else if (o instanceof CommonResponse) {
            response = (CommonResponse<Object>) o;
            // 否则, 把响应对象作为 CommonResponse 的 data 部分
        } else {
            response.setData(o);
        }

        return response;
    }
}
```

```java
/**
 * <h1>忽略统一响应注解定义</h1>
 * 定义在 annotation
 * Created by Qinyi.
 */
@Target({ElementType.TYPE, ElementType.METHOD})
@Retention(RetentionPolicy.RUNTIME)
public @interface IgnoreResponseAdvice {
}

```

```java
/**
 * <h1>统一响应</h1>
 */
@Data
@NoArgsConstructor
@AllArgsConstructor
public class CommonResponse<T> implements Serializable {

    private Integer code;
    private String message;
    private T data;

    public CommonResponse(Integer code, String message) {

        this.code = code;
        this.message = message;
    }
}

```

```java
@Configuration
public class ObjectMapperConfig {

    @Bean
    @Primary
    public ObjectMapper objectMapper() {

        ObjectMapper objectMapper = new ObjectMapper();

        // 忽略不识别的字段 --> 当 JSON 字符串包含 Java 类没有的属性时, 反序列化就会失败
        objectMapper.configure(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES, false);

        return objectMapper;
    }
}

```

```java
@Configuration
public class WebMvcConfig extends WebMvcConfigurationSupport {

    @Override
    public void addInterceptors(InterceptorRegistry registry) {

        registry.addInterceptor(new TraceIdInterceptor()).addPathPatterns("/**").order(0);
    }

    @Override
    protected void configureAsyncSupport(AsyncSupportConfigurer configurer) {
        configurer.setTaskExecutor(mvcTaskExecutor());
    }

    @Bean
    public ThreadPoolTaskExecutor mvcTaskExecutor() {

        ThreadPoolTaskExecutor taskExecutor = new ThreadPoolTaskExecutor();
        taskExecutor.setCorePoolSize(20);
        taskExecutor.setMaxPoolSize(20);
        taskExecutor.setThreadNamePrefix("imooc-qinyi-");
        taskExecutor.initialize();

        return taskExecutor;
    }
}

```

```java
@Slf4j
@Component
public class TraceIdInterceptor implements HandlerInterceptor {

    private static final String FLAG = "REQUEST_ID";

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler)
            throws Exception {

        // 先清理掉之前的请求 id
        MDC.clear();

        String traceId = request.getHeader(FLAG);

        if (StringUtils.isEmpty(traceId)) {
            if (null == MDC.get(FLAG)) {
                MDC.put(FLAG, UUID.randomUUID().toString());
            }
        } else {
            MDC.put(FLAG, traceId);
        }

        return true;
    }
}

```

### JVM 环境配置

![](image/Pasted%20image%2020241218010557.png)

# 工程启动失败没有打印日志

## 先确定启动失败的原因

![](image/Pasted%20image%2020241218011612.png)

## 确定没有日志的原因

![](image/Pasted%20image%2020241218011700.png)

# 认识并自定义异常分析接口 FailureAnaluzer

## 什么是 FailureAnaluzer

![](image/Pasted%20image%2020241218012143.png)

## 自定义 FailureAnaluzer 及其需要注意的地方

![](image/Pasted%20image%2020241218012721.png)

## 代码

```java
/**
 * <h1>自定义启动异常分析器: IllegalArgumentException</h1>
 * */
public class IllegalArgumentFailureAnalyzer extends
        AbstractFailureAnalyzer<IllegalArgumentException> {

    @Override
    protected FailureAnalysis analyze(Throwable rootFailure, IllegalArgumentException cause) {

        return new FailureAnalysis(
                cause.getMessage(),
                "你需要检查 application.yml 中定义的参数",
                cause
        );
    }
}
```

# Tomcat 与 JVM 配置调优

## Tomcat 配置调优

![](image/Pasted%20image%2020241218013431.png)

![](image/Pasted%20image%2020241218013541.png)

```yml
server:
  servlet:
    context-path: /api
  port: 8888
  tomcat:
    min-spare-threads: 500
    max-threads: 2500
    accept-count: 1000
    max-connections: 5000
  connection-timeout: 10000
```

## JVM 配置调优

![](image/Pasted%20image%2020241218014022.png)

# AOP 切面统一打印请求日志

## AOP 有关术语

![](image/Pasted%20image%2020241218014240.png)
## 代码

```java
/**
 * <h1>请求日志切面</h1>
 * */
@Slf4j
@Aspect
@Component
@SuppressWarnings("all")
public class WebLogAspect {

    @Autowired
    private ObjectMapper mapper;
    private static final Integer PRINT_LOG_SIZE_LIMIT = 100;

    /** 以 controller 包下定义的所有请求为切入点 */
    @Pointcut("execution(public * com.imooc.log.stack.controller..*.*(..)))")
    public void webLog() { }

    @Before("webLog()")
    public void doBefore(JoinPoint joinPoint) throws Throwable {

        // 开始打印请求日志
        ServletRequestAttributes attributes = (ServletRequestAttributes)
                RequestContextHolder.getRequestAttributes();
        HttpServletRequest request = attributes.getRequest();

        // 打印请求参数相关信息
        log.debug("======================= Request Coming =======================");
        log.debug("URL: [{}]", request.getRequestURL().toString());
        log.debug("HTTP Method: [{}]", request.getMethod());
        // 打印调用 controller 的全路径以及执行方法
        log.debug("Class Method: [{}].[{}]",
                joinPoint.getSignature().getDeclaringTypeName(),
                joinPoint.getSignature().getName());
        // 打印请求入参
        String requestArgs = mapper.writeValueAsString(joinPoint.getArgs());
        if (requestArgs.length() > PRINT_LOG_SIZE_LIMIT) {
            log.trace("Request Args: [{}]", requestArgs);
        } else {
            log.debug("Request Args: [{}]", requestArgs);
        }
    }

    @After("webLog()")
    public void doAfter() throws Throwable {

        log.debug("======================= Request Done =======================");
        log.debug("");
    }

    @Around("webLog()")
    public Object doAround(ProceedingJoinPoint proceedingJoinPoint) throws Throwable {

        StopWatch sw = StopWatch.createStarted();
        Object result = proceedingJoinPoint.proceed();

        String resultJson = mapper.writeValueAsString(result);
        if (resultJson.length() > PRINT_LOG_SIZE_LIMIT) {
            log.trace("Response Args: [{}]", resultJson);
        } else {
            log.debug("Response Args: [{}]", resultJson);
        }

        sw.stop();
        log.debug("Time Elapsed: [{}ms]", sw.getTime(TimeUnit.MILLISECONDS));
        return result;
    }
}

```

# 全局统一异常处理

## 怎么做

![](image/Pasted%20image%2020241218015728.png)

## 代码

```java

/**
 * <h1>错误描述接口</h1>
 * */
public interface BaseErrorInfo {

    /**
     * <h2>返回错误码</h2>
     * */
    String getErrorCode();

    /**
     * <h2>返回错误信息</h2>
     * */
    String getErrorMessage();
}


/**
 * <h1>自定义系统错误枚举</h1>
 * */
@AllArgsConstructor
public enum BaseErrorEnum implements BaseErrorInfo {

    SUCCESS("10000", "成功"),
    PARAM_INVALID("10001", "请求参数不合法"),
    INNER_LOGIC_ERROR("10002", "内部逻辑出错"),
    CAN_NOT_FOUND_RESOURCE("10003", "找不到对应的资源"),
    ;

    private final String errorCode;
    private final String errorMessage;

    @Override
    public String getErrorCode() {
        return errorCode;
    }

    @Override
    public String getErrorMessage() {
        return errorMessage;
    }
}

```

```java
/**
 * <h1>自定义异常类</h1>
 * */
@EqualsAndHashCode(callSuper = true)
@Data
public class BizException extends RuntimeException {

    private String errorCode;
    private String errorMessage;

    public BizException() {
        super();
    }

    public BizException(BaseErrorInfo errorInfo) {
        super(errorInfo.getErrorCode());
        this.errorCode = errorInfo.getErrorCode();
        this.errorMessage = errorInfo.getErrorMessage();
    }

    public BizException(BaseErrorInfo errorInfo, Throwable cause) {
        super(errorInfo.getErrorCode(), cause);
        this.errorCode = errorInfo.getErrorCode();
        this.errorMessage = errorInfo.getErrorMessage();
    }
}
```

```java
/**
 * <h1>全局异常处理</h1>
 * */
@Slf4j
@RestControllerAdvice
public class GlobalExceptionAdvice {

    /**
     * <h2>捕获 BizException 进行统一的异常处理</h2>
     * */
    @ExceptionHandler(value = BizException.class)
    public CommonResponse<Void> bizExceptionHandler(HttpServletRequest req,
                                                    BizException ex) {
        log.error("has some error in request: [{}], errorCode: [{}], errorMsg: [{}]",
                req.getRequestURI(), ex.getErrorCode(), ex.getErrorMessage());
        return new CommonResponse<>(Integer.valueOf(ex.getErrorCode()), ex.getErrorMessage());
    }

    /**
     * <h2>兜底异常捕获</h2>
     * */
    @ExceptionHandler(value = Exception.class)
    public CommonResponse<String> handlerException(HttpServletRequest req, Exception ex) {

        log.error("has exception in request: [{}]", req.getRequestURI(), ex);
        CommonResponse<String> response = new CommonResponse<>(-1,
                "business error");
        response.setData(ex.getMessage());
        return response;
    }
}
```

# 通过线程堆栈分析 CPU 占用过高

## 定位和处理

![](image/Pasted%20image%2020241218020453.png)

# GC 调优

![](image/Pasted%20image%2020241218020657.png)


