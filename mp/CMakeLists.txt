cmake_minimum_required(VERSION 3.8)
project(netasio)

include_directories(/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/asio-1.18.2/include)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 17)

add_executable(netasio simple_client.cpp)