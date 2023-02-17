#/bin/bash
set -e

function Usage(){
echo "Usage: ./build.sh [options]

Help:
  -h               print this message

Standard options:
  -p=platform      target platform [x64/aarch64/armhf]

Sample:
  ./build.sh -p x64
"
}

target_platform=""

while getopts "p:h" arg
do
    case $arg in
    p)
        target_platform=$OPTARG
        ;;
    h)
        Usage
        exit 1
        ;;
    ?)
        Usage
        exit 1
        ;;
    esac
done

echo "----- create directory "

function cmake_toolchain_x64(){
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/x64.cmake ..
}

function cmake_toolchain_aarch64(){
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/aarch64.cmake ..
}

function cmake_toolchain_armhf(){
    cmake -DCMAKE_TOOLCHAIN_FILE=./toolchains/armhf.cmake ..
}

mkdir -p build
cd build
rm * -rf

echo "----- start build "

cmake_toolchain_$target_platform

make

echo "----- build done"