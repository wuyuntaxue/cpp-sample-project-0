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
yaml-cpp读写配置文件模块：对应用程序的接口设计编写，yaml-cpp的使用
yaml-cpp打开文件时，如果路径不存在要创建路径、文件
获取GitHash，做成宏，用来表示版本编码
整理buildtime宏中时间格式
spdlog：确保多线程状态下功能正常，更多拓展功能（控制台和文件同时写的可能性）
json库的演示操作、编译是否正常
cmake控制的头文件
```



### 修改记录

#### 2022-05-07

```
添加spdlog库文件
添加base64编解码hpp
添加nlohmann/json.hpp

添加了base64的演示函数
在src/log/目录下添加了对spdlog的初始化等函数，添加spdlog的简单使用演示
```



#### 2022-04-30

```
新建工程，调试各个版本的cmake编译
增加yaml-cpp库，对应src/config目录下的文件调用，验证基础功能（x64）
```

