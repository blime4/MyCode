create table class --班级
(
   classno            CHAR(15)             not null,--班级号
   classname          VARCHAR2(20)         not null,--班级名
   headteacher        VARCHAR2(20),--班主任
   primary key (classno)
);

create table student  --学生
(
   sno                VARCHAR2(10)         not null,--学号
   sname              VARCHAR2(20)         not null,--姓名
   classname          VARCHAR2(20)         not null,--班级名
   ssex               CHAR(3)              not null,--性别
   primary key (sno)
);
alter table student modify ssex default '男' check (ssex in('男','女'));

create table courseteam--课程组
(
   teamno             CHAR(15)             not null,--课程组号
   teamname           VARCHAR2(40)         not null,--课程组名
   teamleader         VARCHAR2(20),--负责人
   primary key (teamno)
);
 
create table teacher--老师
(
   tno                CHAR(6)              not null,--教工号
   teamno             CHAR(15),--课程组号
   tname              VARCHAR2(20)         not null,--姓名
   teamname           VARCHAR2(40)         not null,--课程组名
   tsex               CHAR(3)              not null,--性别
   ttitle             VARCHAR2(10)         not null,--职称
   primary key (tno)   
);
alter table teacher modify tsex default '男' check (tsex in('男','女'));

create table course--课程
(
   cno                CHAR(9)              not null,--课程号
   cname              VARCHAR2(40)         not null,--课程名
   ccredit            FLOAT(2)             not null,--学分
   primary key (cno)
);
alter table course add type VARCHAR2(30);--课程类型

create table curriculum--课程表
(
   sno                VARCHAR2(10)         not null,--学号
   cno                CHAR(9)              not null,--课程号
   type               VARCHAR2(30),--课程类型
   week               VARCHAR2(20),--周数
   day                VARCHAR2(10),--星期几
   time               VARCHAR2(10),--第几节
   grade              FLOAT(4),
   primary key (sno, cno,day),
   foreign key (sno) references student(sno),
   foreign key (cno) references course(cno)
);
alter table curriculum drop column type;

create table teach--授课表
(
   tno                CHAR(6)              not null,--教工号
   cno                CHAR(9)              not null,--课程号
   classno            CHAR(15)             not null,--班级号
   week               VARCHAR2(40),--周数
   day                VARCHAR2(10),--星期几
   time               VARCHAR2(10),--第几节
   primary key (tno, cno,classno,day),
   foreign key (tno) references teacher(tno),
   foreign key (cno) references course(cno),
   foreign key (classno) references class(classno)
);

select * from class;
select * from student;
select * from course;
select * from courseteam;
select * from teacher;
select * from curriculum;
select * from teach;


--学生个人课表查询
create or replace procedure queryPer_Sche(pno in Student.Sno%type)
as
    cursor per_cursor is
    select sname,cname,day,time,week from curriculum,student,course
    where Student.sno=pno and student.sno=curriculum.sno and course.cno=curriculum.cno order by day asc;
        cur per_cursor%rowtype;
begin
    DBMS_OUTPUT.put_line(pno||'个人课表');
    for cur in per_cursor loop
        exit when per_cursor%notfound;
         DBMS_OUTPUT.put_line('课程：'||cur.cname||'  星期：'||cur.day||'  节次:'||cur.time||'  周数：' ||cur.week);
    end loop;
end;
set serveroutput on;
call queryPer_Sche('1706300077');
 

--学生成绩查询
create or replace procedure queryPer_Grade(pno in Student.Sno%type)
as
    cursor per_cursor is
    --select Per_Grade_view.* from Per_Grade_view,student where student.sno=pno;
    select distinct cname,grade from course,curriculum where sno=pno and curriculum.cno=course.cno;
        cur per_cursor%rowtype;
    
    begin
      --open per_cursor;
        DBMS_OUTPUT.put_line(pno||'个人成绩');
        for cur in per_cursor loop
            exit when per_cursor%notfound;
            --成绩为空不操作
            DBMS_OUTPUT.put_line('科目--'||cur.cname||'   成绩--'||cur.grade);
        end loop;
       --close per_cursor;
    end;
call queryPer_Grade('1706300077');


