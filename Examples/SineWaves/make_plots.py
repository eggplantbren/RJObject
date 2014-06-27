from pylab import *

rc("font", size=14, family="serif", serif="Computer Sans")
rc("text", usetex=True)

posterior_sample = loadtxt('posterior_sample.txt')

hist(posterior_sample[:,1005], 50)
xlabel('Number of Sinusoids $N$', fontsize=14)
ylabel('Number of posterior samples', fontsize=14)
xlim([-0.5, 10.5])
savefig('N_result.pdf', bbox_inches='tight')
show()

