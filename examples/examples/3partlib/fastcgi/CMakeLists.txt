#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3PARTLIB_EXECUTABLE_OUTPUT_PATH}/fastcgi)

#头文件目录
INCLUDE_DIRECTORIES( ${FASTCGI_INCLUDE}  ./include )

#目录源码路径
SET( FASTCGITEST_SRC_DIR ./source )

#代码列表
FILE (GLOB FASTCGITEST_FILES ${FASTCGITEST_SRC_DIR}/*.cpp)

#依赖的LIB
SET(FASTCGITEST_LIB  ${LIB_FASTCGI} )

#生成 
ADD_EXECUTABLE( fastcgiTest ${FASTCGITEST_FILES})

#连接生成相关库
TARGET_LINK_LIBRARIES( fastcgiTest ${FASTCGITEST_LIB} )
