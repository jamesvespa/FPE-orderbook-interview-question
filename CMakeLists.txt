cmake_minimum_required(VERSION 3.31)
project(orderbook)

set(CMAKE_CXX_STANDARD 20)

include_directories("${orderbook_SOURCE_DIR}/include")

add_subdirectory(src)