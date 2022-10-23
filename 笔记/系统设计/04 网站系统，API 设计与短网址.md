# 为什么了解网站系统如此重要？

- System Design 几乎都是 Backend Design
- Backend Design 几乎都是 Web Backend Design
- 传统做软件开发的，很少会去面系统设计，大多都是设计模式，面向对象开发和设计，编程基础知识
- 现在大公司都发展起了自己的 Web 服务，而且很多软件的服务，也需要后端人员维护

# 当你访问 www.google.com 的时候发生了什么

- 面试真题

- 你在浏览器输入 www.google.com
- 你首先访问的是离你最近的 DNS 服务器  
	- Domain Name Service  
	- DNS 服务器记录了 www.google.com 这个域名的 IP 地址是什么
- 你的浏览器然后向该 IP 发送 http/https 请求
	- 每台服务器/计算机联网都需要一个 IP 地址
	- 通过 IP 地址就能找到该 服务器/计算机
- 服务器(Web Server)收到请求，将请求递交给正在 80 端口监听的HTTP Server
- 比较常用的 HTTP Server 有 Apache, Unicorn, Gunicorn, Uwsgi
- HTTP Server 将请求转发给 Web Application  
	- 最火的三大Web Application Framework
	- Django, Ruby on Rails, NodeJS
	- Python 新宠:Flask
- Web Application 处理请求  
	- 根据当前路径 “/”找到对应的逻辑处理模块  
	- 根据用户请求参数(GET+POST)决定如何获取/存放数据
	- 从数据存储服务(数据库或者文件系统)中读取数据  
	- 组织数据成一张 html 网页作为返回结果
- 浏览器得到结果，展示给用户

# 网站系统的基本概念

- DNS  
- HTTP  
- Domain  
- IP Address  
- URL  
- Web Server (硬件)  
- HTTP Server (软件)  
- Web Application (软件)

# 简单的网站系统架构原理图

![](image/Pasted%20image%2020221009123818.png)

# 复杂的网站系统架构原理图

![](image/Pasted%20image%2020221009123848.png)

# API Design

- 常见的一类系统设计知识点的考察

## 什么是 API

- API = Application Programming Interface

- 样例 1  
	- 你实现了一个叫做 Utility 的 class，然后这个 class 提供一个 sortIntegers 的 method，可以对参数中的整数数组进行排序。这就是一个 API
- 样例 2
	- 你访问了 https://www.awebsite.com/api/users/ 获得了所有的用户的信息。这就是一个 Web API
- 通常来说，只要是你提供了一些方法，函数，功能给别人用，别人通过直接的函数调用或者 http 等方式进行调用，得到了返回结果，这就是 API

## 下面哪种 API 的设计更合理

- 目标
	- 获得当前登陆用户在 LintCode 上某个题上的所有提交记录
- 提示
	- 完整的API地址应该为 https://www.lintcode.com/api/... 
	- 以下简写为 /api/...

1. /api/users/<current_user_id>/submissions/?problem_id=1000
2. /api/users/me/submissions/?problem_id=1000  
3. /api/submissions/?problem_id=1000&user_id=<current_user_id>
4. /api/submissions/?problem_id=1000 
	- 后台用当前用户去筛选（通过Session） 
5. /api/problems/1000/submissions/ # 后台用当前用户去筛选
	- 后台用当前用户去筛选（通过Session）

- 仔细思考一下，里面真正正确的只有第 4 个选项
- 凡是里面带了 user_id 的都不对，这样的话，这些东西都是能篡改的，那我岂不是能把我的 user_id 一改，去访问别人的信息，这不就是信息泄漏，所以排除选项 1 和 3
- 为什么选项 2 和 5 为什么不对，你看它们的一级目录，不觉得有些混淆吗？我到底是在 user 里面查，还是 problems 里面查，这不就是语义模糊了

## Rest API

- 你要获取的数据是什么，路径的主目录就是什么 
- 要获取 problem 就是 /api/problems/
- 要获取 submission 就是 /api/submissions/

### RESTful API

- REST = Representational State Transfer 
- 满足 REST 协议的架构和设计，叫做 RESTful  
- RESTful API 的通俗定义
	- 每个 URL 代表某种类型的一个或者多个数据
	- 如 /api/problems/ 表示得到所有 problems 的数据
	- 如 /api/problems/1/ 表示得到 problem_id=1 的这个 problem 的数据
