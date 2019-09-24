import Manu
import math

def Test(arg,exp):
    seekresult=CH_232_1.Clear()
    print("测试用例%d"%arg[3])
    
    Protocol_3.当前室温.Value=arg[0]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    Protocol_3.当前室温.Value=arg[1]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    Protocol_3.当前室温.Value=arg[2]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    show=[]
    str = '室温预期显示为：%d'%(exp[0])
    show.append(str)
    passed=Manu.Check(show)
    
    if(passed):
        print ("界面显示与预期一致，界面判断通过")
    else:
        print ("界面显示与预期不一致,界面判断不通过")
        
    assertor = API.Platform.Assertion.Create()
    assertor.API.AddInput("设置室内温度",arg[2])
    assertor.API.AddOutput("采集显示温度",exp[0],passed)
    
    if(passed):
        print("本次测试通过")
        assertor.Pass()
    else:
        print("本次测试不通过，请输入测试问题")
        assertor.Field()
    b=assertor.Commit()
    

Standard_Test(Test)    
    