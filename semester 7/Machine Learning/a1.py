# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

from sklearn import datasets
from sklearn.naive_bayes import GaussianNB
from sklearn.model_selection import KFold
from sklearn.linear_model import LogisticRegression
import matplotlib.pyplot as plt
import csv
import numpy as np

all_performances = []

def classifiers(data, target, dataset):
    
    performance = []
    entry = []
    ########## NAIVE BAYES AND LOGISTIC REGRESSION ##################
    finalaccNB = 0
    finalaccLR = 0
    for i in range(10):
            
        k = 5
        kf = KFold(n_splits=5, shuffle=True)
        cv = kf.split(data)
        accuracyNB = 0
        accuracyLR = 0
        print(cv)
        for train_ind, test_ind in cv:
            gnb = GaussianNB()
            data_train, data_test = data[train_ind], data[test_ind]
            target_train, target_test = target[train_ind], target[test_ind]
            model = gnb.fit(data_train, target_train)
            y_pred = model.predict(data_test)
            accuracyNB = accuracyNB + ((y_pred==target_test).sum())/target_test.shape[0]
            
            
            logreg_model = LogisticRegression()
            logreg_model.fit(data_train, target_train)
            pred = logreg_model.predict(data_test)
            accuracyLR = accuracyLR + ((pred==target_test).sum())/target_test.shape[0]
            
        accuracyNB = accuracyNB/k*100
        accuracyLR = accuracyLR/k*100
        finalaccNB = finalaccNB+accuracyNB
        finalaccLR = finalaccLR+accuracyLR
        
    finalaccNB = finalaccNB/10
    entry.append((finalaccNB,'Naive Bayes'))
    finalaccLR = finalaccLR/10
    entry.append((finalaccLR,'Logistic Regression'))
    all_performances.append(entry)
    performance.append(entry[0][0])
    performance.append(entry[1][0])
    objects = ('Naive Bayes','Logistic Regression')
    y_pos = np.arange(len(objects))
     
    barlist = plt.bar(y_pos, performance, align='center', alpha=0.5)
    plt.xticks(y_pos, objects)
    plt.ylabel('Performance')
    plt.title('Performance of different classifiers on '+dataset)
    barlist[0].set_color('r')
    plt.show()


bc = datasets.load_breast_cancer()
data, target = bc.data, bc.target
classifiers(data, target, 'breast cancer dataset')

with open('/home/sandipan/ml/house-votes-data.csv') as file:
    next(file)                      #to ignore header of csv file
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data1 = np.array(x).astype("int")

target1 = data1[:,data1.shape[1]-1]
data1 = data1[:,:data1.shape[1]-1]
classifiers(data1, target1, 'house-votes-84 dataset')































#print("Accuracy: %0.2f +/- %0.2f" % (score.mean(), score.std() * 2))
#########################################

########## LOGISTIC REGRESSION ############
#
#
#target = target.reshape((target.shape[0],1))
#con = np.concatenate((data, target), axis=1)   #used when running LR separately
#random.shuffle(con)
#xval = (int)(data.shape[0]*0.7)
#x_train, y_train = con[:xval,:data.shape[1]], con[:xval,data.shape[1]:]
#x_test, y_test = con[xval:,:data.shape[1]], con[xval:,data.shape[1]:]


