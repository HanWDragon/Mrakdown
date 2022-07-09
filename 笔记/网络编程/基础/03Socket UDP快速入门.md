# UDP是什么

![](image/Pasted%20image%2020220211225415.png)

## 为什么不可靠

![](image/Pasted%20image%2020220211225526.png)

## 能做什么

![](image/Pasted%20image%2020220211225708.png)

## UDP包最大长度

![](image/Pasted%20image%2020220211225801.png)

# UDP核心API

## DatagramSocket

![](image/Pasted%20image%2020220211230006.png)

![](image/Pasted%20image%2020220211230104.png)

![](image/Pasted%20image%2020220211230151.png)

## DatagramPacket

![](image/Pasted%20image%2020220211230441.png)

![](image/Pasted%20image%2020220211230536.png)

![](image/Pasted%20image%2020220211230618.png)

![](image/Pasted%20image%2020220211230717.png)

![](image/Pasted%20image%2020220211230742.png)

# UDP 单播、广播（组播）、多播

![](image/Pasted%20image%2020220211231416.png)

## IP地址类别

![](image/Pasted%20image%2020220211231719.png)

## 广播地址

![](image/Pasted%20image%2020220211231928.png)

## 网络信息

![](image/Pasted%20image%2020220211232054.png)

![](image/Pasted%20image%2020220211232038.png)

## IP地址构成

![](image/Pasted%20image%2020220211232142.png)

## 广播地址运算

![](image/Pasted%20image%2020220211232452.png)

![](image/Pasted%20image%2020220211232527.png)

![](image/Pasted%20image%2020220211232733.png)

## 广播通信问题

![](image/Pasted%20image%2020220211232858.png)

# 互联网搜索案例

![](image/Pasted%20image%2020220211233039.png)

## 代码演示

```java
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.util.UUID;

/**
 * UDP 提供者，用于提供服务
 */
public class UDPProvider {

    public static void main(String[] args) throws IOException {
        // 生成一份唯一标示
        String sn = UUID.randomUUID().toString();
        Provider provider = new Provider(sn);
        provider.start();

        // 读取任意键盘信息后可以退出
        //noinspection ResultOfMethodCallIgnored
        System.in.read();
        provider.exit();
    }

    private static class Provider extends Thread {
        private final String sn;
        private boolean done = false;
        private DatagramSocket ds = null;

        public Provider(String sn) {
            super();
            this.sn = sn;
        }

        @Override
        public void run() {
            super.run();

            System.out.println("UDPProvider Started.");

            try {
                // 监听20000 端口
                ds = new DatagramSocket(20000);

                while (!done) {

                    // 构建接收实体
                    final byte[] buf = new byte[512];
                    DatagramPacket receivePack = new DatagramPacket(buf, buf.length);

                    // 接收
                    ds.receive(receivePack);

                    // 打印接收到的信息与发送者的信息
                    // 发送者的IP地址
                    String ip = receivePack.getAddress().getHostAddress();
                    int port = receivePack.getPort();
                    int dataLen = receivePack.getLength();
                    String data = new String(receivePack.getData(), 0, dataLen);
                    System.out.println("UDPProvider receive form ip:" + ip
                            + "\tport:" + port + "\tdata:" + data);

                    // 解析端口号
                    int responsePort = MessageCreator.parsePort(data);
                    if (responsePort != -1) {
                        // 构建一份回送数据
                        String responseData = MessageCreator.buildWithSn(sn);
                        byte[] responseDataBytes = responseData.getBytes();
                        // 直接根据发送者构建一份回送信息
                        DatagramPacket responsePacket = new DatagramPacket(responseDataBytes,
                                responseDataBytes.length,
                                receivePack.getAddress(),
                                responsePort);

                        ds.send(responsePacket);
                    }

                }

            } catch (Exception ignored) {
            } finally {
                close();
            }

            // 完成
            System.out.println("UDPProvider Finished.");
        }


        private void close() {
            if (ds != null) {
                ds.close();
                ds = null;
            }
        }


        /**
         * 提供结束
         */
        void exit() {
            done = true;
            close();
        }

    }

}

```

