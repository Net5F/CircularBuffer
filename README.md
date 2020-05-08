## Usage
```
#include "CircularBuffer.h"

CircularBuffer<int, 3> buffer(10);
// Buffer is now [10, 10, 10]

buffer.push(1);
buffer.push(2);
// Buffer is now [2, 1, 10]

int exampleVar = buffer[2];
// exampleVar == 10

buffer.push(42);
buffer.push(404);
// Buffer is now [404, 42, 2]
```

## Tests
```
mkdir tests/build
cd tests/build
cmake -G "MSYS Makefiles" .. // (Or whatever generator you want)
make
./CircularBufferTests.exe
```

## CMake
CMakelists.txt defines the interface target CircularBuffer.
