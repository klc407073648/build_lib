CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(BUILD_LIB) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

# 编译选项
include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)

# 编译内容信息
include(${PROJECT_SOURCE_DIR}/cmake/message.cmake)

# 设置C/C++编译选项 TODO
#SET(CMAKE_C_FLAGS "-W -Wformat")
#SET(CMAKE_CXX_FLAGS "-W -Wformat")

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
## 设置第三方应用库路径
SET(3PART_PATH              ${PROJECT_SOURCE_DIR}/include/3partlib)
include(${PROJECT_SOURCE_DIR}/cmake/3partlib.cmake)

## 设置公共库路径
SET(COMM_PATH               ${PROJECT_SOURCE_DIR}/include/comlib)
include(${PROJECT_SOURCE_DIR}/cmake/comlib.cmake)

# 链接头文件和库
include(${PROJECT_SOURCE_DIR}/cmake/linklib.cmake)

#添加子路径
if(CMAKE_BUILD_TYPE STREQUAL "Release")
ADD_SUBDIRECTORY(
       ./examples
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(BUILD_EXAMPLES)
       message(STATUS "build all examples")
       ADD_SUBDIRECTORY(
          ./examples
       )
    else()
       message(STATUS "build only ./examples/ToolClass")
       ADD_SUBDIRECTORY(
        ./examples
       )
    endif()    
endif()