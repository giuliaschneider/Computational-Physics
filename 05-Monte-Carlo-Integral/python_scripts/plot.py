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


def getNumber(s):
    pos_ = s.find('_n')+2
    posEnd = s.find('_L')
    print(s[pos_:posEnd])
    return float(s[pos_:posEnd])

current_dic = os.getcwd()
sub_dic = abspath(join(current_dic, '..', 'results'))
files = [f for f in os.listdir(sub_dic) if "txt" in f]
files = sorted(files,key=getNumber)

print(files)

labels = ["$n=5$", "$n=10$", "$n=20$", "$n=40$","$n=50$"]


def saveplot(fig, filename):
    file_str =  join(sub_dic, 'figures', filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')



def print_all():
    fig = plt.figure(1,(13/2.54,13/2.54))
    ax = fig.add_subplot(1,1,1)

    for i,filename in enumerate(files):
        filename = join(sub_dic,filename)
        print(filename)
        M, Im = np.genfromtxt(filename,delimiter = ",", unpack = True)
        print(Im)
        ax.plot(M, Im,  'o', ms = 4,label= labels[i])
        """
        if i == 1 or i == 2:
            ax.plot(M[0:-1:2],Im[0:-1:2],'o',ms = 4,label=filenames[i])
        elif i == 0:
            ax.plot(M[:1808],Im[:1808],'o',ms = 4,label=filenames[i])
        else:
            ax.plot(M,Im,'o',ms = 4,label=filenames[i])
        """
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlabel("Number of configurations $M$")
        ax.set_ylabel(r"Average distance between particles $<d_{mean}>$")
        #ax.set_ylim(6.65,7.15)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)

    fname = "all_plots"
    print(fname)
    saveplot(fig, fname)

def print_2():
    filename = join("vary_n/",files[3])
    fig = plt.figure(1,(7.5/2.54,7.5/2.54))
    ax = fig.add_subplot(1,1,1)
    M, Im = np.genfromtxt(filename,delimiter = "\t", unpack = True)
    print(M[1808])
    ax.plot(M[:1808],Im[:1808],'o',ms = 4)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("Number of configurations $M$")
    ax.set_ylabel(r"Average distance between particles $<d_{mean}>$")
    ax.set_ylim(6.65,7.15)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    fname = filenames[3]
    print(filename)
    print(fname)

    saveplot(fig, fname)

if __name__ == '__main__':
    print_all()
    #print_5_20()

    #print_2()
