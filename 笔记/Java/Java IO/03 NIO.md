# BIO 中的阻塞方法

![](image/Pasted%20image%2020241219051459.png)

# 非阻塞式 NIO

![](image/Pasted%20image%2020241219051701.png)

# NIO 编程模型



# Channel 和 Buffer

![](image/Pasted%20image%2020241219053105.png)

## Buffer 基本操作

| 操作               | 描述                                                      |
| ---------------- | ------------------------------------------------------- |
| `clear()`        | 准备缓冲区以便写入数据。将 position 设为 0，将 limit 设为 capacity。        |
| `flip()`         | 准备缓冲区以便读取数据。将 limit 设为当前 position，然后将 position 设为 0。    |
| `rewind()`       | 准备缓冲区以便重读已经包含的数据。将 position 设为 0，不改变 limit。             |
| `compact()`      | 将未读的数据复制到缓冲区的开头。将 position 设为未读数据的数量，limit 设为 capacity。 |
| `mark()`         | 标记当前 position，以便后续调用 reset() 恢复到此位置。                    |
| `reset()`        | 恢复到先前标记的位置。必须在调用 mark() 之后使用，否则会抛出异常。                   |
| `position()`     | 获取或设置当前 position。                                       |
| `limit()`        | 获取或设置当前 limit。                                          |
| `capacity()`     | 返回缓冲区的容量，容量不能改变。                                        |
| `remaining()`    | 返回 limit 和 position 之间的元素数量。                            |
| `hasRemaining()` | 判断在当前位置和 limit 之间是否有元素。                                 |

## Channel 基本操作

| 操作方法                                            | 描述                                             |
| ----------------------------------------------- | ---------------------------------------------- |
| `read(ByteBuffer)`                              | 从 `Channel` 读取数据到 `Buffer` 中                   |
| `write(ByteBuffer)`                             | 将 `Buffer` 中的数据写入到 `Channel` 中                 |
| `close()`                                       | 关闭 `Channel`，释放资源                              |
| `position()`                                    | 获取当前 `Channel` 的位置                             |
| `position(long)`                                | 设置 `Channel` 的位置                               |
| `size()`                                        | 获取 `Channel` 中的文件的大小（对于文件 `Channel`）           |
| `truncate(long)`                                | 截断 `Channel` 中的文件，使其大小为指定的字节数（对于文件 `Channel`）  |
| `force(boolean)`                                | 将 `Channel` 中的所有未写入数据强制写入底层存储器（对于文件 `Channel`） |
| `transferTo(long, long, WritableByteChannel)`   | 将数据从当前` Channel` 传输到目标 `Channel`               |
| `transferFrom(ReadableByteChannel, long, long)` | 从源 `Channel` 传输数据到当前 `Channel`                 |

### 几个重要的 Channel

![](image/Pasted%20image%2020241219054102.png)

## Selector

### Selector 操作表格

|操作|描述|
|---|---|
|`select()`|阻塞到至少有一个通道在你注册的事件上就绪。返回就绪通道的数量。|
|`selectNow()`|非阻塞地执行选择操作。立即返回，就绪通道的数量可能为零。|
|`select(long timeout)`|阻塞等待指定的时间，直到至少有一个通道就绪。返回就绪通道的数量。|
|`wakeup()`|使一个阻塞的选择操作立即返回。|
|`close()`|关闭 Selector 并释放所有相关资源。|
|`keys()`|返回所有注册到此 Selector 的 SelectionKey 集合。|
|`selectedKeys()`|返回已选择的 SelectionKey 集合（即就绪的通道）。|

### Channel 状态表格

| 状态             | 描述                               |
| -------------- | -------------------------------- |
| `open`         | 通道已经打开，可以进行读写等操作。                |
| `closed`       | 通道已关闭，不能进行任何 I/O 操作。             |
| `blocking`     | 通道处于阻塞模式，I/O 操作会阻塞当前线程直到完成。      |
| `non-blocking` | 通道处于非阻塞模式，I/O 操作立即返回，可能没有处理任何数据。 |
| `ready`        | 通道已经准备好进行某种 I/O 操作（如读、写、连接）。     |
| `not-ready`    | 通道尚未准备好进行某种 I/O 操作。              |

