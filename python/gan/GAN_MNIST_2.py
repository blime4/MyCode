import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
import pickle

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('./MNIST_data')

i = 10
img = mnist.train.images[i]
plt.imshow(img.reshape((28,28)), cmap='Greys_r')

def get_inputs(noise_dim,image_height,image_width,image_depth):
    """
    :param noise_dim: ����ͼƬ��size
    :param image_height: ��ʵͼ���height
    :param image_width: ��ʵͼ���width
    :param image_depth: ��ʵͼ���depth
    """
    inputs_real =tf.placeholder(tf.float32,[None,image_width,image_height,image_depth],name='inputs_real')
    inputs_noise =tf.placeholder(tf.float32,[None,noise_dim],name='inputs_noise')
    
    return inputs_real, inputs_noise

def get_generator(noise_img,output_dim,is_train=True,alpha=0.01):
    """
    :param noise_img: �����źţ�tensor����
    :param output_dim: ����ͼƬ��depth
    :param is_train: �Ƿ�Ϊѵ��״̬���ò�����Ҫ������Ϊbatch_normalization�����еĲ���ʹ��
    :param alpha: Leaky ReLUϵ��
    """
    with tf.variable_scope("generator",reuse=(not is_train)):
        # 100 x 1 to 4 x 4 x 512
        # ȫ���Ӳ�
        layer1 = tf.layers.dense(noise_img,4*4*512)
        layer1 = tf.reshape(layer1,[-1,4,4,512])
        layer1 = tf.layers.batch_normalization(layer1,training=is_train)
        layer1 = tf.maximum(alpha*layer1, layer1)
        layer1 = tf.nn.dropout(layer1,keep_prob=0.8)
        # 4 x 4 x 512 to 7 x 7 x 256
        layer2 = tf.layers.conv2d_transpose(layer1,256,4, stride=1, padding='valid')
        layer2 = tf.layers.batch_normalization(layer2,training=is_train)
        layer2 = tf.maximum(alpha*layer2,layer2)
        layer2 = tf.nn.dropout(layer2,keep_prob=0.8)
        # 7 x 7 256 to 14 x 14 x 128
        layer3 = tf.layers.conv2d_transpose(layer2,128,3,strides=2,padding='same')
        layer3 = tf.layers.batch_normalization(layer3,training=is_train)
        layer3 = tf.maximum(alpha*layer3, layer3)
        layer3 = tf.nn.dropout(layer3,keep_prob=0.8)
        # 14 x 14 x 128 to 28 x 28 x 1
        logits = tf.layers.conv2d_transpose(layer3,output_dim,3,strides=2,padding='same')
        # MNISTԭʼ���ݼ������ط�Χ��0-1�����������ͼƬ��ΧΪ(-1,1)
        # �����ѵ��ʱ����סҪ��MNIST���ط�Χ����resize
        outputs = tf.tanh(logits)
        
        return outputs        
        