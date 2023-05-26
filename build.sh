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

Sample:
  ./build.sh -p x64
"
}

target_platform=""
build_thread=$(nproc)

while getopts "p:hj:" arg
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

make -j ${build_thread}

echo "----- build done"