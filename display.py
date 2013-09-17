import numpy as np
import matplotlib.pyplot as plt

import os
saveFrames = True # For making movies
if saveFrames:
	os.system('rm Frames/*.png')

output = np.atleast_2d(np.loadtxt('output.txt'))

num_hyperparameters = 4
num_dimensions = output[0, 0]
max_num_components = output[0, 1]

plt.ion()
plt.figure()
plt.hold(False)
for i in xrange(0, output.shape[0]):
	x = output[i, (3 + num_hyperparameters):(3 + num_hyperparameters+max_num_components)]
	y = output[i, (3 + num_hyperparameters + max_num_components):(3 + num_hyperparameters+2*max_num_components)]
	m = output[i, (3 + num_hyperparameters + 2*max_num_components):(3 + num_hyperparameters + 3*max_num_components)]

	x = x[m > 0.]
	y = y[m > 0.]
	m = m[m > 0.]

	if x.size > 0:
		plt.scatter(x, y, s=100.*m/m.max(), alpha=0.5, color='k')
	plt.axis('scaled')
	plt.axis([-1., 1., -1., 1.])
	plt.title('{i}/{N}'.format(i=(i+1), N=output.shape[0]))
	plt.xlabel('$x$', fontsize=20)
	plt.ylabel('$y$', fontsize=20)

	if saveFrames:
		plt.savefig('Frames/' + '%0.4d'%(i+1) + '.png', bbox_inches='tight')
		print('Frames/' + '%0.4d'%(i+1) + '.png')

	plt.draw()

plt.ioff()
plt.show()
