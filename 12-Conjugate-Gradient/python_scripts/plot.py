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
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import gridspec

def getNumber(s):
    pos_ = s.find('_')
    return float(s[:pos_])


current_dic = os.getcwd()
resultsDir = abspath(join(current_dic, "../results"))
files = [f for f in os.listdir(resultsDir) if ".txt" in f]
#files = sorted(files,key=getNumber)

def saveplot(fig, filename):
    file_str =  join(resultsDir,"figures",filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def plot_potential():
    for i, filename in enumerate(files):
        filename = join(resultsDir, filename)
        data = np.loadtxt(filename)
        N = int(np.sqrt(data.size))
        print(N)

        data = data.reshape(N,N)
        #data = data[::-1,:]
        extent = 0,1,1,0

        fig = plt.figure(i,(8.5/2.54,8.5/2.54))
        ax = fig.add_subplot(1,1,1)
        cs = ax.imshow(data,extent=extent)
        ax.xaxis.tick_top()
        ax.xaxis.set_ticks_position("top")
        ax.yaxis.set_ticks_position("left")
        ax.yaxis.set_ticks(np.arange(0, 1.2, 0.25))
        #ax.set_xlabel("$x$")
        #ax.set_ylabel("$z$")
        #ax.set_xlim(0,11)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)
        fig.colorbar(cs)
        fname = filename[:-4]
        saveplot(fig, fname)
        plt.close(fig)




if __name__ == '__main__':
    plot_potential()
