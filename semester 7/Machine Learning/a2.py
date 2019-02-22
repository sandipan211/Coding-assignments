
# coding: utf-8

# In[131]:


import numpy as np
from numpy.random import rand
import csv
import pandas as pd
import matplotlib.pyplot as plt
import matplotlib.cm as cm
from matplotlib.colors import Normalize
import sklearn.linear_model.perceptron as p
from sklearn.model_selection import train_test_split, KFold
from sklearn.preprocessing import StandardScaler
from sklearn import datasets
from sklearn.neural_network import MLPClassifier, MLPRegressor
from sklearn.metrics import classification_report,confusion_matrix


# In[132]:


def plotacc(performance, labels, dataset):
    
    temp = (labels[0],)
    l = list(temp)
    for i in range(1, len(labels)):
        l.append(labels[i])
        
    objects = tuple(l)
    y_pos = np.arange(len(objects))
     
    my_cmap = cm.get_cmap('jet')
    # get normalize function (takes data in range [vmin, vmax] -> [0, 1])
    my_norm = Normalize(vmin=0, vmax=len(labels))
    # some boring fake data
    my_data = len(labels)*rand(len(labels))
    
    plt.bar(y_pos, performance, align='center', alpha=0.5,color=my_cmap(my_norm(my_data)))
    plt.xticks(y_pos, objects)
    plt.ylabel('Performance')
    plt.title('Performance of different networks on '+dataset)

    plt.show()




# In[146]:


#function for MULTI LAYER PERCEPTRON (HL = 1)
#nh = ns/(a*(ni+no)) : used here to calculate no. of neurons in hidden layer

def mlp(x_train, x_test, y_train, y_test, nh, method, dataset):
    layers = len(nh)
    nh = tuple(nh)
    
    if method=='c':
        mlp = MLPClassifier(activation = 'logistic', solver='lbfgs', hidden_layer_sizes=(nh), random_state=1, max_iter = 1000)
    #For small datasets, ‘lbfgs’ can converge faster and perform better.
    #logistic here is the sigmoid activation
    
    elif method=='r':
        mlp = MLPRegressor(activation = 'logistic', solver='lbfgs', hidden_layer_sizes=(nh), random_state=1, max_iter = 1000)
    #For small datasets, ‘lbfgs’ can converge faster and perform better.
    #logistic here is the sigmoid activation
    mlp.fit(x_train, y_train)
    pred = mlp.predict(x_test)
    accuracy = (pred==y_test).sum()/len(y_test)
    print('Accuracy on ', dataset,' with multiple layer perceptron having',layers,'layers: ',accuracy*100,'%')
    if method!='r':
        print('Confusion matrix:\n',confusion_matrix(y_test,pred))
        print(classification_report(y_test,pred))
    
    return accuracy


# In[136]:


#function for SINGLE LAYER PERCEPTRON 

def slp(x_train, x_test, y_train, y_test, dataset):
    net = p.Perceptron(max_iter=500, verbose=0, random_state=None, fit_intercept=True, eta0=0.002)
    print(net)
    model = net.fit(x_train, y_train)
    y_pred = model.predict(x_test)
    accuracy = (y_pred==y_test).sum()/len(y_test)
    print('Accuracy on ', dataset,' with single layer perceptron: ',accuracy*100,'%')
    print('Confusion matrix:\n',confusion_matrix(y_test,y_pred))
    print(classification_report(y_test,y_pred))
    
    return accuracy


# In[137]:


bc = datasets.load_breast_cancer()
data, target = bc.data, bc.target
# target = target.reshape((target.shape[0],1))
# con = np.concatenate((data, target), axis=1)   #used when running LR separately
# random.shuffle(con)
# xval = (int)(data.shape[0]*0.7)
# x_train, y_train = con[:xval,:data.shape[1]], con[:xval,data.shape[1]:]
# x_test, y_test = con[xval:,:data.shape[1]], con[xval:,data.shape[1]:]

x_train_bc, x_test_bc, y_train_bc, y_test_bc = train_test_split(data, target, test_size=0.3, random_state = 42)
scaler = StandardScaler()
scaler.fit(x_train_bc)
x_train_bc = scaler.transform(x_train_bc)
x_test_bc = scaler.transform(x_test_bc)

nh = int(x_train_bc.shape[0]/(2*(x_train_bc.shape[1]+len(np.unique(y_train_bc)))))  #no.of hidden layer neurons

acc_slp = slp(x_train_bc, x_test_bc, y_train_bc, y_test_bc, 'breast-cancer') #slp tested on breast_cancer dataset
acc_mlp = mlp(x_train_bc, x_test_bc, y_train_bc, y_test_bc, [nh], 'c','breast-cancer') #mlp tested on breast_cancer dataset

plotacc([acc_slp,acc_mlp], ['slp','mlp'], 'breast-cancer')


# In[138]:



with open('/home/sandipan/ml/house-votes-data.csv') as file:
    next(file)                      #to ignore header of csv file
    reader = csv.reader(file, delimiter = ',')
    x = list(reader)
    data1 = np.array(x).astype("int")

