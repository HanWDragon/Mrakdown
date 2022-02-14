mysql day03���ñʼ�

1����ѯÿһ��Ա�������ڲ������ƣ�Ҫ����ʾԱ�����Ͳ�������

mysql> select * from emp;
+-------+--------+-----------+------+------------+---------+---------+--------+
| EMPNO | ENAME  | JOB       | MGR  | HIREDATE   | SAL     | COMM    | DEPTNO |
+-------+--------+-----------+------+------------+---------+---------+--------+
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |
|  7499 | ALLEN  | SALESMAN  | 7698 | 1981-02-20 | 1600.00 |  300.00 |     30 |
|  7521 | WARD   | SALESMAN  | 7698 | 1981-02-22 | 1250.00 |  500.00 |     30 |
|  7566 | JONES  | MANAGER   | 7839 | 1981-04-02 | 2975.00 |    NULL |     20 |
|  7654 | MARTIN | SALESMAN  | 7698 | 1981-09-28 | 1250.00 | 1400.00 |     30 |
|  7698 | BLAKE  | MANAGER   | 7839 | 1981-05-01 | 2850.00 |    NULL |     30 |
|  7782 | CLARK  | MANAGER   | 7839 | 1981-06-09 | 2450.00 |    NULL |     10 |
|  7788 | SCOTT  | ANALYST   | 7566 | 1987-04-19 | 3000.00 |    NULL |     20 |
|  7839 | KING   | PRESIDENT | NULL | 1981-11-17 | 5000.00 |    NULL |     10 |
|  7844 | TURNER | SALESMAN  | 7698 | 1981-09-08 | 1500.00 |    0.00 |     30 |
|  7876 | ADAMS  | CLERK     | 7788 | 1987-05-23 | 1100.00 |    NULL |     20 |
|  7900 | JAMES  | CLERK     | 7698 | 1981-12-03 |  950.00 |    NULL |     30 |
|  7902 | FORD   | ANALYST   | 7566 | 1981-12-03 | 3000.00 |    NULL |     20 |
|  7934 | MILLER | CLERK     | 7782 | 1982-01-23 | 1300.00 |    NULL |     10 |
+-------+--------+-----------+------+------------+---------+---------+--------+

mysql> select * from dept;
+--------+------------+----------+
| DEPTNO | DNAME      | LOC      |
+--------+------------+----------+
|     10 | ACCOUNTING | NEW YORK |
|     20 | RESEARCH   | DALLAS   |
|     30 | SALES      | CHICAGO  |
|     40 | OPERATIONS | BOSTON   |
+--------+------------+----------+

��emp����ȡename����dept����ȡdname��û�������������ղ�ѯ����ǣ�

ENAME				DNAME
-------------------------------------------
SMITH				ACCOUNTING	��Ч��¼
SMITH				RESEARCH		��Ч��¼
SMITH				SALES			��Ч��¼
SMITH				OPERATIONS	��Ч��¼

ALLEN				ACCOUNTING
ALLEN				RESEARCH
ALLEN				SALES
ALLEN				OPERATIONS

.....
56����¼��

�Ӹ�������Ϊ�˴ﵽ4ѡ1��Ҳ��Ϊ�����ݵ���Ч�ԡ�

	select 
		e.ename,d.dname
	from
		emp e
	join
		dept d
	on
		e.deptno = d.deptno;
	
	������ֻ��Ϊ�˱���ѿ���������ֻ��Ϊ�˲�ѯ����Ч����ϼ�¼��
	ƥ��Ĵ���һ�ζ�û���٣�����56�Ρ�

2��insert������һ�β��������¼�𣿡����ա�
	���Եģ�
	mysql> desc t_user;
	+-------------+-------------+------+-----+---------+-------+
	| Field       | Type        | Null | Key | Default | Extra |
	+-------------+-------------+------+-----+---------+-------+
	| id          | int(11)     | YES  |     | NULL    |       |
	| name        | varchar(32) | YES  |     | NULL    |       |
	| birth       | date        | YES  |     | NULL    |       |
	| create_time | datetime    | YES  |     | NULL    |       |
	+-------------+-------------+------+-----+---------+-------+

	һ�ο��Բ��������¼��
		insert into t_user(id,name,birth,create_time) values
		(1,'zs','1980-10-11',now()), 
		(2,'lisi','1981-10-11',now()),
		(3,'wangwu','1982-10-11',now());

		�﷨��insert into t_user(�ֶ���1,�ֶ���2) values(),(),(),();

	mysql> select * from t_user;
	+------+--------+------------+---------------------+
	| id   | name   | birth      | create_time         |
	+------+--------+------------+---------------------+
	|    1 | zs     | 1980-10-11 | 2020-03-19 09:37:01 |
	|    2 | lisi   | 1981-10-11 | 2020-03-19 09:37:01 |
	|    3 | wangwu | 1982-10-11 | 2020-03-19 09:37:01 |
	+------+--------+------------+---------------------+

3�����ٴ����������˽����ݡ�

	mysql> create table emp2 as select * from emp;

	ԭ����
		��һ����ѯ�������һ�ű��½�����������
		���������ɱ��Ŀ��ٸ��ƣ�������
		������������ͬʱ���е�����Ҳ�����ˣ�����
	
	create table mytable as select empno,ename from emp where job = 'MANAGER';

