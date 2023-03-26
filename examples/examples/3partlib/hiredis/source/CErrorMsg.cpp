#include "CErrorMsg.h"

CErrorMsg::CErrorMsg(const std::string &strErrorMsg, int nErrorCode, const std::string &strHint) : m_strErrorMsg(strErrorMsg), m_nErrorCode(nErrorCode), m_strHint(strHint)
{
}

CErrorMsg::~CErrorMsg() {}

int CErrorMsg::get_errorCode() const
{
	return m_nErrorCode;
}

const std::string &CErrorMsg::get_errorMsg() const
{
	return m_strErrorMsg;
}

const std::string &CErrorMsg::get_errorHint() const
{
	return m_strHint;
}

void CErrorMsg::set_errorCode(int nErrorCode)
{
	m_nErrorCode = nErrorCode;
}

void CErrorMsg::set_errorMsg(const std::string &strMsg)
{
	m_strErrorMsg = strMsg;
}

void CErrorMsg::set_errorHint(const std::string &strHint)
{
	m_strHint = strHint;
}
