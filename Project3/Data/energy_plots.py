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
  pot_title_sun = r'Potential E, $U/U_{max}$, of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  pot_title_earth = r'Potential E, $U/U_{max}$, of Earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
  kin_title_sun = r'Kinetic E, $K/K_{max}$, of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  kin_title_earth = r'Kinetic E, $K/K_{max}$, of Earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
  ang_title_sun = r'Angular momentum, $\left| \vec{L} \right| / \left| \vec{L} \right|_{max}$, of Sun for RK4 and Verlet, $\Delta$t = '+string_dt_V
  ang_title_earth = r'Angular momentum, $\left| \vec{L} \right| / \left| \vec{L} \right|_{max}$, of Earth for RK4 and Verlet, $\Delta$t = '+string_dt_V
if len(string_split2[3].split('.')) < 3:
  string_dt_R = string_split2[3].split('.')[0] 
else:
  string_dt_V = string_split1[3].split('.')[1]
  string_dt_R = string_split2[3].split('.')[1]
  pot_title_sun = r'Potential E, $U/U_{max}$, of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  pot_title_earth = r'Potential energy, $U/U_{max}$, of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  E_title_earth = r'Energy plot of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  kin_title_sun = r'Kinetic E, $K/K_{max}$, of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  kin_title_earth = r'Kinetic E, $K/K_{max}$, of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  ang_title_sun = r'Angular momentum, $\left| \vec{L} \right| / \left| \vec{L} \right|_{max}$, of Sun for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  ang_title_earth = r'Angular momentum, $\left| \vec{L} \right| / \left| \vec{L} \right|_{max}$, of Earth for RK4 and Verlet, $\Delta$t = 0.'+string_dt_V
  
  
# Verlet:
sun_potV, sun_kinV, sun_angV, earth_potV, earth_kinV, earth_angV = read_file(File_verlet)

# RK4:
sun_potR, sun_kinR, sun_angR, earth_potR, earth_kinR, earth_angR = read_file(File_RK4)

# Constructing time arrays:

T_V = int(string_split1[2].split('y')[0])
T_R = int(string_split2[2].split('y')[0])

tV = np.linspace(0, T_V, len(sun_potV))
tR = np.linspace(0, T_R, len(sun_potR))

"""
font = {'family' : 'normal',
        'weight' : 'bold',
        'size'   : 12}

plt.rc('font', **font)
"""
"""
plt.figure(1)
plt.plot(tV, sun_potV/max(sun_potV), '-b')
plt.plot(tR, sun_potR/max(sun_potR), '-g')
#plt.ylim([-0.001, 0.007])
plt.xlabel(r'time t [years]')
plt.ylabel(r'Potential Energy $ U = \frac{-G M_{\odot} m_{\mathrm{earth}}}{r}$ [$\mathrm{AU}^2 M_{\odot}^2 \mathrm{yr}^{-2}$]')
plt.title(pot_title_sun)
plt.legend(['Verlet','RK4'])
plt.savefig('sun_pot_dt'+string_dt_V+'.png')
plt.show()

/max(earth_potV)
/max(earth_potR)
/max(earth_kinV)
/max(earth_kinR)

plt.figure(2)
plt.plot(tV, earth_angV/max(earth_angV), '-b')
plt.plot(tR, earth_angR/max(earth_angR), '-g')
#plt.ylim([187*10**(-7), 190*10**(-7)])
plt.xlabel(r'time t [years]')
plt.ylabel(r'Angular Momentum $\vec{L} = m \vec{v} \times \vec{r}$')
plt.title(ang_title_earth)
plt.legend(['Verlet','RK4'])
plt.savefig('earth_ang_dt'+string_dt_V+'.png')
plt.show()
"""

plt.figure(3)
plt.subplot(211)
plt.plot(tV, earth_potV, '-b')
plt.plot(tR, earth_potR, '-g')
#plt.ylim([0.995, 1.08])
plt.ylabel(r'$ U = \frac{-G M_{\odot} m_{\mathrm{earth}}}{r}$', fontsize = 25)
plt.legend(['Verlet','RK4'])

plt.title(E_title_earth, y = 1.02, fontsize=20)

plt.subplot(212)
plt.plot(tV, earth_kinV, '-b')
plt.plot(tR, earth_kinR, '-g')
#plt.ylim([ 0.92, 1.008])
plt.xlabel(r'time t [years]')
plt.ylabel(r'$K = \frac{1}{2} m v^2$', fontsize = 25)
plt.legend(['Verlet','RK4'])


#plt.savefig('earth_energy_dt'+string_dt_V+'.png')
plt.show()
