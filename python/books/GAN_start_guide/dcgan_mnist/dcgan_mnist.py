from keras.models import Sequential
from keras.layers import Dense,Reshape
from keras.layers.core import Activation
from keras.layers.normalization import BatchNormalization
from keras.layers.convolutional import UpSampling2D,Convolution2D,MaxPooling2D
from keras.layers.core import Flatten
from keras.optimizers import SGD
from keras.datasets import mnist
import numpy as np
from PIL import Image
import argparse
import math

def generator_model():
    model = Sequential()
    model.add(Dense(input_dim=100,output_dim=1024))
    model.add(Activation('tanh'))
    model.add(Dense(128*7*7))
    model.add(BatchNormalization())
    model.add(Reshape((7,7,128),input_shape=(128*7*7,)))
    model.add(UpSampling2D(size=(2,2)))
    model.add(Convolution2D(64,5,5,border_mode='same'))
    model.add(Activation('tanh'))
    model.add(UpSampling2D(size=(2,2)))
    model.add(Convolution2D(1,5,5,border_mode='same'))
    model.add(Activation('tanh'))
    return model

def discriminator_model():
    model = Sequential()
    model.add(Convolution2D(64,5,5,border_mode='same'),input_shape=(28,28,1))
    model.add(Activation('tanh'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    model.add(Convolution2D(128,5,5))
    model.add(Activation('tanh'))
    model.add(MaxPooling2D(pool_size=(2,2)))
    model.add(Flatten())
    model.add(Dense(1024))
    model.add(Activation('tanh'))
    model.add(Dense(1))
    model.add(Activation('sigmoid'))
    return model

def generator_containing_discriminator(generator,discriminator):
    model = Sequential()
    model.add(generator)
    discriminator.trainable = False
    model.add(discriminator)
    return model

def combine_images(generated_images):
    num = generated_images.shape[0]
    width = int(math.sqrt(num))
    height = int(math.ceil(float(num) / width))
    shape = generated_images.shape[2:]
    image = np.zeros((height*shape[0],width*shape[1]),dtype=generated_images.dtype)
    for index,img in enumerate(generated_images):
        i = int(index/width)
        j = index%width
        image[i*shape[0]:(i+1)*shape[0],j*shape[1]:(j+1)*shape[1]] = \ img[0,:,:]
        
