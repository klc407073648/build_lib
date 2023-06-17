#头文件目录
INCLUDE_DIRECTORIES( ${GOOGLETEST_INCLUDE} ./include )

#代码列表
FILE (GLOB STIBEL_TEST_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_TEST} SHARED ${STIBEL_TEST_FILES})

#if(BUILD_TESTS)
#    add_subdirectory(./test)
#endif()

#if(BUILD_SAMPLES)
#    add_subdirectory(./samples)
#endif()