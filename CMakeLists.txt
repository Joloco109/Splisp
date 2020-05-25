cmake_minimum_required(VERSION 3.5)

project(splisp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(pegtl)
find_package(Boost 1.72.0)

add_executable(splisp
  src/main.cpp src/parser.cpp
)
target_link_libraries(splisp Qt5::Core)
target_link_libraries(splisp taocpp::pegtl)
