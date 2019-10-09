import Manu

def Test(arg,exp):
    print("hello")
    Protocol_1.瞬时流量.Value=arg[1]
    Protocol_1.计费标记.Value=arg[2]
    print ('######第%s个测试用例开始#################' %arg[0])
    print ("输入：瞬时流量=%s,计费标识：%d" %(arg[1],arg[2]))
    b = Protocol_1.Write()
    print ("上报实时数据:%s"%b)
    if not b:
        print ("上报请求失败...")
    else:
        str='请检查待测软件界面的输出是否与预期一致:'
        str1='累计流量=%.2f, 累计流量计费=%.2f'%(exp[0],exp[1])
        show=[]
        show.append(str)
        show.append(str1)
        passed=Manu.Check(show)
    print('######第%s个测试用例结束#################' %arg[0])
    
Standard_Test(Test)
        
    