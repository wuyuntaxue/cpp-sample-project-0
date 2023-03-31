# cpp-sample-project-0

c++代码工程，个人使用的一个模板

包含使用c++构建工程，是常用到的第三方库

依赖的第三方库，尽量支持x64/aarch64/armhf三个版本



### Build

```shell
./build.sh [option]
```

or

```shell
mkdir build
cd build
##########
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/x64.cmake ..
#or
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/armhf.cmake ..
#or
cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/aarch64.cmake ..
#########
make
```



### TODO List

```

完善test_log演示代码，研究线程名如何输出到log中，buildtime等


获取GitHash，做成宏，用来表示版本编码
整理buildtime宏中时间格式
spdlog：确保多线程状态下功能正常，更多拓展功能（控制台和文件同时写的可能性）
cmake控制的头文件
build.sh功能完善
```



### 修改记录

### 2023-03-21

修改log的使用方式，待完善

### 2023-03-30

完善test_json的代码

增加log的test代码，多个sinks的使用（控制台+文件）

#### 2023-03-29

config的mkdirs优化。

添加test子模块-先添加了test_base64，之后演示操作都可以单独做一个test工程

nlohmann::json的test模块，还需要完善。

#### 2023-03-23

config类（读写yaml配置文件），增加单例模式的接口

#### 2023-03-22

添加clang-format，并应用到自己（除第三方库）的代码上

修改build脚本，解决：不输入参数时不打印帮助信息的问题

#### 2023-02-17

添加了build.sh: 可以简单的根据参数选择目标平台（cmake的toolchain文件）

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

