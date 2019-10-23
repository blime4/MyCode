import scipy.stats as stats
x =stats.uniform.rvs(size=20)
print(x)

import matplotlib.pyplot as plt
plt.plot(x)
plt.show()

y = stats.norm.rvs(size=20,loc=0,scale=1)
z = stats.poisson.rvs(0.6,loc=0,scale=20)
print(y)
print(z)
plt.plot(y)
plt.plot(z)
plt.show()