4������ѯ������뵽һ�ű����У�insert��صģ��������˽����ݡ�
	create table dept_bak as select * from dept;
	mysql> select * from dept_bak;
	+--------+------------+----------+
	| DEPTNO | DNAME      | LOC      |
	+--------+------------+----------+
	|     10 | ACCOUNTING | NEW YORK |
	|     20 | RESEARCH   | DALLAS   |
	|     30 | SALES      | CHICAGO  |
	|     40 | OPERATIONS | BOSTON   |
	+--------+------------+----------+

	insert into dept_bak select * from dept; //�����ã�

	mysql> select * from dept_bak;
	+--------+------------+----------+
	| DEPTNO | DNAME      | LOC      |
	+--------+------------+----------+
	|     10 | ACCOUNTING | NEW YORK |
	|     20 | RESEARCH   | DALLAS   |
	|     30 | SALES      | CHICAGO  |
	|     40 | OPERATIONS | BOSTON   |
	|     10 | ACCOUNTING | NEW YORK |
	|     20 | RESEARCH   | DALLAS   |
	|     30 | SALES      | CHICAGO  |
	|     40 | OPERATIONS | BOSTON   |
	+--------+------------+----------+

5������ɾ�����е����ݣ���truncate�Ƚ���Ҫ���������ա�

	//ɾ��dept_bak���е�����
	delete from dept_bak; //����ɾ�����ݵķ�ʽ�Ƚ�����

	mysql> select * from dept_bak;
	Empty set (0.00 sec)

	delete���ɾ�����ݵ�ԭ������delete����DML��䣡������
		���е����ݱ�ɾ���ˣ��������������Ӳ���ϵ���ʵ�洢�ռ䲻�ᱻ�ͷţ�����
		����ɾ��ȱ���ǣ�ɾ��Ч�ʱȽϵ͡�
		����ɾ���ŵ��ǣ�֧�ֻع�������˿����ٻָ����ݣ�����
	
	truncate���ɾ�����ݵ�ԭ����
		����ɾ��Ч�ʱȽϸߣ�����һ�νضϣ�����ɾ����
		����ɾ��ȱ�㣺��֧�ֻع���
		����ɾ���ŵ㣺���١�

	�÷���truncate table dept_bak; �����ֲ�������DDL��������

	����ǳ�����������¼��������
		ɾ����ʱ��ʹ��delete��Ҳ����Ҫִ��1��Сʱ����ɾ���꣡Ч�ʽϵ͡�
		����ѡ��ʹ��truncateɾ�����е����ݡ�ֻ��Ҫ����1���ӵ�ʱ���ɾ��������Ч�ʽϸߡ�
		����ʹ��truncate֮ǰ��������ϸѯ�ʿͻ��Ƿ����Ҫɾ����������ɾ��֮�󲻿ɻָ���

		truncate��ɾ�����е����ݣ������ڣ�
	
	ɾ����������
		drop table ����; // �ⲻ��ɾ�����е����ݣ����ǰѱ�ɾ����

6���Ա��ṹ����ɾ�ģ�
	
	ʲô�ǶԱ��ṹ���޸ģ�
		����һ���ֶΣ�ɾ��һ���ֶΣ��޸�һ���ֶΣ�����
	
	�Ա��ṹ���޸���Ҫʹ�ã�alter
	����DDL���

	DDL������create drop alter
	
	��һ����ʵ�ʵĿ����У�����һ��ȷ��֮�󣬱�һ����ƺ�֮�󣬺��ٵ�
	���б��ṹ���޸ġ���Ϊ���������е�ʱ���޸ı��ṹ���ɱ��Ƚϸߡ�
	�޸ı��Ľṹ����Ӧ��java�������Ҫ���д������޸ġ��ɱ��ǱȽϸߵġ�
	�������Ӧ���������Ա���е���

	�ڶ��������޸ı��ṹ�Ĳ������٣��������ǲ���Ҫ���գ������һ��
	���Ҫ�޸ı��ṹ�������ʹ�ù��ߣ�������

	�޸ı��ṹ�Ĳ����ǲ���Ҫд��java�����еġ�ʵ����Ҳ����java����Ա�ķ��롣

7��Լ�����ǳ���Ҫ�������*****��

7.1��ʲô��Լ����
	Լ����Ӧ��Ӣ�ﵥ�ʣ�constraint
	�ڴ�������ʱ�����ǿ��Ը����е��ֶμ���һЩԼ��������֤����������ݵ�
	�����ԡ���Ч�ԣ�����

	Լ�������þ���Ϊ�˱�֤�����е�������Ч����

7.2��Լ��������Щ��
	�ǿ�Լ����not null
	Ψһ��Լ��: unique
	����Լ��: primary key �����PK��
	���Լ����foreign key�����FK��
	���Լ����check��mysql��֧�֣�oracle֧�֣�

	���������ص�ѧϰ�ĸ�Լ����
		not null
		unique
		primary key
		foreign key

