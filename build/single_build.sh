#!/bin/bash
# build_lib\build_comlib 下使用
# build_lib\examples 下使用
set -x

curPath=$(pwd)
versionNum=''
config_file='common.sh'
cmake_build_type='Release'
cmake_build_version='V2.1.1'

[ ! -z $1 ] && cmake_build_type=$1

[ ! -z $2 ] && cmake_build_version=$2

function single_build() {
	echo "single_build begin"

	if [ ! -d ${curPath}/build ]; then
		mkdir -p ${curPath}/build 
	fi

	rm -rf ${curPath}/build/*

	cd ${curPath}/build

	LIB_PATH=$curPath/../output/lib

	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${LIB_PATH}/3partlib:${LIB_PATH}/comlib

	cmake -DCMAKE_BUILD_TYPE=${cmake_build_type} -DCMAKE_BUILD_VERSION=${cmake_build_version} ..

	make

	echo "single_build end"
}

function MAIN() {
	echo "[$FUNCNAME] ${0} begin"
	single_build
	echo "[$FUNCNAME] ${0} end"
}

MAIN
