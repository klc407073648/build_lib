# 自封装应用库
MESSAGE (STATUS "comlib set begin")

## 设置自封装应用库的头文件,StiBel三方库是依赖底层的一些库实现的,因此INCLUDE和LIB应该直接包含对应头文件和库文件，避免使用时再包含
#SET(COMM_PATH                               ${PROJECT_SOURCE_DIR}/include/comlib)

SET(STIBEL_COMMON_CONFIG_INCLUDE            ${COMM_PATH}/StiBel/Common/Config/include)
SET(STIBEL_COMMON_FOUNDATION_INCLUDE        ${COMM_PATH}/StiBel/Common/Foundation/include)
SET(STIBEL_DATA_MYSQL_INCLUDE               ${COMM_PATH}/StiBel/Data/MySQL/include)
SET(STIBEL_DATA_REDIS_INCLUDE               ${COMM_PATH}/StiBel/Data/Redis/include)
SET(STIBEL_JSON_INCLUDE                     ${COMM_PATH}/StiBel/JSON/include)
SET(STIBEL_LOG_INCLUDE                      ${COMM_PATH}/StiBel/Log/include)
SET(STIBEL_UTIL_INCLUDE                     ${COMM_PATH}/StiBel/Util/include)
SET(STIBEL_XML_INCLUDE                      ${COMM_PATH}/StiBel/XML/include)
SET(STIBEL_YAML_INCLUDE                     ${COMM_PATH}/StiBel/YAML/include)
SET(STIBEL_TEST_INCLUDE                     ${COMM_PATH}/StiBel/Test/include)

## 自封装应用库的头文件集合
set(COMM_INCLUDE_PATH ${STIBEL_COMMON_CONFIG_INCLUDE} ${STIBEL_COMMON_FOUNDATION_INCLUDE} ${STIBEL_DATA_MYSQL_INCLUDE} ${STIBEL_DATA_REDIS_INCLUDE} 
${STIBEL_JSON_INCLUDE} ${STIBEL_LOG_INCLUDE} ${STIBEL_UTIL_INCLUDE} ${STIBEL_XML_INCLUDE} ${STIBEL_YAML_INCLUDE} ${STIBEL_TEST_INCLUDE})

MESSAGE (STATUS "COMM_INCLUDE_PATH:       " ${COMM_INCLUDE_PATH})

## 设置自封装应用库的链接名称，便于快速使用
SET(LIB_STIBEL_COMMON_CONFIG       StiBelCommonConfig${LIB_VERSION})
SET(LIB_STIBEL_COMMON_FOUNDATION   StiBelCommonFoundation${LIB_VERSION})
SET(LIB_STIBEL_DATA_MYSQL          StiBelDataMySQL${LIB_VERSION})
SET(LIB_STIBEL_DATA_REDIS          StiBelDataRedis${LIB_VERSION})
SET(LIB_STIBEL_JSON                StiBelJSON${LIB_VERSION})
SET(LIB_STIBEL_LOG                 StiBelLog${LIB_VERSION})
SET(LIB_STIBEL_UTIL                StiBelUtil${LIB_VERSION})
SET(LIB_STIBEL_XML                 StiBelXML${LIB_VERSION})
SET(LIB_STIBEL_YAML                StiBelYAML${LIB_VERSION})
SET(LIB_STIBEL_TEST                StiBelTEST${LIB_VERSION})

## 自封装应用库名列表，便于快速使用
set(COMM_LIB_LIST ${LIB_STIBEL_COMMON_CONFIG} ${LIB_STIBEL_COMMON_FOUNDATION} ${LIB_STIBEL_DATA_MYSQL} ${LIB_STIBEL_DATA_REDIS} 
${LIB_STIBEL_JSON} ${LIB_STIBEL_LOG} ${LIB_STIBEL_UTIL} ${LIB_STIBEL_XML} ${LIB_STIBEL_YAML} ${LIB_STIBEL_TEST})

MESSAGE (STATUS "COMM_LIB_LIST:       " ${COMM_LIB_LIST})

MESSAGE (STATUS "comlib set end")