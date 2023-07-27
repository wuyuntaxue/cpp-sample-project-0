#/bin/bash
set -e

function Usage(){
echo "
Usage: ./build.sh [options]

Help:
  -h               print this message

Standard options:
  -p platform      target platform [x64/aarch64/armhf]

Build thread:
  -j thread nums   default: $(nproc)

Build Test:
  -t               build test

Debug:
  -r               build type(Release or Debug)

Sample:
  ./build.sh -p x64
"
}

target_platform=""
build_thread=$(nproc)
cmake_build_type="Release"

# 是否编译test模块
is_build_test="NO"

while getopts "p:htj:r:" arg
do
    case $arg in
    p)
        target_platform=$OPTARG
        ;;
    j)
        build_thread=$OPTARG
        ;;
    h)
        Usage
        exit 0
        ;;
    t)
        is_build_test="YES"
        ;;
    r)
        cmake_build_type=$OPTARG
        if [[ ${cmake_build_type} == "Debug" || ${cmake_build_type} == "Release" ]];then
            cmake_build_type=${cmake_build_type}
        else
            echo "cmake build type is invalid! should be Release or Debug"
            cmake_build_type="Release"
        fi
        ;;
    ?)
        Usage
        exit 1
        ;;
    esac
done

if [ "$target_platform" = "" ] 
then
    echo "The target platform must be specified" >&2
    Usage
    exit 1
fi

echo "----- create directory "

function cmake_toolchain_x64(){
    cmake -D CMAKE_TOOLCHAIN_FILE=./toolchains/x64.cmake \
          -D IS_BUILD_TEST=${is_build_test} \
          -D CMAKE_BUILD_TYPE=${cmake_build_type} \
          ..
}

function cmake_toolchain_aarch64(){
    cmake -D CMAKE_TOOLCHAIN_FILE=./toolchains/aarch64.cmake \
          -D IS_BUILD_TEST=${is_build_test} \
          ..
}

function cmake_toolchain_armhf(){
    cmake -D CMAKE_TOOLCHAIN_FILE=./toolchains/armhf.cmake \
          -D IS_BUILD_TEST=${is_build_test} \
          ..
}

mkdir -p build
cd build
rm * -rf

echo "----- start build "

cmake_toolchain_$target_platform

make -j ${build_thread}

echo "----- build done"