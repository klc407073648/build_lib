/**
 * @file XmlUtil.h
 * @brief 封装易用的json数据处理类,底层实现源码来自于jsoncpp
 * @author klc
 * @date 2020-07-19
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_XMLUTIL_H__
#define __STIBEL_XMLUTIL_H__

#include <string>
#include <vector>
#include <tinyxml.h>

namespace StiBel {
namespace XML {

class XmlUtil
{
public:
    static void printXml(const std::string &filename);
    static bool readXml(const std::string &filename, TiXmlDocument &doc);
    static bool write2Xml(const std::string &fileName, const TiXmlDocument &doc);
};

} // namespace StiBel
} // namespace XML

#endif //__STIBEL_XMLUTIL_H__