- 使用 HTTP 的四个动作(POST，DELETE，GET，PUT)来代表对数据的增删查改
- 所有的筛选条件，创建参数，都放到 HTTP 的参数里

### 练习 1 增删查改某个用户的信息

#### 正确的设计

- POST /api/accounts/
- DELETE /api/accounts/1/
- GET /api/accounts/1/
- PUT /api/accounts/1/

#### 错误的设计

- /api/accounts/create/
- /api/accounts/1/delete/
- /api/accounts/1/show/ 
- /api/accounts/1/update/

### 练习 2 创建转账记录

#### 正确的设计

- POST /api/transaction/?from=1&to=2&money=500

#### 错误的设计

- POST /api/accounts/1/transfer/500/to/2/

## 面试真题 Design News Feed API

- 与 Design News Feed System 的区别是不需要管后台数据如何存储和获取，只需要进行和前端交互的接口设计

### 考点

- 什么是 API，设计获取 News Feeds List 的 Web API 请求格式 
-   设计 API 返回的内容格式
-   设计翻页 Pagination
-   设计 Mentions 的数据格式

### 面试官提问 1 设计 News Feed List 的 Web API 请求格式

- GET https://www.facebook-or-twitter.com/api/newsfeed/ 
- or  
- GET https://api.facebook-or-twitter.com/newsfeed/

- Read request 用 GET
- 要获取的 Resource 是什么，一级目录就是什么

### 面试官提问 2 设计API 的返回格式

- 返回 Structured Data 还是 HTML?
	- Structured Data 比如 JSON 或者 XML

#### JSON vs XML

- 目前主流的基于 HTTP 协议的数据格式
- 一般都会选择用 JSON 
- XML 目前主要用于在 Android 的代码中记录一些格式化的数据

### 面试官提问 3 如何设计翻页 Pagination

- 下面哪种请求是正确的
	- 请求1 /api/newsfeed/?page=1 
	- 请求2 /api/newsfeed/?max_id=xxx

#### 翻页 Pagination

- 传统翻页方法 ?page=1
- 优点 可以直接跳转到第 x 页
- 缺点 如果有新数据被插入时，翻到下一页可能会看到上一页的内容 
- 适用于用户希望查阅很久以前的内容的使用场景  
- NewsFeed 是否适用
	- 不适用，你也不想你在逛着朋友圈，或者看说说的时候翻页看到了你刚刚看到的东西，这样的用户体验并不好
	- 适合于那种刷题网站，或有数据变动不算大的网站，不容易给用户造成困扰

![](image/Pasted%20image%2020221009134334.png)

- News Feed 一般不会采用页码进行翻页
- 而是采用无限翻页 Endless Pagination
- API 设计  /api/newsfeed/?max_id=1000
	- 没有 max_id 表示第一页 
	- 有 max_id 找到所有 id <= max_id 的最顶上的一页的数据(假设倒序)

#### 面试官提问 3.1 如何判定有没有下一页?

- 当 response 里什么数据都没有时表示没有下一页
- 这种方法有什么问题？
	- 答案就是多请求一次，其实也无伤大雅，但是也有解决方法
- 解决方法
	- 每次多取一个数据，如果取到，把这个数据作为 next_max_id 返回给前端

```
PAGE_SIZE = 20  
从 request 中获取 max_id
if 没有 max_id
	获得最新的 PAGE_SIZE + 1 条数据
else
	获得 id <=max_id 的最新的 PAGE_SIZE + 1 条数据 

如果获取到的数据为 21 条，将第21条的 id 赋值给 next_max_id
否则 next_max_id = null

返回数据:
{  
	'next_max_id': next_max_id,  
	'items': [...最多 PAGE_SIZE 条数据]
}
```

#### 面试官提问 3.2 如何获得更新内容

- GET `/api/newsfeed/?min_id=<id>`
- 找到所有 id > 目前客户端里最新的一条帖子的 id 的所有帖子

### 面试官提问4:设计 Mentions 的数据格式

- 当 News Feed 的文本内容里有 Mentions 的时候，即提到了某个人
- 该如何在文本内容中体现并让前端可以显示成一个带 link 的样式

#### 方法 1 在文本中直接返回 html 格式的链接

```html
Hello world, this is the first post from  
<a href=”/users/someone/”>@someone</a>
please follow me!
```

##### 缺点

1. 需要预防 javascript injection attack
	举例:人人网曾经遭受过一次 javascript injection attack，看了某个帖子之后，自动就分享出去了
