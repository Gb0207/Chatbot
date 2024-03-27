#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtNetwork>
#include <QTcpSocket>
#include <QTcpServer>
#include <QHostAddress>
#include <QString>
#include <QtWidgets>
#include <QDebug>
#include <QTabWidget>
#include <QMessageBox>
#include <QPixmap>
#include <QMap>
#include <QMovie>

namespace Ui {

class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
    // QString m_servIP = "10.10.20.121";
    QString m_servIP = "10.10.20.99";

    QList<QString> pizza_N;
    QList<QString> pizza_S;
    QMap<QString, QPushButton*> Pizza;

    QList<QString> jokbal_N;
    QList<QString> jokbal_S;
    QMap<QString, QPushButton*> Jokbal;

    QList<QString> japen_N;
    QList<QString> japen_S;
    QMap<QString, QPushButton*> Japen;

    QList<QString> china_N;
    QList<QString> china_S;
    QMap<QString, QPushButton*> China;

    QList<QString> chicken_N;
    QList<QString> chicken_S;
    QMap<QString, QPushButton*> Chicken;

    QList<QString> bunsik_N;
    QList<QString> bunsik_S;
    QMap<QString, QPushButton*> Bunsik;

    QString name; //매장이름
    QString category; //카테고리명
    QMap<QString, QString> menuDetailsMap;

    QPushButton *menu_btn; //메뉴버튼
    QMap<QString, QPushButton*> menu_pick; //선택한 메뉴의 메뉴명과 가격

    QPushButton *side_btn; //사이드와 음료의 버튼
    QMap<QString, QString> side; //사이드와 음료의 이름과 가격
    int total = 0; //총금액
    QString menu_name_total; //모든 선택 메뉴
    int point = 0; //포인트
    QString price_total = "STAY,"; //결제 시 송신할 스트링
    QString User; //유저이름
    QString Address; //유저주소
    QString order = "주문대기";
    QString store; //매장이름
    QString search_cashback; //캐시백화면 닉네임이름

    void initClnt();
    void Connect();
    void store_list();

signals:
    void signal_Info();

private slots:
    void slot_readMessage();
    void slot_disconnected();
//화면 안의 검색버튼 및 검색창 송신 관련 슬롯함수
    void Service_Btn();
    void slot_search_btnclicked();
    void slot_order_btnclicked();
    void slot_cashdack_btnclicked();
    void slot_payname_btnclicked();
//화면전환 버튼 슬롯함수
    void slot_homeBtnClicked(); //홈화면에서 검색 기능 및 카테고리와 각종 버튼 선택 시 화면전환 슬롯함수
    void slot_store_listBtnClicked(); //매장목록화면에서 목록버튼생성관련, 매장선택 시 송신 화면전환 슬롯함수
    void slot_storeBtnClicked(); //매장화면에서 수신받은 데이터로 매뉴 목록버튼 생성 및 클릭 시 화면전환 슬롯함수
    void slot_menuBtnClicked(); //메뉴화면에서 목록버튼 생성 및 클릭 시 화면전환 슬롯함수
    void slot_payBtnClicked(); //결제화면에서 버튼 생성 및 송수신 화면전환 슬롯함수
    void slot_cashdackBtnClicked(); //캐시백화면에서 버튼 생성 및 송수신 화면전환 슬롯함수
    void slot_orderBtnClicked(); // 주문내역화면에서 버튼 생성 및 송수신 화면전환 슬롯함수
//홈화면에서 카테고리 탭버튼 선택시 화면 전환 슬롯
    void slot_tabWidget_Jokbal();
    void slot_tabWidget_Japen();
    void slot_tabWidget_Pizza();
    void slot_tabWidget_China();
    void slot_tabWidget_Chicken();
    void slot_tabWidget_Bunsik();

    void slot_total_plus();//사이드와 음료 선택 시 버튼의 딕셔너리를 값을 들고와 금액 추가하는 슬롯함수
    void slot_pay_btn_clicked(); //결제화면에서 결제하기 버튼 클릭 시 송신하는 슬롯함수
    void slot_cashdack_btn_clicked(); //캐시백화면에서 캐시백 받기 버튼 클릭 시 송신하는 슬롯함수
    void on_pushButton_clicked(); //홈화면 광고 클릭 시 해당 링크로 새 인터넷창띄우는 슬롯함수

    void All_btn_image(); //모든 버튼 연결, 이미지연결 함수
};
#endif // WIDGET_H
