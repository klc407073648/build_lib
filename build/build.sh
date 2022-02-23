#!/bin/bash
curPath=`pwd`
buildTime=''
echo "curPath=$curPath"

function preDeal()
{
	echo "bgein to preDeal"

	cd $curPath

	cp -r /usr/lib64/mysql/* /usr/lib/
	pip3 install -r requirements.txt

	checkBuildResult preDeal

	dos2unix *.sh
	chmod 777 *.sh

	echo "end to preDeal"
}

function parseExcel()
{
	echo "bgein to parseExcel"

	cd $curPath

	python3 run.py

	checkBuildResult parseExcel

	echo "end to parseExcel"
}

function build_3partlib()
{
	echo "bgein to build 3partlib"

	cd $curPath

	./build_3partlib.sh

	checkBuildResult build_3partlib

	echo "end to build 3partlib"
}

function build_comlib()
{
	echo "bgein to build comlib"

	cd $curPath

	./build_comLib.sh

	checkBuildResult build_comlib

	echo "end to build comlib"
}

function build_examples()
{
	echo "build_examples begin"

	cd $curPath/../examples

	cp $curPath/../output/StiBel_${buildTime}.tar.gz .
	tar -zxf StiBel_${buildTime}.tar.gz

	cd ./build

	cmake ..
	make

	checkBuildResult build_examples
	
	echo "build_examples end"
}

function build_tar_file()
{
	echo "build_tar_file begin"

	cd $curPath/../output

	buildTime=`date +"%Y%m%d"`

	tar zcvf StiBel_${buildTime}.tar.gz ./include ./lib

	checkBuildResult build_tar_file

	echo "build_tar_file end"
}

function checkBuildResult()
{
   if [ $? -ne 0 ];then
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
   build_tar_file
   build_examples
   echo "build.sh MAIN end" 
}

MAIN
