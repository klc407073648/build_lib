#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_INCLUDE} ./include )

#代码列表
FILE (GLOB STIBEL_MYSQL_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_MYSQL} SHARED ${STIBEL_MYSQL_FILES} )

if(BUILD_TEST)
    add_subdirectory(./test)
endif()
