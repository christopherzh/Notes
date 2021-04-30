/*
1.	查询选修 2 号课程的学生学号与该课程成绩。
2.	查询选修课程名为数据结构的学生学号与年龄。
3.	查询不选 3 号课程的学生学号与姓名。
4.	查询学习全部课程学生姓名。
5.	查询所有学生 除了选修 1 号课程外 所有成绩均及格的学生的学号和平均成绩,
其结果按平均成绩的降序排列。
6.	查询选修数据库原理成绩第 2 名的学生姓名。
7.	查询所有 3 个学分课程中有 3 门以上(含 3 门)课程获 80 分以上(含 80 分)
的学生的姓名。
8.	查询选课门数唯一的学生的学号。
*/
SELECT  Sno,Grade FROM sc WHERE Cno='2';

SELECT sc.sno,s.sage FROM sc LEFT JOIN s ON sc.sno=s.sno 
LEFT JOIN c ON sc.cno=c.cno WHERE  cname='数据结构';
SELECT sc.sno,s.sage FROM sc LEFT JOIN s ON sc.sno=s.sno  
WHERE cno=(SELECT cno FROM c WHERE cname='数据结构');

SELECT  sno,sname FROM  s 
WHERE NOT EXISTS(SELECT * FROM  sc WHERE s.sno=sc.sno AND cno='3');

SELECT sname FROM s WHERE NOT EXISTS 
(SELECT  * FROM c WHERE NOT EXISTS 
(SELECT * FROM sc WHERE sc.sno=s.sno AND c.cno=sc.cno ) );

SELECT sno.AVG(Grade) FROM sc WHERE ;

SELECT sname from s