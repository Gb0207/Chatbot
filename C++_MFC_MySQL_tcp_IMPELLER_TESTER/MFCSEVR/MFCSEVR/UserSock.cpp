// UserSock.cpp: 구현 파일
//

#include "pch.h"
#include "MFCSEVR.h"
#include "UserSock.h"
#include "iostream"


// UserSock

UserSock::UserSock()
{
}

UserSock::~UserSock()
{
}


// UserSock 멤버 함수


void UserSock::OnReceive(int nErrorCode)
{
	int data;
	Receive(&data, sizeof(int));
	
	std::cout << "클라이언트에게 받은 정수: " << data << std::endl;

	int data2 = 10;
	Send(&data2, sizeof(int));

	CSocket::OnReceive(nErrorCode);
}


void UserSock::OnClose(int nErrorCode)
{
	CSocket::OnClose(nErrorCode);

	ShutDown(2);
	Close();
}
