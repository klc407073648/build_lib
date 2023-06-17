#ifndef CommonTest_H_
#define CommonTest_H_

#include <iostream>
#include "gtest/gtest.h"

class CommonTest : public ::testing::Test
{
protected:
    // You can do set-up work for each test here.
    CommonTest(){}

    // You can do clean-up work that doesn't throw exceptions here.
    virtual ~CommonTest(){}

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    virtual void SetUp(){}

    // Code here will be called immediately after each test (right
    // before the destructor).
    virtual void TearDown(){}

public:
};

#endif /* CommonTest */