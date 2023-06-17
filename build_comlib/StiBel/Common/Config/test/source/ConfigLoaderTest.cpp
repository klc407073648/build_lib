#include "StiBel/Test/CommonTest.h"
#include "StiBel/Common/Config/ConfigFile.h"
#include "StiBel/Common/Config/ConfigLoader.h"
#include "StiBel/Util/Util.h"

using namespace StiBel::Common::Config;
using namespace StiBel::Util;
using StiBel::Test::CommonTest;

/* ConfigLoaderTest */
class ConfigLoaderTest : public CommonTest
{

protected:
    ConfigLoaderTest()
    {
        curPath = StiBel::Util::ShellUtil::execShellPipeEndWithLineFeed("pwd");
        rootPath = curPath + "/../../../../../build_comlib/StiBel/Common/Config/test/conf/";
    }

    ~ConfigLoaderTest()
    {
    }

    void SetUp()
    {
    }

    void TearDown()
    {
    }

public:
    std::string curPath;
    std::string rootPath;
};

/* ConfigLoaderTest */

/* 测试json文件加载 */
TEST_F(ConfigLoaderTest, Given_json_file_When_load_Then_success_parse_content)
{
    // enable_printf();//TODO
    std::string jsonPath = rootPath + "normal.json";
    ConfigFile configFile(jsonPath, "json数组");
    ConfigLoader loader(configFile);

    const Json::Value &value = loader.jsonValue();
    // loader.printJson(value);

    EXPECT_EQ("testuser", value["userAccount"].asString());
    EXPECT_EQ("12345678", value["userPassword"].asString());
    EXPECT_EQ("12345678", value["checkPassword"].asString());
}

/* 测试xml文件加载 */
TEST_F(ConfigLoaderTest, Given_xml_file_When_load_Then_success_parse_content)
{
    // 校验Student name="Jason" 和 里面的 <grade>98</grade>
    //enable_printf();
    std::string xmlPath = rootPath + "school.xml";
    ConfigFile configFile(xmlPath, "school数据");
    ConfigLoader loader(configFile);
    TiXmlElement *rootElement = (loader.xmlValue()).RootElement();

    TiXmlElement *classElement = rootElement->FirstChildElement();
    TiXmlElement *studentElement = classElement->FirstChildElement();

    TiXmlAttribute *attributeOfStudent = studentElement->FirstAttribute();

    // TODO EXPECT_STREQ EXPECT_EQ 区别，有的比较地址
    printf("attributeOfStudent  %s:%s", attributeOfStudent->Name(), attributeOfStudent->Value());

    EXPECT_EQ("name", attributeOfStudent->Name());
    EXPECT_STREQ("Jason", attributeOfStudent->Value());

    TiXmlElement *studentContactElement = studentElement->FirstChildElement();
    printf("studentContactElement %s:%s", studentContactElement->Value(), studentContactElement->GetText());
    EXPECT_STREQ("grade", studentContactElement->Value());
    EXPECT_STREQ("98", studentContactElement->GetText());

	//disable_printf();
    // loader.printXml(rootElement);
}

/* 测试yaml文件加载 */
TEST_F(ConfigLoaderTest, Given_yaml_file_When_load_Then_success_parse_content)
{
    std::string yamltPath = rootPath + "config.yml";
    ConfigFile configFile(yamltPath, "confg数据");
    ConfigLoader loader(configFile);

    const YAML::Node &value = loader.yamlValue();
    // loader.printYaml(loader.yamlValue());

    EXPECT_EQ("Jason", value["name"].as<std::string>());
    EXPECT_EQ("male", value["sex"].as<std::string>());
    EXPECT_EQ(18, value["age"].as<int>());
    EXPECT_EQ(1001, value["ID"].as<int>());
    EXPECT_EQ(94.25, value["average"].as<float>());
}

/* 测试json原生数据加载 */
TEST_F(ConfigLoaderTest, Given_json_value_When_load_Then_success_parse_content)
{
    Json::Value value;
    value["id"] = 1001;
    value["name"] = "Jason";
    value["class"] = "math";
    value["age"] = 27;

    ConfigLoader loader(value);
    // loader.printJson(loader.jsonValue());

    EXPECT_EQ(1001, value["id"].asInt());
    EXPECT_EQ("Jason", value["name"].asString());
    EXPECT_EQ("math", value["class"].asString());
    EXPECT_EQ(27, value["age"].asInt());
}

/* 测试xml文件加载 */
TEST_F(ConfigLoaderTest, Given_xml_value_When_load_Then_success_parse_content)
{
    TiXmlDocument doc;
    TiXmlDeclaration *decl = new TiXmlDeclaration("1.0", "", "");
    TiXmlElement *schoolElement = new TiXmlElement("School");
    TiXmlElement *classElement1 = new TiXmlElement("Class");
    classElement1->SetAttribute("name", "C++");

    TiXmlElement *classElement2 = new TiXmlElement("Class");
    classElement2->SetAttribute("name", "Java");

    TiXmlElement *stu1Element = new TiXmlElement("Student");
    stu1Element->SetAttribute("name", "klc");
    stu1Element->SetAttribute("number", "1001");
    TiXmlElement *stu1GradeElement = new TiXmlElement("grade");
    stu1GradeElement->LinkEndChild(new TiXmlText("100"));
    TiXmlElement *stu1AddressElement = new TiXmlElement("address");
    stu1AddressElement->LinkEndChild(new TiXmlText("China"));
    stu1Element->LinkEndChild(stu1GradeElement);
    stu1Element->LinkEndChild(stu1AddressElement);

    doc.LinkEndChild(decl);
    doc.LinkEndChild(schoolElement);

    ConfigLoader loader(doc);
    TiXmlElement *rootElement = (loader.xmlValue()).RootElement();
    loader.printXml(rootElement);
}

/* 测试yaml文件加载 */
TEST_F(ConfigLoaderTest, Given_yaml_value_When_load_Then_success_parse_content)
{
    YAML::Node value;
    value["key"] = "value";
    value["number"] = 255;
    value["seq"].push_back("first element");
    value["seq"].push_back("second element");

    ConfigLoader loader(value);
    // loader.printYaml(loader.yamlValue());

    EXPECT_EQ("value", value["key"].as<std::string>());
    EXPECT_EQ(255, value["number"].as<int>());
}
