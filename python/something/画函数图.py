import matplotlib.pyplot as plt
import numpy as np
import math

x = np.arange(0.01,1,0.01)
# y = [math.log(a) for a in x]
y_1 = [-math.log(a) for a in x]
y_2 = [math.log(1-a) for a in x]
plt.title("y=log(x)")
# plt.plot(x,y)

plt.plot(x,y_1)
plt.plot(x,y_2)
plt.show()