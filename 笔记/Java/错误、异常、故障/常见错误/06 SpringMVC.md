# 自定义异常

## HTTP 状态码

![](image/Pasted%20image%2020241212033955.png)

## 需要自定义返回状态码

![](image/Pasted%20image%2020241212034016.png)
## 自定义返回码的方式

![](image/Pasted%20image%2020241212035329.png)

## Rest 请求处理过程

1. 客户端请求：    
    - 客户端向服务器发送一个 HTTP 请求。请求包括 URL、HTTP 方法（GET, POST, PUT, DELETE 等）、请求头和可选的请求体。
2. 请求接收：
    - 服务器接收到请求，并将其转发到 DispatcherServlet，这是 Spring MVC 的核心组件。
3. 请求映射：
    - DispatcherServlet 使用 HandlerMapping 来确定哪个控制器（Controller）应该处理该请求。它基于 URL 路径和 HTTP 方法查找合适的处理器。
4. 调用控制器方法：
    - 一旦找到合适的控制器，DispatcherServlet 将请求转发给控制器中的相应方法。控制器方法通常用 @RequestMapping 或 @GetMapping, @PostMapping 等注解来映射请求。
5. 处理请求：
    - 控制器方法处理请求，执行必要的业务逻辑。这可能包括调用服务层、与数据库交互或其他操作。
6. 生成响应：
    - 控制器方法返回一个结果，通常是一个 Java 对象。这个对象可能需要转换为 JSON 或 XML 格式。
7. 视图解析：
    - 对于 REST 服务，通常使用 HttpMessageConverter 来将 Java 对象转换为 HTTP 响应体中的 JSON 或 XML 格式，而不是传统的视图解析。
8. 响应返回：
    - DispatcherServlet 将 HTTP 响应返回给客户端，包含状态码、响应头和响应体。
9. 客户端接收响应：
    - 客户端接收到响应，并处理返回的数据。

# 序列化和反序列化

## @DateTimeFormat 注解

![](image/Pasted%20image%2020241212161418.png)
 
## POST 表单 (Body) 时间转换

- 推荐第二种，使用Spring 来管理
- 也可以不使用注解，直接将格式转换器注册到Jackson

![](image/Pasted%20image%2020241212161429.png)

### 代码

```java
@Slf4j
public class DateJacksonConverter extends JsonDeserializer<Date> {

    private static final String[] pattern = new String[] {
            "yyyy-MM-dd HH:mm:ss", "yyyy/MM/dd"
    };

    @Override
    public Date deserialize(JsonParser jsonParser, DeserializationContext context)
            throws IOException, JsonProcessingException {

        Date targetDate = null;
        String originDate = jsonParser.getText();

        if (StringUtils.isNotEmpty(originDate)) {

            try {
                long longDate = Long.parseLong(originDate.trim());
                targetDate = new Date(longDate);
            } catch (NumberFormatException pe) {
                try {
                    targetDate = DateUtils.parseDate(
                            originDate, DateJacksonConverter.pattern
                    );
                } catch (ParseException ex) {
                    log.error("parse error: {}", ex.getMessage());
                    throw new IOException("parse error");
                }
            }
        }

        return targetDate;
    }

    @Override
    public Class<?> handledType() {
        return Date.class;
    }
}

```

```java
@Configuration
public class DateConverterConfig {

    @Bean
    public DateJacksonConverter dateJacksonConverter() {
        return new DateJacksonConverter();
    }

    @Bean
    public Jackson2ObjectMapperFactoryBean jackson2ObjectMapperFactoryBean(
            @Autowired DateJacksonConverter dateJacksonConverter
    ) {
        Jackson2ObjectMapperFactoryBean jackson2ObjectMapperFactoryBean =
                new Jackson2ObjectMapperFactoryBean();
        jackson2ObjectMapperFactoryBean.setDeserializers(dateJacksonConverter);

        return jackson2ObjectMapperFactoryBean;
    }
}

```

# 日志放在拦截器还是过滤器

## 过滤器（Filter）

![](image/Pasted%20image%2020241212165326.png)

![](image/Pasted%20image%2020241212165536.png)

## 拦截器（Interceptor）

![](image/Pasted%20image%2020241212165740.png)

## 相同和不同

![](image/Pasted%20image%2020241212200002.png)

### 过滤器（Filters）

- 过滤器是基于 Servlet 规范的组件，可以用于在请求到达 Servlet 之前和响应返回客户端之前进行预处理和后处理。
- 通常用于处理编码、日志记录、安全性、请求修改等。

实现：
1. 创建过滤器类：实现 `javax.servlet.Filter` 接口。
2. 实现方法：
    - `init(FilterConfig filterConfig)`: 用于初始化过滤器。
    - `doFilter(ServletRequest request, ServletResponse response, FilterChain chain)`: 执行过滤逻辑。在调用 `chain.doFilter(request, response)` 之前进行请求的预处理，之后进行响应的后处理。
    - `destroy()`: 用于销毁过滤器时的清理工作。
3. 配置过滤器：
    - 在 `web.xml` 中配置，或使用 Spring Boot 中的 `@WebFilter` 注解或 `FilterRegistrationBean`。

### 拦截器（Interceptors）

- 拦截器是 Spring 框架提供的机制，可以拦截处理器（Controller）的方法调用。
- 用于在请求到达 Controller 之前和响应返回视图之前进行处理。
- 更加面向 Spring 框架，能访问 Spring 的上下文和依赖注入。

实现：
1. 创建拦截器类：实现 `HandlerInterceptor` 接口或继承 `HandlerInterceptorAdapter`（已废弃，建议直接实现接口）。
2. 实现方法：
    - `preHandle(HttpServletRequest request, HttpServletResponse response, Object handler)`: 在请求处理之前调用，返回 `true` 继续流程，返回 `false` 中止请求。
    - `postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView)`: 在请求处理之后，视图渲染之前调用。
    - `afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex)`: 在请求完成之后调用，用于清理资源。
3. 配置拦截器：
    - 在 Spring 配置文件中注册拦截器，或使用 `WebMvcConfigurer` 接口的 `addInterceptors` 方法。

### 总结

- 过滤器更底层，与 Servlet 容器结合紧密，适用于全局的请求处理。
- 拦截器更高层次，专注于 SpringMVC 的请求生命周期，适用于控制器级别的请求处理。
- 选择使用哪个取决于你的需求和应用架构：如果你需要与 Spring 框架紧密集成，拦截器可能是更好的选择；如果需要更底层的控制，则选择过滤器。

# HttpServletRequest 和 HttpServletResponse 方法互斥

## 流

![](image/Pasted%20image%2020241212200209.png)

## 两个坑

- 因为读取的指针一直在前进，读取了之后，别人再读取指针已经到了最后，所以不会返回任何数据

![](image/Pasted%20image%2020241212203007.png)

## 如何解决

- 使用HttpServletXXWrapper，在过滤器使用 doFilter 塞入 Wrapper
- 核心就是替换原来的 HttpServletXX

## 代码

```java
public class RequestParseUtil {

    /**
     * <h2>当前的请求是否是 rest 类型</h2>
     * */
    public static boolean isJson(HttpServletRequest request) {

        if (request.getContentType() != null) {
            return request.getContentType().equals(MediaType.APPLICATION_JSON_VALUE)
                    || request.getContentType()
                    .equals(MediaType.APPLICATION_JSON_UTF8_VALUE);
        }

        return false;
    }

    public static String getBodyString(final ServletRequest request) {
        try {
            return inputStream2String(request.getInputStream());
        } catch (IOException ex) {
            throw new RuntimeException();
        }
    }

    private static String inputStream2String(InputStream inputStream) {

        StringBuilder sb = new StringBuilder();
        BufferedReader reader = null;

        try {

            reader = new BufferedReader(
                    new InputStreamReader(inputStream, Charset.defaultCharset())
            );
            String line;
            while ((line = reader.readLine()) != null) {
                sb.append(line);
            }
        } catch (IOException ex) {
            throw new RuntimeException();
        }

        return sb.toString();
    }
}

```

```java
public class RequestWrapper extends HttpServletRequestWrapper {

    /** 存储输入流数据 */
    private final byte[] body;

    /**
     * Constructs a request object wrapping the given request.
     *
     * @param request The request to wrap
     * @throws IllegalArgumentException if the request is null
     */
    public RequestWrapper(HttpServletRequest request) {
        super(request);

        body = RequestParseUtil.getBodyString(request).getBytes(
                Charset.defaultCharset());
    }

    @Override
    public BufferedReader getReader() throws IOException {
        return new BufferedReader(new InputStreamReader(getInputStream()));
    }

    @Override
    public ServletInputStream getInputStream() throws IOException {

        ByteArrayInputStream inputStream = new ByteArrayInputStream(body);

        return new ServletInputStream() {
            @Override
            public boolean isFinished() {
                return false;
            }

            @Override
            public boolean isReady() {
                return false;
            }

            @Override
            public void setReadListener(ReadListener listener) {

            }

            @Override
            public int read() throws IOException {
                return inputStream.read();
            }
        };
    }
}

```

```java
@Slf4j
@WebFilter(urlPatterns = "/*", filterName = "RequestWrapperFilter")
public class RequestWrapperFilter implements Filter {
    @Override
    public void init(FilterConfig filterConfig) throws ServletException {

    }

    @Override
    public void doFilter(ServletRequest request, ServletResponse response,
                         FilterChain chain) throws IOException, ServletException {
        log.info("RequestWrapperFilter Replace InputStream!");

        ServletRequest requestWrapper =
                new RequestWrapper((HttpServletRequest) request);
        chain.doFilter(requestWrapper, response);
    }

    @Override
    public void destroy() {

    }
}
```