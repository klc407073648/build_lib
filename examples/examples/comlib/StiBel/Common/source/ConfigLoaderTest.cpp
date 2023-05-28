#include <iostream>
#include "StiBel/Common/ConfigFile.h"
#include "StiBel/Common/ConfigLoader.h"
#include "StiBel/Common/Util.h"

using namespace StiBel::Common;

// TODO改成googletest
void testFileLoad()
{
    std::string curPath = StiBel::Common::ShellUtil::execShellPipeEndWithLineFeed("pwd");
    std::string rootPath = curPath + "/../../../examples/comlib/StiBel/Common/conf/";
    std::string jsonPath = rootPath + "normal.json";
    std::string xmlPath = rootPath + "school.xml";
    std::string yamltPath = rootPath + "config1.yml";

    ConfigFile configFile(jsonPath, "json数组");
    ConfigLoader loader(configFile);
    loader.printJson(loader.jsonValue());

    ConfigFile configFile1(xmlPath, "school数据");
    ConfigLoader loader1(configFile1);
    TiXmlElement *rootElement = (loader1.xmlValue()).RootElement();
    loader1.printXml(rootElement);

    ConfigFile configFile2(yamltPath, "confg1数据");
    ConfigLoader loader2(configFile2);
    loader2.printYaml(loader2.yamlValue());
}

void testOriginJsonData()
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

void testOriginXmlData()
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

void testOriginYamlData()
{
    YAML::Node root;
    root["key"] = "value";
    root["number"] = 255;
    root["seq"].push_back("first element");
    root["seq"].push_back("second element");

    ConfigLoader loader(root);
    loader.printYaml(loader.yamlValue());
}

int main(int args, char *argv[])
{
    std::cout << "---------------testFileLoad------------------" << std::endl;
    testFileLoad();
    std::cout << "---------------testOriginJsonData------------------" << std::endl;
    testOriginJsonData();
    std::cout << "---------------testOriginXmlData------------------" << std::endl;
    testOriginXmlData();
    std::cout << "---------------testOriginYamlData------------------" << std::endl;
    testOriginYamlData();
    return 0;
}