# coding:utf-8
def Main():
      print 'Hello world'
      import time
      seekresult=TCP�����_������.Clear()
      ������ָ��.������������ָ��.Value = 0xFFFFFFFF #�ȹ���
      bool=������ָ��.Write()
    #   ������ָ������г���Ϣ.BlockRead()
      ������ָ��.������������ָ��.Value = 0x00000000 #����ָ��
      bool=������ָ��.Write()
      time0=time.time()
      while 1:
            bool = ������ָ������г���Ϣ.Read()
            #print ������ָ������г���Ϣ.Read()
           # print ������ָ������г���Ϣ.����.Case1.���ֵ.Value
            if bool and ������ָ������г���Ϣ.����.Case1.���ֵ.Value == 0:
                  print '����״̬�¿���������ͨ��'
                  break
            time1=time.time()
            if time1-time0>2:
                 print '����״̬�¿��������Բ�ͨ��'
                 break
            
           # print time1-time0    
      
      seekresult=TCP�����_������.Clear()
      ������ָ��.������������ָ��.Value = 0x00000000#����ָ��
      bool=������ָ��.Write()
      time0=time.time()
      while 1:
            bool = ������ָ������г���Ϣ.Read()
            print ������ָ������г���Ϣ.Read()
            # print ������ָ������г���Ϣ.����.Case1.���ֵ.Value            
            if bool and ������ָ������г���Ϣ.����.Case1.���ֵ.Value == 0:
                  print '����״̬�¿���������ͨ��'
                  print ������ָ������г���Ϣ
                  break
            time1=time.time()
            if time1-time0>2:
                 print '����״̬�¿��������Բ�ͨ��'
                 break
            
            #print time1-time0    
            

Main()