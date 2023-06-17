#include "StiBel/Util/Util.h" 
#include "StiBel/Test/CommonTest.h" 
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using namespace StiBel::Util;
using StiBel::Test::CommonTest;

/* UtilTest */
class UtilTest : public CommonTest
{

protected:
    UtilTest()
    {
    }

    ~UtilTest()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

public:
};


/* 测试Util */
TEST_F(UtilTest, Given_mykey_When_setenv_Then_success_getenv)
{
    ShellUtil::setEnv("mykey", "myvalue");
    EXPECT_EQ("myvalue111", ShellUtil::getEnv("mykey"));
}
  