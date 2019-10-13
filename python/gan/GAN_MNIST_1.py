import tensorflow as tf
from matplotlib import pyplot as plt
import pickle
import numpy as np

%matplotlib inline

from tensorflow.examples.tutorials.mnist import input_data
mnist = input_data.read_data_sets('./MNIST_data')

img = mnist.train.images[50]
plt.imshow(img.reshape((28,28)))

def get_inputs(real_size,noise_size):
    real_img = tf.placeholder(tf.float32,[None,real_size],name='real_img')
    noise_img = tf.placeholder(tf.float32,[None,noise_size],name='noise_img')
    return real_img,noise_img

def get_generator(noise_img,n_units,out_dim,reuse=False,alpha=0.01):
    """
    生成器
    
    noise_img: 生成器的输入
    n_units: 隐层单元个数
    out_dim: 生成器输出tensor的size，这里应该为32*32=784
    alpha: leaky ReLU系数
    """
    with tf.variable_scope("generator", reuse=reuse):
        hidden1 = tf.layers.dense(noise_img,n_units)
        hidden1 = tf.maximum(alpha*hidden1,hidden1)
        hidden1 = tf.layers.dropout(hidden1,rate=0.2)
        logits = tf.layers.dense(hidden1,out_dim)
        outputs = tf.tanh(logits)
        return logits,outputs
    
def get_discriminator(img,n_units,reuse=False,alpha=0.01):
    """
    判别器
    
    n_units: 隐层结点数量
    alpha: Leaky ReLU系数
    """
    with tf.variable_scope("discriminator",reuse=reuse):
        hidden1 = tf.layers.dense(img, n_units)
        hidden1 = tf.maximum(alpha*hidden1,hidden1)
        
        logits = tf.layers.dense(hidden1,1)
        output = tf.sigmoid(logits)
        
        return logits,output
    

# 定义参数
# 真实图像的size
img_size = mnist.train.images[0].shape[0]
# 传入给generator的噪声size
noise_size = 100
# 生成器隐层参数
g_units = 128
# 判别器隐层参数
d_units = 128
# leaky ReLU的参数
alpha = 0.01
# learning_rate
learning_rate = 0.001
# label smoothing
smooth = 0.1

tf.reset_default_graph()
real_img,noise_img = get_inputs(img_size,noise_size)
g_logits,g_outputs = get_generator(noise_img,g_units,img_size)
d_logits_real,d_outputs_real = get_discriminator(real_img,d_units)
d_logits_fake,d_outputs_fake = get_discriminator(g_outputs,d_units,reuse=True)


d_loss_real = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_logits_real, labels=tf.ones_like(d_logits_real))*(1-smooth))
d_loss_fake = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_logits_fake, labels=tf.zeros_like(d_logits_fake)))
d_loss = tf.add(d_loss_real, d_loss_fake)
g_loss = tf.reduce_mean(tf.nn.sigmoid_cross_entropy_with_logits(logits=d_logits_fake,labels=tf.ones_like(d_logits_fake))*(1-smooth))

train_vars = tf.trainable_variables()
g_vars = [var for var in train_vars if var.name.startswith("generator")]
d_vars = [var for var in train_vars if var.name.startswith("discriminator")]
d_train_opt = tf.train.AdamOptimizer(learning_rate).minimize(d_loss, var_list=d_vars)
g_train_opt = tf.train.AdamOptimizer(learning_rate).minimize(g_loss, var_list=g_vars)

batch_size = 64
epochs = 300
n_sample = 25
samples = []
losses = []
saver = tf.train.Saver(var_list=g_vars)

with tf.Session() as sess:
    sess.run(tf.global_variables_initializer())
    for e in range(epochs):
        for batch_i in range(mnist.train.num_examples//batch_size):
            batch = mnist.train.next_batch(batch_size)
            batch_images=batch[0].reshape(batch_size,784)
            batch_images = batch_images*2-1
            batch_noise = np.random.uniform(-1,1,size=(batch_size,noise_size))
            
            _ = sess.run(d_train_opt,feed_dict={real_img:batch_images,noise_img:batch_noise})
            _ = sess.run(g_train_opt,feed_dict={noise_img:batch_noise})
            
        train_loss_d = sess.run(d_loss,feed_dict={real_img:batch_images,noise_img:batch_noise})
        train_loss_d_real = sess.run(d_loss_real,feed_dict={real_img:batch_images,noise_img:batch_noise})
        train_loss_d_fake = sess.run(d_loss_fake,feed_dict={real_img:batch_images,noise_img:batch_noise})
        train_loss_g = sess.run(g_loss,feed_dict={noise_img:batch_noise})
        
        print("Epochs{}/{}...".format(e+1,epochs),
              "Discriminator loss: {:.4f}(Real:{:.4f}+Fake:{:.4f})...".format(train_loss_d,train_loss_d_real,train_loss_d_fake),
              "Generator loss:{:.4f}".format(train_loss_g))
        losses.append((train_loss_d,train_loss_d_real,train_loss_d_fake,train_loss_g))
        sample_noise = np.random.uniform(-1,1,size=(n_sample,noise_size))
        gen_samples = sess.run(get_generator(noise_img,g_units,img_size,reuse=True),
                               feed_dict={noise_img:sample_noise})
        samples.append(gen_samples)
        saver.save(sess,'./checkpoints/generator.ckpt')
        
with open('train_samples.pkl','wb') as f:
    pickle.dump(samples,f)
    
fig,ax = plt.subplots(figsize=(20,7))
losses = array(losses)
plt.plot(losses.T[0],label='Discriminator Total Loss')
plt.plot(losses.T[1],label='Discriminator Real Loss')
plt.plot(losses.T[2],label='Discriminator Fake Loss')
plt.plot(losses.T[3],label='Generator')
plt.title("Training Losses")
plt.append()

with open ('train_samples.pkl','rb') as f:
    samples = pickle.load(f)

def view_samples(epoch,samples):
    """
    epoch代表第几次迭代的图像
    samples为我们的采样结果
    """
    fig,axes = plt.subplots(figsize=(7,7),nrows=5,ncols=5,sharey=True,sharex=True)
    for ax,img im zip(axes.flatten(),samples[epoch][1]):
        ax.xaxis.set_visible(False)
        ax.yaxis.set_visible(False)
        im = ax.imshow(img.reshape(28,28))
    return fig, axes

_ = view_samples(-1,samples)

epoch_idx = [0,5,10,20,40,60,80,100,150,250]
show_img = []
for i in epoch_idx:
    show_img.append(samples[i][1])
    
rows,cols = 10,25
fig,axes = plt.subplots(figsize=(30,20),nrows=rows,ncols=cols,sharex=True,sharey=True)
idx = range(0,epochs,int(epochs/rows))

for sample,ax_row in zip(show_imgs,axes):
    for img,ax in zip(sample[::int(len(sample)/cols)],ax_row):
        ax.imshow(img.reshape(28,28))
        ax.xaxis.set_visible(False)
        ax.yaxis.set_visible(False)
        
saver = tf.train.Saver(var_list=g_vars)
with tf.Session() as sess: 
    saver.restore(sess,tf.train.latest_checkpoint('checkpoints'))
    sample_noise = np.random.uniform(-1,1,size=(25,noise_size))
    gen_samples = sess.run(get_generator(noise_img,g_units,img_size,reuse=True),
                           feed_dict={noise_img:sample_noise})
    

_ = view_samples(0,[gen_samples])