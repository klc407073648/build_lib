#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_INCLUDE} ${STIBEL_COMMON_INCLUDE} ${REDIS_INCLUDE} ./include )

#生成动态库
ADD_LIBRARY(StiBel_redis SHARED ./src/CMyRedis.cpp ./src/Redis.cpp)


