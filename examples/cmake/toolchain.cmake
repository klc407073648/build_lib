MESSAGE (STATUS "toolchain set begin")

# 工具链
if( TOOLCHAIN )
  MESSAGE (STATUS "TOOLCHAIN:" ${TOOLCHAIN})
else()
  set(TOOLCHAIN "x86_64-pc-linux-gnu-gcc-9.1.0")
  MESSAGE (STATUS "TOOLCHAIN:" ${TOOLCHAIN})
endif()

# 架构
if( ARCH )
  MESSAGE (ARCH "ARCH:" ${ARCH})
else()
  set(ARCH "x86_64")
  MESSAGE (STATUS "ARCH:" ${ARCH})
endif()

# 编译器
if( ${ARCH} STREQUAL "aarch64" )
  set (CMAKE_C_COMPILER     /usr/local/bin/aarch64-pc-linux-gnu-gcc)
  set (CMAKE_CXX_COMPILER   /usr/local/bin/aarch64-pc-linux-gnu-g++)
else()
  #set (CMAKE_C_COMPILER "/usr/local/${TOOLCHAIN}/bin/x86_64-pc-linux-gnu-gcc")
  set (CMAKE_C_COMPILER     /usr/local/bin/x86_64-pc-linux-gnu-gcc)
  set (CMAKE_CXX_COMPILER   /usr/local/bin/x86_64-pc-linux-gnu-g++)
endif()

MESSAGE (STATUS "toolchain set end")