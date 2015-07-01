import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

from simple import *

state = np.array([])

steps = 10000
N = np.zeros(steps)
x = np.array([])

for i in range(0, steps):
  state = proposal(state)
  x = np.hstack([x, state])
  N[i] = state.size

plt.plot(N)
plt.show()

plt.hist(x, 100)
plt.show()

