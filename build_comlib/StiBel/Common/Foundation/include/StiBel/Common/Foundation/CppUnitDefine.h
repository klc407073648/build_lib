/**
 * @file CppUnitDefine.h
 * @brief CppUnit的宏定义
 * @author klc
 * @date 2021-03-31
 * @copyright Copyright (c) 2021年 klc
 */

#ifndef __STIBEL_CPPUNITDEFINE_H__
#define __STIBEL_CPPUNITDEFINE_H__

namespace StiBel {
namespace Common {
namespace Foundation {
#define CppUnit_addTest(suite, cls, mth) \
	suite->addTest(new CppUnit::TestCaller<cls>(#mth, &cls::mth))

} // namespace StiBel
} // namespace Common
} // namespace Foundation

#endif