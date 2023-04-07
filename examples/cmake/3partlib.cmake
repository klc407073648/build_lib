# 第三方库设置
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

SET(LIB_TRANTOR ssl crypto)
SET(LIB_ZLIB z)
SET(LIB_UUID uuid)
