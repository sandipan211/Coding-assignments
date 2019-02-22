# -*- coding: utf-8 -*-
"""
Created on Sat Feb 17 12:59:51 2018

@author: SANDIPAN
"""

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



######################## 3-4-5 partitioning ##############################
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
flag = 0
icount = 0
att_col = 3       
k = int(input('Enter the no. of intervals: '))
with open('E:/Academics/sem 6 docs/Data mining/Wholesale_customers_data.csv') as file:
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data = np.array(x).astype("int")

data = data[data[:,att_col].argsort()]   
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
    if flag==0:
        iters = len(intervals)-1
        flag = 1
        
    icount += parts
    if icount<k:
        if myiter<iters:
            
            temp = []
            for j in range(noisydata.shape[0]):
                if noisydata[j]<intervals[myiter] and noisydata[j]>=intervals[myiter+1]:
                    temp.append(noisydata[j])            
                
                
            datamax = int(max(temp))
            print(datamax)
            datamin = int(min(temp))
            print(datamin)
            myiter += 1
        else:
            myiter = 0
            intervals = list(set(intervals))
            intervals = sorted(intervals, reverse=True)
            flag=0
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

#############################################################################



#def entropy(tuples):
#
#    classes = np.unique(tuples)
#    tlist = list(tuples)
#    e = 0.0
#    for i in range(len(classes)):
#        prob = (tlist.count(classes[i]))/len(tuples)
#        e += -1*prob*np.log2(prob)
#        
#    return e
#
#
#splitpts = []
#thresh = int(input('Enter the no. of intervals: '))
#with open('E:/Academics/sem 6 docs/Data mining/liverdata.csv') as file:
#    reader = csv.reader(file, delimiter = ',')
#    x = list(reader)
#    data = np.array(x).astype('float')
#
#classcol = data.shape[1]-1
#classes = len(np.unique(data[:,classcol]))
#col = data[:,1]
#icount = 1
#att = col
#
#while(1):
#    
#    
#    if icount<=thresh:
#        
#        info = []
#        for i in range(len(att)):           #change att everywhere
#        
#            set1 = []
#            set2 = []
#            for j in range(len(att)):
#                if i==0 and j==0:
#                    set1.append(data[j][classcol])
#                elif i==len(att)-1 and i==j:
#                    set2.append(data[j][classcol])
#                else:
#                    
#                   if j<=i:
#                    set1.append(data[j][classcol])
#                   else:
#                    set2.append(data[j][classcol])
#                   
#                    
#            
#            e_set1 = entropy(set1)
#            e_set2 = entropy(set2)
#            thisinfo = (len(set1))/(len(att))*e_set1 + (len(set2))/(len(att))*e_set2
#            info.append(thisinfo)
#        
#        min_info = min(info)
#        min_index = info.index(min_info)
#        split1 = []
#        split2 = []
##        for i in range(len(att)):
##            if i<=min_index:
##                split1.append(att[i])
##            else:
##                split2.append(att[i])
#        splitpts.append(min_index)
#        icount += 1
#        
#     
#    else:
#        break