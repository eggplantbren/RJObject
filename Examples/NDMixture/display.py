from pylab import *
import os

data = loadtxt('data.txt')
posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))

ion()

for i in range(0, posterior_sample.shape[0]):
	hold(False)
	plot(data[:,0], data[:,1], 'b.')
	hold(True)

	x = posterior_sample[i, 10:20]
	y = posterior_sample[i, 20:30]
	x = x[x != 0.]
	y = y[y != 0.]

	plot(x, y, 'ro')
	draw()

ioff()
show()

