/**
 * @file CErrorMsg.h
 * @brief redis���쳣�����װ
 *        �����쳣�Ļ���,����ͨ���̳���ɸ��������쳣��ʵ��
 * @author klc
 * @date 2020-08-03
 * @copyright Copyright (c) 2020�� klc
 */

#ifndef __STIBEL_CERRORMSG_H__
#define __STIBEL_CERRORMSG_H__

#include <string>

using std::string;

namespace StiBel {
namespace Data {
namespace Redis {

class CErrorMsg
{
public:
	CErrorMsg(string strErrorMsg = "", int nErrorCode = 0, string strHint="")
	:_strErrorMsg(strErrorMsg), _nErrorCode(nErrorCode), _strHint(strHint)
	{
	}
	virtual ~CErrorMsg(){}
	int get_errorCode() const{return _nErrorCode;}
	string get_errorMsg() const{return _strErrorMsg;}
	string get_errorHint() const{return _strHint;}
	void set_errorCode(int nErrorCode){_nErrorCode = nErrorCode;}
	void set_errorMsg(string strMsg){_strErrorMsg = strMsg;}
	void set_errorHint(string strHint){_strHint = strHint;}
protected:
private:
	string _strErrorMsg;
	int _nErrorCode;
	string _strHint;
};

} } } // namespace StiBel::Data::Redis
#endif // __STIBEL_CERRORMSG_H__