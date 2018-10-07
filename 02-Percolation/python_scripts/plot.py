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
files = [f for f in os.listdir(resultsDir) if "3" in f and "100" in f]
files.sort()
ylabels = ["Fraction of samples with percolative cluster", "Average shortest path", "Average time of fire"]



def saveplot(fig, filename):
    file_str =  abspath(join('../results/figures/', filename))
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def print_all_plots():
    p = np.linspace(0,1,101);

    for i,filename in enumerate(files):

        filepath = join(resultsDir, filename)
        data = np.loadtxt(filepath)
        fig = plt.figure(i,(8.5/2.54,8.5/2.54))
        ax = fig.add_subplot(1,1,1)
        #ax.plot(data[:1000],data[1:1001],'o')
        ax.plot(p,data)

        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlim(0,1)
        #ax.set_ylim(0,31)
        ax.set_xlabel("Occupation probability $p$")
        ax.set_ylabel(ylabels[i])
        #fig.text(0.15,0.15,r"$p=2^{31}$, $c=16807$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
        #fig.text(0.15,0.15,r"$p=31$, $c=3$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
        ax.legend(loc="lower right", frameon=False, labelspacing=0.05)
        #fig.show()
        fname = filename[:-4]
        saveplot(fig, fname)
        del data

def print_all_spanningClusters():
    p = np.linspace(0,1,101);
    legends = ["$N=20$","$N=50$","$N=100$","$N=300$"]
    fig = plt.figure(1,(10/2.54,10/2.54))
    ax = fig.add_subplot(1,1,1)

    for i,filename in enumerate(files):
        filepath = join(resultsDir, filename)
        data = np.loadtxt(filepath)
        #ax.plot(data[:1000],data[1:1001],'o')
        ax.plot(p,data,label=legends[i])

        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlim(0,1)
        #ax.set_ylim(0,31)
        ax.set_xlabel("Occupation probability $p$")
        ax.set_ylabel("Fraction of samples with percolative cluster")
        #fig.text(0.15,0.15,r"$p=2^{31}$, $c=16807$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
        #fig.text(0.15,0.15,r"$p=31$, $c=3$", transform=ax.transAxes, bbox=dict(facecolor='white', alpha=0.9))
        ax.legend(loc="lower right", frameon=False, labelspacing=0.05)
        #fig.show()
        fname = "3a_all_spanningCluster"
        saveplot(fig, fname)
        del data



if __name__ == '__main__':
    print_all_plots()
    #print_all_spanningClusters()
