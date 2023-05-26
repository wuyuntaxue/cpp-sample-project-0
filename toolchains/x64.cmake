set(CMAKE_SYSTEM_NAME Linux)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
#指定编译器

link_directories("${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/lib/x64/")
link_directories("${PROJECT_SOURCE_DIR}/3rd/jemalloc/lib/x64/")
link_directories("${PROJECT_SOURCE_DIR}/3rd/sqlite3-3420000/x64/lib/")
#添加库文件的查找路径

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin/x64)
#设置可执行文件输出位置

set(PLATFORM "x64" CACHE STRING "")