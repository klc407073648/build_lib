# googletest

* [官网](https://google.github.io/googletest/)
* [googletest使用](https://blog.csdn.net/m0_65931372/article/details/126527421)

## 概述

GoogleTest is Google’s C++ **testing and mocking framework**. This user’s guide has the following contents:

* GoogleTest Primer - Teaches you how to write simple tests using GoogleTest. Read this first if you are new to GoogleTest.
* GoogleTest Advanced - Read this when you’ve finished the Primer and want to utilize GoogleTest to its full potential.
* GoogleTest Samples - Describes some GoogleTest samples.
* GoogleTest FAQ - Have a question? Want some tips? Check here first.
* Mocking for Dummies - Teaches you how to create mock objects and use them in tests.
* Mocking Cookbook - Includes tips and approaches to common mocking use cases.
* Mocking Cheat Sheet - A handy reference for matchers, actions, invariants, and more.
* Mocking FAQ - Contains answers to some mocking-specific questions.

## 编写用例

ASSERT_EQ: 出错程序终止，失败时中止，常用于前后有关系的场景。
EXPECT_EQ: 出错程序继续运行，可以在测试报告展示多个错误。

```cpp
EXPECT_TRUE( condition );
ASSERT_TRUE( condition );
EXPECT_FALSE( condition );
ASSERT_FALSE( condition );

//二元比较，等于
EXPECT_EQ( val1 , val2 );
ASSERT_EQ( val1 , val2 );

//不等于，注意比较空指针的时候，使用EXPECT_NE( ptr , nullptr) 而不是 EXPECT_NE( ptr , NULL) 
EXPECT_NE( val1 , val2 );
ASSERT_NE( val1 , val2 );

//小于
EXPECT_LT( val1 , val2 );
ASSERT_LT( val1 , val2 );

//小于等于
EXPECT_LE( val1 , val2 );
ASSERT_LE( val1 , val2 );

//大于
EXPECT_GT( val1 , val2 );
ASSERT_GT( val1 , val2 );

//大于等于
EXPECT_GE( val1 , val2 );
ASSERT_GE( val1 , val2 );

//谓词断言，能比 EXPECT_TRUE 提供更详细的错误消息
EXPECT_PRED1( pred , val1 );
EXPECT_PRED2( pred , val1 , val2 );
EXPECT_PRED3( pred , val1 , val2 , val3 );
EXPECT_PRED4( pred , val1 , val2 , val3 , val4 );
EXPECT_PRED5( pred , val1 , val2 , val3 , val4 , val5 );
ASSERT_PRED1( pred , val1 );
ASSERT_PRED2( pred , val1 , val2 );
ASSERT_PRED3( pred , val1 , val2 , val3 );
ASSERT_PRED4( pred , val1 , val2 , val3 , val4 );
ASSERT_PRED5( pred , val1 , val2 , val3 , val4 , val5 );
```


```cpp
ASSERT_EQ(x.size(), y.size()) << "Vectors x and y are of unequal length";

for (int i = 0; i < x.size(); ++i) {
  EXPECT_EQ(x[i], y[i]) << "Vectors x and y differ at index " << i;
}
```

### 简单测试

Use the TEST():
```cpp
TEST(TestSuiteName, TestName) {
  ... test body ...
}
```

对应同一个函数的测试，一个使用相同的**TestSuiteName**

```cpp
// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(Factorial(0), 1);
}

// Tests factorial of positive numbers.
TEST(FactorialTest, HandlesPositiveInput) {
  EXPECT_EQ(Factorial(1), 1);
  EXPECT_EQ(Factorial(2), 2);
  EXPECT_EQ(Factorial(3), 6);
  EXPECT_EQ(Factorial(8), 40320);
}
```

### 测试夹具

当使用两个或多个程序操作相似的数据时，可以使用测试夹具。

```cpp
TEST_F(TestFixtureClassName, TestName) {
  ... test body ...
}
```

示例: 

```cpp
class QueueTest : public ::testing::Test {
 protected:
  void SetUp() override {
     // q0_ remains empty
     q1_.Enqueue(1);
     q2_.Enqueue(2);
     q2_.Enqueue(3);
  }

  // void TearDown() override {}

  Queue<int> q0_;
  Queue<int> q1_;
  Queue<int> q2_;
};
```


```
TEST_F(QueueTest, IsEmptyInitially) {
  EXPECT_EQ(q0_.size(), 0);
}

TEST_F(QueueTest, DequeueWorks) {
  int* n = q0_.Dequeue();
  EXPECT_EQ(n, nullptr);

  n = q1_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 1);
  EXPECT_EQ(q1_.size(), 0);
  delete n;

  n = q2_.Dequeue();
  ASSERT_NE(n, nullptr);
  EXPECT_EQ(*n, 2);
  EXPECT_EQ(q2_.size(), 1);
  delete n;
}
```

# examples下的demo使用

路径: build_lib\examples\examples\3partlib\googletest

代码

```cpp
// 校验当前用户成功
TEST_F(UserControllerCurrentTest, current_user_check_success)
{
    // 前面获取过程忽略
    EXPECT_EQ("admin", "admin") << "check current user fail.";
}

// 校验当前用户失败
TEST_F(UserControllerCurrentTest, current_user_check_fail)
{
    // 前面获取过程忽略
    EXPECT_EQ("admin", "klcadmin") << "check current user fail.";
}
```

执行结果:

```
[root@5d4b980baaa2 build]# ./googletest/googletest_test
[==========] Running 2 tests from 1 test suite.
[----------] Global test environment set-up.
[----------] 2 tests from UserControllerCurrentTest
[ RUN      ] UserControllerCurrentTest.current_user_check_success
[       OK ] UserControllerCurrentTest.current_user_check_success (0 ms)
[ RUN      ] UserControllerCurrentTest.current_user_check_fail
/home/stibel/examples/examples/3partlib/googletest/source/UserCurrent.cpp:16: Failure
Expected equality of these values:
  "admin"
    Which is: 0x403d60
  "klcadmin"
    Which is: 0x403d5d
check current user fail.
[  FAILED  ] UserControllerCurrentTest.current_user_check_fail (0 ms)
[----------] 2 tests from UserControllerCurrentTest (0 ms total)

[----------] Global test environment tear-down
[==========] 2 tests from 1 test suite ran. (1 ms total)
[  PASSED  ] 1 test.
[  FAILED  ] 1 test, listed below:
[  FAILED  ] UserControllerCurrentTest.current_user_check_fail

 1 FAILED TEST

```