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
File_RK4 = sys.argv[2]

string_split1 = File_verlet.split('_')
string_split2 = File_RK4.split('_')

if len(string_split1) and len(string_split2) != 4:
  print "Filename needs to be on the form Data_method_time-step.dat or .txt" 

run_time_V = string_split1[2]
run_time_R = string_split2[2]

if len(string_split1[3].split('.')) < 3: # Filenames jump to "scientific" notation a for dt < 10^-4
  string_dt_V = string_split1[3].split('.')[0]
  im_title_V = r'Earth orbit around sun, Verlet method, $\Delta$ t = '+string_dt_V+'. Run time = '+run_time_V
  rad_title = r'Distance from Earth to Sun vs time, $\Delta t$ = '+string_dt_V
if len(string_split2[3].split('.')) < 3:
  string_dt_R = string_split2[3].split('.')[0] 
  im_title_R = r'Earth orbit around sun, RK4, $\Delta$ t = '+string_dt_R+'. Run time = '+run_time_R
else:
  string_dt_V = string_split1[3].split('.')[1]
  string_dt_R = string_split2[3].split('.')[1]
  im_title_V = r'Earth orbit around sun, Verlet method, $\Delta$ t = 0.'+string_dt_V+'. Run time = '+run_time_V
  im_title_R = r'Earth orbit around sun, RK4, $\Delta$ t = 0.'+string_dt_R+'. Run time = '+run_time_R
  rad_title = r'Distance from Earth to Sun vs time, $\Delta t$ = 0.'+string_dt_V

# Verlet:
Vsun_x, Vsun_y, Vearth_x, Vearth_y = read_file(File_verlet)

# RK4:
Rsun_x, Rsun_y, Rearth_x, Rearth_y = read_file(File_RK4)

T_V = int(string_split1[2].split('y')[0])
T_R = int(string_split2[2].split('y')[0])

tV = np.linspace(0, T_V, len(Vsun_x))
tR = np.linspace(0, T_R, len(Rsun_x))

earth_distR = np.sqrt(Rearth_x**2 + Rearth_y**2)
earth_distV = np.sqrt(Vearth_x**2 + Vearth_y**2)

plt.figure(1)
plt.plot(Vearth_x, Vearth_y, '-b')
plt.plot(Vsun_x, Vsun_y ,'or')
plt.xlabel('Distance [AU]')
plt.ylabel('Distance [AU]')
plt.title(im_title_V, y = 1.02, fontsize=15)
plt.legend(['Earth', 'Sun'])
plt.axis('equal')
plt.axis([-1.5, 1.5, -1.5, 1.5])
plt.savefig('sun_earth_verlet_'+string_dt_V+'_'+run_time_R+'.png')
plt.show()

plt.figure(2)
plt.plot(Rearth_x, Rearth_y, '-b')
plt.plot(Rsun_x, Rsun_y ,'or')
plt.xlabel('Distance [AU]')
plt.ylabel('Distance [AU]')
plt.title(im_title_R, y = 1.02)
plt.legend(['Earth', 'Sun'])
plt.axis('equal')
plt.axis([-1.5, 1.5, -1.5, 1.5])
#plt.savefig('sun_earth_RK4_'+string_dt_R+'_'+run_time_R+'.png')
plt.show()

"""
plt.figure(3)
plt.plot(tV, earth_distV/max(earth_distV), '-b')
plt.plot(tR, earth_distR/max(earth_distR), '-g')
plt.xlabel('time [years]')
plt.ylabel('Distance, [AU]')
plt.title(rad_title)
plt.legend(['Verlet','RK4'])
plt.savefig('sun_earth_dist_'+string_dt_V+'.png')
plt.show()
"""