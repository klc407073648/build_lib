#include "StiBel/Common/Foundation/MutexLock.h"
#include "StiBel/Common/Foundation/Condition.h"
#include "StiBel/Common/Foundation/ThreadPool.h" 
#include <stdio.h>
#include <stdlib.h>

namespace StiBel {
namespace Common {
namespace Foundation {

ThreadPool::ThreadPool(int threadNum , int queueSize)
:_isRunning(true)
{
	_locker = new MutexLock();
	_cond = new Condition(*_locker);
	createThreads(threadNum,queueSize);
}

ThreadPool::~ThreadPool()
{
	destroyThreads();	
}

int ThreadPool::addTask(const Task& task)
{
	printLog("addTask() begin");
	int err = 0;
	if( _locker->lock() == false )
	{
		printLog("addTask() lock  failure");
		return THREADPOOL_LOCK_FAILURE;
	}
	do
	{
		// 请求队列满
		if( _taskQueue.size() >= _queueSize )
		{
			_locker->unlock();
			err = THREADPOOL_QUEUE_FULL;
			break;
		}

		// 线程池停止
		if(!_isRunning)
		{
			err = THREADPOOL_SHUTDOWN;
            break;
		}
		printLog("addTask() push_back  ");
		_taskQueue.push_back(task);

	} while(false);

	if(_locker->unlock()!=0)
	{
		return THREADPOOL_LOCK_FAILURE;
	}

	//唤醒至少一个阻塞在条件变量上的线程
	if(_cond->notify() !=0 )
	{
		err = THREADPOOL_NOTIFY_FAILURE;      
	}
	
	printLog("addTask() end");
	return err;
}

int ThreadPool::getTaskQueueSize()
{
	_locker->lock();
	int size = _taskQueue.size();
	_locker->unlock();
	return size;
}

int ThreadPool::destroyThreads()
{
	printLog("destroyThreads() begin");
    int err = 0;

	if( _locker->lock() == false )
	{
		return THREADPOOL_LOCK_FAILURE;
	}

	do
	{
		if(!_isRunning)
		{
			err = THREADPOOL_SHUTDOWN;
            break;
		}

		if( _cond->notifyAll() !=0 || _locker->unlock() == true)
		{
			err = THREADPOOL_LOCK_FAILURE;
            break;      
		}

		//回收进程
		for (int i = 0; i < _threadNum; i++)
		{
			if(pthread_join(_threads[i], NULL) != 0)
            {
                err = THREADPOOL_THREAD_FAILURE;
            }
		}

	} while (false);
	
	if(!err) 
    {
        free(_threads);
		_threads = NULL;
    }
	printLog("destroyThreads() end");
    return err;
}

int ThreadPool::createThreads(int threadNum , int queueSize)
{
	printLog("createThreads() begin");
	if(threadNum <= 0 || threadNum > MAX_THREADS || queueSize <= 0 || queueSize > MAX_QUEUE) 
    {
        printLog("please check the value of threadNum and queueSize");
		return -1;
    }

	_threadNum = threadNum;
	_queueSize = queueSize;

	_threads = (pthread_t*)malloc(sizeof(pthread_t) * _threadNum);
	for (int i = 0; i < _threadNum; i++)
	{
		if(pthread_create(&_threads[i], NULL, threadFunc, this)!= 0) //线程创建完成，并去执行对应函数threadFunc
		{
			return -1;
		}
	}
	
	printLog("createThreads() end");

	return 0;
}

void ThreadPool::printLog(std::string str)
{
	if( openLog == 1 )
	std::cout<<str<<std::endl;
}

void* ThreadPool::threadFunc(void* arg)
{
	ThreadPool* pool = static_cast<ThreadPool*>(arg);
	pool->run();
    return pool;
}

void ThreadPool::run()
{
	printLog("run() begin");
	while (true)
    {
		Task task = NULL;
		_locker->lock();
		

		while (_taskQueue.empty() && _isRunning)
		{
			//刚开始所有任务都阻塞等待_cond
			_cond->wait();
		}

		if (!_isRunning && _taskQueue.empty())
		{
			break;
		}

		task = _taskQueue.front();
		_taskQueue.pop_front();
		_locker->unlock();
		task();
	}
	
	_locker->unlock();
	printLog("run() end");

}

} // namespace StiBel
} // namespace Common
} // namespace Foundation