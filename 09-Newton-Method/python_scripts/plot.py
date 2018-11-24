import numpy as np
import sys
import os as os
from os.path import abspath, isfile, join, dirname

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


root = os.getcwd()
dataDir = abspath(join(root, "..", "results"))
resultsDir = abspath(join(root, "..", "results", "figures"))

files = [f for f in os.listdir(dataDir) if "txt" in f and "Secant" in f]
files.sort();


legend_labels = [
            "$x_{init}=(4.85$,1.85$)",
            "$x_{init}=(4.90$,1.90$)",
            "$x_{init}=(4.95$,1.95$)",
            "$x_{init}=(5.00$,2.00$)",
            "$x_{init}=(5.05$,2.05$)",
            "$x_{init}=(5.10$,2.10$)",
            "$x_{init}=(5.15$,2.15$)",
            "$x_{init}=(5.25$,2.25$)",
            "$x_{init}=(5.30$,2.30$)",
            "$x_{init}=(5.35$,2.35$)",
            "$x_{init}=(5.40$,2.40$)",
            "$x_{init}=(5.45$,2.45$)",
            "$x_{init}=(5.50$,2.50$)",
            "$x_{init}=(5.55$,2.55$)"]


"""
legend_labels = [
            "$x_{init}=(5.25$,2.25$)",
            "$x_{init}=(5.30$,2.30$)",
            "$x_{init}=(5.35$,2.35$)",
            "$x_{init}=(5.40$,2.40$)",
            "$x_{init}=(5.45$,2.45$)",
            "$x_{init}=(5.50$,2.50$)",
            "$x_{init}=(5.55$,2.55$)",
            "$x_{init}=(5.60$,2.60$)"]
"""

def saveplot(fig, filename):
    file_str =   join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')

def print_all_plots():
    index = 1
    for i, file in enumerate(files):
        if i==0 or i==7:
            fig = plt.figure(index,(8.5/2.54,8.5/2.54))
            ax = fig.add_subplot(1,1,1)
        filename = join(dataDir, file)
        L, err = np.genfromtxt(filename, delimiter = ", ", unpack = True)
        #ax.plot(data[:1000],data[1:1001],'o')
        ax.semilogy(L,err,label=legend_labels[i])
        ax.xaxis.set_ticks_position("bottom")
        ax.yaxis.set_ticks_position("left")
        ax.set_xlabel("Iteration $i$")
        ax.set_ylabel("Error $|x-x^*|$")
        ax.set_xlim(0,11)
        ax.legend(loc="best", frameon=False, labelspacing=0.05)
        del err
        if i==6 or i==13:
            fname = "secant_error{}".format(index)
            index += 1
            saveplot(fig, fname)


def F(x,y):
    x0 = 5.2
    y0 = 2.2
    return np.exp(-(x-x0)**2-(y-y0)**2)

def f(x,y):
    x0 = 5.2
    y0 = 2.2
    expon = np.exp(-(x-x0)**2-(y-y0)**2)
    fx = -2*(x-x0)*expon
    fy = -2*(y-y0)*expon
    return fx, fy

def plot_function():
    x = np.linspace(3.2,7.2,1e2)
    y = np.linspace(0.2,4.2,1e2)
    X,Y = np.meshgrid(x,y)
    FXY = F(X,Y)
    fxy = f(x,y)

    fig = plt.figure(1,(8.5/2.54,6.8/2.54))
    ax = fig.add_subplot(1,1,1)
    cs = ax.contourf(X,Y,FXY)
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("$x$")
    ax.set_ylabel("$y$")
    fig.colorbar(cs)
    fname = "function"
    saveplot(fig, fname)

def plot_functionf():
    x = np.linspace(3.2,7.2,50)
    y = np.linspace(0.2,4.2,50)
    X,Y = np.meshgrid(x,y)
    fx, fy = f(X,Y)
    xx = np.linspace(4.85,5.55,15)
    yy = xx-3

    fig = plt.figure(2,(6.8/2.54,6.8/2.54))
    ax = fig.add_subplot(1,1,1)
    cs = ax.quiver(X,Y,fx,fy)
    ax.plot(xx,yy,'ro',ms =1,mfc='r')
    ax.xaxis.set_ticks_position("bottom")
    ax.yaxis.set_ticks_position("left")
    ax.set_xlabel("$x$")
    ax.set_ylabel("$y$")
    fname = "functionf"
    saveplot(fig, fname)



if __name__ == '__main__':
    print_all_plots()
    #plot_function()
    #plot_functionf()
