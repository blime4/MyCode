import Manu

def Test(arg,exp):
    datas=arg[0].split(',')
    l=[]
    for a in datas:
        l.append(int(a,16))
    seekresult=CH_232_2.Clear()
    bool=CH_232_2.Write(l)
    
    show=[]
    str='输入：%s'%s(arg[1])
    show.append(str)
    show.append("是否一致")
    passed=Manu.Check(show)
    
    if passed:
        print("ok")
    else:
        print("不ok")
    

Standard_Test(Test)