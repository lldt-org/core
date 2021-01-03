cmake_minimum_required(VERSION 3.16)
project("LLDT-Core")

set(CMAKE_CXX_STANDARD 17)

add_executable(untitled main.cpp source/Build.cpp source/Build.h include/FrontEnd.h include/ServiceLoader.h)