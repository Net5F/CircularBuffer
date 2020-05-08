# Add our header-only library target
add_library(CircularBuffer INTERFACE)

target_include_directories(CircularBuffer
    INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(CircularBuffer INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/CircularBuffer.h
)