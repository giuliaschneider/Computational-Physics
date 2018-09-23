import numpy as np
import sys
import os as os
from os.path import isfile, join, dirname, abspath

import matplotlib as mpl
mpl.use("pgf")
pgf_with_custom_preamble = {
    "text.usetex": True,    # use inline math for ticks
    "pgf.rcfonts": False,   # don't setup fonts from rc parameters
}
mpl.rcParams.update(pgf_with_custom_preamble)
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

path = sys.argv[1]


data = np.loadtxt((path))

currentDir = os.getcwd()
resultsDir = abspath(join(currentDir, "../results/figures"))

def saveplot(fig, filename):
    file_str =  join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def square_test():
    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)
    #ax.plot(data[:1000],data[1:1001],'o')
    ax.plot(data[:-1],data[1:],'o')

    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    #ax.set_xlim(0,31)
    #ax.set_ylim(0,31)
    ax.set_xlabel(r"$x_{i}$")
    ax.set_ylabel(r"$x_{i+1}$")
    #fig.text(0.15,0.15,r"$p=2^{31}$, $c=16807$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
    fig.text(0.15,0.15,r"$p=31$, $c=3$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
    ax.legend(loc="lower right", frameon=False, labelspacing=0.05)
    #fig.show()
    saveplot(fig, "1b")

def cube_test():
    fig = plt.figure()
    ax = Axes3D(fig)
    ax.scatter(data[:1000],data[1:1001],data[2:1002],'o')
    ax.view_init(24, 72.5)
    #ax.set_xlim(0.2,0.5)
    ax.set_xlabel(r"$x_{i}$")
    ax.set_ylabel(r"$x_{i+1}$")
    ax.set_zlabel(r"$x_{i+2}$")
    ax.legend(loc="lower right", frameon=False, labelspacing=0.05)
    saveplot(fig, "1c")

def circle():
    fig = plt.figure(1, (4,4))
    ax = fig.add_subplot(1,1,1)
    ax.plot(data[:,0],data[:,1],'o')
    ax.axis('off')
    #ax.xaxis.set_ticks_position("bottom")
    #ax.yaxis.set_ticks_position("left")
    #ax.set_xlim(0.2,0.5)
    #ax.set_xlabel("\$x_{i}\$")
    #ax.set_ylabel("\$x_{i+1}$")
    ax.legend(loc="lower right", frameon=False, labelspacing=0.05)
    saveplot(fig, "2")

if __name__ == '__main__':
    #square_test()
    #cube_test()
    circle()
