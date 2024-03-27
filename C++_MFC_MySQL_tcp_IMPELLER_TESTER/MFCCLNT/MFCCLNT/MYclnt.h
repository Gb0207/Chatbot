#pragma once
#include <afxsock.h>
class MYclnt : public CSocket
{
public:
	virtual void OnReceive(int nErrorCode);
};

