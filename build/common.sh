#注意大写的全是宏定义值

#当前路径、第三方库构建路径、公共库构建路径
# 加入项目目录,后续注入到环境变量env中
#export prj_path='$PRJ_PATH'
#export cur_path=$prj_path
cur_path=`pwd`
build_3partlib_path=$cur_path/../build_3partlib/
build_comlib_path=$cur_path/../build_comlib/

#第三方库组件列表、公共库组件列表
build_3partlib_list='$COMP_3PARTLIB_LIST'
build_comlib_list='$COMP_COMLIB_LIST'

# cmake构建类型、构建版本、tar.gz是否保留静态库
cmake_build_type=$CMAKE_BUILD_TYPE
cmake_build_version=$CMAKE_BUILD_VERSION
is_use_static_lib=$IS_USE_STATIC_LIB

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
comp2tar["openssl"]="$COMP_OPENSSL"
comp2tar["zlib"]="$COMP_ZLIB"
comp2tar["uuid"]="$COMP_UUID"

#日志路径、日志文件、日志级别
log_dir=$cur_path/$LOG_PATH
log_file=$log_dir/$LOG_FILE_NAME
log_level=$LOG_LEVEL

#日志级别
logDebugNum=4
logInfoNum=3
logWarnNum=2
logErrorNum=1

#日志级别
use_static_lib=1
not_use_static_lib=0

#是否保存日志
isSave=1

function printBuildInfo()
{
   logInfo "build_3partlib_path:$build_3partlib_path"
   logInfo "build_comlib_path:$build_comlib_path"

   logInfo "build_3partlib_list:$build_3partlib_list"
   logInfo "build_comlib_list:$build_comlib_list"

   logInfo "log_dir:$log_dir"
   logInfo "log_file:$log_file"
   logInfo "log_level:$log_level"

   logInfo "cmake_build_type:$cmake_build_type"
   logInfo "cmake_build_version:$cmake_build_version"
   logInfo "is_use_static_lib:$is_use_static_lib"

   for key in ${!comp2tar[*]};do
      logInfo "$key:${comp2tar[$key]}"
   done
}

#写日志
function write_log()
{
  if [ ! -d ${log_dir} ];then
	 mkdir -p ${log_dir} 
  fi
  
  if [ ! -f ${log_file} ];then
	 touch  ${log_file} 
  fi
  
  fileCount=`ls ${log_dir}/*.log |wc -l`
  
  if [ ${fileCount} -gt 10 ];then
     find ${log_dir} -type f |xargs ls -tr | head -5 | xargs rm
  fi
  
  echo -n `date "+%Y-%m-%d %T "` >>${log_file}
  echo " $1" >>${log_file}
  
  return 0
}

#日志打印函数
#四个级别:Debug、Info、Warn、Error
function logDebug()
{
   if [ $log_level -ge $logDebugNum ];then 
      echo -e "\033[32m[Debug] -- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logInfo()
{
   if [ $log_level -ge $logInfoNum ];then 
      echo -e "\033[36m[Info] -- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logWarn()
{
   if [ $log_level -ge $logWarnNum ];then 
      echo -e "\033[33m[Warn] -- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logError()
{
   if [ $log_level -ge $logErrorNum ];then
      echo -e "\033[31m[Error] -- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

#校验执行结果
function checkBuildResult()
{
   if [ $? -ne 0 ];then
       write_log "check $1 fail"  && logError "check $1 fail"
       exit 1
   else
       write_log "check $1 success"  && logDebug "check $1 success"
   fi
}