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
#1
SELECT  Sno,Grade FROM sc WHERE Cno='2';

#2
#solution1
SELECT sc.sno,s.sage FROM sc LEFT JOIN s ON sc.sno=s.sno 
LEFT JOIN c ON sc.cno=c.cno WHERE  cname='数据结构';
#solution2
SELECT sc.sno,s.sage FROM sc LEFT JOIN s ON sc.sno=s.sno  
WHERE cno=(SELECT cno FROM c WHERE cname='数据结构');

#3
SELECT  sno,sname FROM  s 
WHERE NOT EXISTS(SELECT * FROM  sc WHERE s.sno=sc.sno AND cno='3');

#4
SELECT sname FROM s WHERE NOT EXISTS 
(SELECT  * FROM c WHERE NOT EXISTS 
(SELECT * FROM sc WHERE sc.sno=s.sno AND c.cno=sc.cno ) );

#5
SELECT sno,AVG(grade) FROM sc  WHERE cno='1' OR grade>=60 
GROUP BY sc.sno ORDER BY  AVG(grade) DESC ;

#6
#situation2
SELECT sname FROM s,sc,c
WHERE s.sno=sc.sno AND sc.cno=c.cno AND cname='数据库'
ORDER BY grade DESC LIMIT 1,1;
#situation1
SELECT sname FROM s,sc,c
WHERE s.sno=sc.sno AND sc.cno=c.cno AND c.cname='数据库' AND 
grade<(SELECT MAX(sc.grade) FROM sc,c
WHERE sc.cno=c.cno AND c.cname='数据库') ORDER BY grade DESC LIMIT 0,1 ;



#7
SELECT sname FROM s 
WHERE sno IN (
SELECT sc.sno FROM sc,c
WHERE sc.cno=c.cno AND c.ccredit=3 AND sc.grade>=80 
GROUP BY sc.sno HAVING COUNT(sc.cno)>=3);

#8
SELECT sno,COUNT(cno) FROM sc GROUP BY sno HAVING COUNT(cno)=1;


/*
仅为练习分组
SELECT cno,MAX(grade)  FROM sc  
WHERE cno IN 
(SELECT sc.cno FROM sc,c WHERE sc.cno=c.cno AND c.cname='数据库' ) 
GROUP BY sc.cno;
*/