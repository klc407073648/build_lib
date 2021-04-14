/**
 * @file Noncopyable.h
 * @brief 非拷贝类封装
 * @author klc
 * @date 2020-04-30
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_NOCOPYABLE_H__
#define __STIBEL_NOCOPYABLE_H__

namespace StiBel {
    
class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}
private:
    Noncopyable(const Noncopyable&);
    const Noncopyable& operator=(const Noncopyable&);
};

} // namespace StiBel

#endif //__STIBEL_NOCOPYABLE_H__