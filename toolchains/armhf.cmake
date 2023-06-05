set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "arm-none-linux-gnueabihf-gcc")
set(CMAKE_CXX_COMPILER "arm-none-linux-gnueabihf-g++")
#指定编译器

link_directories("${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/lib/armhf/")
link_directories("${PROJECT_SOURCE_DIR}/3rd/sqlite3-3420000/armhf/lib/")
link_directories("${PROJECT_SOURCE_DIR}/3rd/protobuf-v3.20.2/armhf/lib/")
#添加库文件的查找路径

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/armhf)
#设置可执行文件输出位置

set(PLATFORM "armhf" CACHE STRING "")