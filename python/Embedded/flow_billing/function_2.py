def Test(arg,exp):
    print("hello")
    Protocol_1.�ܵ�ѹ��.Value = arg[1]
    print ('######��%s������������ʼ#################' %arg[0])
    print ("���룺�ܵ�ѹ��=%.2f"%arg[1])
    bool=Protocol_1.Write()
    API.Common.Timer.Normal.Sleep(500)
    b=Protocol_2.Read()
    if not b:
        print("�ϱ�-���� ʧ�ܡ�����������")
    else:
        ret='Yes'
        actual=Protocol_2.�ܵ�ѹ������ָ��.Value
        if actual !=exp[0]:
            ret='No'
        print("�ܵ�ѹ������ָ�Ԥ��ֵ=%s ʵ��ֵ=%s��"%(exp[0],actual))
        print("���Խ����%s"%ret)
    print("######��%s��������������#################"%arg[0])

Standard_Test(Test)