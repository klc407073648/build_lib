CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(BUILD_LIB) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

# 选项
include(${PROJECT_SOURCE_DIR}/cmake/options.cmake)

#自定义 cmake 模块所在的路径 ———— 考虑所有的内容都通过FindYamlCpp来查找不需要自定义查找
#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# 设置C++编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

# PROJECT_BINARY_DIR：运行cmake命令的目录, PROJECT_SOURCE_DIR：工程根目录
MESSAGE (STATUS "BUILD_LIB_BINARY_DIR:        " ${BUILD_LIB_BINARY_DIR})
MESSAGE (STATUS "BUILD_LIB_SOURCE_DIR:        " ${BUILD_LIB_SOURCE_DIR})
MESSAGE (STATUS "BUILD_TYPE:                  " ${BUILD_TYPE})
MESSAGE (STATUS "LIB_VERSION:                 " ${LIB_VERSION})

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

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

# 设置各类应用库的文件路径
SET(3PART_DIR  ${PROJECT_SOURCE_DIR}/lib/3partlib)
SET(COMM_DIR   ${PROJECT_SOURCE_DIR}/lib/comlib)

#cmake 在find_path和find_library时,会搜索一些默认的路径
#g++在编译过程中，能够搜索到mysql和hiredis的头文件和库文件路径，因为
#这些头文件和库文件都放置/usr/include、/usr/local/include，/usr/local/lib/、/usr/lib64/ 下
#属于g++搜索路径下的内容，即不在需要指定MYSQL_INCLUDE、MYSQL_DIR来添加工程的路径

#设置自定义搜索路径
set(CMAKE_INCLUDE_PATH ${JSONCPP_INCLUDE} ${LOG4CPP_INCLUDE} ${TINYXML_INCLUDE} ${ZEROMQ_INCLUDE} ${HIREDIS_INCLUDE} ${FASTCGI_INCLUDE} ${POCO_INCLUDE} ${CPPUNIT_INCLUDE} ${YAMLCPP_INCLUDE} ${GRPC_INCLUDE} ${PROTOBUF_INCLUDE} ${GOOGLETEST_INCLUDE})
set(CMAKE_LIBRARY_PATH ${3PART_DIR} ${COMM_DIR})

# 寻找对应库是否存在
include(${PROJECT_SOURCE_DIR}/cmake/Find3partlib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindComlib.cmake)

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