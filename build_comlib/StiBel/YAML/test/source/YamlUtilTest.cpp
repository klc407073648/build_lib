#include <iostream>
#include "CommonTest.h"
#include "StiBel/YAML/YamlUtil.h"

//using namespace StiBel::YAML;

/* YamlUtilTest */
class YamlUtilTest : public CommonTest
{

protected:
    YamlUtilTest()
    {
    }

    ~YamlUtilTest()
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

/* YamlUtilTest */

/* 测试json字符串读取 */
TEST_F(YamlUtilTest, Given_json_str_When_get_Then_success_parse_content)
{
    YAML::Node node;
    YamlUtil::printYaml(node);
}