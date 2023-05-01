MESSAGE (STATUS "linklib set begin")

# 设置各类应用库的文件路径
SET(3PART_DIR  ${PROJECT_SOURCE_DIR}/lib/3partlib)
SET(COMM_DIR   ${PROJECT_SOURCE_DIR}/lib/comlib)

#设置自定义搜索路径
set(CMAKE_INCLUDE_PATH ${3PART_INCLUDE_PATH} ${COMM_INCLUDE_PATH})
set(CMAKE_LIBRARY_PATH ${3PART_DIR} ${COMM_DIR})

# 寻找对应库是否存在
include(${PROJECT_SOURCE_DIR}/cmake/Find3partlib.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/FindComlib.cmake)

#添加外部库的搜索路径
LINK_DIRECTORIES(${3PART_DIR} ${COMM_DIR})


MESSAGE (STATUS "linklib set end")