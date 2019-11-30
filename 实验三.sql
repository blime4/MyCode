
drop table teacher;
drop table department;

create table department(
  dno VARCHAR2(10) primary key,
  dname varchar2(20)
);

create table teacher(
  TNO                  VARCHAR2(20)         not null,
  DNO                  VARCHAR2(10)         not null,
  TName                NVARCHAR2(20)        not null,
  TSex                 VARCHAR2(3)          not null,
  TSalary              NUMBER(30,2),
  projectFunds         NUMBER(10,2),
  workdays             INTEGER,
  constraint PK_TEACHER primary key (TNO),
  constraint F_TEACHER foreign key (dno)references department(dno)
);

insert into department(dno,dname)values('d001','计算机科学系');
insert into department(dno,dname)values('d002','软件工程系');
insert into department(dno,dname)values('d003','数学系');

insert into teacher(tno, tname, tsex, tsalary, dno,projectFunds,workdays) values('t001', '张三', '男', 3000,'d001',100000,1000);
insert into teacher(tno, tname, tsex,  tsalary, dno, projectFunds,workdays) values('t002', '李四', '女', 3600,'d001',50000,1200);
insert into teacher(tno, tname, tsex,  tsalary, dno, projectFunds,workdays) values('t003', '王五', '女', 5600,'d002',80000,365);
insert into teacher(tno, tname, tsex,  tsalary, dno, projectFunds,workdays) values('t004', '刘晨', '女', 5800, 'd002',60000,365);
insert into teacher(tno, tname, tsex,  tsalary, dno, workdays) values('t005', '王二小', '男', 3500,'d003',600);
insert into teacher(tno, tname, tsex,  tsalary, dno, workdays) values('t006', '李小龙', '男', 5687, 'd003',1100);
insert into teacher(tno, tname, tsex,  tsalary, dno, workdays) values('t007', '熊猫', '男', 6000, 'd003',200);
insert into teacher(tno, tname, tsex,  tsalary, dno, projectFunds,workdays) values('t008', '李小小', '女', 5687, 'd001',30000,365);

select *from department;
select *from teacher;



-- 本实验的基本内容是通过编写存储过程、函数和触发器，掌握 Oracle 数据库中存储过 程、函数和触发器的定义、使用和管理方法。实验基本步骤如下：
-- 1. 为 Teacher 表创建一个触发器，触发器名称为“学生名字首字母+UpdateTeacher”，
-- 当插入新教师时，如果新教师的工资少于 4000，拒绝插入数据；当工资高于 90000 时，把 工资改为 9000；
-- 当删除教师时，输出被删除的教师基本信息。
create or replace trigger PUpdateTeacher
    before insert or delete on teacher
    for each row
    begin
    if inserting then
        if :new.tsalary<4000 then
            raise_application_error(-20001,'教师的工资少于 4000，拒绝插入数据');
        elsif :new.tsalary>90000 then
            :new.tsalary := 9000;
        end if;
    elsif deleting then
        DBMS_OUTPUT.PUT_LINE('删除成功！');
        DBMS_OUTPUT.PUT_LINE('被删除教师名字: '||:old.TName||' 教师号: '||:old.TNO||' 性别: '||:old.TSex||' 工资: '||:OLD.TSalary);
    end if;
    end PUpdateTeacher;

-- 2. 编写代码测试第 1 步创建的触发器；
insert into teacher(tno, tname, tsex, tsalary, dno,projectFunds,workdays) values('t009', '张三', '男', 3000,'d001',100000,1000);
select * from teacher;
insert into teacher(tno, tname, tsex, tsalary, dno,projectFunds,workdays) values('t010', '张三', '男', 100000,'d001',100000,1000);
select * from teacher;
delete from teacher where TNO='t010';
-- [2019-11-18 16:20:00] 删除成功！
-- [2019-11-18 16:20:00] 被删除教师名字: 张三 教师号: t010 性别: 男 工资: 9000


-- 3. 创建视图“学生名字首字母+teacherdept”，视图内容包含教师所有信息及其所在部 门信息，
-- 即语句 SELECT dname, teacher.* from department, teacher Where department.dno = teacher.dno WITH CHECK OPTION。
-- 为该视图创建一个 instead of 触发器，当用户向该视图 中插入数据时，数据被插入到 teacher 表中。
create view Pteacherdept as
    SELECT department.dname, teacher.* from department, teacher Where department.dno = teacher.dno WITH CHECK OPTION;
select * from Pteacherdept;
create or replace trigger tri_view_insert
    instead of insert
    on Pteacherdept
    for each row
begin
    insert into teacher(tno, DNO,tname,tsex,tsalary,projectFunds,workdays) values (:new.tno,:new.dno,:new.tname,:new.tsex,:new.tsalary,:new.projectFunds,:new.workdays);
end;

-- 4. 编写代码测试第 3 步创建的触发器；
insert into Pteacherdept(tno, tname, tsex, tsalary, dno,projectFunds,workdays) values('t009', '张三', '男', 4000,'d001',100000,1000);
select * from teacher;
delete from teacher where TNO='t009';


-- 5. 创建一个存储过程，名称设为“学生名字首字母+sumDaysByTno”，存储过程有两 个参数，输入参数为教师编号，输出参数为总的工作天数。
create or replace procedure PsumDaysByTno(
    P_tno teacher.tno%TYPE,
    p_workdays out teacher.workdays%type
)
as
begin
    select workdays into p_workdays from teacher where TNO=P_tno;
end PsumDaysByTno;
-- 6. 编写代码测试第 5 步创建的存储过程；

declare
    p_workdays teacher.workdays%type;
begin
    PsumDaysByTno('t002',p_workdays);
    DBMS_OUTPUT.PUT_LINE(p_workdays);
end;

-- 7. 定义一个函数，名称设为“学生名字首字母+sumFundByTno”，参数为教师编号， 返回该教师的所有项目的经费总和；
create or replace function PsumFundByTno(
    P_tno teacher.tno%TYPE)
    return teacher.workdays%type
as
    p_fund teacher.projectFunds%type;
begin
    select projectFunds into p_fund from teacher where TNO=P_tno;
    return p_fund;
end PsumFundByTno;

-- 8. 编写代码测试第 7 步创建的函数；
declare
    p_fund teacher.projectFunds%type;
begin
    p_fund := PsumFundByTno('t004');
    DBMS_OUTPUT.PUT_LINE(p_fund);
end;


-- 9. 删除实验中创建的存储过程；
drop procedure PsumDaysByTno;
-- 10. 删除实验中创建的函数；
drop function PsumFundByTno;
-- 11. 删除实验中创建的触发器
drop trigger PUpdateTeacher;








