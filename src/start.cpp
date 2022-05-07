#include "config/config.hpp"
#include <iostream>
#include "log/log.hpp"
#include "base64/base64.hpp"

//base64演示
void base64_test(){
    std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG);

    const char* name = "Where there's pain, there's life.";
    std::string baseStr = base64_encode(name, strlen(name));  //base64编码，传入数组和数据长度，返回string类型的base64字符串

    _logger->warn("baseStr: {}", baseStr);

    std::string resultStr = base64_decode(baseStr);  //base64解码，传入base64字符串，返回解码后的string
    
    _logger->warn("resultStr: {}", resultStr);
}



int main(){
    std::cout << "taxue sample start" << std::endl;
    log_init();  //初始化spd日志

    std::shared_ptr<spdlog::logger> _logger = spdlog::get(LOG_TAG); //在初始化日志之后，进程的任意位置可以获取log
    _logger->info("hello spdlog");

    read_config_file_test("./config.yaml");

    std::string s1="heihei";
    _logger->info("read config file done,{} and {}", 100, s1);

    base64_test();

    _logger->warn("[{}:{}]sample project done, goodbye(^_^)", __FILENAME__, __LINE__);
    log_drop();  //释放日志
    return 0;
}