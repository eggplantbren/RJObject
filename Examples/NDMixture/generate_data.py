from pylab import *

seed(0)

data = randn(1000, 2)
data[0:500, 0] += 1.
data[0:500, 1] += 2.
data[500:, :] *= 0.5
data[500:, 0] += 3.
data[500:, 1] += 4.

savetxt('data.txt', data)
plot(data[:,0], data[:,1], 'b.')
show()

