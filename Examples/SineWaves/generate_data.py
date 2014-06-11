from pylab import *

"""
Original example with two phase transations, but they do not interfere
with the posterior. This is here for no reason other than to make sure
the second example is identical to what Courtney has been using.
"""
seed(123)

t = linspace(0., 100., 1001)
y = sin(2.*pi*t/30.) + sin(2.*pi*t/2. + 1.)
sig = 1.
Y = y + sig*randn(y.size)

"""
This one has a phase transition at temperature = 1 :-D
"""

t = linspace(0., 100., 1001)
y = sin(2.*pi*t/30.) + 0.3*sin(2.*pi*t/2. + 1.)
sig = 1.
Y = y + sig*randn(y.size)

data = empty((t.size, 2))
data[:,0], data[:,1] = t, Y

savetxt('fake_data.txt', data)

rc("font", size=14, family="serif", serif="Computer Sans")
rc("text", usetex=True)
plot(t, y, 'r', linewidth=2, label='Noise-free signal')
plot(t, Y, 'bo', alpha=0.4, label='Noisy measurements')
ylim([-5., 5.])
legend(numpoints=1)
xlabel('Time')
ylabel('Signal')
savefig('sinewave_data.pdf', bbox_inches='tight')
show()

