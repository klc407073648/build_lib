/**
 * @file yamlUtil.h
 * @brief 封装易用的json数据处理类,底层实现源码来自于jsoncpp
 * @author klc
 * @date 2020-07-19
 * @copyright Copyright (c) 2020年 klc
 */

#ifndef __STIBEL_yamlUtil_H__
#define __STIBEL_yamlUtil_H__

#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

class yamlUtil
{
public:
    static void printYaml(const YAML::Node &node);
    static YAML::Node readYaml(const std::string &filename);
    static bool write2Yaml(const std::string &fileName, const YAML::Node &node);
};

#endif //__STIBEL_LOGIN_H__
