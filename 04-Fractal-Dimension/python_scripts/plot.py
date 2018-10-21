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





def saveplot(fig, filename):
    file_str =  abspath(join("..", "results", "figures", filename))
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def print_all_plots():

    currentDir = os.getcwd()
    resultsDir = abspath(join(currentDir, "..", "results"))
    files = [f for f in os.listdir(resultsDir) if ".txt" and "1000" in f]
    files.sort()


    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)
    filepath = join(resultsDir, files[1])
    R, data = np.genfromtxt(filepath,delimiter = "\t", unpack = True)
    nData = R.size
    lower = int(0.01*nData)
    upper = int(0.3*nData)
    print(nData)
    print(R[lower])
    print(R[upper])
    c = np.polyfit(np.log(R[lower:upper]), np.log(data[lower:upper]),1)[0]
    print(c)
    c_string = r"$d_f={:.3f}$".format(c)
    fig.text(0.35,0.6,c_string, transform=ax.transAxes)
    ax.loglog(R,data,'o')
    ax.loglog(R[lower:upper],(R[lower:upper])**c,'k--',linewidth=0.5)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("$log(R)$")
    ax.set_ylabel("$log(M(R))$")
    #ax.set_xlim(0,50)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    del data

    fname = files[1][:-4]
    saveplot(fig, fname)

    fig = plt.figure(2,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)
    filepath = join(resultsDir, files[0])

    data = np.loadtxt(filepath)
    print(len(data))
    R = 1/np.arange(1,data.size+1)
    nData = R.size
    lower = int(0.002*nData)
    upper = int(0.15*nData)
    print(nData)
    print(R[lower])
    print(R[upper])
    c = np.polyfit(np.log(R[lower:upper]), np.log(data[lower:upper]),1)[0]
    print(c)
    c_string = r"$d_f={:.3f}$".format(c)
    fig.text(0.35,0.6,c_string, transform=ax.transAxes)
    ax.loglog(R,data,'o')
    ax.loglog(R[lower:upper],R[lower:upper]**c*150000,'k--',linewidth=0.5)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel(r"$log(1/ \epsilon)$")
    ax.set_ylabel(r"$log(N(\epsilon))$")
    #ax.set_xlim(0,50)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    del data

    fname = files[0][:-4]
    saveplot(fig, fname)





if __name__ == '__main__':
    print_all_plots()
