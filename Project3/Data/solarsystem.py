import numpy as np
import sys
import matplotlib.pyplot as plt

def read_file(filename):
  file = open(filename, 'r')
  object_x = []
  object_y = []
  
  for line in file:
    data = line.split()
    
    object_x.append(float(data[0]))
    object_y.append(float(data[1]))
    
  file.close()
  
  object_x = np.array(object_x)
  object_y = np.array(object_y)

  return object_x, object_y

string1 = sys.argv[1].split('_')
method = string1[1].split('.')[0]
print method

if len(sys.argv) != 10:
  print "Needs data for the Sun and all 8 planets of the solar syste"

sun_x, sun_y = read_file(sys.argv[1])
merc_x, merc_y = read_file(sys.argv[2])
ven_x, ven_y = read_file(sys.argv[3])
earth_x, earth_y = read_file(sys.argv[4])
mars_x, mars_y = read_file(sys.argv[5])
jup_x, jup_y = read_file(sys.argv[6])
sat_x, sat_y = read_file(sys.argv[7])
ur_x, ur_y = read_file(sys.argv[8])
nep_x, nep_y = read_file(sys.argv[9])

im_title = 'Solar system, '+method+' method. Run time = 200 years'

plt.figure(1)
plt.plot(sun_x, sun_y )
plt.plot(merc_x, merc_y)
plt.plot(ven_x, ven_y)
plt.plot(earth_x, earth_y)
plt.plot(mars_x, mars_y)
plt.plot(jup_x, jup_y)
plt.plot(sat_x, sat_y)
plt.plot(ur_x, ur_y)
plt.plot(nep_x, nep_y)
plt.axis('equal')
plt.xlabel('Distance [AU]', fontsize=16)
plt.ylabel('Distance [AU]', fontsize=16)
plt.title(im_title, y = 1.02, fontsize=16.5)
plt.legend(['Sun', 'Mercury', 'Venus', 'Earth', 'Mars', 'Jupiter', 'Saturn', 'Uranus', 'Neptune'])
plt.savefig('solarsystem_2000yr_'+method+'.png')
plt.show()

#RK4 time step: 0.0001 -- Run time 100 years. Impossible to do any sort of reliable calculations
#Verlet time step: 0.0002 -- run time 200 years.

