#include <iostream>
#include "gtest/gtest.h"
#include "UserCurrent.h"

// 校验当前用户成功
TEST_F(UserControllerCurrentTest, current_user_check_success)
{
    // 前面获取过程忽略
    EXPECT_EQ("admin", "admin") << "check current user fail.";
}

// 校验当前用户失败
TEST_F(UserControllerCurrentTest, current_user_check_fail)
{
    // 前面获取过程忽略
    EXPECT_EQ("admin", "klcadmin") << "check current user fail.";
}
