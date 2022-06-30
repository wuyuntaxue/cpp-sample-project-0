#include "config.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

configType::configType(){

}

configType::configType(std::string filename){
    m_filename = filename;
}

configType::~configType(){

}

//读取配置文件，并将配置项赋值到相应变量
void configType::read_config_file(std::string filename){
    try{
        YAML::Node yml = YAML::LoadFile(filename);
        if(yml["taxue"]){  //确认节点是否存在

            if(yml["taxue"]["name"]){  //确认节点是否存在，这里代表taxue节点下的name节点
                data.name =  yml["taxue"]["name"].as<std::string>();  //string类型
            }

            if(yml["taxue"]["age"]){
                data.age =  yml["taxue"]["age"].as<int>();  //int类型
            }

            if(yml["taxue"]["grade"]){
                data.grade = yml["taxue"]["grade"].as<double>();  //浮点型
            }

            if(yml["taxue"]["ishuman"]){
                data.isHuman = yml["taxue"]["ishuman"].as<bool>();  //bool型
            }

            if(yml["taxue"]["numbers"]){
                data.numbers = yml["taxue"]["numbers"].as< std::vector<int> >();  //标准容器类型
            }
        }
    }catch(std::exception& e){
        std::cout<< "read file error:" << e.what() <<std::endl;
        return;
    }
}

void configType::read_config_file(){
    read_config_file(m_filename);
}

//递归创建多层目录，假设string是正常的，所以此函数存在风险
int configType::mkdirs(std::string path, mode_t mode){
    int ret = access( path.c_str(), F_OK);
    if(ret != 0){
        auto loc = path.rfind("/");
        std::string subpath = path.substr(0,loc);

        if( mkdirs(subpath, mode) != 0){
            return -1;
        }
        
        if( mkdir( path.c_str(), mode) != 0 ){
            std::cout << "creat failed" << std::endl;
            return -1;
        }else{
            std::cout << "creat success" << std::endl;
        }
    }
    return 0;
}

//保存配置项到文件
void configType::save_config_file(std::string filename){

    //确认文件是否存在
    int ret = access( filename.c_str(), F_OK);
    if(ret != 0){
        auto loc = filename.rfind("/");
        std::string pathname = filename.substr(0,loc);
        
        if( mkdirs( pathname.c_str(), 0755) != 0 ){
            std::cout << "save config error: failed mkdir " << std::endl;
        }
    }

    YAML::Node yml;
    std::ofstream fout(filename);

    try{
        yml["taxue"]["name"]   = data.name;
        yml["taxue"]["age"]    = data.age;
        yml["taxue"]["grade"]  = data.grade;
        yml["taxue"]["ishuman"] = data.isHuman;
        yml["taxue"]["numbers"] = data.numbers;

        fout << yml;
        
    }catch(std::exception& e){
        std::cout << "save config error:" << e.what() << std::endl;
    }

    fout.close();
}

void configType::save_config_file(){
    save_config_file(m_filename);
}

//将配置项打印出来
void configType::print_config(){
    std::cout << "-----------config data---------------" << std::endl;
    std::cout << "name: " << data.name << std::endl;
    std::cout << "age: " << data.age << std::endl;
    std::cout << "grade:" << data.grade << std::endl;
    std::cout << "ishuman: " << data.isHuman << std::endl;

    for(const auto &n : data.numbers){
        std::cout << n << " ";
    }
    std::cout << std::endl;

    std::cout << "-------------------------------------" << std::endl;
}