#!/bin/bash
#下载的zookeeper版本
ZOOKEEPER=zookeeper-3.4.10.tar.gz

#定义服务名称  需要自己配置，看自己的机器
SERVER1=zookeeper1
SERVER2=zookeeper2
SERVER3=zookeeper3

#定义端口  需要自己配置，看自己的机器
SERVER1_PORT=2182
SERVER2_PORT=2183
SERVER3_PORT=2184

#拷贝配置文件
copyFile(){

        conf_file_path=$1

        #获取当前传递进来的文件夹的路径
        conf_file_dir=$(cd "$(dirname "$1")"; pwd)
        new_file_path=$conf_file_dir"/zoo.cfg"

        #创建一个新文件
        #touch $new_file_path

        cp $conf_file_path $new_file_path

        #新文件地址
        echo $new_file_path
}

#配置文件
configFile(){
if [ "$1" != "" ]
    then

        new_file_path=$(copyFile $1)
        #新文件地址
        echo $new_file_path

        echo $2
        #--------------------update file----------------------
        sed -i 's#/tmp/zookeeper#/tmp/'$2'/data#' $new_file_path

        #添加log日志
        sed -i '/^dataDir/a\dataLogDir=\/tmp\/'$2'\/logs' $new_file_path

        #设定ip
        sed -i 's/2181/'$3'/g'  $new_file_path

        #追加服务配置
        sed -i '$a \server.1=127.0.0.1:2222:2225\nserver.2=127.0.0.1:3333:3335\nserver.3=127.0.0.1:4444:4445 ' $new_file_path

else
        echo '大兄弟，请指定你的zookeeperのzoo.cfg文件路径啊'
fi
}

#安装文件
installFile(){

    echo "开始下载文件"
    echo "默认指定下载目录为/usr/local/"

    read -p "指定下载的目录:" name
    path="/usr/local"
        if [ "$name" == "" ]
        then
                echo "设置为默认路径:/usr/local/"
        elif $(test -d "$name")
        then
                #echo $name
        path=$name
    fi

    out_file_path=$path/zookeeper

    echo "当保存载目录是"$out_file_path

    #创建文件夹
    mkdir -p $out_file_path    

    SERVER1_OUT_PATH=$out_file_path/$SERVER1/
    SERVER2_OUT_PATH=$out_file_path/$SERVER2/
    SERVER3_OUT_PATH=$out_file_path/$SERVER3/

    ehco "-------------------清空文件夹------------------" 
    #清空以前解压的
    rm -rf $SERVER1_OUT_PATH
    rm -rf $SERVER2_OUT_PATH
    rm -rf $SERVER3_OUT_PATH

    #创建文件夹
    mkdir -p $SERVER1_OUT_PATH
    mkdir -p $SERVER2_OUT_PATH
    mkdir -p $SERVER3_OUT_PATH

    #创建文件夹
    echo "创建文件夹"$SERVER1_OUT_PATH
    echo "创建文件夹"$SERVER2_OUT_PATH
    echo "创建文件夹"$SERVER3_OUT_PATH


    #下载文件
    wget -O $out_file_path/$ZOOKEEPER http://yellowcong.qiniudn.com/zookeeper-3.4.10.tar.gz 

    echo "文件下载地址"$out_file_path/$ZOOKEEPER

    #解压文件
    echo "-------------------解压文件----------------"

    #解压到指定的文件夹
    tar -zxvf $out_file_path/$ZOOKEEPER -C $SERVER1_OUT_PATH
    cp -rf $SERVER1_OUT_PATH/* $SERVER2_OUT_PATH
    cp -rf $SERVER1_OUT_PATH/* $SERVER3_OUT_PATH

    echo "----------------集群配置-------------------"
    #配置集群，配置集群文件
    configFile $SERVER1_OUT_PATH/zookeeper-3.4.10/conf/zoo_sample.cfg $SERVER1 $SERVER1_PORT
    configFile $SERVER2_OUT_PATH/zookeeper-3.4.10/conf/zoo_sample.cfg $SERVER2 $SERVER2_PORT
    configFile $SERVER3_OUT_PATH/zookeeper-3.4.10/conf/zoo_sample.cfg $SERVER3 $SERVER3_PORT


    echo "----------------配置myid文件---------------"
    #配置文件夹
    mkdir -p /tmp/$SERVER1/data
    mkdir -p /tmp/$SERVER1/logs
    echo 1 > /tmp/$SERVER1/data/myid

    mkdir -p /tmp/$SERVER2/data
    mkdir -p /tmp/$SERVER2/logs
    echo 2 > /tmp/$SERVER2/data/myid

    mkdir -p /tmp/$SERVER3/data
    mkdir -p /tmp/$SERVER3/logs
    echo 3 > /tmp/$SERVER3/data/myid

    echo "------------------启动文件-----------------"
    #启动集群   
    sh $out_file_path/$SERVER2/zookeeper-3.4.10/bin/zkServer.sh start 
    sh $out_file_path/$SERVER3/zookeeper-3.4.10/bin/zkServer.sh start
    sh $out_file_path/$SERVER1/zookeeper-3.4.10/bin/zkServer.sh start

    echo "-----------------查看启动状态---------------"
    #查看集群情况
    sh $out_file_path/$SERVER2/zookeeper-3.4.10/bin/zkServer.sh status
    sh $out_file_path/$SERVER3/zookeeper-3.4.10/bin/zkServer.sh status
    sh $out_file_path/$SERVER1/zookeeper-3.4.10/bin/zkServer.sh status
}

installFile

# chmod +x install.sh
