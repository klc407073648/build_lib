#!/bin/bash
curPath=`pwd`
buildTime=''
echo "curPath=$curPath"

function preDeal()
{
	echo "bgein to preDeal"

	cd $curPath

	dos2unix *.sh
	chmod 777 *.sh

	echo "end to preDeal"
}

function parseExcel()
{
	echo "bgein to parseExcel"

	cd $curPath

	python3 run.py

	echo "end to parseExcel"
}

function build_3partlib()
{
	echo "bgein to build 3partlib"

	cd $curPath

	./build_3partlib.sh

	echo "end to build 3partlib"
}

function build_comlib()
{
	echo "bgein to build comlib"

	cd $curPath

	./build_comLib.sh

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
	
	echo "build_examples end"
}

function build_tar_file()
{
	echo "build libs begin"

	cd $curPath/../output

	buildTime=`date +"%Y%m%d"`

	tar zcvf StiBel_${buildTime}.tar.gz ./include ./lib

	echo "build libs end"
}

function MAIN()
{
   echo "MAIN begin"
   preDeal
   parseExcel
   build_3partlib
   build_comlib
   build_tar_file
   build_examples
   echo "MAIN end" 
}

MAIN
