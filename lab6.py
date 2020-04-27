import numpy as np
import matplotlib.pyplot as plt
fig, ax = plt.subplots()


data = np.loadtxt("C:\\Users\\serge\\source\\repos\\lab6\\ans1.txt")
plt.grid()
ax.plot(data[:,0],data[:,1],marker='o')
Z = np.exp(-data[:,0]**2 - data[:,1]**2)
CS = ax.contour(data[:,0],data[:,1], Z)
ax.clabel(CS, inline=1, fontsize=10)
plt.show()
