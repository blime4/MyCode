def Test(arg,exp):
    print("hello")
    Protocol_1.˲ʱ����.Value=arg[1]
    print("######��%s������������ʼ#################"%arg[0])
    print("���룺˲ʱ������%s"%arg[1])
    bool=Protocol_1.Write()
    API.Common.Timer.Normal.Sleep(500)
    b=Protocol_2.Read()
    if not b:
        print("�ϱ�-���� ʧ�ܡ�����������")
    else:
        ret="Yes"
        actual=Protocol_2.˲ʱ����������־.Value
        if actual !=exp[0]:
            ret="No"
        print("�ܵ�ѹ������ָ�Ԥ��ֵ=%s ʵ��ֵ=%s��"%(exp[0],actual))
        print("���Խ����%s"%ret)

Standard_Test(Test)
              