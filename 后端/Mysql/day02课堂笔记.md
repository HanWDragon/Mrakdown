mysql day02���ñʼ�

1���Ѳ�ѯ���ȥ���ظ���¼��distinct��
	ע�⣺ԭ�����ݲ��ᱻ�޸ģ�ֻ�ǲ�ѯ���ȥ�ء�
	ȥ����Ҫʹ��һ���ؼ��֣�distinct

	mysql> select distinct job from emp;
	+-----------+
	| job       |
	+-----------+
	| CLERK     |
	| SALESMAN  |
	| MANAGER   |
	| ANALYST   |
	| PRESIDENT |
	+-----------+

	// ������д�Ǵ���ģ��﷨����
	// distinctֻ�ܳ����������ֶε���ǰ����
	mysql> select ename,distinct job from emp;

	// distinct������job,deptno�����ֶ�֮ǰ����ʾ�����ֶ���������ȥ�ء�
	mysql> select distinct job,deptno from emp;
	+-----------+--------+
	| job       | deptno |
	+-----------+--------+
	| CLERK     |     20 |
	| SALESMAN  |     30 |
	| MANAGER   |     20 |
	| MANAGER   |     30 |
	| MANAGER   |     10 |
	| ANALYST   |     20 |
	| PRESIDENT |     10 |
	| CLERK     |     30 |
	| CLERK     |     10 |
	+-----------+--------+

	ͳ��һ�¹�����λ��������
		select count(distinct job) from emp;
		+---------------------+
		| count(distinct job) |
		+---------------------+
		|                   5 |
		+---------------------+

2�����Ӳ�ѯ

2.1��ʲô�����Ӳ�ѯ��
	��һ�ű��е�����ѯ����Ϊ������ѯ��
	emp����dept������������ѯ���ݣ���emp����ȡԱ�����֣���dept����ȡ�������֡�
	���ֿ����ѯ�����ű�����������ѯ���ݣ�����Ϊ���Ӳ�ѯ��

2.2�����Ӳ�ѯ�ķ��ࣿ

	�����﷨��������ࣺ
		SQL92��1992���ʱ����ֵ��﷨
		SQL99��1999���ʱ����ֵ��﷨
		���������ص�ѧϰSQL99.(��������м���ʾһ��SQL92������)
	
	���ݱ����ӵķ�ʽ���ࣺ
		�����ӣ�
			��ֵ����
			�ǵ�ֵ����
			������

		�����ӣ�
			�������ӣ������ӣ�
			�������ӣ������ӣ�

		ȫ���ӣ�������

2.3�������ű��������Ӳ�ѯʱ��û���κ����������ƻᷢ��ʲô����

	��������ѯÿ��Ա�����ڲ������ƣ�
		mysql> select ename,deptno from emp;
		+--------+--------+
		| ename  | deptno |
		+--------+--------+
		| SMITH  |     20 |
		| ALLEN  |     30 |
		| WARD   |     30 |
		| JONES  |     20 |
		| MARTIN |     30 |
		| BLAKE  |     30 |
		| CLARK  |     10 |
		| SCOTT  |     20 |
		| KING   |     10 |
		| TURNER |     30 |
		| ADAMS  |     20 |
		| JAMES  |     30 |
		| FORD   |     20 |
		| MILLER |     10 |
		+--------+--------+
		mysql> select * from dept;
		+--------+------------+----------+
		| DEPTNO | DNAME      | LOC      |
		+--------+------------+----------+
		|     10 | ACCOUNTING | NEW YORK |
		|     20 | RESEARCH   | DALLAS   |
		|     30 | SALES      | CHICAGO  |
		|     40 | OPERATIONS | BOSTON   |
		+--------+------------+----------+

		���ű�����û���κ��������ƣ�
		select ename,dname from emp, dept;
		+--------+------------+
		| ename  | dname      |
		+--------+------------+
		| SMITH  | ACCOUNTING |
		| SMITH  | RESEARCH   |
		| SMITH  | SALES      |
		| SMITH  | OPERATIONS |
		| ALLEN  | ACCOUNTING |
		| ALLEN  | RESEARCH   |
		| ALLEN  | SALES      |
		| ALLEN  | OPERATIONS |
		...
		56 rows in set (0.00 sec)
		14 * 4 = 56

		�����ű��������Ӳ�ѯ��û���κ��������Ƶ�ʱ�����ղ�ѯ�����������
		���ű������ĳ˻����������󱻳�Ϊ���ѿ��������󡣣��ѿ������ֵģ�����
		һ����ѧ���󡣣�

2.4����ô����ѿ���������
	����ʱ��������������������ļ�¼��ɸѡ������
	select 
		ename,dname 
	from 
		emp, dept
	where
		emp.deptno = dept.deptno;
	
	select 
		emp.ename,dept.dname 
	from 
		emp, dept
	where
		emp.deptno = dept.deptno;
	
	// �������������Ҫ��Ч�����⡣
	select 
		e.ename,d.dname 
	from 
		emp e, dept d
	where
		e.deptno = d.deptno; //SQL92�﷨��

	+--------+------------+
	| ename  | dname      |
	+--------+------------+
	| CLARK  | ACCOUNTING |
	| KING   | ACCOUNTING |
	| MILLER | ACCOUNTING |
	| SMITH  | RESEARCH   |
	| JONES  | RESEARCH   |
	| SCOTT  | RESEARCH   |
	| ADAMS  | RESEARCH   |
	| FORD   | RESEARCH   |
	| ALLEN  | SALES      |
	| WARD   | SALES      |
	| MARTIN | SALES      |
	| BLAKE  | SALES      |
	| TURNER | SALES      |
	| JAMES  | SALES      |
	+--------+------------+

	˼�������ղ�ѯ�Ľ��������14��������ƥ��Ĺ����У�ƥ��Ĵ�����������
		����56�Σ�ֻ������������ѡһ������û�м��١�
	
	ע�⣺ͨ���ѿ���������ó����������Ӵ���Խ��Ч��Խ�ͣ������������
	���Ӵ�����

