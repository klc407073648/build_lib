#include "yamlUtil.h"
#include <iostream>
#include <fstream>

using namespace std;

void yamlUtil::printYaml(const YAML::Node &node)
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
                cout << (it->first).as<string>() << ':' << endl;
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

YAML::Node yamlUtil::readYaml(const std::string &filename)
{
    YAML::Node config;

    try
    {
        config = YAML::LoadFile(filename);
    }
    catch (std::exception &e)
    {
        std::cout << "error loading file, yaml file error or not exist." << std::endl;
    }

    return config;
}

static bool yamlUtil::write2Yaml(const std::string &fileName, const YAML::Node &node)
{
    try
    {
        if (node.IsNull())
        {
            return false;
        }

        std::ofstream ofs;
        ofs.open(fileName);
        if (ofs.fail())
        {
            std::cout << "[write2Yaml] open " << fileName << " fail." << std::endl;
            return false;
        }

        ofs << node << std::endl;
        ofs.close();
    }
    catch (std::exception &e)
    {
        std::cout << "[writeString2JsonFile] err:" << e.what() << std::endl;
        return false;
    }

    return true;
}