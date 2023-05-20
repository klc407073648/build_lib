#include "ConfigLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

namespace StiBel
{
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
        callFunc(_config.getFileType(), _config.getName());
    }

    ConfigLoader::ConfigLoader(ConfigFile &&config)
        : _config(std::move(config))
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(const Json::Value &data) : _jsonValue(data)
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(Json::Value &&data) : _jsonValue(std::move(data))
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(const TiXmlDocument &data) : _xmlValue(data)
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(TiXmlDocument &&data) : _xmlValue(std::move(data))
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(const YAML::Node &data) : _yamlValue(data)
    {
        initMap();
    }

    ConfigLoader::ConfigLoader(YAML::Node &&data) : _yamlValue(std::move(data))
    {
        initMap();
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
        }

        _jsonValue = value;
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

    void ConfigLoader::loadXmlConfig(const std::string &name)
    {
    }

    void ConfigLoader::loadYamlConfig(const std::string &name)
    {
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
}
