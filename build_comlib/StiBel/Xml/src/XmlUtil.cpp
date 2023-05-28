#include "XmlUtil.h"
#include <iostream>
#include <fstream>

using namespace std;

namespace StiBel {
namespace XML {

void XmlUtil::printXml(const std::string &filename)
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

bool XmlUtil::readXml(const std::string &filename, TiXmlDocument &doc)
{
    if (!doc.LoadFile(filename.c_str()))
    {
        std::cout << "can not parse xml:" << filename << std::endl;
        return false;
    }

    return true;
}

bool XmlUtil::write2Xml(const std::string &fileName, const TiXmlDocument &doc)
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

} // namespace StiBel
} // namespace XML