#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <conio.h> 
#include <Windows.h>
#include <process.h>

#define BUF_SIZE 1024
#define NAME_SIZE 20
#define MAX_LINES 1000 //파일용
#define MAX_LINE_LENGTH 100 //파일용

int startMenu(); //시작화면
int chatting(); //채팅선택화면
int oneToOne(); //개인채팅화면 친구 찾기 및 친구 추가 선택
int onpePass(); //오픈채팅화면 비밀번호입력화면
void nickname(); //오픈채팅의 닉네임화면 닉네임입력화면
std::string nickname1(); //친구찾기의 닉네임화면 닉네임입력화면
void nickname2(); //친구추가의 닉네임화면 닉네임입력화면
std::string friendList(std::vector<std::string> msg, int cnt); //친구찾기화면 친구 접속 상태 및 친구선택화면
std::string friendPlus(); //친구추가화면 친구정보추가 입력화면
void oneChat(std::string); //일대일 채팅화면
void onpeChat(int password); //오픈채팅화면
void file(SOCKET Now); //파일 송신
void friendCheck();

unsigned WINAPI SendMSG(void * arg);
unsigned WINAPI RecvMSG(void * arg);
void ErrorHandling(char* msg);

WSADATA wsaData;
SOCKET hSock;
SOCKADDR_IN servAdr;
HANDLE hSndThread, hRcvThread;

const char *server = "10.10.20.99";
const int port = 980207;
char name[NAME_SIZE];
char msg[BUF_SIZE];

