#!/bin/bash

# maven install

mvnpath=/usr/local/maven
# 不存在
if [ ! -d "$mvnpath" ]; then
    echo "正在创建$mvnpath目录"
    sudo mkdir $mvnpath
    echo "目录$mvnpath创建成功"
fi

#apache-maven-3.6
echo "正在下载maven安装包，请稍等..."

wget --no-cookies --no-check-certificate --header "Cookie: oraclelicense=accept-securebackup-cookie" "http://mirrors.hust.edu.cn/apache/maven/maven-3/3.3.9/binaries/apache-maven-3.3.9-bin.tar.gz"

mvnfile=$(ls | grep apache*maven-*.gz)


if [ -f "$mvnfile" ]; then

    #这个名字其实就是mvn .tar.gz解压之后的文件夹的名字
    mvndirname="apache-maven-3.3.9-bin"

    #不能加 用'zxvf' 加了 z 就创建了包里面的apace* 文件夹，而我们只要把apace*文件夹下的文件全部解压到 mvnpath里面就好
    #--strip-components N 表示删除目录结构（n=1表示删除最外【或前1】层结构）
    tar zxvf $mvnfile -C $mvnpath --strip-components 1    

    echo "安装maven成功"
    echo "配置环境变量"

    mv ~/.bashrc ~/.bashrc.backup.mvn
    cat ~/.bashrc.backup.mvn >> ~/.bashrc

    echo "PATH=\"$PATH:$mvnpath/bin\"" >> ~/.bashrc
    echo "MAVEN_HOME=$mvnpath" >> ~/.bashrc

    source ~/.bashrc
	
	echo "PATH=\"$PATH:$mvnpath/bin\"" >> /etc/profile
    echo "MAVEN_HOME=$mvnpath" >> /etc/profile
	
	source /etc/profile

    echo "刷新profile"
	source /etc/profile
    echo "刷新成功"
    echo "配置环境成功"
    echo "测试是否安装成功"
    mvn -v
    echo "安装成功"
	echo "删除脚本和压缩包"
	rm -rf maven.sh $mvnfile
	
else
    echo "没有找到maven文件"

fi

export NEXUS_HOME=/usr/local/nexus
export PATH=$PATH:$NEXUS_HOME/bin