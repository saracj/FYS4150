import numpy as np
import matplotlib.pylab as plt
import sys

def read_file(filename):
  file = open(filename, 'r')
  sun_pot = []
  sun_kin = []
  sun_ang = []
  
  earth_pot = []
  earth_kin = []
  earth_ang = []
  
  for line in file:
    data = line.split()
    
    if len(data) > 6 or len(data) < 6:
      print "Data file needs to contain the potential, kinetic and angular momentum of the sun and earth (in that order) --> sun_potentail  sun_kinetic  sun_angular  earth_potential  earth_kinetic  earth_angular"
      
    sun_pot.append(float(data[0]))
    sun_kin.append(float(data[1]))
    sun_ang.append(float(data[2]))
    
    earth_pot.append(float(data[3]))
    earth_kin.append(float(data[4]))
    earth_ang.append(float(data[5]))
    
  file.close()
  
  sun_pot = np.array(sun_pot)
  sun_kin = np.array(sun_kin)
  sun_ang = np.array(sun_ang)
  
  earth_pot = np.array(earth_pot)
  earth_kin = np.array(earth_kin)
  earth_ang = np.array(earth_ang)
  
  return sun_pot, sun_kin, sun_ang, earth_pot, earth_kin, earth_ang


if len(sys.argv) < 3 or len(sys.argv) > 3:
  print "Need to specify filename of data files for verlet and RK4! (In that order)"

# Read in filenames in command line (sys.argv[0] is the .py-file)
File_verlet = sys.argv[1]
File_RK4 = sys.argv[2]

string_split1 = File_verlet.split('_')
string_split2 = File_RK4.split('_')

if len(string_split1) and len(string_split2) != 4:
  print "Filename needs to be on the form Energy_method_time-step.dat" 

run_time_V = string_split1[2]
run_time_R = string_split2[2]

if len(string_split1[3].split('.')) < 3: # Filenames jump to "scientific" notation a for dt < 10^-4
  string_dt_V = string_split1[3].split('.')[0]
  pot_title_sun = r'Potential E of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  pot_title_earth = r'Potential E of earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
  kin_title_sun = r'Kinetic E of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  kin_title_earth = r'Kinetic E of earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
  ang_title_sun = r'Angular momentum of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  ang_title_earth = r'Angular momentum of earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
if len(string_split2[3].split('.')) < 3:
  string_dt_R = string_split2[3].split('.')[0] 
else:
  string_dt_V = string_split1[3].split('.')[1]
  string_dt_R = string_split2[3].split('.')[1]
  pot_title_sun = r'Potential E of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  pot_title_earth = r'Potential E of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  kin_title_sun = r'Kinetic E of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  kin_title_earth = r'Kinetic E of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  ang_title_sun = r'Angular momentum of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  ang_title_earth = r'Angular momentum of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  
  
# Verlet:
sun_potV, sun_kinV, sun_angV, earth_potV, earth_kinV, earth_angV = read_file(File_verlet)

# RK4:
sun_potR, sun_kinR, sun_angR, earth_potR, earth_kinR, earth_angR = read_file(File_RK4)

# Constructing time arrays:

T_V = int(string_split1[2].split('y')[0])
T_R = int(string_split2[2].split('y')[0])

tV = np.linspace(0, T_V, len(sun_potV))
tR = np.linspace(0, T_R, len(sun_potR))

plt.figure(1)
plt.plot(tV, sun_potV, '-b')
plt.plot(tR, sun_potR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Potential Energy $ U = \frac{-G M_{\odot} m_{\mathrm{earth}}}{r}$ [$\mathrm{AU}^2 M_{\odot}^2 \mathrm{yr}^{-2}$]')
plt.title(pot_title_sun)
plt.savefig('sun_pot_dt'+string_dt_V+'.png')
plt.show()

plt.figure(2)
plt.plot(tV, earth_potV, '-b')
plt.plot(tR, earth_potR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Potential Energy $ U = \frac{-G M_{\odot} m_{\mathrm{earth}}}{r}$ [$\mathrm{AU}^2 M_{\odot}^2 \mathrm{yr}^{-2}$]')
plt.title(pot_title_earth)
plt.savefig('earth_pot_dt'+string_dt_V+'.png')
plt.show()

""" Pointless for Sun
plt.figure(3)
plt.plot(tV, sun_kinV, '-b')
plt.plot(tR, sun_kinR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Kinetic Energy $K = \frac{1}{2} m v^2$ [$m_\odot \mathrm{AU}^2 \mathrm{yr}^{-2} $]')
plt.title(kin_title_sun)
plt.savefig('sun_kin_dt'+string_dt_V+'.png')
plt.show()
"""
plt.figure(4)
plt.plot(tV, earth_kinV, '-b')
plt.plot(tR, earth_kinR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Kinetic Energy $K = \frac{1}{2} m v^2$ [$m_\odot \mathrm{AU}^2 \mathrm{yr}^{-2} $]')
plt.title(kin_title_earth)
plt.savefig('earth_kin_dt'+string_dt_V+'.png')
plt.show()

""" Pointless for Sun
plt.figure(5)
plt.plot(tV, sun_angV, '-b')
plt.plot(tR, sun_angR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Angular Momentum L = m \cross \vec v \cross \vec r')
plt.title(ang_title_sun)
plt.savefig('sun_ang_dt'+string_dt_V+'.png')
plt.show()
"""

plt.figure(6)
plt.plot(tV, earth_angV, '-b')
plt.plot(tR, earth_angR, '-g')
plt.xlabel(r'time t [years]')
plt.ylabel(r'Angular Momentum L = m \cross \vec v \cross \vec r')
plt.title(ang_title_earth)
plt.savefig('earth_ang_dt'+string_dt_V+'.png')
plt.show()

