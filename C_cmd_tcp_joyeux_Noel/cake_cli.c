#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 10000
#define BUF 5000
#define buf 5000
#define mBUF 5000
Arr[BUF_SIZE]={0};

void error_handling(char *message);

int main(int argc, char *argv[]) 
{
    argc = 3;
    argv[1] = "10.10.20.99";
    argv[2] = "1000";

    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    int sock;
    struct sockaddr_in serv_addr;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error");

    while (1)
    {
        char message[BUF_SIZE];
        char msg[buf];
        char magmag[mBUF];
        int choice;
        int clnt_menu;

        // 메뉴 및 가격 수신 및 출력
        read(sock, message, BUF_SIZE);
        printf("----------Menu----------\n%s", message);
        printf("메뉴를 선택해주세요: ");
        scanf("%d", &clnt_menu);

        // 선택한 메뉴 번호 송신
        write(sock, &clnt_menu, sizeof(clnt_menu));

        // 선택한 메뉴와 가격 수신
        read(sock, msg, buf);
        printf("%s\n", msg);

        // 결제 또는 추가 여부 입력 및 송신
        printf("1)결제하기\n2)메뉴 추가하기\n: ");
        scanf("%d", &choice);
        write(sock, &choice, sizeof(choice));

        if (choice == 1) {
            // 결제하기 선택 시_ 예약 완료 메시지 수신 및 출력
            read(sock, magmag, mBUF);
            printf("%s\n", magmag);

            break;
        }
        else if (choice == 2){
            // 메뉴 추가하기 선택 시_다시 메뉴 수신
            continue;
        }
    }
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
