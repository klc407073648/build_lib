#contain sh
config_file=comlib_config

source ./common.sh

cur_path=`pwd`

#defalut print logDebug
function writeLogFileAndEcho()
{
   if [ "$2"x = ""x ];then
       write_log "$1"  && logDebug "$1"
   else
       write_log "$1"  && "$2" "$1"
   fi
}

function preDeal()
{
   logInfo "preDeal begin"

   rm -rf $cur_path/../include/comlib/*
   rm -rf $cur_path/../lib/comlib/*

   logInfo "preDeal end"
}

function parseConfigFile()
{
   writeLogFileAndEcho "parseConfigFile begin" 

   logInfo "parse var from $config_file"

   build_list=`cat $config_file |grep "build_list=" |cut -f2 -d'='`

   logInfo "build_list is $build_list"


   writeLogFileAndEcho "parseConfigFile end"
}

function copyHeadFile()
{
   writeLogFileAndEcho "copyHeadFile begin" 

   for build_name in $build_list  
   do 
      writeLogFileAndEcho "copyHeadFile $build_name begin"
   
      mkdir -p $cur_path/../include/comlib/StiBel/$build_name/include
      cp -rf $cur_path/StiBel/$build_name/include/*   $cur_path/../include/comlib/StiBel/$build_name/include

      writeLogFileAndEcho "copyHeadFile $build_name end"
   done  

   writeLogFileAndEcho "copyHeadFile end"
}

function buildComlib()
{
   writeLogFileAndEcho "buildComlib begin" 

   cd $cur_path/build

   cmake .. && make

   writeLogFileAndEcho "buildComlib end"
}

function MAIN()
{
   writeLogFileAndEcho "MAIN begin"
   preDeal
   parseConfigFile
   copyHeadFile
   buildComlib
   writeLogFileAndEcho "MAIN end" 
}

MAIN
