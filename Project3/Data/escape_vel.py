import numpy as np
import sys
import matplotlib.pyplot as plt

def read_file(filename):
  file = open(filename, 'r')
  sun_x = []
  sun_y = []
  
  earth_x = []
  earth_y = []
  
  for line in file:
    data = line.split()
    if len(data) > 4 or len(data) < 4:
      print "Data file needs to contain the positions of only the Sun and earth! (x_sun, y_syn, x_earth, y_earth)"
    
    sun_x.append(float(data[0]))
    sun_y.append(float(data[1]))
    
    earth_x.append(float(data[2]))
    earth_y.append(float(data[3]))
    
  file.close()
  
  sun_x = np.array(sun_x)
  sun_y = np.array(sun_y)
  
  earth_x = np.array(earth_x)
  earth_y = np.array(earth_y)
  
  return sun_x, sun_y, earth_x, earth_y
  


if len(sys.argv) < 3 or len(sys.argv) > 3:
  print "Need to specify filename of data files for verlet and RK4! (In that order)"

# Read in filenames in command line (sys.argv[0] is the .py-file)
File_verlet = sys.argv[1]

string_split1 = File_verlet.split('_')

if len(string_split1) != 5:
  print "Filename needs to be on the form Data_escape-vel_method_time-step.dat or .txt" 

run_time = string_split1[3]
init_vel = string_split1[2]

if len(string_split1[4].split('.')) < 3: # Filenames jump to "scientific" notation a for dt < 10^-4
  string_dt = string_split1[4].split('.')[0]
  im_title = r'Earth orbit with initial velocity $v_0 = $'+init_vel+' [AU/year], $\Delta$ t = '+string_dt+'. Run time = '+run_time
else:
  string_dt = string_split1[4].split('.')[1]
  im_title = r'Earth orbit with initial velocity $v_0 = $'+init_vel+' [AU/year], $\Delta$ t = 0.'+string_dt+'. Run time = '+run_time



Vsun_x, Vsun_y, Vearth_x, Vearth_y = read_file(File_verlet)

plt.figure(1)
plt.figure(1)
plt.plot(Vearth_x, Vearth_y, '-b')
plt.plot(Vsun_x, Vsun_y ,'or')
plt.xlabel('Distance [AU]')
plt.ylabel('Distance [AU]')
plt.title(im_title, y = 1.02, fontsize=13)
plt.legend(['Earth', 'Sun'])
plt.axis('equal')
#plt.axis([-1.5, 1.5, -1.5, 1.5])
plt.savefig('escape-vel_'+init_vel+'_'+string_dt+'_'+run_time+'.png')
plt.show()