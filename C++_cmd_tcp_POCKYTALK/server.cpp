#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <windows.h>
#include <process.h>

#define BUF_SIZE 100
#define MAX_CLNT 256

unsigned WINAPI HandleClnt(void *arg);
void SendMsg(char *msg, int len, SOCKET Now);
void ErrorHandling(char* msg);
void mainMenu();
void sock_info_list();

int clntCnt=0;
SOCKET clntSocks[MAX_CLNT];
HANDLE hMutex;
const int port = 980207;

WSADATA wsaData;
SOCKET hServSock, hClntSock;
SOCKADDR_IN servAdr, clntAdr;
int clntAdrSz;
HANDLE hThread;
std::vector<std::string> nickname;

typedef struct sock_info
{
    std::string nick;
    int chatNum;
    std::string Fnick[3];
    std::string OnOff;
}SOCK_INFO;
SOCK_INFO clnt[4];
    
int main(int argc)
{
    sock_info_list();
    mainMenu();

    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        ErrorHandling("WSAStartup() error!");
    }
    hMutex=CreateMutex(NULL, FALSE, NULL);
    hServSock=socket(PF_INET, SOCK_STREAM, 0);

    memset(&servAdr,0,sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=htonl(INADDR_ANY);
    servAdr.sin_port=htons(port);

    if(bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr))==SOCKET_ERROR)
        ErrorHandling("bind() error");
    if(listen(hServSock, 5)==SOCKET_ERROR)
        ErrorHandling("listen() error");

    while (1)
    {
        clntAdrSz=sizeof(clntAdr);
        hClntSock=accept(hServSock, (SOCKADDR*)&clntAdr, &clntAdrSz);

        WaitForSingleObject(hMutex,INFINITE);
        clntSocks[clntCnt++]=hClntSock;
        ReleaseMutex(hMutex);
        hThread=(HANDLE)_beginthreadex(NULL,0,HandleClnt,(void*)&hClntSock,0,NULL);

        std::cout << "Connected client IP:" << inet_ntoa(clntAdr.sin_addr) << std::endl;
    }
    closesocket(hServSock);
    WSACleanup();
    return 0;
}
/*함수이름: mainMenu()
기능: 서버 프로그램 실행 시 출력 구현 함수
반환: */
void mainMenu(){
    std::cout << "\n";
    std::cout << "===============================================\n";      
    std::cout << "                                               \n";
    std::cout << "                 < SERVER ON >                 \n";
    std::cout << "                                               \n";
    std::cout << "===============================================\n\n";
}
/*스레드 이름: unsigned WINAPI  HandleClnt()
기능: 클라이언트와 송수신하며, 수신받은 데이터를 정리해 포키톡 회원정보 수정과 채팅 및 파일 송신 하는 스레드*/
unsigned WINAPI HandleClnt(void *arg)
{
    SOCKET hClntSock=*((SOCKET*)arg);
    int strLen=0;
    std::string str;
    char msg[BUF_SIZE];
    std::string fnick;

    while ((strLen=recv(hClntSock, msg, sizeof(msg), 0)) !=0)
    {
        std::istringstream iss(str=msg);
        std::string buf;
        std::vector<std::string> result;
        
        while (getline(iss, buf, ':'))
        {
            result.push_back(buf);
        }
        if (result[0] == "nicklist")
        {
            for(int i=0; i<4; i++)
            {
                if(result[1] == clnt[i].nick)
                {
                    clnt[i].OnOff = "On";
                    for(int j=0; j<3; j++)
                    {
                        fnick.append(clnt[i].Fnick[j]);
                        fnick.append(",");
                        for(int l=0; l<4; l++)
                        {
                            if(clnt[i].Fnick[j] == clnt[l].nick)
                            {
                                fnick.append(clnt[l].OnOff);
                                fnick.append(",");
                            } 
                        }
                    }
                    char * nick = const_cast<char*>(fnick.c_str());
                    send(hClntSock, nick, fnick.size(), 0);
                }
            } 
        }
        else if(result[0] == "nickplus") 
        {
            for(int i=0; i<4; i++)
            {
                if(result[1] == clnt[i].nick)
                {
                    if(clnt[i].Fnick[0] == " ")
                    {
                        clnt[i].Fnick[0] = result[2];
                        char * plus = "친구를 추가하였습니다.";
                        send(hClntSock, plus, strlen(plus), 0);
                        break;
                    }
                    else if(clnt[i].Fnick[1] == " ")
                    {
                        clnt[i].Fnick[1] = result[2];
                        char * plus = "친구를 추가하였습니다.";
                        send(hClntSock, plus, strlen(plus), 0);
                        break;
                    }
                    else if(clnt[i].Fnick[2] == " ")
                    {
                        clnt[i].Fnick[2] = result[2];
                        char * plus = "친구를 추가하였습니다.";
                        send(hClntSock, plus, strlen(plus), 0);
                        break;
                    }
                    else
                    {
                        char * plus2 = "더 이상 친구추가를 할 수 없습니다.";
                        send(hClntSock, plus2, strlen(plus2), 0);
                        break;
                    } 
                }  
            } 

        }
        else if(result[0] == "file") 
        {
            std::cout << msg << std::endl;
            for(int i=0; i<clntCnt; i++)
            {
                if(hClntSock != clntSocks[i])
                {
                    send(clntSocks[i], msg, sizeof(msg), 0);
                }
            } 
        }
        else
        {
            SendMsg(msg, strLen, hClntSock);
        }
    }
    WaitForSingleObject(hMutex,INFINITE);
    for(int i=0; i<clntCnt; i++)
    {
        if(hClntSock==clntSocks[i])
        {
            while (i++<clntCnt-1)
            {
                clntSocks[i]=clntSocks[i+1];
            }
            break;
        }
    }
    clntCnt--;
    ReleaseMutex(hMutex);
    closesocket(hClntSock);
    return 0;
}
/*함수이름: SendMsg()
기능: 현재 수신받은 클라이언트를 제외한 다른 클라이언트에게 데이터를 송신하는 함수
반환: 없음 */
void SendMsg(char *msg, int len, SOCKET Now) //send to all
{
    WaitForSingleObject(hMutex,INFINITE);
    
    for(int i=0; i<clntCnt; i++)
    {
        if(Now != clntSocks[i])
        {
            send(clntSocks[i], msg, len, 0);
        }
    } 
    ReleaseMutex(hMutex);
}
/*함수이름: sock_info_list()
기능: 포키톡 회원정보 구조체 초기화하는 함수
반환: 없음*/
void sock_info_list()
{
    clnt[0].nick = "gyub";
    clnt[0].chatNum = 10;
    clnt[0].Fnick[0] = "soo";
    clnt[0].Fnick[1] = "kim";
    clnt[0].Fnick[2] = "pack";
    clnt[0].OnOff = "Off";

    clnt[1].nick = "soo";
    clnt[1].chatNum = 20;
    clnt[1].Fnick[0] = "gyub";
    clnt[1].Fnick[1] = "kim";
    clnt[1].Fnick[2] = "pack";
    clnt[1].OnOff = "Off";

    clnt[2].nick = "kim";
    clnt[2].chatNum = 30;
    clnt[2].Fnick[0] = "gyub";
    clnt[2].Fnick[1] = "soo";
    clnt[2].Fnick[2] = "pack";
    clnt[2].OnOff = "Off";

    clnt[3].nick = "pack";
    clnt[3].chatNum = 40;
    clnt[3].Fnick[0] = "gyub";
    clnt[3].Fnick[1] = "soo";
    clnt[3].Fnick[2] = " ";
    clnt[3].OnOff = "Off";
}
/*함수이름: ErrorHandling()
기능: 에러발생 시 출력하는 함수
반환: 없음*/
void ErrorHandling(char* msg)
{
    fputs(msg,stderr);
    fputc('\n',stderr);
    exit(1);
}