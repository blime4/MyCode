import Manu
def Test(arg,exp):
      seekresult=CH_232_2.Clear()
      seekresult=CH_232_1.Clear()
      
      
      bool=车辆入闸.Write()
      ETC输入信息.type.Value=arg[1]
      ETC输入信息.balence.Value=arg[2]
      bool=ETC输入信息.Write()

      time=API.Common.Timer.Normal.Now()
      while True:
         bool=ETC输出.Read()
         if bool==True:
               break
      
     # bool=输出指令.Read()
      time1=API.Common.Timer.Normal.Now()
      time2=time1-time
      print(time2)
      print(time2.Milliseconds)
      ###
      show=[]
      str='预期输出（免费）%d'%(exp[0])
      str1='预期输出（收费）%d'%(exp[1])
      show.append(str)
      show.append(str1)
      ok=Manu.Check(show)
      ####
      if ok:
            print('符合')
      else:
            print("不符合")
     
   
Standard_Test(Test)
