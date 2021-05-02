/*
1.	首先解除S表和SC表的参照关系。然后在Student表上创建一个触发器，
使更新一个学生的学号信息时能够级联的更新此学生在SC表中的选课记录的学号信息，
并进行验证
2.	首先解除S表和SC表的参照关系。然后在Student表上创建一个触发器，
使删除一个学生时能够级联的删除此学生在SC表中的选课记录，并进行验证。
3.	在 S 表中编写 insert 的触发器，假如每个班的学生不能超过 30 个，
如果低于此数，添加可以完成；如果超过此数，则插入将不能实现。
4.	在 SC 表上编写 update 触发器，
当修改 SC 表中的 Grade 字段时将其修改前后的信息保存在 SC_log 表中。
实验完成后,撤消建立的基本表和视图。
*/



#1
ALTER TABLE sc
DROP FOREIGN KEY fk_s;
CREATE TRIGGER update_sno1
AFTER UPDATE ON S
FOR EACH ROW
UPDATE  sc SET  sc.sno=new.sno 
WHERE sc.sno=old.sno ;

#验证
UPDATE s SET sno='201215130' WHERE sno='201215120';


#2
ALTER TABLE sc
DROP FOREIGN KEY fk_s;

CREATE TRIGGER delete_sno
AFTER  DELETE ON s
FOR EACH ROW
DELETE FROM sc WHERE sc.Sno=old.Sno;

#验证
DELETE FROM s WHERE sno='201215121';
DELETE FROM s WHERE sno='201215123';


#3
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

#验证
INSERT INTO S
VALUES
	('201215129', '李莉', '男', 20, 'CS'),
    ('201215131', '刘星', '女', 19, 'CS'),
    ('201215132', '王浩然', '女', 18, 'MA'),
    ('201215133', '张立', '男', 19, 'IS'),
    ('201215134', '王强', '男', 22, 'CS'),
    ('201215135', '李爽', '男', 20, 'CS'),
    ('201215136', '李莉', '男', 20, 'CS'),
    ('201215137', '刘星', '女', 19, 'CS'),
    ('201215138', '王浩然', '女', 18, 'MA'),
    ('201215139', '张立', '男', 19, 'IS'),
    ('201215140', '李爽', '男', 20, 'CS'),
    ('201215141', '李莉', '男', 20, 'CS'),
    ('201215142', '刘星', '女', 19, 'CS'),
    ('201215143', '王浩然', '女', 18, 'MA'),
    ('201215144', '张立', '男', 19, 'IS'),
    ('201215145', '王强', '男', 22, 'CS'),
    ('201215146', '李爽', '男', 20, 'CS'),
    ('201215147', '李莉', '男', 20, 'CS'),
    ('201215148', '刘星', '女', 19, 'CS'),
    ('201215149', '王浩然', '女', 18, 'MA'),
    ('201215150', '张立', '男', 19, 'IS'),
    ('201215151', '王强', '男', 22, 'CS'),
    ('201215152', '李爽', '男', 20, 'CS'),
    ('201215153', '李莉', '男', 20, 'CS'),
    ('201215154', '王强', '男', 22, 'CS'),
    ('201215155', '王浩然', '女', 18, 'MA'),
    ('20121515', '王浩然', '女', 18, 'MA');
INSERT INTO S VALUES('201215156', '王浩然', '男', 20, 'CS');

#4
CREATE TABLE sc_log(
    pre_grade int CHECK(pre_grade BETWEEN 0 AND 100),
    now_grade int CHECK(now_grade BETWEEN 0 AND 100)
);
CREATE TRIGGER update_grade
AFTER UPDATE ON  sc
FOR EACH ROW BEGIN
	INSERT INTO SC_log VALUES (OLD.Grade, NEW.Grade);
END

#验证
UPDATE sc SET Grade = Grade +10
WHERE Cno = '4';


#5
DROP TABLE sc_log;
DROP VIEW boy;