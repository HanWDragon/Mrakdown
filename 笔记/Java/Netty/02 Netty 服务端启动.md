# 服务启动 Demo

- 标准示例代码

```java
public final class Server {

    public static void main(String[] args) throws Exception {
        EventLoopGroup bossGroup = new NioEventLoopGroup(1);
        EventLoopGroup workerGroup = new NioEventLoopGroup();

  
            ServerBootstrap b = new ServerBootstrap();
            b.group(bossGroup, workerGroup)
                    .channel(NioServerSocketChannel.class)
                    .childOption(ChannelOption.TCP_NODELAY, true)
                    .childAttr(AttributeKey.newInstance("childAttr"), "childAttrValue")
                    .handler(new ServerHandler())
                    .childHandler(new ChannelInitializer<SocketChannel>() {
                        @Override
                        public void initChannel(SocketChannel ch) {
                            ch.pipeline().addLast(new AuthHandler());
                            //..

                        }
                    });

            ChannelFuture f = b.bind(8888).sync();

            f.channel().closeFuture().sync();
        } finally {
            bossGroup.shutdownGracefully();
            workerGroup.shutdownGracefully();
        }
    }
}
```

```java
public class ServerHandler extends ChannelInboundHandlerAdapter {
    @Override
    public void channelActive(ChannelHandlerContext ctx) {
        System.out.println("channelActive");
    }

    @Override
    public void channelRegistered(ChannelHandlerContext ctx) {
        System.out.println("channelRegistered");
    }

    @Override
    public void handlerAdded(ChannelHandlerContext ctx) {
        System.out.println("handlerAdded");
    }

    @Override
    public void channelRead(final ChannelHandlerContext ctx, Object msg) throws Exception {
        super.channelRead(ctx, msg);

        new Thread(new Runnable() {
            @Override
            public void run() {
                // 耗时的操作
                String result = loadFromDB();

                ctx.channel().writeAndFlush(result);
                ctx.executor().schedule(new Runnable() {
                    @Override
                    public void run() {
                        // ...
                    }
                }, 1, TimeUnit.SECONDS);

            }
        }).start();
    }

    private String loadFromDB() {
        return "hello world!";
    }
}

```

# 服务端 Channel

![](image/Pasted%20image%2020250131065711.png)

## 启动流程

## 两个问题

![](image/Pasted%20image%2020250131040046.png)

## 服务端启动


![](image/Pasted%20image%2020250131040217.png)

![](image/Pasted%20image%2020250131040224.png)

### 反射创建服务端 Channel

![](image/Pasted%20image%2020250131040513.png)

- 这里的 newChannel 返回是使用工厂通过反射创建的，是在 ServerBootstrap 里 channel 这个属性配置的

- 之前提到的[两个问题](#两个问题)第一个就很明显了，是在 NioScoketChaeenl 里就有默认构造函数

![](image/Pasted%20image%2020250131041324.png)

![](image/Pasted%20image%2020250131041120.png)

### 初始化服务端 Channel

![](image/Pasted%20image%2020250131041859.png)

![](image/Pasted%20image%2020250131041948.png)

### 注册 selector

![](image/Pasted%20image%2020250131042644.png)

### 端口绑定

![](image/Pasted%20image%2020250131045732.png)