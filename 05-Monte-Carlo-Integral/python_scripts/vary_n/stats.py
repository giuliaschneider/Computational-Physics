import numpy as np
import sys
import os as os

from os.path import isfile, join, dirname



current_dic = os.getcwd()
sub_dic = join(current_dic, 'vary_n/')
files = [f for f in os.listdir(current_dic) if "txt" in f]
files.sort();


filenames = ["$n=2$", "$n=5$", "$n=20$", "$n=40$","$n=50$"]

def calcStatistics():
    mean = np.zeros(len(files))
    for i,filename in enumerate(files[2:5:2]):
        M, Im = np.genfromtxt(filename,delimiter = "\t", unpack = True)
        mean[i] = np.mean(M[1000:])

    filename = "stats.tex"
    saveTable(header, data, filename)




def saveTable(header, filename):
    file_str =  join(dirname(dirname(dirname(current_dic))), 'report/tables/', filename)

    thefile = open(file_str, 'w')
    thefile.write(r'\begin{table}[hbt]')
    thefile.write('\n')
    thefile.write(r'\caption{}')
    thefile.write('\n')
    thefile.write(r'\begin{center}')
    thefile.write('\n')
    thefile.write(r'\begin{tabular}')
    thefile.write('\n')
    thefile.write(r'\toprule')

    n = len(header)

    for i, hi in enumerate(header):
        if i ==0:
            thefile.write(hi)
        else:
            thefile.write('&')
            thefile.write(hi)
    thefile.write(r'\\')
    thefile.write('\n')











if __name__ == '__main__':
    saveTable({1, 2, 3}, "test.tex")
