import Manu

def Test(arg,exp):
    print("hello world")
    Protocol_1.˲ʱ����.Value=arg[1]
    Protocol_1.�Ʒѱ�־.Value=arg[2]
    Protocol_1.�ܵ�ѹ��.Value=arg[3]
    print("��%s��������ʼ"%arg[0])
    print '���룺˲ʱ����=%s �Ʒѱ�־=%s �ܵ�ѹ��=%s' %(arg[1],arg[2],arg[3]) 
    b=Protocol_1.Write()
    print '�ϱ�ʵʱ���ݣ�%s' %b
    if not b:
        print ("ʧ��")
    else:
        str='�������������������'
        str1 = '˲ʱ����=%.2f �Ʒѱ�־=%d �ܵ�ѹ��=%.2f' %(exp[0],exp[1],exp[2])
        show=[]
        show.append(str)
        show.append(str1)
        passed=Manu.Check(show)
        print("���Խ����%s"%passed)
    print("######��%s��������������#################" %arg[0])

Standard_Test(Test)