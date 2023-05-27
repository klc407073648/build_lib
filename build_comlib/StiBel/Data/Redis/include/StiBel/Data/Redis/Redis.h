/**
 * @file Redis.h
 * @brief redis封装类，底层是调用hiredis接口
 * @author klc
 * @date 2021-04-21
 * @copyright Copyright (c) 2021年 klc
 
 */

#ifndef __STIBEL_REDIS_H__
#define __STIBEL_REDIS_H__
#include <string.h>
#include <memory>
#include <map>
#include <vector>
#include <list>
#include <functional>
#include <sstream>
#include <hiredis/hiredis.h>
#include "StiBel/Common/MutexLock.h"
#include "StiBel/Common/Singleton.h"

using StiBel::MutexLock;

namespace StiBel {
namespace Data {
namespace Redis {

const int DEFALUT_CONNECT_TIMEOUT=50;//ms

typedef std::shared_ptr<redisReply> ReplyPtr;

class IRedis {
public:
    typedef std::shared_ptr<IRedis> ptr;
    IRedis() : m_logEnable(true) { }
    virtual ~IRedis() {}

    virtual ReplyPtr cmd(const char* fmt, ...) = 0;
    virtual ReplyPtr cmd(const char* fmt, va_list ap) = 0;
    virtual ReplyPtr cmd(const std::vector<std::string>& argv) = 0;

    const std::string& getName() const { return m_name;}
    void setName(const std::string& v) { m_name = v;}

    const std::string& getPasswd() const { return m_passwd;}
    void setPasswd(const std::string& v) { m_passwd = v;}

protected:
    std::string m_name;
    std::string m_passwd;
    bool m_logEnable;
};

class ISyncRedis : public IRedis {
public:
    typedef std::shared_ptr<ISyncRedis> ptr;
    virtual ~ISyncRedis() {}

    virtual bool reconnect() = 0;
    virtual bool connect(const std::string& ip, int port, uint64_t ms = 0) = 0;
    virtual bool connect() = 0;
    virtual bool setTimeout(uint64_t ms) = 0;

    virtual int appendCmd(const char* fmt, ...) = 0;
    virtual int appendCmd(const char* fmt, va_list ap) = 0;
    virtual int appendCmd(const std::vector<std::string>& argv) = 0;

    virtual ReplyPtr getReply() = 0;

    uint64_t getLastActiveTime() const { return m_lastActiveTime;}
    void setLastActiveTime(uint64_t v) { m_lastActiveTime = v;}

protected:
    uint64_t m_lastActiveTime;
};

class Redis : public ISyncRedis {
public:
    typedef std::shared_ptr<Redis> ptr;
    Redis();
    Redis(const std::map<std::string, std::string>& conf);

    virtual bool reconnect();
    virtual bool connect(const std::string& ip, int port, uint64_t ms = 0);
    virtual bool connect();
    virtual bool setTimeout(uint64_t ms);

    virtual ReplyPtr cmd(const char* fmt, ...);
    virtual ReplyPtr cmd(const char* fmt, va_list ap);
    virtual ReplyPtr cmd(const std::vector<std::string>& argv);

    virtual int appendCmd(const char* fmt, ...);
    virtual int appendCmd(const char* fmt, va_list ap);
    virtual int appendCmd(const std::vector<std::string>& argv);

    virtual ReplyPtr getReply();
private:
	std::string m_host;
    uint32_t m_port;
    uint32_t m_connectMs;
    struct timeval m_cmdTimeout;
    std::shared_ptr<redisContext> m_context;
};

class RedisManager {
public:
    RedisManager();
    RedisManager(const std::map<std::string, std::map<std::string, std::string> >& conf);
    IRedis::ptr get(const std::string& name);
    std::string toString() const;

    std::ostream& dump(std::ostream& os);
private:
    void freeRedis(IRedis* r);
    void init();
private:
    StiBel::MutexLock m_mutexLock;
    std::map<std::string, std::list<IRedis*> > m_datas;
    std::map<std::string, std::map<std::string, std::string> > m_config;
};

typedef StiBel::SingletonPtr<RedisManager> RedisMgr;

/*
class RedisUtil {
public:
    static ReplyPtr Cmd(const std::string& name, const char* fmt, ...);
    static ReplyPtr Cmd(const std::string& name, const char* fmt, va_list ap); 
    static ReplyPtr Cmd(const std::string& name, const std::vector<std::string>& args); 

    static ReplyPtr TryCmd(const std::string& name, uint32_t count, const char* fmt, ...);
    static ReplyPtr TryCmd(const std::string& name, uint32_t count, const std::vector<std::string>& args); 
};
*/
} } } // namespace StiBel::Data::Redis

#endif
