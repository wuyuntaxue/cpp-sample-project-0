# cpp-sample-project-0

c++代码工程，个人使用的一个模板

包含使用c++构建工程，是常用到的第三方库

依赖的第三方库，尽量支持x64/aarch64/armhf三个版本



### Build

```shell
mkdir build
cd build
##########
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/x64.cmake ..
#or
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/armhf.cmake ..
#or
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/aarch.cmake ..
#########
make
```



### TODO List

```
yaml-cpp读写配置文件模块：对应用程序的接口设计编写
spdlog，日志模块有待添加
```



### 修改记录

#### 2022-04-30

```
新建工程，调试各个版本的cmake编译
增加yaml-cpp库，对应src/config目录下的文件调用，验证基础功能（x64）
```

