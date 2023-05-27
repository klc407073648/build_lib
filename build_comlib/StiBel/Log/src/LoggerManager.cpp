#include"StiBel/Log/LoggerManager.h"
#include"StiBel/Common/Util.h"
#include<algorithm>
#include<log4cpp/PatternLayout.hh>
#include<log4cpp/OstreamAppender.hh>
#include<log4cpp/FileAppender.hh>
#include<log4cpp/RollingFileAppender.hh>
#include<log4cpp/Priority.hh>
#include<log4cpp/PropertyConfigurator.hh>

using namespace std;

namespace StiBel {
namespace Log {

string LoggerManager::_confFileName="./conf/log4cpp.conf";
bool LoggerManager::_ready=false;

LoggerManager::LoggerManager():
_instanceName("root")
{
   init();
}

LoggerManager::LoggerManager(const string& name):
_instanceName(name)
{
	init();
}

LoggerManager::~LoggerManager() 
{
    _root->info("LoggerManager destroy, name is %s",_instanceName.c_str());
    _root->shutdown();
}

void LoggerManager::init()
{
    _root=&log4cpp::Category::getRoot();
	
	if (_instanceName=="root")
	{
        _instance=NULL;
		_root->info("LoggerManager created, name is %s",_instanceName.c_str());
	}
	else
	{
        _instance=&log4cpp::Category::getInstance(_instanceName);
		_instance->info("LoggerManager created, name is %s",_instanceName.c_str());
	}
}

void LoggerManager::start(const string& name)
{
    _ready=true;
    setConfFileName(name);
    readConfFromFile();
}

void LoggerManager::setConfFileName(const string& name)
{
    _confFileName=name;
}

const string& LoggerManager::getConfFileName() const
{
    return _confFileName;
}

void LoggerManager::readConfFromFile()
{
    try
    {
        log4cpp::PropertyConfigurator::configure(_confFileName);
    }
    catch (log4cpp::ConfigureFailure& f) 
    {
        std::cout << "Configure Problem: " << f.what() <<std::endl;
    }

    std::cout << "readConfFromFile success"<<std::endl;
    //_instance->info("readConfFromFile success");
}

void LoggerManager::setRootPriority(Priority& priority) {
    _priority=priority;
    switch (_priority) {
        case (ERROR):
            _root->setPriority(log4cpp::Priority::ERROR);
            break;
        case (WARN):
            _root->setPriority(log4cpp::Priority::WARN);
            break;
        case (INFO):
            _root->setPriority(log4cpp::Priority::INFO);
            break;
        case (DEBUG):
            _root->setPriority(log4cpp::Priority::DEBUG);
            break;
        default:
            _root->setPriority(log4cpp::Priority::DEBUG);
            break;    
    }
}

const int&  LoggerManager::getPriority() const
{
    return _priority;
}

const string& LoggerManager::getInstanceName()  const
{
    return _instanceName;
}

log4cpp::Category* LoggerManager::getCategory() const
{
	return _instance;
}

const bool& LoggerManager::idReady() const
{
    return _ready;
}


} }  // namespace StiBel::Log