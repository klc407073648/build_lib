# build_lib

用于编译生成第三方库的头文件和so，进一步二次封装成个人库，便于统一使用。

## 整体框架

 ![动态库制作](./guide/images/动态库制作.png)


## 主要构建逻辑

1. 通过build.sh脚本执行第三方库和个人库的build过程；
2. build.sh里首先会解析3part.xlsx文件，得到第三方组件列表和变量信息的内容；
3. build_3partlib中包含多个文件夹，文件夹内是对应库的源文件，build_3partlib.sh 是第三方库的生成的主要脚本；
4. build_comlib中包含StiBel个人库的源文件,包含Common、Data、JSON等，主要是对现有库进行二次封装，便于使用；
5. 最终生成的头文件和库文件，会放到output文件夹下的include/3partlib(comlib)、lib/3partlib(comlib) 中，并最终打包成 StiBel_20210627.tar.gz 格式的文件。

## 编译环境要求

* gcc : 9.1.0
* Python : 3.7.10
* cmake : 3.14.5

## 容器方式构建

容器构建方式：

1. 主要依赖构建镜像:docker.io/klc407073648/centos_build_lib:v3.0，里面已经集成构建所需依赖。

2. 具体执行过程:

```bash
cd /home/myprj/

git clone git@github.com:klc407073648/build_lib.git

docker run -it -d -v /home/klc/auto_job/build_lib/download/build_lib:/home/klc/auto_job/build_lib/download/build_lib --name build_lib_0 docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash

docker exec -it build_lib_0 bash

cd /home/tools/build_lib/build

chmod 777 *.sh
dos2unix *.sh

./build.sh
```

* 最终执行完毕会显示：

  ```bash
  [100%] Linking CXX executable ../../../../../deploy/comlib/JSON/JsonUtilTest
  [100%] Built target JsonUtilTest
  check build_examples success
  build_examples end
  build.sh MAIN end
  ```

* 生成的文件：
  * `/home/tools/build_lib/output` 下 StiBel_V2.1.1.tar.gz

3. 使用方法
   * 参考 examples下的CMakeLists.txt

## 构建过程示意

第三方库构建：

* 得到构建的组件信息，根据build_3partlib_list内容构建所需组件

![第三方库构建](./guide/images/第三方库构建.png)

第三方库构建：

* 得到构建的组件信息，根据build_comlib_list内容构建所需组件

![个人库构建](./guide/images/个人库构建.png)

测试第三方库:

```bash
[root@68214022c8f0 output]# cd ../examples/deploy/3partlib/jsoncpp/
[root@68214022c8f0 jsoncpp]# pwd
/home/tools/build_lib/examples/deploy/3partlib/jsoncpp
[root@68214022c8f0 jsoncpp]# ./jsoncppTest
{"uploadid": "teststr","code": 100,"msg": "","files": ""}
1
100
teststr
```

测试个人库:
```bash
[root@68214022c8f0 /]# cd /home/tools/build_lib/examples/deploy/comlib/Commom/
[root@68214022c8f0 Commom]# ./ThreadPoolTest
createThreads() begin
run() begin
run() begin
createThreads() end
```

## 单编

example下单编

```
docker run -it -d -v /home/klc/auto_job/build_lib_test:/home/klc/auto_job/build_lib_test --name stibel_build_lib_test_0 docker.io/klc407073648/centos_build_lib:v3.0 /bin/bash

docker exec -it stibel_build_lib_test_0 bash

cd /home/klc/auto_job/build_lib_test/build_lib/examples/
# 宿主机上操作：cp -rf /home/klc/auto_job/build_lib/StiBel_V2.1.1.tar.gz /home/klc/auto_job/build_lib_test/build_lib/examples/

tar -zxvf StiBel_V2.1.1.tar.gz  .
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/klc/auto_job/build_lib_test/build_lib/examples/lib

cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_VERSION=V2.1.1 ..
```

## 项目发展过程

1. 初始版本V1.0

```
build.sh            构建脚本
build_3partlib      第三方库构建
build_comlib        自封装库构建
include             生成库头文件存放路径
lib                 生成库动态库文件存放路径
```

* 加入Redis
* 加入yamlcpp
* 加入sylar的mysql封装库
* 加入protobuf

2. 迭代版本V2.0

```
build               构建脚本(第三方库和自封装库的构建),依赖python解析excel获取变量信息
build_3partlib      第三方库源码
build_comlib        自封装库源码
output              包含include和lib文件夹
```

2. 迭代版本V2.1

```
build               构建脚本(第三方库和自封装库的构建),依赖python解析excel获取变量信息
build_3partlib      第三方库源码
build_comlib        自封装库源码
examples            加入第三方库和公共库的example  （核心）
output              包含include和lib文件夹
```

* 加入guide 各个库的使用md
* 加入poco
* 加入drogon
* 修改cmake，加入.cmake文件模块化处理