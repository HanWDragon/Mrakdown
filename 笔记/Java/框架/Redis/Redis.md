## Redis简介

Redis是一种数据库。能够存储数据、管理数据的一种软件。

## 数据库应用的发展历程：

单机数据库时代

缓存、水平切分时代

读写分离时代

分表分库时代(集群)

关系型数据库

- oracle
- mysql
- DB2
- sqlserver ....

非关系型数据库(NoSql) 彻底改变底层存储机制。不再采用关系数据模型，而是采用聚合数据结构存储数据

- redis

- mongoDB

- HBase ....

## Nosql数据模型

关系型数据库：表

	      tbl_student                            tbl_clazz
		       id    name    age    clazz_id          id       name
		       1001  zhangsan 20      111             111      clazz1
		       1002  lisi     21      111             222      clazz2

非关系型数据库  聚合模型  把一组相关联的数据作为一个整体进行存储和管理

- JSON 数据保存到键值对中、数据和数据之间用逗号隔开，{}表示对象，[]表示数组   

```json
	{
		id:1001,
		name:zhangsan,
		age:20,
	class:{
				id:111,
				name:clazz1
		}
	}
	{
		id:1002,
		name:lisi,
		age:21,
		class:{
			id:111,
			name:class1
		}
	}	             
```

- K-V键值对
- 列簇
- 图表模型 ....

Redis采用的是K-V模型存储数据的。

Redis是一个用C语言编写的、开源的、基于内存运行并支持持久化的、高性能的NoSQL数据库.也是当前热门的NoSQL数据库之一

Redis中的数据大部分时间都是存储内存中的，适合存储频繁访问、数据量比较小的数据的缓存数据库

## 安装redis

参考安装手册

1. 解压：tar -zxvf ...

2. 编译：make
	         需要先安装gcc
	         编译结果：在redis的安装目录下src目录中，生成redis的一系列可执行文件。

3. 安装：make install
	         把redis的安装目录下src目录中生成redis的一系列可执行文件拷贝到/usr/local/bin中，
		     在任何目录下都可以执行redis命令。

4. 启动redis服务：

	- 前台启动：在任何目录下执行 redis-server

	- 后台启动：在任何目录下执行 redis-server &

	- 启动redis服务时，指定配置文件：redis-server redis.conf &

5. 关闭redis服务：

  - 通过kill命令：

```shell
		       ps -ef|grep redis查看pid
		       kill -9 pid
```

  - 通过redis-cli命令关闭：

```shell
		       redis-cli shutdown
```

6. redis的客户端：用来连接redis服务，向redis服务端发送命令，并且显示redis服务处理结果

	redis-cli：是redis自带客户端，使用命令redis-cli就可以启动redis的客户端程序。


	redis-cli：默认连接127.0.0.1(本机)的6379端口上的redis服务。
	
	redis-cli -p 端口号：连接127.0.0.1(本机)的指定端口上的redis服务。
	redis-cli -h ip地址 -p 端口：连接指定ip主机上的指定端口的redis服务。
	退出客户端：在客户端执行命令：exit或者quit

## redis的基本知识：

- 测试redis服务的性能：
	       `redis-benchmark` 
	
- 查看redis服务是否正常运行：
	       `ping  如果正常---pong`
	
- 查看redis服务器的统计信息：
	       info  查看redis服务的所有统计信息
	       info [信息段] 查看redis服务器的指定的统计信息，如：`info Replication`
	
- redis的数据库实例：作用类似于mysql的数据库实例，redis中的数据库实例只能由redis服务来创建和维护，开发人员不能修改和自行创建数据库实例；默认情况下，redis会自动创建16个数据库实例，并且给这些数据库实例进行编号，从0开始，一直到15，使用时通过编号来使用数据库；可以通过配置文件，指定redis自动创建的数据库个数；redis的每一个数据库实例本身占用的存储空间是很少的，所以也不造成存储空间的太多浪费。

- 默认情况下，redis客户端连接的是编号是0的数据库实例；可以使用select index切换数据库实例。