7.3���ǿ�Լ����not null

	�ǿ�Լ��not nullԼ�����ֶβ���ΪNULL��
	drop table if exists t_vip;
	create table t_vip(
		id int,
		name varchar(255) not null  // not nullֻ���м�Լ����û�б���Լ����
	);
	insert into t_vip(id,name) values(1,'zhangsan');
	insert into t_vip(id,name) values(2,'lisi');

	insert into t_vip(id) values(3);
	ERROR 1364 (HY000): Field 'name' doesn't have a default value

	С������
		xxxx.sql�����ļ�����Ϊsql�ű��ļ���
		sql�ű��ļ��б�д�˴�����sql��䡣
		����ִ��sql�ű��ļ���ʱ�򣬸��ļ������е�sql����ȫ��ִ�У�
		������ִ��SQL��䣬����ʹ��sql�ű��ļ���
		��mysql������ôִ��sql�ű��أ�
			mysql> source D:\course\03-MySQL\document\vip.sql
		
		����ʵ�ʵĹ����У���һ�쵽�˹�˾����Ŀ���������һ��xxx.sql�ļ���
		��ִ������ű��ļ���������ϵ����ݿ����ݾ����ˣ�

7.4��Ψһ��Լ��: unique

	Ψһ��Լ��uniqueԼ�����ֶβ����ظ������ǿ���ΪNULL��
	drop table if exists t_vip;
	create table t_vip(
		id int,
		name varchar(255) unique,
		email varchar(255)
	);
	insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
	insert into t_vip(id,name,email) values(2,'lisi','lisi@123.com');
	insert into t_vip(id,name,email) values(3,'wangwu','wangwu@123.com');
	select * from t_vip;

	insert into t_vip(id,name,email) values(4,'wangwu','wangwu@sina.com');
	ERROR 1062 (23000): Duplicate entry 'wangwu' for key 'name'

	insert into t_vip(id) values(4);
	insert into t_vip(id) values(5);
	+------+----------+------------------+
	| id   | name     | email            |
	+------+----------+------------------+
	|    1 | zhangsan | zhangsan@123.com |
	|    2 | lisi     | lisi@123.com     |
	|    3 | wangwu   | wangwu@123.com   |
	|    4 | NULL     | NULL             |
	|    5 | NULL     | NULL             |
	+------+----------+------------------+
	name�ֶ���Ȼ��uniqueԼ���ˣ����ǿ���ΪNULL��

	������name��email�����ֶ�������������Ψһ�ԣ�������
		drop table if exists t_vip;
		create table t_vip(
			id int,
			name varchar(255) unique,  // Լ��ֱ�����ӵ��к���ģ������м�Լ����
			email varchar(255) unique
		);
		���ű����������ǲ����������ϡ������󡱵ġ�
		����������ʾ��name����Ψһ�ԣ�email����Ψһ�ԡ�����Ψһ��

		���������������Ƿ����ҡ������󡱵ġ�
		������������Ϸ�ʽ�������Ļ����϶�����ʧ�ܣ���Ϊ'zhangsan'��'zhangsan'�ظ��ˡ�
		insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
		insert into t_vip(id,name,email) values(2,'zhangsan','zhangsan@sina.com');

		��ô���������ı������ܷ����������أ�
			drop table if exists t_vip;
			create table t_vip(
				id int,
				name varchar(255),
				email varchar(255),
				unique(name,email) // Լ��û���������еĺ��棬����Լ������Ϊ����Լ����
			);
			insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
			insert into t_vip(id,name,email) values(2,'zhangsan','zhangsan@sina.com');
			select * from t_vip;

			name��email�����ֶ���������Ψһ������
			insert into t_vip(id,name,email) values(3,'zhangsan','zhangsan@sina.com');
			ERROR 1062 (23000): Duplicate entry 'zhangsan-zhangsan@sina.com' for key 'name'

		ʲôʱ��ʹ�ñ���Լ���أ�
			��Ҫ������ֶ�������������ĳһ��Լ����ʱ����Ҫʹ�ñ���Լ����

	unique ��not null����������
		drop table if exists t_vip;
		create table t_vip(
			id int,
			name varchar(255) not null unique
		);

		mysql> desc t_vip;
		+-------+--------------+------+-----+---------+-------+
		| Field | Type         | Null | Key | Default | Extra |
		+-------+--------------+------+-----+---------+-------+
		| id    | int(11)      | YES  |     | NULL    |       |
		| name  | varchar(255) | NO   | PRI | NULL    |       |
		+-------+--------------+------+-----+---------+-------+

		��mysql���У����һ���ֶ�ͬʱ��not null��uniqueԼ���Ļ���
		���ֶ��Զ���������ֶΡ���ע�⣺oracle�в�һ������

		insert into t_vip(id,name) values(1,'zhangsan');

		insert into t_vip(id,name) values(2,'zhangsan'); //�����ˣ�name�����ظ�

		insert into t_vip(id) values(2); //�����ˣ�name����ΪNULL��

