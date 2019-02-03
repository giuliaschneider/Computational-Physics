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


def getNumber(s):
    pos_ = s.find('_t')+2
    postxt = s.find('.')
    return float(s[pos_:postxt])


def saveplot(fig, filename):
    file_str =  join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')



def plot_potential():
    files = [join(dataDir, f )for f in os.listdir(dataDir) if ".txt" in f]
    files.sort()
    a = 0
    b = 20

    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)

    for i, filename in enumerate(files):
        print(filename)
        data = np.loadtxt(filename)
        x = np.linspace(a,b,data.size)
        ax.plot(x,data,label = "$t={}".format(getNumber(filename)))

    ax.set_xlabel("$x$")
    ax.set_ylabel("$u$")
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5), frameon=False, labelspacing=0.05)
    fname = basename(filename[:-4])
    saveplot(fig, fname)
    plt.close(fig)




if __name__ == '__main__':
    plot_potential()
