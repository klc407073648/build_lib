CMAKE_MINIMUM_REQUIRED(VERSION 2.8)  # 设定版本
PROJECT(BUILD_LIB) # 设定工程名
SET(CMAKE_CXX_COMPILER "g++")  # 设定编译器

# 设置依赖的cmake的路径
SET(PRJ_CMAKE_FILE_PATH ${PROJECT_SOURCE_DIR}/../examples/cmake)

# 编译选项
include(${PRJ_CMAKE_FILE_PATH}/options.cmake)

# 编译内容信息
include(${PRJ_CMAKE_FILE_PATH}/message.cmake)

# 设定可执行二进制文件和库目录,为各个examples文件设置输出路径
#EXECUTABLE_OUTPUT_PATH为生成可执行文件路径，LIBRARY_OUTPUT_PATH为生成库文件路径。
SET(BUILD_LIB_DIR ${PROJECT_SOURCE_DIR}/../output/lib/comlib)
SET(LIBRARY_OUTPUT_PATH ${BUILD_LIB_DIR})
SET(STIBEL_TEST_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../output/StiBel/test)
SET(STIBEL_SAMPLES_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../output/StiBel/samples)

# 设置第三方应用库的头文件
SET(3PART_PATH  ${PROJECT_SOURCE_DIR}/../output/include/3partlib)
include(${PRJ_CMAKE_FILE_PATH}/3partlib.cmake)

# 设置公共库头文件,其他文件仅需要依赖Common内容
SET(COMM_PATH       ${PROJECT_SOURCE_DIR})
include(${PRJ_CMAKE_FILE_PATH}/comlib.cmake)

# 设置各类应用库的文件路径
SET(3PART_DIR  ${PROJECT_SOURCE_DIR}/../output/lib/3partlib)

#设置自定义搜索路径
set(CMAKE_INCLUDE_PATH ${3PART_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH ${3PART_DIR})

#添加外部库的搜索路径
LINK_DIRECTORIES(${3PART_DIR})

ADD_SUBDIRECTORY(
		./StiBel
	)