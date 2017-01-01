cmake_minimum_required(VERSION 2.8)
project(bobo_batch_users)
#设置编译选项
add_definitions("-g -fPIC -shared -Wall -pipe -fno-ident -MMD -Werror -D_GNU_SOURCE -D_REENTRANT")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )

#set cmake packages
#find_package(spp REQUIRED)

#set include files
include_directories(${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/proto)
include_directories(${CMAKE_SOURCE_DIR}/utils)
#include_directories(spp/common)

#set src files
aux_source_directory(${CMAKE_SOURCE_DIR} DIR_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/proto DIR_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/utils DIR_SRCS)

#path of target_link_libraries
link_directories(${CMAKE_SOURCE_DIR}/../lib)

#build lib
add_library(bobo_batch_users SHARED ${DIR_SRCS}) 

#添加链接库
target_link_libraries(cleancc attrapi  trmem sproto)
