from pylab import *

data = loadtxt('fake_data.txt')
posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))

ion()
for i in xrange(0, posterior_sample.shape[0]):
  hold(False)
  plot(data[:,0], data[:,1], 'b.')
  hold(True)
  plot(data[:,0], posterior_sample[i, 0:data.shape[0]], 'r')
  draw()
ioff()
show()
