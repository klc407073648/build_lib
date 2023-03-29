# poco

# 参考资料

* [源码](https://github.com/pocoproject/poco)

# 概述

> 基本版本（Basic Edition）不需要外部依赖

> 完整版本（Complete Edition）：需要外部依赖OpenSSL、MySQL 客户端和ODBC


## 精简版

```
cd $cur_path/$poco_path
poco_output="$cur_path/$poco_path/output"
mkdir -p  $poco_output
tar -zxvf poco-1.10.1-all.tar.gz
cd ./poco-1.10.1-all
./configure --config=Linux --no-tests --no-samples --minimal --prefix=$poco_output
make && make install

./configure --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB,Redis, --prefix=/home/MyPrj_V12/build_comlib/poco/output

--no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB,Redis, --prefix=/home/MyPrj_V14/build_comlib/poco/output

./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=/home/poco/poco-1.12.2-all/poco_output

选项说明：
–config=Linux：在Linux环境下编译
–minimal：最小功能编译，只构建XML、JSON、工具和网络
–no-tests：不编译测试部分的代码
–no-samples：不编译样例部分的代码
-prefix：指定安装路径
```

## 完整版

```
yum -y install unixODBC
yum -y install unixODBC-devel
yum -y install mysql
yum -y install mysql-devel
yum -y install openssl-devel 
yum -y install postgresql-devel
./configure
make && make install
```

执行过程
```
1.普通用户中下载gcc的最新源码包：(或在http://mirror.hust.edu.cn/gnu/gcc/gcc-9.1.0/中下载)

wget http://ftp.gnu.org/gnu/gcc/gcc-9.1.0/gcc-9.1.0.tar.gz

2. 解压安装包

tar -xzvf gcc-9.1.0.tar.gz

3. 进入目录gcc-9.1.0 

 cd gcc-9.1.0

4.运行download_prerequisites脚本

./contrib/download_prerequisites

该脚本文件会帮我们下载、配置、安装依赖库

5. 建立目录，将所有输出放入该目录

mkdir gcc_temp

6. 进入目录

cd gcc_temp

7. 执行以下命令：

../configure -enable-checking=release -enable-languages=c,c++ -disable-multilib

8. 编译（比较耗时，大概2~4小时，编译时注意时间安排）

make  make install

9. 检查验证

执行gcc --version 
```

## 最终POCO编译成功版本

```
[root@VM-16-6-centos ~]# docker run -it -d -v /home/klc/poco:/home/poco --name build_lib_0 docker.io/klc407073648/centos_build_lib:v3.0 bash
29ca61c7c80e4b67265864fe7d0fb44f4c921cb69ecaba7a94648c20b06304c6
[root@VM-16-6-centos ~]# docker exec -it build_lib_0 bash
[root@29ca61c7c80e /]# cd /home/poco/
[root@29ca61c7c80e poco]# tar -zxvf poco-1.12.2-all.tar.gz
[root@29ca61c7c80e poco]# cd ./poco-1.12.2-all
[root@29ca61c7c80e poco-1.12.2-all]# mkdir poco_output
[root@29ca61c7c80e poco-1.12.2-all]# yum install -y mysql mysql-devel openssl-devel
[root@29ca61c7c80e poco-1.12.2-all]# cp -r /usr/lib64/mysql/* /usr/lib/
[root@29ca61c7c80e poco-1.12.2-all]# ./configure --config=Linux --no-tests --no-samples --omit=Data/ODBC,Data/SQLite,Data/PostgreSQL,MongoDB --prefix=/home/poco/poco-1.12.2-all/poco_output
[root@29ca61c7c80e poco-1.12.2-all]# make
[root@29ca61c7c80e poco-1.12.2-all]# make install
```

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\poco

测试XML库代码:

执行结果:

```
[root@5d4b980baaa2 poco]# ./pocoTest
<?xml version='1.0' encoding='UTF-8'?>
<!--This is comment.-->
<root_element>
        <child_element_a a1="1" a2="2"/>
        <child_element_b b1="3" b2="4"/><![CDATA[ignore parse txt !@#$%^&*()]]>txt_content</root_element>
```
