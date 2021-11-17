#!/bin/bash
source ./common.sh

function copyHeadFile()
{
   writeLogFileAndEcho "copyHeadFile begin" 

   for build_name in $build_comlib_list 
   do 
      writeLogFileAndEcho "copyHeadFile $build_name begin"
   
      mkdir -p $build_comlib_path/../output/include/comlib/StiBel/$build_name/include
      cp -rf $build_comlib_path/StiBel/$build_name/include/*   $build_comlib_path/../output/include/comlib/StiBel/$build_name/include

      writeLogFileAndEcho "copyHeadFile $build_name end"
   done  

   writeLogFileAndEcho "copyHeadFile end"
}

function buildComlib()
{
   writeLogFileAndEcho "buildComlib begin" 

   cd $build_comlib_path/build

   cmake .. && make

   writeLogFileAndEcho "buildComlib end"
}

function MAIN()
{
   writeLogFileAndEcho "MAIN begin"
   copyHeadFile
   buildComlib
   writeLogFileAndEcho "MAIN end" 
}

MAIN
