import Manu

E = [1,0,1,1,0,0]
for x in E:
    
    抬杆确认信号.cmd.Value=x
    bool=抬杆确认信号.Write()
    API.Common.Timer.Normal.Sleep(500)
    print("抬起信号%s"%x)
    if x:
        str='抬起'
    else:
        str='不抬起'
    show=[]
    show.append(str)
    passed = Manu.Check(show)
