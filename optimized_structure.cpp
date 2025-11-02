#include "optimized_structure.h"

ThreadSafe::ThreadSafe() : field0(0), field1(0) {}

void ThreadSafe::setField0(int value) {
    std::lock_guard<std::mutex> lock(mtx0);
    field0 = value;
}

int ThreadSafe::getField0() {
    std::lock_guard<std::mutex> lock(mtx0);
    return field0;
}

void ThreadSafe::setField1(int value) {
    std::lock_guard<std::mutex> lock(mtx1);
    field1 = value;
}

int ThreadSafe::getField1() {
    std::lock_guard<std::mutex> lock(mtx1);
    return field1;
}

ThreadSafe::operator std::string() {
    std::scoped_lock lock(mtx0, mtx1);
    return "Field0: " + std::to_string(field0) + 
            ", Field1: " + std::to_string(field1);
}