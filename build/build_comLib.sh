#!/bin/bash
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

   cd $build_comlib_path/build

   cmake -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_BUILD_VERSION=${CMAKE_BUILD_VERSION} ..
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