```java
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.CountDownLatch;

/**
 * UDP 搜索者，用于搜索服务支持方
 */
public class UDPSearcher {
    private static final int LISTEN_PORT = 30000;


    public static void main(String[] args) throws IOException, InterruptedException {
        System.out.println("UDPSearcher Started.");

        Listener listener = listen();
        sendBroadcast();

        // 读取任意键盘信息后可以退出
        //noinspection ResultOfMethodCallIgnored
        System.in.read();

        List<Device> devices = listener.getDevicesAndClose();

        for (Device device : devices) {
            System.out.println("Device:" + device.toString());
        }

        // 完成
        System.out.println("UDPSearcher Finished.");
    }

    private static Listener listen() throws InterruptedException {
        System.out.println("UDPSearcher start listen.");
        CountDownLatch countDownLatch = new CountDownLatch(1);
        Listener listener = new Listener(LISTEN_PORT, countDownLatch);
        listener.start();

        countDownLatch.await();
        return listener;
    }

    private static void sendBroadcast() throws IOException {
        System.out.println("UDPSearcher sendBroadcast started.");

        // 作为搜索方，让系统自动分配端口
        DatagramSocket ds = new DatagramSocket();


        // 构建一份请求数据
        String requestData = MessageCreator.buildWithPort(LISTEN_PORT);
        byte[] requestDataBytes = requestData.getBytes();
        // 直接构建packet
        DatagramPacket requestPacket = new DatagramPacket(requestDataBytes,
                requestDataBytes.length);
        // 20000端口, 广播地址
        requestPacket.setAddress(InetAddress.getByName("255.255.255.255"));
        requestPacket.setPort(20000);

        // 发送
        ds.send(requestPacket);
        ds.close();

        // 完成
        System.out.println("UDPSearcher sendBroadcast finished.");
    }

    private static class Device {
        final int port;
        final String ip;
        final String sn;

        private Device(int port, String ip, String sn) {
            this.port = port;
            this.ip = ip;
            this.sn = sn;
        }

        @Override
        public String toString() {
            return "Device{" +
                    "port=" + port +
                    ", ip='" + ip + '\'' +
                    ", sn='" + sn + '\'' +
                    '}';
        }
    }

    private static class Listener extends Thread {
        private final int listenPort;
        private final CountDownLatch countDownLatch;
        private final List<Device> devices = new ArrayList<>();
        private boolean done = false;
        private DatagramSocket ds = null;


        public Listener(int listenPort, CountDownLatch countDownLatch) {
            super();
            this.listenPort = listenPort;
            this.countDownLatch = countDownLatch;
        }

        @Override
        public void run() {
            super.run();

            // 通知已启动
            countDownLatch.countDown();
            try {
                // 监听回送端口
                ds = new DatagramSocket(listenPort);


                while (!done) {
                    // 构建接收实体
                    final byte[] buf = new byte[512];
                    DatagramPacket receivePack = new DatagramPacket(buf, buf.length);

                    // 接收
                    ds.receive(receivePack);

                    // 打印接收到的信息与发送者的信息
                    // 发送者的IP地址
                    String ip = receivePack.getAddress().getHostAddress();
                    int port = receivePack.getPort();
                    int dataLen = receivePack.getLength();
                    String data = new String(receivePack.getData(), 0, dataLen);
                    System.out.println("UDPSearcher receive form ip:" + ip
                            + "\tport:" + port + "\tdata:" + data);

                    String sn = MessageCreator.parseSn(data);
                    if (sn != null) {
                        Device device = new Device(port, ip, sn);
                        devices.add(device);
                    }
                }
            } catch (Exception ignored) {

            } finally {
                close();
            }
            System.out.println("UDPSearcher listener finished.");

        }

        private void close() {
            if (ds != null) {
                ds.close();
                ds = null;
            }
        }

        List<Device> getDevicesAndClose() {
            done = true;
            close();
            return devices;
        }
    }
}

```

```java
public class MessageCreator {
    private static final String SN_HEADER = "收到暗号，我是（SN）:";
    private static final String PORT_HEADER = "这是暗号，请回电端口（Port）:";

    public static String buildWithPort(int port) {
        return PORT_HEADER + port;
    }

    public static int parsePort(String data) {
        if (data.startsWith(PORT_HEADER)) {
            return Integer.parseInt(data.substring(PORT_HEADER.length()));
        }

        return -1;
    }

    public static String buildWithSn(String sn) {
        return SN_HEADER + sn;
    }

    public static String parseSn(String data) {
        if (data.startsWith(SN_HEADER)) {
            return data.substring(SN_HEADER.length());
        }
        return null;
    }

}

```