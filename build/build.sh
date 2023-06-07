#!/bin/bash
#curPath="/home/stibel"
#mkdir -p $curPath
#set -x

curPath=$(pwd)
versionNum=''
config_file='common.sh'

function preDeal() 
{
	echo "bgein to preDeal"

	cd $curPath

	cp -r /usr/lib64/mysql/* /usr/lib/
	#pip3 install -r requirements.txt
	# 临时屏蔽，直接根据源码包安装，避免网络原因安装失败
	pip3 install ./src/xlrd/xlrd-1.2.0-py2.py3-none-any.whl

	checkBuildResult preDeal

	dos2unix *.sh
	chmod 777 *.sh

	echo "end to preDeal"
}

function parseExcel() {
	echo "bgein to parseExcel"

	cd $curPath

	python3 run.py

	checkBuildResult parseExcel

	echo "end to parseExcel"
}

function build_3partlib() {
	echo "bgein to build 3partlib"

	cd $curPath

	./build_3partlib.sh

	checkBuildResult build_3partlib

	echo "end to build 3partlib"
}

function build_comlib() {
	echo "bgein to build comlib"

	cd $curPath

	./build_comLib.sh

	checkBuildResult build_comlib

	echo "end to build comlib"
}

function static_lib_deal() {
	echo "bgein to static lib deal"

	cd $curPath

	if [ $IS_USE_STATIC_LIB -eq $not_use_static_lib ]; then
		cd $curPath/../output/lib/3partlib/
		rm -rf ./*.a
		echo "delete static lib file *.a"
	fi

	echo "end to static lib deal"
}

function build_tar_file() 
{
	echo "build_tar_file begin"

	cd $curPath/../output

	#buildTime=`date +"%Y%m%d"`
	#tar zcvf StiBel_${buildTime}.tar.gz ./include ./lib

	versionNum=$(cat $curPath/$config_file | grep "cmake_build_version=" | cut -f2 -d'=')

	tar zcvf StiBel_${versionNum}.tar.gz ./include ./lib

	checkBuildResult build_tar_file

	echo "build_tar_file end"
}

function build_examples() 
{
	echo "build_examples begin"

	cd $curPath/../examples

	cp $curPath/../output/StiBel_${versionNum}.tar.gz .
	tar -zxf StiBel_${versionNum}.tar.gz

	if [ ! -d $curPath/../examples/build ]; then
		mkdir -p $curPath/../examples/build
	fi

	cd ./build

	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$curPath/../examples/lib/3partlib:$curPath/../examples/lib/comlib

	cmake_build_type=$(cat $curPath/$config_file | grep "cmake_build_type=" | cut -f2 -d'=')
	cmake_build_version=$(cat $curPath/$config_file | grep "cmake_build_version=" | cut -f2 -d'=')
	cmake -DCMAKE_BUILD_TYPE=${cmake_build_type} -DCMAKE_BUILD_VERSION=${cmake_build_version} ..

	make

	checkBuildResult build_examples

	echo "build_examples end"
}

function build_tar_with_cmake() 
{
	echo "build_tar_with_cmake begin"

	rm -rf $curPath/../examples/StiBel_${versionNum}.tar.gz

	rm -rf $curPath/../output/StiBel_${versionNum}.tar.gz

	cd $curPath/../examples

	tar zcvf StiBel_${versionNum}.tar.gz ./include ./lib ./cmake ./conf

	cp $curPath/../examples/StiBel_${versionNum}.tar.gz $curPath/../output

	checkBuildResult build_tar_with_cmake

	echo "build_tar_with_cmake end"
}

function checkBuildResult() 
{
	if [ $? -ne 0 ]; then
		echo "check $1 fail"
		exit 1
	else
		echo "check $1 success"
	fi
}

function MAIN() 
{
	echo "build.sh MAIN begin"
	preDeal
	parseExcel
	build_3partlib
	build_comlib
	static_lib_deal
	build_tar_file
	build_examples
	build_tar_with_cmake
	echo "build.sh MAIN end"
}

MAIN
