#include "StiBel/Data/Redis/Redis.h"
#include "StiBel/Common/Util.h"

using StiBel::Common::TypeUtil;
using namespace std;

namespace StiBel {
namespace Data {
namespace Redis {


static std::string get_value(const std::map<std::string, std::string>& m
                             ,const std::string& key
                             ,const std::string& def = "") {
    auto it = m.find(key);
    return it == m.end() ? def : it->second;
}

Redis::Redis() {
    
}

Redis::Redis(const std::map<std::string, std::string>& conf) {
    
    std::string tmp = get_value(conf, "host");
    int pos = tmp.find(":");
    m_host = tmp.substr(0, pos);
    m_port = TypeUtil::Atoi(tmp.substr(pos + 1));
    m_passwd = get_value(conf, "passwd");
    m_logEnable = TypeUtil::Atoi(get_value(conf, "log_enable", "1"));
	m_name = get_value(conf, "name");

    tmp = get_value(conf, "timeout","0");
    
    uint64_t v = TypeUtil::Atoi(tmp);

    m_cmdTimeout.tv_sec = v / 1000;
    m_cmdTimeout.tv_usec = v % 1000 * 1000;
	
    cout<<"m_host:"<<m_host<<",m_port:"<<m_port<<",m_passwd:"<<m_passwd<<",m_logEnable:"<<m_logEnable<<endl;
}

bool Redis::reconnect() {
    return redisReconnect(m_context.get());
}

bool Redis::connect() {
    return connect(m_host, m_port,DEFALUT_CONNECT_TIMEOUT);
}

bool Redis::connect(const std::string& ip, int port, uint64_t ms) {
    m_host = ip;
    m_port = port;
    m_connectMs = ms;
    if(m_context) {
        return true;
    }
    timeval tv = {(int)ms / 1000, (int)ms % 1000 * 1000};
    auto c = redisConnectWithTimeout(ip.c_str(), port, tv);
    if(c) {
        //shared_ptr 获得使用计数为1的p的所有权，以及 (可选) 使用 del and/or alloc as deleter and allocator, respectively。
		//m_context获取c的所有权，且析构时使用redisFree
        m_context.reset(c, redisFree);
		
        if(m_cmdTimeout.tv_sec || m_cmdTimeout.tv_usec) {
            setTimeout(m_cmdTimeout.tv_sec * 1000 + m_cmdTimeout.tv_usec / 1000);
        }

        if(!m_passwd.empty()) {
            auto r = (redisReply*)redisCommand(m_context.get(), "auth %s", m_passwd.c_str());
            if(!r) {
                cout << "auth error:("<< m_host << ":" << m_port << ", " << m_name << ")";
                return false;
            }
            if(r->type != REDIS_REPLY_STATUS) {
                cout << "auth reply type error:" << r->type << "("<< m_host << ":" << m_port << ", " << m_name << ")";
                return false;
            }
            if(!r->str) {
                cout << "auth reply str error: NULL("<< m_host << ":" << m_port << ", " << m_name << ")";
                return false;
            }
            if(strcmp(r->str, "OK") == 0) {
                return true;
            } else {
                cout << "auth error: " << r->str << "("<< m_host << ":" << m_port << ", " << m_name << ")";
                return false;
            }
        }
        return true;
    }

    return false;
}

bool Redis::setTimeout(uint64_t v) {
    m_cmdTimeout.tv_sec = v / 1000;
    m_cmdTimeout.tv_usec = v % 1000 * 1000;
    redisSetTimeout(m_context.get(), m_cmdTimeout);//设置操作超时时间
    return true;
}

ReplyPtr Redis::cmd(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    ReplyPtr rt = cmd(fmt, ap);
    va_end(ap);
    return rt;
}

ReplyPtr Redis::cmd(const char* fmt, va_list ap) {
    auto r = (redisReply*)redisvCommand(m_context.get(), fmt, ap);
    if(!r) {
        if(m_logEnable) {
            cout << "redisCommand error: (" << fmt << ")(" << m_host << ":" << m_port << ")(" << m_name << ")";
        }
        return nullptr;
    }
    ReplyPtr rt(r, freeReplyObject);
    if(r->type != REDIS_REPLY_ERROR) {
        return rt;
    }
    if(m_logEnable) {
        cout << "redisCommand error: (" << fmt << ")(" << m_host << ":" << m_port << ")(" << m_name << ")"
                    << ": " << r->str;
    }
    return nullptr;
}

ReplyPtr Redis::cmd(const std::vector<std::string>& argv) {
    std::vector<const char*> v;
    std::vector<size_t> l;
    for(auto& i : argv) {
        v.push_back(i.c_str());
        l.push_back(i.size());
    }

    auto r = (redisReply*)redisCommandArgv(m_context.get(), argv.size(), &v[0], &l[0]);
    if(!r) {
        if(m_logEnable) {
            cout << "redisCommandArgv error: (" << m_host << ":" << m_port << ")(" << m_name << ")";
        }
        return nullptr;
    }
    ReplyPtr rt(r, freeReplyObject);
    if(r->type != REDIS_REPLY_ERROR) {
        return rt;
    }
    if(m_logEnable) {
        cout << "redisCommandArgv error: (" << m_host << ":" << m_port << ")(" << m_name << ")"
                    << r->str;
    }
    return nullptr;
}

ReplyPtr Redis::getReply() {
    redisReply* r = nullptr;
    if(redisGetReply(m_context.get(), (void**)&r) == REDIS_OK) {
        ReplyPtr rt(r, freeReplyObject);
        return rt;
    }
    if(m_logEnable) {
        cout << "redisGetReply error: (" << m_host << ":" << m_port << ")(" << m_name << ")";
    }
    return nullptr;
}

int Redis::appendCmd(const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int rt = appendCmd(fmt, ap);
    va_end(ap);
    return rt;

}

int Redis::appendCmd(const char* fmt, va_list ap) {
    return redisvAppendCommand(m_context.get(), fmt, ap);
}

int Redis::appendCmd(const std::vector<std::string>& argv) {
    std::vector<const char*> v;
    std::vector<size_t> l;
    for(auto& i : argv) {
        v.push_back(i.c_str());
        l.push_back(i.size());
    }
    return redisAppendCommandArgv(m_context.get(), argv.size(), &v[0], &l[0]);
}

IRedis::ptr RedisManager::get(const std::string& name) {
    m_mutexLock.lock();
    auto it = m_datas.find(name);
    if(it == m_datas.end()) {
        return nullptr;
    }
    if(it->second.empty()) {
        return nullptr;
    }
    auto r = it->second.front();
    it->second.pop_front();
    
    m_mutexLock.unlock();

    auto rr = dynamic_cast<ISyncRedis*>(r);
    if((time(0) - rr->getLastActiveTime()) > 30) {
        if(!rr->cmd("ping")) {
            if(!rr->reconnect()) {
                m_mutexLock.lock();
                m_datas[name].push_back(r);
                m_mutexLock.unlock();
                return nullptr;
            }
        }
    }
    rr->setLastActiveTime(time(0));
    return std::shared_ptr<IRedis>(r, std::bind(&RedisManager::freeRedis
                        ,this, std::placeholders::_1));
}

void RedisManager::freeRedis(IRedis* r) {
    m_mutexLock.lock();
    m_datas[r->getName()].push_back(r);
    m_mutexLock.unlock();
}

RedisManager::RedisManager() {
    //默认配置map
    std::map<std::string, std::map<std::string, std::string> > m_configMap;
    std::map<std::string, std::string> m_map;
    //数据库的参数
    m_map["host"]="127.0.0.1:6379";
    m_map["type"]="redis";
	m_map["passwd"]="klczxas741789";
	m_map["timeout"]="100";
	m_map["name"]="redis_1";
    m_map["pool"]="2";
    m_configMap["redis_1"]=m_map;

    m_config=m_configMap;

    init();
}

RedisManager::RedisManager(const std::map<std::string, std::map<std::string, std::string> >& conf)
{
    m_config =conf;
    init();
}

void RedisManager::init() {
    size_t done = 0;
    size_t total = 0;
    for(auto& i : m_config) {
        auto type = get_value(i.second, "type");
        auto pool = TypeUtil::Atoi(get_value(i.second, "pool"));
        total += pool;
        for(int n = 0; n < pool; n++) {
            if(type == "redis") {
                Redis* rds(new Redis(i.second));
                rds->connect();
                rds->setLastActiveTime(time(0));
                m_mutexLock.lock();
                m_datas[i.first].push_back(rds);
                //Atomic::addFetch(done, 1);
                done++;
                m_mutexLock.unlock();
            } else {
                done++;
                //Atomic::addFetch(done, 1);
            }
        }
    }

    while(done != total) {
        usleep(5000);
    }
}

std::string RedisManager::toString() const {
    std::stringstream ss;
    dump(ss);
    return ss.str();
}

std::ostream& RedisManager::dump(std::ostream& os) {
    os << "[RedisManager total=" << m_config.size() << "]" << std::endl;
    for(auto& i : m_config) {
        os << "    " << i.first << " :[";
        for(auto& n : i.second) {
            os << "{" << n.first << ":" << n.second << "}";
        }
        os << "]" << std::endl;
    }
    return os;
}

/*
ReplyPtr RedisUtil::Cmd(const std::string& name, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    ReplyPtr rt = Cmd(name, fmt, ap);
    va_end(ap);
    return rt;
}

ReplyPtr RedisUtil::Cmd(const std::string& name, const char* fmt, va_list ap) {
    auto rds = RedisMgr::GetInstance()->get(name);
    if(!rds) {
        return nullptr;
    }
    return rds->cmd(fmt, ap);
}

ReplyPtr RedisUtil::Cmd(const std::string& name, const std::vector<std::string>& args) {
    auto rds = RedisMgr::GetInstance()->get(name);
    if(!rds) {
        return nullptr;
    }
    return rds->cmd(args);
}

ReplyPtr RedisUtil::TryCmd(const std::string& name, uint32_t count, const char* fmt, ...) {
    for(uint32_t i = 0; i < count; ++i) {
        va_list ap;
        va_start(ap, fmt);
        ReplyPtr rt = Cmd(name, fmt, ap);
        va_end(ap);

        if(rt) {
            return rt;
        }
    }
    return nullptr;
}

ReplyPtr RedisUtil::TryCmd(const std::string& name, uint32_t count, const std::vector<std::string>& args) {
    for(uint32_t i = 0; i < count; ++i) {
        ReplyPtr rt = Cmd(name, args);
        if(rt) {
            return rt;
        }
    }
    return nullptr;
}
*/

} } } // namespace StiBel::Data::Redis
