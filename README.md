This repository contains my first CPP HW during my second year. 
Lets discribe CMake file in root path:

```cmake_minimum_required(VERSION 3.10)
project(TestingLinalRepo)//name of my project

add_subdirectory(LinLib)//adding subdir in our build 
add_subdirectory(Tests/)//same as previous 

add_executable(Testing_prog source/linalg_test.cpp)//make exe file to run the programm(name-first pos, location - second pos)

target_include_directories(Testing_prog PUBLIC ${CMAKE_SOURCE_DIR}/LinLib/include)
target_link_libraries(Testing_prog PUBLIC LinLib gtest_main)
target_link_libraries(Testing_prog PUBLIC LinLib)
target_link_libraries(Testing_prog PUBLIC LinLib GTest::gtest_main)```