2.5��������֮��ֵ���ӡ�

��������ѯÿ��Ա�����ڲ������ƣ���ʾԱ�����Ͳ�������
emp e��dept d���������ӡ������ǣ�e.deptno = d.deptno

SQL92�﷨��
	select 
		e.ename,d.dname
	from
		emp e, dept d
	where
		e.deptno = d.deptno;
	
	sql92��ȱ�㣺�ṹ�����������������������ͺ��ڽ�һ��ɸѡ�����������ŵ���where���档

SQL99�﷨��
	select 
		e.ename,d.dname
	from
		emp e
	join
		dept d
	on
		e.deptno = d.deptno;
	

	//inner����ʡ�ԣ�����inner�ɶ��Ը��ã�����һ�۾��ܿ������������ӣ�
	select 
		e.ename,d.dname
	from
		emp e
	inner join
		dept d
	on
		e.deptno = d.deptno; // �����ǵ�����ϵ�����Ա���Ϊ��ֵ���ӡ�

	
	sql99�ŵ㣺�����ӵ������Ƕ����ģ�����֮���������Ҫ��һ��ɸѡ���������������where

	SQL99�﷨��
		select 
			...
		from
			a
		join
			b
		on
			a��b����������
		where
			ɸѡ����

2.6��������֮�ǵ�ֵ����

�������ҳ�ÿ��Ա����н�ʵȼ���Ҫ����ʾԱ������н�ʡ�н�ʵȼ���
mysql> select * from emp; e
+-------+--------+-----------+------+------------+---------+---------+--------+
| EMPNO | ENAME  | JOB       | MGR  | HIREDATE   | SAL     | COMM    | DEPTNO |
+-------+--------+-----------+------+------------+---------+---------+--------+
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |
|  7499 | ALLEN  | SALESMAN  | 7698 | 1981-02-20 | 1600.00 |  300.00 |     30 |
|  7521 | WARD   | SALESMAN  | 7698 | 1981-02-22 | 1250.00 |  500.00 |     30 |
|  7566 | JONES  | MANAGER   | 7839 | 1981-04-02 | 2975.00 |    NULL |     20 |
....

mysql> select * from salgrade; s
+-------+-------+-------+
| GRADE | LOSAL | HISAL |
+-------+-------+-------+
|     1 |   700 |  1200 |
|     2 |  1201 |  1400 |
|     3 |  1401 |  2000 |
|     4 |  2001 |  3000 |
|     5 |  3001 |  9999 |
+-------+-------+-------+

select 
	e.ename, e.sal, s.grade
from
	emp e
join
	salgrade s
on
	e.sal between s.losal and s.hisal; // ��������һ��������ϵ����Ϊ�ǵ�ֵ���ӡ�



select 
	e.ename, e.sal, s.grade
from
	emp e
inner join
	salgrade s
on
	e.sal between s.losal and s.hisal;

+--------+---------+-------+
| ename  | sal     | grade |
+--------+---------+-------+
| SMITH  |  800.00 |     1 |
| ALLEN  | 1600.00 |     3 |
| WARD   | 1250.00 |     2 |
| JONES  | 2975.00 |     4 |
| MARTIN | 1250.00 |     2 |
| BLAKE  | 2850.00 |     4 |
| CLARK  | 2450.00 |     4 |
| SCOTT  | 3000.00 |     4 |
| KING   | 5000.00 |     5 |
| TURNER | 1500.00 |     3 |
| ADAMS  | 1100.00 |     1 |
| JAMES  |  950.00 |     1 |
| FORD   | 3000.00 |     4 |
| MILLER | 1300.00 |     2 |
+--------+---------+-------+

2.7��������֮������
��������ѯԱ�����ϼ��쵼��Ҫ����ʾԱ�����Ͷ�Ӧ���쵼����

mysql> select empno,ename,mgr from emp;
+-------+--------+------+
| empno | ename  | mgr  |
+-------+--------+------+
|  7369 | SMITH  | 7902 |
|  7499 | ALLEN  | 7698 |
|  7521 | WARD   | 7698 |
|  7566 | JONES  | 7839 |
|  7654 | MARTIN | 7698 |
|  7698 | BLAKE  | 7839 |
|  7782 | CLARK  | 7839 |
|  7788 | SCOTT  | 7566 |
|  7839 | KING   | NULL |
|  7844 | TURNER | 7698 |
|  7876 | ADAMS  | 7788 |
|  7900 | JAMES  | 7698 |
|  7902 | FORD   | 7566 |
|  7934 | MILLER | 7782 |
+-------+--------+------+

���ɣ�һ�ű��������ű���
emp a Ա����
+-------+--------+------+
| empno | ename  | mgr  |
+-------+--------+------+
|  7369 | SMITH  | 7902 |
|  7499 | ALLEN  | 7698 |
|  7521 | WARD   | 7698 |
|  7566 | JONES  | 7839 |
|  7654 | MARTIN | 7698 |
|  7698 | BLAKE  | 7839 |
|  7782 | CLARK  | 7839 |
|  7788 | SCOTT  | 7566 |
|  7839 | KING   | NULL |
|  7844 | TURNER | 7698 |
|  7876 | ADAMS  | 7788 |
|  7900 | JAMES  | 7698 |
|  7902 | FORD   | 7566 |
|  7934 | MILLER | 7782 |
+-------+--------+------+

