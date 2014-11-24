import numpy as np
import sys
import matplotlib.pyplot as plt


def read_file(filename):
  file = open(filename, 'r')
  u = []  

  for line in file:
    data = line.split()
    
    u.append(float(data[0]))

  file.close()
  
  u = np.array(u)
  return u
  
filename_gauss = 'Histogram_gaussStepLength.dat'
u = read_file(filename_gauss)

plt.hist(u, bins=100, color='blue', histtype='step')
plt.savefig(filename_gauss.split('.')[0]+'.png')
plt.show()