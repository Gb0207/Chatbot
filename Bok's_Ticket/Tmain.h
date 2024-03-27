#ifndef __TMAIN_H__
#define __TMAIN_H__

/*
클래스 이름 : Tmain
유저의 아이디, 패스워드, 이메일, 전화번호를 저장
*/
class Tmain
{  

public:
	void fpage(); //start page
    int LoginMenu(); //login menu page
    int Signin(); //login page
    void Forgotid(); //Forgotid page
    void Forgotpw(); //Forgotpw page
    int CreateAccount(); //CreateAccount page
    int showMenu(); //menu page/print and get
    int run(int selMenuNum); //get menu print
    int MakeReservation(); //make a reservation page
    int AreaReservation(int PlanAp); //Area reservation page
    void showReservedTicket(); //showReservedTicket page
};

#endif