int main(int argc)
{
    while (1)
    {
        if (startMenu() == 1)
        {
            while (1)
            {
                int num = chatting();
                if (num == 1)
                {
                    while (1)
                    {
                        friendCheck();
                        if (oneToOne() == 1) //친구찾기
                        {
                            std::string frien = nickname1();
                            if(frien == "q" || frien == "Q")
                            {
                                continue;
                            }
                            oneChat(frien);
                        }
                        else if(oneToOne() == 2) //친구추가
                        {
                            nickname2();
                            continue;
                        }
                        else if(oneToOne() == 3)
                        {
                            break;
                        }
                        else
                        {
                            std::cout << "잘못입력하였습니다." <<std::endl;
                            Sleep(1000);
                            continue;
                        }
                    }
                    continue;
                }
                else if (num == 2)
                {
                    while (1)
                    { 
                        int pass = onpePass();
                        if(pass == 980207)
                        {
                            nickname();
                            onpeChat(pass);
                        }
                        else
                        {
                            std::cout << "잘못입력하였습니다." << std::endl;
                            Sleep(1000);
                            continue;
                        }
                    }
                }
                else
                {
                    std::cout << "잘못입력하였습니다." <<std::endl;
                    Sleep(1000);
                    continue;
                }
            }  
        }   
        else if (startMenu() == 0)
        {
            std::cout << "프로그램을 종료합니다." << std::endl;
            break;
        }
        else
        {
            std::cout << "잘못입력하였습니다." << std::endl;
            continue;
        }
    }
    return 0;
}
/*함수이름: startMenu()
기능: 시작화면으로 입력 시 다음 화면으로 이동
반환: 1.채팅선택화면 2.프로그램 종료 int형 반환*/
int startMenu()
{
    system("cls");
    int start;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "         ______  _____  _____  _   ____   __        \n";
    std::cout << "         | ___ \\|  _  |/  __ \\| | / /\\ \\ / /    \n";
    std::cout << "         | |_/ /| | | || /  \\/| |/ /  \\ V /       \n";
    std::cout << "         |  __/ | | | || |    |    \\   \\ /        \n";
    std::cout << "         | |    \\ \\_/ /| \\__/\\| |\\  \\  | |    \n";
    std::cout << "         \\_|     \\___/  \\____/\\_| \\_/  \\_/    \n\n";                                                             
    std::cout << "                      1. START                      \n";
    std::cout << "                      0. DONE                       \n";
    std::cout << "====================================================\n\n";
    std::cin >> start;
    return start;
}
/*함수이름: chatting()
기능: 채팅선택화면으로 개인톡방 또는 오픈톡방 선택 시 다음 화면으로 이동
반환: 1.개인톡방화면 2.오픈채팅방 int형 반환*/
int chatting()
{
    system("cls");
    int chat;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                    1. ONE TO ONE                    \n";
    std::cout << "                    2. ONPE CHAT                     \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n\n";
    std::cin >> chat;
    return chat;
}
/*함수이름: oneToOne()
기능: 개인톡방화면으로 친구찾기 및 친구 추가 선택 시 다음 화면으로 이동
반환: 친구번호 int형 반환*/
int oneToOne()
{
    system("cls");
    int onechat;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                     1. 친구 찾기                     \n";
    std::cout << "                     2. 친구 추가                     \n";
    std::cout << "                     3. 뒤로                          \n";
    std::cout << "                                                      \n";
    std::cout << "=====================================================\n\n";
    std::cin >> onechat;
    return onechat;
}
/*함수이름: nickname()
기능: 오픈채팅방의 닉네임화면으로 닉네임 입력 시 다음 화면으로 이동
반환: 반환 없음*/
void nickname()
{
    system("cls");
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                    INPUT NICKNAME                   \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n";
    std::cout << ": ";
    std::cin >> name;
    return;
}
/*함수이름: nickname1()
기능: 친구 찾기의 닉네임화면으로 닉네임 입력 시 다음 화면으로 이동
반환: 선택한 친구이름*/
std::string nickname1()
{
    system("cls");
    std::string frien;
    std::string name1;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                 INPUT YOUR NICKNAME                 \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n";
    std::cout << ": ";
    std::cin >> name1;

    strcpy(name, name1.c_str());
    std::string total = "nicklist:";
    total.append(name1);
    send(hSock,total.c_str(), total.size(),0);

    std::string buf;
    std::vector<std::string> result;
    char nameMSG[NAME_SIZE+BUF_SIZE];
    int friendCnt =3;
    while(1)
    {
        recv(hSock,nameMSG,NAME_SIZE+BUF_SIZE-1,0);

        std::istringstream iss(nameMSG);
        while (getline(iss, buf, ','))
        {
            result.push_back(buf);
        }
        frien = friendList(result, friendCnt);
        break;
    }
    closesocket(hSock);
    WSACleanup();
    return frien;
}
/*함수이름: nickname2()
기능: 친구 추가의 닉네임화면으로 닉네임 입력 시 다음 화면으로 이동
반환: 반환 없음*/
void nickname2()
{
    system("cls");
    std::string name2;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                 INPUT YOUR NICKNAME                 \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n";
    std::cout << ": ";
    std::cin >> name2;

    std::string total = "nickplus:";
    total.append(name2);

    std::string plus = friendPlus();
    total.append(":");
    total.append(plus);

    send(hSock,total.c_str(), total.size(),0);

    char servPlus[NAME_SIZE+BUF_SIZE];
    while (1)
    {
        recv(hSock,servPlus,NAME_SIZE+BUF_SIZE-1,0);
        break;
    }
    std::cout << servPlus;
    Sleep(2000);
    closesocket(hSock);
    WSACleanup();
    return;
}
/*함수이름: friendList()
기능: 친구찾기화면으로 친구 선택 시 다음 화면으로 이동
반환: 친구번호 int형 반환*/
std::string friendList(std::vector<std::string> msg, int cnt)
{
    system("cls");
    int j = 0; // 접속상태용
    std::string frien;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                         LIST                        \n";
    std::cout << "=====================================================\n";
    for(int i=0; i<cnt*2; i++)
    {
        std::cout << "NickName: " << msg[i];
        j++;
        std::cout << "  " << msg[j] << "-line" <<std::endl;
        j++;
        i++;
    }
    std::cout << "<back (Q)>\n";
    std::cout << "=====================================================\n";
    std::cout << ": ";
    std::cin >> frien;

    return frien;
}
/*함수이름: friendPlus()
기능: 친구추가화면으로 친구 추가 입력 시 친구 찾기 화면으로 이동
반환: 친구정보 string형 반환*/
std::string friendPlus()
{
    system("cls");
    std::string plus;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                    NEW FRIEND                       \n";
    std::cout << "                    INPUT NICKNAME                   \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n\n";
    std::cout << ": ";
    std::cin >> plus;
    plus.append(":");
    return plus;
}
/*함수이름: friendCheck()
기능: 서버소켓 연결요청 하는 함수
반환: 없음*/
void friendCheck()
{
    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        ErrorHandling("WSAStartup() error!");
    }

    hSock=socket(PF_INET,SOCK_STREAM,0);

    memset(&servAdr,0,sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=inet_addr(server);
    servAdr.sin_port=htons(port);

    if(connect(hSock,(SOCKADDR*)&servAdr,sizeof(servAdr))==SOCKET_ERROR)
    {
        ErrorHandling("coonect() error");
    }
    return;
}
/*함수이름: oneChat()
기능: 일대일 채팅방
반환: 없음*/
void oneChat(std::string frien)
{
    system("cls");
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                      "<< frien << " CHAT            \n";
    std::cout << "=====================================================\n";

    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        ErrorHandling("WSAStartup() error!");
    }

    hSock=socket(PF_INET,SOCK_STREAM,0);

    memset(&servAdr,0,sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=inet_addr(server);
    servAdr.sin_port=htons(port);

    if(connect(hSock,(SOCKADDR*)&servAdr,sizeof(servAdr))==SOCKET_ERROR)
    {
        ErrorHandling("coonect() error");
    }

    hSndThread=(HANDLE)_beginthreadex(NULL,0,SendMSG,(void*)&hSock,0,NULL);
    hRcvThread=(HANDLE)_beginthreadex(NULL,0,RecvMSG,(void*)&hSock,0,NULL);

    WaitForSingleObject(hSndThread,INFINITE);
    WaitForSingleObject(hRcvThread,INFINITE);
    closesocket(hSock);
    WSACleanup();
    return;
}
/*함수이름: onenChat()
기능: 오픈채팅화면으로 비밀번호 입력 시 다음 화면으로 이동
반환: 비밀번호 string 반환*/
int onpePass()
{
    int password;
    system("cls");
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                    INPUT PASSWORD                   \n";
    std::cout << "                                                     \n";
    std::cout << "=====================================================\n";
    std::cout << ": ";
    std::cin >> password;
    return password;
}
/*함수이름: onpeChat(int password)
기능: 오픈채팅화면 일대다채팅방
반환: 비밀번호 string 반환*/
void onpeChat(int password)
{
    system("cls");
    
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                      OPEN CHAT                      \n";
    std::cout << "=====================================================\n";

    if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
    {
        ErrorHandling("WSAStartup() error!");
    }

    hSock=socket(PF_INET,SOCK_STREAM,0);

    memset(&servAdr,0,sizeof(servAdr));
    servAdr.sin_family=AF_INET;
    servAdr.sin_addr.s_addr=inet_addr(server);
    servAdr.sin_port=htons(password);

    if(connect(hSock,(SOCKADDR*)&servAdr,sizeof(servAdr))==SOCKET_ERROR)
    {
        ErrorHandling("coonect() error");
    }

    hSndThread=(HANDLE)_beginthreadex(NULL,0,SendMSG,(void*)&hSock,0,NULL);
    hRcvThread=(HANDLE)_beginthreadex(NULL,0,RecvMSG,(void*)&hSock,0,NULL);

    WaitForSingleObject(hSndThread,INFINITE);
    WaitForSingleObject(hRcvThread,INFINITE);
    closesocket(hSock);
    WSACleanup();
    return;
}
unsigned WINAPI SendMSG(void * arg) //송신
{
    SOCKET hSock=*((SOCKET*)arg);
    while(1)
    {
        fgets(msg,BUF_SIZE,stdin);
        if(!strcmp(msg,"q\n")||!strcmp(msg,"Q\n"))
        {
            closesocket(hSock);
            // exit(0);
            return 0;
        }
        else if(!strcmp(msg,"f\n")||!strcmp(msg,"F\n"))
        {
            file(hSock);
            return 0;
        }

        std::string total = name;
        total.append(": ");
        total.append(msg);
        send(hSock,total.c_str(), total.size(),0);
    }
    return 0;
}
unsigned WINAPI RecvMSG(void* arg) //수신
{
    // int hSock=*((SOCKET*)arg);
    SOCKET hSock=*((SOCKET*)arg);
    char nameMSG[NAME_SIZE+BUF_SIZE];
    int strLen=0;
    std::string str;

    // while(1)
    // {
    //     strLen=recv(hSock,nameMSG,NAME_SIZE+BUF_SIZE-1,0);
    //     if(strLen==-1) return -1;
    //     nameMSG[strLen]=0;
    //     fputs(nameMSG,stdout);

        // std::istringstream iss(msg);
        // std::string buf;
        // std::vector<std::string> result;
        // while (getline(iss, buf, ':'))
        // {
        //     result.push_back(buf);
        // }
        // if(result[1] == " file")
        // { 
        //     fp=fopen("FILE2.txt", "w");
        //     if (fp == NULL) 
        //     {
        //         fprintf(stderr, "File Open Error...\n"); // 파일 열기 실패 시 에러 메시지 출력
        //         exit(1);
        //     }
        //     fputs(result[2].c_str(),fp);
        //     fclose(fp);
        // }
    // }
    // return 0;
    while ((strLen=recv(hSock,nameMSG,sizeof(nameMSG),0)) !=0)
    {
        std::istringstream iss(str=nameMSG);
        std::string buf;
        std::vector<std::string> result;

        while (getline(iss, buf, ':'))
        {
            result.push_back(buf);
        }
        if(result[0] == "file")
        { 
            FILE *fp = fopen("FILE2.txt", "w");
            if (fp == NULL) 
            {
                fprintf(stderr, "File Open Error...\n"); // 파일 열기 실패 시 에러 메시지 출력
                exit(1);
            }
            std::cout << result[1];
            fputs(result[1].c_str(),fp);
            fclose(fp);
            std::cout << "파일을 저장하였습니다" <<std::endl;
        }
        else
        {
            std::cout << "[" << result[0] << "]" << result[1];
        }
    }
    return 0;
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

void file(SOCKET Now)
{
    FILE *fp;
    fp=fopen("FILE.txt", "r");
    if (fp == NULL) {
        fprintf(stderr, "File Open Error...\n"); // 파일 열기 실패 시 에러 메시지 출력
        exit(1);
    }
    char lines[MAX_LINES][MAX_LINE_LENGTH]; // 파일에서 읽은 각 줄을 저장하는 2차원 배열
    int line_count = 0; // 파일에서 읽은 줄의 수를 저장하는 변수

    // 파일에서 각 줄을 읽어 lines 배열에 저장
    while (fgets(lines[line_count], MAX_LINE_LENGTH, fp) != NULL) 
    {
        if (line_count < MAX_LINES - 1) 
        {
            line_count++;
        } 
        else 
        {
            fprintf(stderr, "Arr Over Error...\n"); // 배열 크기 초과 시 에러 메시지 출력
            break;
        }
    }
    //저장한 파일 내용 송신
    std::string file = "file:";
    for(int i =0; i <line_count; i++)
    {
        file.append(lines[i]);    
    }
    send(Now,file.c_str(),file.size(),0);
    std::cout << file << std::endl;
    std::cout << "파일을 송신하였습니다.\n";
    fclose(fp);
    return;
}