- 查看当前数据库实例中所有key的数量：dbsize

- 查看当前数据库实例中所有的key：keys *   

- 清空数据库实例：flushdb

- 清空所有的数据库实例：flushall

- 查看redis中所有的配置信息：config get *      

-  查看redis中的指定的配置信息：config get parameter
	
## Redis的五种数据结构：

程序是用来处理数据的，Redis是用来存储数据的；

程序处理完的数据要存储到redis中，不同特点的数据要存储在Redis中不同类型的数据结构中
字符串：   zhangsan  20   true                    			 string 单key:单value:                username:zhangsan age:20
list列表：  13900009999 zs@163.com 321321     list      单key:多有序value:        contacts:13900009999,xxx,xxxx
set集合：  beijing shanghai chongqing tianjin     set      单key:多无序value:        city:bj sh cq tj
pojo：       id:1001,name:zhangsan,age:20           hash  单key:对象(属性:值):       student​id:1001,name:zhangsan,age:20
	                                             	  	  	  	          	zset    单key:多有序vlaue:        city:   1000 tj,1200 cq,1500 sh,2000 bj	

## redis中的操作命令：

- redis中有关key的操作命令：

	- 查看数据库中的key：keys pattern
		*：匹配0个或者多个字符
		?: 匹配1个字符
		[]:匹配[]里边的1个字符

		keys \*：查看数据库中所有的key
		keys k\*:查看数据库中所有以k开头的key
		keys h\*o：查看数据库中所有以h开头、以o结尾的key
		keys h?o: 查看数据库中所有以h开头、以o结尾的、并且中间只有一个字符的key
		keys h[abc]llo：查看数据库中所有以h开头以llo结尾，并且h后边只能取abc中的一个字符的key	       
		
	- 判断key在数据库中是否存在：exists key 
		
		如果存在，则返回1；如果不存在，则返回0
		exists key [key key ....] 返回值是存在的key的数量
		exists k1
		exists k1 k2 k3 hello
		
	- 移动指定key到指定的数据库实例：move key index
		move k 1
	
	- 查看指定key的剩余生存时间：ttl key
	
		如果key没有设置生存时间，返回-1
		如果key不存在，返回-2
		ttl k1
		ttl k2
		
	- 设置key的最大生存时间：expire key seconds
					         expire k2 20
		
	- 查看指定key的数据类型：type key
					        type k1
		
	- 重命名key： rename key newkey
					        rename hello k2
		
	- 删除指定的key：del key [key key .....] 
					        返回值是实际删除的key的数量
		del k1 k2 k3 k4
	
- redis中有关string类型数据的操作命令：
					        			      
	- 将string类型的数据设置到redis中：set 键 值
						        			      set zsname zhangsan
		set zsage 20
		set totalRows 100
		set zsage 30 如果key已经存在，则后来的value会把以前的value覆盖掉.
	- 从redis中获取string类型的数据：get 键
						        			      	get zsname
			get zsage
			get totalRows
	- 追加字符串：append key value
						        			      返回追加之后的字符串长度
		如果key不存在，则新创建一个key，并且把value值设置为value。
		set phone 1389999
		append phone 8888
	- 获取字符串数据的长度：strlen key
						        			      strlen phone
	- 将字符串数值进行加1运算：incr key
						        			      返回加1运算之后的数据
		如果key不存在，首先设置一个key，值初始化为0，然后进行incr运算。
		要求key所表示value必须是数值，否则，报错
		incr zsage
		incr age
		incr zsname  报错
	- 将字符串数值进行减1运算：decr key
						        			      返回减1运算之后的数据
		如果key不存在，首先设置一个key，值初始化为0，然后进行decr运算。
		要求key所表示value必须是数值，否则，报错
	- 将字符串数值进行加offset运算：incrby key offset
						        			      返回加offset运算之后的数据
		如果key不存在，首先设置一个key，值初始化为0，然后进行incrby运算。
		要求key所表示value必须是数值，否则，报错
		incrby zsage 10
	- 将字符串数值进行减offset运算：decrby key offset
						        			      返回减offset运算之后的数据
		如果key不存在，首先设置一个key，值初始化为0，然后进行decrby运算。
		要求key所表示value必须是数值，否则，报错
		decrby zsage 10
	- 闭区间获取字符串key中从startIndex到endIndex的字符组成的子字符串：getrange key startIndex endIndex
						        			      下标自左至右，从0开始，依次往后，最后一个字符的下标是字符串长多-1；
	- 设置字符串数据的同时，设置它最大生命周期：setex key seconds value
						        			      setex k1 20 v1
	- 设置string类型的数据value到redis数据库中，当key不存在时设置成功，否则，则放弃设置：setnx key value
						        			      setnx zsage 20
	- 批量将string类型的数据设置到redis中：mset 键1 值1 键2 值2 .....
						        			      mset k1 v1 k2 v2 k3 v3 k4 v4 k5 v5
	- 批量从redis中获取string类型的数据：mget 键1 键2 键3.....
						        			      mget k1 k2 k3 k4 k5 k6 zsname zs age totalRows
	- 批量设置string类型的数据value到redis数据库中，当所有key都不存在时设置成功，否则(只要有一个已经存在)，则全部放弃设置：msetnx 键1 值1 键2 值2 .....
						        			      msetnx kk1 vv1 kk2 vv2 kk3 vv3 k1 v1

