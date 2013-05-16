from pylab import *

N = 5000

# Parameters
q = 0.5

# Defines Radial profile
def R(u):
	return -log(1. - u)

# The uniforms
u1 = rand(N)
u2 = rand(N)

# The actual positions
x = R(u1)/sqrt(q)*cos(2.*pi*u2)
y = R(u1)*sqrt(q)*sin(2.*pi*u2)

plot(x, y, 'k.', markersize=1)
axis('equal')
xlabel('$x$')
ylabel('$y$')
show()


