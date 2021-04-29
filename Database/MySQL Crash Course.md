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
### 实例
```sql

```
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
```
## 重命名表
```sql
RENAME TABLE table1 TO renamed_table1;
```

# 插入、更新与删除数据

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