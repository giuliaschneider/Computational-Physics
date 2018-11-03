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
files = [f for f in os.listdir(current_dic) if "0000.txt" in f]
files.sort()

#fnames = ["n64", "magnetization_n256", "magnetization_n1024"]

filename = files[0]
#data = np.loadtxt(filename)

def saveplot(fig, filename):
    file_str =  join(dirname(dirname(current_dic)), 'report/figures/') + filename
    #fig.savefig(file_str + ".pgf",bbox_inches='tight')
    fig.savefig(file_str + ".png",bbox_inches='tight')


def plot_all():

    for f, filename in enumerate(files):
        data = np.loadtxt(filename)
        dataPlot = data.reshape(int(np.sqrt(data.size)),-1)
        nonZeroIndex = np.nonzero(dataPlot)
        xmin = nonZeroIndex[0][np.argmin(nonZeroIndex[0])]
        ymin = nonZeroIndex[1][np.argmin(nonZeroIndex[1])]
        xmax = nonZeroIndex[0][np.argmax(nonZeroIndex[0])]
        ymax = nonZeroIndex[1][np.argmax(nonZeroIndex[1])]
        xymin = min(xmin+2, ymin+2)
        xymax = max(xmax+2, ymax+2)
        print(dataPlot.shape)
        fig = plt.figure(f,(8.3/2.54,8.3/2.54))
        ax = fig.add_subplot(1,1,1)
        mycmap = mpl.cm.get_cmap('copper')
        mycmap.set_under('w')
        img = ax.imshow(dataPlot[xymin:xymax, xymin:xymax],
                        interpolation ='none', cmap = mycmap,
                        vmin = .0001)
        plt.axis('off',)
        plt.colorbar(img)

        saveplot(fig, filename[:-4])
        print(filename)

        plt.close(fig)




if __name__ == '__main__':
    plot_all()
