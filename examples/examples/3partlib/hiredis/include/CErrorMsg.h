// C_Error.h
#ifndef C_ERROR_H_H
#define C_ERROR_H_H
#include <string>
//------------------------------------------------------------------------
// �� ��: CErrorMsg
// ��; : �����쳣�Ļ���,����ͨ���̳���ɸ��������쳣��ʵ��
//------------------------------------------------------------------------
class CErrorMsg
{
public:
	CErrorMsg(const std::string &strErrorMsg = "", int nErrorCode = 0, const std::string &strHint = "");
	virtual ~CErrorMsg();

	int get_errorCode() const;
	const std::string &get_errorMsg() const;
	const std::string &get_errorHint() const;
	void set_errorCode(int nErrorCode);
	void set_errorMsg(const std::string &strMsg);
	void set_errorHint(const std::string &strHint);

protected:
private:
	std::string m_strErrorMsg;
	int m_nErrorCode;
	std::string m_strHint;
};
#endif // C_ERROR_H_H