import Manu

def Test(arg,exp):
    print('测试用例%d:命令设定温度%d'%(arg[1],arg[0]))
    Protocol_1.Tmp.Value=arg[0]
    Protocol_1.Write()
    API.Common.Timer.Normal.Sleep(1000)
    
    show=[]
    str='遥控器设定温度为:%d,界面预期显示温度为：%d'%(arg[0],exp[0])
    show.append(str)
    show.append('界面温度显示是否正确?')
    passed = Manu.Check(show)
    if(passed):
        print ('界面显示与预期一致，界面判断通过')
    else:
        print ('界面显示与预期不一致，界面判断不通过')
    
    if(arg[0]<16 and exp[0]==16 and passed) or (arg[0]>30 and exp[0]==30 and passed) or (16<=arg[0]<=30 and exp[0]==arg[0] and passed):
        print ('本次测试通过')
    else:
        print ('本次测试不通过')
    CH_232_2.Clear()
    
Standard_Test(Test)