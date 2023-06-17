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
#include "StiBel/Common/Foundation/Noncopyable.h"

namespace StiBel {
namespace Common {
namespace Foundation {

/**
* @brief 互斥锁类
*/
class MutexLock: Noncopyable
{
public:
    MutexLock()
    {
        pthread_mutex_init(&_mutex, NULL);
    }
    ~MutexLock()
    {
        pthread_mutex_lock(&_mutex);
        pthread_mutex_destroy(&_mutex);
    }
    bool lock()
    {
        return pthread_mutex_lock(&_mutex) == 0;
    }
    bool unlock()
    {
        return pthread_mutex_unlock(&_mutex) == 0;
    }

    pthread_mutex_t *get()
    {
        return &_mutex;
    }
private:
    pthread_mutex_t _mutex;
};

/**
* @brief 互斥锁控制器类，构造析构封装了加锁和解锁的过程
*/
class MutexLockGuard: Noncopyable
{
public:
    explicit MutexLockGuard(MutexLock &mutex):
    _mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock &_mutex;
};

} // namespace StiBel
} // namespace Common
} // namespace Foundation

#endif //__STIBEL_MUTEXLOCK_H__