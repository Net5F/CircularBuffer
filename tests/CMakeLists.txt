cmake_minimum_required(VERSION 3.13)

project(CircularBuffer)

# Define our executable target.
add_executable(CircularBufferTests test_main.cpp)

target_include_directories(CircularBufferTests
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(CircularBufferTests
    PRIVATE
        CircularBuffer
)

# Compile with C++17
target_compile_features(CircularBufferTests PRIVATE cxx_std_20)
set_target_properties(CircularBufferTests PROPERTIES CXX_EXTENSIONS OFF)

# CircularBuffer target.
add_subdirectory(.. "build")
