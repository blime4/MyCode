import Manu
import math

def Test(arg,exp):
    seekresult=CH_232_1.Clear()
    print("��������%d"%arg[3])
    
    Protocol_3.��ǰ����.Value=arg[0]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    Protocol_3.��ǰ����.Value=arg[1]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    Protocol_3.��ǰ����.Value=arg[2]
    Protocol_3.Write()
    API.Common.Timer.Normal.Sleep(500)
    
    show=[]
    str = '����Ԥ����ʾΪ��%d'%(exp[0])
    show.append(str)
    passed=Manu.Check(show)
    
    if(passed):
        print ("������ʾ��Ԥ��һ�£������ж�ͨ��")
    else:
        print ("������ʾ��Ԥ�ڲ�һ��,�����жϲ�ͨ��")
        
    assertor = API.Platform.Assertion.Create()
    assertor.API.AddInput("���������¶�",arg[2])
    assertor.API.AddOutput("�ɼ���ʾ�¶�",exp[0],passed)
    
    if(passed):
        print("���β���ͨ��")
        assertor.Pass()
    else:
        print("���β��Բ�ͨ�����������������")
        assertor.Field()
    b=assertor.Commit()
    

Standard_Test(Test)    
    