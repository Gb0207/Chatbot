#include "widget.h"
#include "ui_widget.h"
//생성자
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    All_btn_image(); // 버튼,이미지 연결
    setWindowTitle("Bok's Eat's");
    socket = new QTcpSocket(this); //소켓 생성
    initClnt(); // 송수신 커넥트
    Connect(); // 서버에 연결요청
    connect(ui->Service, &QPushButton::pressed, this, &Widget::Service_Btn); // 고객센터 서버에 연결요청
}
/*함수이름: All_btn_image()
기능: 홈화면, 매장목록화면과 광고 및 이미지 버튼 연결, 모든 화면의 홈, 뒤로가기, 캐시백 버튼의 연결을 모아둔 함수
반환값: 없음*/
void Widget::All_btn_image()
{
    //홈화면 꾸미기
    QMovie *movie = new QMovie("/Users/lms/Documents/bokclient/bokimage/label.gif");
    ui->label->setMovie(movie);
    ui->label->setScaledContents(true);
    movie->start();
    ui->label_2->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/iogo.jpg)");

    ui->home_menu_btn_1->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/족발b.png)");
    ui->home_menu_btn_2->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/일식b.png)");
    ui->home_menu_btn_3->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/피자b.png)");
    ui->home_menu_btn_4->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/중식b.png)");
    ui->home_menu_btn_5->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/치킨b.png)");
    ui->home_menu_btn_6->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/분식b.png)");

    store_list(); //매장목록화면

    //버튼 연결
    connect(ui->search, &QPushButton::pressed, this, &Widget::slot_search_btnclicked);
    connect(ui->search, &QPushButton::pressed, this, &Widget::slot_readMessage);
    connect(ui->search_lineEdit, &QLineEdit::returnPressed, ui->search, &QPushButton::pressed);

    connect(ui->order_btn, SIGNAL(clicked()), this, SLOT(slot_orderBtnClicked()));

    connect(ui->home_btn_1, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->home_btn_2, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->home_btn_3, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->home_btn_4, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->home_btn_5, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->home_btn_6, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));

    connect(ui->cashdack_btn_1, SIGNAL(clicked()), this, SLOT(slot_cashdackBtnClicked()));
    connect(ui->cashdack_btn_2, SIGNAL(clicked()), this, SLOT(slot_cashdackBtnClicked()));
    connect(ui->cashdack_btn_3, SIGNAL(clicked()), this, SLOT(slot_cashdackBtnClicked()));
    connect(ui->cashdack_btn_4, SIGNAL(clicked()), this, SLOT(slot_cashdackBtnClicked()));

    connect(ui->back_btn_1, SIGNAL(clicked()), this, SLOT(slot_homeBtnClicked()));
    connect(ui->back_btn_2, SIGNAL(clicked()), this, SLOT(slot_store_listBtnClicked()));
    connect(ui->back_btn_3, SIGNAL(clicked()), this, SLOT(slot_storeBtnClicked()));
    connect(ui->back_btn_4, SIGNAL(clicked()), this, SLOT(slot_menuBtnClicked()));
    connect(ui->back_btn_5, SIGNAL(clicked()), this, SLOT(slot_store_listBtnClicked()));

    connect(ui->home_menu_btn_1, SIGNAL(clicked()), this, SLOT(slot_tabWidget_Jokbal()));
    connect(ui->home_menu_btn_2, SIGNAL(clicked()), this, SLOT(slot_tabWidget_Japen()));
    connect(ui->home_menu_btn_3, SIGNAL(clicked()), this, SLOT(slot_tabWidget_Pizza()));
    connect(ui->home_menu_btn_4, SIGNAL(clicked()), this, SLOT(slot_tabWidget_China()));
    connect(ui->home_menu_btn_5, SIGNAL(clicked()), this, SLOT(slot_tabWidget_Chicken()));
    connect(ui->home_menu_btn_6, SIGNAL(clicked()), this, SLOT(slot_tabWidget_Bunsik()));
}
/*함수이름: initClnt()
기능: 서버의 송신정보를 수신하는 시그널과 서버의 연결 종료 시그널 연결하는 함수
반환값: 없음*/
void Widget::initClnt()
{
    connect(socket, SIGNAL(readyRead()), this,  SLOT(slot_readMessage())); //수신
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected())); //종료시그널
}
/*함수이름: store_list()
기능: 매장목록의 테이블의 정렬맞춤과 매장 버튼 생성 및 이미지와 매장이름을 연결해 클릭이벤트 시 화면전환하는 함수
반환값: 없음*/
void Widget::store_list()
{
    ui->tableWidget_Pizza->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Pizza->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_Jokbal->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Jokbal->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_Japen->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Japen->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_Pizza->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Pizza->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_China->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_China->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_Chicken->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Chicken->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidget_Bunsik->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_Bunsik->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    pizza_N.append("도미노피자");
    pizza_N.append("파파존스");
    pizza_N.append("피자탑");
    pizza_N.append("피자헛");
    pizza_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/도미노피자.png)");
    pizza_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/파파존스.png)");
    pizza_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/피자탑.png)");
    pizza_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/피자헛.png)");
    for(int i=0; i<4; i++)
    {
        Pizza.insert(pizza_N[i], new QPushButton);
        Pizza[pizza_N[i]]->setStyleSheet(pizza_S[i]);
        ui->tableWidget_Pizza->setCellWidget(i, 0, Pizza[pizza_N[i]]);
        connect(Pizza[pizza_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }

    jokbal_N.append("송가네왕족발");
    jokbal_N.append("삶오로지다족발보쌈-수완점");
    jokbal_N.append("1석2족보쌈-본점");
    jokbal_N.append("깐깐한족발-송정점");
    jokbal_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/송가네왕족발.png)");
    jokbal_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/삶오로지다족발보쌈-수완점.png)");
    jokbal_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/1석2족보쌈-본점.png)");
    jokbal_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/깐깐한족발-송정점.png)");
    for(int i=0; i<4; ++i)
    {
        Jokbal.insert(jokbal_N[i], new QPushButton);
        Jokbal[jokbal_N[i]]->setStyleSheet(jokbal_S[i]);
        ui->tableWidget_Jokbal->setCellWidget(i, 0, Jokbal[jokbal_N[i]]);
        connect(Jokbal[jokbal_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }

    japen_N.append("봉우리참치");
    japen_N.append("수제돈카츠전문점-광산점");
    japen_N.append("뚱까츠");
    japen_N.append("타코로와");
    japen_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/봉우리참치.png)");
    japen_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/수제돈카츠전문점-광산점.png)");
    japen_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/뚱까츠.png)");
    japen_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/타코로와.png)");
    for(int i=0; i<4; ++i)
    {
        Japen.insert(japen_N[i], new QPushButton);
        Japen[japen_N[i]]->setStyleSheet(japen_S[i]);
        ui->tableWidget_Japen->setCellWidget(i, 0, Japen[japen_N[i]]);
        connect(Japen[japen_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }

    china_N.append("황제쟁반짜장-소촌점");
    china_N.append("북경옛날손짜장");
    china_N.append("도야짬뽕-광주하남점");
    china_N.append("청룡각-광주하남점");
    china_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/황제쟁반짜장-소촌점.png)");
    china_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/북경옛날손짜장.png)");
    china_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/도야짬뽕-광주하남점.png)");
    china_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/청룡각-광주하남점.png)");
    for(int i=0; i<4; ++i)
    {
        China.insert(china_N[i], new QPushButton);
        China[china_N[i]]->setStyleSheet(china_S[i]);
        ui->tableWidget_China->setCellWidget(i, 0, China[china_N[i]]);
        connect(China[china_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }

    chicken_N.append("호식이두마리치킨-광주우산점");
    chicken_N.append("BHC-광주소촌우산점");
    chicken_N.append("지코바치킨-하남1호점");
    chicken_N.append("굽네치킨피자-광주하남점");
    chicken_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/호식이두마리치킨-광주우산점.png)");
    chicken_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/BHC-광주소촌우산점.png)");
    chicken_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/지코바치킨-하남1호점.png)");
    chicken_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/굽네치킨피자-광주하남점.png)");
    for(int i=0; i<4; ++i)
    {
        Chicken.insert(chicken_N[i], new QPushButton);
        Chicken[chicken_N[i]]->setStyleSheet(chicken_S[i]);
        ui->tableWidget_Chicken->setCellWidget(i, 0, Chicken[chicken_N[i]]);
        connect(Chicken[chicken_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }

    bunsik_N.append("마몽로제떡볶이-소촌점");
    bunsik_N.append("김밥명가-하남점");
    bunsik_N.append("신전떡볶이");
    bunsik_N.append("수유리우동집-하남점");
    bunsik_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/마몽로제떡볶이-소촌점.png)");
    bunsik_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/김밥명가-하남점.png)");
    bunsik_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/신전떡볶이.png)");
    bunsik_S.append("border-image: url(/Users/lms/Documents/bokclient/bokimage/수유리우동집-하남점.png)");
    for(int i=0; i<4; ++i)
    {
        Bunsik.insert(bunsik_N[i], new QPushButton);
        Bunsik[bunsik_N[i]]->setStyleSheet(bunsik_S[i]);
        ui->tableWidget_Bunsik->setCellWidget(i, 0, Bunsik[bunsik_N[i]]);
        connect(Bunsik[bunsik_N[i]], &QPushButton::clicked, this, &Widget::slot_storeBtnClicked);
    }
}

