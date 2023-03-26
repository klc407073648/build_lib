#include "CMyRedis.h"
#include <cstring>

CMyRedis::CMyRedis()
{
	m_pRedisContext = NULL;
	m_pRedisReply = NULL;
}
CMyRedis::~CMyRedis()
{
	if (m_pRedisContext)
	{
		redisFree(m_pRedisContext);
	}
	m_pRedisContext = NULL;
	m_pRedisReply = NULL;
}

void CMyRedis::Connect(const std::string &strIp, int nPort, const std::string &pwd)
{
	m_strIp = strIp;
	m_nPort = nPort;
	m_pRedisContext = redisConnect(strIp.c_str(), nPort);

	if (m_pRedisContext != NULL && m_pRedisContext->err)
	{
		std::string err = (m_pRedisContext->errstr == NULL ? "connect error" : m_pRedisContext->errstr);
		int code = m_pRedisContext->err;
		redisFree(m_pRedisContext);
		m_pRedisContext = NULL;
		throw CErrorMsg(err, code, "connect error!");
	}

	if (!pwd.empty())
	{
		m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "AUTH %s", pwd.c_str());
		if (!(m_pRedisReply->type == REDIS_REPLY_STATUS && (strcmp(m_pRedisReply->str, "OK") == 0)))
		{
			std::string strerr = (m_pRedisReply->str == NULL ? "auth error!" : m_pRedisReply->str);
			freeReplyObject(m_pRedisReply);
			throw CErrorMsg(strerr, -1, "auth error!");
		}
	}

	return;
}

/*#define REDIS_ERR_IO 1 /* Error in read or write */
/*#define REDIS_ERR_EOF 3 /* End of file */
/*#define REDIS_ERR_PROTOCOL 4 /* Protocol error */
/*#define REDIS_ERR_OOM 5 /* Out of memory */
/*#define REDIS_ERR_OTHER 2 /* Everything else... */
bool CMyRedis::CheckConenct()
{
	if (m_pRedisContext)
	{
		return !(m_pRedisContext->err);
	}
	return false;
}

/*
 *字符串相关操作
 */
void CMyRedis::Set(const std::string &strKey, const std::string &strValue)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "set %s %s", strKey.c_str(), strValue.c_str());
	if (m_pRedisReply == NULL)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("set error! m_pRedisReply is NULL");
	}
	if (!(m_pRedisReply->type == REDIS_REPLY_STATUS && (strcmp(m_pRedisReply->str, "OK") == 0)))
	{
		std::string strerr = (m_pRedisReply->str == NULL ? "set error!" : m_pRedisReply->str);
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg(strerr, -1, "set error!");
	}
	freeReplyObject(m_pRedisReply);
	return;
}

std::string CMyRedis::Get(const std::string &strKey)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "get %s", strKey.c_str());
	if (m_pRedisReply == NULL)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("get error! m_pRedisReply is NULL");
	}
	if ((m_pRedisReply->type != REDIS_REPLY_NIL) && (m_pRedisReply->type != REDIS_REPLY_STRING))
	{
		std::string strerr = (m_pRedisReply->str == NULL ? "get error!" : m_pRedisReply->str);
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg(strerr, -1, "get error! m_pRedisReply type error!");
	}
	std::string str = (m_pRedisReply->str == NULL ? "" : m_pRedisReply->str);
	freeReplyObject(m_pRedisReply);
	return str;
}

int CMyRedis::Del(const std::string &strKey)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "del %s", strKey.c_str());
	if (m_pRedisReply == NULL)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("del error! m_pRedisReply is NULL");
	}
	if (m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		std::string strerr = (m_pRedisReply->str == NULL ? "del error!" : m_pRedisReply->str);
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg(strerr, -1, "del error! m_pRedisReply type error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

/*
 *列表相关操作
 */
int CMyRedis::Push(const std::string &strListKey, const std::string &strValue, int nFlag /* = 0*/)
{
	if (0 == nFlag)
	{
		m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "rpush %s %s", strListKey.c_str(), strValue.c_str());
	}
	else
	{
		m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "lpush %s %s", strListKey.c_str(), strValue.c_str());
	}
	if (m_pRedisReply == NULL)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("push error! m_pRedisReply is NULL");
	}
	if (m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		std::string strerr = (m_pRedisReply->str == NULL ? "push error!" : m_pRedisReply->str);
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg(strerr, -1, "push error! m_pRedisReply type error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

std::string CMyRedis::Pop(const std::string &strListKey, int nFlag /*= 0*/)
{
	if (0 == nFlag)
	{
		m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "rpop %s", strListKey.c_str());
	}
	else
	{
		m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "lpop %s", strListKey.c_str());
	}
	if (m_pRedisReply == NULL || (m_pRedisReply->type != REDIS_REPLY_NIL && m_pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("pop error!");
	}
	std::string str = "";
	if (m_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if (m_pRedisReply->type == REDIS_REPLY_STRING)
		str = m_pRedisReply->str;
	freeReplyObject(m_pRedisReply);
	return str;
}

std::string CMyRedis::Lindex(const std::string &strListKey, int nIndex)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "lindex %s %d", strListKey.c_str(), nIndex);
	if (m_pRedisReply == NULL || (m_pRedisReply->type != REDIS_REPLY_NIL && m_pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("lindex error!");
	}
	std::string str = "";
	if (m_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if (m_pRedisReply->type == REDIS_REPLY_STRING)
		str = m_pRedisReply->str;
	freeReplyObject(m_pRedisReply);
	return str;
}

void CMyRedis::Lrange(const std::string &strListKey, int nStart, int nEnd, std::string strArray[], int &nCount)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "lrange %s %d %d", strListKey.c_str(), nStart, nEnd);
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("lrange error!");
	}
	int nMax = nCount;
	int i = 0;
	for (i; i < m_pRedisReply->elements; i++)
	{
		if (i >= nMax)
			break;
		strArray[i] = m_pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(m_pRedisReply);
	return;
}
/*
 *集合相关操作
 */
