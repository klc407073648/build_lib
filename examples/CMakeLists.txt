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

# 设置第三方应用库的头文件
SET(3PART_INCLUDE           ${PROJECT_SOURCE_DIR}/include/3partlib)

SET(JSONCPP_INCLUDE         ${3PART_INCLUDE}/jsoncpp/include)
SET(LOG4CPP_INCLUDE         ${3PART_INCLUDE}/log4cpp/include)
SET(TINYXML_INCLUDE         ${3PART_INCLUDE}/tinyxml/include)
SET(ZEROMQ_INCLUDE          ${3PART_INCLUDE}/zeromq/include) 
SET(HIREDIS_INCLUDE         ${3PART_INCLUDE}/hiredis/include)
SET(FASTCGI_INCLUDE         ${3PART_INCLUDE}/fastcgi/include)
SET(POCO_INCLUDE            ${3PART_INCLUDE}/poco/include)
SET(CPPUNIT_INCLUDE         ${3PART_INCLUDE}/cppunit/include)
SET(YAMLCPP_INCLUDE         ${3PART_INCLUDE}/yamlcpp/include)
SET(PROTOBUF_INCLUDE        ${3PART_INCLUDE}/protobuf/include)
#SET(GRPC_INCLUDE            ${3PART_INCLUDE}/grpc/include)
#SET(MYQSL_INCLUDE           ${3PART_INCLUDE}/mysql/include)

# 设置自封装应用库的头文件
SET(COMM_INCLUDE            ${PROJECT_SOURCE_DIR}/include/comlib)

SET(STIBEL_COMMON_INCLUDE   ${COMM_INCLUDE}/StiBel/Common/include)
SET(STIBEL_MYSQL_INCLUDE    ${COMM_INCLUDE}/StiBel/Data/MySQL/include ${MYQSL_INCLUDE})
SET(STIBEL_REDIS_INCLUDE    ${COMM_INCLUDE}/StiBel/Data/Redis/include)
SET(STIBEL_LOG_INCLUDE      ${COMM_INCLUDE}/StiBel/Log/include)
SET(STIBEL_JSON_INCLUDE     ${COMM_INCLUDE}/StiBel/JSON/include)

# 设置各类应用库的文件路径
SET(3PART_DIR  ${PROJECT_SOURCE_DIR}/lib/3partlib)
SET(COMM_DIR   ${PROJECT_SOURCE_DIR}/lib/comlib)

#cmake 在find_path和find_library时,会搜索一些默认的路径
#g++在编译过程中，能够搜索到mysql和hiredis的头文件和库文件路径，因为
#这些头文件和库文件都放置/usr/include、/usr/local/include，/usr/local/lib/、/usr/lib64/ 下
#属于g++搜索路径下的内容，即不在需要指定MYSQL_INCLUDE、MYSQL_DIR来添加工程的路径

#设置自定义搜索路径
set(CMAKE_INCLUDE_PATH ${JSONCPP_INCLUDE} ${LOG4CPP_INCLUDE} ${TINYXML_INCLUDE} ${ZEROMQ_INCLUDE} ${HIREDIS_INCLUDE} ${FASTCGI_INCLUDE} ${POCO_INCLUDE} ${CPPUNIT_INCLUDE} ${YAMLCPP_INCLUDE} ${GRPC_INCLUDE} ${PROTOBUF_INCLUDE})
set(CMAKE_LIBRARY_PATH ${3PART_DIR} ${COMM_DIR})

#搜索第三方应用库对应的头文件和库是否存在,来判断是否安装了对应库
find_path(JSONCPP_INCLUDE_DIR json/json.h)
find_library(JSONCPP_LIBRARY NAMES jsoncpp)

find_path(LOG4CPP_INCLUDE_DIR log4cpp/Category.hh)
find_library(LOG4CPP_LIBRARY NAMES log4cpp)

find_path(TINYXML_INCLUDE_DIR tinyxml.h)
find_library(TINYXML_LIBRARY NAMES tinyxml)

find_path(ZEROMQ_INCLUDE_DIR zmq.hpp)
find_library(ZEROMQ_LIBRARY NAMES zmq)

find_path(HIREDIS_INCLUDE_DIR hiredis/hiredis.h)
find_library(HIREDIS_LIBRARY NAMES hiredis)

find_path(FASTCGI_INCLUDE_DIR fcgi_stdio.h)
find_library(FASTCGI_LIBRARY NAMES fcgi)

