cmake_minimum_required(VERSION 3.10)
project(TestingLinalRepo)
add_subdirectory(LinLib)
add_subdirectory(Tests/)
add_executable(Testing_prog source/linalg_test.cpp)
target_include_directories(Testing_prog PUBLIC ${CMAKE_SOURCE_DIR}/LinLib/include)
target_link_libraries(Testing_prog PUBLIC LinLib gtest_main)
target_link_libraries(Testing_prog PUBLIC LinLib)
target_link_libraries(Testing_prog PUBLIC LinLib GTest::gtest_main)


