import Manu

def Test(arg,exp):
    print('��������%d:�����趨�¶�%d'%(arg[1],arg[0]))
    Protocol_1.Tmp.Value=arg[0]
    Protocol_1.Write()
    API.Common.Timer.Normal.Sleep(1000)
    
    show=[]
    str='ң�����趨�¶�Ϊ:%d,����Ԥ����ʾ�¶�Ϊ��%d'%(arg[0],exp[0])
    show.append(str)
    show.append('�����¶���ʾ�Ƿ���ȷ?')
    passed = Manu.Check(show)
    if(passed):
        print ('������ʾ��Ԥ��һ�£������ж�ͨ��')
    else:
        print ('������ʾ��Ԥ�ڲ�һ�£������жϲ�ͨ��')
    
    if(arg[0]<16 and exp[0]==16 and passed) or (arg[0]>30 and exp[0]==30 and passed) or (16<=arg[0]<=30 and exp[0]==arg[0] and passed):
        print ('���β���ͨ��')
    else:
        print ('���β��Բ�ͨ��')
    CH_232_2.Clear()
    
Standard_Test(Test)