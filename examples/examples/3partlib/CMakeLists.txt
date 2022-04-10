#ToolClass
SET(3PART_LIBS JSONCPP LOG4CPP TINYXML ZEROMQ HIREDIS FASTCGI CPPUNIT YAMLCPP PROTOBUF)

#第三方库组件:名称与组件子路径的映射
SET(JSONCPP_PATH jsoncpp)
SET(LOG4CPP_PATH log4cpp)
SET(TINYXML_PATH tinyxml)
SET(ZEROMQ_PATH zeromq)
SET(HIREDIS_PATH redis)
SET(FASTCGI_PATH fastcgi)
SET(CPPUNIT_PATH cppunit)
SET(YAMLCPP_PATH yamlcpp)
SET(PROTOBUF_PATH protobuf)
SET(GOOGLETEST_PATH googletest)

MESSAGE (STATUS "3partlib build begin")

#循环处理,如果包含include和lib文件,则构建对应子路径内容
FOREACH(3PART_LIB ${3PART_LIBS})	
  if(${3PART_LIB}_INCLUDE_DIR AND ${3PART_LIB}_LIBRARY)
    add_subdirectory(${${3PART_LIB}_PATH})
    MESSAGE (STATUS "build ${3PART_LIB}_PATH:" ${${3PART_LIB}_PATH})
  else()
    add_subdirectory(${${3PART_LIB}_PATH} EXCLUDE_FROM_ALL)
    MESSAGE (STATUS "not build ${3PART_LIB}_PATH:" ${${3PART_LIB}_PATH})
  endif()	 
ENDFOREACH()

MESSAGE (STATUS "3partlib build end")
