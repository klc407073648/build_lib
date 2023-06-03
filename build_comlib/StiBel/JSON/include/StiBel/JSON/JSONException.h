
/**
 * @file JSONException.h
 * @brief JSON异常处理类
 * @author klc
 * @date 2021-03-31
 * @copyright Copyright (c) 2021年 klc
 */

#ifndef __STIBEL_JSONEXCEPTION_H__
#define __STIBEL_JSONEXCEPTION_H__

#include "StiBel/Common/Foundation/Exception.h"

namespace StiBel {
namespace JSON {

STIBEL_DECLARE_EXCEPTION(JSONException, StiBel::Common::Foundation::Exception)

} } // namespace StiBel::JSON


#endif // JSON_JSONException_INCLUDED
