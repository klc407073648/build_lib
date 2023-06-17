#include "StiBel/Data/Redis/CMyRedis.h"

namespace StiBel {
namespace Data {
namespace Redis {

CMyRedis::ptr CMyRedis::_myRedis = NULL;

CMyRedis::CMyRedis()
{
	_pRedisContext = NULL;
	_pRedisReply = NULL;
}
CMyRedis::~CMyRedis()
{
	if(_pRedisContext)
	{
		redisFree(_pRedisContext);
	}
	_pRedisContext = NULL;
	_pRedisReply = NULL;
}

static CMyRedis::ptr  CMyRedis::getInstance(const string& strIp,int nPort,const string& passwd)
{
	if(_myRedis ==NULL)
	{
		CMyRedis::ptr mredis(new CMyRedis());
		_myRedis = mredis;
		//_myRedis(new CMyRedis());
		_myRedis->Connect(strIp,nPort,passwd);
	}
	return _myRedis;
}

void CMyRedis::Connect(const string& strIp,int nPort,const string& passwd)
{
		_strIp = strIp;
		_nPort = nPort;
		_pRedisContext = redisConnect(strIp.c_str(), nPort);
		if(_pRedisContext != NULL && _pRedisContext->err)
		{
			string err = (_pRedisContext->errstr==NULL?"connect error":_pRedisContext->errstr);
			int code = _pRedisContext->err;
			redisFree(_pRedisContext);
			_pRedisContext = NULL;
			throw CErrorMsg(err, code, "connect error!");
		}

		_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"AUTH %s", passwd.c_str());
		if(_pRedisReply == NULL)
		{
			freeReplyObject(_pRedisReply);
			throw CErrorMsg("auth error! _pRedisReply is NULL");
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
	if(_pRedisContext)
	{
		return !(_pRedisContext->err);
	}
	return false;
}

/*
 *字符串相关操作
 */
void CMyRedis::Set(const string & strKey,const string &strValue)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"set %s %s", strKey.c_str(), strValue.c_str());
	if(_pRedisReply == NULL)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("set error! _pRedisReply is NULL");
	}
	if(!(_pRedisReply->type == REDIS_REPLY_STATUS && (strcmp(_pRedisReply->str, "OK") == 0)))
	{
		string strerr = (_pRedisReply->str==NULL?"set error!":_pRedisReply->str);
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strerr, -1, "set error!");
	}
	freeReplyObject(_pRedisReply);
	return;
}

void CMyRedis::Setex(const string & strKey,int strSec,const string &strValue)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"setex %s %d %s", strKey.c_str(), strSec,strValue.c_str());
	if(_pRedisReply == NULL)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("set error! _pRedisReply is NULL");
	}
	if(!(_pRedisReply->type == REDIS_REPLY_STATUS && (strcmp(_pRedisReply->str, "OK") == 0)))
	{
		string strerr = (_pRedisReply->str==NULL?"set error!":_pRedisReply->str);
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strerr, -1, "set error!");
	}
	freeReplyObject(_pRedisReply);
	return;
}


string CMyRedis::Get(const string & strKey)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"get %s", strKey.c_str());
	if(_pRedisReply == NULL)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("get error! _pRedisReply is NULL");
	}
	if((_pRedisReply->type != REDIS_REPLY_NIL) && (_pRedisReply->type != REDIS_REPLY_STRING))
	{
		string strerr = (_pRedisReply->str==NULL?"get error!":_pRedisReply->str);
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strerr, -1, "get error! _pRedisReply type error!");
	}
	string str = (_pRedisReply->str==NULL?"":_pRedisReply->str);
	freeReplyObject(_pRedisReply);
	return str;
}

int CMyRedis::Del(const string & strKey)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"del %s", strKey.c_str());
	if(_pRedisReply == NULL)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("del error! _pRedisReply is NULL");
	}
	if(_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		string strerr = (_pRedisReply->str==NULL?"del error!":_pRedisReply->str);
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strerr, -1, "del error! _pRedisReply type error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

/*
 *列表相关操作
 */
int CMyRedis::Push(const string & strListKey,const string & strValue,int nFlag/* = 0*/)
{
	if(0 == nFlag)
	{
		_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"rpush %s %s", strListKey.c_str(), strValue.c_str());
	}else
	{
		_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"lpush %s %s", strListKey.c_str(), strValue.c_str());
	}
	if(_pRedisReply == NULL)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("push error! _pRedisReply is NULL");
	}
	if(_pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		string strerr = (_pRedisReply->str==NULL?"push error!":_pRedisReply->str);
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strerr, -1, "push error! _pRedisReply type error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

string CMyRedis::Pop(const string & strListKey,int nFlag /*= 0*/)
{
	if(0 == nFlag)
	{
		_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"rpop %s", strListKey.c_str());
	}else
	{
		_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"lpop %s", strListKey.c_str());
	}
	if(_pRedisReply == NULL || (_pRedisReply->type != REDIS_REPLY_NIL && _pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("pop error!");
	}
	string str = "";
	if(_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if(_pRedisReply->type == REDIS_REPLY_STRING)
		str = _pRedisReply->str;
	freeReplyObject(_pRedisReply);
	return str;
}

string CMyRedis::Lindex(const string & strListKey,int nIndex)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"lindex %s %d", strListKey.c_str(), nIndex);
	if(_pRedisReply == NULL || (_pRedisReply->type != REDIS_REPLY_NIL && _pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("lindex error!");
	}
	string str = "";
	if(_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if(_pRedisReply->type == REDIS_REPLY_STRING)
		str = _pRedisReply->str;
	freeReplyObject(_pRedisReply);
	return str;	
}

void CMyRedis::Lrange(const string & strListKey,int nStart,int nEnd,string strArray[],int & nCount)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"lrange %s %d %d", strListKey.c_str(), nStart, nEnd);
	if(_pRedisReply == NULL || _pRedisReply->type!= REDIS_REPLY_ARRAY)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("lrange error!");
	}
	int nMax = nCount;
	int i = 0;
	for(i; i<_pRedisReply->elements; i++)
	{
		if(i>=nMax)
			break;
		strArray[i] = _pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(_pRedisReply);
	return;
}
/*
 *集合相关操作
 */
