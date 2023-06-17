#include "StiBel/Common/Foundation/ThreadPool.h" 
#include "StiBel/Test/CommonTest.h" 
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using StiBel::Common::Foundation::ThreadPool;
using StiBel::Test::CommonTest;

/* ThreadPoolTest */
class ThreadPoolTest : public CommonTest
{

protected:
    ThreadPoolTest()
    {
    }

    ~ThreadPoolTest()
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

class MyTask
{  
public:  
    MyTask(){}
      
    int run(int i, const char* p)  
    {  
        printf("thread[%lu] : (%d, %s)\n", pthread_self(), i, (char*)p);  
        sleep(1);  
        return 0;  
    }  
};  

/* 测试线程池成功执行任务 */
TEST_F(ThreadPoolTest, Given_threadpool_and_task_When_addTask_to_threadpool_Then_success_exec_task)
{
    //enable_print();//TODO
    ThreadPool threadPool(10,40);  
    MyTask taskObj[20];
    for(int i = 0; i < 20; i++)  
    {
        threadPool.addTask(std::bind(&MyTask::run, &taskObj[i], i, "helloworld"));
    }

    while(1)  
    {  
        printf("there are still %d tasks need to process\n", threadPool.getTaskQueueSize());  
        if (threadPool.getTaskQueueSize() == 0)
        {  
			threadPool.destroyThreads();
			printf("No I will exit from main\n");
			break;
        }  
        sleep(2);  
    } 
}
  
