from collections import defaultdict
import prettytable as pt
import numpy as np
import pandas as pd

#vt终结符
Vt=['+','*','(',')','i','#','epsilon']
#vn非终结符
Vn=["E","E'","T","T'","F"]
#产生式
production=[]
#拆分文法中的或。例如：把文法中A->B|C切分为A->B和A->C
def splitOr(gramma):
    #列表存放所有产生式  
    for i in gramma:
        i=i.split(' ')
        # print("i:",i)
        #pro1存放每一条产生式，i[0]是产生式左边的符号
        pro1=i[0]
        j=1
        while j<len(i):
            if i[j]=="->":
                break
            j+=1
        j+=1
        
        while j<len(i):

            #去掉换行符
            if i[j][-1]=='\n':
                i[j]=i[j][0:-1]

            if i[j]!='|':
                pro1+=" "+i[j]

            else:
                production.append(pro1.split(' '))
                pro1=i[0]
            j+=1
        production.append(pro1.split(' '))
    return production

#FIRST集和FOLLOW集
first=defaultdict(set)
follow=defaultdict(set)

def getFirst(curVn):
    #只要集合不为空说明已经求过则可以直接返回值即可。
    if first[curVn]!=set():
        return first[curVn]
     # 遍历每个产生式
    for p in production:
        if p[0]==curVn:
            #判断产生式右部第一个字符是否为终结符
            if p[1] in Vt:
                first[curVn].add(p[1])
            elif p[1] in Vn:
                if first[p[1]]==set():
                    #调用getFirst函数
                    first[curVn]=set(getFirst(p[1]))
                else:
                    first[curVn]=set(first[p[1]])
    return first[curVn]

def getFollow(curVn):
    if curVn =='E':
        follow[curVn].add('#')
    if curVn!='E' and follow[curVn]!=set():
        return follow[curVn]
    for p in production:
        length=len(p)
        for i in range(1,length):
            if p[i]!=curVn:
                continue 
            # 如果当前非终结符是产生式右部最后一个符号，则它的FOLLOW集等于产生式左部符号的FOLLOW集。      下一个一定是结束符#
            if i == length-1:              
                follow[curVn]=set(getFollow(p[0]))
                continue
            #后面紧跟的是终结符
            if p[i+1] in Vt:
                follow[curVn].add(p[i+1])
            #后面紧跟的是非终结符
            elif p[i+1] in Vn:               
                follow[curVn]=follow[curVn] | first[p[i+1]]
                follow[curVn]=follow[curVn] | set(getFollow(p[0]))
                #删去epsilon
                if 'epsilon' in follow[curVn]:
                    follow[curVn].discard('epsilon')
    return follow[curVn]

stringFirst=defaultdict(set)

#求一个字符串的first集
def getStringFirst(curPro):
    res=[] 
    for i in range(1,len(curPro)):
        if curPro[i] in Vt:
            res.append(curPro[i])
            break
        elif curPro[i] in Vn:
            if 'epsilon' in first[curPro[i]]:
                res.extend(first[curPro])
            else:
                res.extend(first[curPro[i]])
                break
    #去掉重复的符号
    ress=[]
    for i in res:
        if i not in ress:
            ress.append(i)
    return ress

#构造二维表格，行索引为非终结符Vn，列索引为终结符Vt
data=[[[]for i in range(len(Vt))] for i in range(len(Vn))]
M=pd.DataFrame(data=data,index=Vn,columns=Vt)

#构造分析表
def getM():
    for curPro in production:        
        A=curPro[0]
        stringFirst=getStringFirst(curPro)
        for a in stringFirst:
            if a=='epsilon':                
                continue
            #给分析表相应位置添加产生式
            M.loc[A][a].append(curPro)

    for curPro in production:
        A=curPro[0]
        stringFirst=getStringFirst(curPro)
        #若是空产生式，找产生式左边的FOLLOW集的终结符作为列索引
        if 'epsilon' in stringFirst:
            for b in follow[A]:
                M.loc[A][b].append(curPro)

class Stack(object):
    def __init__(self):
        self.__list = []
    
    def push(self,item):
        self.__list.append(item)

    def pop(self):
        return self.__list.pop()

    def top(self):
        if self.__list:
            return self.__list[-1]
        return None

    def is_empty(self):
        return self.__list == []

    def size(self):
        return len(self.__list)

    def show(self):
        return ''.join(self.__list)

tb=pt.PrettyTable(["符号栈","当前输入符号","输入串","说明"])
#LL1分析器
def LL1(inputString):

    turnString=inputString[::-1]#翻转输入串
    #输入串的栈
    inStack=Stack()
    inStack.push('#')
    len1=len(turnString)
    for i in range(0,len1):
        inStack.push(turnString[i])

    #符号栈初始化
    sigStack=Stack()
    sigStack.push('#')
    sigStack.push('E')

    #输入串的栈顶,即
    inTop=inStack.top()
    #符号栈的栈顶
    sigTop=sigStack.top()

    tb=pt.PrettyTable(["序号","符号栈","当前输入符号","输入串","说明"])

    i=0
    #当前输入符号
    cur=inTop
    while sigTop!='#':
        i+=1
        #输入串的栈顶,即当前输入符号
        inTop=inStack.top()
        #符号栈的栈顶
        sigTop=sigStack.top()

        if sigTop==cur:
            sigShow=sigStack.show()
            sigStack.pop()
            inShow=inStack.show()[::-1]
            explain='匹配，弹出栈顶元素'+cur+'并读入下一个输入符号' 
            tb.add_row([i,sigShow,cur,inShow,explain])

            inStack.pop()
            cur=inStack.top()

        
        #分析表中有
        elif M[inTop][sigTop][0] in production:   
            prod= M[inTop][sigTop][0]  
            sigShow=sigStack.show()
            inShow=inStack.show()[::-1]
            #sigTop记录栈顶元素，弹出栈顶元素
            sigTop=sigStack.top()
            
            len2=len(prod)
            sigShow=sigStack.show()
            sigStack.pop()
            for ii in range(len2-1):
                #逆序压栈
                if prod[len2-ii-1] != 'epsilon':
                    sigStack.push(prod[len2-ii-1])
                    explain='弹出栈顶符号'+sigTop+'，将M['+sigTop+']['+cur+']中的产生式右部逆序压栈'
                    
                #不压栈
                else:
                    explain='弹出栈顶符号'+sigTop+'，因M['+sigTop+']['+cur+']中的产生式右部为epsilon，故不压栈'
            tb.add_row([i,sigShow,cur,inShow,explain])
            
            #sigTop记录栈顶元素
            sigTop=sigStack.top()

        if sigTop=='#':
            i+=1
            tb.add_row([i,'#','#',' ','匹配，分析成功'])
    print(tb)

if __name__=='__main__':

    with open("./test.txt",'r',encoding='utf-8') as gramma:
        productions = splitOr(gramma)
        print('产生式：',productions)

    for curVn in Vn:
        getFirst(curVn)
    print('first集合:',first)
    for curVn in Vn:
        getFollow(curVn)
    print('follow集合：',follow)
    getM()
    print('分析表M:')
    print(M)

    inputString="i+i*i"
    LL1(inputString)
