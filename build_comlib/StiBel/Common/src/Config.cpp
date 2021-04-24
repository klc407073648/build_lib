#include "StiBel/Config.h"

namespace StiBel {

Config::Config(const std::string &name, const ParamsMap &conf_map, const std::string &description, const std::string &type)
	: ConfigBase(name, description), _confMap(conf_map), _type(type)
{
}

Config::~Config()
{
}

std::string Config::toString(){
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

std::ostream& Config::dump(std::ostream& os) {
    os << "[Config total=" << _confMap.size() << "]" << std::endl;
    for(auto& i : _confMap) {
        os << "    " << i.first << " :[";
        for(auto& n : i.second) {
            os << "{" << n.first << ":" << n.second << "}";
        }
        os << "]" << std::endl;
    }
    return os;
}

std::map<std::string, std::string> Config::getParams(std::string &name)
{
	std::map<std::string, std::string> tmp;
	if (name != "" && _confMap.find(name) != _confMap.end())
		return _confMap[name];
	else
		return  tmp;
}

/*
std::string Config::toString() 
{
	std::string retStr;
	ParamsMap::iterator iterMap = _confMap.begin();
	for (; iterMap != _confMap.end(); iterMap++)
	{
		retStr.append("{key: " + iterMap->first + " , values: [");
		std::map<std::string, std::string>::iterator iter = (iterMap->second).begin();
		for (; iter != (iterMap->second).end(); iter++)
		{
			retStr.append(iter->first);
			retStr.append(":");
			retStr.append(iter->second);
			retStr.append(",");
		}
		retStr = retStr.substr(0, retStr.length() - 1); //去掉最后一个逗号
		retStr.append("]},");
	}
	return retStr.substr(0, retStr.length() - 1);
}
*/

} //namespace StiBel

