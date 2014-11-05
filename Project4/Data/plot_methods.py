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
	filename = sys.argv[i].split('_')
	methods.append(filename[0])
	t1.append(filename[1].split('=')[1])
	t2.append('0.'+filename[2].split('=')[1].split('.')[1])
	t1_string.append(t1[i-1].split('.')[1])
	t2_string.append(t2[i-1].split('.')[1])	
print methods, t1, t2


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
plt.xlabel('Position x')
plt.ylabel('Concentration u')
plt.legend(['Analytical', 'Explicit', 'Implicit', 'Crank-Nicolson'])
#plt.title(methods[0]+', '+methods[1]+', '+methods[2]+' | t = '+t1[0])
plt.title('Implicit, Explicit & Crank-Nicolson | t = '+t1[0], y = 1.02)
plt.savefig('Solution_t='+t1_string[0]+'.png')
plt.show()

plt.figure(2)
plt.plot(x, analytical_t2)
plt.plot(x, expl_t2)
plt.plot(x, impl_t2)
plt.plot(x, CN_t2)
plt.plot(x, np.zeros(len(x)), '--k')
plt.xlabel('Position x')
plt.ylabel('Concentration u')
plt.legend(['Analytical', 'Explicit', 'Implicit', 'Crank-Nicolson'])
#plt.title(methods[0]+', '+methods[1]+', '+methods[2]+' | t = '+t2[0])
plt.title('Implicit, Explicit & Crank-Nicolson | t = '+t2[0], y = 1.02)
plt.savefig('Solution_t='+t2_string[0]+'.png')
plt.show()










