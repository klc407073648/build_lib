# cppunit使用

# 参考文章

* [HowToUseCppUnit](https://github.com/niceSimon7/HowToUseCppUnit)
* [CppUnit快速入门](https://blog.csdn.net/wyyy2088511/article/details/80107131)
* [cppunit使用详解](https://www.cnblogs.com/zhoug2020/p/4515729.html)

## 编译

```
cd /home/tools/cppunit/
tar  -zxf cppunit-1.12.1.tar.gz
cd ./cppunit-1.12.1/
./configure
make
make install
```

## 使用

```
[root@VM-0-10-centos cppunit]# export LD_LIBRARY_PATH=/usr/local/lib
[root@VM-0-10-centos cppunit]# g++ -o  testApp testApp.cpp -I/usr/local/include/cppunit -L/usr/local/lib -lcppunit -ldl
[root@VM-0-10-centos cppunit]# ./testApp
Test::testHelloWorldHello, world!
 : OK
 
[root@VM-0-10-centos cppunit]# g++ -o  simpleTest simpleTest.cpp -I/usr/local/include/cppunit -L/usr/local/lib -lcppunit -ldl
[root@VM-0-10-centos cppunit]# ./simpleTest

!!!FAILURES!!!
Test Results:
Run:  1   Failures: 1   Errors: 0


1) test:  (F) line: 13 simpleTest.cpp
equality assertion failed
- Expected: 0
- Actual  : 1
```