--查询学生绩点
create or replace procedure queryPer_GPA(pno in Student.Sno%type)
as
    cursor per_cursor is 
    select distinct course.cname,curriculum.grade,course.ccredit from curriculum,course 
    where curriculum.sno=pno and course.cno=curriculum.cno;
    ans float :=0;
    result0 float :=0;
    zongGPA float :=0;
    tempGPA float :=0;
        begin
            for cur in per_cursor loop
                exit when per_cursor%notfound;
                zongGPA:=zongGPA+cur.ccredit;
                if cur.grade is null then begin zongGPA:=zongGPA-cur.ccredit;end;
                elsif (cur.grade between 0 and 59) then begin ans:=ans+0;tempGPA:=0;end;
                elsif (cur.grade between 61 and 63) then begin ans:=ans+1.3*cur.ccredit;tempGPA:=1.3;end;
                elsif (cur.grade between 64 and 64) then begin ans:=ans+1.5*cur.ccredit;tempGPA:=1.5;end;
                elsif (cur.grade between 65 and 67) then begin ans:=ans+1.7*cur.ccredit;tempGPA:=1.7;end;
                elsif (cur.grade between 68 and 71) then begin ans:=ans+2*cur.ccredit;  tempGPA:=2;  end;
                elsif (cur.grade between 72 and 74) then begin ans:=ans+2.3*cur.ccredit;tempGPA:=2.3;end;
                elsif (cur.grade between 75 and 77) then begin ans:=ans+2.7*cur.ccredit;tempGPA:=2.7;end;
                elsif (cur.grade between 78 and 81) then begin ans:=ans+3*cur.ccredit;  tempGPA:=3;  end;
                elsif (cur.grade between 82 and 84) then begin ans:=ans+3.3*cur.ccredit;tempGPA:=3.3;end;
                elsif (cur.grade between 85 and 89) then begin ans:=ans+3.7*cur.ccredit;tempGPA:=3.7;end;
                elsif (cur.grade between 90 and 94) then begin ans:=ans+4*cur.ccredit;  tempGPA:=4;  end;
                elsif (cur.grade between 95 and 100) then begin ans:=ans+4.3*cur.ccredit;tempGPA:=4.3;end ;
                end if;
                if cur.grade is not null then
                    begin
                       DBMS_OUTPUT.put_line(cur.cname||'   绩点--'||tempGPA);
                    end;
                end if ;

                --DBMS_OUTPUT.put_line('累计学分为--'||zongGPA);
            end loop;
            if zongGPA=0 then
                DBMS_OUTPUT.put_line('成绩还未录入，请耐心等候!');
            else
                --DBMS_OUTPUT.put_line('总学分为--'||zongGPA);
                DBMS_OUTPUT.put_line('总绩点为--'||round(ans/zongGPA,4));
            end if;
        end;

call queryPer_GPA('1706300077');



--教师授课表查询
create or replace procedure queryteacher_sche(pno in teacher.tno%type)
as 
    cursor per_cursor is
    select distinct time,tno,day,week from teach where tno=pno order by day asc;
        cur per_cursor%rowtype;
    begin 
        for cur in per_cursor loop
            exit when per_cursor%notfound;
            DBMS_OUTPUT.put_line('教工号：'||cur.tno||' 星期：'||cur.day||' 节次：'||cur.time||' 周数：'||cur.week);
       end loop;
    end;
call queryteacher_sche('103570');      

create view stu_info_view as
select distinct curriculum.sno,sname  from curriculum,teach,student
where  curriculum.sno=student.sno and curriculum.day=teach.day and curriculum.week=teach.week and curriculum.time=teach.time;
select * from stu_info_view;

--老师查询选课学生表
create or replace procedure querystu_info(p1 in teach.tno%type,p2 in teach.cno%type)
as
    cursor per_cursor is
    select distinct curriculum.sno,sname  from curriculum,teach,student
    where teach.tno=p1 and teach.cno=p2 and curriculum.cno=teach.cno and curriculum.sno=student.sno 
    and curriculum.day=teach.day and curriculum.week=teach.week and curriculum.time=teach.time;
        cur per_cursor%rowtype;
    begin
        for cur in per_cursor loop
            exit when per_cursor%notfound;
            DBMS_OUTPUT.put_line('上课学生学号：'||cur.sno||'  学生姓名：'||cur.sname);
        end loop;
    end;
call querystu_info('103570','130600014');--参数为教工号，课程号


--查询班级课程表
create or replace procedure queryclass_sche(pno in Student.classname%type)
as
    cursor per_cursor is
    select distinct classname,course.cname,curriculum.day,curriculum.time,curriculum.week from curriculum,student,course
    where student.classname=pno and course.type in('通识类必修课程','专业必修课程') and curriculum.cno=course.cno
    order by day asc;
       cur per_cursor%rowtype;
    begin
        DBMS_OUTPUT.put_line(pno||'班级课程表');
        for cur in per_cursor loop
            DBMS_OUTPUT.put_line('课程:'||cur.cname||'  星期：'||cur.day||'  节次：'||cur.time||'  上课周数：'||cur.week);
            exit when per_cursor%notfound;
        end loop;
    end;
