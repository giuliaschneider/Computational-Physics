import numpy as np
import sys
import os as os

from os.path import isfile, join, dirname, abspath
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
dataDir = abspath(join(root, "..", "results"))
resultsDir = abspath(join(root, "..", "results", "figures"))



def saveplot(fig, filename):
    file_str =  join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def getN(s):
    pos_ = s.find('_n')+2
    #pos_ = s.find('_kbt')
    posEnd = s.find('0_')+1
    return int(s[pos_:posEnd])

def getKbt(s):
    #pos_ = s.find('_kbt')+4
    pos_ = s.find('0_')+2
    posEnd = s.find('.txt')
    return float(s[pos_:posEnd])

def plot_differentSystemSizes():

    labels = ["$k_BT=0.5$", "$k_BT=1$", "$k_BT=1.5$",
              "$k_BT=2$","$k_BT=2.2690$", "$k_BT=3$"]

    kbT = [0.5, 1, 1.5, 2, 2.2690, 3]

    files = [f for f in os.listdir(dataDir) if ".txt" in f]
    files.sort()
    print(files)
    fig = plt.figure(1,(8.3/2.54,8.3/2.54))
    ax = fig.add_subplot(1,1,1)

    for i, file in enumerate(files):


        print(file)
        L = getN(file)
        filename = join(dataDir, file)
        print(filename)

        N = L**2
        E, M = np.genfromtxt(filename,delimiter = ",", unpack = True)
        E /= N
        M /= N
        ax.plot(range(1,M.size+1), M, label = labels[i])

        ax.set_xlabel('Number of system sweeps')

        ax.set_ylabel('Magnetization $M$')
        figlegend = plt.figure(10,(4.3/2.54,4.3/2.54))
        saveplot(fig, "mc_n{}".format(L))

        #figLegend = pylab.figure(figsize = (1.5,1.3))
        # produce a legend for the objects in the other figure
        #pylab.figlegend(*ax.get_legend_handles_labels(), loc = 'upper left', frameon=False)
        #saveplot(figLegend, "legend")

        plt.close(fig)






def printAveragedM():
    # Print averaged
    dataDir = abspath(join(os.getcwd(), "..", "results"))

    files = [f for f in os.listdir(dataDir) if ".txt" in f]
    files.sort()

    kbtVector = np.empty(len(files))
    MVector = np.empty(len(files))
    EVector =  np.empty(len(files))

    for i, file in enumerate(files):
        filepath = join(dataDir, file)
        print(file)
        L = getN(file)
        N = L**2
        kbt = getKbt(file)

        E, M = np.genfromtxt(filepath,delimiter = ",", unpack = True,
                             skip_header=1)
        M /= N
        E /= N
        kbtVector[i] = kbt
        MVector[i] = np.mean(np.abs(M[-300:]))
        EVector[i] = np.mean(np.abs(E[-300:]))

    fig = plt.figure(100,(8.3/2.54,8.3/2.54))
    ax = fig.add_subplot(1,1,1)
    ax.plot(kbtVector, MVector, 'o',)
    ax.set_xlabel('$k_B \cdot T$ [J]')
    ax.set_ylabel('Average magnetization $M$')
    saveplot(fig, "magnetization_n{}".format(L))
    plt.close(fig)

    fig = plt.figure(100,(8.3/2.54,8.3/2.54))
    ax = fig.add_subplot(1,1,1)
    ax.plot(kbtVector, EVector, 'o',)
    ax.set_xlabel('$k_B \cdot T$ [J]')
    ax.set_ylabel('Average energy $E$')
    saveplot(fig, "energy_n{}".format(L))
    plt.close(fig)

if __name__ == '__main__':
    #plot_differentSystemSizes()
    printAveragedM()