7.5������Լ����primary key�����PK���ǳ���Ҫ�����*****

	����Լ����������
		����Լ��������һ��Լ����
		�����ֶΣ����ֶ�������������Լ�����������ֶν����������ֶ�
		����ֵ�������ֶ��е�ÿһ��ֵ������������ֵ��
	
	ʲô����������ɶ�ã�
		����ֵ��ÿһ�м�¼��Ψһ��ʶ��
		����ֵ��ÿһ�м�¼������֤�ţ�����
	
	��ס���κ�һ�ű���Ӧ����������û������������Ч����

	������������not null + unique������ֵ������NULL��ͬʱҲ�����ظ�����

	��ô��һ�ű���������Լ���أ�
		drop table if exists t_vip;
		// 1���ֶ�����������������һ����
		create table t_vip(
			id int primary key,  //�м�Լ��
			name varchar(255)
		);
		insert into t_vip(id,name) values(1,'zhangsan');
		insert into t_vip(id,name) values(2,'lisi');

		//���󣺲����ظ�
		insert into t_vip(id,name) values(2,'wangwu');
		ERROR 1062 (23000): Duplicate entry '2' for key 'PRIMARY'

		//���󣺲���ΪNULL
		insert into t_vip(name) values('zhaoliu');
		ERROR 1364 (HY000): Field 'id' doesn't have a default value
	
	������������������ʹ�ñ���Լ����
		drop table if exists t_vip;
		create table t_vip(
			id int,
			name varchar(255),
			primary key(id)  // ����Լ��
		);
		insert into t_vip(id,name) values(1,'zhangsan');

		//����
		insert into t_vip(id,name) values(1,'lisi');
		ERROR 1062 (23000): Duplicate entry '1' for key 'PRIMARY'
	
	����Լ����Ҫ�Ǹ�����ֶ�������������Լ����
		drop table if exists t_vip;
		// id��name��������������������������������
		create table t_vip(
			id int,
			name varchar(255),
			email varchar(255),
			primary key(id,name)
		);
		insert into t_vip(id,name,email) values(1,'zhangsan','zhangsan@123.com');
		insert into t_vip(id,name,email) values(1,'lisi','lisi@123.com');

		//���󣺲����ظ�
		insert into t_vip(id,name,email) values(1,'lisi','lisi@123.com');
		ERROR 1062 (23000): Duplicate entry '1-lisi' for key 'PRIMARY'

		��ʵ�ʿ����в�����ʹ�ã���������������ʹ�õ�һ������
		��Ϊ����ֵ���ڵ�����������м�¼������֤�ţ�ֻҪ����ﵽ���ɣ���һ��������������
		���������Ƚϸ��ӣ�������ʹ�ã�����
	
	һ����������Լ���ܼ�������
		drop table if exists t_vip;
		create table t_vip(
			id int primary key,
			name varchar(255) primary key
		);
		ERROR 1068 (42000): Multiple primary key defined
		���ۣ�һ�ű�������Լ��ֻ������1����������ֻ����1������
	
	����ֵ����ʹ�ã�
		int
		bigint
		char
		�����͡�

		������ʹ�ã�varchar��������������ֵһ�㶼�����֣�һ�㶼�Ƕ����ģ�

	�������ˣ���һ�����͸�������֮�⣬�������������з��ࣿ
		��Ȼ����������ֵ��һ����Ȼ������ҵ��û��ϵ��
		ҵ������������ֵ��ҵ����ܹ��������������п��˺�������ֵ�������ҵ��������

		��ʵ�ʿ�����ʹ��ҵ�������࣬����ʹ����Ȼ������һЩ��
			��Ȼ����ʹ�ñȽ϶࣬��Ϊ����ֻҪ�������ظ����У�����Ҫ�����塣
			ҵ���������ã���Ϊ����һ����ҵ��ҹ�����ô��ҵ�����䶯��ʱ��
			���ܻ�Ӱ�쵽����ֵ������ҵ������������ʹ�á�����ʹ����Ȼ������

	��mysql���У���һ�ֻ��ƣ����԰��������Զ�ά��һ������ֵ��
		drop table if exists t_vip;
		create table t_vip(
			id int primary key auto_increment, //auto_increment��ʾ��������1��ʼ����1������
			name varchar(255)
		);
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		insert into t_vip(name) values('zhangsan');
		select * from t_vip;

		+----+----------+
		| id | name     |
		+----+----------+
		|  1 | zhangsan |
		|  2 | zhangsan |
		|  3 | zhangsan |
		|  4 | zhangsan |
		|  5 | zhangsan |
		|  6 | zhangsan |
		|  7 | zhangsan |
		|  8 | zhangsan |
		+----+----------+
		
