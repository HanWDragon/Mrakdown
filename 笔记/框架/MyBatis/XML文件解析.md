

# XML文件解析

- MyBatis-Config.xml

	```xml
	<?xml version="1.0" encoding="UTF-8" ?>
	<!DOCTYPE configuration
	        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
	        "http://mybatis.org/dtd/mybatis-3-config.dtd">
	<configuration>
	
	    <!--settings：控制mybatis全局行为-->
	    <settings>
	        <!--设置mybatis输出日志-->
	        <setting name="logImpl" value="STDOUT_LOGGING" />
	    </settings>
	
	    <!--环境配置： 数据库的连接信息
	        default:必须和某个environment的id值一样。
	        告诉mybatis使用哪个数据库的连接信息。也就是访问哪个数据库
	    -->
	    <environments default="mydev">
	        <!-- environment : 一个数据库信息的配置， 环境
	             id:一个唯一值，自定义，表示环境的名称。
	        -->
	        <environment id="mydev">
	            <!--
	               transactionManager ：mybatis的事务类型
	                   type: JDBC(表示使用jdbc中的Connection对象的commit，rollback做事务处理)
	            -->
	            <transactionManager type="JDBC"/>
	            <!--
	               dataSource:表示数据源，连接数据库的
	                  type：表示数据源的类型， POOLED表示使用连接池
	            -->
	            <dataSource type="POOLED">
	                <!--
	                   driver, user, username, password 是固定的，不能自定义。
	                -->
	                <!--数据库的驱动类名-->
	                <property name="driver" value="com.mysql.jdbc.Driver"/>
	                <!--连接数据库的url字符串-->
	                <property name="url" value="jdbc:mysql://localhost:3306/springdb"/>
	                <!--访问数据库的用户名-->
	                <property name="username" value="root"/>
	                <!--密码-->
	                <property name="password" value="123456"/>
	            </dataSource>
	        </environment>
	
	
	        <!--表示线上的数据库，是项目真实使用的库-->
	        <environment id="online">
	            <transactionManager type="JDBC"/>
	            <dataSource type="POOLED">
	                <property name="driver" value="com.mysql.jdbc.Driver"/>
	                <property name="url" value="jdbc:mysql://localhost:3306/onlinedb"/>
	                <property name="username" value="root"/>
	                <property name="password" value="fhwertwr"/>
	            </dataSource>
	        </environment>
	    </environments>
	
	    <!-- sql mapper(sql映射文件)的位置-->
	    <mappers>
	        <!--一个mapper标签指定一个文件的位置。
	           从类路径开始的路径信息。  target/clasess(类路径)
	        -->
	        <mapper resource="com/bjpowernode/dao/StudentDao.xml"/>
	        <!--<mapper resource="com/bjpowernode/dao/SchoolDao.xml" />-->
	    </mappers>
	</configuration>
	<!--
	   mybatis的主配置文件： 主要定义了数据库的配置信息， sql映射文件的位置
	
	   1. 约束文件
	   <!DOCTYPE configuration
	        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
	        "http://mybatis.org/dtd/mybatis-3-config.dtd">
	
	    mybatis-3-config.dtd：约束文件的名称
	
	  2. configuration 根标签。
	-->
	```

- Mapper.xml

	```xml
	<?xml version="1.0" encoding="UTF-8" ?>
	<!DOCTYPE mapper
	        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
	        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
	<mapper namespace="com.Han.dao.StudentDao">
	    <!--
	       select:表示查询操作。
	       id: 你要执行的sql语法的唯一标识， mybatis会使用这个id的值来找到要执行的sql语句
	           可以自定义，但是要求你使用接口中的方法名称。
	
	       resultType:表示结果类型的， 是sql语句执行后得到ResultSet,遍历这个ResultSet得到java对象的类型。
	          值写的类型的全限定名称
	    -->
	    <select id="selectStudents" resultType="com.bjpowernode.domain.Student" >
	        select id,name,email,age from student order by id
	    </select>
	
	    <!--插入操作-->
	    <insert id="insertStudent">
	        insert into student values(#{id},#{name},#{email},#{age})
	    </insert>
	</mapper>
	<!--
	  sql映射文件（sql mapper）： 写sql语句的， mybatis会执行这些sql
	  1.指定约束文件
	     <!DOCTYPE mapper
	        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
	        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
	
	    mybatis-3-mapper.dtd是约束文件的名称， 扩展名是dtd的。
	
	  2.约束文件作用：  限制，检查在当前文件中出现的标签，属性必须符合mybatis的要求。
	
	  3.mapper 是当前文件的根标签，必须的。
	    namespace：叫做命名空间，唯一值的， 可以是自定义的字符串。
	               要求你使用dao接口的全限定名称。
	
	  4.在当前文件中，可以使用特定的标签，表示数据库的特定操作。
	   <select>:表示执行查询，select语句
	   <update>:表示更新数据库的操作， 就是在<update>标签中 写的是update sql语句
	   <insert>:表示插入， 放的是insert语句
	   <delete>:表示删除， 执行的delete语句
	-->
	```

	

