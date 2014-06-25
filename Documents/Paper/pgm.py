"""
PGM for the general problem using daft (http://daft-pgm.org/)
"""

import matplotlib
from matplotlib import rc
rc("font", family="serif", size=12)
rc("text", usetex=True)
matplotlib.rcParams['text.latex.preamble']=[r"\usepackage{amsmath}"]

import daft

pgm = daft.PGM([5., 4.], origin=[-2.5, -1.5])

# Create the nodes
pgm.add_node(daft.Node('alpha', r'$\boldsymbol{\alpha}$', 0., 2.))
pgm.add_node(daft.Node('x', r'$\mathbf{x}_i$', 0., 0.))
pgm.add_node(daft.Node('data', r'$\mathcal{D}$', 2., 0., observed=True))
pgm.add_node(daft.Node('N', r'$N$', -2., 0.))
pgm.add_node(daft.Node('hidden', r'', -1., 0., scale=0, plot_params={'alpha':0}))

# Add the edges
pgm.add_edge('alpha', 'x')
pgm.add_edge('x', 'data')
pgm.add_edge('N', 'hidden')

# Add the plates
pgm.add_plate(daft.Plate([-1., -1., 2., 2.], label=r'Objects $i=1, ..., N$'))

pgm.render()
pgm.figure.savefig("pgm.eps")
pgm.figure.savefig("pgm.pdf")
pgm.figure.savefig('pgm.png')


