/**
 * @file YamlUtil.h
 * @brief 封装易用的yaml数据处理类,底层实现源码来自于yamlcpp
 * @author klc
 * @date 2020-07-19
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_YAMLUTIL_H__
#define __STIBEL_YAMLUTIL_H__

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

//namespace StiBel {
//namespace YAML {

class YamlUtil
{
public:
    static void printYaml(const YAML::Node &node);
    static YAML::Node readYaml(const std::string &filename);
    static bool write2Yaml(const std::string &fileName, const YAML::Node &node);
};
//} // namespace StiBel
//} // namespace YAML

#endif //__STIBEL_YAMLUTIL_H__
