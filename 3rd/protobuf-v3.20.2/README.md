```shell
# 安装前置
$ sudo apt-get install autoconf automake libtool

# 初始化、配置安装路径
$ ./autogen.sh
$ ./configure --prefix=/usr/local/comenv/protobuf

# 编译
$ make -j4
$ sudo make install
#可以看到在指定路径下生成了lib\bin\include三个目录