call queryclass_sche('软件172');


--教师登分
create or replace procedure record(p1 in teach.cno%type,p2 in curriculum.sno%type,p3 in curriculum.grade%type)
as
    grade1 curriculum.grade%type :=0;
    cname1 course.cname%type :=null;
    sname1 student.sname%type :=null;
    begin
    select distinct student.sname,course.cname,curriculum.grade into sname1,cname1,grade1
    from student,curriculum,teach,course where teach.cno=p1
    and curriculum.sno=p2
    and curriculum.sno=student.sno
    and teach.cno=curriculum.cno
    and curriculum.cno=course.cno;
    DBMS_OUTPUT.put_line(' 学生名字： '||sname1||' 课程：'||cname1);
    DBMS_OUTPUT.put_line(' 原成绩：'||grade1);
    update curriculum set grade=p3 where sno=p2 and cno =p1;
    DBMS_OUTPUT.put_line(' 现成绩：'||p3);
    commit;
end;
call record('130600015','1706300077','100');

set serveroutput on;
--触发器，确保录入的成绩信息有效,当成绩小于0或大于100时会提示成绩异常
create or replace trigger trigrade before insert or update on curriculum
    for each row
    begin
        if :new.grade<0  then 
          raise_application_error(-20007,'成绩异常');
          elsif :new.grade>100 then
          raise_application_error(-20007,'成绩异常');
        end if;
    end;
call record('130600015','1706300077','-1');

    
--排课系统，输入课程
create or replace procedure course_scheduling(p1 in course.cno%type,p2 in course.cname%type,p3 in course.ccredit%type,p4 in course.type%type)
as
    begin
        insert into course(cno, cname, ccredit,TYPE) VALUES(p1,p2,p3,p4);
        DBMS_OUTPUT.put_line('插入成功');
    end;    
call course_scheduling('130600027','人工智能导论',2,'专业选修课程')
call course_scheduling('100000','体育课',2,'选修课程')

--学生选专业选修课
create or replace procedure optional_course(p1 in curriculum.sno%type,p2 in curriculum.cno%type)
as
    cursor per_cursor is
    select distinct teach.week, teach.day,teach.time from teach,course 
    where teach.cno=p2 and teach.cno=course.cno and course.type like '%选修%';
        cur per_cursor%rowtype;
    cursor com_cursor is
    select distinct week,day,time from curriculum where sno=p1;
        com com_cursor%rowtype;
    begin
        for cur in per_cursor loop
            exit when per_cursor%notfound;
            for com in com_cursor loop
                exit when com_cursor%notfound;
                --for循环和原本课表上的课对比，如果时间冲突就报错
                if cur.time=com.time and cur.day=com.day and cur.week=com.week then
                    raise_application_error(-20005,'时间冲突，不可选！');
                end if;
            end loop;
        end loop;
        for cur in per_cursor loop
            exit when per_cursor%notfound;
            insert into curriculum(sno, cno, week, day, time) values (p1,p2,cur.week,cur.day,cur.time);
            DBMS_OUTPUT.put_line('选课成功');
        end loop; 
        commit;
    end;    
set serveroutput on;
call optional_course('1706300078','130600027');

select *from curriculum;

create view student_view as select *from student;
create view teacher_view as select *from teacher;
create view course_view as select *from course;



create global temporary table temp_dwt1--创建临时表
        (day varchar2(10),
         week VARCHAR2(40),
         time varchar2(10)) on commit delete rows ;         
--创建触发器，当老师授课表插入课程时，判断这节课是否必修课，若是必修课，这节课添加到该班级的所有学生的课程表中。
--用临时表暂时保存这节课的信息
create or replace trigger auto_add_course before insert on teach
    for each row
    declare
    check_type course.type%type;
    temp_cno course.cno%type;
    temp_sno student.sno%type;
    temp_tno teach.tno%type;
    begin
        temp_cno :=:new.cno;
        temp_tno :=:new.tno;
        insert into temp_dwt1(day,week,time) values (:new.day,:new.week,:new.time);
        DBMS_OUTPUT.put_line(temp_cno);
        select distinct type into check_type from course where course.cno=temp_cno;
        if check_type like '%必修%' then
            DBMS_OUTPUT.put_line('oooo');
            insert into curriculum(sno,cno,day,week,time) select sno,cno,temp_dwt1.day,temp_dwt1.week,temp_dwt1.time from student,course,temp_dwt1
            where course.cno=temp_cno and student.classname in
            (select distinct classname from class where class.classno in
            ( select classno from teach where tno=temp_tno)) ;
            else
            DBMS_OUTPUT.put_line('1111');
        end if;
        delete from TEMP_DWT1 where temp_dwt1.day=:new.day;
    end;
    
