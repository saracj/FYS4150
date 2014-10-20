import numpy as np
import sys
import matplotlib.pyplot as plt

def read_file(filename):
  file = open(filename, 'r')
  sun_x = []
  sun_y = []
  
  earth_x = []
  earth_y = []
  
  jupiter_x = []
  jupiter_y = []
  
  for line in file:
    data = line.split()
    if len(data) > 6 or len(data) < 6:
      print "Data file needs to contain the positions of only the Sun, earth and jupiter! (x_sun, y_syn, x_earth, y_earth, x_jupiter, y_jupiter)"
    
    sun_x.append(float(data[0]))
    sun_y.append(float(data[1]))
    
    earth_x.append(float(data[2]))
    earth_y.append(float(data[3]))
    
    jupiter_x.append(float(data[4]))
    jupiter_y.append(float(data[5]))
    
  file.close()
  
  sun_x = np.array(sun_x)
  sun_y = np.array(sun_y)
  
  earth_x = np.array(earth_x)
  earth_y = np.array(earth_y)
  
  jupiter_x = np.array(jupiter_x)
  jupiter_y = np.array(jupiter_y)
  
  return sun_x, sun_y, earth_x, earth_y, jupiter_x, jupiter_y

if len(sys.argv) < 2 or len(sys.argv) > 2:
  print "Need to specify filename of data files for Three-Body Problem"

# Read in filenames in command line (sys.argv[0] is the .py-file)
File_verlet = sys.argv[1]

string_split1 = File_verlet.split('_')

if len(string_split1) != 4:
  print "Filename needs to be on the form Data_three-body_time-step.dat or .txt" 

run_time = string_split1[2]

if len(string_split1[3].split('.')) < 3: # Filenames jump to "scientific" notation a for dt < 10^-4
  string_dt = string_split1[3].split('.')[0]
  im_title = r'Three body solar system $\Delta$ t = '+string_dt+'. Run time = '+run_time
else:
  string_dt = string_split1[3].split('.')[1]
  im_title = r'Three body solar system $\Delta$ t = 0.'+string_dt+'. Run time = '+run_time

# Verlet:
sun_x, sun_y, earth_x, earth_y, jupiter_x, jupiter_y = read_file(File_verlet)

T = int(string_split1[2].split('y')[0])

tV = np.linspace(0, T, len(sun_x))

earth_dist = np.sqrt(earth_x**2 + earth_y**2)

plt.figure(1)
plt.plot(earth_x, earth_y, '-b')
plt.plot(jupiter_x, jupiter_y, '-g')
plt.plot(sun_x, sun_y ,'or')
plt.xlabel('Distance [AU]')
plt.ylabel('Distance [AU]')
plt.title(im_title, y = 1.02, fontsize=15)
plt.legend(['Earth', 'Jupiter', 'Sun'])
plt.axis('equal')
#plt.axis([-1.5, 1.5, -1.5, 1.5])
plt.savefig('three-body_'+string_dt+'_'+run_time+'.png')
plt.show()