- redis中有关list类型数据的操作命令：     单key-多有序value
	一个key对应多个value；
	多个value之间有顺序，最左侧是表头，最右侧是表尾；
	每一个元素都有下标，表头元素的下标是0，依次往后排序，最后一个元素下标是列表长度-1；
	每一个元素的下标又可以用负数表示，负下标表示从表尾计算，最后一个元素下标用-1表示；
	元素在列表中的顺序或者下标由放入的顺序来决定。
	通过key和下标来操作数据。 
	
	- 将一个或者多个值依次插入到列表的表头(左侧)：lpush key value [value value .....]
		lpush list01 1 2 3   结果：3 2 1
		lpush list01 4 5      结果：5 4 3 2 1
	- 获取指定列表中指定下标区间的元素：lrange key startIndex endIndex
		lrange list01 1 3    结果：4 3 2
		lrange list01 1 -2   结果:  4 3 2
		lrange list01 0 -1   结果：5 4 3 2 1
	- 将一个或者多个值依次插入到列表的表尾(右侧)：rpush key value [value value .....]
		rpush list02 a b c   结果：a b c
		rpush list02 d e      结果：a b c d e
		lpush list02 m n     结果:   n m a b c d e
	- 从指定列表中移除并且返回表头元素：lpop key
		lpop list02
	- 从指定列表中移除并且返回表尾元素：rpop key
		rpop list02
	- 获取指定列表中指定下标的元素：lindex key index
		lindex list01 2 结果：3
	- 获取指定列表的长度：llen key
		llen list01
	- 根据count值移除指定列表中跟value相等的数据：lrem key count value
		count>0：从列表的左侧移除count个跟value相等的数据；
	- 截取指定列表中指定下标区间的元素组成新的列表，并且赋值给key：ltrim key startIndex endIndex
		lpush list04 1 2 3 4 5  结果：5 4 3 2 1
		ltrim list04 1 3
		lrange list04 0 -1         结果：4 3 2
	- 将指定列表中指定下标的元素设置为指定值： lset key index value
		lset list04 1 10
	- 将value插入到指定列表中位于pivot元素之前/之后的位置： linsert key before/after pivot vlaue
		linsert list04 before 10 50
		linsert list04 after 10 60
	