# 代码

## 多方法实现文件拷贝

- 因为到了新版本，很多 io 操作底层都用 NIO 改写了

```java
interface FileCopyRunner {

    void copyFile(File source, File target);

}

public class FileCopyDemo {
    private static final int ROUNDS = 5;

    private static void benchmark(FileCopyRunner test, File source, File target) {
        long elapsed = 0L;
        for (int i=0; i<ROUNDS; i++) {
            long startTime = System.currentTimeMillis();
            test.copyFile(source, target);
            elapsed += System.currentTimeMillis() - startTime;
            target.delete();
        }
        System.out.println(test + ": " + elapsed / ROUNDS);
    }

    private static void close(Closeable closeable) {
        if (closeable != null) {
            try {
                closeable.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

    }

    public static void main(String[] args) {

        FileCopyRunner noBufferStreamCopy = new FileCopyRunner() {
            @Override
            public void copyFile(File source, File target) {
                InputStream fin = null;
                OutputStream fout = null;
                try {
                    fin = new FileInputStream(source);
                    fout = new FileOutputStream(target);

                    int result;
                    while ((result = fin.read()) != -1) {
                        fout.write(result);
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    close(fin);
                    close(fout);
                }
            }

            @Override
            public String toString() {
                return "noBufferStreamCopy";
            }
        };

        FileCopyRunner bufferedStreamCopy = new FileCopyRunner() {
            @Override
            public void copyFile(File source, File target) {
                InputStream fin = null;
                OutputStream fout = null;
                try {
                    fin = new BufferedInputStream(new FileInputStream(source));
                    fout = new BufferedOutputStream(new FileOutputStream(target));

                    byte[] buffer = new byte[1024];

                    int result;
                    while ((result = fin.read(buffer)) != -1) {
                        fout.write(buffer, 0, result);
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    close(fin);
                    close(fout);
                }
            }

            @Override
            public String toString() {
                return "bufferedStreamCopy";
            }
        };

        FileCopyRunner nioBufferCopy = new FileCopyRunner() {
            @Override
            public void copyFile(File source, File target) {
                FileChannel fin = null;
                FileChannel fout = null;

                try {
                    fin = new FileInputStream(source).getChannel();
                    fout = new FileOutputStream(target).getChannel();

                    ByteBuffer buffer = ByteBuffer.allocate(1024);
                    while (fin.read(buffer) != -1) {
                        buffer.flip();
                        while (buffer.hasRemaining()) {
                            fout.write(buffer);
                        }
                        buffer.clear();
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    close(fin);
                    close(fout);
                }
            }

            @Override
            public String toString() {
                return "nioBufferCopy";
            }
        };

        FileCopyRunner nioTransferCopy = new FileCopyRunner() {
            @Override
            public void copyFile(File source, File target) {
                FileChannel fin = null;
                FileChannel fout = null;
                try {
                    fin = new FileInputStream(source).getChannel();
                    fout = new FileOutputStream(target).getChannel();
                    long transferred = 0L;
                    long size = fin.size();
                    while (transferred != size) {
                        transferred += fin.transferTo(0, size, fout);
                    }
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                } finally {
                    close(fin);
                    close(fout);
                }
            }

            @Override
            public String toString() {
                return "nioTransferCopy";
            }
        };

        File smallFile = new File("/var/tmp/smallFile");
        File smallFileCopy = new File("/var/tmp/smallFile-copy");

        System.out.println("---Copying small file---");
        benchmark(noBufferStreamCopy, smallFile, smallFileCopy);
        benchmark(bufferedStreamCopy, smallFile, smallFileCopy);
        benchmark(nioBufferCopy, smallFile, smallFileCopy);
        benchmark(nioTransferCopy, smallFile, smallFileCopy);

        File bigFile = new File("/var/tmp/bigFile");
        File bigFileCopy = new File("/var/tmp/bigFile-copy");

        System.out.println("---Copying big file---");
        //benchmark(noBufferStreamCopy, bigFile, bigFileCopy);
        benchmark(bufferedStreamCopy, bigFile, bigFileCopy);
        benchmark(nioBufferCopy, bigFile, bigFileCopy);
        benchmark(nioTransferCopy, bigFile, bigFileCopy);

        File hugeFile = new File("/var/tmp/hugeFile");
        File hugeFileCopy = new File("/var/tmp/hugeFile-copy");

        System.out.println("---Copying huge file---");
        //benchmark(noBufferStreamCopy, hugeFile, hugeFileCopy);
        benchmark(bufferedStreamCopy, hugeFile, hugeFileCopy);
        benchmark(nioBufferCopy, hugeFile, hugeFileCopy);
        benchmark(nioTransferCopy, hugeFile, hugeFileCopy);

    }

}

```

