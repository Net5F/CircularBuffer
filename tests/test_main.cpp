#include "CircularBuffer.h"
#include <iostream>
#include <vector>
#include <assert.h>

using namespace AM;

template<typename T, std::size_t maxSize>
bool compareBufferContents(CircularBuffer<T, maxSize>& buffer,
                          std::vector<T>& compareVector) {
    for (unsigned int i = 0; i < maxSize; ++i) {
        if (buffer[i] != compareVector[i]) {
            return false;
        }
    }

    return true;
}

int main() {
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

    std::cout << "All tests passed." << std::endl;

    return 0;
}
