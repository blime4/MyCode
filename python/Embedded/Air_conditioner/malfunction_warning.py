E = [-13,-12,-11,-10,-9,-8,-7,10,38,39,40,41,42]

for i in range(0,5):
    for a in E:
        Protocol_3.��ǰ����.value =a
        Protocol_3.Write()
        API.Common.Timer.Normal.Sleep(500)
        print(a)
    if (i==2):
        print("����5��û�д������¶ȣ�����ʾ������ʶ")
        API.Common.Timer.Normal.Sleep(5000)
    if(i==3):
        print("����6��û�д������¶ȣ���ʾ������ʶ")
        API.Common.Timer.Normal.Sleep(6000)
    if(i==4):
        print("����4��û�д������¶�,������׼������ʾ")
        API.Common.Timer.Normal.Sleep(4000)