using PyCall
@pyimport matplotlib.pyplot as plt

srand(0)

# Create the data
N_data = 1001
x_data = linspace(-10.0, 10.0, N_data)
y_data = zeros(N_data)
N = 10
for(i in 1:N)
	y_data += -log(1.0 - rand())*exp(-0.5*(x_data - (-10.0 + 20.0*rand())).^2/0.5^2)
end
y_data += 0.3*randn(N_data)

plt.plot(x_data, y_data, "bo")
plt.show()