emp b �쵼��
+-------+--------+------+
| empno | ename  | mgr  |
+-------+--------+------+
|  7369 | SMITH  | 7902 |
|  7499 | ALLEN  | 7698 |
|  7521 | WARD   | 7698 |
|  7566 | JONES  | 7839 |
|  7654 | MARTIN | 7698 |
|  7698 | BLAKE  | 7839 |
|  7782 | CLARK  | 7839 |
|  7788 | SCOTT  | 7566 |
|  7839 | KING   | NULL |
|  7844 | TURNER | 7698 |
|  7876 | ADAMS  | 7788 |
|  7900 | JAMES  | 7698 |
|  7902 | FORD   | 7566 |
|  7934 | MILLER | 7782 |
+-------+--------+------+

select 
	a.ename as 'Ա����', b.ename as '�쵼��'
from
	emp a
join
	emp b
on
	a.mgr = b.empno; //Ա�����쵼��� = �쵼��Ա�����

+--------+--------+
| Ա���� | �쵼��|
+--------+--------+
| SMITH  | FORD   |
| ALLEN  | BLAKE  |
| WARD   | BLAKE  |
| JONES  | KING   |
| MARTIN | BLAKE  |
| BLAKE  | KING   |
| CLARK  | KING   |
| SCOTT  | JONES  |
| TURNER | BLAKE  |
| ADAMS  | SCOTT  |
| JAMES  | BLAKE  |
| FORD   | JONES  |
| MILLER | CLARK  |
+--------+--------+
13����¼��û��KING���������ӡ�

���Ͼ����������еģ������ӣ����ɣ�һ�ű��������ű���

2.8��������

mysql> select * from emp; e
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

mysql> select * from dept; d
+--------+------------+----------+
| DEPTNO | DNAME      | LOC      |
+--------+------------+----------+
|     10 | ACCOUNTING | NEW YORK |
|     20 | RESEARCH   | DALLAS   |
|     30 | SALES      | CHICAGO  |
|     40 | OPERATIONS | BOSTON   |
+--------+------------+----------+

�����ӣ���A��B���ӣ�AB���ű�û�����ι�ϵ��ƽ�ȵġ���
select 
	e.ename,d.dname
from
	emp e
join
	dept d
on
	e.deptno = d.deptno; //�����ӵ��ص㣺����ܹ�ƥ����������������ݲ�ѯ������

+--------+------------+
| ename  | dname      |
+--------+------------+
| CLARK  | ACCOUNTING |
| KING   | ACCOUNTING |
| MILLER | ACCOUNTING |
| SMITH  | RESEARCH   |
| JONES  | RESEARCH   |
| SCOTT  | RESEARCH   |
| ADAMS  | RESEARCH   |
| FORD   | RESEARCH   |
| ALLEN  | SALES      |
| WARD   | SALES      |
| MARTIN | SALES      |
| BLAKE  | SALES      |
| TURNER | SALES      |
| JAMES  | SALES      |
+--------+------------+

�����ӣ��������ӣ���
select 
	e.ename,d.dname
from
	emp e 
right join 
	dept d
on
	e.deptno = d.deptno;

// outer�ǿ���ʡ�Եģ����ſɶ���ǿ��
select 
	e.ename,d.dname
from
	emp e 
right outer join 
	dept d
on
	e.deptno = d.deptno;

right����ʲô����ʾ��join�ؼ����ұߵ����ű�������������Ҫ��Ϊ�˽�
���ű�������ȫ����ѯ�������Ӵ��Ź�����ѯ��ߵı���
�������ӵ��У����ű����ӣ����������ι�ϵ��

�����ӣ��������ӣ���
select 
	e.ename,d.dname
from
	dept d 
left join 
	emp e
on
	e.deptno = d.deptno;

// outer�ǿ���ʡ�Եģ����ſɶ���ǿ��
select 
	e.ename,d.dname
from
	dept d 
left outer join 
	emp e
on
	e.deptno = d.deptno;

����right�����������ӣ��ֽ��������ӡ�
����left�����������ӣ��ֽ��������ӡ�
�κ�һ�������Ӷ��������ӵ�д����
�κ�һ�������Ӷ��������ӵ�д����

+--------+------------+
| ename  | dname      |
+--------+------------+
| CLARK  | ACCOUNTING |
| KING   | ACCOUNTING |
| MILLER | ACCOUNTING |
| SMITH  | RESEARCH   |
| JONES  | RESEARCH   |
| SCOTT  | RESEARCH   |
| ADAMS  | RESEARCH   |
| FORD   | RESEARCH   |
| ALLEN  | SALES      |
| WARD   | SALES      |
| MARTIN | SALES      |
| BLAKE  | SALES      |
| TURNER | SALES      |
| JAMES  | SALES      |
| NULL   | OPERATIONS |
+--------+------------+

˼���������ӵĲ�ѯ�������һ���� >= �����ӵĲ�ѯ���������
	��ȷ��


��������ѯÿ��Ա�����ϼ��쵼��Ҫ����ʾ����Ա�������ֺ��쵼����
	select 
		a.ename as 'Ա����', b.ename as '�쵼��'
	from
		emp a
	left join
		emp b
	on
		a.mgr = b.empno; 
	
	+--------+--------+
	| Ա����      | �쵼��     |
	+--------+--------+
	| SMITH  | FORD   |
	| ALLEN  | BLAKE  |
	| WARD   | BLAKE  |
	| JONES  | KING   |
	| MARTIN | BLAKE  |
	| BLAKE  | KING   |
	| CLARK  | KING   |
	| SCOTT  | JONES  |
	| KING   | NULL   |
	| TURNER | BLAKE  |
	| ADAMS  | SCOTT  |
	| JAMES  | BLAKE  |
	| FORD   | JONES  |
	| MILLER | CLARK  |
	+--------+--------+


