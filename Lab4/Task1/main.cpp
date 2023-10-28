#include "dynamicArray.h"
#include <iostream>
#include <cassert>

void static test1() {
    DynamicArray arr = createDynamicArrayWithCapacity(10);
    assert(arr.capacity == 10);
}

void static test2() {
    DynamicArray arr = createDynamicArray();
    assert(arr.length == 0);
    addElementToArray(arr, 5);
    assert(arr.length == 1);
}

void static test3() {
    DynamicArray arr = createDynamicArrayWithCapacity(1);
    addElementToArray(arr, 5);
    assert(arr.capacity == 1);
    addElementToArray(arr, 10);
    assert(arr.capacity == 2);
    addElementToArray(arr, 20);
    assert(arr.capacity == 4);
}

void static test4() {
    DynamicArray arr = createDynamicArray();
    addElementToArray(arr, 5);
    int el = getElementAtIndex(arr, 0);
    assert(el == 5);
}

void static test5() {
    DynamicArray arr{};
    addElementToArray(arr, 5);
    addElementToArray(arr, 6);
    addElementToArray(arr, 7);

    std::span<int> span = getCurrentSpan(arr);

    assert(span.size() == 3);
    assert(span[0] == 5);
    assert(span[1] == 6);
    assert(span[2] == 7);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

    std::cout << "All tests passed!" << std::endl;

    return 0;
}
