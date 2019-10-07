cmake_minimum_required(VERSION 2.8.4)
project(design_patterns)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -std=c++11")

add_executable(proxy proxy.cpp)
add_executable(memento memento.cpp)
add_executable(chain_of_responsibility chain_of_responsibility.cpp)
add_executable(mediator mediator.cpp)