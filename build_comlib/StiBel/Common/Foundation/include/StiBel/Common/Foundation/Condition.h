/**
 * @file Condition.h
 * @brief 互斥锁类封装
 * @author klc
 * @date 2020-04-30
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_CONDITION_H__
#define __STIBEL_CONDITION_H__

#include <time.h>
#include <cstdint>
#include <errno.h>
#include <cstdio>
#include <pthread.h>
#include "StiBel/Common/Foundation/Noncopyable.h"
#include "StiBel/Common/Foundation/MutexLock.h"

namespace StiBel {
namespace Common {
namespace Foundation {
/**
* @brief 条件变量类
*/
class Condition: Noncopyable
{
public:
      explicit Condition(MutexLock &mutex) : _mutex(mutex)
      {
          pthread_cond_init(&_cond, NULL);
      }

      ~Condition() 
      { 
          pthread_cond_destroy(&_cond);
      }

      void wait()
      { 
          pthread_cond_wait(&_cond, _mutex.get());
      }

      bool notify() 
      { 
         return  pthread_cond_signal(&_cond) == 0;
      }

      bool notifyAll() 
      { 
          return pthread_cond_broadcast(&_cond) == 0;
      }

      bool waitForSeconds(int seconds)
      {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&_cond, _mutex.get(), &abstime);
      }

private:
      MutexLock &_mutex;
      pthread_cond_t _cond;
};

} // namespace StiBel
} // namespace Common
} // namespace Foundation

#endif //__STIBEL_CONDITION_H__