target1 = data1[:,data1.shape[1]-1]
data1 = data1[:,:data1.shape[1]-1]
x_train_hv, x_test_hv, y_train_hv, y_test_hv = train_test_split(data1, target1, test_size=0.3, random_state = 42)

nh = int(x_train_hv.shape[0]/(2*(x_train_hv.shape[1]+len(np.unique(y_train_hv)))))  #no.of hidden layer neurons

acc_slp = slp(x_train_hv, x_test_hv, y_train_hv, y_test_hv, 'house-votes-84') #slp tested on house_votes_84 dataset
acc_mlp = mlp(x_train_hv, x_test_hv, y_train_hv, y_test_hv, [nh], 'c', 'house-votes-84') #mlp tested on house_votes_84 dataset

plotacc([acc_slp,acc_mlp], ['slp','mlp'], 'house-votes-84')


# In[139]:


#comparing with 1hl, 2hl, and 3hl mlps

nh = int(x_train_hv.shape[0]/(2*(x_train_hv.shape[1]+len(np.unique(y_train_hv)))))  #no.of hidden layer neurons

acc_mlp1 = mlp(x_train_hv, x_test_hv, y_train_hv, y_test_hv, [nh], 'c', 'house-votes-84') #mlp tested on house_votes_84 dataset
acc_mlp2 = mlp(x_train_hv, x_test_hv, y_train_hv, y_test_hv, [nh,nh], 'c', 'house-votes-84') #mlp tested on house_votes_84 dataset
acc_mlp3 = mlp(x_train_hv, x_test_hv, y_train_hv, y_test_hv, [nh, nh, nh], 'c', 'house-votes-84') #mlp tested on house_votes_84 dataset

plotacc([acc_mlp1,acc_mlp2, acc_mlp3], ['mlp1','mlp2', 'mlp3'], 'house-votes-84')


# In[140]:


def one_hot_encode(data, rows, cols, cat):
    allcodes = []
    flag = 1
    for col in range(cols):               #finding unique values of each attribute and generating mappings
        dvals = []
        codes = []
        count = 0
        for row in range(cat.shape[0]):
            if cat.iloc[row][col] not in dvals:
                dvals.append(cat.iloc[row][col])
                cat.iloc[row][col] = count
                codes.append(count)
                count = count+1

            else:
                obj = cat.iloc[row][col]
                cat.iloc[row][col] = codes[dvals.index(obj)]

        allcodes.append(codes)


    for j in range(len(allcodes)):          #creating separate attributes for each unique value ini each attribute
                                            #and encoding into one-hot
        temp = np.zeros((rows,len(allcodes[j])))
        l = []
        for k in range(len(allcodes[j])):
            s = cat.columns[j]+'_'+str(k)
            l.append(s)

        new = pd.DataFrame(data=temp[:,:], columns=l)
        for i in range(rows):
            val = cat.iloc[i][j]
            new.iloc[i][val] = 1

        if flag==1:
            old = new.copy()
        else:
            cop = new.copy()
            old = pd.concat([old, cop], axis=1).copy()
        flag=0    

    data = pd.concat([data, old], axis=1)
    
    return data          # new one-hot encoded categorical attributes are now concatenated with previous attributes
                         # and returned


# In[141]:


#testing on HOUSE PRICING DATASET

df = pd.read_csv('/home/sandipan/ml/train.csv')
r, c = df.shape
data = df.iloc[:,1:c-1]
target = df.iloc[:, c-1]
cat = df.select_dtypes(include=['object'])
data = data.select_dtypes(exclude=['object'])

rows, cols = cat.shape


oh_data = one_hot_encode(data, rows, cols, cat)          #manually encoding categorical attributes to one-hot
print(oh_data)


# In[147]:


#10-fold cross validation

k = 10
oh_data = oh_data.fillna(0)
new_data = oh_data.values.astype("float64")
scaler = StandardScaler()
scaler.fit(new_data)
new_data = scaler.transform(new_data)
#target = target.values.astype("float64")
kf = KFold(n_splits = k, shuffle = True)
cv = kf.split(new_data)
acc1 = 0
acc2 = 0

for train_ind, test_ind in cv:
#     print(train_ind, test_ind)
    x_train, x_test = new_data[train_ind], new_data[test_ind]
    y_train, y_test = target[train_ind], target[test_ind]
    
    nh = int(x_train.shape[0]/(2*(x_train.shape[1]+len(np.unique(y_train)))))  # no.of hidden layer neurons

    acc_mlp1 = mlp(x_train, x_test, y_train, y_test, [20], 'r', 'house-price') # mlp tested on 
    acc_mlp2 = mlp(x_train, x_test, y_train, y_test, [20, 20], 'r', 'house-price') # house_price dataset
    acc1 = acc1+acc_mlp1
    acc2 = acc2+acc_mlp2
    
acc1 = (acc1/k)*100
acc2 = (acc2/k)*100

print('Overall accuracy on house-price dataset with multiple layer perceptron having 1 layer: ',acc1*100,'%')
print('Overall accuracy on house-price dataset with multiple layer perceptron having 2 layers: ',acc2*100,'%')

plotacc([acc1,acc2], ['mlp1','mlp2'], 'house-price')

