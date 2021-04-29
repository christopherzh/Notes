create schema school; 
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
    Grade int,
    constraint c1 check (Grade>=0 and Grade<=100),
    constraint fk_s foreign key (Sno) references S(Sno),
    constraint fk_c foreign key (Cno) references C(Cno)
);