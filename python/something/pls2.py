# -*- coding:UTF-8 -*-
from tkinter import *
import tkinter.font as tkfont
import tkinter as tk
from tkinter import ttk
import cx_Oracle
import tkinter.messagebox 



import pandas as pd
from sqlalchemy import create_engine
engine = create_engine('oracle+cx_oracle://blime:pls@localhost/orcl')
conn = engine.connect()


class login():
    def __init__(self,master):
        self.master = master
        self.master.config()
        self.master.title('Welcome to perbl system!')
        self.master.geometry('450x300')
        login_window = tk.Frame(self.master, width=450, height=300)
        login_window.pack()
        self.var_usr_name=tk.StringVar()     
        self.var_usr_name.set('sno/tno/mno')
        self.var_usr_pwd= tk.StringVar()     
        self.var_usr_pos= tk.StringVar()
        tk.Label(login_window,text='User name:').place(x=50,y=130)
        tk.Label(login_window,text='Password:').place(x=50,y=170)
        tk.Label(login_window,text='Position:').place(x=50,y=200)
        entry_usr_name = tk.Entry(login_window,textvariable=self.var_usr_name,width=30)
        entry_usr_name.place(x=160,y=130)
        entry_usr_pwd = tk.Entry(login_window,textvariable=self.var_usr_pwd,show='*',width=30)
        entry_usr_pwd.place(x=160,y=170)
        r1 = tk.Radiobutton(login_window,text='Student',variable=self.var_usr_pos,value='Student')
        r2 = tk.Radiobutton(login_window,text='Teacher',variable=self.var_usr_pos,value='Teacher')
        r3 = tk.Radiobutton(login_window,text='Manager',variable=self.var_usr_pos,value='Manager')
        r1.place(x=160,y=200)
        r2.place(x=240,y=200)
        r3.place(x=320,y=200)
        
        def query_user(usr_name,usr_pwd,usr_pos):
            if usr_name=='' or usr_name=='sno/tno/mno':
                tk.messagebox.showinfo(message='Please enter your username!')
            elif usr_pwd=='':
                tk.messagebox.showinfo(message='Please enter your password!')
            elif usr_pos=='':
                tk.messagebox.showinfo(message='Please choose your position!')
            # conn = cx_Oracle.connect('blime/pls@localhost/orcl')
            sql=""
            pwd=""
            if usr_pos=="Teacher":
                sql = "SELECT * FROM teacher WHERE tno = \'" + usr_name + "\'";
                pwd='tpwd'
            elif usr_pos=="Student":
                sql = "SELECT * FROM student WHERE sno = \'" + usr_name + "\'";
                pwd='spwd'
            elif usr_pos=="Manager":
                sql = "SELECT * FROM manager WHERE mno = \'" + usr_name + "\'";
                pwd='mpwd'
            global user_data
            user_data = pd.read_sql_query(sql,con=engine)
            if user_data.empty:
                tk.messagebox.showinfo(message='user not found!')
            else:
                if usr_pwd != user_data[pwd].values:
                    tk.messagebox.showinfo(message='password error!')
                else:
                    login_window.destroy()
                    if usr_pos=="Teacher":
                        teacher(self.master)
                    elif usr_pos=="Student":
                        student(self.master)
                    else:
                        manager(self.master)

        def usr_help():
            pass
        def usr_login():
            usr_name = self.var_usr_name.get()
            usr_pwd = self.var_usr_pwd.get()
            usr_pos = self.var_usr_pos.get()
            print(usr_name)
            print(usr_pwd)
            print(usr_pos)
            query_user(usr_name,usr_pwd,usr_pos)
        #login and help button
        btn_login = tk.Button(login_window,text='Login',command=usr_login)
        btn_login.place(x=170,y=230)
        btn_help = tk.Button(login_window,text='Help',command=usr_help)
        btn_help.place(x=270,y=230)

 
