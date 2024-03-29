#!/bin/bash
#set -x

source ./common.sh

function copyHeadFile()
{
   logDebug "copyHeadFile begin" 

   for build_name in $build_comlib_list 
   do 
      logInfo "copyHeadFile $build_name begin"
   
      mkdir -p $build_comlib_path/../output/include/comlib/StiBel/$build_name/include
      cp -rf $build_comlib_path/StiBel/$build_name/include/*   $build_comlib_path/../output/include/comlib/StiBel/$build_name/include

      logInfo "copyHeadFile $build_name end"
   done  

   logDebug "copyHeadFile end"
}

function buildComlib()
{
   logDebug "buildComlib begin" 

   if [ ! -d $build_comlib_path/build ];then
      mkdir -p $build_comlib_path/build
   fi

   cd $build_comlib_path/build

   cmake -DCMAKE_BUILD_TYPE=${cmake_build_type} -DCMAKE_BUILD_VERSION=${cmake_build_version} ..
   make

   logDebug "buildComlib end"
}

function MAIN()
{
   logDebug "build_comLib.sh MAIN begin"
   copyHeadFile
   buildComlib
   logDebug "build_comLib.sh MAIN end" 
}

MAIN
