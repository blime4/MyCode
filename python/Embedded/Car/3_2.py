import Manu
def Test(arg,exp):
      seekresult=CH_232_2.Clear()
      seekresult=CH_232_1.Clear()
      
      
      bool=������բ.Write()
      ETC������Ϣ.type.Value=arg[1]
      ETC������Ϣ.balence.Value=arg[2]
      bool=ETC������Ϣ.Write()

      time=API.Common.Timer.Normal.Now()
      while True:
         bool=ETC���.Read()
         if bool==True:
               break
      
     # bool=���ָ��.Read()
      time1=API.Common.Timer.Normal.Now()
      time2=time1-time
      print(time2)
      print(time2.Milliseconds)
      ###
      show=[]
      str='Ԥ���������ѣ�%d'%(exp[0])
      str1='Ԥ��������շѣ�%d'%(exp[1])
      show.append(str)
      show.append(str1)
      ok=Manu.Check(show)
      ####
      if ok:
            print('����')
      else:
            print("������")
     
   
Standard_Test(Test)
