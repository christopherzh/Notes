create schema school; 
create table S(
    Sno char(9),
    Sname char(3),
    Ssex char(1);
    Sage numeric(2),
    Sdept char(2),
    constraint pk_S primary key Sno
);
create table C(
    Cno char(1),
    Cname char(4),
    Ccredit numeric(1),
    constraint pk_C primary key Cno
);
create table SC(
    Sno char(9),
    Cno char(1),
    Grade numeric(2),
    constraint c1 Grade>=0 and Grade<=100,
    constraint fk_sc foreign key Sno,Cno references S,C
);