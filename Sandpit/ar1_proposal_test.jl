using PyCall
@pyimport matplotlib.pyplot as plt

srand(0)

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
	y_model = zeros(N_data)
	for(i in 1:N)
		y_model += -log(1.0 - params[1, 1])*exp(-0.5*(x_data - (-10.0 + 20.0*params[1, 2])).^2/0.2^2)
	end

	return -0.5*sum((y_data - y_model).^2/sig_data^2)
end

plt.plot(x_data, y_data, "bo")
plt.show()

