#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3PARTLIB_EXECUTABLE_OUTPUT_PATH}/jsoncpp)

#头文件目录
INCLUDE_DIRECTORIES( ${JSONCPP_INCLUDE}  ${STIBEL_COMMON_FOUNDATION_INCLUDE} ${STIBEL_UTIL_INCLUDE} ./include )

#目录源码路径
SET( JSONCPPTEST_SRC_DIR ./source )

#代码列表
FILE (GLOB JSONCPPTEST_FILES ${JSONCPPTEST_SRC_DIR}/*.cpp)

#依赖的LIB
SET(JSONCPPTEST_LIB  ${LIB_JSONCPP} ${LIB_STIBEL_COMMON_FOUNDATION} ${LIB_PTHREAD} ${LIB_STIBEL_UTIL})

#生成 
ADD_EXECUTABLE( jsoncppTest ${JSONCPPTEST_FILES})

#连接生成相关库
TARGET_LINK_LIBRARIES( jsoncppTest ${JSONCPPTEST_LIB} )
