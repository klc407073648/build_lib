CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(BUILD_LIB) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
else()
  set(BUILD_TYPE "Release")
endif()

if(NOT CMAKE_BUILD_VERSION)
  set(LIB_VERSION "V1.1.0")
else()
  set(LIB_VERSION ${CMAKE_BUILD_VERSION})
endif()

if(CMAKE_BUILD_PROJECT_OPTION STREQUAL "all")
  option(MYPRJ_BUILD_EXAMPLES "Build All examples" ON)
endif()

#构建测试用例
option(BUILD_TESTS "Build all tests." ON) 

#自定义 cmake 模块所在的路径 ———— 考虑所有的内容都通过FindYamlCpp来查找不需要自定义查找
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#设置C++编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

#PROJECT_BINARY_DIR：运行cmake命令的目录。
#PROJECT_SOURCE_DIR：工程根目录
MESSAGE (STATUS "BUILD_LIB_BINARY_DIR:        " ${BUILD_LIB_BINARY_DIR})
MESSAGE (STATUS "BUILD_LIB_SOURCE_DIR:        " ${BUILD_LIB_SOURCE_DIR})
MESSAGE (STATUS "BUILD_TYPE:                  " ${BUILD_TYPE})
MESSAGE (STATUS "LIB_VERSION:                 " ${LIB_VERSION})

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

# 设定可执行二进制文件和库目录
#EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径，BUILD_LIB_DIR生成库的路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/)
SET(BUILD_LIB_DIR ${PROJECT_SOURCE_DIR}/deploy/lib)
SET(LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR})
SET(3PART_BIN_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/3partlib/bin)

#为各个examples文件下目录设置输出路径
SET(3PARTLIB_EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/3partlib)
SET(COMLIB_EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/comlib)

# 封装StiBel的模块内容
include(${PROJECT_SOURCE_DIR}/cmake/StiBel.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindStiBel.cmake)

#添加外部库的搜索路径
LINK_DIRECTORIES(${3PART_DIR} ${COMM_DIR})

#添加子路径
if(CMAKE_BUILD_TYPE STREQUAL "Release")
SUBDIRS(
       ./examples
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MYPRJ_BUILD_EXAMPLES)
       message(STATUS "build all examples")
       SUBDIRS(
          ./examples
       )
    else()
       message(STATUS "build only ./examples/ToolClass")
       SUBDIRS(
        ./examples
       )
    endif()    
endif()