- redis中有关set类型数据的操作命令：单key-多无序value
		                                         一个key对应多个vlaue；
	value之间没有顺序，并且不能重复.通过业务数据直接操作集合
	
	- 将一个或者多个元素添加到指定的集合中：sadd key value [value value ....]
			                                         如果元素已经存在，则会忽略。 
		返回成功加入的元素的个数
		sadd set01 a b c a  结果：a b c
		sadd set01 b d e
	- 获取指定集合中所有的元素：smembers key
			                                         smembers set01
	- 判断指定元素在指定集合中是否存在:sismember key member
			                                         存在，返回1
		不存在，返回0
		sismember set01 f
		sismember set01 a
	- 获取指定集合的长度：scard key
			                                         scard set01
	- 移除指定集合中一个或者多个元素：srem key member [member .....]
			                                         不存在的元素会被忽略
		返回成功成功移除的个数
		srem set01 b d m
	- 随机获取指定集合中的一个或者多个元素：srandmember key [count]
			                                         count>0：随机获取的多个元素之间不能重复
		count<0: 随机获取的多个元素之间可能重复
		sadd set02 1 2 3 4 5 6 7 8
		srandmember set02
		srandmember set02 3
		srandmember set02 -3
	- 从指定集合中随机移除一个或者多个元素：spop key [count]
			                                         spop set02
	- 将指定集合中的指定元素移动到另一个元素:smove source dest member
			                                         smove set01 set02 a
	- 获取第一个集合中有、但是其它集合中都没有的元素组成的新集合：sdiff key key [key key ....]
			                                         sdiff set01 set02 set03
	- 获取所有指定集合中都有的元素组成的新集合：sinter key key [key key ....]
			                                         sinter set01 set02 set03
	- 获取所有指定集合中所有元素组成的大集合：sunion key key [key key .....]
			                                         sunion set01 set02 set03
	
- redis中有关hash类型数据的操作命令：单key:field-value
			                                         	                                                 field-value
	studentzs:id-1001
	name-zhangsan
	age-20
	
	.....		
	
	- 将一个或者多个field-vlaue对设置到哈希表中：hset key filed1 value1 [field2 value2 ....] 
		如果key field已经存在，把value会把以前的值覆盖掉
		hset stu1001 id 1001
		hset stu1001 name zhangsan age 20
	
	- 获取指定哈希表中指定field的值：hget key field
		hget stu1001 id
		hget stu1001 name
	
	- 批量将多个field-value对设置到哈希表中： hmset key filed1 value1 [field2 value2 ....] 
		hmset stu1002 id 1002 name lisi age 20
	
	- 批量获取指定哈希表中的field的值：hmget key field1 [field2 field3 ....]
		hmget stu1001 id name age
	
	- 获取指定哈希表中所有的field和value：hgetall key
		hgetall stu1002
	
	- 从指定哈希表中删除一个或者多个field：hdel key field1 [field2 field3 ....]
	
		hdel stu1002 name age
	
	- 获取指定哈希表中所有的filed个数：hlen key
		hlen stu1001
		hlen stu1002
	
	- 判断指定哈希表中是否存在某一个field：hexists key field
		hexists stu1001 name
		hexists stu1002 name
	
	- 获取指定哈希表中所有的field列表：hkeys key
		hkeys stu1001
		hkeys stu1002
	
	- 获取指定哈希表中所有的value列表：hvals key
		hvals stu1001
		hvals stu1002
	
	- 对指定哈希表中指定field值进行整数加法运算：hincrby key field int
		hincrby stu1001 age 5
	
	- 对指定哈希表中指定field值进行浮点数加法运算：hincrbyfloat key field float
		hset stu1001 score 80.5
		hincrbyfloat stu1001 score 5.5
	
	- 将一个field-vlaue对设置到哈希表中，当key-field已经存在时，则放弃设置；否则，设置file-value：hsetnx key field value
		hsetnx stu1001 age 30
	
