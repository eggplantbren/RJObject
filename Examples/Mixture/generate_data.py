from pylab import *

seed(0)

x = randn(100)
x = hstack([x, 2 + randn(100)])
x = hstack([x, 5 + randn(50)])

savetxt('data.txt', x)

hist(x, 100)
show()

