#include "base64/base64.hpp"
#include <iostream>
#include <string>

// base64
void base64_test() {

    std::string name = "Where there's pain, there's life.";
    // base64编码，传入数组和数据长度，返回string类型的base64字符串
    std::string baseStr = base64_encode(name.c_str(), name.size());

    std::cout << "baseStr: " << baseStr << std::endl;

    // base64解码，传入base64字符串，返回解码后的string
    std::string resultStr = base64_decode(baseStr);
    std::cout << "resultStr: " << resultStr << std::endl;
}

int main() {
    base64_test();

    return 0;
}