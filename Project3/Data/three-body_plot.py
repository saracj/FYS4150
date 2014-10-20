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

if len(sys.argv) < 3 or len(sys.argv) > 3:
  print "Need to specify filename of data files for verlet and RK4! (In that order)"

# Read in filenames in command line (sys.argv[0] is the .py-file)
File_verlet = sys.argv[1]
File_RK4 = sys.argv[2]

string_split1 = File_verlet.split('_')
string_split2 = File_RK4.split('_')

if len(string_split1) and len(string_split2) != 5:
  print "Filename needs to be on the form Data_three-body_method_Mj_time-step.dat or .txt" 

run_time_V = string_split1[3]
run_time_R = string_split2[3]

#jupiter_mass = string_split1[3]

if len(string_split1[4].split('.')) < 3: # Filenames jump to "scientific" notation a for dt < 10^-4
  string_dt_V = string_split1[4].split('.')[0]
  im_title_V = r'Three-body orbits, Verlet, $\Delta$ t = '+string_dt_V+'. Run time = '+run_time_V
if len(string_split2[4].split('.')) < 3:
  string_dt_R = string_split2[4].split('.')[0] 
  im_title_R = r'Three-body orbits, RK4, $\Delta$ t = '+string_dt_R+'. Run time = '+run_time_R
else:
  string_dt_V = string_split1[4].split('.')[1]
  string_dt_R = string_split2[4].split('.')[1]
  im_title_V = r'Three-body orbits, Verlet, $\Delta$ t = 0.'+string_dt_V+'. Run time = '+run_time_V
  im_title_R = r'Three-body orbits, RK4, $\Delta$ t = 0.'+string_dt_R+'. Run time = '+run_time_R

# Verlet:
Vsun_x, Vsun_y, Vearth_x, Vearth_y, Vjupiter_x, Vjupiter_y = read_file(File_verlet)

# RK4:
Rsun_x, Rsun_y, Rearth_x, Rearth_y, Rjupiter_x, Rjupiter_y= read_file(File_RK4)

T_V = int(string_split1[3].split('y')[0])
T_R = int(string_split2[3].split('y')[0])

tV = np.linspace(0, T_V, len(Vsun_x))
tR = np.linspace(0, T_R, len(Rsun_x))

earth_distR = np.sqrt(Rearth_x**2 + Rearth_y**2)
earth_distV = np.sqrt(Vearth_x**2 + Vearth_y**2)

plt.figure(1)
plt.plot(Vearth_x, Vearth_y, '-b')
plt.plot(Vjupiter_x, Vjupiter_y ,'-g')
plt.plot(Vsun_x, Vsun_y ,'or')
plt.xlabel('Distance [AU]', fontsize=16)
plt.ylabel('Distance [AU]', fontsize=16)
plt.title(im_title_V, y = 1.02, fontsize=16.5)
plt.legend(['Earth', 'Jupiter', 'Sun'])
plt.axis('equal')
#plt.axis([-1.5, 1.5, -1.5, 1.5])
plt.savefig('three-body-moving_verlet_'+string_dt_V+'_'+run_time_R+'.png')
plt.show()

plt.figure(2)
plt.plot(Rearth_x, Rearth_y, '-b')
plt.plot(Rjupiter_x, Rjupiter_y ,'-g')
plt.plot(Rsun_x, Rsun_y ,'or')
plt.xlabel('Distance [AU]',  fontsize=16)
plt.ylabel('Distance [AU]', fontsize=16)
plt.title(im_title_R, y = 1.02, fontsize=16.5)
plt.legend(['Earth', 'Jupiter', 'Sun'])
plt.axis('equal')
#plt.axis([-1.5, 1.5, -1.5, 1.5])
plt.savefig('three-body-moving_RK4_'+string_dt_R+'_'+run_time_R+'.png')
plt.show()