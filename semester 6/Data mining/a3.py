# -*- coding: utf-8 -*-
"""
Created on Thu Feb 15 22:59:55 2018

@author: SANDIPAN
"""

import numpy as np
import math
import csv
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import pandas as pd


############# histogram discretization #############
#bins = int(input("Enter the no. of intervals: "))
#with open('E:/Academics/sem 6 docs/Data mining/data_stock.csv') as file:
#    reader = csv.reader(file, delimiter = ',')
#    x = list(reader)
#    data = np.array(x).astype("float")
#    data = data[data[:,0].argsort()]   # sort by 0th column
#    noisydata = data[:,0]
#
#width = (noisydata.max()-noisydata.min())/bins
#ints = []
#val = noisydata.min()
#for i in range(bins+1):
#    ints.append(val+i*width)
#    
#ints = sorted(ints, reverse=True)
#plt.hist(noisydata, bins)
#intervaldata = []
#index = 0
#for i in range(bins):
#    eachint = []
#    for j in range(len(noisydata)):
#        if noisydata[j]<ints[index] and noisydata[j]>=ints[index+1]:
#            eachint.append(noisydata[j])
#    intervaldata.append(eachint)
#    index+=1
#




def partition345(dbits, newmax, intervals):
    if dbits==3 or dbits==6 or dbits==7 or dbits==9:
        partitions = 3
        if dbits!=7:
            jump = dbits/partitions
            for i in range(partitions+1):
                intervals.append(int(newmax-(jump*i*(10**(digits-1)))))
        
        else:
            intervals.append(int(newmax))
            intervals.append(int(newmax-2*(10**(digits-1))))
            intervals.append(int(newmax-5*(10**(digits-1))))
            intervals.append(int(newmax-7*(10**(digits-1))))
         
    elif dbits==2 or dbits==4 or dbits==8:
        partitions = 4
        jump = dbits/partitions
        for i in range(partitions+1):
            intervals.append(int(newmax-(jump*i*(10**(digits-1)))))
    else:
        partitions = 5
        jump = dbits/partitions
        for i in range(partitions+1):
            intervals.append(int(newmax-(jump*i*(10**(digits-1)))))
     
    return partitions
            
            
intervals = []
myiter = 0
icount = 0
att_col = 3         #not working for 2, check for the conditions when u don't increment the higher range
#e.g, from 62890 to 70000, but the high is already 70000,; that case you won't be considering 70000 for binning finally
k = int(input('Enter the no. of intervals: '))
with open('E:/Academics/sem 6 docs/Data mining/Wholesale_customers_data.csv') as file:
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data = np.array(x).astype("int")

data = data[data[:,att_col].argsort()]   # sort by 0th column
noisydata = data[:,att_col]
datamin = int(np.min(noisydata))
datamax = int(np.max(noisydata))
while True:

    digits = int(len(str(datamax)))             
    max_msbdigit = int(datamax/(10**(digits-1)))
    if icount==0:
       newmax = int((max_msbdigit+1)*(10**(digits-1)))
    else:
        if datamax>(max_msbdigit)*(10**(digits-1)):
            newmax = int((max_msbdigit+1)*(10**(digits-1)))
        else:
            newmax = datamax
    min_msbdigit = int(datamin/(10**(digits-1)))
    if min_msbdigit==0:
        newmin = 0
    else:
            if datamin>min_msbdigit*(10**(digits-1)):
                newmin = int((min_msbdigit)*(10**(digits-1)))
            else:
                newmin = datamin
  

    diff = newmax-newmin
    dbits = int(diff/(10**(digits-1)))


    parts = partition345(dbits, newmax, intervals)
    icount += parts
    if icount<k:
        if myiter!=parts:
            datamax = int(intervals[myiter])
            print(datamax)
            datamin = int(intervals[myiter+1])
            print(datamin)
            myiter += 1
        else:
            myiter = 0
            intervals = list(set(intervals))
            intervals = sorted(intervals, reverse=True)
    else:
        break
    
        
   

interval_data=[]
intervals = list(set(intervals))
intervals = sorted(intervals, reverse=True)
index = 0
for i in range(len(intervals)-1):
    eachpart = []
    for j in range(noisydata.shape[0]):
        if noisydata[j]<intervals[index] and noisydata[j]>=intervals[index+1]:
            eachpart.append(noisydata[j])
    index = index+1
    interval_data.append(eachpart)



