#include "StiBel/Common/ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

namespace StiBel {
namespace Common {

    void ConfigLoader::initMap()
    {
        _configFuncMap = {
            {JSON_TYPE, &ConfigLoader::loadJsonConfig},
            {XML_TYPE, &ConfigLoader::loadXmlConfig},
            {YAML_TYPE, &ConfigLoader::loadYamlConfig},
            {EXCEL_XLSX_TYPE, &ConfigLoader::loadExcelXlsxConfig},
            {EXCEL_XLS_TYPE, &ConfigLoader::loadExcelXlsConfig},
            {EXCEL_CSV_TYPE, &ConfigLoader::loadExcelCsvConfig},
        };
    }

    void ConfigLoader::callFunc(FileType type, const std::string &name)
    {
        if (_configFuncMap.count(type))
        {
            (this->*_configFuncMap[type])(name);
        }
        else
        {
            std::cout << "configFuncMap not exist " << type << " handlerConfigFunc" << std::endl;
        }
    }

    ConfigLoader::ConfigLoader(const ConfigFile &config) : _config(config)
    {
        initMap();
        _loadFileType = _config.getFileType();
        std::cout << "fileType:" << _loadFileType << ", name:" << _config.getName() << std::endl;
        callFunc(_loadFileType, _config.getName());
    }

    ConfigLoader::ConfigLoader(ConfigFile &&config)
        : _config(std::move(config))
    {
    }

    ConfigLoader::ConfigLoader(const Json::Value &data) : _jsonValue(data)
    {
    }

    ConfigLoader::ConfigLoader(Json::Value &&data) : _jsonValue(std::move(data))
    {
    }

    ConfigLoader::ConfigLoader(const TiXmlDocument &data) : _xmlValue(data)
    {
    }

    ConfigLoader::ConfigLoader(TiXmlDocument &&data) : _xmlValue(std::move(data))
    {
    }

    ConfigLoader::ConfigLoader(const YAML::Node &data) : _yamlValue(data)
    {
    }

    ConfigLoader::ConfigLoader(YAML::Node &&data) : _yamlValue(std::move(data))
    {
    }

    ConfigLoader::~ConfigLoader()
    {
    }

    void ConfigLoader::loadJsonConfig(const std::string &name)
    {
        Json::Reader reader;
        Json::Value value;

        const char *path = name.c_str();
        std::ifstream infile(path);

        if (!reader.parse(infile, value))
        {
            std::cout << "parse " << name << " fail!" << std::endl;
            return;
        }

        _jsonValue = value;
    }

    void ConfigLoader::loadXmlConfig(const std::string &name)
    {
        TiXmlDocument value;

        if (!value.LoadFile(name.c_str()))
        {
            std::cout << "can not parse xml:" << name << std::endl;
            return;
        }

        _xmlValue = value;
    }

    void ConfigLoader::loadYamlConfig(const std::string &name)
    {
        YAML::Node value;

        try
        {
            value = YAML::LoadFile(name);
        }
        catch (std::exception &e)
        {
            std::cout << "can not parse yaml:" << name << std::endl;
            return;
        }

        _yamlValue = value;
    }

    void ConfigLoader::loadExcelXlsxConfig(const std::string &name)
    {
    }

    void ConfigLoader::loadExcelXlsConfig(const std::string &name)
    {
    }

    void ConfigLoader::loadExcelCsvConfig(const std::string &name)
    {
    }

    void ConfigLoader::printJson(const Json::Value &data)
    {
        Json::Value::Members mem = data.getMemberNames();
        for (auto iter = mem.begin(); iter != mem.end(); iter++)
        {
            std::cout << *iter << "\t: ";
            if (data[*iter].type() == Json::objectValue)
            {
                std::cout << std::endl;
                printJson(data[*iter]);
            }
            else if (data[*iter].type() == Json::arrayValue)
            {
                std::cout << std::endl;
                auto cnt = data[*iter].size();
                for (auto i = 0; i < cnt; i++)
                {
                    printJson(data[*iter][i]);
                }
            }
            else if (data[*iter].type() == Json::stringValue)
            {
                std::cout << data[*iter].asString() << std::endl;
            }
            else if (data[*iter].type() == Json::realValue)
            {
                std::cout << data[*iter].asDouble() << std::endl;
            }
            else if (data[*iter].type() == Json::uintValue)
            {
                std::cout << data[*iter].asUInt() << std::endl;
            }
            else
            {
                std::cout << data[*iter].asInt() << std::endl;
            }
        }
        return;
    }

    void ConfigLoader::printXml(const TiXmlElement *element)
    {
        for (TiXmlElement *nodeEle = element->FirstChildElement(); nodeEle; nodeEle = nodeEle->NextSiblingElement())
        {
            TiXmlElement *tempEle = nodeEle;
            if (nodeEle->GetText() != NULL)
            {
                std::string tag = nodeEle->Value();
                std::string content = nodeEle->GetText();
                std::cout << tag << ":" << content << std::endl;
            }

            if (!tempEle->NoChildren())
            {
                printXml(tempEle);
            }
        }
    }

    void ConfigLoader::printYaml(const YAML::Node &node)
    {
        // 获取类型
        for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
        {
            std::string key = it->first.as<std::string>();
            YAML::Node value = it->second;
            switch (value.Type())
            {
            case YAML::NodeType::Scalar:
                std::cout << "Scalar " << key << ":" << value << std::endl;
                break;
            case YAML::NodeType::Sequence:
                std::cout << "Sequence " << key << ":" << std::endl;
                for (size_t i = 0; i < value.size(); i++)
                {
                    std::cout << " " << value[i];
                }
                std::cout << std::endl;
                break;
            case YAML::NodeType::Map:
                std::cout << "Map " << std::endl;
                for (auto it = value.begin(); it != value.end(); ++it)
                {
                    std::cout << (it->first).as<std::string>() << ':' << std::endl;
                    printYaml(it->second);
                }
                break;
            case YAML::NodeType::Null:
                std::cout << "Null: " << key << std::endl;
                break;
            case YAML::NodeType::Undefined:
                std::cout << "Undefined: " << key << std::endl;
                break;
            }
        }
    }
    
} // namespace StiBel
} // namespace Common
