import Manu

def Test(arg,exp):
    print("hello world")
    Protocol_1.瞬时流量.Value=arg[1]
    Protocol_1.计费标志.Value=arg[2]
    Protocol_1.管道压力.Value=arg[3]
    print("第%s个用例开始"%arg[0])
    print '输入：瞬时流量=%s 计费标志=%s 管道压力=%s' %(arg[1],arg[2],arg[3]) 
    b=Protocol_1.Write()
    print '上报实时数据：%s' %b
    if not b:
        print ("失败")
    else:
        str='请检查待测软件界面输出：'
        str1 = '瞬时流量=%.2f 计费标志=%d 管道压力=%.2f' %(exp[0],exp[1],exp[2])
        show=[]
        show.append(str)
        show.append(str1)
        passed=Manu.Check(show)
        print("测试结果：%s"%passed)
    print("######第%s个测试用例结束#################" %arg[0])

Standard_Test(Test)