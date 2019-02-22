# -*- coding: utf-8 -*-
"""
Created on Fri Jan 12 14:12:40 2018

@author: SANDIPAN
"""



import numpy as np
import math
import csv
import random
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import pandas as pd
import scipy.stats as stats
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import LogisticRegression

#mu = 0
#variance = 2
#sigma = math.sqrt(variance)
#pts = 100000
#
#sym_x = np.linspace(mu - 3*sigma, mu + 3*sigma, pts)
#symdensity = mlab.normpdf(sym_x, mu, sigma)
#sym_mean = np.mean(symdensity)
#sym_median = np.median(symdensity)
#sym_mode = (stats.mode(symdensity))[0][0]
#plt.plot(sym_x,symdensity)
#plt.axvline(sym_mean, linewidth = 2, color='b')
#plt.axvline(sym_median, linewidth = 2, color='r')
#plt.axvline(sym_mode, linewidth = 2, color='g')
#
#
#plt.xlabel('datapts')
#plt.ylabel('density')
#plt.grid(True)
#plt.savefig('symmetric_dataset.png')
#plt.show()
#
############## positively skewed dataset
#
#pskew_x = pd.DataFrame(np.random.exponential(size = pts))
#pskew_x.plot(kind = "density", xlim = (-1,6))
#pskew_mat = pskew_x.as_matrix()
#pskew_mean = np.mean(pskew_mat)
#pskew_median = np.median(pskew_mat)
#pskew_mode = (stats.mode(pskew_mat))[0][0]
#
#plt.axvline(pskew_mean, linewidth = 2, color='b')
#plt.axvline(pskew_median, linewidth = 2, color='r')
#plt.axvline(pskew_mode, linewidth = 2, color='g')
#
#
#plt.xlabel('datapts')
#plt.ylabel('density')
#plt.grid(True)
#plt.savefig('pskewed_dataset.png')
#plt.show()
#
#
############## negatively skewed dataset
#
#nskew_x = pd.DataFrame(np.random.exponential(size = pts))
#nskew_x.plot(kind = "density", xlim = (6,-1))
#nskew_mat = nskew_x.as_matrix()
#nskew_mean = np.mean(nskew_mat)
#nskew_median = np.median(nskew_mat)
#nskew_mode = (stats.mode(nskew_mat))[0][0]
#
#plt.axvline(nskew_mean, linewidth = 2, color='b')
#plt.axvline(nskew_median, linewidth = 2, color='r')
#plt.axvline(nskew_mode, linewidth = 2, color='g')
#
#
#plt.xlabel('datapts')
#plt.ylabel('density')
#plt.grid(True)
#plt.savefig('nskewed_dataset.png')
#plt.show()
#

############################  Linear Regression   #############################
#def LinearReg():
#
#    missing_att = []
#    missing_rows = []
#    missingRA = []
#    data = pd.read_csv('E:/Academics/sem 6 docs/Data mining/class-grades.csv', error_bad_lines=False)
#    for i in range(data.shape[0]):
#        for j in range(data.shape[1]):
#            if math.isnan(data.iloc[i][j])==True:
#                if j not in missing_att:
#                   missing_att.append(j)
#                if i not in missing_rows:
#                   missing_rows.append(i)
#                missingRA.append(((i,j)))
#    
#    cleaned = data
#    nomissdata = data.drop(data.index[missing_rows])
#    
#    
##    pred_values =  []
#    reg = LinearRegression()
#    for i in range(len(missing_att)):
#        
#        modeldata = nomissdata.drop(nomissdata.columns[i], axis=1)
#        reg.fit(modeldata, nomissdata.iloc[:,missing_att[i]])
#        df = pd.DataFrame(reg.coef_, columns = ["Slope"])
#        maxind = df.iloc[:,0].idxmax()
#        X = data.iloc[:,maxind]
#        slope = df.iloc[maxind]
#        b = reg.intercept_
#        for j in range(len(missing_rows)):
#            if missingRA[j][1]==missing_att[i]:
#               val = slope*X[missing_rows[j]]+b
##               cleaned.at[missing_rows[j],[missing_att[i]] = val['Slope']
#               cleaned.set_value(missing_rows[j],cleaned.columns[missing_att[i]],val[0])           
#               
#        #pred_values.append(((missing_att[i],pred)))
#        
#
#    return data, cleaned
#    
#dat, clean = LinearReg()

############################# Binning ########################################
bins = int(input("Enter the no. of bins: "))

with open('E:/Academics/sem 6 docs/Data mining/data_stock.csv') as file:
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data = np.array(x).astype("float")
    data = data[data[:,0].argsort()]   # sort by 0th column
    noisydata = data[:,0]
    
    bindata = []
    bymean = []
    bymedian = []
    bybound = []
    lastj = 0
    elenum = int (noisydata.shape[0]/bins)
    
    for i in range(bins):
        eachbin = []
        for j in range(lastj,lastj+elenum):
            eachbin.append(noisydata[j])
        bindata.append(eachbin)
        lastj = j+1
    
    for i in range(lastj,noisydata.shape[0]):
        bindata[bins-1].append(noisydata[i])
   
    
    ##########  by means ##########
    for i in range(len(bindata)):
        thisbin = np.array(bindata[i])
        mean = np.mean(thisbin)
        for j in range(len(thisbin)):
            thisbin[j] = mean
        bymean.append(list(thisbin))        
        
    ########## by median ##########
    for i in range(len(bindata)):
        thisbin = np.array(bindata[i])
        median = np.median(thisbin)
        for j in range(len(thisbin)):
            thisbin[j] = median
        bymedian.append(list(thisbin))        
    
    ########## by boundary ##########
    for i in range(len(bindata)):
        thisbin = np.array(bindata[i])
        lb = np.min(thisbin)
        ub = np.max(thisbin)

        for j in range(len(thisbin)):
            if (thisbin[j]-lb)<(ub-thisbin[j]):
                thisbin[j] = lb
            else:
                thisbin[j] = ub
        bybound.append(list(thisbin))        
    
##############################################################################
    
#
########################  LOGISTIC REGRESSION #########################
#data = pd.read_csv('E:/Academics/sem 6 docs/Data mining/iris.csv')
#data = data.sample(frac=1)                 #randomize data
#data = data.as_matrix()
#data = pd.DataFrame(data)
#xval = int(0.7*data.shape[0])
#
#x_train = data.iloc[0:xval,0:4]
#y_train = data.iloc[0:xval,4]
#x_test = data.iloc[xval:,0:4]
#y_test = data.iloc[xval:,4]
#
#for i in range(10):
#    row = random.randint(0,y_test.shape[0]-1)                   #inclusive both ends
#    y_test[xval+row] = math.nan
#    
#logisticRegr = LogisticRegression()
#logisticRegr.fit(x_train, y_train)    
# 
#predictions = pd.Series(logisticRegr.predict(x_test))
##########################################################################


###################### MULTIPLE REGRESSION ################################

#data1 = pd.read_csv('E:/Academics/sem 6 docs/Data mining/data_stock.csv',header = None)
#xval = int(0.7*data1.shape[0])
#x_train = data1.iloc[0:xval,0:8]
#y_train = data1.iloc[0:xval,8]
#x_test = data1.iloc[xval:,0:8]
#y_test = data1.iloc[xval:,8]
#
#for i in range(10):
#    row = random.randint(0,y_test.shape[0]-1)                   #inclusive both ends
#    y_test[xval+row] = math.nan
#
#reg = LinearRegression()
#reg.fit(x_train, y_train)
#
#predictions = pd.Series(reg.predict(x_test))

##############################################################################   
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    