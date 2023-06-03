#include "CommonTest.h"
#include "StiBel/Common/Config/ConfigFile.h"
#include "StiBel/Common/Config/ConfigLoader.h"
#include "StiBel/Util/Util.h"

using namespace StiBel::Common::Config;
using namespace StiBel::Util;

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
    //enable_print();//TODO
    std::string jsonPath = rootPath + "normal.json";
    ConfigFile configFile(jsonPath, "json数组");
    ConfigLoader loader(configFile);
    loader.printJson(loader.jsonValue());
}

/* 测试xml文件加载 */
TEST_F(ConfigLoaderTest, Given_xml_file_When_load_Then_success_parse_content)
{
    std::string xmlPath = rootPath + "school.xml";
    ConfigFile configFile(xmlPath, "school数据");
    ConfigLoader loader(configFile);
    TiXmlElement *rootElement = (loader.xmlValue()).RootElement();
    loader.printXml(rootElement);
}

/* 测试yaml文件加载 */
TEST_F(ConfigLoaderTest, Given_yaml_file_When_load_Then_success_parse_content)
{
    std::string yamltPath = rootPath + "config.yml";
    ConfigFile configFile(yamltPath, "confg1数据");
    ConfigLoader loader(configFile);
    loader.printYaml(loader.yamlValue());
}

/* 测试json原生数据加载 */
TEST_F(ConfigLoaderTest, Given_json_value_When_load_Then_success_parse_content)
{
    Json::Value root;
    root["id"] = "1001";
    root["name"] = "Jason";
    root["class"] = "math";
    root["age"] = 27;
    // root["hoppy"].append("music");
    // root["hoppy"].append("book");
    // root["hoppy"].append("swimming");

    ConfigLoader loader(root);
    loader.printJson(loader.jsonValue());
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

    TiXmlElement *stu2Element = new TiXmlElement("Student");
    stu2Element->SetAttribute("name", "gsc");
    stu2Element->SetAttribute("number", "1002");
    TiXmlElement *stu2GradeElement = new TiXmlElement("grade");
    stu2GradeElement->LinkEndChild(new TiXmlText("95"));
    TiXmlElement *stu2AddressElement = new TiXmlElement("address");
    stu2AddressElement->LinkEndChild(new TiXmlText("China"));
    stu2Element->LinkEndChild(stu2GradeElement);
    stu2Element->LinkEndChild(stu2AddressElement);

    TiXmlElement *stu3Element = new TiXmlElement("Student");
    stu3Element->SetAttribute("name", "cf");
    stu3Element->SetAttribute("number", "1003");
    TiXmlElement *stu3GradeElement = new TiXmlElement("grade");
    stu3GradeElement->LinkEndChild(new TiXmlText("99"));
    TiXmlElement *stu3AddressElement = new TiXmlElement("address");
    stu3AddressElement->LinkEndChild(new TiXmlText("China"));
    stu3Element->LinkEndChild(stu3GradeElement);
    stu3Element->LinkEndChild(stu3AddressElement);

    TiXmlElement *stu4Element = new TiXmlElement("Student");
    stu4Element->SetAttribute("name", "lz");
    stu4Element->SetAttribute("number", "1004");
    TiXmlElement *stu4GradeElement = new TiXmlElement("grade");
    stu4GradeElement->LinkEndChild(new TiXmlText("97"));
    TiXmlElement *stu4AddressElement = new TiXmlElement("address");
    stu4AddressElement->LinkEndChild(new TiXmlText("China"));
    stu4Element->LinkEndChild(stu4GradeElement);
    stu4Element->LinkEndChild(stu4AddressElement);

    classElement1->LinkEndChild(stu1Element);
    classElement1->LinkEndChild(stu2Element);

    classElement2->LinkEndChild(stu3Element);
    classElement2->LinkEndChild(stu4Element);

    schoolElement->LinkEndChild(classElement1);
    schoolElement->LinkEndChild(classElement2);

    doc.LinkEndChild(decl);
    doc.LinkEndChild(schoolElement);

    ConfigLoader loader(doc);
    TiXmlElement *rootElement = (loader.xmlValue()).RootElement();
    loader.printXml(rootElement);
}

/* 测试yaml文件加载 */
TEST_F(ConfigLoaderTest, Given_yaml_value_When_load_Then_success_parse_content)
{
    YAML::Node root;
    root["key"] = "value";
    root["number"] = 255;
    root["seq"].push_back("first element");
    root["seq"].push_back("second element");

    ConfigLoader loader(root);
    loader.printYaml(loader.yamlValue());
}
