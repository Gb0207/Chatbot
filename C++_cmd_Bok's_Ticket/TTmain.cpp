#include <iostream>
#include "Tmain.h"
using namespace std;

/*
함수 이름: main
모든 화면 전환 기능을 수행
반환값: 0
*/
int main()
{
    Tmain tmain;
    int whiln1 =2;
    int whiln2 =2;

    tmain.fpage();
	
    while(whiln1 !=1)
    {
        int loginNum = tmain.LoginMenu();
        if(loginNum == 1)
        {
            int loginresult = tmain.Signin();
            if(loginresult == 1)
            {
                break;
            }
            else if(loginresult == 2)
            {
                continue;
            }
        }
        if(loginNum == 2)
        {
            tmain.Forgotid(); 
            tmain.Forgotpw(); 
            tmain.Signin();
            break;
        }
        if(loginNum == 3)
        {
            tmain.Forgotpw(); 
            tmain.Signin();
            break;
        }
        if(loginNum == 4)
        {
            tmain.CreateAccount(); 
            continue;
        }
    } 
    while (whiln2 !=1)
    {
        int selMenuNum = tmain.showMenu();
        int runReturn = 0;
        int Resnot = 0;
        if(selMenuNum == 5) //경기예약하기 화면으로
        {
            int PlanAp = tmain.MakeReservation();
            Resnot = tmain.AreaReservation(PlanAp); 
            if(Resnot == 1)
            {
                continue;
            }
        }
        if(selMenuNum == 6) //예약확인 화면으로
        {
            tmain.showReservedTicket();
            continue;
        }
        else if(selMenuNum !=5 && selMenuNum !=6)
        {
            runReturn = tmain.run(selMenuNum);
        }
        if(runReturn == 1)
        {
            continue;
        }
        if(runReturn == 2)
        {
            break;
        }
    }
    return 0;
}