## 多人聊天室

### Client

```java
public class ChatClient {

    private static final String DEFAULT_SERVER_HOST = "127.0.0.1";
    private static final int DEFAULT_SERVER_PORT = 8888;
    private static final String QUIT = "quit";
    private static final int BUFFER = 1024;

    private String host;
    private int port;
    private SocketChannel client;
    private ByteBuffer rBuffer = ByteBuffer.allocate(BUFFER);
    private ByteBuffer wBuffer = ByteBuffer.allocate(BUFFER);
    private Selector selector;
    private Charset charset = Charset.forName("UTF-8");

    public ChatClient() {
        this(DEFAULT_SERVER_HOST, DEFAULT_SERVER_PORT);
    }

    public ChatClient(String host, int port) {
        this.host = host;
        this.port = port;
    }

    public boolean readyToQuit(String msg) {
        return QUIT.equals(msg);
    }

    private void close(Closeable closable) {
        if (closable != null) {
            try {
                closable.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private void start() {
        try {
            client = SocketChannel.open();
            client.configureBlocking(false);

            selector = Selector.open();
            client.register(selector, SelectionKey.OP_CONNECT);
            client.connect(new InetSocketAddress(host, port));

            while (true) {
                selector.select();
                Set<SelectionKey> selectionKeys = selector.selectedKeys();
                for (SelectionKey key : selectionKeys) {
                    handles(key);
                }
                selectionKeys.clear();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ClosedSelectorException e) {
            // 用户正常退出
        } finally {
            close(selector);
        }

    }

    private void handles(SelectionKey key) throws IOException {
        // CONNECT事件 - 连接就绪事件
        if (key.isConnectable()) {
            SocketChannel client = (SocketChannel) key.channel();
            if (client.isConnectionPending()) {
                client.finishConnect();
                // 处理用户的输入
                new Thread(new UserInputHandler(this)).start();
            }
            client.register(selector, SelectionKey.OP_READ);
        }
        // READ事件 -  服务器转发消息
        else if (key.isReadable()) {
            SocketChannel client = (SocketChannel) key.channel();
            String msg = receive(client);
            if (msg.isEmpty()) {
                // 服务器异常
                close(selector);
            } else {
                System.out.println(msg);
            }
        }
    }

    public void send(String msg) throws IOException {
        if (msg.isEmpty()) {
            return;
        }

        wBuffer.clear();
        wBuffer.put(charset.encode(msg));
        wBuffer.flip();
        while (wBuffer.hasRemaining()) {
            client.write(wBuffer);
        }

        // 检查用户是否准备退出
        if (readyToQuit(msg)) {
            close(selector);
        }
    }

    private String receive(SocketChannel client) throws IOException {
        rBuffer.clear();
        while (client.read(rBuffer) > 0);
        rBuffer.flip();
        return String.valueOf(charset.decode(rBuffer));
    }

    public static void main(String[] args) {
        ChatClient client = new ChatClient("127.0.0.1", 7777);
        client.start();
    }
}

```

