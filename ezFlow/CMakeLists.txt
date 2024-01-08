cmake_minimum_required(VERSION 3.27)
project(ezFlowLocal)

set(CMAKE_CXX_STANDARD 17)

add_executable(ezFlowLocal main.cpp
        steps.h
        UX.h
        utils.h)
