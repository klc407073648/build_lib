curPath=`pwd`
echo "curPath=$curPath"

function build_3partlib()
{
	echo "bgein to build 3partlib"

	cd $curPath/build_3partlib

	dos2unix *.sh
	dos2unix *config
	chmod 777 *.sh

	./build_3partlib.sh

	echo "end to build 3partlib"
}

function build_comlib()
{
	echo "bgein to build comlib"

	cd $curPath/build_comlib

	dos2unix *.sh
	dos2unix *config
	chmod 777 *.sh

	./buildComLib.sh

	echo "end to build comlib"
}

function check_build_result()
{
	echo "check_build_result begin"

	cd $curPath
	build_list_3partlib=`cat ./build_3partlib/3partlib_config |grep "build_list=" |cut -f2 -d'='`

	for build_name in $build_list_3partlib  
    do 
		count=`find ./lib/3partlib -name "lib${build_name}*.so" |wc -l`
		if [ $count == "0" ];then
           echo "build ${build_name} fail"
		else
		   echo "build ${build_name} success"
		fi
	done

	build_list_comlib="common json log mysql redis"

	for build_name in $build_list_comlib  
    do 
		count=`find ./lib/comlib -name "libStiBel_${build_name}*.so" |wc -l`
		if [ $count == "0" ];then
           echo "build ${build_name} fail"
		else
		   echo "build ${build_name} success"
		fi
	done

	echo "check_build_result end"
}

function build_tar_file()
{
	echo "build libs begin"

	cd $curPath

	buildTime=`date +"%Y%m%d"`

	tar zcvf StiBel_${buildTime}.tar.gz ./include ./lib

	echo "build libs end"
}


function MAIN()
{
   echo "MAIN begin"
   build_3partlib
   build_comlib
   check_build_result
   build_tar_file
   echo "MAIN end" 
}

MAIN
