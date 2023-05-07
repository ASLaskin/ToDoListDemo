cmake_minimum_required(VERSION 3.24)
project(ToDoListDemo)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp)
add_executable(ToDoListDemo main.cpp weekly.cpp weekly.h)
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(ToDoListDemo sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

