from pylab import *

posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))
data = loadtxt('Data/test_image.txt')
sig = loadtxt('Data/test_sigma.txt')

ion()
hold(False)
for i in xrange(0, posterior_sample.shape[0]):
	img = posterior_sample[i, 0:200**2].reshape((200, 200))
	subplot(1, 2, 1)
	imshow(img)
	title('Model {i}'.format(i=i))
	subplot(1, 2, 2)
	sigma = sqrt(sig**2 + posterior_sample[i,-2]**2)
	imshow((img - data)/sigma)
	title('Standardised Residuals')
	draw()

ioff()
show()

