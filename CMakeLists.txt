cmake_minimum_required(VERSION 3.20)

project(CacheCore)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    CacheCore

    server/main.cpp
    src/socket/Socket.cpp
)

target_include_directories(
    CacheCore
    PRIVATE
    include
)