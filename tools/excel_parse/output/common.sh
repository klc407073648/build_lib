#注意大写的全是宏定义值

#当前路径、第三方库构建路径、公共库构建路径
# 加入项目目录,后续注入到环境变量env中
export prj_path='/home/stibel'
export cur_path=$prj_path
export build_3partlib_path=$cur_path/../build_3partlib/
export build_comlib_path=$cur_path/../build_comlib/

#第三方库组件列表、公共库组件列表
export build_3partlib_list='cppcheck cppunit fastcgi googletest hiredis jsoncpp log4cpp poco protobuf tinyxml yamlcpp zeromq drogon'
export build_comlib_list='Common Data/MySQL Data/Redis JSON Log '

# cmake构建类型、构建版本、tar.gz是否保留静态库
export cmake_build_type='Release'
export cmake_build_version='V2.1.1'
export is_use_static_lib=0

#第三方库组件:名称与包全名的映射 componentName2tarName
declare -A comp2tar
comp2tar["cppcheck"]="cppcheck-2.6.tar.gz"
comp2tar["cppunit"]="cppunit-1.12.1.tar.gz"
comp2tar["spawnfcgi"]="spawn-fcgi-1.6.4.tar.gz"
comp2tar["fastcgi"]="fcgi-2.4.1-SNAP-0910052249.tar.gz"
comp2tar["hiredis"]="hiredis-0.14.1.tar.gz"
comp2tar["jsoncpp"]="jsoncpp-1.9.5.tar.gz"
comp2tar["log4cpp"]="log4cpp-1.1.3.tar.gz"
comp2tar["poco"]="poco-1.12.2-all.tar.gz"
comp2tar["protobuf"]="protobuf-3.6.1.tar.gz"
comp2tar["tinyxml"]="tinyxml-2.6.2.tar.gz"
comp2tar["yamlcpp"]="yaml-cpp-yaml-cpp-0.6.3.tar.gz"
comp2tar["zeromq"]="libzmq-4.3.4.tar.gz"
comp2tar["cppzmq"]="cppzmq-4.8.0.tar.gz"
comp2tar["googletest"]="googletest-release-1.11.0.tar.gz"
comp2tar["trantor"]="trantor-1.5.10.tar.gz"
comp2tar["drogon"]="drogon-1.8.3.tar.gz"

#日志路径、日志文件、日志级别
log_dir=$cur_path/mylog
log_file=$log_dir/build.log
log_level=4
