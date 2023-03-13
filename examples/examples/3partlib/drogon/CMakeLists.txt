#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3PARTLIB_EXECUTABLE_OUTPUT_PATH}/drogon)

#头文件目录
INCLUDE_DIRECTORIES( ${DROGON_INCLUDE} ${TRANTOR_INCLUDE} ./include )

#目录源码路径
SET( DROGONTEST_SRC_DIR ./source )

execute_process(COMMAND sh /home/test/examples/examples/examples/3partlib/drogon/test.sh )
find_package(Drogon CONFIG REQUIRED)
set(CMAKE_PREFIX_PATH               "/home/test/examples/lib/3partlib/lib64/cmake")
#execute_process(COMMAND sh -c "sed -i \"/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES ${DROGON_PATH}/include/\" ${3PART_BIN_OUTPUT_PATH}/../lib64/cmake/Drogon/DrogonTargets.cmake")
#exec_program("sed -i \"/INTERFACE_INCLUDE_DIRECTORIES*/c\INTERFACE_INCLUDE_DIRECTORIES \"${TRANTOR_INCLUDE}/\"" ${3PART_BIN_OUTPUT_PATH}/../lib64/cmake/Drogon/TrantorTargets.cmake")


	  
#代码列表
FILE (GLOB DROGONTEST_FILES ${DROGONTEST_SRC_DIR}/*.cc)

#依赖的LIB
SET(DROGONTEST_LIB  ${LIB_DROGON} )

#生成 
ADD_EXECUTABLE( hellowordTest ${DROGONTEST_FILES})

#连接生成相关库
TARGET_LINK_LIBRARIES( hellowordTest ${DROGONTEST_LIB} )
