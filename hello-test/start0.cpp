#include <iostream>
#include <string>
#include <vector>

class BaseType {
public:
    BaseType() {}
     ~BaseType() {}

    void print() {
        std::cout << "base print" << std::endl;
    }
};

class TestType : public BaseType {
public:
    TestType() {}
     ~TestType() {}

    void print() {
        std::cout << "test print" << std::endl;
    }
};

int main() {
    // {
    //     BaseType *pTest = new TestType();
    //     auto      pBase = dynamic_cast<TestType *>(pTest);

    //     pTest->print();
    //     pBase->print();
    //     delete pTest;
    // }

    {
        TestType * pDerive = new TestType();
        auto pTest = dynamic_cast<BaseType*>(pDerive);

        pTest->print();
        delete pTest;
    }

    {
        const int a = 10;
        auto b = const_cast<int*>(&a);
        std::cout << "*b=" << *b << ", a=" << a << std::endl;
        *b += 10;
        std::cout << "*b=" << *b << ", a=" << a << std::endl;
    }


    return 0;
}