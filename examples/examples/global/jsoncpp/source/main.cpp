#include <iostream>
#include "ConfigFile.h"
#include "ConfigLoader.h"

using namespace StiBel;

int main(int args, char *argv[])
{
    ConfigFile configFile("/home/klc/auto_job/build_lib/download/build_lib/examples/examples/global/jsoncpp/conf/normal.json","json数组");
    ConfigLoader loader(configFile);
    loader.printJson(loader.jsonValue());
    return 0;
}