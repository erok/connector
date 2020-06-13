cmake_minimum_required(VERSION 3.16)
project(Connector)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(SEND_ERROR "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()

add_library(Connector INTERFACE)
target_include_directories(Connector INTERFACE include/)

set(EXAMPLE_FILES example/main.cpp)

add_executable(Example ${EXAMPLE_FILES})
target_link_libraries(Example Connector)