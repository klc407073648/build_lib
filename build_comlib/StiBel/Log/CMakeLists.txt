#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_INCLUDE}  ${LOG4CPP_INCLUDE} ./include)

#生成动态库
ADD_LIBRARY(StiBel_log SHARED ./src/LoggerManager.cpp )
