cmake_minimum_required(VERSION 3.9)
project(exp)

set(CMAKE_CXX_STANDARD 98)

add_executable(exp tol.cpp lib/butterfly.h lib/scc.h lib/header.h
        lib/DataConversion.h lib/level_deciding.h lib/DAGgenerator.h
        lib/GraphDiff.h lib/IOtest.h lib/preprocess.h)