7.6�����Լ����foreign key�����FK���ǳ���Ҫ�����*****

	���Լ���漰����������
		���Լ����һ��Լ����foreign key��
		����ֶΣ����ֶ������������Լ��
		���ֵ������ֶε��е�ÿһ��ֵ��


	ҵ�񱳾���
		��������ݿ�������������༶��ѧ��������Ϣ��

		��һ�ַ������༶��ѧ���洢��һ�ű��У�����
		t_student
		no(pk)			name		classno			classname
		----------------------------------------------------------------------------------
		1					jack			100			�����д�������ׯ��ڶ���ѧ����1��
		2					lucy			100			�����д�������ׯ��ڶ���ѧ����1��
		3					lilei			100			�����д�������ׯ��ڶ���ѧ����1��
		4					hanmeimei	100			�����д�������ׯ��ڶ���ѧ����1��
		5					zhangsan		101			�����д�������ׯ��ڶ���ѧ����2��
		6					lisi			101			�����д�������ׯ��ڶ���ѧ����2��
		7					wangwu		101			�����д�������ׯ��ڶ���ѧ����2��
		8					zhaoliu		101			�����д�������ׯ��ڶ���ѧ����2��
		�������Ϸ�����ȱ�㣺
			�������࣬�ռ��˷ѣ�������
			�������ǱȽ�ʧ�ܵģ�
		
		�ڶ��ַ������༶һ�ű���ѧ��һ�ű�����
		
		t_class �༶��
		classno(pk)			classname
		------------------------------------------------------
		100					�����д�������ׯ��ڶ���ѧ����1��
		101					�����д�������ׯ��ڶ���ѧ����1��
	
		t_student ѧ����
		no(pk)			name				cno(FK����t_class���ű���classno)
		----------------------------------------------------------------
		1					jack				100
		2					lucy				100
		3					lilei				100
		4					hanmeimei		100
		5					zhangsan			101
		6					lisi				101
		7					wangwu			101
		8					zhaoliu			101

		��cno�ֶ�û���κ�Լ����ʱ�򣬿��ܻᵼ��������Ч�����ܳ���һ��102������102�༶�����ڡ�
		����Ϊ�˱�֤cno�ֶ��е�ֵ����100��101����Ҫ��cno�ֶ��������Լ����
		��ô��cno�ֶξ�������ֶΡ�cno�ֶ��е�ÿһ��ֵ�������ֵ��

		ע�⣺
			t_class�Ǹ���
			t_student���ӱ�

			ɾ������˳��
				��ɾ�ӣ���ɾ����

			��������˳��
				�ȴ��������ٴ����ӡ�

			ɾ�����ݵ�˳��
				��ɾ�ӣ���ɾ����

			�������ݵ�˳��
				�Ȳ��븸���ٲ����ӡ�

		˼�����ӱ��е�������õĸ����е�ĳ���ֶΣ������õ�����ֶα�����������
			��һ���������������پ���uniqueԼ����

		���ԣ��������ΪNULL��
			���ֵ����ΪNULL��

8���洢���棨�˽����ݣ�

8.1��ʲô�Ǵ洢���棬��ʲô���أ�
	�洢������MySQL�����е�һ������������ݿ���û�С���Oracle���У����ǲ���������֣�
	�洢����������ָ߶˴����ϵ��Ρ�
	ʵ���ϴ洢������һ�����洢/��֯���ݵķ�ʽ��
	��ͬ�Ĵ洢���棬���洢���ݵķ�ʽ��ͬ��

8.2����ô��������/ָ�����洢���桱�أ�
	show create table t_student;

	�����ڽ�����ʱ�����ָ���洢���档
	CREATE TABLE `t_student` (
	  `no` int(11) NOT NULL AUTO_INCREMENT,
	  `name` varchar(255) DEFAULT NULL,
	  `cno` int(11) DEFAULT NULL,
	  PRIMARY KEY (`no`),
	  KEY `cno` (`cno`),
	  CONSTRAINT `t_student_ibfk_1` FOREIGN KEY (`cno`) REFERENCES `t_class` (`classno`)
	) ENGINE=InnoDB AUTO_INCREMENT=11 DEFAULT CHARSET=utf8

	�ڽ�����ʱ����������С���ŵ�")"���ұ�ʹ�ã�
		ENGINE��ָ���洢���档
		CHARSET��ָ�����ű����ַ����뷽ʽ��
	
		���ۣ�
			mysqlĬ�ϵĴ洢�����ǣ�InnoDB
			mysqlĬ�ϵ��ַ����뷽ʽ�ǣ�utf8
	
	����ʱָ���洢���棬�Լ��ַ����뷽ʽ��
	create table t_product(
		id int primary key,
		name varchar(255)
	)engine=InnoDB default charset=gbk;

8.3����ô�鿴mysql֧����Щ�洢�����أ�

mysql> select version();
+-----------+
| version() |
+-----------+
| 5.5.36    |
+-----------+

��� show engines \G

*************************** 1. row ***************************
      Engine: FEDERATED
     Support: NO
     Comment: Federated MySQL storage engine
Transactions: NULL
          XA: NULL
  Savepoints: NULL
