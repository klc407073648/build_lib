#include <iostream>
#include "StiBel/Test/CommonTest.h"
#include "StiBel/YAML/YamlUtil.h"

//using namespace StiBel::YAML;
using StiBel::Test::CommonTest;

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

TEST_F(YamlUtilTest, Given_file_name_and_node_When_write_Then_write_fail)
{
    YAML::Node node;
    ASSERT_TRUE(!YamlUtil::write2Yaml("file.yml",node));
}