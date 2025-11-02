#pragma once

#include <string>
#include <mutex>

class ThreadSafe {
private:
    int field0;
    int field1;

    mutable std::mutex mtx0;
    mutable std::mutex mtx1;
public:
    ThreadSafe();

    void setField0(int value);
    int getField0();
    void setField1(int value);
    int getField1();
    operator std::string();
};