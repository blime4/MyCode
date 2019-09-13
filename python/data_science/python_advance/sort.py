x = [4,1,2,3]
y = sorted(x)
print(y)
print(x)

#通过绝对值对列表元素从最大到最小排序
x = sorted([-4,1,-2,3],key=abs,reverse=True)
print(x)