2. API 无法被 Mobile 端共享
	Mobile 显示链接并不是用 `<a>`
3. URL 可能会改动
	如果将链接内容作为 post 的一部分存入数据库中，以后如果链接发生了变化，如从 `/users/<id>/` 改成 了 `/users/<username>/` 
	那么旧的链接无法被马上弃用(因为已经存在数据库里了，改起来太费劲，需要遍历所有的数据)
	从而导致有安全隐患设计的 URL `/users/<id>/` 无法被弃用。

#### 推荐方法 自定义链接结构

- 如 `<user username=“someone”>Hello World</user>`
- 让 Web 和 Mobile 分别对该格式进行解析 解析成各自平台认识的格式
- 还有一些好处就是对于之后发生了API变动或者是数据格式变化，我们也可以在代码层面来修改
- 比如以前的使用 `<user id=“someone_id”>Hello World</user>`，之后的使用 `<user username=“someone”>Hello World</user>` 我们也能够在代码层面完成解析，不用变动太多
- 要是连标签都改了，代码层面都能解决

# 设计短网址系统

- 设计短网址系统 Design Tiny URL
- https://bitly.com/ 
- https://goo.gl/

## 回顾系统设计的常见误区

- 流量一定巨大无比
- 那必须是要用NoSQL了
- 那必须是分布式系统了
- 某同学
	- 先来个Load Balancer
	- 后面一堆Web Server
	- 然后 memcached
	- 最底层NoSQL，搞定!

## 系统设计问题的基本步骤

- 4S分析法

1. 提问
	- 分析功能、需求、QPS、存储容量 - Scenario
2. 画图
	- 根据分析结果设计“可行解” - Service+Storage
3. 进化
	- 研究可能遇到的问题，优化系统 - Scale

## Scenario 场景分析

### 我要设计啥

- 根据 Long URL 生成一个 Short URL
	- http://www.jiuzhang.com => http://bit.ly/1UIoQB6

![](image/Pasted%20image%2020221009144459.png)

- 根据 Short URL 还原 Long URL，并跳转
	- http://bit.ly/1UIoQB6 => http://www.jiuzhang.com

![](image/Pasted%20image%2020221009144547.png)

### 两个需要和面试官确认的问题

- Long Url 和 Short Url 之间必须是一一对应的关系么?
	- 比如有的网址会被频繁分享，每次生成 Short Url 这样会导致空间被浪费，虽然少了一些逻辑判断但是浪费了空间，这也是在面试中要问清楚的点，不同的要求设计会不一样的？
- Short Url 长时间没人用需要释放么? 
	- 有的人认为，这个是用后就丢的东西，只是便于分享，但有的人认为，这个要一直保留，因为这个对自己很重要
- **不同的要求设计出来的系统完全不一样 !**

### QPS + Storage

1. 询问面试官微博日活跃用户
	- 约100M
2. 推算产生一条Tiny URL的QPS
	- 假设每个用户平均每天发 0.1 条带 URL 的微博 
	- Average Write QPS = 100M * 0.1 / 86400 ~ 100 
	- Peak Write QPS = 100 * 2 = 200
3. 推算点击一条Tiny URL的QPS
	- 假设每个用户平均点1个Tiny URL（我们在本站浏览都是内部链接，这个是不算Tiny URL）
	- Average Read QPS = 100M * 1 / 86400 ~ 1k 
	- Peak Read QPS = 2k
4. 推算每天产生的新的 URL 所占存储
	-   100M * 0.1 ~ 10M 条
	-   每一条 URL 长度平均 100 算，一共1G
	-   1T 的硬盘可以用 3 年
5. 得出结论
	- 这是一个读多写少的系统，然后每天的峰值写才 200 QPS，每天的读峰值 2000 QPS
	- 这不就是一台优化过的单机数据库加上缓存就能做到的事情
	- 一台机器就能解决的事情，要是像有的人一上来就是各种高大上，你觉得有必要吗？
	- 这都是资源和钱，不要把问题想的太复杂，从最简单的开始，慢慢迭代优化！

## Service 服务

- 该系统比较简单只有一个 Service
- URL Service

### 逻辑块聚类与接口设计

- TinyUrl只有一个UrlService  
	- 本身就是一个小Application
	- 无需关心其他的
- 函数设计  
	- UrlService.encode(long_url)
	- UrlService.decode(short_url)
