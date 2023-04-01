
#首先找到所有需要编译的.proto文件
file(GLOB protobuf_files
	${CMAKE_CURRENT_SOURCE_DIR}/*.proto
)

#定义相关的目录地址
#PROTO_META_BASE_DIR:编译之后生成文件的目录。
#PROTO_FLAGS:指定编译.proto文件时的总的寻找路径，
#.proto中的import命令根据根据这个地址去连接其他的.proto文件：
SET(PROTO_META_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${CMAKE_CURRENT_SOURCE_DIR})

#通过FOREACH去循环之前的.proto文件，依次编译每个文件，然后将生成的.pb.cc和.pb.h移动回原始的目录
FOREACH(FIL ${protobuf_files})
 
  GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)
 
  string(REGEX REPLACE ".+/(.+)\\..*" "\\1" FILE_NAME ${FIL})
  string(REGEX REPLACE "(.+)\\${FILE_NAME}.*" "\\1" FILE_PATH ${FIL})
 
  #string(REGEX MATCH "(/mediapipe/framework.*|/mediapipe/util.*|/mediapipe/calculators/internal/)" OUT_PATH ${FILE_PATH})
 
  set(PROTO_HDRS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}/${FIL_WE}.pb.h")
  set(PROTO_SRCS "${CMAKE_CURRENT_BINARY_DIR}${OUT_PATH}/${FIL_WE}.pb.cc")
  
  message("PROTO_HDRS " ${PROTO_HDRS} )
  message("PROTO_SRCS " ${PROTO_SRCS} )

  EXECUTE_PROCESS(
  COMMAND ${3PART_BIN_OUTPUT_PATH}/protoc ${PROTO_FLAGS} --cpp_out=${PROTO_META_BASE_DIR} ${FIL}
  )
  message("Copying " ${PROTO_SRCS} " to " ${FILE_PATH})
 
  file(COPY ${PROTO_HDRS} DESTINATION ${FILE_PATH}/include)
  file(COPY ${PROTO_SRCS} DESTINATION ${FILE_PATH}/source)
  # Copying /home/stibel/examples/build/examples/3partlib/protobuf/game.pb.cc to /home/stibel/examples/examples/3partlib/protobuf/
 
ENDFOREACH()

#可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${3PARTLIB_EXECUTABLE_OUTPUT_PATH}/protobuf)

#头文件目录
INCLUDE_DIRECTORIES( ${PROTOBUF_INCLUDE}  ./include )

#目录源码路径
SET( PROTOBUFTEST_SRC_DIR ./source )

#代码列表
FILE (GLOB PROTOBUFTEST_FILES ${PROTOBUFTEST_SRC_DIR}/*.cpp ${PROTOBUFTEST_SRC_DIR}/*.cc)

#依赖的LIB
SET(PROTOBUFTEST_LIB  ${LIB_PROTOBUF} ${LIB_PTHREAD} )

#生成 
ADD_EXECUTABLE( protobufTest ${PROTOBUFTEST_FILES})

#连接生成相关库
TARGET_LINK_LIBRARIES( protobufTest ${PROTOBUFTEST_LIB} )

