CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(BUILD_LIB) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

# 编译选项
include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)

# 选项: 构建用例 和 CTest用例
option(BUILD_EXAMPLES "Enable build all examples" ON)

# 编译内容信息
include(${PROJECT_SOURCE_DIR}/cmake/message.cmake)

# 设定可执行二进制文件和库目录
# EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径，BUILD_LIB_DIR生成库的路径
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/)
SET(BUILD_LIB_DIR ${PROJECT_SOURCE_DIR}/deploy/lib)
SET(LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR})
SET(3PART_BIN_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib/3partlib/bin)

#为各个examples文件下目录设置输出路径
SET(3PARTLIB_EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/3partlib)
SET(COMLIB_EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/deploy/comlib)

# 封装StiBel的模块内容
include(${PROJECT_SOURCE_DIR}/cmake/3partlib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/comlib.cmake)

# 链接头文件和库
include(${PROJECT_SOURCE_DIR}/cmake/linklib.cmake)

#添加子路径
if(CMAKE_BUILD_TYPE STREQUAL "Release")
SUBDIRS(
       ./examples
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(BUILD_EXAMPLES)
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