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
#include "StiBel/Common/Noncopyable.h"
#include "StiBel/Common/MutexLock.h"

namespace StiBel {

/**
* @brief 条件变量类
*/
class Condition: Noncopyable
{
public:
      explicit Condition(MutexLock &_mutex) : mutex(_mutex)
      {
          pthread_cond_init(&cond, NULL);
      }

      ~Condition() 
      { 
          pthread_cond_destroy(&cond);
      }

      void wait()
      { 
          pthread_cond_wait(&cond, mutex.get());
      }

      bool notify() 
      { 
         return  pthread_cond_signal(&cond) == 0;
      }

      bool notifyAll() 
      { 
          return pthread_cond_broadcast(&cond) == 0;
      }

      bool waitForSeconds(int seconds)
      {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
      }

private:
      MutexLock &mutex;
      pthread_cond_t cond;
};

} // namespace StiBel

#endif //__STIBEL_CONDITION_H__