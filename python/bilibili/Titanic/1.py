import pandas
titanic = pandas.read_csv("./titanic/train.csv")
titanic.head()

print(titanic.describe())

titanic["Age"] = titanic["Age"].fillna(titanic["Age"].median())

print(titanic["Sex"].unique())

titanic.loc[titanic["Sex"]=="male","Sex"] = 0
titanic.loc[titanic["Sex"]=="female","Sex"] = 1

print(titanic["Embarked"].unique())

titanic["Embarked"] = titanic["Embarked"].fillna('S')
titanic.loc[titanic["Embarked"]=="S","Embarked"] = 0
titanic.loc[titanic["Embarked"]=="C","Embarked"] = 1
titanic.loc[titanic["Embarked"]=="Q","Embarked"] = 2

from sklearn.linear_model import LinearRegression
from sklearn.model_selection import KFold

predictors = ["Pclass","Sex","Age","SibSp","Parch","Fare","Embarked"]

alg = LinearRegression()
kf = KFold(n_folds=3,random_state=1)

predictions = []

for train,test in enumerate(kf.split(titanic[predictors].iloc[train,:])):
    train_preditors = titanic[predictors].iloc[train,:]
    train_target = titanic["Survived"].iloc[train]
    alg.fit(train_preditors, train_target)
    test_predictions = alg.predict(titanic[predictors].iloc[test,:])
    predictions.append(test_predictions)