```java
public class UserInputHandler implements Runnable {

    private ChatClient chatClient;

    public UserInputHandler(ChatClient chatClient) {
        this.chatClient = chatClient;
    }

    @Override
    public void run() {
        try {
            // 等待用户输入消息
            BufferedReader consoleReader =
                    new BufferedReader(new InputStreamReader(System.in));
            while (true) {
                String input = consoleReader.readLine();

                // 向服务器发送消息
                chatClient.send(input);

                // 检查用户是否准备退出
                if (chatClient.readyToQuit(input)) {
                    break;
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
```

### Server

```java
public class ChatServer {

    private static final int DEFAULT_PORT = 8888;
    private static final String QUIT = "quit";
    private static final int BUFFER = 1024;

    private ServerSocketChannel server;
    private Selector selector;
    private ByteBuffer rBuffer = ByteBuffer.allocate(BUFFER);
    private ByteBuffer wBuffer = ByteBuffer.allocate(BUFFER);
    private Charset charset = Charset.forName("UTF-8");
    private int port;

    public ChatServer() {
        this(DEFAULT_PORT);
    }

    public ChatServer(int port) {
        this.port = port;
    }

    private void start() {
        try {
            server = ServerSocketChannel.open();
            server.configureBlocking(false);
            server.socket().bind(new InetSocketAddress(port));

            selector = Selector.open();
            server.register(selector, SelectionKey.OP_ACCEPT);
            System.out.println("启动服务器， 监听端口：" + port + "...");

            while (true) {
                selector.select();
                Set<SelectionKey> selectionKeys = selector.selectedKeys();
                for (SelectionKey key : selectionKeys) {
                    // 处理被触发的事件
                    handles(key);
                }
                selectionKeys.clear();
            }

        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            close(selector);
        }

    }

    private void handles(SelectionKey key) throws IOException {
        // ACCEPT事件 - 和客户端建立了连接
        if (key.isAcceptable()) {
            ServerSocketChannel server = (ServerSocketChannel) key.channel();
            SocketChannel client = server.accept();
            client.configureBlocking(false);
            client.register(selector, SelectionKey.OP_READ);
            System.out.println(getClientName(client) + "已连接");
        }
        // READ事件 - 客户端发送了消息
        else if (key.isReadable()) {
            SocketChannel client = (SocketChannel) key.channel();
            String fwdMsg = receive(client);
            if (fwdMsg.isEmpty()) {
                // 客户端异常
                key.cancel();
                selector.wakeup();
            } else {
                System.out.println(getClientName(client) + ":" + fwdMsg);
                forwardMessage(client, fwdMsg);

                // 检查用户是否退出
                if (readyToQuit(fwdMsg)) {
                    key.cancel();
                    selector.wakeup();
                    System.out.println(getClientName(client) + "已断开");
                }
            }

        }
    }

    private void forwardMessage(SocketChannel client, String fwdMsg) throws IOException {
        for (SelectionKey key: selector.keys()) {
            Channel connectedClient = key.channel();
            if (connectedClient instanceof ServerSocketChannel) {
                continue;
            }

            if (key.isValid() && !client.equals(connectedClient)) {
                wBuffer.clear();
                wBuffer.put(charset.encode(getClientName(client) + ":" + fwdMsg));
                wBuffer.flip();
                while (wBuffer.hasRemaining()) {
                    ((SocketChannel)connectedClient).write(wBuffer);
                }
            }
        }
    }

    private String receive(SocketChannel client) throws IOException {
        rBuffer.clear();
        while(client.read(rBuffer) > 0);
        rBuffer.flip();
        return String.valueOf(charset.decode(rBuffer));
    }

    private String getClientName(SocketChannel client) {
        return "客户端[" + client.socket().getPort() + "]";
    }

    private boolean readyToQuit(String msg) {
        return QUIT.equals(msg);
    }

    private void close(Closeable closable) {
        if (closable != null) {
            try {
                closable.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args) {
        ChatServer chatServer = new ChatServer(7777);
        chatServer.start();
    }
}

```