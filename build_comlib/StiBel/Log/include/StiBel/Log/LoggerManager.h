/**
 * @file LoggerManager.h
 * @brief ��־ģ���װ
 * @author klc
 * @date 2020-03-01
 * @copyright Copyright (c) 2020�� klc
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
	 * @brief ��־���ȼ�
	 */
	enum Priority {
		ERROR,
		WARN,
		INFO,
		DEBUG
	};
	
	/**
	 * @brief ��־������
	 */
	class LoggerManager {
		 public: 
			/* Ĭ�Ϲ��캯��*/
			LoggerManager(); 

			/* �����ƵĹ��캯��*/
			LoggerManager(const string& name); 

			/* ��������*/
			~LoggerManager();

			/*��ʼ������*/
			void  init();

			/*��ȡ�����ļ�����*/
			const string& getConfFileName() const;

			/* ����root�����ȼ���һ��ֱ���޸�root���ȼ�Ӱ��m_Instance���ȼ�*/
			void setRootPriority(Priority& priority);

			/* ��ȡm_Instance���ȼ�*/
			const int&  getPriority() const;

			/*��ȡ��־��ʵ������*/
			const string& getInstanceName() const;

			/*��ȡ��־�������ʵ��*/
			log4cpp::Category* getCategory() const;

			/*�Ƿ�׼������*/
			const bool& idReady() const;

		 public: 
		 	/*�������ļ�������log����*/
			static void start(const string& name);
		 private: 
			/*���������ļ�����Appender������*/
			static void readConfFromFile();
	
			/*���������ļ�*/
			static void setConfFileName(const string& name);

		 private:
			log4cpp::Category* _instance; // ��־�������ʵ��
			string 	_instanceName;// ��־�������ʵ������
			log4cpp::Category* _root; // ����־��
			Priority _priority;// ���ȼ�
			static string _confFileName;// �����ļ�
			static bool _ready;// �Ƿ������־
		};
	

} }  // namespace StiBel::Log

#endif //__LOG_LOGGERMANAGER_H__
