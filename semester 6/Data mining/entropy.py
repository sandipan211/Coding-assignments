# -*- coding: utf-8 -*-
"""
Created on Fri Feb 23 01:39:02 2018

@author: SANDIPAN
"""

import numpy as np
import math
import csv
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import pandas as pd



def entropy(tuples):

    classes = np.unique(tuples)
    tlist = list(tuples)
    e = 0.0
    for i in range(len(classes)):
        prob = (tlist.count(classes[i]))/len(tuples)
        e += -1*prob*np.log2(prob)
        
    return e

def split_interval(att):
        info = []
        for i in range(len(att)):           
        
            set1 = []
            set2 = []
            for j in range(len(att)):
                    
                   if att[j]<=att[i]:
                    set1.append(data[j][classcol])
                   else:
                    set2.append(data[j][classcol])
                   
                    
            
            e_set1 = entropy(set1)
            e_set2 = entropy(set2)
            thisinfo = (len(set1))/(len(att))*e_set1 + (len(set2))/(len(att))*e_set2
            print('info = '+ str(thisinfo))
            info.append(thisinfo)
#            print(set1)
#            print(set2)
        min_info = min(info)
        print(min_info)
        min_index = info.index(min_info)
#        split2 = []
#        for i in range(len(att)):
#            if i<=min_index:
#                split1.append(att[i])
#            else:
#                split2.append(att[i])
 
        splitpts.append(min_index)
        
        return min_index

        
        
        
        
splitpts = []
run_upto = 0
thisiter = 1
flag = 1
thresh = int(input('Enter the no. of intervals: '))
with open('E:/Academics/sem 6 docs/Data mining/liverdata.csv') as file:
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data = np.array(x).astype('float')

classcol = data.shape[1]-1
classes = len(np.unique(data[:,classcol]))
col = data[:,1]
icount = 1
att = col
limits = [0,len(col)-1]
while(1):
    
    
    if icount<thresh:
        
        if icount==1:
            sp= split_interval(att)
            limits.append(sp)
            limits = sorted(limits)
            icount += 1
        if icount>=thresh:
            break
        for j in range(0,run_upto+2):
            
#            if j==0 or j==run_upto:
#                
#                if j==0:
#                    lb = j
#                    ub = 
#                if j==run_upto:
#                    ub=len(col)-1
#            else:
#                lb = splitpts[j]
#                ub = splitpts[j+1]
            lb = limits[j]
            ub = limits[j+1]
            att = col[lb:ub]
            sp = split_interval(att)
            limits.append(sp)
            icount +=1
            if icount>=thresh:
                flag = 0
                break
            
        
        run_upto +=  2**thisiter
        thisiter += 1
        limits = sorted(limits)
        if flag==0:
            break
#        splitpts = sorted(splitpts)
    else:
        break
    
    
discretized = []
index = 0
for i in range(len(limits)-1):
    eachpart = []
    for j in range(limits[index],limits[index+1]):
        eachpart.append(col[j])
    index+=1
    discretized.append(eachpart)        
    
discretized[len(discretized)-1].append(col[len(col)-1])



