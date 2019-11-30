from tkinter import *
import tkinter.font as tkfont
import tkinter as tk
from tkinter import ttk
import cx_Oracle
import tkinter.messagebox 


# 数据库操作
import pandas as pd
from sqlalchemy import create_engine
engine = create_engine('oracle+cx_oracle://blime:pls@localhost/orcl')
conn = engine.connect()
# with engine.connect() as conn,conn.begin():
#     data_teacher = pd.read_sql_table('teacher',conn)
#     data_student = pd.read_sql_table('student',conn)
#     data_manager = pd.read_sql_table('manager',conn)

# print(data_teacher['tno'])
# print(data_student['sno'])
# print(data_manager['mno'])


def query_user(usr_name,usr_pwd,usr_pos):
    if usr_name=='' or usr_name=='sno/tno/mno':
        tk.messagebox.showinfo(message='Please enter your username!')
    elif usr_pwd=='':
        tk.messagebox.showinfo(message='Please enter your password!')
    elif usr_pos=='':
        tk.messagebox.showinfo(message='Please choose your position!')
    # conn = cx_Oracle.connect('blime/pls@localhost/orcl')
    if usr_pos=="Teacher":
        sql = "SELECT * FROM teacher WHERE tno = \'" + usr_name + "\'";
        pwd='tpwd'
    elif usr_pos=="Student":
        sql = "SELECT * FROM student WHERE sno = \'" + usr_name + "\'";
        pwd='spwd'
    elif usr_pos=="Manager":
        sql = "SELECT * FROM manager WHERE mno = \'" + usr_name + "\'";
        pwd='mpwd'
    
    user_data = pd.read_sql_query(sql,con=engine)
#     print(user_data)
    if user_data.empty:
        tk.messagebox.showinfo(message='user not found!')
    else:
#         print (user_data[pwd].values)
        if usr_pwd != user_data[pwd].values:
            tk.messagebox.showinfo(message='password error!')
        else:
            print(user_data)

#登录界面
login_window = tk.Tk()
login_window.title('Welcome to perbl system!')
login_window.geometry('450x300')

tk.Label(login_window,text='User name:').place(x=50,y=130)
tk.Label(login_window,text='Password:').place(x=50,y=170)
tk.Label(login_window,text='Position:').place(x=50,y=200)
var_usr_name=tk.StringVar()     #用户名，这里用的是用户的编号
var_usr_name.set('sno/tno/mno')
var_usr_pwd= tk.StringVar()     #密码 
var_usr_pos= tk.StringVar()     #身份,老师/学生/管理员

entry_usr_name = tk.Entry(login_window,textvariable=var_usr_name,width=30)
entry_usr_name.place(x=160,y=130)
entry_usr_pwd = tk.Entry(login_window,textvariable=var_usr_pwd,show='*',width=30)
entry_usr_pwd.place(x=160,y=170)

r1 = tk.Radiobutton(login_window,text='Student',variable=var_usr_pos,value='Student')
r2 = tk.Radiobutton(login_window,text='Teacher',variable=var_usr_pos,value='Teacher')
r3 = tk.Radiobutton(login_window,text='Manager',variable=var_usr_pos,value='Manager')

r1.place(x=160,y=200)
r2.place(x=240,y=200)
r3.place(x=320,y=200)


def usr_login():
    usr_name = var_usr_name.get()
    usr_pwd = var_usr_pwd.get()
    usr_pos = var_usr_pos.get()
    print(usr_name)
    print(usr_pwd)
    print(usr_pos)
    query_user(usr_name,usr_pwd,usr_pos)

def usr_help():
    pass

#login and help button
btn_login = tk.Button(login_window,text='Login',command=usr_login)
btn_login.place(x=170,y=230)
btn_help = tk.Button(login_window,text='Help',command=usr_help)
btn_help.place(x=270,y=230)

login_window.mainloop()