2.9�����ű������ű���ô���ӣ�
	�﷨��
		select 
			...
		from
			a
		join
			b
		on
			a��b����������
		join
			c
		on
			a��c����������
		right join
			d
		on
			a��d����������
		
		һ��SQL�������Ӻ������ӿ��Ի�ϡ������Գ��֣�

	�������ҳ�ÿ��Ա���Ĳ��������Լ����ʵȼ���
	Ҫ����ʾԱ��������������н�ʡ�н�ʵȼ���
	
	select 
		e.ename,e.sal,d.dname,s.grade
	from
		emp e
	join
		dept d
	on 
		e.deptno = d.deptno
	join
		salgrade s
	on
		e.sal between s.losal and s.hisal;
	
	+--------+---------+------------+-------+
	| ename  | sal     | dname      | grade |
	+--------+---------+------------+-------+
	| SMITH  |  800.00 | RESEARCH   |     1 |
	| ALLEN  | 1600.00 | SALES      |     3 |
	| WARD   | 1250.00 | SALES      |     2 |
	| JONES  | 2975.00 | RESEARCH   |     4 |
	| MARTIN | 1250.00 | SALES      |     2 |
	| BLAKE  | 2850.00 | SALES      |     4 |
	| CLARK  | 2450.00 | ACCOUNTING |     4 |
	| SCOTT  | 3000.00 | RESEARCH   |     4 |
	| KING   | 5000.00 | ACCOUNTING |     5 |
	| TURNER | 1500.00 | SALES      |     3 |
	| ADAMS  | 1100.00 | RESEARCH   |     1 |
	| JAMES  |  950.00 | SALES      |     1 |
	| FORD   | 3000.00 | RESEARCH   |     4 |
	| MILLER | 1300.00 | ACCOUNTING |     2 |
	+--------+---------+------------+-------+

	�������ҳ�ÿ��Ա���Ĳ��������Լ����ʵȼ��������ϼ��쵼��
	Ҫ����ʾԱ�������쵼������������н�ʡ�н�ʵȼ���

	select 
		e.ename,e.sal,d.dname,s.grade,l.ename
	from
		emp e
	join
		dept d
	on 
		e.deptno = d.deptno
	join
		salgrade s
	on
		e.sal between s.losal and s.hisal
	left join
		emp l
	on
		e.mgr = l.empno;
	
	+--------+---------+------------+-------+-------+
	| ename  | sal     | dname      | grade | ename |
	+--------+---------+------------+-------+-------+
	| SMITH  |  800.00 | RESEARCH   |     1 | FORD  |
	| ALLEN  | 1600.00 | SALES      |     3 | BLAKE |
	| WARD   | 1250.00 | SALES      |     2 | BLAKE |
	| JONES  | 2975.00 | RESEARCH   |     4 | KING  |
	| MARTIN | 1250.00 | SALES      |     2 | BLAKE |
	| BLAKE  | 2850.00 | SALES      |     4 | KING  |
	| CLARK  | 2450.00 | ACCOUNTING |     4 | KING  |
	| SCOTT  | 3000.00 | RESEARCH   |     4 | JONES |
	| KING   | 5000.00 | ACCOUNTING |     5 | NULL  |
	| TURNER | 1500.00 | SALES      |     3 | BLAKE |
	| ADAMS  | 1100.00 | RESEARCH   |     1 | SCOTT |
	| JAMES  |  950.00 | SALES      |     1 | BLAKE |
	| FORD   | 3000.00 | RESEARCH   |     4 | JONES |
	| MILLER | 1300.00 | ACCOUNTING |     2 | CLARK |
	+--------+---------+------------+-------+-------+

3���Ӳ�ѯ��

3.1��ʲô���Ӳ�ѯ��
	select�����Ƕ��select��䣬��Ƕ�׵�select����Ϊ�Ӳ�ѯ��

3.2���Ӳ�ѯ�����Գ����������أ�
	select
		..(select).
	from
		..(select).
	where
		..(select).

3.3��where�Ӿ��е��Ӳ�ѯ

	�������ҳ�����͹��ʸߵ�Ա�������͹��ʣ�
		select 
			ename,sal
		from
			emp 
		where
			sal > min(sal);

		ERROR 1111 (HY000): Invalid use of group function
		where�Ӿ��в���ֱ��ʹ�÷��麯����
	
	ʵ��˼·��
		��һ������ѯ��͹����Ƕ���
			select min(sal) from emp;
			+----------+
			| min(sal) |
			+----------+
			|   800.00 |
			+----------+
		�ڶ������ҳ�>800��
			select ename,sal from emp where sal > 800;
		
		���������ϲ�
			select ename,sal from emp where sal > (select min(sal) from emp);
			+--------+---------+
			| ename  | sal     |
			+--------+---------+
			| ALLEN  | 1600.00 |
			| WARD   | 1250.00 |
			| JONES  | 2975.00 |
			| MARTIN | 1250.00 |
			| BLAKE  | 2850.00 |
			| CLARK  | 2450.00 |
			| SCOTT  | 3000.00 |
			| KING   | 5000.00 |
			| TURNER | 1500.00 |
			| ADAMS  | 1100.00 |
			| JAMES  |  950.00 |
			| FORD   | 3000.00 |
			| MILLER | 1300.00 |
			+--------+---------+