int CMyRedis::Sadd(const std::string &strSetKey, const std::string &strItem)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "sadd %s %s", strSetKey.c_str(), strItem.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

int CMyRedis::Srem(const std::string &strSetKey, const std::string &strItem)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "srem %s %s", strSetKey.c_str(), strItem.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

bool CMyRedis::SisMember(const std::string &strSetKey, const std::string &strItem)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "sismember %s %s", strSetKey.c_str(), strItem.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

void CMyRedis::Smembers(const std::string &strSetKey, std::string strArray[], int &nCount)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "smembers %s", strSetKey.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("smembers error!");
	}
	int nMax = nCount;
	int i = 0;
	for (i; i < m_pRedisReply->elements; i++)
	{
		if (i >= nMax)
			break;
		strArray[i] = m_pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(m_pRedisReply);
	return;
}

/*
 *散列操作
 */
int CMyRedis::HSet(const std::string &strHashKey, const std::string &key, const std::string &value)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "hset %s %s %s", strHashKey.c_str(), key.c_str(), value.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("hset error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

std::string CMyRedis::HGet(const std::string &strHashKey, const std::string &key)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "hget %s %s", strHashKey.c_str(), key.c_str());
	if (m_pRedisReply == NULL || (m_pRedisReply->type != REDIS_REPLY_NIL && m_pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("hget error!");
	}
	std::string str = "";
	if (m_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if (m_pRedisReply->type == REDIS_REPLY_STRING)
		str = m_pRedisReply->str;
	freeReplyObject(m_pRedisReply);
	return str;
}

int CMyRedis::HDel(const std::string &strHashKey, const std::string &key)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "hdel %s %s", strHashKey.c_str(), key.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("hdel error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}
void CMyRedis::HGetAll(const std::string &strHashKey, std::string strArray[], int &nCount)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "hgetall %s", strHashKey.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("hgetall error!");
	}
	int nMax = nCount;
	int i = 0;
	for (i; i < m_pRedisReply->elements; i++)
	{
		if (i >= nMax)
			break;
		strArray[i] = m_pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(m_pRedisReply);
	return;
}

/*
 *有序集合相关操作
 */
int CMyRedis::ZAdd(const std::string &strZSetKey, int nScore, const std::string &value)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "zadd %s %d %s", strZSetKey.c_str(), nScore, value.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		std::string strError = m_pRedisReply->str;
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg(strError);
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}

void CMyRedis::ZRange(const std::string &strZSetKey, int nStartIndex, int nEndIndex,
					  std::string strArray[], int &nCount)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "zrange %s %d %d",
											   strZSetKey.c_str(),
											   nStartIndex,
											   nEndIndex);
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("zrange error!");
	}
	int nMax = nCount;
	int i = 0;
	for (i; i < m_pRedisReply->elements; i++)
	{
		if (i >= nMax)
			break;
		strArray[i] = m_pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(m_pRedisReply);
	return;
}

void CMyRedis::ZRangeByScore(const std::string &strZSetKey, int nStartScore, int nEndScore, std::string strArray[], int &nCount)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "zrangebyscore %s %d %d",
											   strZSetKey.c_str(),
											   nStartScore,
											   nEndScore);
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("zrangebyscore error!");
	}
	int nMax = nCount;
	int i = 0;
	for (i; i < m_pRedisReply->elements; i++)
	{
		if (i >= nMax)
			break;
		strArray[i] = m_pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(m_pRedisReply);
	return;
}

int CMyRedis::ZRem(const std::string &strZSetKey, const std::string &value)
{
	m_pRedisReply = (redisReply *)redisCommand(m_pRedisContext, "zrem %s %s", strZSetKey.c_str(), value.c_str());
	if (m_pRedisReply == NULL || m_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(m_pRedisReply);
		throw CErrorMsg("zrem error!");
	}
	int nRet = m_pRedisReply->integer;
	freeReplyObject(m_pRedisReply);
	return nRet;
}
