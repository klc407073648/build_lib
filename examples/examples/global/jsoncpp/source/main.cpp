#include <iostream>
#include "ConfigFile.h"
#include "ConfigLoader.h"

using namespace StiBel;

int main(int args, char *argv[])
{
    ConfigFile configFile("/home/klc/auto_job/build_lib_test/build_lib/examples/examples/global/jsoncpp/conf/normal.json","json数组");
    ConfigLoader loader(configFile);
    loader.printJson(loader.jsonValue());


    ConfigFile configFile1("/home/klc/auto_job/build_lib_test/build_lib/examples/examples/global/jsoncpp/conf/school.xml","school数据");
    ConfigLoader loader1(configFile1);
	TiXmlElement *rootElement = (loader1.xmlValue()).RootElement();
    loader1.printXml(rootElement);

    ConfigFile configFile2("/home/klc/auto_job/build_lib_test/build_lib/examples/examples/global/jsoncpp/conf/config1.yml","confg1数据");
    ConfigLoader loader2(configFile2);
    loader2.printYaml(loader2.yamlValue());

    return 0;
}