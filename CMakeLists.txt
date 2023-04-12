cmake_minimum_required(VERSION 3.25)
project(22Spring_DS_Exp2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(22Spring_DS_Exp2
        includes/AdjListDirNetwork.h
        includes/AdjListDirNetworkArc.h
        includes/AdjListDirNetworkVex.h
        includes/Assistance.h
        includes/Kruskal.h
        includes/MineHeap.h
        includes/Prim.h
        includes/UFSets.h
        TestAdjListDirNetwork.cpp)
