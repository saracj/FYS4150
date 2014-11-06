import numpy as np
import sys
import matplotlib.pyplot as plt


def read_file(filename):
  file = open(filename, 'r')
  x = []
  u_t1 = []
  u_t2 = []  

  for line in file:
    data = line.split()
    
    x.append(float(data[0]))
    u_t1.append(float(data[1]))
    u_t2.append(float(data[2]))
    
  file.close()
  
  x = np.array(x)
  u_t1 = np.array(u_t1)
  u_t2 = np.array(u_t2)

  return x, u_t1, u_t2

methods = []
t1 = []
t2 = []
t1_string = []
t2_string = []
for i in range(1, len(sys.argv)):
	filename = sys.argv[i].split('.')
	methods.append(filename[0])

x, analytical_t1, analytical_t2 = read_file(sys.argv[1]) # Analytical
x, expl_t1, expl_t2 = read_file(sys.argv[2]) # Explicit
x, impl_t1, impl_t2 = read_file(sys.argv[3]) # Implicit
x, CN_t1, CN_t2 = read_file(sys.argv[4]) # Crank-Nicolson

plt.figure(1)
plt.plot(x, analytical_t1)
plt.plot(x, expl_t1)
plt.plot(x, impl_t1)
plt.plot(x, CN_t1)
plt.plot(x, np.zeros(len(x)), '--k')
plt.xlabel('Position x', fontsize=16)
plt.ylabel('Concentration u', fontsize=16)
plt.legend(['Analytical', 'Explicit', 'Implicit', 'Crank-Nicolson'])
plt.title('Implicit, Explicit & Crank-Nicolson, t = 0.05', fontsize=16, y = 1.02)
plt.savefig('Solution1.png')
plt.show()

plt.figure(2)
plt.plot(x, analytical_t2)
plt.plot(x, expl_t2)
plt.plot(x, impl_t2)
plt.plot(x, CN_t2)
plt.plot(x, np.zeros(len(x)), '--k')
plt.xlabel('Position x', fontsize=16)
plt.ylabel('Concentration u', fontsize=16)
plt.legend(['Analytical', 'Explicit', 'Implicit', 'Crank-Nicolson'])
plt.title('Implicit, Explicit & Crank-Nicolson, t = 0.8', fontsize=16, y = 1.02)
plt.savefig('Solution2.png')
plt.show()










