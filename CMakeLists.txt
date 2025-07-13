cmake_minimum_required(VERSION 3.10)

project(MinecraftServerCPPLauncher)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(MinecraftServerCPPLauncher main.cpp)