E = [1,2,3,4,5,6,7,8,9,10]
for i in range(0,5):
      for a in E:
            Protocol_3.当前室温.Value=a
            bool=Protocol_3.Write()
            print a
            API.Common.Timer.Normal.Sleep(500)
      if(i==1):
            API.Common.Timer.Normal.Sleep(5000)
            print("5秒没有接收到数据，不报警")
      if(i==2):
            API.Common.Timer.Normal.Sleep(5500)
            print("6秒，报警")
      if(i==3):
            API.Common.Timer.Normal.Sleep(6000)
            print("6.5秒，报警")
      if(i==4):
            API.Common.Timer.Normal.Sleep(4000)
            print("4秒，不报警")