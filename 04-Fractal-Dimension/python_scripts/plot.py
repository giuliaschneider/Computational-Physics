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


current_dic = os.getcwd()
files = [f for f in os.listdir(current_dic) if ".txt" and "1000" in f]
files.sort()





def saveplot(fig, filename):
    file_str =  join(dirname(dirname(current_dic)), 'report/figures/') + filename
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def print_all_plots():
    fig = plt.figure(1,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)
    data = np.loadtxt(files[1])
    R = np.arange(3,data.size+3)
    c = np.polyfit(np.log(R), np.log(data),1)[0]
    print(c)
    c_string = r"$d_f={:.3f}$".format(c)
    fig.text(0.35,0.6,c_string, transform=ax.transAxes)
    ax.loglog(R,data,'o')
    ax.loglog(R,(R)**c,'k--',linewidth=0.5)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("$log(R)$")
    ax.set_ylabel("$log(M(R))$")
    #ax.set_xlim(0,50)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    del data

    fname = "Sandbox_N1000"
    saveplot(fig, fname)

    fig = plt.figure(2,(8.5/2.54,8.5/2.54))
    ax = fig.add_subplot(1,1,1)
    data = np.loadtxt(files[0])
    print(len(data))
    R = 1/np.arange(1,data.size+1)
    c = np.polyfit(np.log(R[:250]), np.log(data[:250]),1)[0]
    print(c)
    c_string = r"$d_f={:.3f}$".format(c)
    fig.text(0.35,0.6,c_string, transform=ax.transAxes)
    ax.loglog(R,data,'o')
    ax.loglog(R[:250],R[:250]**c*150000,'k--',linewidth=0.5)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel(r"$log(1/ \epsilon)$")
    ax.set_ylabel(r"$log(N(\epsilon))$")
    #ax.set_xlim(0,50)
    ax.legend(loc="best", frameon=False, labelspacing=0.05)
    del data

    fname = "BoxCounting_N1000"
    saveplot(fig, fname)





if __name__ == '__main__':
    print_all_plots()
