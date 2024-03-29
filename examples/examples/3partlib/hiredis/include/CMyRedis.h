/* Author:zhangxp
 * Date:2017-5-23
 * Version:1.0
 * Modify:
 * 所有失败操作以异常形式返回,请注意捕获异常.
 使用示例:
	try{
		CMyRedis myRedis;
		myRedis.connect("127.0.0.1");
		myRedis.set("hello", "world");
		std::string str = myRedis.get("hello");
		...
	}catch(CErrorMsg& cErr)
	{
		cout<<cErr.get_errorCode()<<cErr.get_errorMsg().c_str()<<endl;
	}
 *
 *Welcome to use!
 */
#ifndef C_MY_REDIS_H
#define C_MY_REDIS_H
#include "CErrorMsg.h"
#include <string>
#include <hiredis/hiredis.h>

class CMyRedis
{

public:
	CMyRedis();
	~CMyRedis();
	void Connect(const std::string &strIp, int nPort, const std::string &pwd = "");
	bool CheckConenct();
	/*
	 *字符串操作:Set Get Del
	 */
	void Set(const std::string &strKey, const std::string &strValue);
	// 获取指定键的值,如果键不存在,返回"".
	std::string Get(const std::string &strKey);
	// 删除指定键的值,键存在返回1,键不存在返回0.
	int Del(const std::string &strKey);

	/*
	 *列表操作 Push Pop Lindex Lrange
	 */
	// nFlag = 0默认从右端推入,不等于0从左端推入,成功返回当前列表元素个数.
	int Push(const std::string &strListKey, const std::string &strValue, int nFlag = 0);
	// nFlag = 0默认从右端推出,不等于从左端推出,成功返回元素的值,没有元素返回"".
	std::string Pop(const std::string &strListKey, int nFlag = 0);
	// 返回指定序号的单个元素,成功返回元素值,不存在返回"".
	std::string Lindex(const std::string &strListKey, int nIndex);
	// 返回一定返回的元素,strArray返回的元素数组,nCout输入数组的大小,输出返回的元素个数.
	void Lrange(const std::string &strListKey, int nStart, int nEnd, std::string strArray[],
				int &nCount);

	/*
	 *集合操作
	 */
	// 尝试添加一个元素到集合中,成功返回1,返回0表示集合中已经存在这个元素.
	int Sadd(const std::string &strSetKey, const std::string &strItem);
	// 从集合中移除元素,返回移除元素的个数.
	int Srem(const std::string &strSetKey, const std::string &strItem);
	// 检查一个元素是否存在于集合中.
	bool SisMember(const std::string &strSetKey, const std::string &strItem);
	// 返回集合中所有元素,strArray存放返回元素的数组,nCount输入数组的大小,
	// 输出返回的元素个数.
	void Smembers(const std::string &strSetKey, std::string strArray[], int &nCount);

	/*
	 *散列操作
	 */
	// 尝试添加一个键值对到散列中,成功返回1,0表示给定的键已经存在.value会覆盖原有值.
	int HSet(const std::string &strHashKey, const std::string &key, const std::string &value);
	// 返回指定的键的值,不存在返回"".
	std::string HGet(const std::string &strHashKey, const std::string &key);
	// 删除指定的键,返回1表示删除成功,0表示指定键不存在于散列中.
	int HDel(const std::string &strHashKey, const std::string &key);
	// 返回散列所包含的所有键值对.输入nCount表示接收数组的个数,输出nCount表示实际返回的
	// 个数.
	void HGetAll(const std::string &strHashKey, std::string strArray[], int &nCount);

	/*
	 *有序集合操作
	 */
	// 尝试向有序集合中添加元素,返回添加元素的个数.
	int ZAdd(const std::string &strZSetKey, int nScore, const std::string &value);
	// 按序号返回有序集合的元素.
	void ZRange(const std::string &strZSetKey, int nStartIndex, int nEndIndex,
				std::string strArray[], int &nCount);
	// 按分值返回有序集合的元素.
	void ZRangeByScore(const std::string &strZSetKey, int nStartScore,
					   int nEndScore, std::string strArray[], int &nCount);
	// 返回被移除元素的数量.
	int ZRem(const std::string &strZSetKey, const std::string &value);

private:
	redisContext *m_pRedisContext;
	redisReply *m_pRedisReply;
	std::string m_strIp;
	int m_nPort;
};
#endif // C_MY_REDIS_H