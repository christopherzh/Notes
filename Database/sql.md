# 数据库

## 使用Mysql

### 连接数据库

需要下列信息：

* 主机名
* 用户名
* 用户口令（如果需要）

### 选择数据库

```sql
USE database1; #选择特定数据库进行操作
```

### 了解数据库与表

```sql
SHOW DATABASES; #显示所有数据库
SHOW TABLE; #显示数据库中所有表
SHOW STATUS;  #显示服务器状态信息
SHOW CREATE DATABASE; #显示创建特定数据库的MySQL语句
SHOW CREATE TABLE; #显示创建特定表的MySQL语句
SHOW GRANTS; #显示授予用户的安全权限
SHOW ERRORS; #显示服务器错误
SHOW WARNINGS; #显示服务器警告信息
```

## 创建数据库/模式

```sql
CREATE SCHEMA schema1; #创建模式
CREATE DATABASE database1; #创建数据库
#注：在mysql中，两者含义相等
DROP SCHEMA schema1;
```

## 创建表和修改表

### 创建表

基础语法
```sql
CREATE TABLE table1; #基本语句

#通过拷贝另一个表的结构及数据来创建表：
CREATE TABLE 新表
AS
SELECT * FROM 旧表
```

#### 数据类型

**数值类型**

**字符类型**

**日期和时间类型**

### 更新表（ALTER）

```sql
#为表添加一列，其中table1必须存在
ALTER TABLE table1
ADD column1 char(2) [UNIQUE]; #UNIQUE代指完整性约束，可有可无

#更新属性的数据类型
ALTER TABLE table1
MODIFY(ALTER) COLUMN column1 varchar(5);
#删除列
ALTER TABLE table1
DROP COLUMN column1;
```

### 删除表

```sql
DROP TABLE table1;
TRUNCATE TABLE table1; #仅删除表内数据，不删除表
```

### 重命名表

```sql
RENAME TABLE table1 TO renamed_table1;
```

### 完整性约束

#### 更新约束

**主键约束**

```sql
ALTER TABLE table1 
ADD CONSTRAINT pk_1   PRIMARY KEY(id);
```

**CHECK约束**

```sql
ALTER TABLE table1 
ADD CONSTRAINT c_1   CHECK(id>0 AND id<10);
```

**UNIQUE约束**

```sql
ALTER TABLE table1 
ADD CONSTRAINT uni_1  UNIQUE(id);
```

**DEFAULT约束**

```sql
ALTER TABLE table1 
ADD CONSTRAINT de_1   DEFAULT 10 FOR id;
#格式：alter table 表名称 add constraint 约束别名 约束类型 默认 for 列名
```

**外键约束**

```sql
ALTER TABLE table1 
ADD CONSTRAINT fk_1   
FOREIGN KEY(id) REFERENCES fr_table1(fr_id); 
#格式: alter table 表名 add constraint 约束别名 约束类型(列名)references 引用的表名称(列名)
```

**非空约束**

```sql
ALTER TABLE TABLE_NAME
ALTER COLUMN COLUMN_NAME  TYPE_OF_  NOT NULL;
```

#### 删除约束

```sql
ALTER TABLE table1
DROP FOREIGN KEY fk_1; ##FOREIGN KEY约束类型，fk_1为完整性约束名
```

### 索引

```sql
#建立索引
CREATE [UNIQUE] [CLUSTER] INDEX <索引名> 
ON <表名>(<列名>[DESC|ASC],...); 

#删除索引
DROP INDEX <索引名>; 
```

## 插入、更新与删除数据（INSERT,UPDATE,DELETE）

### INSERT语句

**基本语法**
```sql
INSERT INTO 表名称 VALUES (值1, 值2,....)
INSERT INTO 表名称 (列1, 列2,...) VALUES (值1, 值2,....)
```

**实例**
```sql
INSERT INTO table1 VALUES ('data1','data2');
INSERT INTO table1 (column1,column2) VALUES ('data1','data2');
```

#### 插入子查询结果

只能为已经存在的表批量添加新数据，不复制表结构

