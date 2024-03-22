#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define BUF_SIZE 10000
#define BUF 5000
#define Buf 5000
#define BUFFF 5000

struct Menuitem {
    char name[50];
    int money;
};

void error_handling(char *message);

int main(int argc, char *argv[]) 
{
    argc = 2;
    argv[1] = "10000"; 

    if (argc != 2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    int serv_sock, clnt_sock;
    struct sockaddr_in serv_addr, clnt_addr;
    socklen_t clnt_addr_size;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1){
        error_handling("socket() error");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1){
        error_handling("bind() error");
    }

    if (listen(serv_sock, 5) == -1){
        error_handling("listen() error");
    }
    else{
        printf("연결이 가능한 상태입니다.\n");
    }

    clnt_addr_size = sizeof(clnt_addr);

    struct Menuitem menu[7] = {
        {"레몬 파운드 케이크", 12000},
        {"무화과 파운드 케이크", 14000},
        {"초코 파운드 케이크", 10000},
        {"녹차 파운드 케이크", 11000},
        {"얼그레이 파운드 케이크", 13000},
        {"딸기 파운드 케이크", 15000},
        {"딸기 생크림 케이크", 17000}
    };

    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
        if (clnt_sock == -1)
            error_handling("accept() error");

    while (1){
        char menu_msg[BUF_SIZE];
        char msg[BUF];
        char Msg[Buf];
        int choice;

        // 메뉴 및 가격 송신
        sprintf(menu_msg, "1) %s_%d원\n2) %s_%d원\n3) %s_%d원\n4) %s_%d원\n5) %s_%d원\n6) %s_%d원\n7) %s_%d원\n",
                menu[0].name, menu[0].money,
                menu[1].name, menu[1].money,
                menu[2].name, menu[2].money,
                menu[3].name, menu[3].money,
                menu[4].name, menu[4].money,
                menu[5].name, menu[5].money,
                menu[6].name, menu[6].money);

        write(clnt_sock, menu_msg, strlen(menu_msg));

        // 클라이언트가 선택한 메뉴와 가격 수신
        int clnt_menu;
        read(clnt_sock, &clnt_menu, sizeof(clnt_menu));   

        // 선택한 메뉴와 가격 저장
        char clnt_menu_str[50];
        sprintf(clnt_menu_str, "\n%s_%d원", menu[clnt_menu - 1].name, menu[clnt_menu - 1].money);

        // 메뉴 가격 문구 송신
        sprintf(msg,"\n고객님의 선택: %s\n", clnt_menu_str);
        write(clnt_sock, msg, strlen(msg));
        fputs(msg, stdout);

        // 결제 또는 추가 여부 수신
        read(clnt_sock, &choice, sizeof(choice));

        if (choice == 1){
            // 결제하기 선택 시_ 예약 완료 메시지 송신
            fputs("결제하기를 선택하였습니다. 예약프로그램이 종료됩니다.\n", stdout);
            
            sprintf(Msg, "\n선택하신 메뉴: \n");
            for(int i=0; i<clnt_menu-1; i++){
                sprintf(Msg+strlen(Msg), "%s_%d원\n", menu[i].name, menu[i].money);
            }

            sprintf(Msg+strlen(Msg),"%s\n\n예약이 완료되었습니다.\n이용해 주셔서 감사합니다:)\n", clnt_menu_str);
            
            write(clnt_sock, Msg, strlen(Msg));
            break;
        } 
        else if (choice == 2){
            // 추가하기 선택 시_ 다시 메뉴 송신
            fputs("메뉴 추가하기를 선택하였습니다.", stdout);
            continue;
        } 
        else{
            // 잘못된 선택일 경우 에러 메시지 송신
            strcpy(menu_msg, "결제하기 또는 메뉴 추가하기를 선택해주세요.");
            write(clnt_sock, menu_msg, strlen(menu_msg));
        }
    }

    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
