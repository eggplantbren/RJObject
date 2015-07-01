"""
Looking for a method to enhance the probability that 'birth'
proposals have lower amplitude than the prior would suggest.
Let's just sample the prior
"""

import numpy as np
import numpy.random as rng
import matplotlib.pyplot as plt

# Maximum number of components
N_max = 10

# Proposal function just calls the 'add' or 'remove' function
def proposal(state):
  if rng.rand() <= 0.5:
    new = add(state)
  else:
    new = remove(state)
  return new

# Add a component (from the prior, for now)
def add(state):
  if state.size == N_max:
    return state
  return np.hstack([state, rng.rand()])

# Remove a component (just choose one, for now)
def remove(state):
  if state.size == 0:
    return state
  return np.delete(state, rng.randint(state.size))

