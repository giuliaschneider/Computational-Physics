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


currentDir = os.getcwd()
resultsDir = abspath(join(currentDir, "../results"))



def saveplot(fig, filename):
    file_str =  abspath(join('../results/figures/', filename))
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def print_stats():

    files = [f for f in os.listdir(resultsDir) if "3" in f and "100" in f]
    files.sort()
    ylabels = ["Fraction of samples with percolative cluster", "Average shortest path", "Average time of fire"]
    p = np.linspace(0,1,101);

    for i,filename in enumerate(files):
        filepath = join(resultsDir, filename)
        print(filepath)
        data = np.loadtxt(filepath)
        fig = plt.figure(i,(8.5/2.54,8.5/2.54))
        ax = fig.add_subplot(1,1,1)
        ax.plot(p,data)
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlim(0,1)
        ax.set_xlabel("Occupation probability $p$")
        ax.set_ylabel(ylabels[i])

        fname = filename[:-4]
        saveplot(fig, fname)
        plt.close()
        del data


def print_all_spanningClusters():
    files = [f for f in os.listdir(resultsDir) if "3" in f and "spanningCluster" in f]
    files.sort()

    p = np.linspace(0,1,101);
    legends = ["$N=20$","$N=50$","$N=100$","$N=300$"]
    fig = plt.figure(1,(10/2.54,10/2.54))
    ax = fig.add_subplot(1,1,1)

    for i,filename in enumerate(files):
        filepath = join(resultsDir, filename)
        print(filepath)
        data = np.loadtxt(filepath)
        ax.plot(p,data,label=legends[i])

        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlim(0,1)
        ax.set_xlabel("Occupation probability $p$")
        ax.set_ylabel("Fraction of samples with percolative cluster")
        ax.legend(loc="lower right", frameon=False, labelspacing=0.05)

        fname = "3a_all_spanningCluster"
        saveplot(fig, fname)
        del data



if __name__ == '__main__':
    print_stats()
    print_all_spanningClusters()
