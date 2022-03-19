#实验一
create database school; 
use school;
create table S(
    Sno char(9) UNIQUE,
    Sname char(3),
    Ssex char(1),
    Sage int,
    Sdept char(2),
    constraint pk_S primary key (Sno)
);
create table C(
    Cno char(1) UNIQUE ,
    Cname char(4),
    Ccredit int,
    constraint pk_C primary key (Cno)
);
create table SC(
    Sno char(9),
    Cno char(1),
    Grade FLOAT,
    constraint c1 check (Grade>=0 and Grade<=100),
    PRIMARY KEY (`Sno`,`Cno`),
    constraint fk_s foreign key (Sno) references S(Sno),
    constraint fk_c foreign key (Cno) references C(Cno)
);


#实验二
CREATE TABLE  account(
    id int PRIMARY KEY AUTO_INCREMENT ,
    customer_id int,
    dish_id int,
    num int,
    price double,
    mark int ,
    evaluation varchar(40),
    CONSTRAINT c_a CHECK(mark>=0 and mark<=5) 
);
CREATE TABLE  dishes(
    id int PRIMARY KEY AUTO_INCREMENT,
    name varchar(40),
    material varchar(40),
    type int,
    price double,
    photo varchar(40),
    avemark double,
    sales int
);

CREATE  TABLE  customer(
    id int PRIMARY KEY AUTO_INCREMENT,
    name varchar(40),
    password varchar(40),
    balance int
);
CREATE  TABLE  manager(
    id int PRIMARY KEY AUTO_INCREMENT ,
    name varchar(40),
    password varchar(40)
);