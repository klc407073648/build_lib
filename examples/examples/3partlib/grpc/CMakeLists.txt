#grpc

#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3PARTLIB_EXECUTABLE_OUTPUT_PATH}/grpc)
add_subdirectory(cpp/helloworld)
add_subdirectory(cpp/keyvaluestore)

