import Manu

def Test(arg,exp):
    print("hello")
    Protocol_1.˲ʱ����.Value=arg[1]
    Protocol_1.�Ʒѱ��.Value=arg[2]
    print ('######��%s������������ʼ#################' %arg[0])
    print ("���룺˲ʱ����=%s,�Ʒѱ�ʶ��%d" %(arg[1],arg[2]))
    b = Protocol_1.Write()
    print ("�ϱ�ʵʱ����:%s"%b)
    if not b:
        print ("�ϱ�����ʧ��...")
    else:
        str='�������������������Ƿ���Ԥ��һ��:'
        str1='�ۼ�����=%.2f, �ۼ������Ʒ�=%.2f'%(exp[0],exp[1])
        show=[]
        show.append(str)
        show.append(str1)
        passed=Manu.Check(show)
    print('######��%s��������������#################' %arg[0])
    
Standard_Test(Test)
        
    