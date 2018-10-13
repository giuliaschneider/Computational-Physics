import numpy as np
import sys
import os as os
from os.path import isfile, join, dirname, abspath
import matplotlib as mpl
"""
mpl.use("pgf")
pgf_with_custom_preamble = {
    "text.usetex": True,    # use inline math for ticks
    "pgf.rcfonts": False,   # don't setup fonts from rc parameters
}
mpl.rcParams.update(pgf_with_custom_preamble)
"""
from matplotlib import pyplot as plt


currentDir = os.getcwd()
resultsDir = abspath(join(currentDir, "../results/alt"))
files = [f for f in os.listdir(resultsDir) if "CSD_N1000" in f]
files.sort()
legend_labels = ["$p=0.1$", "$p=0.2$", "$p=0.3$", "$p=0.4$", "$p=0.5$", "$p=p_c$","$p=0.6$", "$p=0.7$", "$p=0.8$", "$p=0.9$" ]



def saveplot(fig, filename):
    file_str =  abspath(join("..", "results", "figures", filename))
    print(file_str)
    #fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def print_all_plots():

    fig = plt.figure(1,(6/2.54,6/2.54))
    ax = fig.add_subplot(1,1,1)

    for i,filename in enumerate(files[:5]):
        filepath = join(resultsDir, filename)
        print(filename)
        data = np.loadtxt(filepath)
        data /= 1000**2
        if data.size>50:
            data = data[:]
        print(data.size)

        L = np.arange(1,data.size+1)
        ax.semilogy(L,(data),'o',label=legend_labels[i])
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlabel("Cluster size $s$")
        ax.set_ylabel("$ln(n_s)$")
        #ax.set_xlim(0,50)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)
        del data

    fname = "CSD_N1000_1"
    saveplot(fig, fname)
    plt.close(fig)



    fig = plt.figure(3,(6/2.54,6/2.54))
    ax = fig.add_subplot(1,1,1)

    for i,filename in enumerate(files[6:]):
        filepath = join(resultsDir, filename)
        data = np.loadtxt(filepath)
        data /= 1000**2
        if data.size>50:
            data = data[:]
        L = np.arange(1,data.size+1)
        ax.semilogy(L,(data),'o',label=legend_labels[i+6])
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlabel("Cluster size $s$")
        ax.set_ylabel("$ln(n_s)$")
        #ax.set_xlim(0,50)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)
        del data

    fname = "CSD_N1000_3"
    saveplot(fig, fname)
    plt.close(fig)


def print_pc():
    fig = plt.figure(2,(6/2.54,6/2.54))
    ax = fig.add_subplot(1,1,1)
    filepath = join(resultsDir, files[5])
    data = np.loadtxt(filepath)
    data /= 1000**2
    if data.size>100:
        data = data[:110]
    L = np.arange(1,data.size+1)
    c = np.polyfit(np.log(L), np.log(data),1)[0]

    ax.loglog((L),(data),'o',label=legend_labels[5])
    print(c)
    #print(np.polyval(c,np.log(L[:100])))
    ax.loglog((L),((L)**c/50),'k--',linewidth=0.5)
    print(L[:51]**c)
    c_string = r"$\tau={:.3f}$".format(-c)
    fig.text(0.5,0.5,c_string, transform=ax.transAxes)
    #ax.xaxis.set_tloglogicks_position("bottom")
    #ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("Cluster size $s$")
    ax.set_ylabel("$ln(n_s)$")
    #ax.set_xlim(1,50)
    #ax.set_ylim(1e-6,1)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    fname = "CSD_N1000_2"
    saveplot(fig, fname)
    del data
    plt.show()
    plt.close(fig)



if __name__ == '__main__':
    print_all_plots()
    print_pc()