find_path(POCO_INCLUDE_DIR Poco/RegularExpression.h)
find_library(POCO_LIBRARY NAMES PocoEncodings)

find_path(CPPUNIT_INCLUDE_DIR cppunit/TestCase.h)
find_library(CPPUNIT_LIBRARY NAMES cppunit)

find_path(YAMLCPP_INCLUDE_DIR yaml-cpp/yaml.h)
find_library(YAMLCPP_LIBRARY NAMES yaml-cpp)

find_path(MYSQL_INCLUDE_DIR mysql/mysql.h)
find_library(MYSQL_LIBRARY NAMES mysqlclient)

find_path(PROTOBUF_INCLUDE_DIR google/protobuf/text_format.h)
find_library(PROTOBUF_LIBRARY NAMES protobuf)

#打印第三方应用库的存在消息
SET(3PART_LIBS JSONCPP LOG4CPP TINYXML ZEROMQ HIREDIS FASTCGI POCO CPPUNIT YAMLCPP PROTOBUF MYSQL)

FOREACH(3PART_LIB ${3PART_LIBS})	 
  if(${3PART_LIB}_INCLUDE_DIR AND ${3PART_LIB}_LIBRARY)
    message(STATUS "found ${3PART_LIB}")
  else()
    message(STATUS "not found ${3PART_LIB}")
  endif()	 
ENDFOREACH()

# 设置第三方库的链接名称
SET(LIB_JSONCPP jsoncpp)
SET(LIB_LOG4CPP log4cpp)
SET(LIB_TINYXML tinyxml)
SET(LIB_ZEROMQ  zmq)
SET(LIB_HIREDIS hiredis)
SET(LIB_PTHREAD pthread)
SET(LIB_FASTCGI fcgi)
SET(LIB_POCO       
    PocoCrypto
    PocoJSON
    PocoRedis
    PocoEncodings
    PocoJWT
    PocoUtil
    PocoFoundation
    PocoNet
    PocoXML
)
SET(LIB_CPPUNIT cppunit dl)
SET(LIB_MYSQL mysqlclient)
SET(LIB_YAMLCPP  yaml-cpp)

SET(LIB_PROTOBUF protobuf)
SET(LIB_REFLECTION grpc++_reflection)
SET(LIB_GRPC_GRPCPP grpc++)
SET(LIB_PROTOC protoc)

#自封装应用库是否存在
find_library(STIBEL_COMMON_LIBRARY  NAMES StiBel_common_${LIB_VERSION})
find_library(STIBEL_MYSQL_LIBRARY   NAMES StiBel_mysql_${LIB_VERSION})
find_library(STIBEL_LOG_LIBRARY     NAMES StiBel_log_${LIB_VERSION})
find_library(STIBEL_JSON_LIBRARY    NAMES StiBel_json_${LIB_VERSION})
find_library(STIBEL_REDIS_LIBRARY   NAMES StiBel_redis_${LIB_VERSION})

#校验自封装库是否存在
SET(STIBEL_LIBS COMMON MYSQL LOG JSON REDIS)

FOREACH(STIBEL_LIB ${STIBEL_LIBS})	 
  #string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
  if(STIBEL_${STIBEL_LIB}_LIBRARY)
    message(STATUS "found STIBEL_${STIBEL_LIB}_LIBRARY")
  else()
    message(STATUS "not found STIBEL_${STIBEL_LIB}_LIBRARY")
  endif()	 
ENDFOREACH()

# 设置自封装应用库的链接名称
SET(LIB_STIBEL_COMMON   StiBel_common_${LIB_VERSION} ${LIB_PTHREAD})
SET(LIB_STIBEL_MYSQL    StiBel_mysql_${LIB_VERSION}  ${LIB_MYSQL} )
SET(LIB_STIBEL_REDIS    StiBel_redis_${LIB_VERSION}  ${LIB_HIREDIS})
SET(LIB_STIBEL_LOG      StiBel_log_${LIB_VERSION}    ${LIB_LOG4CPP} ${LIB_PTHREAD} ${LIB_STIBEL_COMMON})
SET(LIB_STIBEL_JSON     StiBel_json_${LIB_VERSION}   ${LIB_JSONCPP})

#添加外部库的搜索路径
LINK_DIRECTORIES(${3PART_DIR} ${COMM_DIR})

#添加子路径
if(CMAKE_BUILD_TYPE STREQUAL "Release")
SUBDIRS(
       ./examples
    )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
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