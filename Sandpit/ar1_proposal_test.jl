using PyCall
using Distributions
@pyimport matplotlib.pyplot as plt

srand(0)
normal = Normal(0.0, 1.0)

# Create the data
N_data = 1001
x_data = linspace(-10.0, 10.0, N_data)
y_data = zeros(N_data)
sig_data = 0.3
N = 10
for(i in 1:N)
	y_data += -log(1.0 - rand())*exp(-0.5*(x_data - (-10.0 + 20.0*rand())).^2/0.2^2)
end
y_data += sig_data*randn(N_data)


function log_likelihood(params::Array{Float64, 2})
	println(min(params), " ", max(params))
	y_model = zeros(N_data)
	for(i in 1:N)
		y_model += -log(1.0 - params[1, 1])*exp(-0.5*(x_data - (-10.0 + 20.0*params[1, 2])).^2/0.2^2)
	end

	return (-0.5*sum((y_data - y_model).^2/sig_data^2), y_model)
end

function ar1_proposal(params::Array{Float64, 2})
	theta = 10.0^(-6.0*rand())*2.0*pi
	n = cdf(normal, params)
	proposal = cos(theta)*n + sin(theta)*randn(size(params))
	proposal = quantile(normal, proposal)
	return proposal
end

steps = 100000
skip = 10

params = rand(N, 2)
logl = log_likelihood(params)[1]

for(i in 1:steps)
	proposal = ar1_proposal(params)
	logl_proposal = log_likelihood(proposal)[1]
	if(rand() <= exp(logl_proposal - logl))
		params = proposal
		logl = logl_proposal 
	end

	if(rem(i, skip) == 0)
		println(i, "/", steps)
	end
end

