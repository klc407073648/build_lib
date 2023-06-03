#头文件目录
INCLUDE_DIRECTORIES( ${TINYXML_INCLUDE}  ./include )

#代码列表
FILE (GLOB STIBEL_XML_FILES ./src/*.cpp)

#生成动态库
ADD_LIBRARY(${LIB_STIBEL_XML} SHARED ${STIBEL_XML_FILES})

if(ENABLE_TESTS)
    add_subdirectory(./test)
    #add_subdirectory(./samples)
endif()

