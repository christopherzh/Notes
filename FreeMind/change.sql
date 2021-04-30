/*
1.	把 1 号课程的非空成绩提高 5%。
2.	在 SC 表中删除课程名为数据结构的成绩的元组。
3.	在 S 和 SC 表中删除学号为 201215122 的所有数据。
4.	建立男学生的视图,属性包括学号、姓名、选修课程名和成绩。
5.	在男学生视图中查询平均成绩大于 80 分的学生学号与姓名。
6.	计算每个学生有成绩的课程门数、平均成绩。
7.	使用 GRANT 语句,把对基本表 S、SC、C 的使用权限授给其它用户。
*/


#1
UPDATE sc SET grade=grade+0.05*grade WHERE cno='1' AND grade IS NOT NULL; 
#2
DELETE FROM sc WHERE cno IN 
(SELECT cno FROM c WHERE sc.cno=cno AND cname='数据结构');
#3
DELETE FROM sc WHERE sno='201215122' ;
DELETE FROM s WHERE sno='201215122' ;
#4
CREATE VIEW boy (bno,bname,cname,grade) AS 
SELECT s.sno,s.sname,c.cname,sc.Grade
FROM s,c,sc
WHERE s.sno=sc.sno AND c.cno=sc.cno AND ssex='男';

#5
SELECT sname FROM s 
WHERE sno IN (
SELECT sc.sno FROM sc,c
WHERE sc.cno=c.cno AND c.ccredit=3 AND sc.grade>=80 
GROUP BY sc.sno HAVING COUNT(sc.cno)>=3);
#6
#7
GRANT 