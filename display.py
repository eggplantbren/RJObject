import numpy as np
import matplotlib.pyplot as plt

output = np.atleast_2d(np.loadtxt('output.txt'))

plt.ion()
plt.figure()
plt.hold(False)
for i in xrange(0, output.shape[0]):
	m = output[i, 9:509]
	x = output[i, 509:1009]
	y = output[i, 1009:1509]

	x = x[m > 0.]
	y = y[m > 0.]
	m = m[m > 0.]

	if x.size > 0:
		plt.scatter(x, y, s=100.*m/m.max(), alpha=0.1, color='k')
	plt.axis('scaled')
	plt.axis([-1., 1., -1., 1.])
	plt.title('{i}/{N}'.format(i=(i+1), N=output.shape[0]))
	plt.xlabel('$x$', fontsize=20)
	plt.ylabel('$y$', fontsize=20)
	plt.draw()

plt.ioff()
plt.show()
