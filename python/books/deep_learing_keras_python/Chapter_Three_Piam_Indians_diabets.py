from keras.models import Sequential
from keras.layers import Dense
import numpy as np
np.random.seed(7)
import pandas as pd

dataset = pd.read_csv('./pima-indians-diabetes.csv')
x = dataset.iloc[:,0:8]
y = dataset.iloc[:,8]

model = Sequential()
model.add(Dense(12,input_dim=8,activation='relu'))
model.add(Dense(8,activation='relu'))
model.add(Dense(1,activation='sigmoid'))
model.compile(loss='binary_crossentropy', optimizer='adam',metrics=['accuracy'])
model.fit(x=x,y=y,epochs=150,batch_size=10)

scores = model.evaluate(x=x, y=y)
print('\n%s: %.2f%%'%(model.metrics_names[1],scores[1]*100))