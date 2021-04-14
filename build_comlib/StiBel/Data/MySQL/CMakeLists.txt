#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_INCLUDE}  ./include )

#生成动态库
ADD_LIBRARY(StiBel_mysql SHARED ./src/MySQL.cpp )