```sql
INSERT INTO <表名>  [(<属性列1> [,<属性列2>…  )] 子查询;

#如果两个表结构一样：
INSERT INTO table_name_new SELECT * FROM table_name_old

#如果两个表结构不一样：
INSERT INTO table_name_new(column1,column2...) 
SELECT column1,column2... FROM table_name_old
```

### UPDATE语句
**基本语法**
```sql
UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值;
```
**实例**
```sql
UPDATE S SET Sname='王强' WHERE Sno='201215124'; 
```

### DELETE语句
**基本语法**
```sql
DELETE FROM 表名称 WHERE 列名称 = 值

#删除所有行，表的结构、属性和索引都是完整的
DELETE FROM table1
DELETE * FROM table1
```
**实例**
```sql
DELETE FROM table1 WHERE column1 = 'data1'; 
```

## 检索数据（SELECT）

### 基本语句

```sql
SELECT column1,column2 FROM table1; #检索table1中选定的列
SELECT * FROM table1; #检索table1中所有列
SELECT DISTINCT id FROM table1； #检索id列中不同的行

#本科教材上的语法格式
SELECT [ALL|DISTINCT] <目标列表达式> [，<目标列表达式>,...]
FROM <表名或视图名>[，<表名或视图名>,...]
[WHERE <条件表达式>]
[GROUP BY <列名1> [HAVING <条件表达式>]]
[ORDER BY <列名2> [ASC|DESC]];
```

### 规定返回的记录数目

#### LIMIT子句

```sql
#从行0开始
SELECT column1 FROM table1 LIMIT 5; #检索单个列，LIMIT 5指示返回结果不多于5行
SELECT column1 FROM table1 LIMIT 4,5; #返回结果为从行4开始的5行，即4到9行，第一个数为开始位置，第二个数为检索行数
SELECT column1 FROM table1 LIMIT 5 OFFSET 4; #与上一条含义相同，仅是不同的写法
```

#### TOP子句

mysql中不支持该语法，应使用上述的LIMIT子句。

```sql
SELECT TOP 2 * FROM table1; # 返回前两条记录
SELECT TOP 50 PERCENT * FROM table1; # 返回前50%的记录
```

### WHERE子句
**基础语法**
```sql
SELECT 列名称 FROM 表名称 WHERE 列 操作符 值
```
**实例**
```sql
SELECT * FROM table1 WHERE column1='data1'; 
```

#### 操作符

| 操作符 | 含义 |
| :--- | :--- |
| = | 等于 |
| <>>    或 != | 不等于 |
| >| 大于 |
| <> | 小于 |
| >= | 大于等于 |
| <= | 小于等于 |
| AND | 与 |
| OR | 或 |
| NOT | 非 |
| BETWEEN value1 AND value2 | 在两值之间 |
| IN (value1,value2,...) | 规定多个值 |
| IS NULL 或IS NOT NULL | 对空值的查询 |

#### LIKE与通配符

LIKE 操作符用于在 WHERE 子句中搜索列中的指定模式，还可使用NOT LIKE来寻找不符合模式的记录

```sql
#基本语法
SELECT column_name(s) FROM table_name 
WHERE column_name LIKE pattern

#实例
SELECT * FROM Persons WHERE City LIKE 'N%'
 #从"Persons" 表中选取居住在以 "N" 开始的城市里的人
```

在搜索数据库中的数据时，SQL 通配符可以替代一个或多个字符。

| 通配符 | 描述 |
| :--- | :--- |
| % | 替代一个或多个字符 |
| \_ | 仅替代一个字符 |
| \[charlist\] | 字符列中的任何单一字符 |
| 或\[!charlist\] | 不在字符列中 |

### 排序检索数据（ORDER BY）

* 可以按一个或多个属性列排序
* 升序：ASC；降序：DESC；缺省值为升序

当排序列含空值时:

* ASC：排序列为空值的元组最后显示
* DESC：排序列为空值的元组最先显示
```sql
#实例
SELECT Company, OrderNumber FROM Orders 
ORDER BY Company DESC, OrderNumber ASC
```

### 数据分组与聚合函数（GROUP BY）
GROUP BY 语句用于结合聚集函数，根据一个或多个列对结果集进行分组。