class manager():
    def __init__(self,master):
        print(user_data)
        self.master = master
        self.master.title('Manager system!')
        self.master.geometry('400x400')
        manager_window = tk.Frame(self.master, width=400, height=300)
        manager_window.pack()
        def add_student():
            self.var_usr_sno =tk.StringVar()
            self.var_usr_name =tk.StringVar()
            self.var_usr_sex =tk.StringVar()
            self.var_usr_age =tk.IntVar()
            self.var_usr_pwd =tk.StringVar()
            self.var_usr_pwd.set('默认密码为:123456')

            def ok():
                usr_sno = self.var_usr_sno.get()
                usr_name = self.var_usr_name.get()
                usr_sex = self.var_usr_sex.get()
                usr_age = self.var_usr_age.get()
                usr_pwd = self.var_usr_pwd.get()
                if usr_sno=='' or usr_name == '' or usr_sex=='' or usr_age=='':
                    tk.messagebox.showinfo(message='please input completely!')
                elif usr_pwd=='':
                    tk.messagebox.showinfo(message='please input password or use default password!')
                if usr_pwd=='默认密码为:123456':
                    usr_pwd ='123456'
                sql = 'SELECT * FROM STUDENT where sno = \'%s\''%(usr_sno)
                res = pd.read_sql_query(sql,con=engine)
                if res.empty:
                    try:
                        sql = 'insert into STUDENT(sno, sname, ssex, sage, spwd) values (\'%s\', \'%s\', \'%s\', \'%s\', \'%s\')'%(usr_sno,usr_name,usr_sex,usr_age,usr_pwd)
                        print(sql)
                        res = pd.read_sql_query(sql,con=engine)
                    except:
                        tk.messagebox.showinfo(message='添加成功！')
                        add_student_window.destroy()
                else:
                    tk.messagebox.showinfo(message='学号已存在，添加失败！')

            def cancel():
                add_student_window.destroy()

            add_student_window = tk.Toplevel(manager_window)
            add_student_window.geometry('450x250')
            add_student_window.title('Add Student')
            tk.Label(add_student_window, text='学号:  ').grid(row=0, column=0)
            tk.Label(add_student_window, text='姓名:  ').grid(row=1, column=0)
            r1 = tk.Radiobutton(add_student_window,text='Man',variable=self.var_usr_sex,value='Man').grid(row=2,column=0)
            r2 = tk.Radiobutton(add_student_window,text='Woman',variable=self.var_usr_sex,value='Woman').grid(row=2,column=1)
            tk.Label(add_student_window, text='年龄:  ').grid(row=3,column=0)
            tk.Label(add_student_window, text='密码:  ').grid(row=4,column=0)
            tk.Entry(add_student_window,textvariable=self.var_usr_sno,width=30).grid(row=0,column=1)
            tk.Entry(add_student_window,textvariable=self.var_usr_name,width=30).grid(row=1,column=1)
            tk.Entry(add_student_window,textvariable=self.var_usr_age,width=30).grid(row=3,column=1)
            tk.Entry(add_student_window,textvariable=self.var_usr_pwd,width=30).grid(row=4,column=1)
            tk.Label(add_student_window, text='   ').grid(row=5)
            tk.Label(add_student_window, text='   ').grid(row=6)
            tk.Button(add_student_window,text='确定',command=ok,padx=100).grid(row=7,column=0)
            tk.Button(add_student_window,text='取消',command=cancel,padx=100).grid(row=7,column=1)

        def del_student():
            
            self.del_usr_sno = tk.StringVar()

            del_student_window = tk.Toplevel(manager_window)
            del_student_window.geometry('500x400')
            del_student_window.title('Delete Student')
            sql = 'SELECT * FROM student'
            all_students = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3','4','5']
            treeview = ttk.Treeview(del_student_window,columns=columns,show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.column('5',width=100,anchor='center')
            treeview.heading('1',text='学号')
            treeview.heading('2',text='姓名')
            treeview.heading('3',text='性别')
            treeview.heading('4',text='年龄')
            treeview.heading('5',text='密码')
            count = 0
            for i in all_students.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3],i[4]))
                count += 1
            def del_ok():
                del_sno = self.del_usr_sno.get()
                sql = 'SELECT * FROM STUDENT WHERE sno = \'%s\'' %(del_sno)
                res = pd.read_sql_query(sql,con=engine)
                if res.empty:
                    tk.messagebox.showinfo(message='该学生不存在，请重新输入')
                else:
                    try:
                        sql='delete from STUDENT where sno = \'%s\''%(del_sno)
                        res = pd.read_sql_query(sql,con=engine)
                    except:
                        tk.messagebox.showinfo(message='删除成功！')
                        del_student_window.destroy()

            def del_cancel():
                del_student_window.destroy()

            tk.Label(del_student_window,text="请输入你想删除的学生学号： ").pack()
            tk.Entry(del_student_window,textvariable=self.del_usr_sno,width=30).pack()
            tk.Button(del_student_window,text='确认删除',command=del_ok,padx=80).pack()
            tk.Button(del_student_window,text='取消',command=del_cancel,padx=92).pack()
            tk.Label(del_student_window,text="所有学生信息：",pady=10).pack()
            treeview.pack()

        def alt_student():
            self.alt_usr_sno =tk.StringVar()
            self.alt_usr_name =tk.StringVar()
            self.alt_usr_sex =tk.StringVar()
            self.alt_usr_age =tk.IntVar()
            self.alt_usr_pwd =tk.StringVar()

            alt_student_window = tk.Toplevel(manager_window)
            alt_student_window.geometry('500x500')
            alt_student_window.title('Alter Student')
            sql = 'SELECT * FROM student'
            all_students = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3','4','5']
            treeview = ttk.Treeview(alt_student_window,columns=columns,show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.column('5',width=100,anchor='center')
            treeview.heading('1',text='学号')
            treeview.heading('2',text='姓名')
            treeview.heading('3',text='性别')
            treeview.heading('4',text='年龄')
            treeview.heading('5',text='密码')
            count = 0
            for i in all_students.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3],i[4]))
                count += 1
            def alt_ok():
                usr_sno = self.alt_usr_sno.get()
                usr_name = self.alt_usr_name.get()
                usr_sex = self.alt_usr_sex.get()
                usr_age = self.alt_usr_age.get()
                usr_pwd = self.alt_usr_pwd.get()
                if usr_sno=='' or usr_name== '' or usr_sex=='' or usr_age=='' or usr_pwd=='':
                    tk.messagebox.showinfo(message='please input completely')
                else:
                    sql = 'SELECT * FROM student where sno = \'%s\''%(usr_sno)
                    res = pd.read_sql_query(sql,con=engine)
                    if res.empty:
                        tk.messagebox.showinfo(message='该学生不存在，请重新输入')
                    else:
                        sql = 'update STUDENT set SNAME=\'%s\',SSEX=\'%s\',SAGE=%d,SPWD=\'%s\'where sno=\'%s\''%(usr_name,usr_sex,usr_age,usr_pwd,usr_sno)
                        conn = cx_Oracle.connect('blime/pls@localhost/orcl')
                        cur = conn.cursor()
                        cur.execute(sql)
                        tk.messagebox.showinfo(message='修改成功！')
                        cur.close()
                        conn.commit()
                        conn.close()
                        alt_student_window.destroy()
                            
            def alt_cancel():
                alt_student_window.destroy()
            tk.Label(alt_student_window,text="请输入你想修改的学生信息： ").pack()
            tk.Label(alt_student_window,text="学号：").pack()
            tk.Entry(alt_student_window,textvariable=self.alt_usr_sno,width=30).pack()
            tk.Label(alt_student_window,text="姓名: ").pack()
            tk.Entry(alt_student_window,textvariable=self.alt_usr_name,width=30).pack()
            tk.Label(alt_student_window,text="性别: ").pack()
            r1 = tk.Radiobutton(alt_student_window,text='Man',variable=self.alt_usr_sex,value='Man').pack()
            r2 = tk.Radiobutton(alt_student_window,text='Woman',variable=self.alt_usr_sex,value='Woman').pack()
            tk.Label(alt_student_window,text="年龄: ").pack()
            tk.Entry(alt_student_window,textvariable=self.alt_usr_age,width=30).pack()
            tk.Label(alt_student_window,text="密码:  ").pack()
            tk.Entry(alt_student_window,textvariable=self.alt_usr_pwd,width=30).pack()
            tk.Button(alt_student_window,text='确认修改',command=alt_ok,padx=80).pack()
            tk.Button(alt_student_window,text='取消',command=alt_cancel,padx=92).pack()
            tk.Label(alt_student_window,text="所有学生信息：",pady=10).pack()
            treeview.pack()

        def add_teacher():
            pass
        def del_teacher():
            pass
        def alt_teacher():
            pass
        def entry_grade():
            entry_grade_window = tk.Toplevel(manager_window)
            entry_grade_window.geometry('600x600')
            entry_grade_window.title('Entry grade')
            self.ent_usr_grade = tk.IntVar()
            self.ent_usr_sno = tk.StringVar()
            self.ent_usr_cname = tk.StringVar()
            tk.Label(entry_grade_window,text='添加学生成绩').pack()
            tk.Label(entry_grade_window,text='学号：').pack()
            tk.Entry(entry_grade_window,textvariable=self.ent_usr_sno,width=80).pack()
            tk.Label(entry_grade_window,text='课程名： ').pack()
            tk.Entry(entry_grade_window,textvariable=self.ent_usr_cname,width=80).pack()
            tk.Label(entry_grade_window,text='成绩: ').pack()
            tk.Entry(entry_grade_window,textvariable=self.ent_usr_grade,width=80).pack()
            isnull_data = pd.Series()
            def entry_ok():
                usr_sno = self.ent_usr_sno.get()
                usr_grade = self.ent_usr_grade.get()
                usr_cname = self.ent_usr_cname.get()
                if usr_sno=='' or usr_grade=='' or usr_cname=='':
                    tk.messagebox.showinfo(message='请填写完整')
                else:
                    if usr_sno not in isnull_data['sno'].to_numpy():
                        tk.messagebox.showinfo(message='学生不存在或者成绩已录入')
                    elif usr_cname not in isnull_data['cname'].to_numpy():
                        tk.messagebox.showinfo(message='课程不存在或者成绩已录入')
                    else:
                        try:
                            sql = 'update curriculum set sgrade = \'%d\' where sno = \'%s\' and cno in (select cno from course where cname=\'%s\')'%(usr_grade,usr_sno,usr_cname)
                            res = pd.read_sql_query(sql,con=engine)
                        except:
                            tk.messagebox.showinfo(message='ok')
                            entry_grade_window.destroy()
            tk.Button(entry_grade_window,text='添加',command=entry_ok,padx=100).pack()
            tk.Label(entry_grade_window,text='未录入成绩列表：').pack()
            sql = 'select Student.sno,Student.sname,course.cname,curriculum.sgrade from STUDENT,COURSE,CURRICULUM where curriculum.sgrade is null and curriculum.sno=Student.sno and curriculum.cno=course.cno'
            isnull_data = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3','4']
            treeview = ttk.Treeview(entry_grade_window,columns=columns,show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.heading('1',text='学号')
            treeview.heading('2',text='学生')
            treeview.heading('3',text='课程名')
            treeview.heading('4',text='成绩')
            
            count = 0
            for i in isnull_data.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3]))
                count += 1
            treeview.pack()
            tk.Label(entry_grade_window,text='已录入成绩列表：').pack()
            sql = 'select Student.sno,Student.sname,course.cname,curriculum.sgrade from STUDENT,COURSE,CURRICULUM where curriculum.sgrade is not null and curriculum.sno=Student.sno and curriculum.cno=course.cno'
            notnull_data = pd.read_sql_query(sql,con=engine)
            treeview = ttk.Treeview(entry_grade_window,columns=columns,show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.heading('1',text='学号')
            treeview.heading('2',text='学生')
            treeview.heading('3',text='课程名')
            treeview.heading('4',text='成绩')
            count = 0
            for i in notnull_data.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3]))
                count += 1
            
            treeview.pack()

        tk.Label(manager_window,text='学生管理',pady=10).pack()
        tk.Button(manager_window,text='添加学生信息',command=add_student,padx=80).pack()
        tk.Button(manager_window,text='删除学生信息',command=del_student,padx=80).pack()
        tk.Button(manager_window,text='修改学生信息',command=alt_student,padx=80).pack()
        tk.Label(manager_window,text='教师管理',pady=10).pack()
        tk.Button(manager_window,text='添加教师信息',command=add_teacher,padx=80).pack()
        tk.Button(manager_window,text='删除教师信息',command=del_teacher,padx=80).pack()
        tk.Button(manager_window,text='修改教师信息',command=alt_teacher,padx=80).pack()
        tk.Label(manager_window,text='教务管理',pady=10).pack()
        tk.Button(manager_window,text='录入课程成绩',command=entry_grade,padx=80).pack()                   


