#注意大写的全是宏定义值

#当前路径、第三方库构建路径、公共库构建路径
# 加入项目目录,后续注入到环境变量env中
export prj_path='$PRJ_PATH'
export cur_path=$prj_path
export build_3partlib_path=$cur_path/../build_3partlib/
export build_comlib_path=$cur_path/../build_comlib/

#第三方库组件列表、公共库组件列表
export build_3partlib_list='$COMP_3PARTLIB_LIST'
export build_comlib_list='$COMP_COMLIB_LIST'

# cmake构建类型、构建版本、tar.gz是否保留静态库
export cmake_build_type='$CMAKE_BUILD_TYPE'
export cmake_build_version='$CMAKE_BUILD_VERSION'
export is_use_static_lib=$IS_USE_STATIC_LIB

#第三方库组件:名称与包全名的映射 componentName2tarName
declare -A comp2tar
comp2tar["cppcheck"]="$COMP_CPPCHECK"
comp2tar["cppunit"]="$COMP_CPPUNIT"
comp2tar["spawnfcgi"]="$COMP_SPAWNFCGI"
comp2tar["fastcgi"]="$COMP_FCGI"
comp2tar["hiredis"]="$COMP_HIREDIS"
comp2tar["jsoncpp"]="$COMP_JSONCPP"
comp2tar["log4cpp"]="$COMP_LOG4CPP"
comp2tar["poco"]="$COMP_POCO"
comp2tar["protobuf"]="$COMP_PROTOBUF"
comp2tar["tinyxml"]="$COMP_TINYXML"
comp2tar["yamlcpp"]="$COMP_YAMLCPP"
comp2tar["zeromq"]="$COMP_LIBZMQ"
comp2tar["cppzmq"]="$COMP_CPPZMQ"
comp2tar["googletest"]="$COMP_GOOGLETEST"
comp2tar["trantor"]="$COMP_TRANTOR"
comp2tar["drogon"]="$COMP_DROGON"

#日志路径、日志文件、日志级别
log_dir=$cur_path/$LOG_PATH
log_file=$log_dir/$LOG_FILE_NAME
log_level=$LOG_LEVEL
