# -*- coding: utf-8 -*-
"""
Created on Fri Jan  5 14:53:47 2018

@author: SANDIPAN
"""

import csv
import numpy as np
import math


clusters = int(input("Enter the no. of clusters: "))

def norm(mat):
    data = (mat-np.min(mat))/(np.max(mat)-np.min(mat))
    return data
    
def cluster_sim(simtype, c):
  
 counter = 1
 while(len(simtype)>c):
  
  
  simclus = np.zeros((len(simtype), len(simtype)))

  for i in range(len(simtype)):
    for j in range(len(simtype)):
        simclus[i][j] = len(set(simtype[i])&set(simtype[j]))/len(set(simtype[i])|set(simtype[j]))

  max_clusters = []
  maxval = np.max(np.triu(simclus, k=1))
  for i in range(len(simtype)):
      for j in range(i+1, len(simtype)):
          if simclus[i,j]==maxval:
              x = list(set(simtype[i])|set(simtype[j]))
              max_clusters.append(x)
              
  for i in range(len(max_clusters)):
    
    toremove =[]              
    for j in range(len(simtype)):
        if set(simtype[j]).issubset(set(max_clusters[i]))==True:
            toremove.append(simtype[j])
    
    for k in range(len(toremove)):
        if toremove[k] in simtype:
            simtype.remove(toremove[k])
    simtype.append(max_clusters[i])    

  print("No. of clusters at pass {0} : {1}".format(counter, len(simtype)))
  counter = counter+1
  
  
  
with open('E:/Academics/sem 6 docs/Data mining/iris.csv') as file:
    reader = csv.reader(file, delimiter=',')
    x = list(reader)
    data = np.array(x).astype("float")
  
alldata= np.zeros((150,4))      
for i in range(0,4):
      alldata[:,i] = norm(data[:,i])

      
dice = np.zeros((150,150))
jaccard = np.zeros((150,150))
cosine = np.zeros((150,150))
overlap = np.zeros((150,150))

d_row_avgs = np.zeros((150,1))
j_row_avgs = np.zeros((150,1))
c_row_avgs = np.zeros((150,1))
o_row_avgs = np.zeros((150,1))

for i in range(0,150):
    for j in range(0,150):
        
        el_sum = np.sum(np.multiply(alldata[i,:], alldata[j,:]))
        sq_sum_i = np.sum(np.multiply(alldata[i,:], alldata[i,:]))
        sq_sum_j = np.sum(np.multiply(alldata[j,:], alldata[j,:]))
        
        dice[i][j] = (2*el_sum)/(sq_sum_i+sq_sum_j)
        jaccard[i][j] = el_sum/(sq_sum_i+sq_sum_j-el_sum)
        cosine[i][j] = el_sum/(math.sqrt(sq_sum_i*sq_sum_j))
        overlap[i][j] = el_sum/(min(sq_sum_i, sq_sum_j))

    d_row_avgs[i] = np.mean(dice[i])                                             #np.mean(dice[i])
    j_row_avgs[i] = np.mean(jaccard[i])
    c_row_avgs[i] = np.mean(cosine[i])
    o_row_avgs[i] = np.mean(overlap[i])
       

dice_sim_objs = []
jaccard_sim_objs = []
cosine_sim_objs = []
overlap_sim_objs = []

for i in range(0, 150):
    
    d_sim_objs = []
    j_sim_objs = []
    c_sim_objs = []
    o_sim_objs = []
    
    for j in range(0, 150):
        
        if(dice[i][j]>d_row_avgs[i]):
                 d_sim_objs.append(j)
        if(jaccard[i][j]>j_row_avgs[i]):
                 j_sim_objs.append(j)
        if(cosine[i][j]>c_row_avgs[i]):
                 c_sim_objs.append(j)
        if(overlap[i][j]>o_row_avgs[i]):
                 o_sim_objs.append(j)
                 
    dice_sim_objs.append(d_sim_objs)
    jaccard_sim_objs.append(j_sim_objs)
    cosine_sim_objs.append(c_sim_objs)
    overlap_sim_objs.append(o_sim_objs)
  
print("\nWith Dice: \n")
cluster_sim(dice_sim_objs, clusters)
print("\nWith Cosine: \n")
cluster_sim(cosine_sim_objs, clusters)
print("\nWith Jaccard: \n")
cluster_sim(jaccard_sim_objs, clusters)
print("\nWith Overlap: \n")
cluster_sim(overlap_sim_objs, clusters)



    
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        