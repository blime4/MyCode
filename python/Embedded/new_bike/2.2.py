import time,Manu

def Main():
      print 'hello world'
      seekresult=TCP服务端_服务器.Clear()
      开关锁指令.服务器开关锁指令.Value=0x00000000
      bool=开关锁指令.Write()
      开关锁指令.服务器开关锁指令.Value=0xFFFFFFFF
      bool=开关锁指令.Write()
      #bool=位置信息.Write()
      t1 = time.time()
      t2 = time.time()
      
      while t2-t1<3:
            #print 开关锁指令反馈和行程信息.Read()
            
            bool=开关锁指令反馈和行程信息.Read()
            t2=time.time()
            if bool==false:
                  print '返回的命令标识：%s' %开关锁指令反馈和行程信息.标识.Value
                  print '返回的负载结果:  %s' %开关锁指令反馈和行程信息.负载.Case1.结果值.Value
                  if 开关锁指令反馈和行程信息.负载.Case1.结果值.Value == 1:
                        print '开锁状态下关锁，测试通过'


Main()