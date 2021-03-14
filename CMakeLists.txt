cmake_minimum_required(VERSION 3.17)
project(l_11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined ")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
add_executable(l_11 my_string.cpp my_string.h my_string_tests.cpp my_string_view.cpp my_string_view.h my_string_view_tests.cpp)

add_subdirectory(lib)
include_directories(lib/googletest/include)

target_link_libraries(l_11 gtest gtest_main)