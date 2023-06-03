#include "StiBel/Common/Config/ConfigFile.h"

namespace StiBel {
namespace Common {
namespace Config {

    std::unordered_map<std::string, FileType> ConfigFile::_fileTypeMap = {
        {".json", JSON_TYPE},
        {".xml", XML_TYPE},
        {".yml", YAML_TYPE},
        {".xlsx", EXCEL_XLSX_TYPE},
        {".xls", EXCEL_XLS_TYPE},
        {".csv", EXCEL_CSV_TYPE},
    };

    ConfigFile::ConfigFile()
    {
    }

    ConfigFile::ConfigFile(const std::string &name, const std::string &description)
        : _name(name), _desc(description)
    {
        // 统一处理配置文件名称转小写,TODO有问题转小写后面读取文件时，路径或文件名小写，读取不到文件
        //std::transform(_name.begin(), _name.end(), _name.begin(), ::tolower);

        // 文件类型，通过配置名称解析得到

        // 文件存在性校验

        // 根据配置文件名称的后缀名，确定文件类型
        int file_suffix_index = _name.find_last_of(".");

        if (file_suffix_index != std::string::npos)
        {
            std::string file_suffix_name = _name.substr(file_suffix_index);
            if (_fileTypeMap.count(file_suffix_name))
            {
                _fileType = _fileTypeMap[file_suffix_name];
                std::cout << _name << " parse success!" << std::endl;
            }
        }
        else
        {
            _fileType = NULL_TYPE;
            std::cout << _name << " parse fail!" << std::endl;
        }
    }

} // namespace StiBel
} // namespace Common
} // namespace Config