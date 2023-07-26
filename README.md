# cpp-sample-project-0

c++代码工程，个人使用的一个模板

包含使用c++构建工程时常用到的第三方库



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


### 注意事项

- 如果使用protobuf而机器没有安装时，需要进入3rd/protobuf-xxx/目录，手动编译（protobuf的库文件太大，超出github的限制）


### TODO List

```

编译选项研究：-fopenmp

完善test_log演示代码，研究线程名如何输出到log中，buildtime等
获取GitHash，做成宏，用来表示版本编码
整理buildtime宏中时间格式
cmake控制的头文件
build.sh功能完善
```



### 修改记录

### 2023-05-27
添加sqlite3库，还没完成使用示例
在Ubuntu20上编译出的库需要glic2.29，我另一台设备是Ubuntu18，就挺尴尬，所以保留了x64的两个版本的lib

### 2023-05-25
添加jemalloc的x86_64的库（V5.3.0）
添加test_jemalloc，不确定怎么用

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