class teacher():
    def __init__(self,master):
        print(user_data)
        self.master = master
        teacher_window = tk.Frame(self.master,width=450, height=300)
        teacher_window.pack()
        self.master.title('Teacher system!')
        self.master.geometry('600x200')
        tk.Label(teacher_window, text='教师信息',anchor='center',pady=10).grid(row=0, column=1)
        tk.Label(teacher_window, text='教工号:  '+user_data['tno'].values).grid(row=1,column=0)
        tk.Label(teacher_window, text='教师名:  '+user_data['tname'].values).grid(row=1,column=1)
        tk.Label(teacher_window, text='职位:  '+user_data['tpos'].values).grid(row=1,column=2)
        tk.Label(teacher_window, text='',pady=15).grid(row=2)
        def tea_student():
            tea_student_window = tk.Toplevel(teacher_window)
            tea_student_window.geometry('500x300')
            tea_student_window.title(user_data['tname'].values+'的学生')
            sql = 'select Student.sno,Student.sname,course.cno,course.cname,curriculum.sgrade from Student,COURSE,TEACHER,CURRICULUM where course.cno=curriculum.cno and course.tno = teacher.tno and Student.sno=curriculum.sno and teacher.tno = \'%s\''%(str(user_data['tno'].values).split('\'')[1])
            tea_stu = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3','4','5']
            treeview = ttk.Treeview(tea_student_window,columns=columns,
                                    show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.column('5',width=100,anchor='center')

            treeview.heading('1',text='学号')
            treeview.heading('2',text='学生名字')
            treeview.heading('3',text='班级号')
            treeview.heading('4',text='课程名字')
            treeview.heading('5',text='成绩')

            
            count = 0
            for i in tea_stu.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3],i[4]))
                count += 1
                
            treeview.pack()
            tk.Label(tea_student_window,text='一共有 '+ str(len(set(tea_stu['sno'])))+ ' 个学生').pack()
            tk.Label(tea_student_window,text='负责 ' + str(len(set(tea_stu['cno'])))+ ' 门课').pack()
        def tea_course():
            tea_student_window = tk.Toplevel(teacher_window)
            tea_student_window.geometry('300x300')
            tea_student_window.title(user_data['tname'].values+'的课表')
            sql = 'select cno,cname,ccredit from course where tno=\'%s\''%(str(user_data['tno'].values).split('\'')[1])
            tea_cou = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3']
            treeview = ttk.Treeview(tea_student_window,columns=columns,
                                    show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名称')
            treeview.heading('3',text='学分')
            
            count = 0
            for i in tea_cou.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2]))
                count += 1
                
            treeview.pack()
            tk.Label(tea_student_window,text='负责 ' + str(len(set(tea_cou['cno'])))+ ' 门课').pack()
            tk.Label(tea_student_window,text='总共 ' + str(tea_cou['ccredit'].cumsum().to_numpy()[-1])+ ' 学分').pack()          
        def tea_analyze():
            tea_analyze_window = tk.Toplevel(teacher_window)
            tea_analyze_window.geometry('300x600')
            tea_analyze_window.title(user_data['tname'].values+'的课表')
            tk.Label(tea_analyze_window,text='课程平均分').pack()
            sql = 'select Student.sno,Student.sname,course.cno,course.cname,curriculum.sgrade from Student,COURSE,TEACHER,CURRICULUM where course.cno=curriculum.cno and course.tno = teacher.tno and Student.sno=curriculum.sno and teacher.tno = \'%s\''%(str(user_data['tno'].values).split('\'')[1])
            tea_ana = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3']
            treeview = ttk.Treeview(tea_analyze_window,columns=columns,
                                    show='headings',height=6)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名称')
            treeview.heading('3',text='平均分')
            
            count = 0
            avg = tea_ana.groupby(['cno','cname']).mean()
            for i in avg.index:
                treeview.insert("",count,values=(str(i).split('\'')[1],str(i).split('\'')[3],str(avg.loc[i].to_numpy()).split('[')[1].split(']')[0]))
                count += 1
                
            treeview.pack()
            tk.Label(tea_analyze_window,text='课程最高分').pack()
            columns = ['1','2','3']
            treeview = ttk.Treeview(tea_analyze_window,columns=columns,
                                    show='headings',height=6)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=80,anchor='center')
            treeview.column('2',width=80,anchor='center')
            treeview.column('3',width=140,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名称')
            treeview.heading('3',text='学号，姓名，最高分')
            
            count = 0
            avg = tea_ana.groupby(['cno','cname']).max()
            for i in avg.index:
                treeview.insert("",count,values=(str(i).split('\'')[1],str(i).split('\'')[3],str(avg.loc[i].to_numpy()).split('[')[1].split(']')[0]))
                count += 1
                
            treeview.pack()
            tk.Label(tea_analyze_window,text='课程最低分').pack()
            columns = ['1','2','3']
            treeview = ttk.Treeview(tea_analyze_window,columns=columns,
                                    show='headings',height=6)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=80,anchor='center')
            treeview.column('2',width=80,anchor='center')
            treeview.column('3',width=140,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名称')
            treeview.heading('3',text='学号，姓名，最低分')
            
            count = 0
            avg = tea_ana.groupby(['cno','cname']).max()
            for i in avg.index:
                treeview.insert("",count,values=(str(i).split('\'')[1],str(i).split('\'')[3],str(avg.loc[i].to_numpy()).split('[')[1].split(']')[0]))
                count += 1
                
            treeview.pack()
        tk.Button(teacher_window, text='门下学生',command=tea_student,width=25).grid(row=3,column=0)
        tk.Button(teacher_window, text='教师课表',command=tea_course,width=25).grid(row=3,column=1)
        tk.Button(teacher_window, text='统计分析',command=tea_analyze,width=25).grid(row=3,column=2)
      
    
class student():
    def __init__(self, master):
        print(user_data)
        self.master = master
        self.master.title('Student system!')
        self.master.geometry('600x300')
        student_window = tk.Frame(self.master, width=450, height=300)
        student_window.pack()
        sno = str(user_data['sno'].values).split('\'')[1]
        sname = str(user_data['sname'].values).split('\'')[1]
        ssex = str(user_data['ssex'].values).split('\'')[1]
        sage = str(user_data['sage'].values).split('[')[1].split(']')[0]
        tk.Label(student_window,text='Number: '+ sno).place(x=30,y=30)
        tk.Label(student_window,text='Name: '+ sname).place(x=130,y=30)
        tk.Label(student_window,text='Sex: '+ ssex).place(x=230,y=30)
        tk.Label(student_window,text='Age: '+ sage).place(x=330,y=30)
        def select_course():
            select_course_window = tk.Toplevel(student_window)
            select_course_window.geometry('500x400')
            select_course_window.title('select_course')
            sql = 'select course.*,tname from course,teacher where teacher.tno=course.tno and course.cno not in (select cno from curriculum where sno = \'%s\')'%(sno)
            sel_cou = pd.read_sql_query(sql,con=engine)
            columns = ['1','2','3','4','5']
            treeview = ttk.Treeview(select_course_window,columns=columns,
                                    show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.column('5',width=100,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名')
            treeview.heading('3',text='学分')
            treeview.heading('4',text='教师号')
            treeview.heading('5',text='教师名')

            
            count = 0
            for i in sel_cou.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3],i[4]))
                count += 1
            self.sel_cou_cno = tk.StringVar()
            def sel_ok():
                sel_cno = self.sel_cou_cno.get()
                if sel_cno=='':
                    tk.messagebox.showinfo(message='请输入你想选的课的课程号')
                elif sel_cno not in sel_cou['cno'].to_numpy():
                    tk.messagebox.showinfo(message='所选课程号不存在，请重新输入！')
                else:
                    sql = 'insert into curriculum(sno, cno) VALUES (\'%s\',\'%s\')' % (sno,sel_cno)
                    try:
                        res = pd.read_sql_query(sql,con=engine)
                    except:
                        tk.messagebox.showinfo(message='选课成功！')
                        select_course_window.destroy()
            tk.Label(select_course_window,text='请选择你想选的课的课程号').pack()
            tk.Entry(select_course_window,textvariable=self.sel_cou_cno,width=30).pack()
            tk.Button(select_course_window,text='确认选课',command=sel_ok,padx=80).pack()
            tk.Label(select_course_window,text='未选的课程如下，可以按照需要选择').pack()
            treeview.pack()
        def change_pwd():
            def confirm_change_pwd():
                op = old_pwd.get()
                np = new_pwd.get()
                npa = new_pwd_again.get()
                global user_data
                if op == '' or np =='' or npa =='':
                    tk.messagebox.showinfo(message='please input')  
                elif op != user_data['spwd'].values:
                    tk.messagebox.showinfo(message='原始密码错误！')
                elif np != npa:
                    tk.messagebox.showinfo(message='两次密码请保持一致！')
                else:
                    try:
                        print('正在修改数据库')
                        sql = 'update student set spwd = \'%s\' where sno = \'%s\''%(npa, sno)
                        pd.read_sql_query(sql,con=engine)
                    except:
                        print('修改后---')
                        sql = 'select * from student where sno = \'%s\''%(sno)
                        user_data = pd.read_sql_query(sql,con=engine)
                        print(user_data)
                        tk.messagebox.showinfo(message='修改成功')
                        change_pwd_window.destroy()
                    
            def cancel_change_pwd():
                change_pwd_window.destroy()

            change_pwd_window = tk.Toplevel(student_window)
            change_pwd_window.geometry('350x200')
            change_pwd_window.title('Change Password')
            tk.Label(change_pwd_window,text='原始密码：     ').place(x=30, y=30)
            tk.Label(change_pwd_window,text='新密码：       ').place(x=30, y=60)
            tk.Label(change_pwd_window,text='确认新密码：   ').place(x=30, y=90)
            old_pwd=tk.StringVar()
            new_pwd=tk.StringVar()
            new_pwd_again=tk.StringVar()
            tk.Entry(change_pwd_window,textvariable=old_pwd).place(x=90,y=30)
            tk.Entry(change_pwd_window,textvariable=new_pwd,show='*').place(x=90,y=60)
            tk.Entry(change_pwd_window,textvariable=new_pwd_again,show='*').place(x=90,y=90)
            tk.Button(change_pwd_window,text='确认',command=confirm_change_pwd).place(x=90,y=120)
            tk.Button(change_pwd_window,text='取消',command=cancel_change_pwd).place(x=180,y=120)

        def personal():
            personal_window = tk.Toplevel(student_window)
            personal_window.geometry('200x200')
            personal_window.title('personal information')
            tk.Label(personal_window,text='Number: '+ sno).place(x=30,y=30)
            tk.Label(personal_window,text='Name: '+ sname).place(x=30,y=60)
            tk.Label(personal_window,text='Sex: '+ ssex).place(x=30,y=90)
            tk.Label(personal_window,text='Age: '+ sage).place(x=30,y=120)

        def query_course():
            query_course_window = tk.Toplevel(student_window)
            query_course_window.geometry('500x200')
            query_course_window.title('query course')
            course_data=pd.read_sql_query('select curriculum.cno,course.cname,course.ccredit,teacher.tname,curriculum.sgrade from curriculum,course,teacher where curriculum.sno=\'%s\' and curriculum.cno=course.cno and course.tno =teacher.tno'%(sno),con=engine)
            columns = ['1','2','3','4','5']
            treeview = ttk.Treeview(query_course_window,columns=columns,
                                    show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=treeview.yview)
            treeview.configure(yscrollcommand=vsb.set)
            treeview.column('1',width=100,anchor='center')
            treeview.column('2',width=100,anchor='center')
            treeview.column('3',width=100,anchor='center')
            treeview.column('4',width=100,anchor='center')
            treeview.column('5',width=100,anchor='center')

            treeview.heading('1',text='课程号')
            treeview.heading('2',text='课程名')
            treeview.heading('3',text='学分')
            treeview.heading('4',text='教师')
            treeview.heading('5',text='成绩')
            
            count = 0
            Total_credit = 0.0
            for i in course_data.to_numpy():
                treeview.insert("",count,values=(i[0],i[1],i[2],i[3],i[4]))
                count += 1
                Total_credit += i[2]
                
            treeview.pack()

        def query_credits():
            Total_credit =pd.read_sql_query('select sum(course.ccredit) from curriculum,course,teacher where curriculum.sno=\'%s\' and curriculum.cno=course.cno and course.tno =teacher.tno'%(sno),con=engine)
            tk.messagebox.showinfo(title='Total_credit',message='总学分为：'+str(Total_credit.values).split('[')[2].split(']')[0]+'分')
        tk.Button(student_window,text='选课',command=select_course,padx=100).place(x=100,y=60)
        tk.Button(student_window,text='修改密码',command=change_pwd,padx=88).place(x=100,y=90)
        tk.Button(student_window,text='个人信息查询',command=personal,padx=76).place(x=100,y=120)
        tk.Button(student_window,text='查询选课状况',command=query_course,padx=76).place(x=100,y=150)
        tk.Button(student_window,text='查询总学分',command=query_credits,padx=82).place(x=100,y=180)
        
    

user_data= pd.Series()
root = tk.Tk()
login(root)
root.mainloop()


