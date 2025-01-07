# 什么是网络编程

![](image/Pasted%20image%2020220211180556.png)

# 什么是网络

![](image/Pasted%20image%2020220211180221.png)

# 局域网

![](image/Pasted%20image%2020220211180237.png)

# 互联网

![](image/Pasted%20image%2020220211180353.png)

# 七层网络模型-OSI

![](image/Pasted%20image%2020220211180637.png)

## 编程

![](image/Pasted%20image%2020220211180851.png)

## 网络模型对应关系

![](image/Pasted%20image%2020220211180957.png)

# Socket与TCP、UDP

**Socket是对TCP和UDP的封装**

## What is Socket？

![](image/Pasted%20image%2020220211181642.png)

## Socket的作用与组成

![](image/Pasted%20image%2020220211181758.png)

## Socket传输原理

![](image/Pasted%20image%2020220211181837.png)

## Socket之TCP

![](image/Pasted%20image%2020220211182042.png)

## Socket之UCP

![](image/Pasted%20image%2020220211182151.png)

## TCP传输图解

![](image/Pasted%20image%2020220211182231.png)

## UDP传输图解

![](image/Pasted%20image%2020220211182657.png)

# Client-Server Application

![](image/Pasted%20image%2020220211215638.png)

# Socket TCP牛刀小试

![](image/Pasted%20image%2020220211220115.png)

## 代码

### 客户端

```java
import java.io.*;
import java.net.Inet4Address;
import java.net.InetSocketAddress;
import java.net.Socket;

public class Client {
    public static void main(String[] args) throws IOException {
        Socket socket = new Socket();
        // 超时时间
        socket.setSoTimeout(3000);

        // 连接本地，端口2000；超时时间3000ms
        socket.connect(new InetSocketAddress(Inet4Address.getLocalHost(), 2000), 3000);

        System.out.println("已发起服务器连接，并进入后续流程～");
        System.out.println("客户端信息：" + socket.getLocalAddress() + " P:" + socket.getLocalPort());
        System.out.println("服务器信息：" + socket.getInetAddress() + " P:" + socket.getPort());

        try {
            // 发送接收数据
            todo(socket);
        } catch (Exception e) {
            System.out.println("异常关闭");
        }

        // 释放资源
        socket.close();
        System.out.println("客户端已退出～");

    }

    private static void todo(Socket client) throws IOException {
        // 构建键盘输入流
        InputStream in = System.in;
        BufferedReader input = new BufferedReader(new InputStreamReader(in));


        // 得到Socket输出流，并转换为打印流
        OutputStream outputStream = client.getOutputStream();
        PrintStream socketPrintStream = new PrintStream(outputStream);


        // 得到Socket输入流，并转换为BufferedReader
        InputStream inputStream = client.getInputStream();
        BufferedReader socketBufferedReader = new BufferedReader(new InputStreamReader(inputStream));

        boolean flag = true;
        do {
            // 键盘读取一行
            String str = input.readLine();
            // 发送到服务器
            socketPrintStream.println(str);


            // 从服务器读取一行
            String echo = socketBufferedReader.readLine();
            if ("bye".equalsIgnoreCase(echo)) {
                flag = false;
            }else {
                System.out.println(echo);
            }
        }while (flag);

        // 资源释放
        socketPrintStream.close();
        socketBufferedReader.close();

    }


}

```

### 服务端

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket server = new ServerSocket(2000);


        System.out.println("服务器准备就绪～");
        System.out.println("服务器信息：" + server.getInetAddress() + " P:" + server.getLocalPort());


        // 等待客户端连接
        for (; ; ) {
            // 得到客户端
            Socket client = server.accept();
            // 客户端构建异步线程
            ClientHandler clientHandler = new ClientHandler(client);
            // 启动线程
            clientHandler.start();
        }

    }

    /**
     * 客户端消息处理
     */
    private static class ClientHandler extends Thread {
        private Socket socket;
        private boolean flag = true;

        ClientHandler(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void run() {
            super.run();
            System.out.println("新客户端连接：" + socket.getInetAddress() +
                    " P:" + socket.getPort());

            try {
                // 得到打印流，用于数据输出；服务器回送数据使用
                PrintStream socketOutput = new PrintStream(socket.getOutputStream());
                // 得到输入流，用于接收数据
                BufferedReader socketInput = new BufferedReader(new InputStreamReader(
                        socket.getInputStream()));

                do {
                    // 客户端拿到一条数据
                    String str = socketInput.readLine();
                    if ("bye".equalsIgnoreCase(str)) {
                        flag = false;
                        // 回送
                        socketOutput.println("bye");
                    } else {
                        // 打印到屏幕。并回送数据长度
                        System.out.println(str);
                        socketOutput.println("回送：" + str.length());
                    }

                } while (flag);

                socketInput.close();
                socketOutput.close();

            } catch (Exception e) {
                System.out.println("连接异常断开");
            } finally {
                // 连接关闭
                try {
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            System.out.println("客户端已退出：" + socket.getInetAddress() +
                    " P:" + socket.getPort());

        }
    }
}

```

# 报文、协议、MAC地址

## 报文段

![](image/Pasted%20image%2020220211223653.png)

![](image/Pasted%20image%2020220211223742.png)

## 传输协议

![](image/Pasted%20image%2020220211223808.png)

## MAC地址

![](image/Pasted%20image%2020220211223923.png)

# IP、端口、远程服务器

## IP地址

![](image/Pasted%20image%2020220211224124.png)

![](image/Pasted%20image%2020220211224143.png)

### IPv4

![](image/Pasted%20image%2020220211224252.png)

### IPv6

![](image/Pasted%20image%2020220211224353.png)

![](image/Pasted%20image%2020220211224424.png)

## 端口

![](image/Pasted%20image%2020220211224500.png)

![](image/Pasted%20image%2020220211224658.png)

### 特殊端口

![](image/Pasted%20image%2020220211224541.png)

## 数据传输层次

![](image/Pasted%20image%2020220211224840.png)

## 远程服务器

![](image/Pasted%20image%2020220211224936.png)

## 连接示意图

![](image/Pasted%20image%2020220211225033.png)

![](image/Pasted%20image%2020220211225116.png)

## Web请求流程

![](image/Pasted%20image%2020220211225139.png)

