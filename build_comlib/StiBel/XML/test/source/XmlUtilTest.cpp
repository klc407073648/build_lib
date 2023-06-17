#include <iostream>
#include "StiBel/Test/CommonTest.h"
#include "StiBel/XML/XmlUtil.h"

using namespace StiBel::XML;
using StiBel::Test::CommonTest;

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
TEST_F(XmlUtilTest, Given_not_exist_xml_file_When_read_Then_return_false)
{
   TiXmlDocument doc;
   ASSERT_TRUE(!XmlUtil::readXml("no_exist.xml", doc));
}
