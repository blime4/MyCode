# hexo+butterfly+github做一个免费好看的博客





> 感谢开源，让我一天轻松搭建了一个好看的博客
>
> 我用的是ubuntu 18.04



下面是自己的总结，写一个教程

网上也有很多很好的教程，也可以直接去看别人的，哈哈哈

下面列举几个对我很有帮助的教程，和我用到的好用的网站



+ [hexo官方中文文档](https://hexo.io/zh-cn/index.html)

+ [Butterfly 演示DEMO](https://jerryc.me/)

  上面两个网站很有帮助，可以直接看上面的，然后关掉这篇教程都没问题了。

  第二个貌似要科学上网才能进去

+ [HCLonely Blog](https://blog.hclonely.com/)

+ [https://sm.ms/  免费好用的图床](https://sm.ms/)

+ [免费高质量图库](https://www.pexels.com/zh-cn/)

  

## 下面正式开始我的教程



### 1.安装必备的一些东西

#### nodejs

```
curl -sL https://deb.nodesource.com/setup_10.x | sudo -E bash -
sudo apt-get install -y nodejs
```

查看自己是否安装成功

```
node -v
npm -v 
```

显示版本号就说明成功了

#### npm淘宝镜像 

> 不然会超级卡

```
npm config set registry https://registry.npm.taobao.org
```

检查是否安装成功

```
npm config get registry
```

>个人测试发现 cnpm有时候也会很慢，所以不用安装



### 2. 安装hexo

哈哈哈 以下就是官网中的五步

```
npm install hexo-cli -g
hexo init blog
cd blog
npm install
hexo server
```

具体意思就是 安装hexo， -g  就是全局安装的意思，这样哪里都能用

init 就是初始化 ，这一步可能比较久 大家耐心 一会 

npm install 就是 再安装一些 需要的依赖

然后就可以hexo server 打开了



也可以 hexo g 生成静态页面 再 hexo s 打开

然后就可以在localhost:4000 中打开了



### 3.一些文件的介绍

+ _config.yml ：全局配置文件 

  

### 4 安装Butterfly

[hexo-theme-butterfly 安裝文檔(一)快速開始](https://jerryc.me/posts/21cfbf15/)

可直接参考上面的链接

如果打不开，可以看下面(我只是加了一点点提示，其余一样的)

#### 安装

在你的博客的根目录拷下来

```
git clone -b master https://github.com/jerryc127/hexo-theme-butterfly.git themes/Butterfly
```

如果想要安装比较新的 dev 分支，可以

```
git clone -b dev https://github.com/jerryc127/hexo-theme-butterfly.git themes/Butterfly
```

> 由于某些原因 哈哈哈 我现在用的是最新的dev分支



#### 应用主题

修改站点配置文件`_config.yml`，把主题改为 `Butterfly`

```
theme: Butterfly
```

> 对小白的贴士：
>
> 不是themes/Butterfly/ 里面的_config.yml 是根目录那个_

>如果你没有 pug 以及 stylus 的渲染器，请下载安装： `npm install hexo-renderer-pug hexo-renderer-stylus --save` or `yarn add hexo-renderer-pug hexo-renderer-stylus`

#### 平滑升级

为了主题的平滑升级，`Butterfly` 使用了 [data files](https://hexo.io/docs/data-files.html) 特性。

推荐把主题默认的配置文件`_config.yml` 复製到 Hexo 工作目录下的 `source/_data/butterfly.yml`，如果 `source/_data` 的目录不存在那就创建一个。

> 注意，如果你创建了 `butterfly.yml`, 它将会替换主题默认配置文件`_config.yml` 里的配置项 (**不是合併而是替换**), 之后你就只需要通过 `git pull` 的方式就可以平滑地升级 `theme-butterfly` 了。



> 反正这里都是很简单的，要注意不要搞错文件就好了
>
> 然后就安装好了

可以输入下面的命令来看看你的新主题

```
hexo clean && hexo g && hexo s  
```

然后就搞定了



### 5 部署到GitHub上

这里我是参考[Hexo+Butterfly+Github+Coding搭建个人博客](https://www.jianshu.com/p/a1a4ebf0e5fc)的，也可以直接点进去看

#### 创建仓库 

格式就是 你的名字.github.io

其他不行

![image-20200615233308906](image-20200615233308906.png)

#### 配置GIt

如果第一次使用git的话，需要设置用户名和邮箱:

```
git config --global user.name "your username"
git config --global user.email "your email"
```

#### 生成公钥

执行以下命令，然后连续三次回车,生成公钥:

> 直接回车 什么都不用写

```
ssh-keygen -t rsa
```

然后 进去 你就能看到`id_rsa`  `id_rsa.pub`两个文件了 就是私钥公钥 

找到id_rsa.pub文件,用文本编辑工具打开，并复制所有文本内容

```
cd ~/.ssh/
vim id_rsa.pub
```



打开浏览器

在Github页面右上角，点击用户头像-Settings-SSH and GPG keys-New SSH key

![img](3381990-89f132eba45e498d.png)

![img](3381990-db59e95e40c39a1f.png)

Title可以随意填写，Key需要填写刚才复制的公钥文本内容。

添加完成后，在控制台输入:

```
ssh -T git@github.com
```

然后就配置好了



#### 上传文件到Github



打开_config.yml，在最后面的deploy做以下修改

```
deploy:
  type: git
  repo: #你的仓库地址,如:https://github.com/milovemengmeng/milovemengmeng.github.io.git
  branch: master
```

安装一个插件

```
npm install hexo-deployer-git --save
```

安装好了之后,就可以输入`hexo d`部署到GitHub上了，d 就是deploy 部署

```
hexo d
```

然后就ok了

就可以在浏览器输入

你的名字.github.io 进入博客了





至于后续我有空还会更新关于 gitalk 的教程 和 音乐播放器的教程

其实网上都有， 我也可能不会更新。哈哈哈