/*함수이름: slot_readMessage()
기능: 서버에서 송신한 데이터를 스트링으로 변환 하며, 수신받은 데이터 정리 후 필요한 화면으로의 전환과 팝업메세지를 띄우거나 UI에 출력하는 슬롯 함수
반환값: 없음*/
void Widget::slot_readMessage()
{
    if(socket->bytesAvailable() >= 0)
    {
        QByteArray readData = socket->readAll();
        QString data = QString::fromUtf8(readData);
        qDebug() << data << "\n";

        /*NONE이면 홈화면 매장 검색 시 없는 매장이라서 다시 입력해야함*/
        if(data == "NONE")
        {
            QMessageBox::information(this,"Bok's Eat's","다시 입력해주세요.\n없는 정보입니다.");
            ui->search_lineEdit ->clear();
            ui->search_lineEdit ->setFocus();
        }
        else if(data == "NPOINT")
        {
            QMessageBox::warning(this,"Bok's Eat's","잔여 포인트가 없습니다.");
        }
        else if(data.startsWith("NEW,"))
        {
            QStringList list1 = data.split(',');
            QString payN = list1.at(1);
            qDebug() <<"포인트: " << payN;
            if(payN == "ON")
            {
                QMessageBox::warning(this,"Bok's Eat's","다시 입력해주세요.\n중복되는 닉네임입니다.");
                ui->pay_name->clear();
                ui->pay_name->focusWidget();
            }
            else
            {
                connect(ui->pay_btn, SIGNAL(clicked()), this, SLOT(slot_pay_btn_clicked()));
            }
        }
        else if(data.startsWith("POINT,"))
        {
            QStringList list1 = data.split(',');
            QString pointP = list1.at(2);
            ui->cashdack_point->append(pointP);
            qDebug() <<"포인트: " << pointP;
        }
        else if(data.startsWith("LIST,"))
        {
            QStringList list1 = data.split(',');
            QString storeN = list1.at(1);
            QString stayOR = list1.at(2);
            ui->order_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->order_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
            ui->order_table->setItem(0,0, new QTableWidgetItem(storeN));
            ui->order_table->setItem(0,1, new QTableWidgetItem(stayOR));
            qDebug() <<"매장명: " << storeN <<"주문상태: " << stayOR;
        }
        else
        {
            if(data.startsWith("ONE,"))
            {
                QStringList list1 = data.split(';');
                QStringList list2 = list1[0].split(',');
                name = list2.at(1);
                qDebug() <<"매장명: " << name;
            }
            /*;를 기준으로 스트링 나누기*/
            QStringList menuItems = data.split(";");
            bool isFirstItem = true;
            foreach (const QString &menuItem, menuItems)
            {
                QStringList details = menuItem.split(",");
                if (isFirstItem && details.size() >= 2)
                {
                    if(!data.startsWith("ONE,"))
                    {
                        name = details.at(0);
                    }
                    category = details.at(1);
                    isFirstItem = false;
                    continue;
                }

                if (details.size() >= 3)
                {
                    // 메뉴 이름과 DEEPMENU를 조합하여 고유한 키 생성
                    QString uniqueKey = details.at(0) + ":" + details.at(1);
                    QString large = details.at(2);

                    // 고유 키와 LARGE 값으로 구성된 맵에 정보 저장
                    menuDetailsMap.insert(uniqueKey, large);
                }
            }
            /*매장화면에 사진 및 테이블위젯 설정 그리고 정보 출력*/
            ui->store_photo ->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/aokimage/"+name+"p.png)");
            ui->store_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
            QMapIterator<QString, QString> i(menuDetailsMap);
            int j=0;
            while (i.hasNext())
            {
                i.next();
                QString key = i.key();
                QStringList keyParts = key.split(":"); // 고유 키 분할하여 메뉴 이름과 DEEPMENU 추출
                QString menuName = keyParts.at(0);
                QString deepMenu = keyParts.size() > 1 ? keyParts.at(1) : QString();
                QString large = i.value();

                if(menuName == "사이드")
                {
                    side.insert(deepMenu,large);
                }
                if(menuName == "음료")
                {
                    side.insert(deepMenu,large);
                }

                qDebug() << "Menu:" << menuName << ", DeepMenu:" << deepMenu << ", Large:" << large;
                menu_btn = new QPushButton(deepMenu);
                ui->store_table->setCellWidget(j, 0, menu_btn);
                ui->store_table->setItem(j, 1, new QTableWidgetItem(large));
                j++;
                menu_pick.insert(large, menu_btn);
                connect(menu_btn, &QPushButton::clicked, this, &Widget::slot_menuBtnClicked);
            }
            if(data.startsWith("ONE,"))
            {
                slot_storeBtnClicked();
            }
        }
    }
}
/*함수이름: slot_disconnected()
기능: 서버와 연결해제 시 콘솔창에 서버종료 문자를 출력하는 슬롯 함수
반환값: 없음*/
void Widget::slot_disconnected()
{
    qDebug() << "서버로부터 접속 종료.";
}
/*함수이름: slot_BtnClicked()
기능: 홈화면의 고객센터버튼 클릭 시 signal_Info시그널 실행하는 슬롯 함수이며, 실행된 시그널로 고객센터 채팅방화면이 팝업됩니다.
반환값: 없음*/
void Widget::Service_Btn()
{
    emit signal_Info();
}
/*함수이름: Connect()
기능: 서버의 아이피와 포트번호를 입력헤 서버에 연결요청하는 함수
반환값: 없음*/
void Widget::Connect()
{
    socket->connectToHost(m_servIP, 25000);
    qDebug() << "<- 서버에게 연결 요청";
}
/*함수이름: slot_search_btnclicked()
기능: 홈화면 검색창에 검색한 문자 UI에서 들고와 "one,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하는 슬롯 함수
반환값: 없음*/
void Widget::slot_search_btnclicked()
{
    QString search = "one,";
    search.append(ui->search_lineEdit->text());
    qDebug() << "서버에 보낼 홈화면 검색창:" << search;

    QByteArray ARRY(search.toUtf8());
    socket->write(ARRY);
}
/*함수이름: slot_order_btnclicked()
기능: 주문내역화면 닉네임창에 검색한 UI에서 들고와 "list,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하는 슬롯 함수
반환값: 없음*/
void Widget::slot_order_btnclicked()
{
    QString search ="list,";
    search.append(ui->order_lineEdit->text());
    qDebug() << "서버에 보낼 주문내역화면 닉네임:" << search;

    QByteArray ARRY(search.toUtf8());
    socket->write(ARRY);
}
/*함수이름: slot_cashdack_btnclicked()
기능: 캐시백화면 닉네임창에 검색한 문자 UI에서 들고와 "point,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하는 슬롯 함수
반환값: 없음*/
void Widget::slot_cashdack_btnclicked()
{
    ui->cashdack_lineEditN->setFocus();
    QString search = "point,";
    search_cashback = ui->cashdack_lineEditN->text();
    search.append(search_cashback);
    qDebug() << "서버에 보낼 캐시백화면 닉네임:" << search;

    QByteArray ARRY(search.toUtf8());
    socket->write(ARRY);
}
/*함수이름: slot_payname_btnclicked()
기능: 결제화면 닉네임창에 검색한 문자 UI에서 들고와 "new,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하는 슬롯 함수
반환값: 없음*/
void Widget::slot_payname_btnclicked()
{
    QString search ="new,";
    search.append(ui->pay_name->text());
    qDebug() << "서버에 보낼 결제화면 닉네임:" << search;

    QByteArray ARRY(search.toUtf8());
    socket->write(ARRY);
}
/*함수이름: slot_cashdack_btn_clicked()
기능: 캐시백화면 캐시백하기 버튼 클릭 시 UI에서 닉네임, 계좌번호, 은행 정보를 들고와 "cash,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하며, 팝업메세지를 띄우는 슬롯 함수
반환값: 없음*/
void Widget::slot_cashdack_btn_clicked()
{
    QString cashback_total = "cash,";
    cashback_total.append(search_cashback +",");
    cashback_total.append(ui->cashdack_lineEditB->text() +",");
    cashback_total.append(ui->comboBox->currentText() +",");
    qDebug() << "서버에 보낼 캐시백화면 닉네임 계좌번호 및 은행:" << cashback_total;
    QByteArray ARRY(cashback_total.toUtf8());
    socket->write(ARRY);

    QMessageBox::information(this,"Bok's Eat's","캐시백되었습니다");
    slot_homeBtnClicked();
    ui->cashdack_lineEditN ->clear();
    ui->cashdack_lineEditB ->clear();
    ui->cashdack_point ->clear();
}
/*함수이름: slot_pay_btn_clicked
기능: 결제화면 결제하기 버튼 클릭 시 UI에서 닉네임, 주소 "STAY,"문자 추가한뒤 바이트로 변환 후 데이터 서버에 송신하며, 송신 후 화면 전환하는 슬롯 함수
반환값: 없음*/
void Widget::slot_pay_btn_clicked()
{
    User = ui->pay_name->text();
    price_total.append(User+",");
    Address = ui->pay_address ->text();
    price_total.append(Address+",");

    qDebug() << "서버에게 보낼 주문내역문장:" << price_total <<"\n";

    QByteArray ARRY(price_total.toUtf8());
    socket->write(ARRY);

    slot_homeBtnClicked();
}


