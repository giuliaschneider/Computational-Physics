import numpy as np
import sys
import os as os
from os.path import abspath, basename, dirname, isfile, join

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


root = os.getcwd()
dataDir = abspath(join(root, "..", "results"))
resultsDir = abspath(join(root, "..", "results", "figures"))
print(resultsDir)

files = [f for f in os.listdir(dataDir) if ".txt" in f]

def saveplot(fig, filename):
    file_str =  join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def plot_potential():
    for i, file in enumerate(files):
        filename = join(dataDir, file)
        data = np.loadtxt(filename)
        N = int(np.sqrt(data.size))
        print(N)

        data = data.reshape(N,N)
        extent = 0,1,1,0

        fig = plt.figure(i,(8.5/2.54,8.5/2.54))
        ax = fig.add_subplot(1,1,1)
        ax.set_axis_off()
        cs = ax.imshow(data,extent=extent)
        #ax.xaxis.tick_top()
        #ax.xaxis.set_ticks_position("top")
        #ax.yaxis.set_ticks_position("left")
        #ax.yaxis.set_ticks(np.arange(0, 1.2, 0.25))
        #fig.colorbar(cs)
        fname = basename(filename[:-4])
        saveplot(fig, fname)
        plt.close(fig)




if __name__ == '__main__':
    plot_potential()
