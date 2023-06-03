/**
 * @file ConfigLoader.h
 * @brief 配置加载类，用于加载各类配置文件包括json、xml、yaml、excel等
 * @author klc
 * @date 2023-05-19
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_CONFIGLOADER_H__
#define __STIBEL_CONFIGLOADER_H__

#include "json/json.h"
#include "tinyxml.h"
#include "yaml-cpp/yaml.h"
#include "StiBel/Common/Config/ConfigFile.h"
#include <map>
#include <functional>
#include <string>

namespace StiBel {
namespace Common {
namespace Config {

  // TODO https://blog.csdn.net/yao_hou/article/details/123292920
  // D:\CODE\klc\StiBel\myprj\fastcgiApp\include
  //  配置函数宏定义

  /* 配置加载类 */
  class ConfigLoader
  {

    // 声明函数指针，作为map的value类型
    typedef void (ConfigLoader::*handlerConfigFunc)(const std::string &);
    typedef std::map<FileType, handlerConfigFunc> configFuncMap;
    using ConfigLoaderPtr = std::shared_ptr<ConfigLoader>;

  public:
    /**
     * @brief 构造函数，基于Config类加载内容
     *
     * @param config
     */
    explicit ConfigLoader(const ConfigFile &config);
    explicit ConfigLoader(ConfigFile &&config);

    /**
     * @brief 构造函数，根据实际数据类型构造
     *
     * @param data
     */
    explicit ConfigLoader(const Json::Value &data);
    explicit ConfigLoader(Json::Value &&data);
    explicit ConfigLoader(const TiXmlDocument &data);
    explicit ConfigLoader(TiXmlDocument &&data);
    explicit ConfigLoader(const YAML::Node &data);
    explicit ConfigLoader(YAML::Node &&data);

    ~ConfigLoader();

  public:
    /* 因为是配置加载类，不应该提供解析数据的修改接口，即通过文件加载或原始数据类型加载后，不能直接修改数据，考虑拷贝构造和赋值构造吗？？？*/
    const Json::Value &jsonValue() const { return _jsonValue; }

    const TiXmlDocument &xmlValue() const { return _xmlValue; }

    const YAML::Node &yamlValue() const { return _yamlValue; }

    const ConfigFile &config() const { return _config; }

    // 加载文件配置
    void load();

    // 根据实际文件变化后重新加载
    void reload();

    // for test
    void printJson(const Json::Value &data);
    void printXml(const TiXmlElement *element);
    void printYaml(const YAML::Node &node);

  private:
    /* 加载各类配置文件的具体实现 */
    void loadJsonConfig(const std::string &name);
    void loadXmlConfig(const std::string &name);
    void loadYamlConfig(const std::string &name);
    void loadExcelXlsxConfig(const std::string &name);
    void loadExcelXlsConfig(const std::string &name);
    void loadExcelCsvConfig(const std::string &name);

  private:
    /**
     * @brief 初始化 configFuncMap，仅ConfigFile的构造函数需要，其他函数默认以对应数据类型进行构造
     */
    void initMap();

    /**
     * @brief 根据类型调用对应文件类型为type，且名称为name的文件内容
     *
     * @param type
     * @param name
     */
    void callFunc(FileType type, const std::string &name);

  private:
    ConfigFile _config;
    Json::Value _jsonValue;
    TiXmlDocument _xmlValue;
    YAML::Node _yamlValue;
    FileType _loadFileType;       // 加载文件类型
    configFuncMap _configFuncMap; // 配置函数映射
    //  读写锁
  };
} // namespace StiBel
} // namespace Common
} // namespace Config

#endif //__STIBEL_CONFIGLOADER_H__