**基本语法**
```sql
SELECT column_name, aggregate_function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name
```
**实例**
```sql
#对多个列进行分组
SELECT Customer,OrderDate,SUM(OrderPrice) FROM Orders
GROUP BY Customer,OrderDate
```

#### HAVING子句

在SQL中增加HAVING子句原因是，WHERE关键字无法与合计函数一起使用。
**基本语法**
```sql
SELECT column_name, aggregate_function(column_name)
FROM table_name
WHERE column_name operator value
GROUP BY column_name
HAVING aggregate_function(column_name) operator value
```
**实例**
```sql
SELECT Customer,SUM(OrderPrice) FROM Orders
WHERE Customer='Bush' OR Customer='Adams'
GROUP BY Customer
HAVING SUM(OrderPrice)>1500
```

### 联接表（JOIN）
JOIN用于根据两个或多个表中的列之间的关系，从这些表中查询数据。

下面列出了您可以使用的 JOIN 类型，以及它们之间的差异。
- JOIN(INNER JOIN): 如果表中有至少一个匹配，则返回行
- LEFT JOIN: 即使右表中没有匹配，也从左表返回所有的行
- RIGHT JOIN: 即使左表中没有匹配，也从右表返回所有的行
- FULL JOIN: 只要其中一个表中存在匹配，就返回行
```sql
SELECT column_name(s)
FROM table_name1
INNER|LEFT|RIGHT|FULL JOIN table_name2 
ON table_name1.column_name=table_name2.column_name
```

### 嵌套查询

子查询的限制：不能使用ORDER BY子句 
1. 不相关子查询

* 子查询的查询条件不依赖于父查询
* 由里向外.逐层处理。即每个子查询在上一级查询处理之前求解，子查询的结果用于建立其父查询的查找条件
2. 相关子查询
* 子查询的查询条件依赖于父查询
* 首先取外层查询中表的第一个元组，根据它与内层查询相关的属性值处理内层查询，若WHERE子句返回值为真，则取此元组放入结果表
* 然后再取外层表的下一个元组
* 重复这一过程，直至外层表全部检查完为止

#### IN谓词

```sql
#实例，使用文末数据库
#查询选修课程名为数据结构的学生学号与年龄
SELECT sc.sno,sage FROM sc LEFT JOIN s ON sc.sno=s.sno  
WHERE cno IN (SELECT cno FROM c WHERE cname='数据结构');
```

#### 比较运算符

* 当能确切知道内层查询返回单值时，可用比较运算符（>，<，=，>=，<=，!=或<>）。
* 与ANY或ALL谓词配合使用
  
```sql
#在上一个实例中，因为子查询只会返回一个结果，所以可使用=运算符进行匹配
SELECT sc.sno,sage FROM sc LEFT JOIN s ON sc.sno=s.sno  
WHERE cno = (SELECT cno FROM c WHERE cname='数据结构');

## 另一个实例：找出每个学生超过他选修课程平均成绩的课程号
SELECT Sno,Cno FROM SC x WHERE Grade = SELECT AVG(Grade) FROM SC y WHERE y.Sno=x.Sno);#此查询为相关子查询，因为y.Sno=x.Sno
```

### ANY(SOME)或ALL谓词
- ANY：任意一个值
- ALL：所有值

需要配合使用比较运算符

|运算符组合|含义|
|--|--|
|> ANY    |大于子查询结果中的某个值 |      
|> ALL    |大于子查询结果中的所有值|
|< ANY    |小于子查询结果中的某个值  |  
|< ALL    |小于子查询结果中的所有值|
|>= ANY    |大于等于子查询结果中的某个值 |   
|>= ALL    |大于等于子查询结果中的所有值|
|<= ANY    |小于等于子查询结果中的某个值 |   
|<= ALL    |小于等于子查询结果中的所有值|
|= ANY    |等于子查询结果中的某个值   |     
|=ALL    |等于子查询结果中的所有值（通常没有实际意义）|
|!=（或<>）ANY    |不等于子查询结果中的某个值|
|!=（或<>）ALL    |不等于子查询结果中的任何一个值|

