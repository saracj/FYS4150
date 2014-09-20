# -*- coding: utf-8 -*-

from scitools.std import * 
import matplotlib.pyplot as plt
from numpy import polyfit, poly1d

n = array([10, 20, 40, 50, 75, 90, 100, 125, 150, 175, 200, 225, 250, 275, 300])
iterations = array([79, 465, 2452, 3993, 9300, 13462, 16715, 26524, 38377, 52313, \
		    68662, 87175, 107819, 131225, 155691])

fit2 = polyfit(n, iterations, 2)
fit3 = polyfit(n, iterations, 3)

N = linspace(0, 300, 100)

p2 = poly1d(fit2)
p3 = poly1d(fit3)

print "second degree fit (poly1d):"
print p2
print "third degree fit (poly1d):"
print p3

#Relative error:

rel_err = abs(p2(n) - iterations)/abs(iterations)
print "Maximum relative error, eps_max = ", max(rel_err)

figure(1)
plt.plot(n, iterations)
plt.xlabel("$n_{step}$")
plt.ylabel("Number of transformations")
plt.title("Number of transformation vs iterations + best polynomial fit")
plt.plot(n, p2(n), '--r')
#plt.plot(n, p3(n), '-k')
plt.legend(["Dataset","2nd degree fit"])
plt.savefig("iteration_polyfit.png")
plt.show()

figure(2)
plt.plot(n, rel_err)
plt.xlabel("$n_{step}$")
plt.ylabel("Relative error, $\epsilon$ ")
plt.title("Relative error as a function of $n_{step}$")
plt.savefig("rel_err.png")
plt.show()