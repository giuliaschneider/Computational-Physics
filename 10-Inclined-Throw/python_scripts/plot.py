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
    pos_ = s.find('_')
    return float(s[:pos_])


current_dic = os.getcwd()
files = [f for f in os.listdir(current_dic) if "txt" in f]
#files = sorted(files,key=getNumber)


alphas = np.zeros(len(files))
gammas = np.zeros(len(files))
xs = np.zeros(len(files))

def saveplot(fig, filename):
    file_str =  join(dirname(dirname(current_dic)), 'report/figures/') + filename
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def print_test():
    data = np.loadtxt(files[0])
    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)

    ax.plot(data[1,:],data[2,:],'o')
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("$x$")
    ax.set_ylabel("$z$")
    #ax.set_xlim(0,11)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    fname = "test"
    saveplot(fig, fname)
    plt.close(fig)


def print_all_plots():
    for i,filename in enumerate(files):
        print(filename)
        data = np.loadtxt(filename)
        pos_alpha = filename.find("alpha")
        pos_ = filename[pos_alpha+6:].find('_')+pos_alpha + 6
        alphas[i]=float(filename[pos_alpha+6:pos_])
        gammas[i]=float(filename[filename.find("gamma")+6:filename.find("gamma")+9])
        xs[i] = data[1,-1]

        fig = plt.figure(i,(8.5/2.54,8.5/2.54))
        ax = fig.add_subplot(1,1,1)

        ax.plot(data[1,:],data[2,:],'o')
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlabel("$x$")
        ax.set_ylabel("$z$")
        #ax.set_xlim(0,11)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)
        fname = "alpha_{:.0f}_gamma{:.0f}".format(alphas[i],10*gammas[i])
        saveplot(fig, fname)
        plt.close(fig)



def get_amax():
    unique_gammas = np.unique(gammas)
    amax = np.zeros(unique_gammas.shape)

    for i, gamma in enumerate(unique_gammas):

        j = np.argmax(xs[gammas==gamma])
        amax[i] = alphas[gammas==gamma][j]
        print(xs[gammas==gamma])
        print(j)
        print(amax[i])

    print(unique_gammas)
    print(amax)
    fig = plt.figure(999,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)

    ax.plot(unique_gammas,amax,'o')
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel(r"$\gamma$")
    ax.set_ylabel(r"$\alpha_{max}$")
    #ax.set_xlim(0,11)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    fname = "amax"
    saveplot(fig, fname)
    plt.close(fig)



if __name__ == '__main__':
    print_all_plots()
    get_amax()
    #print_test()
