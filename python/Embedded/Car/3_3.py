import Manu

E = [1,0,1,1,0,0]
for x in E:
    
    ̧��ȷ���ź�.cmd.Value=x
    bool=̧��ȷ���ź�.Write()
    API.Common.Timer.Normal.Sleep(500)
    print("̧���ź�%s"%x)
    if x:
        str='̧��'
    else:
        str='��̧��'
    show=[]
    show.append(str)
    passed = Manu.Check(show)
