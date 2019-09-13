import numpy as np
import tensorflow as tf
x_data = np.random.randn(2000,3)
w_real = [0.3,0.5,0.1]
b_real = -0.2

noise = np.random.randn(1,2000)*0.1
y_data = np.matmul(w_real,x_data.T) + b_real + noise


NUM_STEPS = 10

g = tf.Graph()
wb_ = []
with g.as_default():
    x = tf.placeholder(tf.float32,shape=[None,3])
    y_true = tf.placeholder(tf.float32,shape=[1,None])

    with tf.name_scope('inference') as scope:
        w = tf.Variable([[0,0,0]],dtype=tf.float32,name='weights')
        b = tf.Variable(0,dtype=tf.float32,name='bias')
        y_pred = tf.matmul(w,tf.transpose(x))+b

    with tf.name_scope('loss') as scope:
        loss = tf.reduce_mean(tf.square(y_pred-y_true))

    with tf.name_scope('train') as scope:
        learning_rate = 0.5
        optimizer = tf.train.GradientDescentOptimizer(learning_rate)
        train = optimizer.minimize(loss)
        init = tf.global_variables_initializer()
        with tf.Session() as sess:
            sess.run(init)
            for step in range(NUM_STEPS):
                sess.run(train,feed_dict={x: x_data, y_true: y_data})
                if (step % 5 == 0):
                    print(step,sess.run([w,b]))
                    wb_.append(sess.run([w,b]))
            print(10,sess.run([w,b]))


# out:
# 0 [array([[0.30068117, 0.49728695, 0.09489334]], dtype=float32), -0.18552221]
# 5 [array([[0.30072367, 0.4999596 , 0.10111057]], dtype=float32), -0.19938989]
# 10 [array([[0.30072367, 0.4999596 , 0.10111058]], dtype=float32), -0.19938989]