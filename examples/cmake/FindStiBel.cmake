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

# 第三方应用库校验

## 搜索第三方应用库对应的头文件和库是否存在,来判断是否安装了对应库
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

find_path(GOOGLETEST_INCLUDE_DIR gtest/gtest.h)
find_library(GOOGLETEST_LIBRARY NAMES gtest)

find_path(DROGON_INCLUDE_DIR drogon/drogon.h)
find_library(DROGON_LIBRARY NAMES Drogon::Drogon)

## 打印第三方应用库的存在消息
SET(3PART_LIBS JSONCPP LOG4CPP TINYXML ZEROMQ HIREDIS FASTCGI POCO CPPUNIT YAMLCPP PROTOBUF MYSQL GOOGLETEST)

FOREACH(3PART_LIB ${3PART_LIBS})	 
  if(${3PART_LIB}_INCLUDE_DIR AND ${3PART_LIB}_LIBRARY)
    message(STATUS "found ${3PART_LIB}")
  else()
    message(STATUS "not found ${3PART_LIB}")
  endif()	 
ENDFOREACH()

# 自封装应用库校验

## 自封装应用库是否存在
find_library(STIBEL_COMMON_LIBRARY  NAMES StiBel_common_${LIB_VERSION})
find_library(STIBEL_MYSQL_LIBRARY   NAMES StiBel_mysql_${LIB_VERSION})
find_library(STIBEL_LOG_LIBRARY     NAMES StiBel_log_${LIB_VERSION})
find_library(STIBEL_JSON_LIBRARY    NAMES StiBel_json_${LIB_VERSION})
find_library(STIBEL_REDIS_LIBRARY   NAMES StiBel_redis_${LIB_VERSION})

## 打印自封装库的存在消息
SET(STIBEL_LIBS COMMON MYSQL LOG JSON REDIS)

FOREACH(STIBEL_LIB ${STIBEL_LIBS})	 
  #string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
  if(STIBEL_${STIBEL_LIB}_LIBRARY)
    message(STATUS "found STIBEL_${STIBEL_LIB}_LIBRARY")
  else()
    message(STATUS "not found STIBEL_${STIBEL_LIB}_LIBRARY")
  endif()
ENDFOREACH()