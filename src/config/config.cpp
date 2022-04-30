#include "config.hpp"
#include <iostream>
#include <fstream>

using namespace std;

int read_config_file_test(std::string filename){
    YAML::Node config;
    try{
         config = YAML::LoadFile(filename);
    }catch(YAML::BadFile &e){
        std::cout<<"read error!"<<std::endl;
        return -1;
    }
    
    try{
        cout << "Node type " << config.Type() << endl;
        cout << "taxue type " << config["taxue"].Type() << endl;
    }catch(std::exception &e){
        std::cout << "read type error!"<< e.what() <<std::endl;
    }
    
 
    try{
        //可以用string类型作为下表，读取参数
        string age = "age";
        cout << "age when string is label:" << config["taxue"][age].as<int>() << endl;
    }catch(YAML::TypedBadConversion<int> &e){
        std::cout<<"label node is NULL"<<std::endl;
    }
    
    //读取不存在的node值，报YAML::TypedBadConversion异常
    try{
        cout << "name:" << config["taxue"]["name"].as<string>() << endl;
    }catch(YAML::TypedBadConversion<string> &e){
        std::cout<<"label node is NULL"<<std::endl;
    }//TypedBadConversion是模板类，读取什么类型的参数就传入什么类型
 
    // for(YAML::const_iterator it= config["skills"].begin(); it != config["skills"].end();++it)
    // {
    //     cout << it->first.as<string>() << ":" << it->second.as<int>() << endl;
    // }
 
    // YAML::Node test1 = YAML::Load("[1,2,3,4]");
    // cout << " Type: " << test1.Type() << endl;
 
    // YAML::Node test2 = YAML::Load("1");
    // cout << " Type: " << test2.Type() << endl;
 
    // YAML::Node test3 = YAML::Load("{'id':1,'degree':'senior'}");
    // cout << " Type: " << test3.Type() << endl;
 
    ofstream fout(filename);
 
    config["taxue"]["happy"] = 99;//添加新元素
 
    fout << config;
    fout.close();
    return 0;
}