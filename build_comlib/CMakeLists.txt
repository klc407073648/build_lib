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

# 选项: 构建build_comlib下StiBel子目录的test
option(BUILD_TESTS "Build all tests" ON)

# 选项: 构建build_comlib下StiBel子目录的samples
option(BUILD_SAMPLES "Build all samples" ON)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

MESSAGE (STATUS "BUILD_LIB_BINARY_DIR:" ${BUILD_LIB_BINARY_DIR})
MESSAGE (STATUS "BUILD_LIB_SOURCE_DIR:" ${BUILD_LIB_SOURCE_DIR})
MESSAGE (STATUS "CMAKE_BUILD_TYPE:" ${CMAKE_BUILD_TYPE})
MESSAGE (STATUS "CMAKE_BUILD_VERSION:" ${CMAKE_BUILD_VERSION})

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

# 设定可执行二进制文件和库目录,为各个examples文件设置输出路径
#EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径。
SET(BUILD_LIB_DIR ${PROJECT_SOURCE_DIR}/../output/lib/comlib)
SET(LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR})
SET(STIBEL_TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../output/StiBel/test)
SET(STIBEL_SAMPLES_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../output/StiBel/samples)

# 设置第三方应用库的头文件
SET(3PART_INCLUDE  ${PROJECT_SOURCE_DIR}/../output/include/3partlib)
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
#SET(GRPC_INCLUDE           ${3PART_INCLUDE}/grpc/include)
#SET(MYQSL_INCLUDE          ${3PART_INCLUDE}/mysql/include)
SET(GOOGLETEST_INCLUDE      ${3PART_INCLUDE}/googletest/include)
SET(DROGON_INCLUDE          ${3PART_INCLUDE}/drogon/include)
SET(TRANTOR_INCLUDE         ${3PART_INCLUDE}/trantor/include)
SET(OPENSSL_INCLUDE         ${3PART_INCLUDE}/openssl/include)
SET(ZLIB_INCLUDE            ${3PART_INCLUDE}/zlib/include)
SET(UUID_INCLUDE            ${3PART_INCLUDE}/uuid/include)

set(3PART_INCLUDE_PATH ${JSONCPP_INCLUDE} ${LOG4CPP_INCLUDE} ${TINYXML_INCLUDE} 
${ZEROMQ_INCLUDE} ${HIREDIS_INCLUDE} ${FASTCGI_INCLUDE} ${POCO_INCLUDE} ${CPPUNIT_INCLUDE} ${YAMLCPP_INCLUDE} 
${PROTOBUF_INCLUDE} ${GOOGLETEST_INCLUDE} ${DROGON_INCLUDE} ${TRANTOR_INCLUDE} ${OPENSSL_INCLUDE} 
${ZLIB_INCLUDE} ${UUID_INCLUDE})

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
SET(LIB_GOOGLETEST  gtest)
SET(LIB_PROTOBUF protobuf)
SET(LIB_REFLECTION grpc++_reflection)
SET(LIB_GRPC_GRPCPP grpc++)
SET(LIB_PROTOC protoc)
SET(LIB_DROGON Drogon::Drogon)
SET(LIB_TRANTOR trantor)
SET(LIB_OPENSSL ssl crypto)
SET(LIB_ZLIB z)
SET(LIB_UUID uuid)

# 设置公共库头文件,其他文件仅需要依赖Common内容
SET(STIBEL_COMMON_CONFIG_INCLUDE      ${PROJECT_SOURCE_DIR}/StiBel/Common/Config/include)
SET(STIBEL_COMMON_FOUNDATION_INCLUDE  ${PROJECT_SOURCE_DIR}/StiBel/Common/Foundation/include)
SET(STIBEL_UTIL_INCLUDE               ${PROJECT_SOURCE_DIR}/StiBel/Util/include)

#设置StiBel封装库名
## 设置自封装应用库的链接名称，便于快速使用
SET(LIB_STIBEL_COMMON_CONFIG       StiBelCommonConfig${LIB_VERSION})
SET(LIB_STIBEL_COMMON_FOUNDATION   StiBelCommonFoundation${LIB_VERSION})
SET(LIB_STIBEL_DATA_MYSQL          StiBelDataMySQL${LIB_VERSION})
SET(LIB_STIBEL_DATA_REDIS          StiBelDataRedis${LIB_VERSION})
SET(LIB_STIBEL_UTIL                StiBelUtil${LIB_VERSION})
SET(LIB_STIBEL_LOG                 StiBelLog${LIB_VERSION})
SET(LIB_STIBEL_JSON                StiBelJSON${LIB_VERSION})
SET(LIB_STIBEL_XML                 StiBelXML${LIB_VERSION})
SET(LIB_STIBEL_YAML                StiBelYAML${LIB_VERSION})

# 设置各类应用库的文件路径
SET(3PART_DIR  ${PROJECT_SOURCE_DIR}/../output/lib/3partlib)

#设置自定义搜索路径
set(CMAKE_INCLUDE_PATH ${3PART_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH ${3PART_DIR})

#添加外部库的搜索路径
LINK_DIRECTORIES(${3PART_DIR} ${COMM_DIR})

SUBDIRS(
		./StiBel
	)