/*기능: 화면이동 슬롯 함수들
stackedWidget 0 = 홈화면 home
stackedWidget 1 = 매장목록화면 store_list
stackedWidget 2 = 상세매장화면 store
stackedWidget 3 = 메뉴화면 menu
stackedWidget 4 = 주문화면 pay
stackedWidget 5 = 캐시백화면 cashdack
stackedWidget 6 = 주문내역화면 order*/

/*함수이름: slot_homeBtnClicked()
기능: 홈화면으로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_homeBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
/*함수이름: slot_store_listBtnClicked()
기능: 매장목록화면으로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_store_listBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}
/*함수이름: slot_storeBtnClicked()
기능: 매장화면으로 화면전환 및 선택한 매장정보를 바이트로 변환 후 서버에 송신하는 슬롯함수
반환값: 없음*/
void Widget::slot_storeBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    QPushButton *Name = qobject_cast<QPushButton*>(sender());

    if(Pizza.values().contains(Name))
    {
        store = Pizza.key(Name);
    }
    else if (Jokbal.values().contains(Name))
    {
        store = Jokbal.key(Name);
    }
    else if (Japen.values().contains(Name))
    {
        store = Japen.key(Name);
    }
    else if (China.values().contains(Name))
    {
        store = China.key(Name);
    }
    else if (Chicken.values().contains(Name))
    {
        store = Chicken.key(Name);
    }
    else if (Bunsik.values().contains(Name))
    {
        store = Bunsik.key(Name);
    }
    qDebug() << store << "\n";
    QByteArray ARRY = QByteArray(store.toUtf8());
    socket->write(ARRY);
}
/*함수이름: slot_menuBtnClicked()
기능: 메뉴화면으로 화면전환 및 서버에서 수신받은 메뉴명,가격을 문자와 숫자로 형변환 하며, 버튼 생성 후 UI에 정렬해서 출력하는 슬롯함수
반환값: 없음*/
void Widget::slot_menuBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    QPushButton *Menu_price = qobject_cast<QPushButton*>(sender());
    QString price = menu_pick.key(Menu_price);
    QString menuName = menu_pick.value(price)->text();
    qDebug() << "가격:" << price << "메뉴명:"<< menuName;
    int PRICE = price.toInt();
    total += PRICE;
    menu_name_total.append(menuName);

    /*매장화면에 사진 및 테이블위젯 설정 그리고 정보 출력*/
    ui->menu_photo->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/aokimage/"+name+"p.png)");
    ui->menu_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->menu_table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    int i=0;
    QMapIterator<QString, QString> mi(side);
    while ( mi.hasNext() )
    {
        mi.next();
        qDebug() << mi.key() << ":" << mi.value();
        QString deep= mi.key();
        QString la= mi.value();
        side_btn = new QPushButton(deep);
        ui->menu_table->setCellWidget(i, 0, side_btn);
        ui->menu_table->setItem(i, 1, new QTableWidgetItem(la));
        i++;
        connect(side_btn, &QPushButton::clicked, this, &Widget::slot_total_plus);
    }
    connect(ui->menu_to_basket, &QPushButton::clicked, this, &Widget::slot_payBtnClicked);
}
/*함수이름: slot_payBtnClicked()
기능: 결제화면으로 화면전환 및 선택한 메뉴의 가격의 총합과 메뉴명 포인트를 계산해서 UI에 출력하며, 가격과 포인트를 문자로 형변환하고 닉네임과 주소를 입력받는 슬롯함수
반환값: 없음*/
void Widget::slot_payBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(4);

    QString change_total, change_point;
    point = total/100;
    change_total.setNum(total);
    change_point.setNum(point);

    ui->pay_point->setText(change_point);
    ui->pay_menu->setText(menu_name_total);
    ui->pay_price->setText(change_total);

    connect(ui->pay__btnN_2, &QPushButton::pressed, this, &Widget::slot_payname_btnclicked);
    connect(ui->pay__btnN_2, &QPushButton::pressed, this, &Widget::slot_readMessage);
    connect(ui->pay_name, &QLineEdit::returnPressed, ui->pay__btnN_2, &QPushButton::pressed);
    // 전체메뉴이름, 총금액, 적립될 포인트, 이름, 주소
    price_total.append(store+","+menu_name_total+","+change_total+","+change_point+",");
}
/*함수이름: slot_cashdackBtnClicked()
기능: 캐시벡화면으로 화면전환 및 닉네임을 입력받는 슬롯함수
반환값: 없음*/
void Widget::slot_cashdackBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(5);

    connect(ui->cashdack__btnN, &QPushButton::pressed, this, &Widget::slot_cashdack_btnclicked);
    connect(ui->cashdack__btnN, &QPushButton::pressed, this, &Widget::slot_readMessage);
    connect(ui->cashdack_lineEditN, &QLineEdit::returnPressed, ui->cashdack__btnN, &QPushButton::pressed);
    connect(ui->cashdack_btn, &QPushButton::pressed, this, &Widget::slot_cashdack_btn_clicked);

}
/*함수이름: slot_orderBtnClicked()
기능: 주문내역화면으로 화면전환 및 닉네임을 입력받는 슬롯함수
반환값: 없음*/
void Widget::slot_orderBtnClicked()
{
    ui->stackedWidget->setCurrentIndex(6);

    connect(ui->order_btn, &QPushButton::pressed, this, &Widget::slot_order_btnclicked);
    connect(ui->order_btn, &QPushButton::pressed, this, &Widget::slot_readMessage);
    connect(ui->order_lineEdit, &QLineEdit::returnPressed, ui->order_btn, &QPushButton::pressed);

    ui->order_lineEdit ->clear();
    ui->order_lineEdit ->setFocus();
}


