#include "pch.h"
#include "MYclnt.h"
#include "iostream"

void MYclnt::OnReceive(int nErrorCode)
{
	CSocket::OnReceive(nErrorCode);
	int data;
	Receive(&data, sizeof(int));

	std::cout << "�������� ���� ����: " << data << std::endl;
}
