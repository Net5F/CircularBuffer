#include "CircularBuffer.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace AM;

template<typename T>
bool compareBufferContents(CircularBuffer<T>& buffer,
                          std::vector<T>& compareVector) {
    for (unsigned int i = 0; i < buffer.size(); ++i) {
        if (buffer[i] != compareVector[i]) {
            return false;
        }
    }

    return true;
}

template<typename T, std::size_t maxSize>
bool compareBufferContents(CircularBuffer<T, maxSize>& buffer,
                           std::vector<T>& compareVector)
{
    for (unsigned int i = 0; i < maxSize; ++i) {
        if (buffer[i] != compareVector[i]) {
            return false;
        }
    }

    return true;
}

void testArrayBased()
{
    // Size is correct.
    CircularBuffer<int, 2024> buffer1;
    assert(buffer1.size() == 2024);

    // Initialization works.
    CircularBuffer<int, 5> buffer2(-1);

    std::vector<int> compareVector = {-1, -1, -1, -1, -1};
    assert(compareBufferContents(buffer2, compareVector));

    // 4 Elements in order.
    CircularBuffer<int, 4> buffer3;
    for (unsigned int i = 0; i < 4; ++i) {
        buffer3.push(i);
    }

    compareVector = {3, 2, 1, 0};
    assert(compareBufferContents(buffer3, compareVector));

    // 5 Elements in order (1 wrap).
    CircularBuffer<int, 4> buffer4;
    for (unsigned int i = 0; i < 5; ++i) {
        buffer4.push(i);
    }

    compareVector = std::vector({4, 3, 2, 1});
    assert(compareBufferContents(buffer4, compareVector));

    // 100 Elements in order (96 wraps).
    CircularBuffer<int, 4> buffer5;
    for (unsigned int i = 0; i < 100; ++i) {
        buffer5.push(i);
    }

    compareVector = std::vector({99, 98, 97, 96});
    assert(compareBufferContents(buffer5, compareVector));

    // Random stuff from the example.
    CircularBuffer<int, 3> buffer6(10);
    compareVector = std::vector({10, 10, 10});
    assert(compareBufferContents(buffer6, compareVector));

    buffer6.push(1);
    buffer6.push(2);
    compareVector = std::vector({2, 1, 10});
    assert(compareBufferContents(buffer6, compareVector));

    int exampleVar = buffer6[2];
    assert(exampleVar == 10);

    buffer6.push(42);
    buffer6.push(404);
    compareVector = std::vector({404, 42, 2});
    assert(compareBufferContents(buffer6, compareVector));

    std::cout << "Array tests passed." << std::endl;
}

void testVectorBased() {
    // Size is correct.
    CircularBuffer<int> buffer1(2024);
    assert(buffer1.size() == 2024);

    // Initialization works.
    CircularBuffer<int> buffer2(5, -1);

    std::vector<int> compareVector = {-1, -1, -1, -1, -1};
    assert(compareBufferContents(buffer2, compareVector));

    // 4 Elements in order.
    CircularBuffer<int> buffer3(4);
    for (unsigned int i = 0; i < 4; ++i) {
        buffer3.push(i);
    }

    compareVector = {3, 2, 1, 0};
    assert(compareBufferContents(buffer3, compareVector));

    // 5 Elements in order (1 wrap).
    CircularBuffer<int> buffer4(4);
    for (unsigned int i = 0; i < 5; ++i) {
        buffer4.push(i);
    }

    compareVector = std::vector({4, 3, 2, 1});
    assert(compareBufferContents(buffer4, compareVector));

    // 100 Elements in order (96 wraps).
    CircularBuffer<int> buffer5(4);
    for (unsigned int i = 0; i < 100; ++i) {
        buffer5.push(i);
    }

    compareVector = std::vector({99, 98, 97, 96});
    assert(compareBufferContents(buffer5, compareVector));

    // Random stuff from the example.
    CircularBuffer<int> buffer6(3, 10);
    compareVector = std::vector({10, 10, 10});
    assert(compareBufferContents(buffer6, compareVector));

    buffer6.push(1);
    buffer6.push(2);
    compareVector = std::vector({2, 1, 10});
    assert(compareBufferContents(buffer6, compareVector));

    int exampleVar = buffer6[2];
    assert(exampleVar == 10);

    buffer6.push(42);
    buffer6.push(404);
    compareVector = std::vector({404, 42, 2});
    assert(compareBufferContents(buffer6, compareVector));

    std::cout << "Vector tests passed." << std::endl;
}

int main() {
    testArrayBased();

    testVectorBased();

    std::cout << "All tests passed." << std::endl;

    return 0;
}