- 访问端口设计
	- GET /<short_url>  
		- return a Http redirect response
	- POST /data/shorten/
		- Data = {url: http://xxxx }
		- Return short url

![](image/Pasted%20image%2020221009175305.png)

![](image/Pasted%20image%2020221009175311.png)

![](image/Pasted%20image%2020221009175317.png)

## Storage 数据存取

- 数据如何存储与访问
	- 第一步：Select 选存储结构
	- 第二步：Schema 细化数据表
- 这个是系统设计中最重要的一个部分，可能有的面试官也不在乎你的前两个分析的好不好，可能直接告诉你答案了，他就只关心你数据怎么存怎么取，能不能说清楚，因为这个是衡量你是不是一个合格的工程师中最重要的一个步骤，看的出你作为工程师实际的经验，所以这一步很重要

### SQL or NoSQL

#### 到底怎么选

- 是否需要支持 Transaction? - 不需要
	- NoSQL + 1
	- NoSQL不支持Transaction
- 是否需要丰富的 SQL Query? - 不需要。NoSQL + 1
	- NoSQL 的SQL Query不是太丰富
	- 也有一些 NoSQL 的数据库提供简单的SQL Query支持
- 是否想偷懒? - Tiny URL 需要写的代码并不复杂。NoSQL + 1
	- 大多数 Web Framework 与 SQL 数据库兼容得很好
	- 用 SQL 比用 NoSQL 少写很多代码
- 对QPS的要求有多高? - 经计算，2k QPS并不高，而且2k读可以用Cache，写很少。SQL +1
	- NoSQL 的性能更高
- 对Scalability的要求有多高? - 存储和QPS要求都不高，单机都可以搞定。SQL+1
	- SQL 需要码农自己写代码来 Scale
		- 还记得Db那节课中怎么做Sharding，Replica
	- NoSQL 这些都帮你做了
- 是否需要Sequential ID? - 取决于你用什么算法
	- SQL 为你提供了 auto-increment 的 Sequential ID  
	- 也就是1,2,3,4,5 ...  
	- NoSQL的ID并不是 Sequential 的
- 所以Tiny URL用什么比较合适
	- 看你的实现

### 如何将 Long Url 转换为一个 6位的 Short Url

#### 使用哈希函数 Hash Function(不可行)

- 比如取 Long Url 的 MD5 的最后 6 位  
	- 只是打个比方，这个方法肯定是有问题的啦
- 优点：快  
- 缺点：难以设计一个没有冲突的哈希算法

#### 随机生成ShortURL + 数据库去重

- 随机一个 6 位的 ShortURL，如果没有被用过，就绑定到该 LongURL
- 伪代码如下

![](image/Pasted%20image%2020221010110325.png)

- 优点：实现简单
- 缺点：生成短网址的速度随着短网址越来越多变得越来越慢，其实也能解决，就是通过增加网址的长度来解决

- 这个场景经常使用于使用人数不太多，需要短期时间验证身份的场景
	- 就像，网上订酒店、机票
	- 这个一个简单有效的方法，但是随着生成的数量的增加，性能会下降

#### 进制转换 Base62

- 大部分的网友都是给你的这个方法，虽然给出了答案，但是你还是要学会比较和分析，第二种方法和第三种方法之间的优劣，答案永远不是唯一的，只是在各个不同条件下的权衡，你去网上搜，只有这个答案，而不自己去思考，这个是不对的，这只是其中一个实现方法而已
- 新浪微博就是这么实现的

- Base62
	- 将 6 位的short url看做一个62进制数(0-9, a-z, A-Z)  
	- 每个 short url 对应到一个整数  
	- 该整数对应数据库表的 Primary Key - Sequential ID
- 6 位可以表示的不同 URL 有多少?
	- 5 位 = $62 ^ 5$ = 0.9B = 9 亿
	- 6 位 = $62 ^ 6$ = 57 B = 570 亿
	- 7 位 = $62 ^ 7$ = 3.5 T = 35000 亿 
- 优点：效率高 
- 缺点：依赖于全局的自增ID，多台机器就遇到问题了。

![](image/Pasted%20image%2020221010161515.png)

### 随机生成 vs 进制转换

- 幸福二选一

#### 基于随机生成的方法

- 需要根据 Long 查询 Short，也需要根据 Short 查询 Long。
- 如果选择用 SQL 型数据库，表结构如下

| shortKey | longUrl |
| :----:   | :----: |
| a0B4Lb   | http://www.jiuzhang.com/ |
| Df523P   | http://www.lintcode.com/ |
| dao80F   | http://www.google.com/   |
| QFD8oqb  | http://www.facebook.com/ |

- 并且需要对 shortKey 和 longURL 分别建索引(index)
	- 什么是索引? http://t.cn/R6xgLd8
	- 索引的原理? http://t.cn/R6xg4aj

- 也可以选用 NoSQL 数据库，但是需要建立两张表(大多数 NoSQL 不支持多重索引 Multi-index)
- 以 Cassandra 为例子 
	- 第一张表
		- 根据 Long 查询 Short
		- `row_key=longURL, column_key=ShortURL, value=null or timestamp`
	- 第二张表
		- 根据 Short 查询 Long  
		- `row_key=shortURL, column_key=LongURL, value=null or timestamp`

##### 基于随机生成方法的 Work Solution

![](image/Pasted%20image%2020221010164752.png)

#### 基于进制转换的方法

- 因为需要用到自增ID(Sequential ID)，因此只能选择使用 SQL 型数据库。
- 表单结构如下
	- shortURL 可以不存储在表单里，因为可以根据 id 来进行换算

| id | longUrl (index=true) |
| :----:   | :----: |
| 1 | http://www.jiuzhang.com/ |
| 2 | http://www.lintcode.com/ |
| 3 | http://www.google.com/   |
| 4 | http://www.facebook.com/ |

##### 基于进制转换方法的Work Solution

![](image/Pasted%20image%2020221010165033.png)

## Scale 进化

- Tiny URL 有什么可以优化的地方?

### Interviewer: How to reduce response time

- 如何提高响应速度？
- 如何提高响应速度?
- 说说看有哪些地方可以加速

#### 利用缓存提速(Cache Aside)

- 利用缓存提速(Cache Aside)
- 缓存里需要存两类数据
	- long to short(生成新 short url 时需要)
	- short to long(查询 short url 时需要)

![](image/Pasted%20image%2020221010165602.png)

#### 利用地理位置信息提速

- 优化服务器访问速度  
	- 不同的地区，使用不同的 Web 服务器  
	- 通过DNS解析不同地区的用户到不同的服务器
- 优化数据访问速度  
	- 使用Centralized MySQL+Distributed Memcached  
	- 一个MySQL配多个Memcached，Memcached跨地区分布
	- 但是要注意，这种架构只适用于访问数据库次数不多，请求不大的情况下，如果频繁的请求，数据库还是要部署在本地

![](image/Pasted%20image%2020221010165731.png)

#### Tiny URL 里程碑

- 场景分析：要做什么功能  
- 需求分析：QPS和Storage  
- 应用服务：UrlService  
- 数据分析：选SQL还是NoSQL  
- 数据分析：细化数据库表  
- 得到一个Work Solution  
- 提高Web服务器与数据服务器之间的访问效率：利用缓存提高读请求的效率  
- 提高用户与服务器之间的访问效率：解决了中国用户访问美国服务器慢的问题


### Interviewer: How to scale

- 假如我们一开始估算错了，一台MySQL搞不定了

#### 什么时候需要多台数据库服务器

- Cache 资源不够  
- 写操作越来越多  
- 越来越多的请求无法通过 Cache 满足

#### 增加多台数据库服务器可以优化什么

- 解决“存不下”的问题 - Storage的角度
- 解决“忙不过”的问题 —— QPS的角度
- Tiny URL 主要是什么问题
	- 忙不过来

#### Vertical Sharding

- 将多张数据表分别分配给多台机器
- Tiny URL 并不适用，只有两个 column 无法再拆分

#### Horizontal Sharding

- 如果用 ID / ShortUrl 做Sharding Key
	- 做 long to short 查询的时候，只能广播给 N 台数据库查询
	- 为什么会需要查 long to short?创建的时候避免重复创建
	- **如果不需要避免重复创建，则这样可行** 
- 如果用 Long Url 做Sharding Key  
	- 做 short to long 查询的时候，只能广播给 N 台数据库查询

#### 选 Sharding Key

- 如果一个 Long 可以对应多个 Short:  
    - 使用 Cache 缓存所有的 Long to Short 
    -  在为一个 Long Url 创建 Short Url 的时候，如果 cache miss 则去直接创建新的 short url 即可  
- 如果一个 Long 只能对应一个 Short
	- 如果使用随机生成 Short Url 的算法
		- 两张表单，一张存储 Long to Short，一张存储 Short to Long
		- 每个映射关系存两份，则可以同时支持 long to short 和 short to long 的查询
	- 如果使用 base62 的进制转换法
		- 这里有一个很严重的问题是，多台机器之间如何维护一个全局自增的 ID?
		- 一般关系型数据库只支持在一台机器上实现这台机器上全局自增的 ID

#### 全局自增ID

- 如何获得在N台服务器中全局共享的一个自增ID是一个难点
- 一种解决办法是，专门用一台数据库来做自增ID服务  
	- 该数据库不存储真实数据，也不负责其他查询  
	- 为了避免单点失效(Single Point Failure) 可能需要多台数据库
- 另外一种解决办法是用 Zookeeper  
	- 但是使用全局自增ID的方法并不是解决 Tiny URL 的最佳方法
	- 有兴趣的同学可以阅读一下拓展资料:http://bit.ly/1RCyPsy

#### 基于 base62 的方法下的 Sharding key 策略

- 使用 **Hash(long_url) % 62** 作为 Sharding key  
- 并将 Hash(long_url) % 62 直接放到 short url 里  
- 如果原来的 short key 是 AB1234 的话，现在的 short key 是
	- hash(long_url) % 62 + AB1234  
	- 如果 hash(long_url) % 62 = 0 那就是 **0**AB1234
	- 这就是对应 0 号数据库
	- 再使用一致性哈希算法，这样就能保证，加机器还是减机器，都能保证数据不丢失
- 这样我们就可以同时通过 short_url 和 long_url 得到 Sharding Key
- 缺点：数据库的机器数目不能超过 62
- 真的要加这么多机器，还不如把网址加长一点，更快

#### 目前的架构

![](image/Pasted%20image%2020221011082324.png)

### Interviewer: 还有可以优化的么

#### Multi Region 的进一步优化

- 上图的架构中，还存在优化空间的地方是
	- 网站服务器 (Web Server) 与 数据库服务器 (Database) 之间的通信  
	- 中心化的服务器集群(Centralized DB set)与 跨地域的 Web Server 之间通信较慢
		- 比如中国的服务器需要访问美国的数据库  
- 那么何不让中国的服务器访问中国的数据库?
	- 如果数据是重复写到中国的数据库，那么如何解决一致性问题? 
		- 很难解决
- 想一想用户习惯  
	- 中国的用户访问时，会被DNS分配中国的服务器
	- 中国的用户访问的网站一般都是中国的网站  
	- 所以我们可以按照网站的**地域信息**进行 Sharding
		- 如何获得网站的地域信息?
		- 只需要将用户比较常访问的网站弄一张表就好了
		- 用户经常访问的都是一些大网站，这就能确定地域信息了
	- 中国的用户访问美国的网站怎么办?
		- 那就让中国的服务器访问美国的数据好了，反正也不会慢多少
		- 中国访问中国是主流需求，优化系统就是要优化主要的需求
		- 有时候特殊的需求，满足会花费大量的时间和金钱，这也是需要权衡的，这部分客户值得花这些吗

#### 最终的架构

![](image/Pasted%20image%2020221011082911.png)

## 重要的事情说N遍

- 系统设计没有标准答案，言之有理即可
- 设计一个可行解比抛出Fancy的概念更有用

## 扩展阅读

- Tiny URL 相关 (只作为参考，有一些答案并不完全正确，以课堂讲述内容为准) 
	- 知乎 http://bit.ly/22FHP5o  
	- The System Design Process http://bit.ly/1B6HOEc

## 拓展练习：实现 Custom URL
- `http://tiny.url/google/=> http://www.google.com`
- `http:ltiny.ur/systemdesianl => http://ww.iuzhang.com/course/2/

### 基于Base62

- 在 URLTable 里直接新增一项 custom url 记录对应的 customurl 是否可行

- URL Table 增加一个 Column 不可行
	- 因为大部分数据这一项都是空的
	- 会浪费存储空间(即使是空也会有空间耗费）
- 新建一张表存储自定义URL
	- CustomURLTable
- 创新自定义短链接
	- 在CustomURLTable中查询和插入
- 根据长链接创建普通短链接
	- 先查询CustomURL Table是否存在
	- 再在URLTable中查询和插入

| custom_url | long_url |
| :----:   | :----: |
| lc  | http://www.lintcode.com/ |
| gg  | http://www.google.com/   |
| fb  | http://www.facebook.com/ |

### 基于随机生成

- 无需任何改动，直接把 custom url 当 short url 创建就可以了
- 完全兼容

