#include "tinyxmlUtil.h"
#include <iostream>
#include <fstream>

using namespace std;

void tinyxmlUtil::printXml(const std::string &filename)
{
    TiXmlDocument doc;
    
    if (doc.LoadFile(filename.c_str()))
    {
        doc.Print();
    }
    else
    {
        std::cout << "can not parse xml conf/school.xml" << std::endl;
    }
}

bool tinyxmlUtil::readXml(const std::string &filename, TiXmlDocument &doc)
{
    if (!doc.LoadFile(filename.c_str()))
    {
        std::cout << "can not parse xml:" << filename << std::endl;
        return false;
    }

    return true;
}

bool tinyxmlUtil::write2Xml(const std::string &fileName, const TiXmlDocument &doc)
{
    try
    {
        doc.SaveFile(fileName.c_str());
    }
    catch (std::exception &e)
    {
        std::cout << "[write2Xml] err:" << e.what() << std::endl;
        return false;
    }

    return true;
}