import time,Manu

def Main():
      print 'hello world'
      seekresult=TCP�����_������.Clear()
      ������ָ��.������������ָ��.Value=0x00000000
      bool=������ָ��.Write()
      ������ָ��.������������ָ��.Value=0xFFFFFFFF
      bool=������ָ��.Write()
      #bool=λ����Ϣ.Write()
      t1 = time.time()
      t2 = time.time()
      
      while t2-t1<3:
            #print ������ָ������г���Ϣ.Read()
            
            bool=������ָ������г���Ϣ.Read()
            t2=time.time()
            if bool==false:
                  print '���ص������ʶ��%s' %������ָ������г���Ϣ.��ʶ.Value
                  print '���صĸ��ؽ��:  %s' %������ָ������г���Ϣ.����.Case1.���ֵ.Value
                  if ������ָ������г���Ϣ.����.Case1.���ֵ.Value == 1:
                        print '����״̬�¹���������ͨ��'


Main()