int CMyRedis::Sadd(const string & strSetKey,const string & strItem)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"sadd %s %s",strSetKey.c_str(), strItem.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

int CMyRedis::Srem(const string & strSetKey,const string & strItem)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"srem %s %s",strSetKey.c_str(), strItem.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

bool CMyRedis::SisMember(const string & strSetKey,const string & strItem)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"sismember %s %s",strSetKey.c_str(), strItem.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("sadd error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

void CMyRedis::Smembers(const string & strSetKey,string strArray[],int& nCount)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"smembers %s", strSetKey.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type!= REDIS_REPLY_ARRAY)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("smembers error!");
	}
	int nMax = nCount;
	int i = 0;
	for(i; i<_pRedisReply->elements; i++)
	{
		if(i>=nMax)
			break;
		strArray[i] = _pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(_pRedisReply);
	return;
}

/*
 *散列操作
 */
int CMyRedis::HSet(const string & strHashKey,const string & key,const string & value)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"hset %s %s %s",strHashKey.c_str(), key.c_str(), value.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("hset error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

string CMyRedis::HGet(const string & strHashKey,const string & key)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"hget %s %s", strHashKey.c_str(), key.c_str());
	if(_pRedisReply == NULL || (_pRedisReply->type != REDIS_REPLY_NIL && _pRedisReply->type != REDIS_REPLY_STRING))
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("hget error!");
	}
	string str = "";
	if(_pRedisReply->type == REDIS_REPLY_NIL)
		str = "";
	if(_pRedisReply->type == REDIS_REPLY_STRING)
		str = _pRedisReply->str;
	freeReplyObject(_pRedisReply);
	return str;	

}

int CMyRedis::HDel(const string & strHashKey,const string & key)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"hdel %s %s",strHashKey.c_str(), key.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("hdel error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;

}
void CMyRedis::HGetAll(const string & strHashKey, string strArray[], int& nCount)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"hgetall %s",strHashKey.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("hgetall error!");
	}
	int nMax = nCount;
	int i = 0;
	for(i; i<_pRedisReply->elements; i++)
	{
		if(i>=nMax)
			break;
		strArray[i] = _pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(_pRedisReply);
	return;
}

/*
 *有序集合相关操作
 */
int CMyRedis::ZAdd(const string & strZSetKey,int nScore,const string & value)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"zadd %s %d %s",strZSetKey.c_str(), nScore, value.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		string strError = _pRedisReply->str;
		freeReplyObject(_pRedisReply);
		throw CErrorMsg(strError);
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}

void CMyRedis::ZRange(const string & strZSetKey,int nStartIndex,int nEndIndex,
						string strArray [ ],int & nCount)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"zrange %s %d %d",
												strZSetKey.c_str(),
												nStartIndex,
												nEndIndex);
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("zrange error!");
	}
	int nMax = nCount;
	int i = 0;
	for(i; i<_pRedisReply->elements; i++)
	{
		if(i>=nMax)
			break;
		strArray[i] = _pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(_pRedisReply);
	return;	
}

void CMyRedis::ZRangeByScore(const string & strZSetKey,int nStartScore,int nEndScore,string strArray [ ],int & nCount)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"zrangebyscore %s %d %d",
												strZSetKey.c_str(),
												nStartScore,
												nEndScore);
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_ARRAY)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("zrangebyscore error!");
	}
	int nMax = nCount;
	int i = 0;
	for(i; i<_pRedisReply->elements; i++)
	{
		if(i>=nMax)
			break;
		strArray[i] = _pRedisReply->element[i]->str;
	}
	nCount = i;
	freeReplyObject(_pRedisReply);
	return;	
}

int CMyRedis::ZRem(const string & strZSetKey,const string & value)
{
	_pRedisReply = (redisReply*)redisCommand(_pRedisContext,"zrem %s %s",strZSetKey.c_str(), value.c_str());
	if(_pRedisReply == NULL || _pRedisReply->type != REDIS_REPLY_INTEGER)
	{
		freeReplyObject(_pRedisReply);
		throw CErrorMsg("zrem error!");
	}
	int nRet = _pRedisReply->integer;
	freeReplyObject(_pRedisReply);
	return nRet;
}


} } } // namespace StiBel::Data::Redis