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
files = [f for f in os.listdir(current_dic) if "saw_n100" in f]
files.sort()

#fnames = ["n64", "magnetization_n256", "magnetization_n1024"]


def saveplot(fig, filename):
    file_str =  join(dirname(dirname(current_dic)), 'report/figures/') + filename
    fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def plot_all():

    for f, filename in enumerate(files):
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
        ax.set_ylim(0, np.max(R2)*1.15)
        saveplot(fig, filename[:-4]+'_R2')
        plt.close(fig)

        dist = R2[-1]

        if "varyM" in filename:
            err1 = 0.01*dist

            fig = plt.figure(f+len(files),(8.3/2.54,8.3/2.54))
            ax = fig.add_subplot(1,1,1)
            ax.plot(M, err ,'o')
            #ax.plot(M[::3], err[::3] ,'o')
            ax.plot(M, np.ones(M.size)*err1, 'r-', linewidth = 0.5)
            ax.set_xlim(M[0], M[-1])
            ax.set_ylim(0, np.max(err)*1.15)
            ax.set_xlabel('Number of configurations $M$')
            ax.set_ylabel('Estimated error $\Delta$')
            saveplot(fig, filename[:-4]+'_err')


        plt.close(fig)




if __name__ == '__main__':
    plot_all()
