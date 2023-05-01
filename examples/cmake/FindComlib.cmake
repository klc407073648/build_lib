# 自封装应用库校验
MESSAGE (STATUS "FindComlib begin")

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

MESSAGE (STATUS "FindComlib end")