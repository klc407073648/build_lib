#include <iostream>
#include "JsonUtil.h"
#include "StiBel/Util.h"

std::string normalPath = "/../../../examples/3partlib/jsoncpp/conf/normal.json";
std::string arrayPath = "/../../../examples/3partlib/jsoncpp/conf/array.json";

int main(int args, char *argv[])
{
    std::string str = "{\"uploadid\": \"teststr\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";
    std::cout << str << std::endl;
    std::cout << JsonUtil::isValid(str) << std::endl;
    std::cout << JsonUtil::getInt(str, "code") << std::endl;
    std::cout << JsonUtil::getStr(str, "uploadid") << std::endl;

    std::string jsonStr;
    std::string newStr;
    std::cout << "-----Set func test---------" << std::endl;
    JsonUtil::setStr(jsonStr, "nam", "Jason");
    JsonUtil::setInt(jsonStr, "num", 1024);
    JsonUtil::setObj(newStr, "json", jsonStr);

    std::vector<std::string> testArray;
    testArray.emplace_back("1");
    testArray.emplace_back("2");
    testArray.emplace_back("3");
    testArray.emplace_back("4");
    testArray.emplace_back("5");

    JsonUtil::setArray(newStr, "array", testArray);
    JsonUtil::setStr(newStr, "strKey", "xxx");
    JsonUtil::setInt(newStr, "intKey", 102);
    std::cout << newStr << std::endl;

    // get func test
    std::cout << "------Get func test---------" << std::endl;
    std::cout << JsonUtil::getInt(newStr, "intKey") << std::endl;
    std::cout << JsonUtil::getStr(newStr, "strKey") << std::endl;
    std::cout << JsonUtil::getObj(newStr, "json") << std::endl;
    std::vector<std::string> testGetArray;
    testGetArray = JsonUtil::getArray(newStr, "array");
    for (auto testStr : testGetArray)
    {
        std::cout << testStr << std::endl;
    }

    std::cout << "------New test---------" << std::endl;

    std::string szJson = "{ \"posts\": [{\"title\": \"hello world\",\"author\": \"kkkk\",\"id\": 2},{\"title\": \"hello ld\",\"author\": \"k\",\"id\": 3}],\"test\": \"1\",\"weatherinfo\":{\"city\":\"北京\", \"cityid\" : \"101010100\", \"temp\" : \"18\", \"WD\" : \"东南风\", \"WS\" : \"1级\", \"SD\" : \"17 % \", \"WSE\" : \"1\", \"time\" : \"17:05\", \"isRadar\" : \"1\", \"Radar\" : \"JC_RADAR_AZ9010_JB\", \"njd\" : \"这是什么\", \"qy\" : \"1011\", \"rain\" : \"0\"} }";

    // 解析json数据
    Json::Reader reader;
    Json::Value value;
    if (!reader.parse(szJson, value))
    {
        return 0;
    }

    // 遍历键值
    JsonUtil::printJson(value);

    std::cout << "------File func test---------" << std::endl;
    std::string curPath = StiBel::ShellUtil::execShellPipe("pwd");

    // 查找换行符的位置
    int pos = curPath.find_last_of('\n');

    // 如果找到了换行符
    if (pos != std::string::npos)
    {
        curPath.erase(pos, 1); // 在换行符的位置删除一个字符，即删除换行符
    }

    normalPath = curPath + normalPath;
    arrayPath = curPath + arrayPath;
    std::cout << "normalPath: " << normalPath << std::endl;
    std::cout << "arrayPath: " << arrayPath << std::endl;

    // 读取Json文件里的内容
    JsonUtil::readStringFromJson(normalPath);
    // 读取Json文件里的内容(数组格式)
    JsonUtil::readArrayStringFromJson(arrayPath);

    // 写入json文件
    std::string writeStr = "{\"name\": \"kkk\",\"num\": 123456,\"msg\": \"Hello World\",\"files\": \"NULL\"}";
    std::cout << "writeString2JsonFile result:" << JsonUtil::writeString2JsonFile("write.json", writeStr) << std::endl;

    return 0;
}