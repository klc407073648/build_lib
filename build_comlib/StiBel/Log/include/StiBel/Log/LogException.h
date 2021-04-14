
/**
 * @file LogException.h
 * @brief Log异常处理类
 * @author klc
 * @date 2021-03-31
 * @copyright Copyright (c) 2021年 klc
 */

#ifndef __STIBEL_LOGEXCEPTION_H__
#define __STIBEL_LOGEXCEPTION_H__

#include "StiBel/Exception.h"

namespace StiBel {
namespace Log {

STIBEL_DECLARE_EXCEPTION(LogException, StiBel::Exception)

} } // namespace StiBel::Log


#endif // __STIBEL_LOGEXCEPTION_H__
