#头文件目录
INCLUDE_DIRECTORIES( ./include )

#代码列表
FILE (GLOB STIBEL_COMMON_FOUNDATION_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_COMMON_FOUNDATION} SHARED ${STIBEL_COMMON_FOUNDATION_FILES})

if(ENABLE_TESTS)
    add_subdirectory(./test)
    add_subdirectory(./samples)
endif()