- redis中有关zset类型数据的操作命令：有序集合
				                                           本质上是集合，所有元素不能重复；
	每一个元素都关联一个分数，redis会根据分数对元素进行自动排序；
	分数可以重复；
	既然有序集合中每一个元素都有顺序，那么也都有下标；
	有序集合中元素的排序规则又列表中元素的排序规则不一样。
	
	- 将一个或者多个member及其score值加入有序集合：zadd key score member [score member ....]
					                                           如果元素已经存在，则把分数覆盖
		zadd zset01 20 z1 30 z2 50 z3 40 z4
		zadd zset01 60 z2
		
	- 获取指定有序集合中指定下标区间的元素：zrange key startIndex endIndex [withscores]
	
	     zrange zset01 0 -1
	     zrange zset01 0 -1 withscores
	
	- 获取指定有序集合中指定分数区间(闭区间)的元素：zrangebyscore key min max [withscores]
					                                           zrangebyscore zset01 30 50 withscores
		
	- 删除指定有序集合中一个或者多个元素：zrem key member [member......]
					                                           zrem zset01 z3 z4
		
	- 获取指定有序集合中所有元素的个数：zcard key
					                                           zcard zset01
		
	- 获取指定有序集合中分数在指定区间内的元素的个数：zcount key min max
					                                           zcount zset01 20 50
		
	- 获取指定有序集合中指定元素的排名(排名从0开始)： zrank key member
					                                           zrank zset01 z4  =>2
		
	- 获取指定有序集合中指定元素的分数：zscore key member
					                                           zscore zset01 z4				
		
	- 获取指定有序集合中指定元素的排名(按照分数从大到小的排名):zrevrank key member
					                                           zrevrank zset01 z4  =>1
## redis的配置文件

- redis安装完成之后，在redis的根沐会提供一个配置文件(redis.conf)；redis服务可以参考配置文件中的参数进行运行；只有启动redis服务器指定使用的配置文件，参数才会生效；否则，redis会采用默认的参数运行。
- redis配置信息：
	port：配置redis服务运行的端口号；如果不配置port，则redis服务默认使用6379端口。
	bind: redis服务被客户端连接时，客户端所能使用的ip地址。
	 默认情况下，不配置bind，客户端连接redis服务时，通过服务器上任何一个ip都能连接到redis服务；一旦配置了bind，客户端就只能通过bind指定的ip地址连接redis服务。
	一般情况下，bind都是配置服务器上某一个真实ip。

- redis-cli ：默认连接127.0.0.1本机上的6379端口服务
	 redis-cli -h 127.0.0.1 -p 6379：同上
	 redis-cli -h 192.168.11.128 -p 6379：

- 强调：一旦redis服务配置了port和bind(如果port不是6379、bind也不是127.0.0.1)，客户端连接redis服务时，就要指定端口和ip：
	 redis-cli：默认连接127.0.0.1上的6379服务
	 redis-cli -h bind绑定的ip地址 -p port设置的端口：连接bind绑定的ip地址主机上的port设置的端口redis服务；
- 关闭redis服务时：redis-cli -h bind绑定的ip地址 -p port设置的端口 shutdown

- 在redis根目录下提供redis.conf配置文件；

	可以配置一些redis服务端运行时的一些参数；
	如果不使用配置文件，那么redis会按照默认的参数运行；
	如果使用配置文件，在启动redis服务时必须指定所使用的配置文件。 

- redis配置文件中关于网络的配置：
	port：指定redis服务所使用的端口，默认使用6379。
	bind: 配置客户端连接redis服务时，所能使用的ip地址，默认可以使用redis服务所在主机上任何一个ip都可以;一般情况下，都会配置一个ip，而且通常是一个真实IP

- 如果配置了port和bind，则客户端连接redis服务时，必须指定端口和ip：
	 redis-cli -h 192.168.11.128 -p 6380
	redis-cli -h 192.168.11.128 -p 6380 shutdown
	tcp-keepalive:连接保活策略。

- 常规配置：
	loglevel:配置日志级别,开发阶段配置debug,上线阶段配置notice或者warning.
	logfile：指定日志文件。redis在运行过程中，会输出一些日志信息；默认情况下，这些日志信息会输出到控制台；我们可以使用logfile配置日志文件，使redis把日志信息输出到指定文件中。
	databases：配置redis服务默认创建的数据库实例个数，默认值是16。

- 安全配置：
	requirepass：设置访问redis服务时所使用的密码；默认不使用。
	此参数必须在protected-mode=yes时才起作用。
	一旦设置了密码验证，客户端连接redis服务时，必须使用密码连接：redis-cli -h ip -p port -a pwd

