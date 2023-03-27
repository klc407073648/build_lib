#include "yamlUtil.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cassert>
#include <string.h>
#include <yaml-cpp/yaml.h>
#include "StiBel/Util.h"

using namespace std;

std::string rootPath = "/../../../examples/3partlib/yamlcpp/conf/";

std::string curPath;

// 解析特定文件内容
void parseFileContent()
{
    YAML::Node config = YAML::LoadFile(curPath + rootPath + "config2.yml");

    cout << "Node type " << config.Type() << endl;
    cout << "skills type " << config["skills"].Type() << endl;

    cout << "name:" << config["name"].as<string>() << endl;
    cout << "sex:" << config["sex"].as<string>() << endl;
    cout << "age:" << config["age"].as<int>() << endl;

    cout << "skills c++:" << config["skills"]["c++"].as<int>() << endl;
    cout << "skills java:" << config["skills"]["java"].as<int>() << endl;
    cout << "skills android:" << config["skills"]["android"].as<int>() << endl;
    cout << "skills python:" << config["skills"]["python"].as<int>() << endl;

    for (YAML::const_iterator it = config["skills"].begin(); it != config["skills"].end(); ++it)
    {
        cout << it->first.as<string>() << ":" << it->second.as<int>() << endl;
    }
}

void writeFile()
{
    // node的增改查删
    YAML::Node node;
    assert(node.IsNull()); // 初始化的节点是Null类型
    node["key"] = "value"; // 当你给它赋值键值对，它转变为Map类型
    // node.force_insert("key", "value");//这个操作和上面等价，但是它不会检查是否存在"key"键，不推荐使用
    if (node["mascot"])
        std::cout << node["mascot"].as<std::string>() << "\n"; // 单纯的查询操作不会增加一个key，当然上面的if不会执行

    node["number"] = 255;
    assert(node.IsMap()); // node是一个Map
    node["seq"].push_back("first element");
    node["seq"].push_back("second element"); // node的seq下是Sequence类型，有两个参数

    YAML::Node node_2;
    node_2.push_back("first item"); // 如果你不给node_2键值对，它是一个sequence类型
    node_2.push_back("second_item");
    node_2.push_back("third_item");
    std::vector<int> v = {1, 3, 5, 7, 9}; // 给node_2插入了一个Sequence
    node_2.push_back(v);
    assert(node_2.IsSequence()); // 当然，node_2仍然是一个Sequence

    assert(node_2[0].as<std::string>() == "first item");
    // 对于Sequence类型，你可以使用它的下标来访问
    // 注意这里as<T>是一个模板转换，node_2[0]的type是NodeType::Scalar
    auto it = node_2.begin();
    for (; it != node_2.end(); it++)
        std::cout << *(it) << std::endl;
    // 当然，你也可以用迭代器来访问
    // 他们的类型分别是NodeType::Scalar，NodeType::Scalar，NodeType::Scalar，NodeType::Sequence
    // 取值时记得使用as进行模板转换
    node_2["key"] = "value";
    assert(node_2.IsMap());                                                        // 一旦node_2接收到键值对，它转变为Map类型
    assert(node_2[0].as<std::string>() == "first item");                           // 此时，Sequence时的下标变为它的key值
    node["node_2"] = node_2;                                                       // 将node_2作为node的一个子项
    node["pointer_to_first_element"] = node["seq"][0];                             // 你也可以给已有的node设置一个别名，类似于一个指针
    assert(node["pointer_to_first_element"].as<std::string>() == "first element"); // 你可以通过这个指针访问那个node

    node.remove(node["seq"][0]);             // 通过指定一个node来删除它
    node.remove("pointer_to_first_element"); // 通过指定key来删除它

    // 写入文件
    std::string writefile = "write.yml";
    yamlUtil::write2Yaml(writefile, node);
}

int main(int argc, char **argv)
{
    curPath = StiBel::ShellUtil::execShellPipe("pwd");

    // 查找换行符的位置
    int pos = curPath.find_last_of('\n');

    // 如果找到了换行符
    if (pos != std::string::npos)
    {
        curPath.erase(pos, 1); // 在换行符的位置删除一个字符，即删除换行符
    }

    cout << "读取指定文件内容" << endl;
    std::string fileName = curPath + rootPath + "config1.yml";
    cout << "fileName:" << fileName << endl;
    YAML::Node node = yamlUtil::readYaml(fileName);
    yamlUtil::printYaml(node);

    std::cout << "解析特定文件内容" << std::endl;
    parseFileContent();

    std::cout << "写文件内容" << std::endl;
    writeFile();
    return 0;
}
