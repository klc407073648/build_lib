# 第三方库设置
MESSAGE (STATUS "3partlib set begin")

## 设置第三方应用库的头文件
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
#SET(GRPC_INCLUDE           ${3PART_INCLUDE}/grpc/include)
#SET(MYQSL_INCLUDE          ${3PART_INCLUDE}/mysql/include)
SET(GOOGLETEST_INCLUDE      ${3PART_INCLUDE}/googletest/include)
SET(DROGON_INCLUDE          ${3PART_INCLUDE}/drogon/include)
SET(TRANTOR_INCLUDE         ${3PART_INCLUDE}/trantor/include)
SET(OPENSSL_INCLUDE         ${3PART_INCLUDE}/openssl/include)
SET(ZLIB_INCLUDE            ${3PART_INCLUDE}/zlib/include)
SET(UUID_INCLUDE            ${3PART_INCLUDE}/uuid/include)

## 第三方应用库的头文件集合
set(3PART_INCLUDE_PATH ${JSONCPP_INCLUDE} ${LOG4CPP_INCLUDE} ${TINYXML_INCLUDE} 
${ZEROMQ_INCLUDE} ${HIREDIS_INCLUDE} ${FASTCGI_INCLUDE} ${POCO_INCLUDE} ${CPPUNIT_INCLUDE} ${YAMLCPP_INCLUDE} 
${PROTOBUF_INCLUDE} ${GOOGLETEST_INCLUDE} ${DROGON_INCLUDE} ${TRANTOR_INCLUDE} ${OPENSSL_INCLUDE} 
${ZLIB_INCLUDE} ${UUID_INCLUDE})

MESSAGE (STATUS "3PART_INCLUDE_PATH:       " ${3PART_INCLUDE_PATH})

## 设置第三方库的链接名称
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

## 第三方应用库名列表，便于快速使用
set(3PART_LIB_LIST ${LIB_JSONCPP} ${LIB_LOG4CPP} ${LIB_TINYXML} ${LIB_ZEROMQ} ${LIB_HIREDIS} ${LIB_PTHREAD} ${LIB_FASTCGI} 
${LIB_POCO} ${LIB_CPPUNIT} ${LIB_MYSQL} ${LIB_YAMLCPP} ${LIB_GOOGLETEST} ${LIB_PROTOBUF} ${LIB_REFLECTION} 
${LIB_GRPC_GRPCPP} ${LIB_PROTOC} ${LIB_DROGON} ${LIB_TRANTOR} ${LIB_OPENSSL} ${LIB_ZLIB} ${LIB_UUID} )

MESSAGE (STATUS "3PART_LIB_LIST:       " ${3PART_LIB_LIST})

MESSAGE (STATUS "3partlib set end")
