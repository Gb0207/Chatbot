#include <iostream> //입출력
#include <fstream> //input file stream
#include <sstream> //istringstream ss(now);
#include <cstdlib> // rand()
#include <cstring>
#include <vector>
#include <termio.h> //getch() clear, sleep
#include <time.h> // rand(seed
#include <unistd.h> //getch() clear, sleep

#include "Tmain.h"

using namespace std;

/*
함수 이름: fpage
시작화면 아스키아트 출력 및 엔터입력시 메뉴화면으로 전환
반환값: 없음
*/
void Tmain::fpage()
{ 
    char phsh; 
	while (phsh != 10)
	{
		cout << "\x1b[44m======================================================================================================" <<endl;
		cout << "  ____               __          __            ______                   __                  __        " << endl;
		cout << " /\\  _`\\            /\\ \\        /\\ \\          /\\__  _\\   __            /\\ \\                /\\ \\__     " << endl;
		cout << " \\ \\ \\L\\ \\    ___   \\ \\ \\/'\\    \\ \\/  ____    \\/_/\\ \\/  /\\_\\     ___   \\ \\ \\/'\\       __   \\ \\ ,_\\    " << endl;
		cout << "  \\ \\  _ <'  / __`\\  \\ \\ , <     \\/  /',__\\      \\ \\ \\  \\/\\ \\   /'___\\  \\ \\ , <     /'__`\\  \\ \\ \\/    " << endl;
		cout << "   \\ \\ \\L\\ \\/\\ \\L\\ \\  \\ \\ \\`\\       /\\__, `\\      \\ \\ \\  \\ \\ \\ /\\ \\__/   \\ \\ \\`\\  /\\  __/    \\ \\ \\_   " << endl;
		cout << "    \\ \\____/\\ \\____/   \\ \\_\\ \\_\\    \\/\\____/       \\ \\_\\  \\ \\_\\\\ \\____\\   \\ \\_\\ \\_\\\\ \\____\\   \\ \\__\\  " << endl;
		cout << "     \\/___/  \\/___/     \\/_/\\/_/     \\/___/         \\/_/   \\/_/ \\/____/    \\/_/\\/_/ \\/____/    \\/__/  " << endl;
		cout << "                                                                                                      " <<endl;
		cout << "======================================================================================================" <<endl;
		cout << "============================================ ENTER PUSH ==============================================" <<endl; 
		cout << "======================================================================================================" <<endl;
		cin.get(phsh);
	}
	system ("clear");
}
/*
함수 이름: LoginMenu
로그인 목록 보여주고 메뉴 선택받는 함수
반환값: 선택된 메뉴 번호 반환
*/
int Tmain::LoginMenu()
{
	int loginNum;
	int a =0;
	while(a == 0)
	{
		cout << "======================================================================================================" <<endl;
		cout << "===================================== Welcome to Bok's Ticket ========================================" <<endl;
		cout << "======================================================================================================" <<endl;
		cout << endl;
		cout << endl;
		cout << "\t\t\t1) SIGN IN" << endl;
		cout << "\t\t\t2) FORGOT ID?" << endl;
		cout << "\t\t\t3) FORGOT PW?" << endl;
		cout << "\t\t\t4) CREATE ACCOUNT" << endl;
		cout << endl;
		cout << endl;
		cout << "======================================================================================================" <<endl;
		cout << "\t\t\t: ";
		cin >> loginNum;
		if(loginNum >=5 || loginNum <= 0)
		{
			cout << "잘못입력하였습니다" << endl;
			sleep(1); 
			system ("clear");
		}
		if(loginNum == 1 ||loginNum == 2 ||loginNum == 3 ||loginNum == 4)
		{
			a++;
			system ("clear");
			return loginNum;
		}
	}	
}
/*
함수 이름: Signin
로그인 입력
반환값: 1이면 로그인 성공 2이면 실패
*/
int Tmain::Signin()
{
	char ID[50];
	char PW[50];
	int loginresult;
	vector<string>UserDataTexe;
	int len = static_cast<int>(UserDataTexe.size());
	vector<string> result;

	cout << endl;
	cout << "======================================================================================================" <<endl;
	cout << "============================================= SIGN IN ================================================" <<endl; 
	cout << "======================================================================================================" <<endl;
	cout << endl << endl;
	cout << "\t\t\tID : ";
	cin >> ID;
	cout << endl;
	cout << "\t\t\tPW : ";
	cin >> PW;
	cout << endl;
	cout << "======================================================================================================" <<endl;
	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("UserData.txt"); //file open
	if(readFile.is_open())
	{
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string str;
			getline(readFile,str); //한줄씩 읽어오기
			UserDataTexe.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserDataTexe.size(); i++)
	{
        // 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserDataTexe[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            result.push_back(buffer);
		}
	}
	for (size_t i = 0; i < result.size(); i++)
	{
		if(ID == result[i] && PW == result[i+1])
		{
			cout << "\tWelcome to Bok's Ticket"<< endl;
			loginresult = 1;
			break;
		}
		if(ID != result[i])
		{
			if(i == (result.size()-1))
			{
				cout << "\tCouldn't find your Bok's Ticket Account" << endl;
				loginresult = 2;
				continue;
			}
		}
	}
	return loginresult;
}
/*
함수 이름: Forgotid
파일에 저장된 데이터에서 입력한 이메일로 아이디 출력 
반환값: 없음
*/
void Tmain::Forgotid()
{
	string femail;
	vector<string>UserDataTexe;
	int len = static_cast<int>(UserDataTexe.size());
	vector<string> result;

	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("UserData.txt"); //file open
	if(readFile.is_open())
	{
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string str;
			getline(readFile,str); //한줄씩 읽어오기
			UserDataTexe.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserDataTexe.size(); i++)
	{
        // 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserDataTexe[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            result.push_back(buffer);
		}
	}
	
	cout << "======================================================================================================" <<endl;
	cout << "=========================================== FORGOT ID ================================================" <<endl; 
	cout << "======================================================================================================" <<endl;
	cout << endl << endl;
	int a=0;
	while (a == 0)
	{
		cout << "\t\t\tEMAIL : ";
		cin >> femail;
		for (size_t i = 0; i < result.size(); i++)
		{
			if(femail == result[i])
			{
				cout << "\t회원입니다"<<"\tID :"<< result[i-2] << endl;
				a = 1;
				break;
			}
			if(femail != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t없는 정보입니다" << endl;
					a=0;
					break;
				}
			}
		}
	}
} 
/*
함수 이름: Forgotpw
파일에 저장된 데이터에서 입력한 아이디로 비밀번호 출력 
반환값: 
*/
void Tmain::Forgotpw()
{
	string fid;
	vector<string>UserDataTexe;
	int len = static_cast<int>(UserDataTexe.size());
	vector<string> result;

	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("UserData.txt"); //file open
	if(readFile.is_open())
	{
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string str;
			getline(readFile,str); //한줄씩 읽어오기
			UserDataTexe.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserDataTexe.size(); i++)
	{
        // 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserDataTexe[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            result.push_back(buffer);
		}
	}
	cout << "======================================================================================================" <<endl;
	cout << "=========================================== FORGOT PW ================================================" <<endl; 
	cout << "======================================================================================================" <<endl;
	cout << endl << endl;
	int a=0;
	while (a == 0)
	{
		cout << "\t\t\tID : ";
		cin >> fid;
		for (size_t i = 0; i < result.size(); i++)
		{
			if(fid == result[i])
			{
				cout << "\t회원입니다"<< "\tPW :" << result[i+1] << endl;
				a = 1;
				break;
			}
			if(fid != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t없는 정보입니다" << endl;
					a=0;
					break;
				}
			}
		}
	}
}
/*
함수 이름: CreateAccoount
회원가입하는 페이지, 아이디, 비밀번호, 이메일, 전화번호, 회원번호를 파일에 저장하는 함수
반환값: 
*/
int Tmain::CreateAccount()
{
	string ID; //회원가입 아이디
	string PW; //회원가입 비밀번호
	string EMAIL; //회원가입 이메일
	string PHONE; //회원가입 핸드폰번호

	srand(time(NULL)); //랜덤함수
	string full; //회원번호 인트에서 스트링으로 변환 후 저장
	int Un = (rand()%100000)+100000; // 회원가입 회원번호
	full = to_string(Un); //회원번호 인트에서 스트링 변환
	
	vector<string>UserDataTexe;
	int len = static_cast<int>(UserDataTexe.size());
	vector<string> result;

	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("UserData.txt"); //file open
	if(readFile.is_open())
	{
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string str;
			getline(readFile,str); //한줄씩 읽어오기
			UserDataTexe.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	else
	{
		ofstream writeToFile; //파일이 없는 경우 생성하기
		writeToFile.open("UserData.txt");
		for(int i=0; i<len; i++)
		{
			string tmp = UserDataTexe[i];
			if(i != len -1)
			{
				tmp += "\n"; //마지막 단어 빼고 엔터 넣어주기
			}
			writeToFile.write(tmp.c_str(), tmp.size()); //tmp.c_str() : C++ string -> const char* 타입으로 변환
		}
		writeToFile.close(); //파일 닫기
	}
	for(int i=0; i<UserDataTexe.size(); i++)
	{
		string now = UserDataTexe[i];
		istringstream ss(now);
		string buffer;
		
		while (getline(ss, buffer, '/'))
		{
			result.push_back(buffer);
		}
	}

	cout << endl;
	cout << "======================================================================================================" <<endl;
	cout << "========================================= CREATE ACCOUNT =============================================" <<endl; 
	cout << "======================================================================================================" <<endl;
	cout << endl << endl;
	//대충와일문돌릴용abcd
	int a =0;
	int b =0;
	int c =0;
	int d =0;
	
	while (a == 0)
	{
		cout << "\t\t\tID : ";
		cin >> ID;
		for (size_t i = 0; i < result.size(); i++)
		{
			if(ID != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t사용 가능한 아이디입니다." << endl;
					a=1;
					break;
				}
			}
			if(ID == result[i])
			{
				cout << "\t중복된 아이디입니다. 다시 입력해주세요"<< endl;
				break;
			}
		}
	}
	cout << "\t\t\tPW : ";
	cin >> PW;
	while (b == 0)
	{
		cout << "\t\t\tEMAIL : ";
		cin >> EMAIL;
		for (size_t i = 0; i < result.size(); i++)
		{
			if(EMAIL != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t사용 가능한 이메일입니다." << endl;
					b=1;
					break;
				}
			}
			if(EMAIL == result[i])
			{
				cout << "\t중복된 이메일입니다. 다시 입력해주세요"<< endl;
				break;
			}
		}
	}
	while (c == 0)
	{
		cout << "\t\t\tPHONE : ";
		cin >> PHONE;
		for (size_t i = 0; i < result.size(); i++)
		{
			if(PHONE != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t사용 가능한 전화번호입니다." << endl;
					c=1;
					break;
				}
			}
			if(PHONE == result[i])
			{
				cout << "\t중복된 전화번호입니다. 다시 입력해주세요"<< endl;
				break;
			}
		}
	}
	while (d == 0)
	{
		for (size_t i = 0; i < result.size(); i++)
		{
			if(full == result[i])
			{
				cout << "\t회원번호를 지정하고 있습니다" << endl;
				int Un = (rand()%100000)+100000; // 회원가입 회원번호
				full = to_string(Un); //회원번호 인트에서 스트링 변환
				break;
			}
		}
		cout << "\t회원가입하였습니다" << endl;
		d = 1;
	}
	cout << "======================================================================================================" <<endl;
	system ("clear");
	ofstream writeFile; //쓸 목적의 파일 선언
	writeFile.open("UserData.txt", ios::app); //파일 열고 이어쓰기
	writeFile << ID << "/" << PW << "/" << EMAIL << "/" << PHONE << "/" << full << "/" << endl;
	writeFile.close(); //파일 닫기
}
/*
함수 이름: showMenu
메뉴를 보여주고 메뉴를 입력받음
반환값: 메뉴 선택 정수
*/
int Tmain::showMenu()
{
    int selMenuNum=0;
	cout << "======================================================================================================" <<endl;
	cout << "============================================== MENU ==================================================" << endl;
	cout << "======================================================================================================" <<endl;
	cout << "\t\t\t1) 경기 기본 정보" << endl;
	cout << "\t\t\t2) 참가국 및 조별 정보" << endl;
	cout << "\t\t\t3) 조별 경기 일정" << endl;
	cout << "\t\t\t4) 한국 감독/ 선수 명단, 선수 정보" << endl;
	cout << "\t\t\t5) 경기 예약" << endl;
	cout << "\t\t\t6) 예약 확인" << endl;
	cout << "\t\t\t7) 종료 하기" << endl;
	cout << "======================================================================================================" <<endl;
	cout << "\t\t\t: ";
	cin >> selMenuNum;		
	system ("clear");
	return selMenuNum;
}
/*
함수 이름: run
메뉴 입력 받은 목록 출력
반환값: 없음
*/
int Tmain::run(int selMenuNum)
{
	if (selMenuNum == 1)
	{
		char phsh1;
		while (phsh1 != 10)
		{// 경기 기본 정보
			cout << "======================================================================================================" <<endl;
			cout << "========================================== BASIC INFORMATION =========================================" <<endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t기간 : 2024년 1월 12일(금) ~ 2월 10일(일) (현지기준)" << endl;
			cout << "\t\t\t개최지 : 카타르 도하, 알 와크라, 알 라이얀, 알 코르" << endl;
			cout << "\t\t\t중계 : tvN, tvN SPORTS, 쿠팡플레이" << endl;
			cin.get(phsh1);
		}
		return 1;
	}
	else if (selMenuNum == 2)
	{// 참가국 및 조별 정보
		char phsh2;
		while (phsh2 != 10)
		{
			cout << "======================================================================================================" <<endl;
			cout << "====================================== PARTICIPATING COUNTRIES =======================================" <<endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\tA 카타르 중국 타지키스탄 레바논" << endl;
			cout << "\t\t\tB 호주 우즈베키스탄 시리아 인도" << endl;
			cout << "\t\t\tC 이란 아랍에미리트 홍콩 팔레스타인" << endl;
			cout << "\t\t\tD 일본 인도네시아 이라크 베트남" << endl;
			cout << "\t\t\tE 대한민국 말레이시아 요르단 바레인" << endl;
			cout << "\t\t\tF 사우디아라비아 태국 키르기스스탄 오만" << endl;
			cin.get(phsh2);
		}
		return 1;
	}
	else if (selMenuNum == 3)
	{// 조별 경기 일정
		int choice=0;
		cout << "======================================================================================================" <<endl;
		cout << "=========================================== GROUP SCHEDULE ===========================================" << endl;
		cout << "======================================================================================================" <<endl;
		cout << "\t\t\t1) A" << endl;
		cout << "\t\t\t2) B" << endl;
		cout << "\t\t\t3) C" << endl;
		cout << "\t\t\t4) D" << endl;
		cout << "\t\t\t5) E" << endl;
		cout << "\t\t\t6) F" << endl;
		cout << "======================================================================================================" <<endl;
		cout << "\t\t\t: ";
		cin >> choice;
		system ("clear");
		switch (choice)
		{
		case 1:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP A SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 13일(토) 01:00  카타르 vs 레바논" << endl;
			cout << "\t\t\t2024년 1월 13일(토) 23:30  중국 vs 타지키스탄" << endl;
			cout << "\t\t\t2024년 1월 17일(수) 20:30  레바논 vs 중국" << endl;
			cout << "\t\t\t2024년 1월 17일(수) 23:30  타지키스탄 vs 카타르" << endl;
			cout << "\t\t\t2024년 1월 23일(화) 00:00  타지키스탄 vs 레바논" << endl;
			cout << "\t\t\t2024년 1월 23일(화) 00:00  카타르 vs 중국" << endl;
			break;
		case 2:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP B SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 13일(토) 20:30  호주 vs 인도" << endl;
			cout << "\t\t\t2024년 1월 14일(일) 02:30  우즈베키스탄 vs 시리아" << endl;
			cout << "\t\t\t2024년 1월 18일(목) 20:30  시리아 vs 호주" << endl;
			cout << "\t\t\t2024년 1월 18일(목) 23:30  인도 vs 우즈베키스탄" << endl;
			cout << "\t\t\t2024년 1월 23일(화) 20:30  시리아 vs 인도" << endl;
			cout << "\t\t\t2024년 1월 23일(화) 20:30  호주 vs 우즈베키스탄" << endl;
			break;
		case 3:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP C SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 14일(일) 23:30  아랍에미리트 vs 홍콩" << endl;
			cout << "\t\t\t2024년 1월 15일(월) 02:30  이란 vs 팔레스타인" << endl;
			cout << "\t\t\t2024년 1월 19일(금) 02:30  팔레스타인 vs 아랍에미리트" << endl;
			cout << "\t\t\t2024년 1월 20일(토) 02:30  홍콩 vs 이란" << endl;
			cout << "\t\t\t2024년 1월 24일(수) 00:00  홍콩 vs 팔레스타인" << endl;
			cout << "\t\t\t2024년 1월 24일(수) 00:00  이란 vs 아랍에미리트" << endl;
			break;
		case 4:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP D SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 14일(일) 20:30  일본 vs 베트남" << endl;
			cout << "\t\t\t2024년 1월 15일(월) 23:30  인도네시아 vs 이라크" << endl;
			cout << "\t\t\t2024년 1월 19일(금) 20:30  이라크 vs 일본" << endl;
			cout << "\t\t\t2024년 1월 19일(금) 23:30  베트남 vs 인도네시아" << endl;
			cout << "\t\t\t2024년 1월 24일(수) 23:30  일본 vs 인도네시아" << endl;
			cout << "\t\t\t2024년 1월 24일(수) 20:30  이라크 vs 베트남" << endl;
			break;
		case 5:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP E SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 15일(월) 20:30  대한민국 vs 바레인" << endl;
			cout << "\t\t\t2024년 1월 16일(화) 02:30  말레이시아 vs 요르단" << endl;
			cout << "\t\t\t2024년 1월 20일(토) 20:30  요르단 vs 대한민국" << endl;
			cout << "\t\t\t2024년 1월 20일(토) 23:30  바레인 vs 말레이시아" << endl;
			cout << "\t\t\t2024년 1월 25일(목) 20:30  대한민국 vs 말레이시아" << endl;
			cout << "\t\t\t2024년 1월 25일(목) 20:30  요르단 vs 바레인" << endl;
			break;
		case 6:
			cout << "======================================================================================================" <<endl;
			cout << "========================================== GROUP F SCHEDULE ==========================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "\t\t\t2024년 1월 16일(화) 23:30  태국 vs 키르기스스탄" << endl;
			cout << "\t\t\t2024년 1월 17일(수) 02:30  사우디아라비아 vs 오만" << endl;
			cout << "\t\t\t2024년 1월 21일(일) 23:30  오만 vs 태국" << endl;
			cout << "\t\t\t2024년 1월 22일(월) 02:30  키르기스스탄 vs 사우디아라비아" << endl;
			cout << "\t\t\t2024년 1월 26일(금) 00:00  키르기스스탄 vs 오만" << endl;
			cout << "\t\t\t2024년 1월 26일(금) 00:00  사우디아라비아 vs 바레인" << endl;
			break;
		}
		return 1;
	}
    else if (selMenuNum == 4) 
	{// 한국 감독과 선수 명단 및 선수 정보
		char phsh4;
		while (phsh4 != 10)
		{
			cout << "======================================================================================================" <<endl;
			cout << "============================================= KOREA TEAM =============================================" << endl;
			cout << "======================================================================================================" <<endl;
			cout << "    감독 : 위르겐 클린스만  수석코치 : 안드레아스 헤어초크  코치 : 파올로 스트링가라  코치 : 차두리 " << endl;
			cout << "    FW 오현규 183cm/72kg  MF 이강인 174cm/72kg  DF 김지수 189cm/73kg  DF 김태환 177cm/72kg  " << endl;
			cout << "    FW 정우영 180cm/70kg  MF 이순민 178cm/73kg  DF 김진수 177cm/68kg  DF 박진섭 182cm/75kg  " << endl;
			cout << "    FW 조규성 189cm/82kg  MF 이재성 180cm/70kg  DF 김민재 190cm/88kg  GK 김승규 187cm/84kg  " << endl;
			cout << "    MF 문선민 172cm/68kg  MF 홍현석 175cm/66kg  DF 김영권 186cm/83kg  GK 송범근 194cm/88kg  " << endl;
			cout << "    MF 박용우 186cm/79kg  MF 황인범 177cm/70kg  DF 김주성 186cm/76kg  GK 조현우 189cm/75kg  " << endl;
			cout << "    MF 손흥민 183cm/78kg  MF 황희찬 177cm/77kg  DF 이기제 176cm/68kg  " << endl;
			cout << "    MF 양현준 179cm/73kg  DF 설영우 180cm/72kg  DF 정승현 188cm/74kg  " << endl;
			cin.get(phsh4);
		}
		return 1;
	}
	else if (selMenuNum == 7)
	{   // 종료 하기
		return 2;
	}
}
/*
함수 이름: MakeReservation
5번 경기 예약입력 시 에약받는 화면 출력
반환값: string 경기 일정 선택 값
*/
int Tmain::MakeReservation()
{
	int ResCh;
	cout << "======================================================================================================" <<endl;
	cout << "=========================================== SELECT SCHEDULE ==========================================" <<endl;
	cout << "======================================================================================================" <<endl;
	cout << "\t\t\t1) 2024년 1월 13일(토) 01:00  카타르 vs 레바논" << endl;
	cout << "\t\t\t2) 2024년 1월 13일(토) 23:30  중국 vs 타지키스탄" << endl;
	cout << "\t\t\t3) 2024년 1월 13일(토) 20:30  호주 vs 인도" << endl;
	cout << "\t\t\t4) 2024년 1월 14일(일) 02:30  우즈베키스탄 vs 시리아" << endl;
	cout << "\t\t\t5) 2024년 1월 14일(일) 23:30  아랍에미리트 vs 홍콩" << endl;
	cout << "\t\t\t6) 2024년 1월 14일(일) 20:30  일본 vs 베트남" << endl;
	cout << "\t\t\t7) 2024년 1월 15일(월) 20:30  대한민국 vs 바레인" << endl;
	cout << "======================================================================================================" <<endl;
	cout << "\t\t\t: ";
	cin >> ResCh;
	return ResCh; //일정 반환
}
/*
함수 이름: PlanReservation
경기예약화면에서 경기 일정 선택을 받아 구역 선택을 하는 화면
반환값: string 구역과 좌석 선택 값
*/
int Tmain::AreaReservation(int PlanAp)
{
	string UesrAp; //경기, 구역, 인원, 좌석
	string ID;

	vector<string>UserData;
	int len = static_cast<int>(UserData.size());
	vector<string> result;
	
	ifstream readFile; //읽을 목적의 파일 선언
	readFile.open("UserData.txt"); //file open
	if(readFile.is_open())
	{
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string str;
			getline(readFile,str); //한줄씩 읽어오기
			UserData.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserData.size(); i++)
	{// 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserData[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            result.push_back(buffer);
		}
	}
	//  예약확인
	vector<string>UserResData;
	int lenR = static_cast<int>(UserResData.size());
	vector<string> resultRes;
	ifstream ReadFile; //읽을 목적의 파일 선언
	ReadFile.open("UserResData.txt"); //file open
	if(ReadFile.is_open())
	{
		while (!ReadFile.eof()) //파일 끝까지 읽었는지 확인
		{
			string strR;
			getline(ReadFile,strR); //한줄씩 읽어오기
			UserResData.push_back(strR); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserResData.size(); i++)
	{// 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserResData[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            resultRes.push_back(buffer);
		}
	}
	
	cout << endl;
	cout << "======================================================================================================" <<endl;
	cout << "=========================================== ENTER YOUR ID ============================================" <<endl; 
	cout << "======================================================================================================" <<endl;
	cout << endl;
	int a =0;
	while (a == 0)
	{
		cout << "\t\t\tID : ";
		cin >> ID;
		for (size_t i = 0; i < resultRes.size(); i++)
		{
			if(ID == resultRes[i])
			{
				cout << "\t현재 아이디는 더 이상 예약이 되지않습니다. "<< endl;
				return 1;
				break;
			}
			if(ID != resultRes[i])
			{
				if(i == (resultRes.size()-1))
				{
					break;
				}
			}
		}
		for (size_t i = 0; i < result.size(); i++)
		{
			if(ID == result[i])
			{
				cout << "\t계속해서 예매를 진행합니다 "<< endl;
				a = 1;
				break;
			}
			if(ID != result[i])
			{
				if(i == (result.size()-1))
				{
					cout << "\t동일한 아이디를 찾지못했습니다. 다시 입력해주세요. " << endl;
					break;
				}
			}
		}
	}
	cout << endl;
	UesrAp.append(ID);
	system ("clear");

	switch (PlanAp)
	{
	case 1:
		UesrAp.append("/2024년 1월 13일(토) 01:00  카타르 vs 레바논/");
		break;
	case 2:
		UesrAp.append("/2024년 1월 13일(토) 23:30  중국 vs 타지키스탄/");
		break;
	case 3:
		UesrAp.append("/2024년 1월 13일(토) 20:30  호주 vs 인도/");
		break;
	case 4:
		UesrAp.append("/2024년 1월 14일(일) 02:30  우즈베키스탄 vs 시리아/");
		break;
	case 5:
		UesrAp.append("/2024년 1월 14일(일) 23:30  아랍에미리트 vs 홍콩/");
		break;
	case 6:
		UesrAp.append("/2024년 1월 14일(일) 20:30  일본 vs 베트남/");
		break;
	case 7:
		UesrAp.append("/2024년 1월 15일(월) 20:30  대한민국 vs 바레인/");
		break;
	default:
		break;
	}
	int row =15; //경기장 행
	int col =20; //경기장 열
	int ResCh; //구역
	int People; //인원 수
	int stadium[row][col] = //경기장 크기
	{
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
		{3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3},
		{3,8,3,7,7,7,6,6,6,6,6,6,6,6,7,7,7,3,8,3},
		{3,8,7,3,5,5,5,5,5,5,5,5,5,5,5,5,3,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,7,3,3,3,3,3,3,3,3,3,3,3,3,7,7,8,3},
		{3,8,7,3,5,5,5,5,5,5,5,5,5,5,5,5,3,7,8,3},
		{3,8,3,7,7,7,6,6,6,6,6,6,6,6,7,7,7,3,8,3},
		{3,3,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,3,3},
		{3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3},
	}; 

	cout << "======================================================================================================" <<endl;
	cout << "============================================ SELECT AREA =============================================" <<endl;
	cout << "======================================================================================================" <<endl;
	for(int i=0; i<row; i++) //행
	{
		cout <<"\t\t     ";
		for(int j=0; j<col; j++) //열
		{
			if(stadium[i][j]==3)
			{
				cout << "⬜ ";
			}
			if(stadium[i][j]==5)
			{
				cout << "🟥 ";
			}
			if(stadium[i][j]==6)
			{
				cout << "🟧 ";
			}
			if(stadium[i][j]==7)
			{
				cout << "🟨 ";
			}
			if(stadium[i][j]==8)
			{
				cout << "🟩 ";
			}
		}
		cout << endl;
	} 
	cout << "======================================================================================================" <<endl;
	cout << "\t1)🟥 MVIP 100,000원  2)🟧 VIP 80,000원  3)🟨 GOLD 60,000원  4)🟩 SIVER 20,000원" << endl;
	cout << "\t: ";
	cin >> ResCh;
	while(ResCh > 4)
	{
		cout << "\t1번부터 4번까지 입력이 가능합니다. 다시 입력해주세요." << endl;
		cout << "\t: ";
		cin >> ResCh;
	}
	switch (ResCh)
	{
	case 1:
		UesrAp.append("MVIP/");
		break;
	case 2:
		UesrAp.append("VIP/");
		break;
	case 3:
		UesrAp.append("GOLD/");
		break;
	case 4:
		UesrAp.append("SIVER/");
		break;
	}

	cout << "======================================================================================================" <<endl;
	cout << "\t인원 수를 입력하세요 (ID당 두 개의 좌석만 예매가 가능합니다.)" << endl;
	cout << "\t: ";
	cin >> People;
	while(People > 2)
	{
		cout << "\t1 또는 2로 입력이 가능합니다. 다시 입력해주세요." << endl;
		cout << "\t: ";
		cin >> People;
	}
	if(People == 1)
	{
		UesrAp.append("좌석 1개/");
	}
	if(People == 2)
	{
		UesrAp.append("좌석 2개/");
	}
	system ("clear");

	cout << "======================================================================================================" <<endl;
	cout << "============================================ SELECT AREA =============================================" <<endl;
	cout << "======================================================================================================" <<endl;
	string seatChoice1; //첫번째 좌석 변수
	string seatChoice2; //두번째좌석 변수
	if(ResCh == 1) // MVIP 5
	{
		int cnt1=1;
		for(int i=0; i<row; i++) //행
		{
			cout <<"\t\t     ";
			for(int j=0; j<col; j++) //열
			{
				if(stadium[i][j] == 5)
				{
					stadium[i][j] = cnt1;
					if(cnt1<10)
					{
						cout << " ";
					}
					cout << stadium[i][j];
					cout << " ";
					cnt1++;
				}
				else
				{
					stadium[i][j] = 3;
					if(stadium[i][j] == 3)
					{
						cout << "⬜ ";
					}
				}
			}
			cout << endl;
		}
	}
	if(ResCh == 2) // VIP 6
	{
		int cnt2=1;
		for(int i=0; i<row; i++) //행
		{
			cout <<"\t\t     ";
			for(int j=0; j<col; j++) //열
			{
				if(stadium[i][j] == 6)
				{
					stadium[i][j] = cnt2;
					if(cnt2<10)
					{
						cout << " ";
					}
					cout << stadium[i][j];
					cout << " ";
					cnt2++;
				}
				else
				{
					stadium[i][j] = 3;
					if(stadium[i][j] == 3)
					{
						cout << "⬜ ";
					}
				}
			}
			cout << endl;
		}
	}
	if(ResCh == 3) // GOLD 7
	{
		int cnt3=1;
		for(int i=0; i<row; i++) //행
		{
			cout <<"\t\t     ";
			for(int j=0; j<col; j++) //열
			{
				if(stadium[i][j] == 7)
				{
					stadium[i][j] = cnt3;
					if(cnt3<10)
					{
						cout << " ";
					}
					cout << stadium[i][j];
					cout << " ";
					cnt3++;
				}
				else
				{
					stadium[i][j] = 3;
					if(stadium[i][j] == 3)
					{
						cout << "⬜ ";
					}
				}
			}
			cout << endl;
		}
	}
	if(ResCh == 4) // SIVER 8
	{
		int cnt4=1;
		for(int i=0; i<row; i++) //행
		{
			cout <<"\t\t     ";
			for(int j=0; j<col; j++) //열
			{
				if(stadium[i][j] == 8)
				{
					stadium[i][j] = cnt4;
					if(cnt4<10)
					{
						cout << " ";
					}
					cout << stadium[i][j];
					cout << " ";
					cnt4++;
				}
				else
				{
					stadium[i][j] = 3;
					if(stadium[i][j] == 3)
					{
						cout << "⬜ ";
					}
				}
			}
			cout << endl;
		}
	}
	cout << "======================================================================================================" <<endl;
	cout << "\t원하는 좌석을 입력해주세요 " << endl;
	cout << "\t: ";
	cin >> seatChoice1;
	UesrAp.append(seatChoice1);
	UesrAp.append(".");
	if(People == 2)
	{
		cout << "\t두 번째 좌석을 입력해주세요 " << endl;
		cout << "\t: ";
		cin >> seatChoice2;
		while(seatChoice1 == seatChoice2)
		{
			cout << "\t첫 번째 좌석과 같은 좌석을 입력하였습니다. 다시 입력해주세요 " << endl;
			cout << "\t: ";
			cin >> seatChoice2;
		}	
	}
	UesrAp.append(seatChoice2);
	UesrAp.append("번 좌석/");
	system ("clear");
	
	ofstream writeFile; //쓸 목적의 파일 선언
	writeFile.open("UserResData.txt", ios::app); //파일 열고 이어쓰기
	writeFile << UesrAp << endl;
	writeFile.close(); //파일 닫기
	cout << "======================================================================================================" <<endl;
	cout << endl;
	cout << "        ____       _____                   ____     __         ____       ______    ____      " <<endl;
	cout << "       /\\  _`\\    /\\  __`\\     /'\\_/`\\    /\\  _`\\  /\\ \\       /\\  _`\\    /\\__  _\\  /\\  _`\\    " <<endl;
	cout << "       \\ \\ \\/\\_\\  \\ \\ \\/\\ \\   /\\      \\   \\ \\ \\L\\ \\\\ \\ \\      \\ \\ \\L\\_\\  \\/_/\\ \\/  \\ \\ \\L\\_\\  " <<endl;
	cout << "        \\ \\ \\/_/_  \\ \\ \\ \\ \\  \\ \\ \\__\\ \\   \\ \\ ,__/ \\ \\ \\  __  \\ \\  _\\L     \\ \\ \\   \\ \\  _\\L  " <<endl;
	cout << "         \\ \\ \\L\\ \\  \\ \\ \\_\\ \\  \\ \\ \\_/\\ \\   \\ \\ \\/   \\ \\ \\L\\ \\  \\ \\ \\L\\ \\    \\ \\ \\   \\ \\ \\L\\ \\ " <<endl;
	cout << "          \\ \\____/   \\ \\_____\\  \\ \\_\\  \\_\\   \\ \\_\\    \\ \\____/   \\ \\____/     \\ \\_\\   \\ \\____/" <<endl;
	cout << "           \\/___/     \\/_____/   \\/_/ \\/_/    \\/_/     \\/___/     \\/___/       \\/_/    \\/___/ " <<endl;
	cout << endl;
}
/*
함수 이름: showReservedTicket
예매확인 화면으로 UserResData.txt 파일 열어서 해당 아이디 중복되면 그 줄 프린트해주는 화면
반환값: 없음
*/
void Tmain::showReservedTicket()
{
	string fid; //파일에 검색할 아이디
	vector<string>UserResData;
	int len = static_cast<int>(UserResData.size());
	vector<string> resultRes;
	ifstream readFile; //읽을 목적의 파일 선언
	string str;
	readFile.open("UserResData.txt"); //file open

	if(readFile.is_open())
	{
		UserResData.clear();
		while (!readFile.eof()) //파일 끝까지 읽었는지 확인
		{
			getline(readFile, str); //한줄씩 읽어오기
			UserResData.push_back(str); //읽어 온 단어 저장
		}
		readFile.close(); //file close
	}
	for(int i=0; i<UserResData.size(); i++)
	{
        // 벡터에 넣어 놓은 한줄을 들고와서 
		std::string now = UserResData[i];
		std::istringstream iss(now);
        char separator = '/';        
		std::string buffer;

		while (getline(iss, buffer, separator))
		{
            resultRes.push_back(buffer);
		}
	}
	cout << endl;
	cout << "======================================================================================================" <<endl;
	cout << "============================================ SELECT AREA =============================================" <<endl;
	cout << "======================================================================================================" <<endl;
	cout << endl << endl;
	int a=0;
	while (a == 0)
	{
		cout << "\tID : ";
		cin >> fid;
		cout << endl;
		for (size_t i = 0; i < resultRes.size(); i++)
		{
			if(fid == resultRes[i])
			{
				cout <<  "\t" << resultRes[i] << " 회원님의 예매정보 입니다" << endl;
				cout << "\t[ " << resultRes[i+1]<< "  " << resultRes[i+2]<<"  "<< resultRes[i+3]<<"  "<< resultRes[i+4] << " ]" <<endl;
				a = 1;
				break;
			}
			if(fid != resultRes[i])
			{
				if(i == (resultRes.size()-1))
				{
					cout << "\t예매정보가 없습니다" << endl;
					a=0;
					break;
				}
			}
		}
	}
	cout << endl;
}