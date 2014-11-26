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
filename_const = 'Histogram_constStepLength.dat'
u_gauss = read_file(filename_gauss)
u_const = read_file(filename_const)


plt.hist(u_const, bins=50, color='green')
plt.title('Particle concentration (constant step length)')
plt.xlabel(r'Position $x$')
plt.ylabel(r'Consentration $u(x)$')
plt.savefig(filename_const.split('.')[0]+'.png')
plt.show()

plt.hist(u_gauss, bins=100, color='blue', histtype='step')
plt.title('Particle concentration (gaussian random step length)')
plt.xlabel(r'Position $x$')
plt.ylabel(r'Consentration $u(x)$')
plt.savefig(filename_gauss.split('.')[0]+'.png')
plt.show()
