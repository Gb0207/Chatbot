#include "pch.h"
#include "MYserv.h"


void MYserv::OnAccept(int nErrorCode)
{
	Accept(m_user);

	CSocket::OnAccept(nErrorCode);
}
