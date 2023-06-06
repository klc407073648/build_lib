# 自封装应用库校验
MESSAGE (STATUS "FindComlib begin")

## 自封装应用库是否存在
find_library(STIBEL_COMMON_CONFIG_LIBRARY       NAMES StiBelCommonConfig${LIB_VERSION})
find_library(STIBEL_COMMON_FOUNDATION_LIBRARY   NAMES StiBelCommonFoundation${LIB_VERSION})
find_library(STIBEL_DATA_MYSQL_LIBRARY          NAMES StiBelDataMySQL${LIB_VERSION})
find_library(STIBEL_DATA_REDIS_LIBRARY          NAMES StiBelDataRedis${LIB_VERSION})
find_library(STIBEL_JSON_LIBRARY                NAMES StiBelJSON${LIB_VERSION})
find_library(STIBEL_LOG_LIBRARY                 NAMES StiBelLog${LIB_VERSION})
find_library(STIBEL_UTIL_LIBRARY                NAMES StiBelUtil${LIB_VERSION})
find_library(STIBEL_XML_LIBRARY                 NAMES StiBelXML${LIB_VERSION})
find_library(STIBEL_YAML_LIBRARY                NAMES StiBelYAML${LIB_VERSION})

## 打印自封装库的存在消息
SET(STIBEL_LIBS COMMON_CONFIG COMMON_FOUNDATION DATA_MYSQL DATA_REDIS JSON LOG UTIL XML YAML)

FOREACH(STIBEL_LIB ${STIBEL_LIBS})	 
  #string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
  if(STIBEL_${STIBEL_LIB}_LIBRARY)
    message(STATUS "found STIBEL_${STIBEL_LIB}_LIBRARY")
  else()
    message(STATUS "not found STIBEL_${STIBEL_LIB}_LIBRARY")
  endif()
ENDFOREACH()

MESSAGE (STATUS "FindComlib end")