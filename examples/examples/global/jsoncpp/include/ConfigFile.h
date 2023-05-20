/**
 * @file ConfigFile.h
 * @brief 配置基础类
 * @author klc
 * @date 2023-05-19
 * @copyright Copyright (c) 2023年 klc
 */

#ifndef __STIBEL_CONFIGFILE_H__
#define __STIBEL_CONFIGFILE_H__

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

namespace StiBel
{

  // 文件类型
  enum FileType
  {
    NULL_TYPE = 0,
    JSON_TYPE,
    XML_TYPE,
    YAML_TYPE,
    EXCEL_XLSX_TYPE,
    EXCEL_XLS_TYPE,
    EXCEL_CSV_TYPE,
  };

  /* 配置基础类 */
  class ConfigFile
  {
  public:
    ConfigFile() {}
    /**
     * @brief 构造函数
     *
     * @param name 配置文件名称,例如mysql.yaml
     * @param description  配置描述，例如记录MySQL的相关参数
     */
    ConfigFile(const std::string &name, const std::string &description = "");

    /**
     * @brief 返回配置名称
     */
    const std::string &getName() const { return _name; }

    /**
     * @brief 返回配置描述
     */
    const std::string &getDescription() const { return _desc; }

    /**
     * @brief 返回文件类型
     */
    const FileType &getFileType() const { return _fileType; }

  private:
    std::string _name;                                             // 配置名称
    std::string _desc;                                             // 配置描述
    FileType _fileType;                                            // 加载文件类型
    static std::unordered_map<std::string, FileType> _fileTypeMap; // 文件类型map
  };

} // namespace drogon

#endif //__STIBEL_CONFIGFILE_H__