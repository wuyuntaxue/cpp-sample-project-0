cmake_minimum_required(VERSION 3.22)

project(taxue_sample VERSION 1.0.0)

aux_source_directory("${PROJECT_SOURCE_DIR}/src/config/" CONFIG_SRCS)

add_executable(sample_exe ${PROJECT_SOURCE_DIR}/src/start.cpp ${CONFIG_SRCS})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDSRD_REQUIRED True)
#指定c++版本

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -W")
#添加编译选项，显示编译过程中的waring

target_link_libraries(sample_exe PUBLIC -lyaml-cpp)
#链接库

target_include_directories(sample_exe PUBLIC 
                            "${PROJECT_SOURCE_DIR}/src"
                            "${PROJECT_SOURCE_DIR}/3rd/yaml-cpp/include"
                            )
