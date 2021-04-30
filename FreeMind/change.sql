/*
1.	把 1 号课程的非空成绩提高 5%。
2.	在 SC 表中删除课程名为数据结构的成绩的元组。
3.	在 S 和 SC 表中删除学号为 201215122 的所有数据。
4.	建立男学生的视图,属性包括学号、姓名、选修课程名和成绩。
5.	在男学生视图中查询平均成绩大于 80 分的学生学号与姓名。
6.	计算每个学生有成绩的课程门数、平均成绩。
7.	使用 GRANT 语句,把对基本表 S、SC、C 的使用权限授给其它用户。
*/
UPDATE sc SET grade=grade+0.05*grade WHERE cno='1' AND grade IS NOT NULL 

DELETE FROM sc WHERE cno IN 
(SELECT sc.cno FROM sc,c WHERE sc.cno=c.cno AND cname='数据结构')

DELETE FROM sc,c WHERE sc.sno='201215122' AND s.sno='201215122'

CREATE VIEW v1(

)

GRANT 