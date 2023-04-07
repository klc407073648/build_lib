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

# 构建examples
if(CMAKE_BUILD_PROJECT_OPTION STREQUAL "all")
  option(MYPRJ_BUILD_EXAMPLES "Build All examples" ON)
endif()

#构建测试用例
option(BUILD_TESTS "Build all tests." ON) 