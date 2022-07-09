java.io中最核心的一个概念就是流（Stream），面向流的编程。
在Java中，一个流要么是输出流，要么是输入流，不可能同时既是输入流又是输出流。
本质上，它实际上是一段连续的内存。数据的读和写都是通过Buffer来实现。
对比数组，Buffer还提供对于数据的结构化访问方式，并且可以追踪到系统的读写过程。
Java中的 7 种原生数据类型都有对应的Buffer类型，如IntBuffer，LongBuffer，ByteBuffer等等，但是没有BooleanBuffer类型，还有一种特殊类型就是MappedByteBuffer。
Channel指的是可以想Buffer中向其写入数据或者是从其中读取数据的对象，它类似与java.io的Stream
所有数据的读写都是通过Buffer来进行的，永远不会出现直接向Channel写对数据的情况，或者是直接从Chaneel读取数据的情况。
与Stream不同的是，Channel是双向的，一个流只能是InputStream或者是OutputStream，Channel打开后则可以进行读取，写入或者读写。
由于Channel是双向的，因此它能更好的反映出底层操作系统的真实情况，在Linux系统中，底层操作系统的通道就是双向的。
关于NIO Buffer中的 3 个重要状态属性的含义：position，limit与capacity。
0 <= mark <= position <= limit <=capacity
通过NIO读取文件涉及到的3个步骤：
1. 从FileInputStream或去FileChannel对象
2. 创建Buffer
3. 将数据从Channel读取到Buffer中

绝对方法与相对方法的含义：
1. 相对方法：limit值与position值会在操作时被考虑到
2. 绝对方法：完全忽略掉limit值与position值。

