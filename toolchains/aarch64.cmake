set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "aarch64-linux-gnu-gcc")
set(CMAKE_CXX_COMPILER "aarch64-linux-gnu-g++")
#指定编译器

link_directories("${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/lib/aarch64/")
#添加库文件的查找路径

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/aarch64)
#设置可执行文件输出位置