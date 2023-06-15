#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_COMMON_FOUNDATION_INCLUDE} ${JSONCPP_INCLUDE} ./include )

#代码列表
FILE (GLOB STIBEL_JSON_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_JSON} SHARED ${STIBEL_JSON_FILES} )

if(BUILD_TESTS)
    add_subdirectory(./test)
endif()

if(BUILD_SAMPLES)
    add_subdirectory(./samples)
endif()