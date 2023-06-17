/**
 * @file Mutex.h
 * @brief 读写锁、自旋锁
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
 * @brief 局部读锁模板实现
 */
template<class T>
struct ReadScopedLockImpl {
public:
    /**
     * @brief 构造函数
     * @param[in] mutex 读写锁
     */
    ReadScopedLockImpl(T& mutex)
        :_mutex(mutex) {
        _mutex.rdlock();
        _locked = true;
    }

    /**
     * @brief 析构函数,自动释放锁
     */
    ~ReadScopedLockImpl() {
        unlock();
    }

    /**
     * @brief 上读锁
     */
    void lock() {
        if(!_locked) {
            _mutex.rdlock();
            _locked = true;
        }
    }

    /**
     * @brief 释放锁
     */
    void unlock() {
        if(_locked) {
            _mutex.unlock();
            _locked = false;
        }
    }
private:
    /// mutex
    T& _mutex;
    /// 是否已上锁
    bool _locked;
};

/**
 * @brief 局部写锁模板实现
 */
template<class T>
struct WriteScopedLockImpl {
public:
    /**
     * @brief 构造函数
     * @param[in] mutex 读写锁
     */
    WriteScopedLockImpl(T& mutex)
        :_mutex(mutex) {
        _mutex.wrlock();
        _locked = true;
    }

    /**
     * @brief 析构函数
     */
    ~WriteScopedLockImpl() {
        unlock();
    }

    /**
     * @brief 上写锁
     */
    void lock() {
        if(!_locked) {
            _mutex.wrlock();
            _locked = true;
        }
    }

    /**
     * @brief 解锁
     */
    void unlock() {
        if(_locked) {
            _mutex.unlock();
            _locked = false;
        }
    }
private:
    /// Mutex
    T& _mutex;
    /// 是否已上锁
    bool _locked;
};

/**
 * @brief 读写互斥量
 */
class RWMutex : Noncopyable{
public:

    /// 局部读锁
    typedef ReadScopedLockImpl<RWMutex> ReadLock;

    /// 局部写锁
    typedef WriteScopedLockImpl<RWMutex> WriteLock;

    /**
     * @brief 构造函数
     */
    RWMutex() {
        pthread_rwlock_init(&m_lock, nullptr);
    }
    
    /**
     * @brief 析构函数
     */
    ~RWMutex() {
        pthread_rwlock_destroy(&m_lock);
    }

    /**
     * @brief 上读锁
     */
    void rdlock() {
        pthread_rwlock_rdlock(&m_lock);
    }

    /**
     * @brief 上写锁
     */
    void wrlock() {
        pthread_rwlock_wrlock(&m_lock);
    }

    /**
     * @brief 解锁
     */
    void unlock() {
        pthread_rwlock_unlock(&m_lock);
    }
private:
    /// 读写锁
    pthread_rwlock_t m_lock;
};

/**
 * @brief 局部锁的模板实现
 */
template<class T>
struct ScopedLockImpl {
public:
    /**
     * @brief 构造函数
     * @param[in] mutex Mutex
     */
    ScopedLockImpl(T& mutex)
        :_mutex(mutex) {
        _mutex.lock();
        _locked = true;
    }

    /**
     * @brief 析构函数,自动释放锁
     */
    ~ScopedLockImpl() {
        unlock();
    }

    /**
     * @brief 加锁
     */
    void lock() {
        if(!_locked) {
            _mutex.lock();
            _locked = true;
        }
    }

    /**
     * @brief 解锁
     */
    void unlock() {
        if(_locked) {
            _mutex.unlock();
            _locked = false;
        }
    }
private:
    /// mutex
    T& _mutex;
    /// 是否已上锁
    bool _locked;
};

/**
 * @brief 自旋锁
 * 自旋锁是一种用于保护多线程共享资源的锁，与一般的互斥锁(mutex)
 * 不同之处在于当自旋锁尝试获取锁的所有权时会以忙等待(busy waiting)的形式不断的循环检查锁是否可用。
 * 在多处理器环境中对持有锁时间较短的程序来说使用自旋锁代替一般的互斥锁往往能提高程序的性能。
 */
class Spinlock : Noncopyable {
public:
    /// 局部锁
    typedef ScopedLockImpl<Spinlock> Lock;

    /**
     * @brief 构造函数
     */
    Spinlock() {
        pthread_spin_init(&_mutex, 0);
    }

    /**
     * @brief 析构函数
     */
    ~Spinlock() {
        pthread_spin_destroy(&_mutex);
    }

    /**
     * @brief 上锁
     */
    void lock() {
        pthread_spin_lock(&_mutex);
    }

    /**
     * @brief 解锁
     */
    void unlock() {
        pthread_spin_unlock(&_mutex);
    }
private:
    /// 自旋锁
    pthread_spinlock_t _mutex;
};

} // namespace StiBel
} // namespace Common
} // namespace Foundation

#endif //__STIBEL_MUTEXLOCK_H__