3.4��from�Ӿ��е��Ӳ�ѯ
	ע�⣺from������Ӳ�ѯ�����Խ��Ӳ�ѯ�Ĳ�ѯ�������һ����ʱ���������ɣ�

	�������ҳ�ÿ����λ��ƽ�����ʵ�н�ʵȼ���

	��һ�����ҳ�ÿ����λ��ƽ�����ʣ����ո�λ������ƽ��ֵ��
		select job,avg(sal) from emp group by job;
		+-----------+-------------+
		| job       | avgsal      |
		+-----------+-------------+
		| ANALYST   | 3000.000000 |
		| CLERK     | 1037.500000 |
		| MANAGER   | 2758.333333 |
		| PRESIDENT | 5000.000000 |
		| SALESMAN  | 1400.000000 |
		+-----------+-------------+t��

	�ڶ������˷������ϰ��������ϵĲ�ѯ����͵���һ����ʵ���ڵı�t��
	mysql> select * from salgrade; s��
	+-------+-------+-------+
	| GRADE | LOSAL | HISAL |
	+-------+-------+-------+
	|     1 |   700 |  1200 |
	|     2 |  1201 |  1400 |
	|     3 |  1401 |  2000 |
	|     4 |  2001 |  3000 |
	|     5 |  3001 |  9999 |
	+-------+-------+-------+
	t����s�����б����ӣ�������t��avg(sal) between s.losal and s.hisal;
		
		select 
			t.*, s.grade
		from
			(select job,avg(sal) as avgsal from emp group by job) t
		join
			salgrade s
		on
			t.avgsal between s.losal and s.hisal;
		
		+-----------+-------------+-------+
		| job       | avgsal      | grade |
		+-----------+-------------+-------+
		| CLERK     | 1037.500000 |     1 |
		| SALESMAN  | 1400.000000 |     2 |
		| ANALYST   | 3000.000000 |     4 |
		| MANAGER   | 2758.333333 |     4 |
		| PRESIDENT | 5000.000000 |     5 |
		+-----------+-------------+-------+

3.5��select������ֵ��Ӳ�ѯ��������ݲ���Ҫ���գ��˽⼴�ɣ�������

�������ҳ�ÿ��Ա���Ĳ������ƣ�Ҫ����ʾԱ��������������
	select 
		e.ename,e.deptno,(select d.dname from dept d where e.deptno = d.deptno) as dname 
	from 
		emp e;


	+--------+--------+------------+
	| ename  | deptno | dname      |
	+--------+--------+------------+
	| SMITH  |     20 | RESEARCH   |
	| ALLEN  |     30 | SALES      |
	| WARD   |     30 | SALES      |
	| JONES  |     20 | RESEARCH   |
	| MARTIN |     30 | SALES      |
	| BLAKE  |     30 | SALES      |
	| CLARK  |     10 | ACCOUNTING |
	| SCOTT  |     20 | RESEARCH   |
	| KING   |     10 | ACCOUNTING |
	| TURNER |     30 | SALES      |
	| ADAMS  |     20 | RESEARCH   |
	| JAMES  |     30 | SALES      |
	| FORD   |     20 | RESEARCH   |
	| MILLER |     10 | ACCOUNTING |
	+--------+--------+------------+

	//����ERROR 1242 (21000): Subquery returns more than 1 row
	select 
		e.ename,e.deptno,(select dname from dept) as dname
	from
		emp e;
	
	ע�⣺����select������Ӳ�ѯ��˵������Ӳ�ѯֻ��һ�η���1�������
	����1�����ͱ����ˡ���

4��union�ϲ���ѯ�����

��������ѯ������λ��MANAGER��SALESMAN��Ա����
	select ename,job from emp where job = 'MANAGER' or job = 'SALESMAN';
	select ename,job from emp where job in('MANAGER','SALESMAN');
	+--------+----------+
	| ename  | job      |
	+--------+----------+
	| ALLEN  | SALESMAN |
	| WARD   | SALESMAN |
	| JONES  | MANAGER  |
	| MARTIN | SALESMAN |
	| BLAKE  | MANAGER  |
	| CLARK  | MANAGER  |
	| TURNER | SALESMAN |
	+--------+----------+
	
	select ename,job from emp where job = 'MANAGER'
	union
	select ename,job from emp where job = 'SALESMAN';
	
	+--------+----------+
	| ename  | job      |
	+--------+----------+
	| JONES  | MANAGER  |
	| BLAKE  | MANAGER  |
	| CLARK  | MANAGER  |
	| ALLEN  | SALESMAN |
	| WARD   | SALESMAN |
	| MARTIN | SALESMAN |
	| TURNER | SALESMAN |
	+--------+----------+

	union��Ч��Ҫ��һЩ�����ڱ�������˵��ÿ����һ���±���
	��ƥ��Ĵ�������ѿ��������ɱ��ķ�������
	����union���Լ���ƥ��Ĵ������ڼ���ƥ�����������£�
	��������������������ƴ�ӡ�

	a ���� b ���� c
	a 10����¼
	b 10����¼
	c 10����¼
	ƥ������ǣ�1000

	a ���� bһ�������10 * 10 --> 100��
	a ���� cһ�������10 * 10 --> 100��
	ʹ��union�Ļ��ǣ�100�� + 100�� = 200�Ρ���union�ѳ˷�����˼ӷ����㣩

union��ʹ�õ�ʱ����ע��������

	//����ģ�union�ڽ��н�����ϲ���ʱ��Ҫ�������������������ͬ��
	select ename,job from emp where job = 'MANAGER'
	union
	select ename from emp where job = 'SALESMAN';

	// MYSQL���ԣ�oracle�﷨�ϸ� �������ԣ�������Ҫ�󣺽�����ϲ�ʱ�к��е���������ҲҪһ�¡�
	select ename,job from emp where job = 'MANAGER'
	union
	select ename,sal from emp where job = 'SALESMAN';
	+--------+---------+
	| ename  | job     |
	+--------+---------+
	| JONES  | MANAGER |
	| BLAKE  | MANAGER |
	| CLARK  | MANAGER |
	| ALLEN  | 1600    |
	| WARD   | 1250    |
	| MARTIN | 1250    |
	| TURNER | 1500    |
	+--------+---------+

5��limit���ǳ���Ҫ��
	
5.1��limit���ã�����ѯ�������һ����ȡ������ͨ��ʹ���ڷ�ҳ��ѯ���С�
�ٶ�Ĭ�ϣ�һҳ��ʾ10����¼��
��ҳ��������Ϊ������û������飬��Ϊһ��ȫ������������û�����
����һҳһҳ��ҳ����

