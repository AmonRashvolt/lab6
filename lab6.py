import numpy as np
import matplotlib.pyplot as plt
fig2=plt.figure()
ax1=plt.subplot('121')
data = np.loadtxt("C:\\Users\\serge\\source\\repos\\lab6\\ans1.txt")
plt.grid()
ax1.plot(data[:,0],data[:,1],marker='o')
plt.show()
