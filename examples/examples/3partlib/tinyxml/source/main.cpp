#include "tinyxmlUtil.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include "StiBel/Common/Util.h"

using namespace std;
string curPath;
string myPrintPath = "/../../../examples/3partlib/tinyxml/conf/school.xml";
string myWritePath = "/../../../examples/3partlib/tinyxml/conf/school-write.xml";
string finalPath;

void printSchoolXml()
{
	curPath = StiBel::ShellUtil::execShellPipeEndWithLineFeed("pwd");

	finalPath = curPath + myPrintPath;
	tinyxmlUtil::printXml(finalPath);
}

void readSchoolXml()
{
	TiXmlDocument doc;

	curPath = StiBel::ShellUtil::execShellPipeEndWithLineFeed("pwd");

	finalPath = curPath + myPrintPath;
	if (!tinyxmlUtil::readXml(finalPath, doc))
	{
		return;
	}

	// School元素
	TiXmlElement *rootElement = doc.RootElement();
	// Class元素
	TiXmlElement *classElement = rootElement->FirstChildElement();

	// 循环遍历所有class
	for (; classElement != NULL; classElement = classElement->NextSiblingElement())
	{
		// Students
		TiXmlElement *studentElement = classElement->FirstChildElement();

		for (; studentElement != NULL; studentElement = studentElement->NextSiblingElement())
		{
			// 获得student的name属性
			TiXmlAttribute *attributeOfStudent = studentElement->FirstAttribute();

			for (; attributeOfStudent != NULL; attributeOfStudent = attributeOfStudent->Next())
			{
				cout << attributeOfStudent->Name() << " : " << attributeOfStudent->Value() << endl;
			}

			TiXmlElement *studentContactElement = studentElement->FirstChildElement();

			for (; studentContactElement != NULL; studentContactElement = studentContactElement->NextSiblingElement())
			{
				string contactType = studentContactElement->Value();
				string contactValue = studentContactElement->GetText();
				cout << contactType << " : " << contactValue << endl;
			}
		}
	}
}

void writeSchoolXml()
{
	using namespace std;

	curPath = StiBel::ShellUtil::execShellPipeEndWithLineFeed("pwd");

	finalPath = curPath + myWritePath;

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

	if (!tinyxmlUtil::write2Xml(finalPath, doc))
	{
		return;
	}
}

int main()
{
	printSchoolXml();
	readSchoolXml();
	writeSchoolXml();

	return 0;
}