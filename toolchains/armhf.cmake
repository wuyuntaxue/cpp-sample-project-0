set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "arm-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-linux-gnueabihf-g++")
#指定编译器

link_directories("${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/lib/armhf/")
#添加库文件的查找路径

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/armhf)
#设置可执行文件输出位置