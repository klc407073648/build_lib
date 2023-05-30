#include <iostream>
#include "CommonTest.h"
#include "StiBel/JSON/JsonUtil.h"

using namespace StiBel::JSON;

/* JsonUtilTest */
class JsonUtilTest : public CommonTest
{

protected:
    JsonUtilTest()
    {
    }

    ~JsonUtilTest()
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

/* JsonUtilTest */

/* 测试json字符串读取 */
TEST_F(JsonUtilTest, Given_json_str_When_get_Then_success_parse_content)
{
    // enable_print();//TODO
    std::string str = "{\"uploadid\": \"teststr\",\"code\": 100,\"msg\": \"hello world\",\"files\": \"test.json\"}";

    ASSERT_TRUE(JsonUtil::isValid(str));
    EXPECT_EQ("teststr", JsonUtil::getStr(str, "uploadid"));
    EXPECT_EQ(100, JsonUtil::getInt(str, "code"));
    EXPECT_EQ("hello world", JsonUtil::getStr(str, "msg"));
    EXPECT_EQ("test.json", JsonUtil::getStr(str, "files"));
}

/* 测试json字符串读入再读出 */
TEST_F(JsonUtilTest, Given_write_json_value_When_read_value_Then_success_parse_content)
{
    // enable_print();//TODO
    std::string jsonStr;
    std::string newStr;
    std::cout << "-----set func test---------" << std::endl;
    JsonUtil::setStr(jsonStr, "aaa", "kkkkkkk");
    JsonUtil::setInt(jsonStr, "num", 1024);
    JsonUtil::setObj(newStr, "json", jsonStr);
    std::vector<std::string> testArray;
    testArray.push_back("1");
    testArray.push_back("2");
    JsonUtil::setArray(newStr, "array", testArray);
    JsonUtil::setStr(newStr, "strKey", "xxx");
    JsonUtil::setInt(newStr, "intKey", 102);
    std::cout << newStr << std::endl;
    // get func test
    std::cout << "------get func test---------" << std::endl;
    std::cout << JsonUtil::getInt(newStr, "intKey") << std::endl;
    std::cout << JsonUtil::getStr(newStr, "strKey") << std::endl;
    std::cout << JsonUtil::getObj(newStr, "json") << std::endl;
    std::vector<std::string> testGetArray;
    testGetArray = JsonUtil::getArray(newStr, "array");
    for (auto testStr : testGetArray)
    {
        std::cout << testStr << std::endl;
    }
}

/* 测试json字符串解析 */
TEST_F(JsonUtilTest, Given_json_str_When_parse_Then_success_parse_content)
{
    // enable_print();//TODO
    std::string szJson = "{ \"posts\": [{\"title\": \"hello world\",\"author\": \"kkkk\",\"id\": 2},{\"title\": \"hello ld\",\"author\": \"k\",\"id\": 3}],\"test\": \"1\",\"weatherinfo\":{\"city\":\"北京\", \"cityid\" : \"101010100\", \"temp\" : \"18\", \"WD\" : \"东南风\", \"WS\" : \"1级\", \"SD\" : \"17 % \", \"WSE\" : \"1\", \"time\" : \"17:05\", \"isRadar\" : \"1\", \"Radar\" : \"JC_RADAR_AZ9010_JB\", \"njd\" : \"这是什么\", \"qy\" : \"1011\", \"rain\" : \"0\"} }";

    // 解析json数据
    Json::Reader reader;
    Json::Value value;
    ASSERT_TRUE(reader.parse(szJson, value));

    // 遍历键值
    JsonUtil::printJson(value);
}