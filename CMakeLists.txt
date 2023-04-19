cmake_minimum_required(VERSION 3.16)
project(adj_list_dir_network)

set(CMAKE_CXX_STANDARD 11)

add_executable(adj_list_dir_network includes/Assistance.h includes/AdjListDirNetwork.h includes/AdjListDirNetworkArc.h includes/AdjListDirNetworkVex.h TestAdjListDirNetwork.cpp includes/UFSets.h includes/MineHeap.h)
