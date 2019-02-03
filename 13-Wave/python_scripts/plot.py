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
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import gridspec

def getNumber(s):
    pos_ = s.find('_t')+2
    postxt = s.find('.')
    return float(s[pos_:postxt])


current_dic = os.getcwd()
files = [f for f in os.listdir(current_dic) if ".txt" in f]
files = sorted(files, key=getNumber)

#files = sorted(files,key=getNumber)

a = 0
b = 20

def saveplot(fig, filename):
    file_str =  join(dirname(dirname(current_dic)), 'report/figures/') + filename
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def plot_potential():

    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)

    for i, filename in enumerate(files):
        data = np.loadtxt(filename)
        x = np.linspace(a,b,data.size)
        ax.plot(x,data,label = "$t={}".format(getNumber(filename)))


    #ax.xaxis.tick_top()
    #ax.xaxis.set_ticks_position("top")
    #ax.yaxis.set_ticks_position("left")
    #ax.yaxis.set_ticks(np.arange(0, 1.2, 0.25))
    ax.set_xlabel("$x$")
    ax.set_ylabel("$u$")
    #ax.set_xlim(0,11)
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5), frameon=False, labelspacing=0.05)
    #fig.colorbar(cs)
    fname = filename[:-4]
    saveplot(fig, fname)
    plt.close(fig)




if __name__ == '__main__':
    plot_potential()
    print(files)
