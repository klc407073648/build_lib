#注意大写的全是宏定义值

#当前路径、第三方库构建路径、公共库构建路径
export cur_path=`pwd`
export build_3partlib_path=$cur_path/../build_3partlib/
export build_comlib_path=$cur_path/../build_comlib/

#第三方库组件列表、公共库组件列表
export build_3partlib_list='$COMP_3PARTLIB_LIST'
export build_comlib_list='$COMP_COMLIB_LIST'

#第三方库组件:名称与包全名的映射
declare -A myMap
myMap["cppcheck"]="$COMP_CPPCHECK"
myMap["cppunit"]="$COMP_CPPUNIT"
myMap["spawnfcgi"]="$COMP_SPAWNFCGI"
myMap["fastcgi"]="$COMP_FCGI"
myMap["hiredis"]="$COMP_HIREDIS"
myMap["jsoncpp"]="$COMP_JSONCPP"
myMap["log4cpp"]="$COMP_LOG4CPP"
myMap["poco"]="$COMP_POCO"
myMap["protobuf"]="$COMP_PROTOBUF"
myMap["tinyxml"]="$COMP_TINYXML"
myMap["yamlcpp"]="$COMP_YAMLCPP"
myMap["zeromq"]="$COMP_LIBZMQ"
myMap["cppzmq"]="$COMP_CPPZMQ"

#日志路径、日志文件、日志级别
log_dir=$cur_path/$LOG_PATH
log_file=$log_dir/$LOG_FILE_NAME
log_level=$LOG_LEVEL

#日志级别
logDebugNum=4
logInfoNum=3
logWarnNum=2
logErrorNum=1

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

   for key in ${!myMap[*]};do
      logInfo "$key:${myMap[$key]}"
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
      echo -e "\033[32m-- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logInfo()
{
   if [ $log_level -ge $logInfoNum ];then 
      echo -e "\033[36m-- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logWarn()
{
   if [ $log_level -ge $logWarnNum ];then 
      echo -e "\033[33m-- $1 --\033[0m"
   fi

   if [ $isSave -eq 1 ];then 
      write_log "$1"
   fi
}

function logError()
{
   if [ $log_level -ge $logErrorNum ];then
      echo -e "\033[31m-- $1 --\033[0m"
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