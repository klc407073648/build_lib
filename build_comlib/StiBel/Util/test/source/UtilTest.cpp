#include "StiBel/Util/Util.h" 
#include "CommonTest.h" 
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using namespace StiBel::Util;

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
TEST_F(UtilTest, Given_threadpool_and_task_When_addTask_to_threadpool_Then_success_exec_task)
{
    //TODO
}
  
