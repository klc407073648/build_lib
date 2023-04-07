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