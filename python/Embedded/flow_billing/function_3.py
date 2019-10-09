def Test(arg,exp):
    print("hello")
    Protocol_1.瞬时流量.Value=arg[1]
    print("######第%s个测试用例开始#################"%arg[0])
    print("输入：瞬时流量：%s"%arg[1])
    bool=Protocol_1.Write()
    API.Common.Timer.Normal.Sleep(500)
    b=Protocol_2.Read()
    if not b:
        print("上报-反馈 失败。。。。。。")
    else:
        ret="Yes"
        actual=Protocol_2.瞬时流量报警标志.Value
        if actual !=exp[0]:
            ret="No"
        print("管道压力控制指令【预期值=%s 实际值=%s】"%(exp[0],actual))
        print("测试结果：%s"%ret)

Standard_Test(Test)
              