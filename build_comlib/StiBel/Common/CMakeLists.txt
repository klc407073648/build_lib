#头文件目录
INCLUDE_DIRECTORIES( ./include )

#生成动态库
ADD_LIBRARY(StiBel_common SHARED ./src/Util.cpp ./src/ThreadPool.cpp ./src/TEncode.cpp ./src/Exception.cpp)

