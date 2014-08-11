from pylab import *

rc("font", size=16, family="serif", serif="Computer Sans")
rc("text", usetex=True)

x = linspace(0., 100., 1001)

prior = 1./(x + 10.)**2
prior = prior/trapz(prior, x=x)
lik = 0.08*exp(-0.5*(x - 60)**2/10**2)
post = prior*lik
post = post/trapz(post, x=x)

plot(x, prior, 'b', linewidth=3, label='Prior')
plot(x, lik, 'c--', linewidth=2, label='Likelihood')
plot(x, post, 'r', linewidth=3, label='Posterior')
plot(60, 0.08, 'c*', markersize=20, label='``Best fit\'\'')
xlabel(r'$\theta$')
ylabel('Probability Density')
legend(loc='upper right', numpoints=1)
savefig('bayes.pdf', bbox_inches='tight')
show()

x = linspace(-1, 1, 201)
[x, y] = meshgrid(x, x)
y = y[::-1, :]

rsq1 = (x + 0.2)**2 + (y - 0.5)**2
rsq2 = (x - 0.4)**2 + (y - 0.7)**2
rsq3 = (y + 1 - x**2)**2
f1 = exp(-0.5*rsq1/0.05**2)
f2 = exp(-0.5*rsq2/0.03**2)
f3 = exp(-0.5*rsq3/0.02**2)
f4 = exp(-0.5*rsq2/0.3**2)
imshow(-f1 - f2 - f3 - f4, cmap='gray')
xlabel('$x$')
ylabel('$y$')
gca().set_xticks([])
gca().set_yticks([])
savefig('challenges.pdf', bbox_inches='tight')
show()

