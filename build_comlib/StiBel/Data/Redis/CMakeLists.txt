#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_FOUNDATION_INCLUDE} ${STIBEL_UTIL_INCLUDE} ${HIREDIS_INCLUDE} ./include )

#代码列表
FILE (GLOB STIBEL_REDIS_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_DATA_REDIS} SHARED ${STIBEL_REDIS_FILES})

if(BUILD_TESTS)
    add_subdirectory(./test)
endif()

if(BUILD_SAMPLES)
    #add_subdirectory(./samples)
endif()
