cmake_minimum_required(VERSION 3.24)
project(adj_list_dir_network)

set(CMAKE_CXX_STANDARD 11)

add_executable(adj_list_dir_network Assistance.h AdjListDirNetwork.h AdjListDirNetworkArc.h AdjListDirNetworkVex.h TestAdjListDirNetwork.cpp UFSets.h MineHeap.h)
