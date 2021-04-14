CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(myprj) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

if(CMAKE_BUILD_PROJECT_OPTION STREQUAL "all")
  option(MYPRJ_BUILD_EXAMPLES "Build All examples" ON)
endif()

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -fpermissive")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

MESSAGE (STATUS "This is binary dir" ${myprj_BINARY_DIR})
MESSAGE (STATUS "This is source dir" ${myprj_SOURCE_DIR})

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

# 设定可执行二进制文件和库目录,为各个examples文件设置输出路径
#EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径。

SET(BUILD_LIB_DIR ${PROJECT_SOURCE_DIR}/../lib/comlib)
SET(LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR})

# 设置各类应用库的头文件
SET(3PART_INCLUDE  ${PROJECT_SOURCE_DIR}/../include/3partlib)

SET(JSONCPP_INCLUDE  ${3PART_INCLUDE}/jsoncpp/include)
SET(LOG4CPP_INCLUDE  ${3PART_INCLUDE}/log4cpp/include)
SET(TINYXML_INCLUDE  ${3PART_INCLUDE}/tinyxml/include)
SET(REDIS_INCLUDE  ${3PART_INCLUDE}/hiredis/include)


SET(COMM_INCLUDE  ${PROJECT_SOURCE_DIR}/../include/comlib)

SET(STIBEL_COMMON_INCLUDE  ${COMM_INCLUDE}/StiBel/Common/include)

SUBDIRS(
		./StiBel
	)


