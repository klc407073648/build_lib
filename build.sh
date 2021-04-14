curPath=`pwd`
echo "curPath=$curPath"

cd $curPath/build_3partlib

dos2unix *.sh
dos2unix *config
chmod 777 *.sh

echo "bgein to build 3partlib"
./build_3partlib.sh

if [ $? != 0 ];then 
	echo "build_3partlib.sh fail , quit!"
	exit 1
fi

echo "end to build 3partlib"

echo "bgein to build comlib"

cd $curPath/build_comlib

dos2unix *.sh
dos2unix *config
chmod 777 *.sh

./buildComLib.sh

if [ $? != 0 ];then 
	echo "buildComLib.sh fail , quit!"
	exit 1
fi

echo "end to build comlib"

echo "build libs"

cd $curPath

buildTime=`date +"%Y%m%d"`

tar zcvf StiBel_${buildTime}.tar.gz ./include ./lib
