from collections import defaultdict
import prettytable as pt
import numpy as np
import pandas as pd


production = []
Vt = []
Vn = []    
first = defaultdict(set)
follow = defaultdict(set)
data = [[[] for i in range(len(Vt))] for i in range(len(Vn))]
M = pd.DataFrame(data=data,index=Vn,columns=Vt)

def predo:
    start = ''
    tag = True
    with open("./test.txt","r",encoding='utf-8') as gramma:
        for i in gramma:
            pro0 = i.split('-')[0]
            pro1 = i.split('>')[1]
            if tag:
                start = pro0
                tag = False
            if pro0 not in Vn:
                Vn.append(pro0)
            # print (pro1)
            a = pro1.split('|')
            for b in a:
                pro2 = b.split('\n')[0]
                pro3 = pro2[::-1]
                # print(pro3)
                for c in range(len(pro2)):
                    if pro3[c]=="'":
                        Vtemp = pro3[c+1]+pro3[c]
                        # print(Vtemp)
                        c += 1
                        continue
                    if pro3[c].isupper():
                        if pro3[c] not in Vn:
                            Vn.append(pro3[c])
                    else :
                        if pro3[c] not in Vt:
                            Vt.append(pro3[c])
                production.append(pro0+"->"+pro2)
        Vt.append('#')
        print("产生式:\n")
        print(production)
        print("终结符:\n")
        print(Vt)    
        print("非终结符:\n")
        print(Vn)

def getFirst(curVn):
    if first[curVn]!=set():
        return first[curVn]
    l = len(curVn)
    for p in production:
        if l==1 and p[1]=='\'':
            continue
        if p[:l] == curVn:
            # print(p)
            # print(p[l+2:l+3])
            if p[l+2:l+3] in Vt:
                first[curVn].add(p[l+2:l+3])
            else:
                a = p[l+2:l+3]
                if p[l+3:l+4] == '\'':
                    a = str(p[l+2:l+4])
                if first[a]==set():
                    first[curVn]=set(getFirst(a))
                else:
                    first[curVn]=set(first[curVn])
    return first[curVn]


def getFollow(curVn):
    if curVn == start:
        follow[curVn].add('#')
    if curVn != start and follow[curVn]!=set():
        return follow[curVn]
    l = len(curVn)
    for p in production:
        l1 = len(p)
        for i in range(3,l1):
            if p[i]==">":
                continue
            if p[i:i+l]!=curVn:
                continue
            if i == l1-l:
                if p[1]=="'":
                    follow[curVn]=set(getFollow(p[:2]))
                else:
                    follow[curVn]=set(getFollow(p[0]))
                continue
            p1 = p[i+l]
            if p1 in Vt:
                follow[curVn].add(p1)
            elif p1 in Vn:
                follow[curVn]=follow[curVn] | first[p1]
                if p[1]=="'":
                    follow[curVn]=follow[curVn] | set(getFollow(p[:2]))
                else:
                    follow[curVn]=follow[curVn] | set(getFollow(p[0]))
                if 'ε' in follow[curVn]:
                    follow[curVn].discard('ε')
    return follow[curVn]

def getStringFirst(curPro):
    res = []
    for i in range(3,len(curPro)):
        if curPro[i]==">":
            continue
        if curPro[i] in Vt:
            res.append(curPro[i])
            break
        else:
            if curPro[i+1] =="'":
                l = 2
            else:
                l = 1
            if curPro[i:i+l] in Vn:
                if "ε" in first[curPro[i:i+l]]:
                    res.extend(first[curPro])
                else:
                    res.extend(first[curPro[i:i+l]])
                    break
    res = list(set(res))
    return res

def getM():
    for curPro in production:
        A = curPro.split('-')[0]
        stringFirst=getStringFirst(curPro)
        for a in stringFirst:
            if a == "ε":
                continue
            M.loc[A][a].append(curPro)

    for curPro in production:
        A = curPro.split('-')[0]
        stringFirst=getStringFirst(curPro)
        if 'ε' in stringFirst:
            for b in follow[A]:
                M.loc[A][b].append(curPro)
    print('分析表M:')
    print(M)
                
                
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
        return "".join(self.__list)
    
    
def LL1(inputString):
    S = inputString[::-1]
    inStack = Stack()
    inStack.push('#')
    l = len(S)
    for i in range(0,l):
        inStack.push(S[i])

    sigStack = Stack()
    sigStack.push('#')
    sigStack.push(start)

    inTop = inStack.top()
    sigTop = sigStack.top()
    tb = pt.PrettyTable(["序号","符号栈","当前输入符号","输入串","说明"])
    i = 0
    cur = inTop
    while sigTop != '#':
        i += 1
        inTop = inStack.top()
        sigTop = sigStack.top()
        if sigTop == cur:
            sigShow = sigStack.show()
            sigStack.pop()
            inShow = inStack.show()[::-1]
            explain = '匹配,弹出栈顶元素'+cur+'读入下一个输入符号'
            tb.add_row([i,sigShow,cur,inShow,explain])
            inStack.pop()
            cur = inStack.top()
        elif M[inTop][sigTop][0] in production:
            prod = M[inTop][sigTop][0].split('>')[1]
            sigShow=sigStack.show()
            inShow=inStack.show()[::-1]
            sigTop=sigStack.top()
            l1 = len(prod)
            sigShow=sigStack.show()
            sigStack.pop()
            explain=''
            tagg = False
            for ii in range(l1-1):
                if tagg:
                    tagg = False
                    continue
                if prod[l1-ii-1] != "ε":
                    if prod[l1-ii-1]=="'":
                        pp = prod[l1-ii-2:l1-ii]
                        tagg = True
                    else:
                        pp = prod[l1-ii-1]
                    print(pp)
                    sigStack.push(pp)
                    explain = '弹出栈顶符号'+sigTop+',将M['+sigTop+']['+cur+']中的产生式右部逆序压栈'
                else:
                    explain='弹出栈顶符号'+sigTop+'，因M['+sigTop+']['+cur+']中的产生式右部为ε，不压栈'
            tb.add_row([i,sigShow,cur,inShow,explain])
            sigTop = sigStack.top()
        else:
            print("有问题")
        if sigTop == '#':
            i += 1
            tb.add_row([i,'#','#',' ','匹配，分析成功'])
    print(tb)


if __name__=='__main__':
    predo()
    getM()
    inputString="i+i*i"
    LL1(inputString)




