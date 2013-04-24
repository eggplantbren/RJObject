import numpy as np
import matplotlib.pyplot as plt

output = np.atleast_2d(np.loadtxt('output.txt'))

plt.ion()
plt.figure()
plt.hold(False)
for i in xrange(0, output.shape[0]):
	m = output[i, 4:104]
	x = output[i, 104:204]
	y = output[i, 204:304]

	x = x[m > 0.]
	y = y[m > 0.]
	m = m[m > 0.]

	if x.size > 0:
		plt.scatter(x, y, s=100.*m/m.max(), alpha=0.5, color='k')
	plt.axis('scaled')
	plt.axis([-1., 1., -1., 1.])
	plt.title('{i}/{N}'.format(i=(i+1), N=output.shape[0]))
	plt.draw()

plt.ioff()
plt.show()
