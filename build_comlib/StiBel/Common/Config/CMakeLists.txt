#头文件目录
INCLUDE_DIRECTORIES( ${STIBEL_UTIL_INCLUDE} ${JSONCPP_INCLUDE} ${YAMLCPP_INCLUDE} ${TINYXML_INCLUDE} ./include )

#代码列表
FILE (GLOB STIBEL_COMMON_CONFIG_FILES ./src/*.cpp)

#生成动态库 TODO
#add_library(Util ${SRCS})
#add_library(Poco::Util ALIAS Util)
ADD_LIBRARY(${LIB_STIBEL_COMMON_CONFIG} SHARED ${STIBEL_COMMON_CONFIG_FILES})

if(ENABLE_TESTS)
    add_subdirectory(./test)
    add_subdirectory(./samples)
endif()