insert into teach (tno, cno, classno, week, day, time) values ('103570','130600014','0630173','7-8节','3','1-8周');
select * from curriculum;


----绩点排名
--创建临时表
create global temporary table temp_rank(pname VARCHAR2(20),get_GPA float) on commit delete rows;

--存储过程show_rank，从临时表中获取所有学生姓名和绩点，输出学生绩点排名
create or replace procedure show_rank
as
    cursor per_cursor is
    select pname,get_GPA from temp_rank where get_GPA is not null order by get_GPA desc ;--未录入成绩的学生不参与排名
        cur per_cursor%rowtype;
        begin
            for cur in per_cursor loop
                DBMS_OUTPUT.put_line('名字--'||cur.pname||'   绩点--'||cur.get_GPA);
            end loop;
            execute immediate 'truncate table temp_rank';
        end;


--存储过程queryPer_GPA_for_rank，获取每个有成绩数据的学生的名字和总绩点
create or replace procedure queryPer_GPA_for_rank(pno in Student.Sno%type,pname out Student.Sname%type,get_GPA out float)
as
    cursor per_cursor is select distinct course.cname,curriculum.grade,course.ccredit,student.sname from curriculum,course,student where curriculum.sno=pno and course.cno=curriculum.cno and student.sno=pno;
    ans float :=0;
    result0 float :=0;
    zongGPA float :=0;
    tempGPA float :=0;
    flag boolean:=true;
        begin
            for cur in per_cursor loop
                exit when per_cursor%notfound;
                zongGPA:=zongGPA+cur.ccredit;
                if cur.grade is null then begin zongGPA:=zongGPA-cur.ccredit;end;
                elsif (cur.grade between 0 and 59) then begin ans:=ans+0;tempGPA:=0;end;
                elsif (cur.grade between 61 and 63) then begin ans:=ans+1.3*cur.ccredit;tempGPA:=1.3;end;
                elsif (cur.grade between 64 and 64) then begin ans:=ans+1.5*cur.ccredit;tempGPA:=1.5;end;
                elsif (cur.grade between 65 and 67) then begin ans:=ans+1.7*cur.ccredit;tempGPA:=1.7;end;
                elsif (cur.grade between 68 and 71) then begin ans:=ans+2*cur.ccredit;  tempGPA:=2;  end;
                elsif (cur.grade between 72 and 74) then begin ans:=ans+2.3*cur.ccredit;tempGPA:=2.3;end;
                elsif (cur.grade between 75 and 77) then begin ans:=ans+2.7*cur.ccredit;tempGPA:=2.7;end;
                elsif (cur.grade between 78 and 81) then begin ans:=ans+3*cur.ccredit;  tempGPA:=3;  end;
                elsif (cur.grade between 82 and 84) then begin ans:=ans+3.3*cur.ccredit;tempGPA:=3.3;end;
                elsif (cur.grade between 85 and 89) then begin ans:=ans+3.7*cur.ccredit;tempGPA:=3.7;end;
                elsif (cur.grade between 90 and 94) then begin ans:=ans+4*cur.ccredit;  tempGPA:=4;  end;
                elsif (cur.grade between 95 and 100) then begin ans:=ans+4.3*cur.ccredit;tempGPA:=4.3;end ;
                end if;
                if flag then
                    begin
                         --DBMS_OUTPUT.put_line('姓名'||cur.sname);
                        pname:=cur.sname;
                        flag:=false;
                    end;
                end if ;
            end loop;
            if zongGPA=0 then
                get_GPA :=null;
            else
                 --DBMS_OUTPUT.put_line('总绩点为--'||round(ans/zongGPA,4));
                get_GPA :=round(ans/zongGPA,4);
            end if;
        end;


--存储过程GPA_rank
create or replace procedure GPA_rank
as
    cursor per_cursor is
    select distinct sno from curriculum;
        cur per_cursor%rowtype;
    get_GPA_0 float;
    pname_0 Student.Sname%type;
    begin
        for cur in per_cursor loop
            queryPer_GPA_for_rank(cur.sno,pname_0,get_GPA_0);--获取每个有成绩数据的学生的名字和总绩点
            insert into temp_rank(pname,get_GPA) values (pname_0,get_GPA_0);--把学生的名字和总绩点插入到临时表
        end loop ;
        show_rank();--输出绩点排名
    end;

call GPA_rank();--调用





