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


