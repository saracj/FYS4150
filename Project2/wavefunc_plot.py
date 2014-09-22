from scitools.std import *
import matplotlib.pyplot as plt

def read_file(filename):
  file = open(filename, 'r')
  u = []
  rho = []
  
  for line in file:
    data = line.split()
    u.append(float(data[1]))
    rho.append(float(data[0]))
    
  file.close()
  u = array(u)
  rho = array(rho)
  return u, rho

files = ["wavefunc_omega1.dat", "wavefunc_omega50.dat", "wavefunc_omega100.dat", "wavefunc_omega500.dat"]

u1, rho1 = read_file(files[0])
u2, rho2 = read_file(files[1])
u3, rho3 = read_file(files[2])
u4, rho4 = read_file(files[3])

plt.figure()
plt.plot(rho1, u1*u1)
plt.plot(rho2, u2*u2)
plt.plot(rho3, u3*u3)
plt.plot(rho4, u4*u4)
plt.plot(rho1, zeros(len(u1)), 'k')
plt.xlabel(r'$ \rho $')
plt.ylabel(r'u($ \rho $)')
plt.title('Wavefunction for different frequencies $\omega_r$')
plt.legend(['$\omega_r$ = 0.01','$\omega_r$ = 0.5','$\omega_r$ = 1', '$\omega_r$ = 5'])
plt.savefig('wave_func.png')
plt.show()