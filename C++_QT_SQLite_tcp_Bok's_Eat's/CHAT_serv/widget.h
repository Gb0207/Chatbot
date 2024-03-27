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
#include <QSignalMapper>
#include <QTime>

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
    QList<QTcpSocket *> list;
    QTcpSocket *socket;
    QTcpServer *server;
    QMap<QTcpSocket*, QString> clientMap; // 소켓과 클라이언트 정보 매핑
    QTcpSocket *currentClient; // 현재 선택된 클라이언트
    QMap<QTcpSocket*, QString> clientConversations;

    QHostAddress m_hostAddress;
    QHostAddress getMyIP();
    void updateClientList(); // 클라이언트 리스트 업데이트 함수
    void initServ();

private slots:
    void slot_newConnection();
    void slot_readMessage();
    void on_sendButton_clicked(); // 메시지 전송 버튼 클릭 이벤트
    void on_clientListView_clicked(const QModelIndex &index); // 리스트뷰에서 클라이언트 선택 이벤트

};

#endif // WIDGET_H