5.2��limit��ô���أ�

	�����÷���limit startIndex, length
		startIndex����ʼ�±꣬length�ǳ��ȡ�
		��ʼ�±��0��ʼ��

	ȱʡ�÷���limit 5; ����ȡǰ5.

	����н�ʽ���ȡ��������ǰ5����Ա����
	select 
		ename,sal
	from
		emp
	order by 
		sal desc
	limit 5; //ȡǰ5

	select 
		ename,sal
	from
		emp
	order by 
		sal desc
	limit 0,5;

	+-------+---------+
	| ename | sal     |
	+-------+---------+
	| KING  | 5000.00 |
	| SCOTT | 3000.00 |
	| FORD  | 3000.00 |
	| JONES | 2975.00 |
	| BLAKE | 2850.00 |
	+-------+---------+

5.3��ע�⣺mysql����limit��order by֮��ִ�У�����������

5.4��ȡ������������[3-5]����Ա����
	select 
		ename,sal
	from
		emp
	order by
		sal desc
	limit
		2, 3;
	
	2��ʾ��ʼλ�ô��±�2��ʼ�����ǵ�������¼��
	3��ʾ���ȡ�

	+-------+---------+
	| ename | sal     |
	+-------+---------+
	| FORD  | 3000.00 |
	| JONES | 2975.00 |
	| BLAKE | 2850.00 |
	+-------+---------+

5.5��ȡ������������[5-9]����Ա����
	select 
		ename,sal
	from
		emp
	order by 
		sal desc
	limit
		4, 5;

	+--------+---------+
	| ename  | sal     |
	+--------+---------+
	| BLAKE  | 2850.00 |
	| CLARK  | 2450.00 |
	| ALLEN  | 1600.00 |
	| TURNER | 1500.00 |
	| MILLER | 1300.00 |
	+--------+---------+

5.6����ҳ

ÿҳ��ʾ3����¼
	��1ҳ��limit 0,3		[0 1 2]
	��2ҳ��limit 3,3		[3 4 5]
	��3ҳ��limit 6,3		[6 7 8]
	��4ҳ��limit 9,3		[9 10 11]

ÿҳ��ʾpageSize����¼
	��pageNoҳ��limit (pageNo - 1) * pageSize  , pageSize

	public static void main(String[] args){
		// �û��ύ����һ��ҳ�룬�Լ�ÿҳ��ʾ�ļ�¼����
		int pageNo = 5; //��5ҳ
		int pageSize = 10; //ÿҳ��ʾ10��

		int startIndex = (pageNo - 1) * pageSize;
		String sql = "select ...limit " + startIndex + ", " + pageSize;
	}

�ǹ�ʽ��
	limit (pageNo-1)*pageSize , pageSize

6������DQL���Ĵ��ܽ᣺
	select 
		...
	from
		...
	where
		...
	group by
		...
	having
		...
	order by
		...
	limit
		...
	
	ִ��˳��
		1.from
		2.where
		3.group by
		4.having
		5.select
		6.order by
		7.limit..

7�����Ĵ�����������

7.1���������﷨��ʽ��(��������DDL��䣬DDL������create drop alter)

	create table ����(�ֶ���1 ��������, �ֶ���2 ��������, �ֶ���3 ��������);

	create table ����(
		�ֶ���1 ��������, 
		�ֶ���2 ��������, 
		�ֶ���3 ��������
	);

	������������t_ ���� tbl_��ʼ���ɶ���ǿ������֪�⡣
	�ֶ���������֪�⡣
	�������ֶ��������ڱ�ʶ����

7.2������mysql�е��������ͣ�

	�ܶ��������ͣ�����ֻ��Ҫ����һЩ�������������ͼ��ɡ�

		varchar(�255)
			�ɱ䳤�ȵ��ַ���
			�Ƚ����ܣ���ʡ�ռ䡣
			�����ʵ�ʵ����ݳ��ȶ�̬����ռ䡣

			�ŵ㣺��ʡ�ռ�
			ȱ�㣺��Ҫ��̬����ռ䣬�ٶ�����

		char(�255)
			�����ַ���
			����ʵ�ʵ����ݳ����Ƕ��١�
			����̶����ȵĿռ�ȥ�洢���ݡ�
			ʹ�ò�ǡ����ʱ�򣬿��ܻᵼ�¿ռ���˷ѡ�

			�ŵ㣺����Ҫ��̬����ռ䣬�ٶȿ졣
			ȱ�㣺ʹ�ò������ܻᵼ�¿ռ���˷ѡ�

			varchar��char����Ӧ����ôѡ��
				�Ա��ֶ���ѡʲô����Ϊ�Ա��ǹ̶����ȵ��ַ���������ѡ��char��
				�����ֶ���ѡʲô��ÿһ���˵����ֳ��Ȳ�ͬ������ѡ��varchar��

		int(�11)
			�����е������͡���ͬ��java��int��

		bigint
			�����еĳ����͡���ͬ��java�е�long��

		float	
			�����ȸ���������

		double
			˫���ȸ���������

		date
			����������

		datetime
			����������

		clob
			�ַ������
			�����Դ洢4G���ַ�����
			���磺�洢һƪ���£��洢һ��˵����
			����255���ַ��Ķ�Ҫ����CLOB�ַ���������洢��
			Character Large OBject:CLOB


		blob
			�����ƴ����
			Binary Large OBject
			ר�������洢ͼƬ����������Ƶ����ý�����ݡ�
			��BLOB���͵��ֶ��ϲ������ݵ�ʱ���������һ��ͼƬ����Ƶ�ȣ�
			����Ҫʹ��IO�����С�
	
	t_movie ��Ӱ����ר�Ŵ洢��Ӱ��Ϣ�ģ�

	���			����				�������					��ӳ����				ʱ��				����					����
	no(bigint)	name(varchar)	history(clob)		playtime(date)		time(double)	image(blob)			type(char)
	------------------------------------------------------------------------------------------------------------------
	10000			��߸				...........			2019-10-11			2.5				....					'1'
	10001			����Ӣ֮����   ...........			2019-11-11			1.5				....					'2'
	....

