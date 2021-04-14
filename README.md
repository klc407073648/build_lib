# build_lib

用于编译生成第三方库的头文件和so，进一步二次封装成个人库，便于统一使用。

## 主要逻辑

1. 通过build.sh脚本执行第三方库和个人库的build过程。
2. build_3partlib中包含多个文件夹，文件夹内是对应库的源文件。
3. build_3partlib.sh 是第三方库的生成的主要脚本，3partlib_config是配置文件，其中build_list配置了所需要生成的库文件名
4. build_comlib中包含StiBel个人库的源文件,包含Common、Data、JSON等，主要是对现有库进行二次封装，便于使用。其中comlib_config是配置文件，其中build_list配置了所需要生成的库文件名。
5. 最终生成的头文件和so文件，会放到include/3partlib(comlib)、lib/3partlib(comlib) 中，并最终打包成 StiBel_20210406.tar.gz 格式的文件。

## 使用方法

1. 解压文件到工程文件目录

tar zxf StiBel_20210406.tar.gz

2. 在CMakeLists.txt配置各个库的路径


