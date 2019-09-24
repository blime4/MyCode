E = [-13,-12,-11,-10,-9,-8,-7,10,38,39,40,41,42]

for i in range(0,5):
    for a in E:
        Protocol_3.当前室温.value =a
        Protocol_3.Write()
        API.Common.Timer.Normal.Sleep(500)
        print(a)
    if (i==2):
        print("测试5秒没有传感器温度，不显示报警标识")
        API.Common.Timer.Normal.Sleep(5000)
    if(i==3):
        print("测试6秒没有传感器温度，显示报警标识")
        API.Common.Timer.Normal.Sleep(6000)
    if(i==4):
        print("测试4秒没有传感器温度,报警标准不再显示")
        API.Common.Timer.Normal.Sleep(4000)