7.3������һ��ѧ������
	ѧ�š����������䡢�Ա������ַ
	create table t_student(
		no int,
		name varchar(32),
		sex char(1),
		age int(3),
		email varchar(255)
	);

	ɾ������
		drop table t_student; // �����ű������ڵ�ʱ��ᱨ����

		// ������ű����ڵĻ���ɾ��
		drop table if exists t_student;
	
7.4����������insert ��DML��
	
	�﷨��ʽ��
		insert into ����(�ֶ���1,�ֶ���2,�ֶ���3...) values(ֵ1,ֵ2,ֵ3);

		ע�⣺�ֶ�����ֵҪһһ��Ӧ��ʲô��һһ��Ӧ��
			����Ҫ��Ӧ����������Ҫ��Ӧ��
	
	insert into t_student(no,name,sex,age,email) values(1,'zhangsan','m',20,'zhangsan@123.com');
	insert into t_student(email,name,sex,age,no) values('lisi@123.com','lisi','f',20,2);

	insert into t_student(no) values(3);

	+------+----------+------+------+------------------+
	| no   | name     | sex  | age  | email            |
	+------+----------+------+------+------------------+
	|    1 | zhangsan | m    |   20 | zhangsan@123.com |
	|    2 | lisi     | f    |   20 | lisi@123.com     |
	|    3 | NULL     | NULL | NULL | NULL             |
	+------+----------+------+------+------------------+
	insert into t_student(name) values('wangwu');
	+------+----------+------+------+------------------+
	| no   | name     | sex  | age  | email            |
	+------+----------+------+------+------------------+
	|    1 | zhangsan | m    |   20 | zhangsan@123.com |
	|    2 | lisi     | f    |   20 | lisi@123.com     |
	|    3 | NULL     | NULL | NULL | NULL             |
	| NULL | wangwu   | NULL | NULL | NULL             |
	+------+----------+------+------+------------------+
	ע�⣺insert��䵫����ִ�гɹ��ˣ���ô��Ȼ���һ����¼��
	û�и������ֶ�ָ��ֵ�Ļ���Ĭ��ֵ��NULL��
	
	drop table if exists t_student;
	create table t_student(
		no int,
		name varchar(32),
		sex char(1) default 'm',
		age int(3),
		email varchar(255)
	);

	+-------+--------------+------+-----+---------+-------+
	| Field | Type         | Null | Key | Default | Extra |
	+-------+--------------+------+-----+---------+-------+
	| no    | int(11)      | YES  |     | NULL    |       |
	| name  | varchar(32)  | YES  |     | NULL    |       |
	| sex   | char(1)      | YES  |     | m       |       |
	| age   | int(3)       | YES  |     | NULL    |       |
	| email | varchar(255) | YES  |     | NULL    |       |
	+-------+--------------+------+-----+---------+-------+
	insert into t_student(no) values(1);
	mysql> select * from t_student;
	+------+------+------+------+-------+
	| no   | name | sex  | age  | email |
	+------+------+------+------+-------+
	|    1 | NULL | m    | NULL | NULL  |
	+------+------+------+------+-------+
	
	insert����еġ��ֶ���������ʡ���𣿿���
		insert into t_student values(2); //�����

		// ע�⣺ǰ����ֶ���ʡ�ԵĻ������ڶ�д���ˣ�����ֵҲҪ��д�ϣ�
		insert into t_student values(2, 'lisi', 'f', 20, 'lisi@123.com');
		+------+------+------+------+--------------+
		| no   | name | sex  | age  | email        |
		+------+------+------+------+--------------+
		|    1 | NULL | m    | NULL | NULL         |
		|    2 | lisi | f    |   20 | lisi@123.com |
		+------+------+------+------+--------------+

