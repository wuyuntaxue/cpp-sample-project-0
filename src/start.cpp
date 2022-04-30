#include "config/config.hpp"
#include <iostream>

int main(){
    std::cout << "taxue sample start" << std::endl;

    read_config_file_test("./config.yaml");

    std::cout << "taxue sample end\n------------" << std::endl;
    return 0;
}