注：以上操作符均可使用聚集函数MAX()与MIN()配合基本操作符来实现

### EXISTS谓词
1. EXISTS谓词
- 带有EXISTS谓词的子查询不返回任何数据，只产生逻辑真值“true”或逻辑假值“false”
- 若内层查询结果非空，则外层的WHERE子句返回真值
- 若内层查询结果为空，则外层的WHERE子句返回假值
- 由EXISTS引出的子查询，其目标列表达式通常都用* ，因为带EXISTS的子查询只返回真值或假值，给出列名无实际意义
2. NOT EXISTS谓词
- 若内层查询结果非空，则外层的WHERE子句返回假值
- 若内层查询结果为空，则外层的WHERE子句返回真值

```sql
#使用文末数据库

#查询学习全部课程学生姓名，即所要查询的学生，不存在一门课程他没有选修。
#即该学生没有一门课程是他不选修的，就是说，该学生选修了所有课程。
SELECT sname FROM s WHERE NOT EXISTS 
(SELECT  * FROM c WHERE NOT EXISTS 
(SELECT * FROM sc WHERE sc.sno=s.sno AND c.cno=sc.cno ) );

#查询不选 3 号课程的学生学号与姓名
SELECT  sno,sname FROM  s 
WHERE NOT EXISTS(SELECT * FROM  sc WHERE s.sno=sc.sno AND cno='3');
```

### 组合查询（UNION）

UNION 操作符用于合并两个或多个 SELECT 语句的结果集。

请注意，UNION 内部的 SELECT 语句必须拥有相同数量的列。列也必须拥有相似的数据类型。同时，每条 SELECT 语句中的列的顺序必须相同。
**基本语法**
```sql
SELECT column_name(s) FROM table_name1
UNION
SELECT column_name(s) FROM table_name2
#注释：默认地，UNION 操作符选取不同的值。如果允许重复的值，请使用 UNION ALL。
SELECT column_name(s) FROM table_name1
UNION ALL
SELECT column_name(s) FROM table_name2
```
**实例**
```sql
SELECT Sno FROM sc WHERE Cno='1'
UNION 
SELECT Sno FROM sc WHERE Cno='2'
```

## 函数

## 视图（VIEW）

### 创建视图
**基本语法**
```sql
CREATE  VIEW <视图名>  [(<列名>  [，<列名>]…)]
AS  <子查询>
[WITH  CHECK  OPTION]；
```

* 组成视图的属性列名：全部省略或全部指定
* 子查询不允许含有ORDER BY子句和DISTINCT短语
* 视图总是显示最近的数据。每当用户查询视图时，数据库引擎通过使用 SQL 语句来重建数据
* 数据库的设计和结构不会受到视图中的函数、where 或 join 语句的影响

**实例**
```sql
#使用文末数据库

#建立男学生的视图,属性包括学号、姓名、选修课程名和成绩
CREATE VIEW boy (bno,bname,cname,grade) AS 
SELECT s.sno,s.sname,c.cname,sc.Grade
FROM s,c,sc
WHERE s.sno=sc.sno AND c.cno=sc.cno AND ssex='男';
```

### 删除视图

```sql
DROP VIEW view_name;
```

