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
        manager_window = tk.Frame(self.master,)
        manager_window.pack()
        self.master.title('Manager system!')
        self.master.geometry('600x300')           
class teacher():
    def __init__(self,master):
        print(user_data)
        self.master = master
        teacher_window = tk.Frame(self.master,)
        teacher_window.pack()
        self.master.title('Teacher system!')
        self.master.geometry('600x300')
class student():
    def __init__(self, master):
        print(user_data)
        self.master = master
        student_window = tk.Frame(self.master,)
        student_window.pack()
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
            pass
        def change_pwd():
            def confirm_change_pwd():
                op = old_pwd.get()
                np = new_pwd.get()
                npa = new_pwd_again.get()
                global user_data
                if op == '' or np =='' or npa =='':
                    tk.messagebox.showinfo(message='请填写完整！')
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
            query_course_window.geometry('400x200')
            query_course_window.title('query course')
            course_data=pd.read_sql_query('select curriculum.cno,course.cname,course.ccredit,teacher.tname from curriculum,course,teacher where curriculum.sno=\'%s\' and curriculum.cno=course.cno and course.tno =teacher.tno'%(sno),con=engine)
            columns = ['1','2','3','4']
            tree = ttk.Treeview(query_course_window,columns=columns,
                                    show='headings',)
            vsb = ttk.Scrollbar(orient='vertical',command=tree.yview)
            tree.configure(yscrollcommand=vsb.set)
            tree.column('1',width=100,anchor='center')
            tree.column('2',width=100,anchor='center')
            tree.column('3',width=100,anchor='center')
            tree.column('4',width=100,anchor='center')

            tree.heading('1',text='课程号')
            tree.heading('2',text='课程名')
            tree.heading('3',text='学分')
            tree.heading('4',text='教师')
            
            count = 0
            Total_credit = 0.0
            for i in course_data.to_numpy():
                tree.insert("",count,value=(i[0],i[1],i[2],i[3]))
                count += 1
                Total_credit += i[2]
                
            tree.pack()

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


