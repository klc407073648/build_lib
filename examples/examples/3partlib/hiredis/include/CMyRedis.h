/* Author:zhangxp
 * Date:2017-5-23
 * Version:1.0
 * Modify:
 * ����ʧ�ܲ������쳣��ʽ����,��ע�Ⲷ���쳣.
 ʹ��ʾ��:
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
	 *�ַ�������:Set Get Del
	 */
	void Set(const std::string &strKey, const std::string &strValue);
	// ��ȡָ������ֵ,�����������,����"".
	std::string Get(const std::string &strKey);
	// ɾ��ָ������ֵ,�����ڷ���1,�������ڷ���0.
	int Del(const std::string &strKey);

	/*
	 *�б���� Push Pop Lindex Lrange
	 */
	// nFlag = 0Ĭ�ϴ��Ҷ�����,������0���������,�ɹ����ص�ǰ�б�Ԫ�ظ���.
	int Push(const std::string &strListKey, const std::string &strValue, int nFlag = 0);
	// nFlag = 0Ĭ�ϴ��Ҷ��Ƴ�,�����ڴ�����Ƴ�,�ɹ�����Ԫ�ص�ֵ,û��Ԫ�ط���"".
	std::string Pop(const std::string &strListKey, int nFlag = 0);
	// ����ָ����ŵĵ���Ԫ��,�ɹ�����Ԫ��ֵ,�����ڷ���"".
	std::string Lindex(const std::string &strListKey, int nIndex);
	// ����һ�����ص�Ԫ��,strArray���ص�Ԫ������,nCout��������Ĵ�С,������ص�Ԫ�ظ���.
	void Lrange(const std::string &strListKey, int nStart, int nEnd, std::string strArray[],
				int &nCount);

	/*
	 *���ϲ���
	 */
	// �������һ��Ԫ�ص�������,�ɹ�����1,����0��ʾ�������Ѿ��������Ԫ��.
	int Sadd(const std::string &strSetKey, const std::string &strItem);
	// �Ӽ������Ƴ�Ԫ��,�����Ƴ�Ԫ�صĸ���.
	int Srem(const std::string &strSetKey, const std::string &strItem);
	// ���һ��Ԫ���Ƿ�����ڼ�����.
	bool SisMember(const std::string &strSetKey, const std::string &strItem);
	// ���ؼ���������Ԫ��,strArray��ŷ���Ԫ�ص�����,nCount��������Ĵ�С,
	// ������ص�Ԫ�ظ���.
	void Smembers(const std::string &strSetKey, std::string strArray[], int &nCount);

	/*
	 *ɢ�в���
	 */
	// �������һ����ֵ�Ե�ɢ����,�ɹ�����1,0��ʾ�����ļ��Ѿ�����.value�Ḳ��ԭ��ֵ.
	int HSet(const std::string &strHashKey, const std::string &key, const std::string &value);
	// ����ָ���ļ���ֵ,�����ڷ���"".
	std::string HGet(const std::string &strHashKey, const std::string &key);
	// ɾ��ָ���ļ�,����1��ʾɾ���ɹ�,0��ʾָ������������ɢ����.
	int HDel(const std::string &strHashKey, const std::string &key);
	// ����ɢ�������������м�ֵ��.����nCount��ʾ��������ĸ���,���nCount��ʾʵ�ʷ��ص�
	// ����.
	void HGetAll(const std::string &strHashKey, std::string strArray[], int &nCount);

	/*
	 *���򼯺ϲ���
	 */
	// ���������򼯺������Ԫ��,�������Ԫ�صĸ���.
	int ZAdd(const std::string &strZSetKey, int nScore, const std::string &value);
	// ����ŷ������򼯺ϵ�Ԫ��.
	void ZRange(const std::string &strZSetKey, int nStartIndex, int nEndIndex,
				std::string strArray[], int &nCount);
	// ����ֵ�������򼯺ϵ�Ԫ��.
	void ZRangeByScore(const std::string &strZSetKey, int nStartScore,
					   int nEndScore, std::string strArray[], int &nCount);
	// ���ر��Ƴ�Ԫ�ص�����.
	int ZRem(const std::string &strZSetKey, const std::string &value);

private:
	redisContext *m_pRedisContext;
	redisReply *m_pRedisReply;
	std::string m_strIp;
	int m_nPort;
};
#endif // C_MY_REDIS_H