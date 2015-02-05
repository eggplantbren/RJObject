from pylab import *

seed(0)

# True surface brightness profile would be a circular gaussian at the origin

N = 100
u = randn(N)
v = randn(N)
intensity = exp(-0.5*u**2 - 0.5*v**2)
sigma = 0.01*ones(N)

data = empty((N, 4))
data[:,0] = u
data[:,1] = v
data[:,2] = intensity
data[:,3] = sigma

savetxt('fake_data.txt', data)


