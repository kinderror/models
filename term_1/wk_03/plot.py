import numpy as np
import matplotlib.pyplot as plt

data = np.loadtxt('data.txt')
t = data[:,0]
x = data[:,1]
v = data[:,2]
x_th = np.cos(t)
#x = x - x_th
fig, ax = plt.subplots()
ax.plot(t, x - x_th)
#ax.plot(t, x_th)
plt.show()
