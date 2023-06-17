#include "StiBel/Test/CommonTest.h"
#include "StiBel/Log/LoggerManager.h"

using namespace StiBel::Log;
using StiBel::Test::CommonTest;

/* LogTest */
class LogTest : public CommonTest
{

protected:
    LogTest()
    {
    }

    ~LogTest()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

public:
};

class randomArray
{
public:
    randomArray()
    {
        LogInfo("randomArray create");
    }
    ~randomArray()
    {
        LogError("randomArray End");
    }

private:
    DECLARE_STATIC_LOGGERMANAGER();
};

CREATE_STATIC_LOGGERMANAGER(randomArray);

/* LogTest */

/* 测试json字符串解析 */
TEST_F(LogTest, Given_json_str_When_parse_Then_success_parse_content)
{
    randomArray* myRandomArray = new randomArray();
    delete myRandomArray;
}