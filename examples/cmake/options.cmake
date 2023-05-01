MESSAGE (STATUS "options set begin")

# 设置C++编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

# 构建类型
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Debug")
else()
  set(BUILD_TYPE "Release")
endif()

# 构建版本
if(NOT CMAKE_BUILD_VERSION)
  set(LIB_VERSION "V1.1.0")
else()
  set(LIB_VERSION ${CMAKE_BUILD_VERSION})
endif()

MESSAGE (STATUS "options set end")