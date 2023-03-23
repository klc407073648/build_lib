# 使用python脚本解析excel内容

> 使用python脚本完成3part.xlsx内容的解析，并将获取的变量值填入common.sh中，便于后续脚本使用


## 使用方法

使用docker.io/klc407073648/centos_build_lib:v3.0镜像，进入容器后，在run.py的路径下执行以下步骤:

1. pip3 install ./src/xlrd/xlrd-1.2.0-py2.py3-none-any.whl

2. python3 run.py

3. 输出结果如下,也可以见output

```
[root@5d4b980baaa2 tools]# python3 run.py
final data save in  comp3partinfo_full_datas.json
final data save in  comp3partinfo_key_datas.json
[{'COMP_CPPCHECK': 'cppcheck-2.6.tar.gz', 'COMP_CPPUNIT': 'cppunit-1.12.1.tar.gz', 'COMP_SPAWNFCGI': 'spawn-fcgi-1.6.4.tar.gz', 'COMP_FCGI': 'fcgi-2.4.1-SNAP-0910052249.tar.gz', 'COMP_HIREDIS': 'hiredis-0.14.1.tar.gz', 'COMP_JSONCPP': 'jsoncpp-1.9.5.tar.gz', 'COMP_LOG4CPP': 'log4cpp-1.1.3.tar.gz', 'COMP_POCO': 'poco-1.12.2-all.tar.gz', 'COMP_PROTOBUF': 'protobuf-3.6.1.tar.gz', 'COMP_TINYXML': 'tinyxml-2.6.2.tar.gz', 'COMP_YAMLCPP': 'yaml-cpp-yaml-cpp-0.6.3.tar.gz', 'COMP_LIBZMQ': 'libzmq-4.3.4.tar.gz', 'COMP_CPPZMQ': 'cppzmq-4.8.0.tar.gz', 'COMP_GOOGLETEST': 'googletest-release-1.11.0.tar.gz', 'COMP_TRANTOR': 'trantor-1.5.10.tar.gz', 'COMP_DROGON': 'drogon-1.8.3.tar.gz'}]
final data save in  varinfo_full_datas.json
final data save in  varinfo_key_datas.json
[{'LOG_PATH': 'mylog', 'LOG_FILE_NAME': 'build.log', 'LOG_LEVEL': 4, 'COMP_3PARTLIB_LIST': 'cppcheck cppunit fastcgi googletest hiredis jsoncpp log4cpp poco protobuf tinyxml yamlcpp zeromq drogon', 'COMP_COMLIB_LIST': 'Common Data/MySQL Data/Redis JSON Log ', 'CMAKE_BUILD_TYPE': 'Release', 'CMAKE_BUILD_VERSION': 'V2.1.1', 'IS_USE_STATIC_LIB': 0, 'PRJ_PATH': '/home/stibel'}]
```