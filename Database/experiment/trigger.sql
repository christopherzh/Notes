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
DROP fk_s;
CREATE TRIGGER ;
#2
ALTER TABLE sc
DROP fk_s;
CREATE TRIGGER;
#3
CREATE TRIGGER INSERT;
#4
CREATE TRIGGER UPDATE;