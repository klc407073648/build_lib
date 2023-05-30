#include <iostream>
#include "CommonTest.h"
#include "StiBel/XML/XmlUtil.h"

using namespace StiBel::XML;

/* XmlUtilTest */
class XmlUtilTest : public CommonTest
{

protected:
    XmlUtilTest()
    {
    }

    ~XmlUtilTest()
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

/* XmlUtilTest */

/* 测试json字符串读取 */
TEST_F(XmlUtilTest, Given_json_str_When_get_Then_success_parse_content)
{
   XmlUtil::printXml("test.xml");
}
