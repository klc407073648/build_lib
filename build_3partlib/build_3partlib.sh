#contain sh
config_file=3partlib_config

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

   rm -rf $cur_path/../include/3partlib/*
   rm -rf $cur_path/../lib/3partlib/*

   logInfo "preDeal end"
}

function parseConfigFile()
{
   writeLogFileAndEcho "parseConfigFile begin" 

   logInfo "parse var from $config_file"

   build_list=`cat $config_file |grep "build_list=" |cut -f2 -d'='`

   logInfo "build_list is $build_list"

   #for line in `cat $config_file`  
   #do   
   #   key=`echo $line |cut -f1 -d'='`
   #   value=`echo $line |cut -f2 -d'='`
   #   export $key=$value
   #   echo "$key=$value"
   #done
   
   jsoncpp_name=`cat $config_file |grep "jsoncpp_name=" |cut -f2 -d'='`
   log4cpp_name=`cat $config_file |grep "log4cpp_name=" |cut -f2 -d'='`
   
   tinyxml_name=`cat $config_file |grep "tinyxml_name=" |cut -f2 -d'='`
   zeromq_name=`cat $config_file |grep "zeromq_name=" |cut -f2 -d'='`
   cppzmq_name=`cat $config_file |grep "cppzmq_name=" |cut -f2 -d'='`

   hiredis_name=`cat $config_file |grep "hiredis_name=" |cut -f2 -d'='`
   fastcgi_name=`cat $config_file |grep "fastcgi_name=" |cut -f2 -d'='`
   spawnfcgi_name=`cat $config_file |grep "spawnfcgi_name=" |cut -f2 -d'='`
   poco_name=`cat $config_file |grep "poco_name=" |cut -f2 -d'='`

   cppunit_name=`cat $config_file |grep "cppunit_name=" |cut -f2 -d'='`

   yamlcpp_name=`cat $config_file |grep "yamlcpp_name=" |cut -f2 -d'='`

   jsoncpp_path=`cat $config_file |grep "jsoncpp_path=" |cut -f2 -d'='`
   log4cpp_path=`cat $config_file |grep "log4cpp_path=" |cut -f2 -d'='`
   tinyxml_path=`cat $config_file |grep "tinyxml_path=" |cut -f2 -d'='`
   zeromq_path=`cat $config_file |grep "zeromq_path=" |cut -f2 -d'='`
   hiredis_path=`cat $config_file |grep "hiredis_path=" |cut -f2 -d'='`
   fastcgi_path=`cat $config_file |grep "fastcgi_path=" |cut -f2 -d'='`
   poco_path=`cat $config_file |grep "poco_path=" |cut -f2 -d'='`
   cppunit_path=`cat $config_file |grep "cppunit_path=" |cut -f2 -d'='`
   yamlcpp_path=`cat $config_file |grep "yamlcpp_path=" |cut -f2 -d'='`

   echo "jsoncpp_name=$jsoncpp_name"
   echo "log4cpp_name=$log4cpp_name"
   
   echo "tinyxml_name=$tinyxml_name"
   echo "zeromq_name=$zeromq_name"
   echo "cppzmq_name=$cppzmq_name"
   echo "hiredis_name=$hiredis_name"
   echo "fastcgi_name=$fastcgi_name"
   echo "spawnfcgi_name=$spawnfcgi_name"
   echo "poco_name=$poco_name"
   echo "cppunit_name=$cppunit_name"
   echo "yamlcpp_name=$yamlcpp_name"

   echo "jsoncpp_path=$jsoncpp_path"
   echo "log4cpp_path=$log4cpp_path"
   echo "tinyxml_path=$tinyxml_path"
   echo "zeromq_path=$zeromq_path"
   echo "hiredis_path=$hiredis_path"
   echo "fastcgi_path=$fastcgi_path"
   echo "poco_path=$poco_path"
   echo "cppunit_path=$cppunit_path"
   echo "yamlcpp_path=$yamlcpp_path"

   writeLogFileAndEcho "parseConfigFile end"
}

function copySoAndHead()
{
   writeLogFileAndEcho "${build_name} .h and .so deal begin"
   
   mkdir -p $cur_path/../include/3partlib/$build_name/include
   cp -rf $build_include_path/* $cur_path/../include/3partlib/$build_name/include
   cp -rf $build_lib_path/* $cur_path/../lib/3partlib

   writeLogFileAndEcho "${build_name} .h and .so deal end"

}

function build_jsoncpp()
{
   cd $cur_path/$jsoncpp_path
   tar -zxf ${jsoncpp_name}
   jsoncpp_build_path=${jsoncpp_name%%.tar.gz}
   cd ./$jsoncpp_build_path

   python /usr/bin/scons platform=linux-gcc 
   libname=`find ./libs -name "libjson*.so"`

   mkdir -p jsoncpp_output/include
   mkdir -p jsoncpp_output/lib

   cp -rf ./include/* ./jsoncpp_output/include
   cp $libname ./jsoncpp_output/lib/libjsoncpp.so

   build_include_path=$cur_path/$jsoncpp_path/$jsoncpp_build_path/jsoncpp_output/include
   build_lib_path=$cur_path/$jsoncpp_path/$jsoncpp_build_path/jsoncpp_output/lib
}

function build_log4cpp()
{
   cd $cur_path/$log4cpp_path
   tar -zxvf ${log4cpp_name}

   log4cpp_build_path=log4cpp
   cd ./$log4cpp_build_path

   mkdir -p  log4cpp_output

   ./autogen.sh    #需要yum install libtool
   ./configure  --prefix=$cur_path/$log4cpp_path/$log4cpp_build_path/log4cpp_output

   make -j4  && make install

   build_include_path=$cur_path/$log4cpp_path/$log4cpp_build_path/log4cpp_output/include
   build_lib_path=$cur_path/$log4cpp_path/$log4cpp_build_path/log4cpp_output/lib
}

function build_tinyxml()
{
   cd $cur_path/$tinyxml_path
   tar -zxf ${tinyxml_name}

   tinyxml_build_path=${tinyxml_name%%.tar.gz}

   cd ./$tinyxml_build_path
   cp ../Makefile ./Makefile

   mkdir -p tinyxml_output/include
   mkdir -p tinyxml_output/lib

   make -j4
         
   cp -rf ./*.h      ./tinyxml_output/include
   cp libtinyxml.so  ./tinyxml_output/lib
   
   build_include_path=$cur_path/$tinyxml_path/$tinyxml_build_path/tinyxml_output/include
   build_lib_path=$cur_path/$tinyxml_path/$tinyxml_build_path/tinyxml_output/lib
}

function build_zeromq_libzmq()
{
   cd $cur_path/$zeromq_path
   tar -zxf ${zeromq_name}

   zeromq_build_path=${zeromq_name%%.tar.gz}

   cd ./$zeromq_build_path
   mkdir zeromq_output
   mkdir build && cd build
   cmake ..
   make -j4 DESTDIR=../zeromq_output/ install

   build_include_path=$cur_path/$zeromq_path/$zeromq_build_path/zeromq_output/usr/local/include
   build_lib_path=$cur_path/$zeromq_path/$zeromq_build_path/zeromq_output/usr/local/lib64

   copySoAndHead
}

function build_zeromq_cppzmq()
{
   cd $cur_path/$zeromq_path
   tar -zxf ${cppzmq_name}

   cppzmq_build_path=${cppzmq_name%%.tar.gz}

   cd ./$cppzmq_build_path
   #加上libzmq路径
   lib_path=$cur_path/../lib/3partlib
   sed -i "/cmake_minimum_required/a\set(CMAKE_LIBRARY_PATH $lib_path)" CMakeLists.txt

   mkdir cppzmq_output
   mkdir build && cd build
   cmake -DCPPZMQ_BUILD_TESTS=OFF ..
   make -j4 DESTDIR=../cppzmq_output/ install

   build_include_path=$cur_path/$zeromq_path/$cppzmq_build_path/cppzmq_output/usr/local/include
   cp -rf $cur_path/$zeromq_path/ex_include/* $build_include_path
   #build_cppzmq_lib_path=$cur_path/$zeromq_path/$zeromq_build_path/zeromq_output/usr/local/lib64
}

function build_hiredis()
{
   cd $cur_path/$hiredis_path
   tar -zxf ${hiredis_name}

   hiredis_build_path=${hiredis_name%%.tar.gz}
   cd ./$hiredis_build_path

   mkdir -p hiredis_output

   make -j4  
   make DESTDIR=./hiredis_output/ install

   build_include_path=$cur_path/$hiredis_path/$hiredis_build_path/hiredis_output/usr/local/include
   build_lib_path=$cur_path/$hiredis_path/$hiredis_build_path/hiredis_output/usr/local/lib
}

function build_fastcgi()
{
   cd $cur_path/$fastcgi_path
   tar -zxf ${fastcgi_name}

   fastcgi_build_path=${fastcgi_name%%.tar.gz}
   cd ./$fastcgi_build_path

   mkdir -p fastcgi_output

   cd ./include

   sed -i "/#ifndef FCGIO_H/i\#include<cstdio>" fcgio.h
   sed -i "/#ifndef FCGIO_H/i\#include<stdio.h>" fcgio.h

   cd ..
   ./configure --prefix=$cur_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output

   make && make install

   build_include_path=$cur_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output/include
   build_lib_path=$cur_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output/lib

   copySoAndHead
}

function build_spawn_fcgi()
{
   cd $cur_path/$fastcgi_path
   tar -zxf ${spawnfcgi_name}

   spawnfcgi_build_path=${spawnfcgi_name%%.tar.gz}
   cd ./$spawnfcgi_build_path

   mkdir -p spawnfcgi_output

   ./configure --prefix=$cur_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output

   make && make install

   build_include_path=$cur_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output/
   build_lib_path=$cur_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output/
   
   #将 bin share 加到PATH
}

function build_poco()
{
   cd $cur_path/$poco_path
   tar -zxf ${poco_name}

   poco_build_path=${poco_name%%.tar.gz}
   cd ./$poco_build_path

   mkdir -p poco_output

   ./configure --config=Linux --no-tests --no-samples --minimal --prefix=$cur_path/$poco_path/$poco_build_path/poco_output

   make && make install

   build_include_path=$cur_path/$poco_path/$poco_build_path/poco_output/include
   build_lib_path=$cur_path/$poco_path/$poco_build_path/poco_output/lib
}

function build_cppunit()
{
   cd $cur_path/$cppunit_path
   tar -zxf ${cppunit_name}

   cppunit_build_path=${cppunit_name%%.tar.gz}
   cd ./$cppunit_build_path

   mkdir -p cppunit_output

   ./configure --prefix=$cur_path/$cppunit_path/$cppunit_build_path/cppunit_output

   make && make install

   build_include_path=$cur_path/$cppunit_path/$cppunit_build_path/cppunit_output/include
   build_lib_path=$cur_path/$cppunit_path/$cppunit_build_path/cppunit_output/lib
   
}

function build_yamlcpp()
{
   cd $cur_path/$yamlcpp_path
   tar -zxf ${yamlcpp_name}

   yamlcpp_build_path=${yamlcpp_name%%.tar.gz}
   cd ./$yamlcpp_build_path

   mkdir -p yamlcpp_output
   mkdir build && cd build
   cmake -DYAML_BUILD_SHARED_LIBS=ON ..
   make  &&  make DESTDIR=../yamlcpp_output/ install

   build_include_path=$cur_path/$yamlcpp_path/$yamlcpp_build_path/yamlcpp_output/usr/local/include
   build_lib_path=$cur_path/$yamlcpp_path/$yamlcpp_build_path/yamlcpp_output/usr/local/lib
}

function build3partLib()
{
   writeLogFileAndEcho "build3partLib begin" 

   for build_name in $build_list  
   do 
      writeLogFileAndEcho "build $build_name begin"
   
      if [ "$build_name"x = "jsoncpp"x ];then
           build_jsoncpp
      elif [ "$build_name"x = "log4cpp"x ];then
           build_log4cpp 
      elif [ "$build_name"x = "tinyxml"x ];then
           build_tinyxml 
      elif [ "$build_name"x = "zeromq"x ];then
           build_zeromq_libzmq
           build_zeromq_cppzmq
      elif [ "$build_name"x = "hiredis"x ];then
           build_hiredis
      elif [ "$build_name"x = "fastcgi"x ];then
           build_fastcgi
           build_spawn_fcgi
      elif [ "$build_name"x = "poco"x ];then
           build_poco
      elif [ "$build_name"x = "cppunit"x ];then
           build_cppunit    
      elif [ "$build_name"x = "yamlcpp"x ];then
           build_yamlcpp   
      fi

      writeLogFileAndEcho "build $build_name end"

      copySoAndHead
   done  

   writeLogFileAndEcho "build3partLib end"
}

function clearBuildPath()
{
   writeLogFileAndEcho "clearBuildPath begin"

   rm -rf $cur_path/$jsoncpp_path/${jsoncpp_name%%.tar.gz}
   rm -rf $cur_path/$log4cpp_path/log4cpp
   rm -rf $cur_path/$tinyxml_path/tinyxml
   rm -rf $cur_path/$zeromq_path/${zeromq_name%%.tar.gz}
   rm -rf $cur_path/$zeromq_path/${cppzmq_name%%.tar.gz}
   rm -rf $cur_path/$hiredis_path/${hiredis_name%%.tar.gz}

   writeLogFileAndEcho "clearBuildPath end"
}

function MAIN()
{
   writeLogFileAndEcho "MAIN begin"
   preDeal
   parseConfigFile
   clearBuildPath
   build3partLib
   clearBuildPath
   writeLogFileAndEcho "MAIN end" 
}

MAIN
