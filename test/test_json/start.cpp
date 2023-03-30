#include "nlohmann/json.hpp"

#include <fstream>
#include <iostream>
#include <string>

/*********************************************************/

// 通过重载to_json和from_json
class FrameStatus {
public:
    int len   = 0;
    int width = 0;
};

// 自带类型、常见的标准库容器，可以直接隐式转换成nlohmann::json类型
// 自定义的结构体，通过重载to_json和from_json函数，可以达到同样的效果
void to_json(nlohmann::json &j, const FrameStatus &p) {
    j = nlohmann::json{{"len", p.len}, {"width", p.width}};
}

void from_json(const nlohmann::json &j, FrameStatus &p) {
    if (j.contains("len") && j.at("len").is_number()) {
        j.at("len").get_to(p.len);
    }

    if (j.contains("width") && j.at("width").is_number()) {
        j.at("width").get_to(p.width);
    }
}

/*********************************************************/

// 不做nlohmann::json相关操作的自定义类型
class FrameStatus2 {
public:
    int len2   = 0;
    int width2 = 0;
};

/*********************************************************/

// 使用常规的解析、构建方式
class MessageType {
public:
    MessageType()
        : _size(0) {}
    int            parse_json(std::string &msg);
    nlohmann::json construct_json();
    void           print_private_value();

private:
    int              _size;
    std::string      _name;
    std::vector<int> _val;
    unsigned int     _numArr[10];
    FrameStatus      _status;
    FrameStatus2     _status2;
};

// 这里不符合的字段不会赋值，也没有报错，需要注意成员初值，或对关注的成员加上特殊处理
int MessageType::parse_json(std::string &msg) {
    nlohmann::json j;

    try {
        j = nlohmann::json::parse(msg);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    // 字段不存在时直接访问会抛出异常
    if (j.contains("size") && j.at("size").is_number()) {
        j["size"].get_to(_size);
        //or
        //_size = j["size"];
    }

    if (j.contains("name") && j.at("name").is_string()) {
        j["name"].get_to(_name);
    }

    if (j.contains("val") && j.at("val").is_array()) {
        j["val"].get_to(_val);
    }

    if (j.contains("num_arr") && j.at("num_arr").is_array()) {
        // 数组需要判断长度再赋值。长度和数组长度不一致时，直接get_to会抛出异常
        for (unsigned int i = 0; i < j.at("num_arr").size(); i++) {
            j["num_arr"][i].get_to(_numArr[i]);
        }
    }

    // 自定义类型已经特例化重载to/from_json
    if (j.contains("status") && j.at("status").is_object()) {
        j["status"].get_to(_status);
    }

    // 自定义类型未重载to/from_json
    if (j.contains("status2") && j.at("status2").is_object()) {
        nlohmann::json subj = j.at("status2");
        if (subj.contains("len2") && subj.at("len2").is_number()) {
            subj.at("len2").get_to(_status2.len2);
        }
        if (subj.contains("width2") && subj.at("width2").is_number()) {
            subj.at("width2").get_to(_status2.width2);
        }
    }

    return 0;
}

nlohmann::json MessageType::construct_json() {
    nlohmann::json j = {
        {"size", _size},
        {"name", _name},
        {"val", _val},
        {"num_arr", _numArr},
        {"status", _status},
        {"status2",
         {
             {"len2", _status2.len2},
             {"width2", _status2.width2},
         }},
    };
    return j;
}

void MessageType::print_private_value() {

    std::cout << "size = " << _size << ", name = " << _name << "\r\n";

    std::cout << "val = [";
    for (auto &i : _val) {
        std::cout << i << " ";
    }
    std::cout << "]\r\n";

    std::cout << "num_arr = [";
    for (unsigned int i = 0; i < sizeof(_numArr) / sizeof(unsigned); i++) {
        std::cout << _numArr[i] << " ";
    }
    std::cout << "]\r\n";

    std::cout << "status: { len : " << _status.len << ", width : " << _status.width << "}\r\n";
    std::cout << "status2: { len2 : " << _status2.len2 << ", width2 : " << _status2.width2 << "}\r\n";

    std::cout << std::endl;
}

/*********************************************************/


int main() {
    MessageType m1;
    // 正常的json字符串
    std::string msg1(
        "{\"size\":100, \"name\":\"abcd\", \"val\":[9,8,7,6,5], \"num_arr\":[1,2,3,4,5,6,7,8,9,10], "
        "\"status\":{\"len\":1024, \"width\": 1920}, \"status2\":{\"len2\":2048, \"width2\": 2440}}");
    // 触发各种异常的json字符串
    std::string msg2("{\"name\":\"abcd\", \"val\":12, \"num_arr\":[1,2,3]}");

    if (0 != m1.parse_json(msg1)) {
        std::cout << "parse json failed" << std::endl;
    }
    m1.print_private_value();

    std::cout << "------------------" << std::endl;
    nlohmann::json jnode = m1.construct_json();
    std::cout << "construct_json str = " << jnode.dump() << std::endl;

    std::cout << "------------------" << std::endl;

    {
        // 写入文件
        std::fstream confFile("./test.json", std::fstream::out);
        if (confFile.is_open()) {
            confFile << jnode;
            confFile.close();
            std::cout << "json file write sucess" << std::endl;
        }
    }

    {
        // 以文件流形式读取 json 文件
        nlohmann::json jtmp;
        std::fstream confFile("./test.json");

        confFile >> jtmp;
        std::cout << jtmp.at("size").get<int>() << " - " << jtmp.at("name").get<std::string>() << std::endl;
        confFile.close();
    }
    
    return 0;
}