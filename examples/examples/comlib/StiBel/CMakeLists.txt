#StiBel
SET(COM_LIBS COMMON MYSQL REDIS LOG JSON)#  XML YAML TODO

#第三方库组件:名称与组件子路径的映射
SET(COMMON_PATH Common)
SET(MYSQL_PATH Data/MySQL)
SET(REDIS_PATH Data/Redis)
SET(LOG_PATH Log)
SET(JSON_PATH JSON)
SET(XML_PATH XML)
SET(YAML_PATH YAML)

MESSAGE (STATUS "comlib build begin")

#循环处理,如果包含include和lib文件,则构建对应子路径内容
FOREACH(COM_LIB ${COM_LIBS})
  if(STIBEL_${COM_LIB}_LIBRARY)
    add_subdirectory(${${COM_LIB}_PATH})
    MESSAGE (STATUS "build ${COM_LIB}_PATH:" ${${COM_LIB}_PATH})
  else()
    add_subdirectory(${${COM_LIB}_PATH} EXCLUDE_FROM_ALL)
    MESSAGE (STATUS "not build ${COM_LIB}_PATH:" ${${COM_LIB}_PATH})
  endif()
ENDFOREACH()

MESSAGE (STATUS "comlib build end")