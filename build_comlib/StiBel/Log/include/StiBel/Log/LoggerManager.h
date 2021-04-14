/**
 * @file LoggerManager.h
 * @brief 日志模块封装
 * @author klc
 * @date 2020-03-01
 * @copyright Copyright (c) 2020年 klc
 */


#ifndef __LOG_LOGGERMANAGER_H__
#define __LOG_LOGGERMANAGER_H__

#include<log4cpp/Category.hh>
#include<iostream>
#include<string>
#include<vector>
#include<map>


using namespace std;

#define DECLARE_STATIC_LOGGERMANAGER()  static StiBel::Log::LoggerManager*  mlogger
#define CREATE_STATIC_LOGGERMANAGER(_class)  StiBel::Log::LoggerManager* _class::mlogger =new StiBel::Log::LoggerManager(#_class)
		
#define LOG_PACK(func,fmt,...)   {func(fmt, ##__VA_ARGS__);}

#define LogDebug(fmt, ...)  LOG_PACK(mlogger->getCategory()->debug, fmt, ##__VA_ARGS__)
#define LogInfo(fmt, ...)  LOG_PACK(mlogger->getCategory()->info, fmt, ##__VA_ARGS__)
#define LogWarn(fmt, ...)  LOG_PACK(mlogger->getCategory()->warn, fmt, ##__VA_ARGS__)
#define LogError(fmt, ...)  LOG_PACK(mlogger->getCategory()->error, fmt, ##__VA_ARGS__)	

namespace StiBel {
namespace Log {

	/**
	 * @brief 日志优先级
	 */
	enum Priority {
		ERROR,
		WARN,
		INFO,
		DEBUG
	};
	
	/**
	 * @brief 日志管理类
	 */
	class LoggerManager {
		 public: 
			/* 默认构造函数*/
			LoggerManager(); 

			/* 带名称的构造函数*/
			LoggerManager(const string& name); 

			/* 析构函数*/
			~LoggerManager();

			/*初始化函数*/
			void  init();

			/*获取配置文件名称*/
			const string& getConfFileName() const;

			/* 设置root的优先级，一般直接修改root优先级影响m_Instance优先级*/
			void setRootPriority(Priority& priority);

			/* 获取m_Instance优先级*/
			const int&  getPriority() const;

			/*获取日志的实例名称*/
			const string& getInstanceName() const;

			/*获取日志输出对象实例*/
			log4cpp::Category* getCategory() const;

			/*是否准备就绪*/
			const bool& idReady() const;

		 public: 
		 	/*以配置文件，开启log服务*/
			static void start(const string& name);
		 private: 
			/*利用配置文件设置Appender的属性*/
			static void readConfFromFile();
	
			/*设置配置文件*/
			static void setConfFileName(const string& name);

		 private:
			log4cpp::Category* _instance; // 日志输出对象实例
			string 	_instanceName;// 日志输出对象实例名称
			log4cpp::Category* _root; // 主日志器
			Priority _priority;// 优先级
			static string _confFileName;// 配置文件
			static bool _ready;// 是否就绪标志
		};
	

} }  // namespace StiBel::Log

#endif //__LOG_LOGGERMANAGER_H__
