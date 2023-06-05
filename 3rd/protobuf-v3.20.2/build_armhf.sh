#/bin/bash
set -e

target_platform="armhf"
install_path=${PWD}/${target_platform}
build_thread=$(nproc)

mkdir -p ${target_platform}
rm ${target_platform}/* -rf

if [ ${build_thread} -gt 4 ]
then
    let build_thread=${build_thread}-2
fi

echo "install path=${install_path}"
echo "build thread=${build_thread}"

cd source

rm protobuf-3.20.2/ -rf

tar -xf protobuf-all-3.20.2.tar.gz

cd protobuf-3.20.2

./autogen.sh

./configure --prefix=${install_path} --host=arm-linux CC=arm-none-linux-gnueabihf-gcc CXX=arm-none-linux-gnueabihf-g++

make -j ${build_thread}

make install

echo "build down"
echo "lib & include path: ${install_path}"