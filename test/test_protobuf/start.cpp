#include "hello/hello.pb.h"
#include "log/log.hpp"

#include <iostream>
#include <string>


// 序列化
int serialize(std::string &resStr) {
    SCH::Student stu;

    // 向对象中填值
    stu.set_id(23456);                        // 普通成员会有set函数来赋值
    stu.set_name("stu1");
    *stu.mutable_email() = "hello@world.com"; // string成员会多一些接口，mutable会返回指针

    // 嵌套的重复成员：
    SCH::Student::PhoneNumber *pNum1 = stu.add_phone();
    pNum1->set_number("1812435454");
    pNum1->set_type(SCH::Student::MOBILE);

    SCH::Student::PhoneNumber *pNum2 = stu.add_phone();
    pNum2->set_number("1234567");
    pNum2->set_type(SCH::Student::HOME);

    // 嵌套的单次成员
    stu.mutable_remark()->set_describe("ok");
    stu.mutable_remark()->set_rank(1);

    // 将stu序列化到string中，string中数据已经是二进制的格式，string只是它的容器
    stu.SerializePartialToString(&resStr);

    // std::cout << "Serialize, debug string: \n" << stu.DebugString() << std::endl; // 按照结构输出
    LOG_INFO("Serialize, debug string:\n{}", stu.DebugString());
    return 0;
}

// 反序列化
int deserialize(std::string &str) {
    SCH::Student stu;
    if (false == stu.ParseFromString(str)) {
        LOG_ERROR("parse failed!");
        return -1;
    } else {
        LOG_INFO("parse, debug string:\n{}", stu.DebugString());
    }

    LOG_WARN("get parsed param info");
    if (stu.has_email()) { // 设置为optional的字段才会有这个接口
        LOG_INFO("email: {}", stu.email());
    }

    LOG_INFO("id: {}", stu.id());

    for (int i = 0; i < stu.phone_size(); i++) {
        SCH::Student::PhoneNumber pnum = stu.phone(i);
        pnum.has_type();

        LOG_INFO("phone: {} - {}", pnum.type(), pnum.number());
    }
    return 0;
}

int main() {
    LOG_INFO("protobuf test start");

    LOG_WARN("serialize start\n");
    std::string SerializeStr;
    serialize(SerializeStr);
    LOG_WARN("serialize done\n");

    LOG_WARN("deserialize start");
    deserialize(SerializeStr);
    LOG_WARN("deserialize done");

    LOG_INFO("protobuf test end");
    return 0;
}