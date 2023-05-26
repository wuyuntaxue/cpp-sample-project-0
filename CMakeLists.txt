cmake_minimum_required(VERSION 3.22)

project(taxue_sample VERSION 1.0.0)

aux_source_directory("${PROJECT_SOURCE_DIR}/src/config/" CONFIG_SRCS)
aux_source_directory("${PROJECT_SOURCE_DIR}/src/log/" LOG_SRCS)

add_executable(sample_exe ${PROJECT_SOURCE_DIR}/src/start.cpp ${CONFIG_SRCS} ${LOG_SRCS})

#指定c++版本
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDSRD_REQUIRED True)

#添加编译选项，显示编译过程中的waring
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -W -Werror=return-type")

#链接库
target_link_libraries(sample_exe PUBLIC -lyaml-cpp -lpthread)

#头文件查找目录
target_include_directories(sample_exe PUBLIC
                            "${PROJECT_SOURCE_DIR}/src"
                            "${PROJECT_SOURCE_DIR}/3rd"
                            "${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/include"
                            "${PROJECT_SOURCE_DIR}/3rd/spdlog/include"
                            "${PROJECT_SOURCE_DIR}/3rd/jemalloc/include"
                            )

#添加子项目
add_subdirectory(${PROJECT_SOURCE_DIR}/test)