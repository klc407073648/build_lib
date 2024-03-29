#include "StiBel/Common/Foundation/ThreadPool.h" 
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

using StiBel::Common::ThreadPool;

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
  
int main()  
{  
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
			exit(0);
        }  
        sleep(2);  
    }  

    return 0;
}  
