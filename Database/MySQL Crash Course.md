
# 使用Mysql
## 连接数据库
需要下列信息：
* 主机名
* 用户名
* 用户口令（如果需要）
## 选择数据库
```sql
USE database1; #选择特定数据库进行操作
```
## 了解数据库与表
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
# 创建表和操纵表

## 创建表
### 基础语法
```sql
CREATE TABLE table1;
```
### 数据类型

#### 数值类型
| 标识符 | 含义 |
| - | -|

#### 字符类型
#### 日期和时间类型

## 更新表
```sql
#为表添加一列，其中table1必须存在
ALTER TABLE table1
ADD column1 char(2);
#删除列
ALTER TABLE table1
DROP COLUMN column1;
```
## 删除表
```sql
DROP TABLE table1;
TRUNCATE TABLE table1; #仅删除表内数据，不删除表
```
## 重命名表
```sql
RENAME TABLE table1 TO renamed_table1;
```

# 插入、更新与删除数据
## INSERT语句
```sql
INSERT INTO table1 VALUES ('data1','data2');
INSERT INTO table1 (column1,column2) VALUES ('data1','data2');
```

## UPDATE语句
```sql
UPDATE 表名称 SET 列名称 = 新值 WHERE 列名称 = 某值;
UPDATE S SET Sname='王强' WHERE Sno='201215124'; #实例
```
# 检索数据 
## SELECT语句
```sql
SELECT column1,column2 FROM table1; #检索table1中选定的列
SELECT * FROM table1; #检索table1中所有列
SELECT DISTINCT id FROM table1； #检索id列中不同的行
SELECT column1 FROM table1 LIMIT 5; #检索单个列，LIMIT 5指示返回结果不多于5行
SELECT column1 FROM table1 LIMIT 4,5; #返回结果为从行4开始的5行，即4到9行，第一个数为开始位置，第二个数为检索行数
SELECT column1 FROM table1 LIMIT 5 OFFSET 4; #与上一条含义相同，仅是不同的写法
```
## 排序检索数据



# 视图

# 触发器    

# 数据库实例
## S表
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

## C表
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
## SC表
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