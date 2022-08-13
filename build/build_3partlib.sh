#!/bin/bash
source ./common.sh

cur_target_build_path=''
fastcgi_path='fastcgi'
zeromq_path='zeromq'
log4cpp_path='log4cpp'

function preDeal()
{
   logInfo "preDeal begin"

   rm -rf $build_3partlib_path/../output/include/3partlib/*
   rm -rf $build_3partlib_path/../output/lib/3partlib/*

   logInfo "preDeal end"
}

function copySoAndHead()
{
   logDebug "${build_name} .h and .so deal begin"
   
   mkdir -p $build_3partlib_path/../output/include/3partlib/$build_name/include
   cp -rf $build_include_path/* $build_3partlib_path/../output/include/3partlib/$build_name/include
   cp -rf $build_lib_path/* $build_3partlib_path/../output/lib/3partlib

   logDebug "${build_name} .h and .so deal end"
}

function build_jsoncpp()
{
   #判断所依赖的scons是否已经安装   
   if [ ! -f /usr/bin/scons ];then
      echo "no exist scons,install it"
      unzip  scons-3.1.1.zip
      cd ./scons-3.1.1/ 
      python setup.py install 
      cd -
   else
      echo "exist scons"
   fi

   ##python /usr/bin/scons platform=linux-gcc
   /usr/bin/python2.7 /usr/bin/scons platform=linux-gcc
   libname=`find ./libs -name "libjson*.so"`

   mkdir -p jsoncpp_output/include
   mkdir -p jsoncpp_output/lib

   cp -rf ./include/* ./jsoncpp_output/include
   cp $libname ./jsoncpp_output/lib/libjsoncpp.so

   build_include_path=$cur_target_build_path/jsoncpp_output/include
   build_lib_path=$cur_target_build_path/jsoncpp_output/lib

   copySoAndHead
}

function build_log4cpp()
{
   cd $build_3partlib_path/$log4cpp_path
   cur_build_name=${myMap[$build_name]} 
   tar -zxvf ${cur_build_name}

   log4cpp_build_path=log4cpp
   cd ./$log4cpp_build_path

   mkdir -p  log4cpp_output

   yum install -y libtool
   ./autogen.sh    #需要yum install libtool
   ./configure  --prefix=$build_3partlib_path/$log4cpp_path/$log4cpp_build_path/log4cpp_output

   make -j4  && make install

   build_include_path=./log4cpp_output/include
   build_lib_path=./log4cpp_output/lib

   copySoAndHead
}

function build_tinyxml()
{
   cp ../Makefile ./Makefile

   mkdir -p tinyxml_output/include
   mkdir -p tinyxml_output/lib

   make -j4
         
   cp -rf ./*.h      ./tinyxml_output/include
   cp libtinyxml.so  ./tinyxml_output/lib
   
   build_include_path=./tinyxml_output/include
   build_lib_path=./tinyxml_output/lib

   copySoAndHead
}

function build_zeromq_libzmq()
{
   cd $build_3partlib_path/$zeromq_path
   cur_build_name=${myMap["zeromq"]} 
   tar -zxf ${cur_build_name}

   zeromq_build_path=${cur_build_name%%.tar.gz}

   cd ./$zeromq_build_path
   mkdir zeromq_output
   mkdir build && cd build
   cmake ..
   make -j4 DESTDIR=../zeromq_output/ install

   build_include_path=../zeromq_output/usr/local/include
   build_lib_path=../zeromq_output/usr/local/lib64

   copySoAndHead
}

function build_zeromq_cppzmq()
{
   cd $build_3partlib_path/$zeromq_path
   cur_build_name=${myMap["cppzmq"]} 
   tar -zxf ${cur_build_name}

   cppzmq_build_path=${cur_build_name%%.tar.gz}

   cd ./$cppzmq_build_path
   #加上libzmq路径
   lib_path=$build_3partlib_path/../output/lib/3partlib
   sed -i "/cmake_minimum_required/a\set(CMAKE_LIBRARY_PATH $lib_path)" CMakeLists.txt

   mkdir cppzmq_output
   mkdir build && cd build
   cmake -DCPPZMQ_BUILD_TESTS=OFF ..
   make -j4 DESTDIR=../cppzmq_output/ install

   build_include_path=../cppzmq_output/usr/local/include
   cp -rf $build_3partlib_path/$zeromq_path/ex_include/* $build_include_path
   cp -rf $build_include_path/* $build_3partlib_path/../output/include/3partlib/$build_name/include
   #build_cppzmq_lib_path=$build_3partlib_path/$zeromq_path/$zeromq_build_path/zeromq_output/usr/local/lib64
}

function build_hiredis()
{
   mkdir -p hiredis_output

   make -j4  
   make DESTDIR=./hiredis_output/ install

   build_include_path=./hiredis_output/usr/local/include
   build_lib_path=./hiredis_output/usr/local/lib

   copySoAndHead
}

function build_fastcgi()
{
   cd $build_3partlib_path/$fastcgi_path
   cur_build_name=${myMap[$build_name]} 
   tar -zxf ${cur_build_name} 

   fastcgi_build_path=${cur_build_name%%.tar.gz}
   cd ./$fastcgi_build_path

   mkdir -p fastcgi_output

   cd ./include

   sed -i "/#ifndef FCGIO_H/i\#include<cstdio>" fcgio.h
   sed -i "/#ifndef FCGIO_H/i\#include<stdio.h>" fcgio.h

   cd ..
   ./configure --prefix=$build_3partlib_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output

   make && make install

   build_include_path=$build_3partlib_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output/include
   build_lib_path=$build_3partlib_path/$fastcgi_path/$fastcgi_build_path/fastcgi_output/lib

   copySoAndHead
}

function build_spawn_fcgi()
{
   cd $build_3partlib_path/$fastcgi_path
   cur_build_name=${myMap["spawnfcgi"]} 
   tar -zxf ${cur_build_name} 

   spawnfcgi_build_path=${cur_build_name%%.tar.gz}
   cd ./$spawnfcgi_build_path

   mkdir -p spawnfcgi_output

   ./configure --prefix=$build_3partlib_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output

   make && make install

   build_include_path=$build_3partlib_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output/
   build_lib_path=$build_3partlib_path/$fastcgi_path/$spawnfcgi_build_path/spawnfcgi_output/
   
   copySoAndHead
   #将 bin share 加到PATH
}

function build_poco()
{
   yum install -y mysql mysql-devel openssl-devel
   
   mkdir -p poco_output

   #./configure --config=Linux --no-tests --no-samples --minimal --prefix=$cur_target_build_path/poco_output
   ./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=$cur_target_build_path/poco_output
   make && make install

   build_include_path=./poco_output/include
   build_lib_path=./poco_output/lib

   copySoAndHead
}

function build_cppunit()
{
   mkdir -p cppunit_output

   ./configure --prefix=$cur_target_build_path/cppunit_output

   make && make install

   build_include_path=./cppunit_output/include
   build_lib_path=./cppunit_output/lib
   
   copySoAndHead
}

function build_yamlcpp()
{
   cd $build_3partlib_path/yamlcpp

   cur_build_name=${myMap[$build_name]} 
   tar -zxf ${cur_build_name} 
   
   yamlcpp_build_path=${cur_build_name%%.tar.gz}
   cd ./$yamlcpp_build_path

   mkdir -p yamlcpp_output
   mkdir build && cd build
   CC=/usr/local/bin/gcc CXX=/usr/local/bin/g++ cmake -DYAML_BUILD_SHARED_LIBS=ON -DYAML_CPP_BUILD_TESTS=OFF ..
   make  
   make DESTDIR=../yamlcpp_output/ install

   build_include_path=../yamlcpp_output/usr/local/include
   build_lib_path=../yamlcpp_output/usr/local/lib

   copySoAndHead
}

function build_cppcheck()
{
   mkdir -p cppcheck_output
   mkdir build && cd build
   cmake .. && make -j4
   make install SRCDIR=. DESTDIR=../cppcheck_output/ CFGDIR=../cfg

   cp -rf ../cppcheck_output/usr/local/* $build_3partlib_path/../output/lib/3partlib
}

function build_protobuf()
{
   mkdir -p protobuf_output
   ./autogen.sh    
   ./configure  --prefix=$cur_target_build_path/protobuf_output

   make -j4 && make check
   make install

   build_include_path=./protobuf_output/include
   build_lib_path=./protobuf_output/lib

   mkdir -p $build_3partlib_path/../lib/3partlib/bin
   cp -rf ./protobuf_output/bin/* $build_3partlib_path/../output/lib/3partlib/bin

   copySoAndHead
}

function build_googletest()
{
   mkdir -p googletest_output
   
   mkdir build && cd build
   cmake  -DBUILD_SHARED_LIBS=ON .. && make -j4
   make DESTDIR=../googletest_output/ install

   build_include_path=../googletest_output/usr/local/include
   build_lib_path=../googletest_output/usr/local/lib64

   copySoAndHead
}

function build3partLib()
{
   logDebug "build3partLib begin" 

   for build_name in $build_3partlib_list  
   do 
      logInfo "build $build_name begin"
   
      if [ "$build_name"x = "zeromq"x ];then
           build_zeromq_libzmq
           build_zeromq_cppzmq
      elif [ "$build_name"x = "fastcgi"x ];then
           build_fastcgi
           build_spawn_fcgi
      elif [ "$build_name"x = "log4cpp"x ];then
           build_log4cpp
      elif [ "$build_name"x = "yamlcpp"x ];then
           build_yamlcpp
      else
           cur_build_name=${myMap[$build_name]} ##获取构建组件所对应的tar.gz名称
           cur_build_path=${cur_build_name%%-*} ##获取-前缀内容，一般为tar.gz的存放目录
           cd $build_3partlib_path/$cur_build_path         ##进入对应目录
           tar -zxf ${cur_build_name}           ##解压目标文件
           target_build_path=${cur_build_name%%.tar.gz} ##获取解压后的文件目录
           cd $target_build_path                ##进入解压后的文件目录
           export cur_target_build_path=`pwd`
           build_$build_name  ##构建对应组件
      fi

      logInfo "build $build_name end"
   done  

   logDebug "build3partLib end"
}

function clearBuildPath()
{
   logDebug "clearBuildPath begin"

   rm -rf $build_3partlib_path/$jsoncpp_path/${jsoncpp_name%%.tar.gz}
   rm -rf $build_3partlib_path/$log4cpp_path/log4cpp
   rm -rf $build_3partlib_path/$tinyxml_path/tinyxml
   rm -rf $build_3partlib_path/$zeromq_path/${zeromq_name%%.tar.gz}
   rm -rf $build_3partlib_path/$zeromq_path/${cppzmq_name%%.tar.gz}
   rm -rf $build_3partlib_path/$hiredis_path/${hiredis_name%%.tar.gz}
   rm -rf $build_3partlib_path/$hiredis_path/${protobuf_name%%.tar.gz}

   logDebug "clearBuildPath end"
}

function MAIN()
{
   logDebug "build_3partlib.sh MAIN begin"
   printBuildInfo
   preDeal
   #parseConfigFile
   #clearBuildPath
   build3partLib
   #clearBuildPath
   logDebug "build_3partlib.sh MAIN end" 
}

MAIN