7.5��insert��������

	���ָ�ʽ����format
		select ename,sal from emp;
		+--------+---------+
		| ename  | sal     |
		+--------+---------+
		| SMITH  |  800.00 |
		| ALLEN  | 1600.00 |
		| WARD   | 1250.00 |
		| JONES  | 2975.00 |
		| MARTIN | 1250.00 |
		| BLAKE  | 2850.00 |
		| CLARK  | 2450.00 |
		| SCOTT  | 3000.00 |
		| KING   | 5000.00 |
		| TURNER | 1500.00 |
		| ADAMS  | 1100.00 |
		| JAMES  |  950.00 |
		| FORD   | 3000.00 |
		| MILLER | 1300.00 |
		+--------+---------+

		��ʽ�����֣�format(����, '��ʽ')
			select ename,format(sal, '$999,999') as sal from emp;
			+--------+-------+
			| ename  | sal   |
			+--------+-------+
			| SMITH  | 800   |
			| ALLEN  | 1,600 |
			| WARD   | 1,250 |
			| JONES  | 2,975 |
			| MARTIN | 1,250 |
			| BLAKE  | 2,850 |
			| CLARK  | 2,450 |
			| SCOTT  | 3,000 |
			| KING   | 5,000 |
			| TURNER | 1,500 |
			| ADAMS  | 1,100 |
			| JAMES  | 950   |
			| FORD   | 3,000 |
			| MILLER | 1,300 |
			+--------+-------+

	str_to_date�����ַ���varchar����ת����date����
	date_format����date����ת���ɾ���һ����ʽ��varchar�ַ������͡�

	drop table if exists t_user;
	create table t_user(
		id int,
		name varchar(32),
		birth date // ����Ҳ����ʹ��date��������
	);

	create table t_user(
		id int,
		name varchar(32),
		birth char(10) // ���տ���ʹ���ַ�����û���⡣
	);

	���գ�1990-10-11 ��10���ַ���

	ע�⣺���ݿ��е���һ�������淶��
		���еı�ʶ������ȫ��Сд�����ʺ͵���֮��ʹ���»��߽����νӡ�

	mysql> desc t_user;
	+-------+-------------+------+-----+---------+-------+
	| Field | Type        | Null | Key | Default | Extra |
	+-------+-------------+------+-----+---------+-------+
	| id    | int(11)     | YES  |     | NULL    |       |
	| name  | varchar(32) | YES  |     | NULL    |       |
	| birth | date        | YES  |     | NULL    |       |
	+-------+-------------+------+-----+---------+-------+

	�������ݣ�
		insert into t_user(id,name,birth) values(1, 'zhangsan', '01-10-1990'); // 1990��10��1��
		�������ˣ�ԭ�������Ͳ�ƥ�䡣���ݿ�birth��date���ͣ��������һ���ַ���varchar��

		��ô�죿����ʹ��str_to_date������������ת����
		str_to_date�������Խ��ַ���ת������������date��
		�﷨��ʽ��
			str_to_date('�ַ�������', '���ڸ�ʽ')

		mysql�����ڸ�ʽ��
			%Y	��
			%m ��
			%d ��
			%h	ʱ
			%i	��
			%s	��
		
		insert into t_user(id,name,birth) values(1, 'zhangsan', str_to_date('01-10-1990','%d-%m-%Y'));

		str_to_date�������԰��ַ���varcharת��������date�������ݣ�
		ͨ��ʹ���ڲ���insert���棬��Ϊ�����ʱ����Ҫһ���������͵����ݣ�
		��Ҫͨ���ú������ַ���ת����date��

	����Ϣ��
		������ṩ�������ַ����������ʽ��str_to_date�����Ͳ���Ҫ�ˣ�����
			%Y-%m-%d
		insert into t_user(id,name,birth) values(2, 'lisi', '1990-10-01');
	
	��ѯ��ʱ�������ĳ���ض������ڸ�ʽչʾ��
		date_format
		����������Խ���������ת�����ض���ʽ���ַ�����

		select id,name,date_format(birth, '%m/%d/%Y') as birth from t_user;
		+------+----------+------------+
		| id   | name     | birth      |
		+------+----------+------------+
		|    1 | zhangsan | 10/01/1990 |
		|    2 | lisi     | 10/01/1990 |
		+------+----------+------------+

		date_format������ô�ã�
			date_format(������������, '���ڸ�ʽ')
			�������ͨ��ʹ���ڲ�ѯ���ڷ��档����չʾ�����ڸ�ʽ��
		
		mysql> select id,name,birth from t_user;
		+------+----------+------------+
		| id   | name     | birth      |
		+------+----------+------------+
		|    1 | zhangsan | 1990-10-01 |
		|    2 | lisi     | 1990-10-01 |
		+------+----------+------------+
		���ϵ�SQL���ʵ�����ǽ�����Ĭ�ϵ����ڸ�ʽ����
		�Զ������ݿ��е�date����ת����varchar���͡�
		���Ҳ��õĸ�ʽ��mysqlĬ�ϵ����ڸ�ʽ��'%Y-%m-%d'

		select id,name,date_format(birth,'%Y/%m/%d') as birth from t_user;
		
		java�е����ڸ�ʽ��
			yyyy-MM-dd HH:mm:ss SSS

7.6��date��datetime�������͵�����
	date�Ƕ����ڣ�ֻ������������Ϣ��
	datetime�ǳ����ڣ�����������ʱ������Ϣ��

	drop table if exists t_user;
	create table t_user(
		id int,
		name varchar(32),
		birth date,
		create_time datetime
	);


	id������
	name���ַ���
	birth�Ƕ�����
	create_time��������¼�Ĵ���ʱ�䣺����������

	mysql������Ĭ�ϸ�ʽ��%Y-%m-%d
	mysql������Ĭ�ϸ�ʽ��%Y-%m-%d %h:%i:%s

	insert into t_user(id,name,birth,create_time) values(1,'zhangsan','1990-10-01','2020-03-18 15:49:50');

	��mysql������ô��ȡϵͳ��ǰʱ�䣿
		now() ���������һ�ȡ��ʱ����У�ʱ������Ϣ����������datetime���͵ġ�
	
		insert into t_user(id,name,birth,create_time) values(2,'lisi','1991-10-01',now());

7.7���޸�update��DML��

�﷨��ʽ��
	update ���� set �ֶ���1=ֵ1,�ֶ���2=ֵ2,�ֶ���3=ֵ3... where ����;

	ע�⣺û���������ƻᵼ����������ȫ�����¡�

	update t_user set name = 'jack', birth = '2000-10-11' where id = 2;
	+------+----------+------------+---------------------+
	| id   | name     | birth      | create_time         |
	+------+----------+------------+---------------------+
	|    1 | zhangsan | 1990-10-01 | 2020-03-18 15:49:50 |
	|    2 | jack     | 2000-10-11 | 2020-03-18 15:51:23 |
	+------+----------+------------+---------------------+

	update t_user set name = 'jack', birth = '2000-10-11', create_time = now() where id = 2;

	�������У�
		update t_user set name = 'abc';

7.8��ɾ������ delete ��DML��
	�﷨��ʽ��
		delete from ���� where ����;

	ע�⣺û�����������ű������ݻ�ȫ��ɾ����

	delete from t_user where id = 2;

	insert into t_user(id) values(2);

	delete from t_user; // ɾ�����У�
