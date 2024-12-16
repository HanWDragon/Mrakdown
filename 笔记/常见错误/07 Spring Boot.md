# 配置出错

## Spring Boot 的配置文件

![](image/Pasted%20image%2020241212220047.png)

## 加载顺序

![](image/Pasted%20image%2020241212230410.png)

## 多环境

![](image/Pasted%20image%2020241212230635.png)

# 定时任务

- 定时任务不定时了，因为没有主动配置线程池，默认定时任务线程池是单线程，如果一个任务死循环，那么别的任务也不会执行

## 如何编写

![](image/Pasted%20image%2020241212231556.png)

## 配置定时任务线程池

![](image/Pasted%20image%2020241212232127.png)

## 代码

```java
@Configuration
public class ScheduleConfig {

    @Bean
    public TaskScheduler taskScheduler() {

        ThreadPoolTaskScheduler taskScheduler = new ThreadPoolTaskScheduler();
        taskScheduler.setPoolSize(5);
        return taskScheduler;
    }
}

```

# 异步任务处理

- 自定义线程池、超时、异常处理

## Spring 开启异步任务

![](image/Pasted%20image%2020241212232357.png)

## 注意事项

![](image/Pasted%20image%2020241212232415.png)

## 代码

```java
Slf4j
@Configuration
public class AsyncTaskConfig implements AsyncConfigurer {

    @Override
    public Executor getAsyncExecutor() {

        ThreadPoolTaskExecutor executor = new ThreadPoolTaskExecutor();

        executor.setThreadNamePrefix("imooc-qinyi-task-");
        executor.setCorePoolSize(2);
        executor.setMaxPoolSize(8);
        executor.setKeepAliveSeconds(5);
        executor.setQueueCapacity(100);
        executor.setRejectedExecutionHandler(new ThreadPoolExecutor.AbortPolicy());

        executor.setWaitForTasksToCompleteOnShutdown(true);
        executor.setAwaitTerminationSeconds(60);

        executor.initialize();

        return executor;
    }

    @Override
    public AsyncUncaughtExceptionHandler getAsyncUncaughtExceptionHandler() {

        return new AsyncUncaughtExceptionHandler() {
            @Override
            public void handleUncaughtException(Throwable ex, Method method,
                                                Object... params) {
                // 发送报警邮件, 短信等等
                log.error("Async Task Has Some Error: {}, {}, {}",
                        ex.getMessage(),
                        method.getDeclaringClass().getName() + "." + method.getName(),
                        Arrays.toString(params));
            }
        };
    }
}

```

# Jackson

## Jackson 和 ObjectMapper

![](image/Pasted%20image%2020241212234038.png)

## Spring 管理 ObjectMapper 的理由

![](image/Pasted%20image%2020241212234115.png)

## 常用注解

![](image/Pasted%20image%2020241212234546.png)

## FastJson 对比

![](image/Pasted%20image%2020241213000000.png)