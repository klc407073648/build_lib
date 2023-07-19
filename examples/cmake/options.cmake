MESSAGE (STATUS "options set begin")

# 设置C++编译选项
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -g -fpermissive")

#设置是否生成共享库
SET(BUILD_SHARED_LIBS ON)

# 选项: 构建用例 和 CTest用例
option(BUILD_EXAMPLES "Enable build all examples" ON)

# 选项: 构建build_comlib下StiBel子目录的test
option(BUILD_TESTS "Build all tests" ON)

# 选项: 构建build_comlib下StiBel子目录的samples
option(BUILD_SAMPLES "Build all samples" ON)

# 构建类型
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  SET(CMAKE_BUILD_TYPE "Debug")
  SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -DDEBUG")
else()
  SET(CMAKE_BUILD_TYPE "Release")
  SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O2 -DNDEBUG")
endif()

# 构建版本
if(NOT CMAKE_BUILD_VERSION)
  SET(LIB_VERSION "V1.1.0")
else()
  SET(LIB_VERSION ${CMAKE_BUILD_VERSION})
endif()

MESSAGE (STATUS "options set end")