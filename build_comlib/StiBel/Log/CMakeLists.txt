#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_FOUNDATION_INCLUDE}  ${LOG4CPP_INCLUDE} ./include)

#代码列表
FILE (GLOB STIBEL_LOG_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_LOG} SHARED ${STIBEL_LOG_FILES} )

if(ENABLE_TESTS)
    add_subdirectory(./test)
    add_subdirectory(./samples)
endif()