## 触发器
### 定义触发器
**基本语法**
```sql
CREATE TRIGGER <触发器名>  
{BEFORE|AFTER} <触发事件> ON <表名>
FOR EACH {ROW|STATEMENT}
[WHEN <触发条件>]
<触发动作体>
```
**实例**
```sql
#使用文末数据库

#更新一个学生的学号信息时能够级联更新此学生在SC表中的选课记录的学号信息
CREATE TRIGGER update_sno1 
AFTER UPDATE ON S
FOR EACH ROW
UPDATE  sc SET  sc.sno=new.sno 
WHERE sc.sno=old.sno;

#每个班的学生不能超过 30 个，如果低于此数，添加可以完成；如果超过此数，则插入将不能实现。
CREATE TRIGGER insert_stu
AFTER INSERT ON S
FOR EACH ROW
BEGIN
	DECLARE stuno INT;
    SELECT COUNT(*) INTO stuno FROM s;
    IF stuno > 30 THEN
		SIGNAL SQLSTATE 'HY000' SET MESSAGE_TEXT = 'Throw Exceptions: Table Full';
	END IF;
END 

#当修改 SC 表中的 Grade 字段时将其修改前后的信息保存在 SC_log 表中
CREATE TABLE sc_log(
    pre_grade int CHECK(pre_grade BETWEEN 0 AND 100),
    now_grade int CHECK(now_grade BETWEEN 0 AND 100)
);
CREATE TRIGGER update_grade
AFTER UPDATE ON  sc
FOR EACH ROW 
BEGIN
	INSERT INTO SC_log VALUES (OLD.Grade, NEW.Grade);
END
```
语法说明：
1. 创建者：表的拥有者
2. 触发器名
3. 表名：触发器的目标表
4. 触发事件：INSERT、DELETE、UPDATE
5. 触发器类型
   1. 行级触发器（FOR EACH ROW）
      - 一条SQL语句影响的每一行触发一次。
      - 如果需要对每一行数据做处理，使用行级触发器

   2. 语句级触发器（FOR EACH STATEMENT）
      - 一条SQL语句触发一次
      - 语句执行完成后，做该语句的后续业务处理，用语句级触发器。



### 激活触发器
- 触发器的执行，是由触发事件激活的，并由数据库服务器自动执行
- 一个数据表上可能定义了多个触发器，同一个表上的多个触发器激活时遵循如下的执行顺序：
   1. 执行该表上的BEFORE触发器；
   2. 激活触发器的SQL语句；
   3. 执行该表上的AFTER触发器。
- 语句级触发器在行级触发器之后触发（AFTER的时候），如果用BEFORE触发，则语句级触发器先执行。

### 删除触发器
```sql
DROP TRIGGER <触发器名> ON <表名>;

#实例，删除教师表Teacher上的触发器Insert_Sal
DROP TRIGGER Insert_Sal ON Teacher;
```
## 数据库安全性

## 数据库实例

### S表

```text
+-----------+-----------+------+------+-------+
| Sno       | Sname     | Ssex | Sage | Sdept |
+-----------+-----------+------+------+-------+
| 201215120 | 李爽      | 男   |   20 | CS    |
| 201215121 | 李莉      | 男   |   20 | CS    |
| 201215122 | 刘星      | 女   |   19 | CS    |
| 201215123 | 王浩然    | 女   |   18 | MA    |
| 201215124 | 王强      | 男   |   22 | CS    |
| 201215125 | 张立      | 男   |   19 | IS    |
+-----------+-----------+------+------+-------+
```

### C表

```text
+-----+--------------+---------+
| Cno | Cname        | Ccredit |
+-----+--------------+---------+
| 1   | 数据库       |       4 |
| 2   | 数学         |       2 |
| 3   | 信息系统     |       4 |
| 4   | 操作系统     |       3 |
| 5   | 数据结构     |       4 |
| 6   | 数据处理     |       2 |
| 7   | C语言        |       4 |
+-----+--------------+---------+
```

### SC表

```text
+-----------+------+-------+
| Sno       | Cno  | Grade |
+-----------+------+-------+
| 201215122 | 3    |    80 |
| 201215122 | 2    |    90 |
| 201215121 | 3    |    88 |
| 201215121 | 1    |    91 |
| 201215121 | 2    |    85 |
| 201215121 | 5    |    94 |
| 201215123 | 3    |    88 |
| 201215123 | 1    |    92 |
| 201215123 | 7    |   100 |
| 201215125 | 1    |    92 |
| 201215125 | 6    |    77 |
| 201215125 | 2    |    79 |
| 201215125 | 4    |    72 |
| 201215125 | 3    |    99 |
| 201215125 | 5    |    58 |
| 201215125 | 7    |    81 |
| 201215124 | 1    |    55 |
| 201215124 | 3    |    81 |
| 201215124 | 6    |    89 |
| 201215124 | 2    |    75 |
| 201215124 | 4    |    81 |
| 201215123 | 4    |    89 |
| 201215120 | 1    |    88 |
+-----------+------+-------+
```

