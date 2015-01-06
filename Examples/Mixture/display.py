from pylab import *
import os

data = loadtxt('galaxies.txt')
posterior_sample = atleast_2d(loadtxt('posterior_sample.txt'))

saveFrames = False # For making movies
if saveFrames:
  os.system('rm Frames/*.png')

x = linspace(0., 50000., 10001)
def mixture(x, params):
  N = int(params[7])
  centers = params[8:18][0:N]
  widths = exp(params[18:28][0:N])
  weights = exp(params[28:38][0:N])
  weights /= weights.sum()

  y = zeros(x.shape)
  for i in xrange(0, N):
    y += weights[i]/widths[i]/sqrt(2.*pi)*exp(-0.5*(x - centers[i])**2/widths[i]**2)

  return y

total = zeros(x.shape)

ion()
for i in xrange(0, posterior_sample.shape[0]):
  hold(False)
  hist(data, 100, alpha=0.5, normed=True)
  hold(True)
  y = mixture(x, posterior_sample[i, :])
  total += y
  plot(x, y, 'r', linewidth=2)
  title("{a} / {b}".format(a=(i+1), b=posterior_sample.shape[0]))
  draw()
  if saveFrames:
    savefig('Frames/' + '%0.4d'%(i+1) + '.png', bbox_inches='tight')
    print('Frames/' + '%0.4d'%(i+1) + '.png')


ioff()
show()

hist(data, 100, alpha=0.5, normed=True)
hold(True)
plot(x, total/posterior_sample.shape[0], 'r', linewidth=2)
show()

