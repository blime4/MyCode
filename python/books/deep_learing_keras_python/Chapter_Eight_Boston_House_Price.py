from sklearn import datasets
import numpy as np
from keras.models import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasRegressor
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import GridSearchCV
from sklearn.pipeline import Pipeline

dataset = datasets.load_boston()
x = dataset.data
y = dataset.target

seed = 7
np.random.seed(seed)

def create_model(units_list=[13],optimizer='adam',init='normal'):
    