## Redis的持久化

redis提供持久化策略，在适当的时机采用适当手段把内存中的数据持久化到磁盘中，每次redis服务启动时，都可以把磁盘上的数据再次加载内存中使用。

1. RDB策略：在指定时间间隔内，redis服务执行指定次数的写操作，会自动触发一次持久化操作。
	RDB策略是redis默认的持久化策略，redis服务开启时这种持久化策略就已经默认开启了。

	save  seconds  changes：配置持久化策略
	dbfilename：配置redis RDB持久化数据存储的文件
	dir:    配置redis RDB持久化文件所在目录

2. AOF策略：采用操作日志来记录进行每一次写操作，每次redis服务启动时，都会重新执行一遍操作日志中的指令。
	效率低下，redis默认不开启AOF功能

	appendonly:配置是否开启AOF策略
	appendfilename：配置操作日志文件

	小结：根据数据的特点决定开启哪种持久化策略；
	一般情况，开启RDB足够了。

## Redis的事务

事务：把一组数据库命令放在一起执行，保证操作原子性，要么同时成功，要么同时失败。

Redis的事务：允许把一组redis命令放在一起，把命令进行序列化，然后一起执行，保证部分原子性。

- multi：用来标记一个事务的开始。
	multi
	set k1 v1
	set k2 v2

- exec：用来执行事务队列中所有的命令。
	exec

- redis的事务只能保证部分原子性：

	- 如果一组命令中，有在压入事务队列过程中发生错误的命令，则本事务中所有的命令都不执行，能够保证事务的原子性。
		multi
		set k3 v3
		seta kk vv
		set k4 v4
		exec

	- 如果一组命令中，在压入队列过程中正常，但是在执行事务队列命令时发生了错误，则只会影响发生错误的命令，不会影响其它命令的执行，不能够保证事务的原子性。
		multi
		set k3 v3
		incr k1
		set k4 v4
		exec

	- discard：清除所有已经压入队列中的命令，并且结束整个事务。
		multi
		set k5 v5 
		set k6 v6
		discard

	- watch：监控某一个键，当事务在执行过程中，此键代码的值发生变化，则本事务放弃执行；否则，正常执行。

		id balance version

		update table set balance=balance-dept,version=version+1
		where id=xxxx and version=100

		set balance 100
		set balance2 1000
		set version 1

		watch version
		multi
		decrby balance 50
		incrby balance2 50
		exec

	- unwatch：放弃监控所有的键。
		   watch version
		unwach
		multi
		decrby balance 50
		
		incrby balance2 50
		exec

## Redis消息的发布与订阅（基本不会用）

redis客户端订阅频道，消息的发布者往频道上发布消息，所有订阅此频道的客户端都能够接受到消息。

- subscribe：订阅一个或者多个频道的消息。
	subscribe ch1 ch2 ch3     
	
- publish：将消息发布到指定频道
	publish ch1 hello    
	
- psubcribe：订阅一个或者多个频道的消息，频道名支持通配符。
	subscribe news.\*
## Redis的主从复制

主少从多、主写从读、读写分离、主写同步复制到从，搭建一主二从redis集群

- 搭建三台redis服务：使用一个redis模拟三台redis服务
	提供三份redis配置文件：redis6379.conf、redis6380.conf、redis6381.conf
	修改三份配置文件:以redis6379.conf为例

	```
	bind 127.0.0.1
	port 6379
	pidfile /var/run/redis_6379.pid
	logfile "6379.log"
	dbfilename dump6379.rdb
	```

	分别使用三个redis配置文件，启动三个redis服务：

	```
	redis-server redis6379.conf &
	redis-server redis6380.conf &
	redis-server redis6381.conf &
	```

