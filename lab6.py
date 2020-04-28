import numpy as np
import matplotlib.pyplot as plt
fig, ax = plt.subplots()
data = np.loadtxt("ans1.txt")
delta = 0.025
x = np.arange(-30.0, 30.0, delta)
y = np.arange(-20.0, 20.0, delta)
X, Y = np.meshgrid(x, y)
#X=data[:,0]
#Y=data[:,1]
Z = 4*X*X-20*X+Y*Y-28*Y+222;
plt.grid()
ax.plot(data[:,0],data[:,1],marker='o')
#Z = np.exp(-data[:,0]**2 - data[:,1]**2)

CS = ax.contour(X,Y, Z)
ax.clabel(CS, inline=1, fontsize=10)
plt.show()
