import numpy as np
import sys
import os as os

from os.path import abspath,  isfile, join, dirname
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
files = [f for f in os.listdir(dataDir) if "varyN_" in f]
files.sort()



def saveplot(fig, filename):
    file_str =   join(resultsDir, filename)
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def plot_all():

    for f, file in enumerate(files):
        filename = join(dataDir, file)
        M, R2, err = np.genfromtxt(filename,delimiter = ",", unpack = True,
                                   skip_header=1)

        fig = plt.figure(f,(8.3/2.54,8.3/2.54))
        ax = fig.add_subplot(1,1,1)
        ax.plot(M, R2,'o')
        #ax.plot(M[::3], R2[::3] ,'o')
        if "varyN" in filename:
            ax.set_xlabel('Number of positions $N$')
        else:
            ax.set_xlabel('Number of configurations $M$')
        ax.set_ylabel('Average square distance $\mathbf{R}^2$')
        ax.set_xlim(M[0], M[-1])
        #ax.set_ylim(M[0], M[-1])
        saveplot(fig, file[:-4]+'_R2')
        plt.close(fig)

        dist = R2[-1]

        if "varyM" in filename:
            err1 = 0.025*dist
            print(err1)

            fig = plt.figure(f+len(files),(8.3/2.54,8.3/2.54))
            ax = fig.add_subplot(1,1,1)
            ax.plot(M[::4], np.log(err[::4]) ,'o')
            #ax.plot(M[::3], err[::3] ,'o')
            ax.plot(M, np.log(np.ones(M.size)*err1), 'r-', linewidth = 0.5)
            ax.set_xlim(M[0], M[-1])
            #ax.set_ylim(1, np.max(err)*1.15)
            ax.set_xlabel('Number of configurations $M$')
            ax.set_ylabel('log(Estimated error) $\log{\Delta}$')
            saveplot(fig, file[:-4]+'_err')


        plt.close(fig)




if __name__ == '__main__':
    plot_all()
