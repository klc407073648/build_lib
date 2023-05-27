/**
 * @file mutexLock.h
 * @brief 互斥锁类封装
 * @author klc
 * @date 2020-04-30
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_MUTEXLOCK_H__
#define __STIBEL_MUTEXLOCK_H__

#include <pthread.h>
#include <cstdio>
#include "StiBel/Common/Noncopyable.h"

namespace StiBel {

/**
* @brief 互斥锁类
*/
class MutexLock: Noncopyable
{
public:
    MutexLock()
    {
        pthread_mutex_init(&mutex, NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_lock(&mutex);
        pthread_mutex_destroy(&mutex);
    }
    bool lock()
    {
        return pthread_mutex_lock(&mutex) == 0;
    }
    bool unlock()
    {
        return pthread_mutex_unlock(&mutex) == 0;
    }

    pthread_mutex_t *get()
    {
        return &mutex;
    }
private:
    pthread_mutex_t mutex;
};

/**
* @brief 互斥锁控制器类，构造析构封装了加锁和解锁的过程
*/
class MutexLockGuard: Noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &_mutex):
    mutex(_mutex)
    {
        mutex.lock();
    }
    ~MutexLockGuard()
    {
        mutex.unlock();
    }
private:
    MutexLock &mutex;
};

} // namespace StiBel

#endif //__STIBEL_MUTEXLOCK_H__