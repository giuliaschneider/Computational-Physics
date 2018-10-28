import numpy as np
import sys
import os as os

from os.path import isfile, join, dirname
import matplotlib as mpl
mpl.use("pgf")
pgf_with_custom_preamble = {
    "text.usetex": True,    # use inline math for ticks
    "font.family": "serif",
    "font.serif": [],
    #"pgf.rcfonts": False,   # don't setup fonts from rc parameters
}
mpl.rcParams.update(pgf_with_custom_preamble)
from matplotlib import pyplot as plt

import pylab

root = os.getcwd()

n64 = []
n256 = []
n1024 = []
for path, subdirs, files in os.walk(root):
    for name in files:
        if "n64" in name:
            n64.append(os.path.join(path, name))
        elif "n256" in name:
            n256.append(os.path.join(path, name))
        elif "n1024" in name:
            n1024.append(os.path.join(path, name))

n64.sort()
n256.sort()
n1024.sort()
files = [n64, n256, n1024]
N = [64**2, 256**2, 1024**2]

#print(files)



labels = ["$k_BT=0.5$", "$k_BT=1$", "$k_BT=1.5$",
          "$k_BT=2$","$k_BT=2.2690$", "$k_BT=3$"]

kbT = [0.5, 1, 1.5, 2, 2.2690, 3]
avgE_64 = []
avgE_256 = []
avgE_1024 = []
avgM_64 = []
avgM_256 = []
avgM_1024 = []

fnames = ["magnetization_n64", "magnetization_n256", "magnetization_n1024"]


def saveplot(fig, filename):
    file_str =  join(dirname(dirname(root)), 'report/figures/') + filename
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def plot_all():

    for f, file in enumerate(files):
        fig = plt.figure(f,(8.3/2.54,8.3/2.54))
        ax = fig.add_subplot(1,1,1)
        for i, filename in enumerate(file):
            print(filename)
            E, M = np.genfromtxt(filename,delimiter = ",", unpack = True)
            ax.plot(range(1,M.size+1), M, label = labels[i])
            E /= N[f]
            M /= N[f]
            if "n64" in filename:
                avgE_64.append(np.mean(E[150:]))
                avgM_64.append(np.mean(M[150:]))
            elif "n256" in filename:
                avgE_256.append(np.mean(E[150:]))
                avgM_256.append(np.mean(M[150:]))
            elif "n1024" in filename:
                avgE_1024.append(np.mean(E[150:]))
                avgM_1024.append(np.mean(M[150:]))

        ax.set_xlabel('Number of system sweeps')
        if f !=1:
            ax.set_ylabel('Magnetization $M$')
        figlegend = plt.figure(10,(4.3/2.54,4.3/2.54))
        saveplot(fig, fnames[f])

        figLegend = pylab.figure(figsize = (1.5,1.3))
        # produce a legend for the objects in the other figure
        pylab.figlegend(*ax.get_legend_handles_labels(), loc = 'upper left', frameon=False)
        saveplot(figLegend, "legend")


        plt.close(fig)

    fig = plt.figure(100,(13/2.54,13/2.54))
    ax = fig.add_subplot(1,1,1)
    ax.plot(kbT, avgE_64, 'o-', label = '$n=64$')
    ax.plot(kbT, avgE_256, 'o-', label = '$n=256$')
    ax.plot(kbT, avgE_1024, 'o-', label = '$n=1024$')
    ax.set_xlabel('$k_B \cdot T$ [J]')
    ax.set_ylabel('Average energy $E$ [J]')
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    saveplot(fig, "energy")
    plt.close(fig)

    fig = plt.figure(100,(13/2.54,13/2.54))
    ax = fig.add_subplot(1,1,1)
    ax.plot(kbT, avgM_64, 'o-', label = '$n=64$')
    ax.plot(kbT, avgM_256, 'o-', label = '$n=256$')
    ax.plot(kbT, avgM_1024, 'o-', label = '$n=1024$')
    ax.set_xlabel('$k_B \cdot T$ [J]')
    ax.set_ylabel('Average energy $M$')
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    saveplot(fig, "magnetization")
    plt.close(fig)



if __name__ == '__main__':
    plot_all()
