#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${STIBEL_SAMPLES_OUTPUT_PATH}/Util)

#头文件目录
INCLUDE_DIRECTORIES(${GOOGLETEST_INCLUDE} ${STIBEL_UTIL_INCLUDE}  ./include )

#目录源码路径
#SET( STIBEL_UTIL_TEST_SRC_DIR ./source )

#代码列表
#FILE (GLOB STIBEL_UTIL_TEST_FILES ${STIBEL_UTIL_TEST_SRC_DIR}/*.cpp)

#依赖的LIB
SET(STIBEL_UTIL_TEST_LIB ${LIB_GOOGLETEST} ${LIB_STIBEL_UTIL} ${LIB_PTHREAD})

#生成 
ADD_EXECUTABLE( UtilSample ./source/UtilSample.cpp)

#连接生成相关库
TARGET_LINK_LIBRARIES( UtilSample ${STIBEL_UTIL_TEST_LIB} )