/*기능: 홈화면 메뉴카테고리 선택 시 매장목록화면으로 전환하는 슬롯함수
tabWidget
home_menu_btn_1 족발 Jokbal = btn_1_tab_1
home_menu_btn_2 일식 Japen = btn_2_tab_2
home_menu_btn_3 피자 Pizza = btn_3_tab_3
home_menu_btn_4 중식 China = btn_4_tab_4
home_menu_btn_5 치킨 Chicken = btn_5_tab_5
home_menu_btn_6 분식 Bunsik = btn_6_tab_6*/

/*함수이름: slot_tabWidget_Jokbal()
기능: 홈화면에서 족발 카테고리 선택 시 해당 족발 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_Jokbal()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(0);
}
/*함수이름: slot_tabWidget_Japen()
기능: 홈화면에서 일식 카테고리 선택 시 해당 일식 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_Japen()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(1);
}
/*함수이름: slot_tabWidget_Pizza()
기능: 홈화면에서 피자 카테고리 선택 시 해당 피자 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_Pizza()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(2);
}
/*함수이름: slot_tabWidget_China()
기능: 홈화면에서 중식 카테고리 선택 시 해당 중식 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_China()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(3);
}
/*함수이름: slot_tabWidget_Chicken()
기능: 홈화면에서 치킨 카테고리 선택 시 해당 치킨 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_Chicken()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(4);
}
/*함수이름: slot_tabWidget_Bunsik()
기능: 홈화면에서 분식 카테고리 선택 시 해당 분식 카테고리로 화면전환 슬롯함수
반환값: 없음*/
void Widget::slot_tabWidget_Bunsik()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->tabWidget->setCurrentIndex(5);
}
/*함수이름: slot_total_plus()
기능: 상세메뉴화면 추가하는 메뉴들의 메뉴명과 가격 합계를 저장하며, 문자를 숫자로 형변환하는 슬롯함수
반환값: 없음*/
void Widget::slot_total_plus()
{
    QPushButton *side_price = qobject_cast<QPushButton*>(sender());
    QString bnt_to_str = side_price->text();
    QString price = side.value(bnt_to_str);
    qDebug() << "가격:" << price << "메뉴명:"<< bnt_to_str;
    int PRICE = price.toInt();
    total += PRICE;
    menu_name_total.append(","+bnt_to_str);
}

//소멸자
Widget::~Widget()
{
    delete ui;
}

/*함수이름: on_pushButton_clicked()
기능: 홈화면의 광고 클릭 시 새인터넷창으로 해당 광로 링크로 이동하는 슬롯함수
반환값: 없음*/
void Widget::on_pushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.cheogajip.co.kr/"));
}

