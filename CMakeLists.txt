cmake_minimum_required(VERSION 3.20)

project(mnist_digit)

file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/img/src/image.cpp
    ${CMAKE_SOURCE_DIR}/reader/src/reader.cpp
)

add_library(reader STATIC ${SOURCES})

target_include_directories(reader PRIVATE 
    ${CMAKE_SOURCE_DIR}/img/include/
    ${CMAKE_SOURCE_DIR}/reader/include/
)

add_executable(test test.cpp)

target_include_directories(test PRIVATE 
    ${CMAKE_SOURCE_DIR}/img/include/
    ${CMAKE_SOURCE_DIR}/reader/include/
)

target_link_libraries(test reader)

set_target_properties(reader PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib
)

set_target_properties(test PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)