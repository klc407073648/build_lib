#include "CMyRedis.h"
#include "CErrorMsg.h"
#include <stdio.h>
#include <iostream>

int main()
{
	CMyRedis myRedis;

	try
	{
		// 需要填写实际ip,port,密码
		// 在docker容器执行时，不能填127.0.0.1
		// 示例:myRedis.Connect("1.1.1.1", 6379,"123456")
		myRedis.Connect("127.0.0.1", 6379, "123456");

		std::cout << "connect success!" << std::endl;
		std::cout << myRedis.CheckConenct() << std::endl;
		myRedis.Set("hello", "world");
		std::cout << myRedis.Get("Work") << std::endl;
		myRedis.Set("set", "get");
		std::cout << myRedis.Get("hello") << std::endl;

		std::cout << "**************zadd****************" << std::endl;
		std::cout << myRedis.ZAdd("zset-key", 1, "member1") << std::endl;
		std::cout << myRedis.ZAdd("zset-key", 4, "member4") << std::endl;
		std::cout << myRedis.ZAdd("zset-key", 3, "member3") << std::endl;
		std::cout << myRedis.ZAdd("zset-key", 2, "member2") << std::endl;
		std::cout << myRedis.ZAdd("zset-key", 5, "member5") << std::endl;

		std::cout << "**************zrange(3,6)****************" << std::endl;
		std::string strArray[10];
		int nCount = 10;
		myRedis.ZRange("zset-key", 3, 6, strArray, nCount);
		for (int i = 0; i < nCount; i++)
		{
			std::cout << strArray[i] << std::endl;
		}
		std::cout << "check connect: " << myRedis.CheckConenct() << std::endl;

		std::cout << "*************zrangebysocre(0,2)***************" << std::endl;
		myRedis.ZRangeByScore("zset-key", 0, 2, strArray, nCount);
		for (int i = 0; i < nCount; i++)
		{
			std::cout << strArray[i] << std::endl;
		}
		std::cout << "check connect: " << myRedis.CheckConenct() << std::endl;

		std::cout << "***************zrem*************************" << std::endl;
		std::cout << myRedis.ZRem("zset-key", "member1") << std::endl;
		std::cout << myRedis.ZRem("zset-key", "member2") << std::endl;
		std::cout << "check connect: " << myRedis.CheckConenct() << std::endl;
		myRedis.Set("hello", "world");
		std::string str = myRedis.Get("hello");
		std::cout << "hello:" << str << std::endl;
		str = myRedis.Get("null");
		std::cout << "null" << str << std::endl;
		std::cout << myRedis.Del("hello") << std::endl;
		std::cout << myRedis.Del("world") << std::endl;

		std::cout << myRedis.Push("list-keytest", "item0") << std::endl;
		std::cout << myRedis.Push("list-keytest", "item1") << std::endl;
		std::cout << myRedis.Push("list-keytest", "item2") << std::endl;
		for (int i = 0; i < 8; i++)
		{
			std::cout << myRedis.Pop("list-keytest") << std::endl;
		}
		std::cout << myRedis.Lindex("list-keytest", 1) << std::endl;
		std::cout << myRedis.Lindex("list-keytest", 10) << std::endl;
		std::string array[10];
		nCount = 10;
		myRedis.Lrange("list-keytest", 200, 201, array, nCount);
		for (int i = 0; i < nCount; i++)
		{
			std::cout << array[i] << std::endl;
		}
		std::cout << myRedis.Sadd("set-key", "test1") << std::endl;
		std::cout << myRedis.Sadd("set-key", "test2") << std::endl;
		std::cout << myRedis.Sadd("set-key", "test3") << std::endl;
		std::cout << myRedis.Sadd("set-key", "test4") << std::endl;

		std::cout << "***********smember:*************" << std::endl;
		std::string strArray1[20];
		nCount = 20;
		myRedis.Smembers("set-key", strArray1, nCount);
		for (int i = 0; i < nCount; i++)
		{
			std::cout << strArray1[i] << std::endl;
		}
		std::cout << myRedis.Sadd("set-key", "hello") << std::endl;
		std::cout << myRedis.Srem("set-key", "world") << std::endl;
		std::cout << myRedis.Srem("set-key", "test") << std::endl;
		std::cout << myRedis.SisMember("set-key", "world") << std::endl;
		std::cout << myRedis.SisMember("set-key", "test") << std::endl;
		std::cout << myRedis.HSet("hash-key", "key1", "value1") << std::endl;
		std::cout << myRedis.HSet("hash-key", "key2", "value2") << std::endl;
		std::cout << myRedis.HSet("hash-key", "key1", "value1") << std::endl;
		std::cout << myRedis.HSet("hash-key", "key3", "value3") << std::endl;
		std::string strArray2[30];
		nCount = 30;
		myRedis.HGetAll("hash-key", strArray2, nCount);
		for (int i = 0; i < nCount; i++)
		{
			std::cout << strArray2[i] << std::endl;
		}
		std::cout << myRedis.HGet("hash-key", "key1") << std::endl;
		std::cout << myRedis.HGet("hash-key", "key3") << std::endl;
		std::cout << myRedis.HGet("hash-key", "key8") << std::endl;
		std::cout << myRedis.HDel("hash-key", "key1") << std::endl;
		std::cout << myRedis.HDel("hash-key", "key11") << std::endl;
	}
	catch (CErrorMsg &cErr)
	{
		printf("error code = %d, errmsg=%s\r\n", cErr.get_errorCode(), cErr.get_errorMsg().c_str());
		return 0;
	}

	return 0;
}