*************************** 2. row ***************************
      Engine: MRG_MYISAM
     Support: YES
     Comment: Collection of identical MyISAM tables
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 3. row ***************************
      Engine: MyISAM
     Support: YES
     Comment: MyISAM storage engine
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 4. row ***************************
      Engine: BLACKHOLE
     Support: YES
     Comment: /dev/null storage engine (anything you write to it disappears
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 5. row ***************************
      Engine: CSV
     Support: YES
     Comment: CSV storage engine
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 6. row ***************************
      Engine: MEMORY
     Support: YES
     Comment: Hash based, stored in memory, useful for temporary tables
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 7. row ***************************
      Engine: ARCHIVE
     Support: YES
     Comment: Archive storage engine
Transactions: NO
          XA: NO
  Savepoints: NO
*************************** 8. row ***************************
      Engine: InnoDB
     Support: DEFAULT
     Comment: Supports transactions, row-level locking, and foreign keys
Transactions: YES
          XA: YES
  Savepoints: YES
*************************** 9. row ***************************
      Engine: PERFORMANCE_SCHEMA
     Support: YES
     Comment: Performance Schema
Transactions: NO
          XA: NO
  Savepoints: NO

mysql֧�־Ŵ�洢���棬��ǰ5.5.36֧��8�����汾��֧ͬ�������ͬ��

8.4������mysql���õĴ洢�������һ��

MyISAM�洢���棿
	�������ı���������������
		ʹ�������ļ���ʾÿ������
			��ʽ�ļ� �� �洢���ṹ�Ķ��壨mytable.frm��
			�����ļ� �� �洢���е����ݣ�mytable.MYD��
			�����ļ� �� �洢����������mytable.MYI����������һ�����Ŀ¼����Сɨ�跶Χ����߲�ѯЧ�ʵ�һ�ֻ��ơ�
		�ɱ�ת��Ϊѹ����ֻ��������ʡ�ռ�

		��ʾһ�£�
			����һ�ű���˵��ֻҪ��������
			���߼���uniqueԼ�����ֶ��ϻ��Զ�����������

		MyISAM�洢�����ص㣺
			�ɱ�ת��Ϊѹ����ֻ��������ʡ�ռ�
			�������ִ洢��������ƣ�������
		
		MyISAM��֧��������ƣ���ȫ�Ե͡�

InnoDB�洢���棿
	����mysqlĬ�ϵĴ洢���棬ͬʱҲ��һ���������Ĵ洢���档
	InnoDB֧������֧�����ݿ�������Զ��ָ����ơ�
	InnoDB�洢��������Ҫ���ص��ǣ��ǳ���ȫ��

	�������ı�����������Ҫ������
		�C ÿ�� InnoDB �������ݿ�Ŀ¼����.frm ��ʽ�ļ���ʾ
		�C InnoDB ���ռ� tablespace �����ڴ洢�������ݣ����ռ���һ���߼����ơ����ռ�洢����+��������

		�C �ṩһ��������¼�����Ի����־�ļ�
		�C �� COMMIT(�ύ)��SAVEPOINT ��ROLLBACK(�ع�)֧��������
		�C �ṩȫ ACID ����
		�C �� MySQL �������������ṩ�Զ��ָ�
		�C ��汾��MVCC�����м�����
		�C ֧����������õ������ԣ���������ɾ���͸���
	
	InnoDB�����ص����֧������
		�Ա�֤���ݵİ�ȫ��Ч�ʲ��Ǻܸߣ�����Ҳ����ѹ��������ת��Ϊֻ����
		���ܺܺõĽ�ʡ�洢�ռ䡣

MEMORY�洢���棿
	ʹ�� MEMORY �洢����ı��������ݴ洢���ڴ��У����еĳ��ȹ̶���
	�������ص�ʹ�� MEMORY �洢����ǳ��졣

	MEMORY �洢��������ı���������������
		�C �����ݿ�Ŀ¼�ڣ�ÿ��������.frm ��ʽ���ļ���ʾ��
		�C �����ݼ��������洢���ڴ��С���Ŀ�ľ��ǿ죬��ѯ�죡��
		�C ���������ơ�
		�C ���ܰ��� TEXT �� BLOB �ֶΡ�

	MEMORY �洢������ǰ����ΪHEAP ���档

	MEMORY�����ŵ㣺��ѯЧ������ߵġ�����Ҫ��Ӳ�̽�����
	MEMORY����ȱ�㣺����ȫ���ػ�֮��������ʧ����Ϊ���ݺ������������ڴ浱�С�

9�������ص㣺�����*****���������⣬�������գ�

9.1��ʲô������

	һ��������ʵ����һ��������ҵ���߼���
	��һ����С�Ĺ�����Ԫ�������ٷ֡�

	ʲô��һ��������ҵ���߼���
		����ת�ˣ���A�˻���B�˻���ת��10000.
		��A�˻���Ǯ��ȥ10000��update��䣩
		��B�˻���Ǯ����10000��update��䣩
		�����һ��������ҵ���߼���

		���ϵĲ�����һ����С�Ĺ�����Ԫ��Ҫôͬʱ�ɹ���Ҫôͬʱʧ�ܣ������ٷ֡�
		������update���Ҫ�����ͬʱ�ɹ�����ͬʱʧ�ܣ��������ܱ�֤Ǯ����ȷ�ġ�
	
9.2��ֻ��DML���Ż���������һ˵���������������޹أ�����
	insert
	delete
	update
	ֻ�����ϵ��������������й�ϵ��������û�й�ϵ��

	��Ϊ ֻ�����ϵ�������������ݿ�������ݽ�������ɾ���ĵġ�
	ֻҪ��Ĳ���һ���漰�����ݵ�����ɾ���ģ���ô��һ��Ҫ���ǰ�ȫ���⡣

	���ݰ�ȫ��һλ������

9.3���������е�ҵ��ֻҪһ��DML��������ɣ����б�Ҫ�������������
	������Ϊ��ĳ���µ�ʱ����Ҫ����DML��乲ͬ��������������ɣ�
	������Ҫ����Ĵ��ڡ�����κ�һ�����ӵ��¶�����һ��DML���㶨��
	��ô������û�д��ڵļ�ֵ�ˡ�

	����ʲô�������أ�
		˵���ף�˵�������ϣ�һ��������ʵ���Ƕ���DML���ͬʱ�ɹ�������ͬʱʧ�ܣ�
	
	���񣺾���������DML���ͬʱ�ɹ�������ͬʱʧ�ܣ�

9.4����������ô��������DML���ͬʱ�ɹ���ͬʱʧ�ܵ��أ�

	InnoDB�洢���棺�ṩһ��������¼�����Ի����־�ļ�

	�������ˣ�
	insert
	insert
	insert
	delete
	update
	update
	update
	��������ˣ�

	�������ִ�й����У�ÿһ��DML�Ĳ��������¼���������Ի����־�ļ����С�
	�������ִ�й����У����ǿ����ύ����Ҳ���Իع�����

	�ύ����
		��������Ի����־�ļ���������ȫ�����׳־û������ݿ���С�
		�ύ�����־�ţ�����Ľ�����������һ��ȫ���ɹ��Ľ�����

	�ع�����
		��֮ǰ���е�DML����ȫ��������������������Ի����־�ļ�
		�ع������־�ţ�����Ľ�����������һ��ȫ��ʧ�ܵĽ�����

9.5����ô�ύ������ô�ع�����
	�ύ����commit; ���
	�ع�����rollback; ��䣨�ع���Զ����ֻ�ܻع�����һ�ε��ύ�㣡��

	�����Ӧ��Ӣ�ﵥ���ǣ�transaction

	����һ�£���mysql����Ĭ�ϵ�������Ϊ�������ģ�
		mysqlĬ���������֧���Զ��ύ����ġ����Զ��ύ��
		ʲô���Զ��ύ��
			ÿִ��һ��DML��䣬���ύһ�Σ�

		�����Զ��ύʵ�����ǲ��������ǵĿ���ϰ�ߣ���Ϊһ��ҵ��
		ͨ������Ҫ����DML��乲ִͬ�в�����ɵģ�Ϊ�˱�֤����
		�İ�ȫ������Ҫ��ͬʱ�ɹ�֮�����ύ�����Բ���ִ��һ��
		���ύһ����
	
	��ô��mysql���Զ��ύ���ƹرյ��أ�
		��ִ��������start transaction;
	
	��ʾ����
		---------------------------------�ع�����----------------------------------------
		mysql> use bjpowernode;
		Database changed
		mysql> select * from dept_bak;
		Empty set (0.00 sec)

		mysql> start transaction;
		Query OK, 0 rows affected (0.00 sec)

		mysql> insert into dept_bak values(10,'abc', 'tj');
		Query OK, 1 row affected (0.00 sec)

		mysql> insert into dept_bak values(10,'abc', 'tj');
		Query OK, 1 row affected (0.00 sec)

		mysql> select * from dept_bak;
		+--------+-------+------+
		| DEPTNO | DNAME | LOC  |
		+--------+-------+------+
		|     10 | abc   | tj   |
		|     10 | abc   | tj   |
		+--------+-------+------+
		2 rows in set (0.00 sec)

		mysql> rollback;
		Query OK, 0 rows affected (0.00 sec)

		mysql> select * from dept_bak;
		Empty set (0.00 sec)


		---------------------------------�ύ����----------------------------------------
		mysql> use bjpowernode;
		Database changed
		mysql> select * from dept_bak;
		+--------+-------+------+
		| DEPTNO | DNAME | LOC  |
		+--------+-------+------+
		|     10 | abc   | bj   |
		+--------+-------+------+
		1 row in set (0.00 sec)

		mysql> start transaction;
		Query OK, 0 rows affected (0.00 sec)

		mysql> insert into dept_bak values(20,'abc
		Query OK, 1 row affected (0.00 sec)

		mysql> insert into dept_bak values(20,'abc
		Query OK, 1 row affected (0.00 sec)

		mysql> insert into dept_bak values(20,'abc
		Query OK, 1 row affected (0.00 sec)

		mysql> commit;
		Query OK, 0 rows affected (0.01 sec)

		mysql> select * from dept_bak;
		+--------+-------+------+
		| DEPTNO | DNAME | LOC  |
		+--------+-------+------+
		|     10 | abc   | bj   |
		|     20 | abc   | tj   |
		|     20 | abc   | tj   |
		|     20 | abc   | tj   |
		+--------+-------+------+
		4 rows in set (0.00 sec)

		mysql> rollback;
		Query OK, 0 rows affected (0.00 sec)

		mysql> select * from dept_bak;
		+--------+-------+------+
		| DEPTNO | DNAME | LOC  |
		+--------+-------+------+
		|     10 | abc   | bj   |
		|     20 | abc   | tj   |
		|     20 | abc   | tj   |
		|     20 | abc   | tj   |
		+--------+-------+------+
		4 rows in set (0.00 sec)

9.6���������4�����ԣ�

	A��ԭ����
		˵����������С�Ĺ�����Ԫ�������ٷ֡�

	C��һ����
		��������Ҫ����ͬһ�������У����в�������ͬʱ�ɹ�������ͬʱʧ�ܣ�
		�Ա�֤���ݵ�һ���ԡ�

	I��������
		A�����B����֮�����һ���ĸ��롣
		����A�ͽ���B֮����һ��ǽ�����ǽ���Ǹ����ԡ�
		A�����ڲ���һ�ű���ʱ����һ������BҲ�������ű�������������

	D���־���
		�������ս�����һ�����ϡ������ύ�����൱�ڽ�û�б��浽Ӳ���ϵ�����
		���浽Ӳ���ϣ�

9.7���ص��о�һ������ĸ����ԣ�����

	A���Һ�B�����м���һ��ǽ�����ǽ���Ժܺ�Ҳ���Ժܱ������������ĸ��뼶��
	���ǽԽ�񣬱�ʾ���뼶���Խ�ߡ�

	���������֮��ĸ��뼶������Щ�أ�4������

		��δ�ύ��read uncommitted����͵ĸ��뼶�𣩡�û���ύ�Ͷ����ˡ�
			ʲô�Ƕ�δ�ύ��
				����A���Զ�ȡ������Bδ�ύ�����ݡ�
			���ָ��뼶����ڵ�������ǣ�
				�������(Dirty Read)
				���ǳƶ����������ݡ�
			���ָ��뼶��һ�㶼�������ϵģ�����������ݿ���뼶���Ƕ����𲽣�

		�����ύ��read committed���ύ֮����ܶ�����
			ʲô�Ƕ����ύ��
				����Aֻ�ܶ�ȡ������B�ύ֮������ݡ�
			���ָ��뼶������ʲô���⣿
				��������������
			���ָ��뼶�����ʲô���⣿
				�����ظ���ȡ���ݡ�
				ʲô�ǲ����ظ���ȡ�����أ�
					��������֮�󣬵�һ�ζ�����������3������ǰ����û��
					���������ܵڶ����ٶ�ȡ��ʱ�򣬶�����������4����3������4
					��Ϊ�����ظ���ȡ��

			���ָ��뼶���ǱȽ���ʵ�����ݣ�ÿһ�ζ����������Ǿ��Ե���ʵ��
			oracle���ݿ�Ĭ�ϵĸ��뼶���ǣ�read committed

		���ظ�����repeatable read���ύ֮��Ҳ����������Զ��ȡ�Ķ��Ǹտ�������ʱ�����ݡ�
			ʲô�ǿ��ظ���ȡ��
				����A����֮�󣬲����Ƕ�ã�ÿһ��������A�ж�ȡ��������
				����һ�µġ���ʹ����B�������Ѿ��޸ģ������ύ�ˣ�����A
				��ȡ�������ݻ���û�з����ı䣬����ǿ��ظ�����
			���ظ��������ʲô���⣿
				����˲����ظ���ȡ���ݡ�
			���ظ������ڵ�������ʲô��
				���Ի���ֻ�Ӱ����
				ÿһ�ζ�ȡ�������ݶ��ǻ��󡣲�����ʵ��
			
			�糿9�㿪ʼ����������ֻҪ���񲻽�����������9�㣬���������ݻ���������
			�������Ǽ��󡣲������Ե���ʵ��

			mysql��Ĭ�ϵ�������뼶������������������������������

		���л�/���л���serializable����ߵĸ��뼶��
			������߸��뼶��Ч����͡���������е����⡣
			���ָ��뼶���ʾ�����Ŷӣ����ܲ�����
			synchronized���߳�ͬ��������ͬ����
			ÿһ�ζ�ȡ�������ݶ�������ʵ�ģ�����Ч������͵ġ�
	
9.8����֤���ָ��뼶��

�鿴���뼶��SELECT @@tx_isolation
+-----------------+
| @@tx_isolation  |
+-----------------+
| REPEATABLE-READ |
+-----------------+
mysqlĬ�ϵĸ��뼶��


�����Եı�t_user
��֤��read uncommited
mysql> set global transaction isolation level read uncommitted;
����A												����B
--------------------------------------------------------------------------------
use bjpowernode;
													use bjpowernode;
start transaction;
select * from t_user;
													start transaction;
													insert into t_user values('zhangsan');
select * from t_user;




��֤��read commited
mysql> set global transaction isolation level read committed;
����A												����B
--------------------------------------------------------------------------------
use bjpowernode;
													use bjpowernode;
start transaction;
													start transaction;
select * from t_user;
													insert into t_user values('zhangsan');
select * from t_user;
													commit;
select * from t_user;






��֤��repeatable read
mysql> set global transaction isolation level repeatable read;
����A												����B
--------------------------------------------------------------------------------
use bjpowernode;
													use bjpowernode;
start transaction;
													start transaction;
select * from t_user;
													insert into t_user values('lisi');
													insert into t_user values('wangwu');
													commit;
select * from t_user;





��֤��serializable
mysql> set global transaction isolation level serializable;
����A												����B
--------------------------------------------------------------------------------
use bjpowernode;
													use bjpowernode;
start transaction;
													start transaction;
select * from t_user;
insert into t_user values('abc');
													select * from t_user;
