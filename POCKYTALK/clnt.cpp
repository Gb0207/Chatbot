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
#define MAX_LINES 1000 //���Ͽ�
#define MAX_LINE_LENGTH 100 //���Ͽ�

int startMenu(); //����ȭ��
int chatting(); //ä�ü���ȭ��
int oneToOne(); //����ä��ȭ�� ģ�� ã�� �� ģ�� �߰� ����
int onpePass(); //����ä��ȭ�� ��й�ȣ�Է�ȭ��
void nickname(); //����ä���� �г���ȭ�� �г����Է�ȭ��
std::string nickname1(); //ģ��ã���� �г���ȭ�� �г����Է�ȭ��
void nickname2(); //ģ���߰��� �г���ȭ�� �г����Է�ȭ��
std::string friendList(std::vector<std::string> msg, int cnt); //ģ��ã��ȭ�� ģ�� ���� ���� �� ģ������ȭ��
std::string friendPlus(); //ģ���߰�ȭ�� ģ�������߰� �Է�ȭ��
void oneChat(std::string); //�ϴ��� ä��ȭ��
void onpeChat(int password); //����ä��ȭ��
void file(SOCKET Now); //���� �۽�
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
                        if (oneToOne() == 1) //ģ��ã��
                        {
                            std::string frien = nickname1();
                            if(frien == "q" || frien == "Q")
                            {
                                continue;
                            }
                            oneChat(frien);
                        }
                        else if(oneToOne() == 2) //ģ���߰�
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
                            std::cout << "�߸��Է��Ͽ����ϴ�." <<std::endl;
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
                            std::cout << "�߸��Է��Ͽ����ϴ�." << std::endl;
                            Sleep(1000);
                            continue;
                        }
                    }
                }
                else
                {
                    std::cout << "�߸��Է��Ͽ����ϴ�." <<std::endl;
                    Sleep(1000);
                    continue;
                }
            }  
        }   
        else if (startMenu() == 0)
        {
            std::cout << "���α׷��� �����մϴ�." << std::endl;
            break;
        }
        else
        {
            std::cout << "�߸��Է��Ͽ����ϴ�." << std::endl;
            continue;
        }
    }
    return 0;
}
/*�Լ��̸�: startMenu()
���: ����ȭ������ �Է� �� ���� ȭ������ �̵�
��ȯ: 1.ä�ü���ȭ�� 2.���α׷� ���� int�� ��ȯ*/
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
/*�Լ��̸�: chatting()
���: ä�ü���ȭ������ ������� �Ǵ� ������� ���� �� ���� ȭ������ �̵�
��ȯ: 1.�������ȭ�� 2.����ä�ù� int�� ��ȯ*/
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
/*�Լ��̸�: oneToOne()
���: �������ȭ������ ģ��ã�� �� ģ�� �߰� ���� �� ���� ȭ������ �̵�
��ȯ: ģ����ȣ int�� ��ȯ*/
int oneToOne()
{
    system("cls");
    int onechat;
    std::cout << "\n";    
    std::cout << "=====================================================\n"; 
    std::cout << "                                                     \n";
    std::cout << "                     1. ģ�� ã��                     \n";
    std::cout << "                     2. ģ�� �߰�                     \n";
    std::cout << "                     3. �ڷ�                          \n";
    std::cout << "                                                      \n";
    std::cout << "=====================================================\n\n";
    std::cin >> onechat;
    return onechat;
}
/*�Լ��̸�: nickname()
���: ����ä�ù��� �г���ȭ������ �г��� �Է� �� ���� ȭ������ �̵�
��ȯ: ��ȯ ����*/
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
/*�Լ��̸�: nickname1()
���: ģ�� ã���� �г���ȭ������ �г��� �Է� �� ���� ȭ������ �̵�
��ȯ: ������ ģ���̸�*/
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
/*�Լ��̸�: nickname2()
���: ģ�� �߰��� �г���ȭ������ �г��� �Է� �� ���� ȭ������ �̵�
��ȯ: ��ȯ ����*/
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
/*�Լ��̸�: friendList()
���: ģ��ã��ȭ������ ģ�� ���� �� ���� ȭ������ �̵�
��ȯ: ģ����ȣ int�� ��ȯ*/
std::string friendList(std::vector<std::string> msg, int cnt)
{
    system("cls");
    int j = 0; // ���ӻ��¿�
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
/*�Լ��̸�: friendPlus()
���: ģ���߰�ȭ������ ģ�� �߰� �Է� �� ģ�� ã�� ȭ������ �̵�
��ȯ: ģ������ string�� ��ȯ*/
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
/*�Լ��̸�: friendCheck()
���: �������� �����û �ϴ� �Լ�
��ȯ: ����*/
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
/*�Լ��̸�: oneChat()
���: �ϴ��� ä�ù�
��ȯ: ����*/
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
/*�Լ��̸�: onenChat()
���: ����ä��ȭ������ ��й�ȣ �Է� �� ���� ȭ������ �̵�
��ȯ: ��й�ȣ string ��ȯ*/
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
/*�Լ��̸�: onpeChat(int password)
���: ����ä��ȭ�� �ϴ��ä�ù�
��ȯ: ��й�ȣ string ��ȯ*/
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
unsigned WINAPI SendMSG(void * arg) //�۽�
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
unsigned WINAPI RecvMSG(void* arg) //����
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
        //         fprintf(stderr, "File Open Error...\n"); // ���� ���� ���� �� ���� �޽��� ���
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
                fprintf(stderr, "File Open Error...\n"); // ���� ���� ���� �� ���� �޽��� ���
                exit(1);
            }
            std::cout << result[1];
            fputs(result[1].c_str(),fp);
            fclose(fp);
            std::cout << "������ �����Ͽ����ϴ�" <<std::endl;
        }
        else
        {
            std::cout << "[" << result[0] << "]" << result[1];
        }
    }
    return 0;
}
/*�Լ��̸�: ErrorHandling()
���: �����߻� �� ����ϴ� �Լ�
��ȯ: ����*/
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
        fprintf(stderr, "File Open Error...\n"); // ���� ���� ���� �� ���� �޽��� ���
        exit(1);
    }
    char lines[MAX_LINES][MAX_LINE_LENGTH]; // ���Ͽ��� ���� �� ���� �����ϴ� 2���� �迭
    int line_count = 0; // ���Ͽ��� ���� ���� ���� �����ϴ� ����

    // ���Ͽ��� �� ���� �о� lines �迭�� ����
    while (fgets(lines[line_count], MAX_LINE_LENGTH, fp) != NULL) 
    {
        if (line_count < MAX_LINES - 1) 
        {
            line_count++;
        } 
        else 
        {
            fprintf(stderr, "Arr Over Error...\n"); // �迭 ũ�� �ʰ� �� ���� �޽��� ���
            break;
        }
    }
    //������ ���� ���� �۽�
    std::string file = "file:";
    for(int i =0; i <line_count; i++)
    {
        file.append(lines[i]);    
    }
    send(Now,file.c_str(),file.size(),0);
    std::cout << file << std::endl;
    std::cout << "������ �۽��Ͽ����ϴ�.\n";
    fclose(fp);
    return;
}