- 通过redis客户端分别连接三台redis服务：
		     
	```
	   redis-cli -h 127.0.0.1 -p 6379
		redis-cli -h 127.0.0.1 -p 6380
		redis-cli -h 127.0.0.1 -p 6381 
	```
	
	查看三台redis服务在集群中的主从角色：
	`info replication`
	默认情况下，所有的redis服务都是主机，即都能写和读，但是都还没有从机。
	
- 先在6379进行写操作：
	    set k1 v1
	三台rdis服务互相独立，互不影响。
	
- 设置主从关系：设从不设主
	    在6380上执行：slaveof 127.0.0.1 6379
	在6381上执行：slaveof 127.0.0.1 6379
	
- 全量复制：一旦主从关系确定，会自动把主库上已有的数据同步复制到从库。 
	    在6380和6381上执行：keys *
	
- 增量复制：主库写数据会自动同步到从库。
	    在6379上执行：set k2 v2
	在6380和6381上执行：keys *
	
- 主写从读，读写分离： 
	    在6380和6381上执行：set k3 v3  ===>报错
	
- 主机宕机、从机原地待命:
	    关闭6379服务：redis-cli -h 127.0.0.1 -p 6379 shutdown
	
	查看6380和6381服务的主从角色：info replication
	
- 主机恢复、一切恢复正常：
	 重启6379服务：redis-server redis6379.conf &
	客户端连接6379：redis-cli -h 127.0.0.1 -p 6379
	
- 从机宕机、主机少一个从机、其它从机不变：
	 关闭6380服务： redis-cli -h 127.0.0.1 -p 6380 shutdown
	
	查看6379服务的主从角色：info replication
   
   查看6381服务的主从角色：info replication
   
- 从机恢复、需要重新设置主从关系：
   重启6380服务：redis-server redis6380.conf &
   客户端连接6380：redis-cli -h 127.0.0.1 -p 6380在6380上执行： slaveof 127.0.0.1 6379
   
- 从机上位：
  
   - 主机宕机、从机原地待命：
   	关闭6379服务：redis-cli -h 127.0.0.1 -p 6379 shutdown
   	查看6380和6381服务的主从角色：info replication
   
   - 从机断开原来主从关系：
   	在6380上执行：slaveof no one
   	查看6380服务的主从角色：info replication
   
   - 重新设置主从关系：
   	在6381上执行：slaveof 127.0.0.1 6380
   
   - 之前主机恢复、变成孤家寡人：
   	重启6379服务：redis-server redis6379.conf &
   	客户端连接6379：redis-cli -h 127.0.0.1 -p 6379
   
   - 天堂变地狱：
   	在6379上执行：slaveof 127.0.0.1 6381
   	在6381上执行：info replication   既是主机又是从机
   
   - 小结：一台主机配置多台从机，一台从机又可以配置多台从机，从而形成一个庞大的集群架构。
   	      减轻一台主机的压力，但是增加了服务间的延迟时间。

## Redis哨兵模式

主机宕机、从机上位的自动版。

- 搭建一主二从集群架构：(上一节)
- 提供哨兵配置文件：
	在redis安装目下创建配置文件：redis_sentinel.conf
	sentinel monitor dc-redis 127.0.0.1 6379 1
- 启动哨兵服务：
	redis-sentinel redis_sentinel.conf
- 主机宕机：
	关闭6379服务：redis-cli -h 127.0.0.1 -p 6379 shutdown
	哨兵程序自动选择从机上位。
- 之前主机恢复：自动从属于新的主机。
	重启6379服务：redis-server redis6379.conf &
	客户端连接6379：redis-cli -h 127.0.0.1 -p 6379

## java操作Redis数据库

jedis是redis官方提供的操作redis数据的技术。

把所有的redis指令都定义成java工具类的方法，方法名和redis的指令名完全一样；
开发通过程序访问redis，只需要使用工具类及其方法即可。

在java程序中访问redis：

- 创建maven版的java工程

- 添加jedis依赖

	```xml
	      <dependency>
	        <groupId>redis.clients</groupId>
	        <artifactId>jedis</artifactId>
	        <version>3.1.0</version>
	    </dependency>
	```

- 创建Jedis连接
	 
- 关闭linux的防火墙

