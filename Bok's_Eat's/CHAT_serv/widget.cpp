#include "widget.h"
#include "ui_widget.h"

// [02.1] Widget class 생성자 실행
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    initServ();
    connect(server, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    connect(ui->lineEdit , &QLineEdit::returnPressed, ui->pushButton, &QPushButton::pressed);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_sendButton_clicked()));

    ui->label_2->setStyleSheet("border-image: url(/Users/lms/Documents/bokclient/bokimage/iogo.jpg)");
    ui->lineEdit->clear();
}

Widget::~Widget()
{
    delete ui;
}
/*함수이름: initServ()
기능: ip port 결합 및 연결요청 대기 함수
반환값: 없음*/
void Widget::initServ()
{
    QHostAddress hostAddress = Widget::getMyIP();
    server = new QTcpServer(this); //생성하고
    if (!server->listen(hostAddress, 50000)) //연결
    {
        QMessageBox::critical(this, tr("TCP Server"), tr("서버를 시작할 수 없습니다. 에러메세지 : %1.").arg(server->errorString()));
        close();
        return; // 실패시 종료
    }
    ui->labelStatus->setText(tr("서버 동작 중 \n\n"));

    connect(server, SIGNAL(newConnection()), this, SLOT(slot_newConnection()));
    ui->connMsgEdit->clear();
}
/*함수이름: slot_newConnection()
기능: 소켓 생성 및 클라이언트에게 데이터 송신 후 UI에 출력 슬롯함수
반환값: 없음*/
void Widget::slot_newConnection()
{
    // 소켓 생성
    while(server->hasPendingConnections())
    {
        list.append(server->nextPendingConnection());
        connect(list.last(), SIGNAL(readyRead()), this, SLOT(slot_readMessage()));
    }
    //서버에 연결 상태 정보 출력
    QString clnt_addr = list.last()->peerAddress().toString();
    QString currTime = QTime::currentTime().toString("hh시 mm분 ss초 zzz밀리초");
    QString text_conn = QString("<-클라이언트 연결 성공 (%1)").arg(currTime);
    ui->connMsgEdit->append(text_conn);

    QByteArray message = QByteArray("안녕하세요. 고객센터입니다:)");
    currTime = QTime::currentTime().toString("hh시 mm분 ss초 zzz밀리초");

    // 문장 전송
    list.last()->write(message);

    // 전송 완료 상태 위젯 표시
    QString text_send = QString("->클라이언트 문장 전송 (%1)").arg(currTime);
    ui->connMsgEdit->append(text_send);

    updateClientList(); // 클라이언트 연결 시 리스트뷰 업데이트


}
/*함수이름: slot_readMessage()
기능: 수신받은 데이터 UI에 출력하는 슬롯함수
반환값: 없음*/
void Widget::slot_readMessage()
{
    QTcpSocket* readSocket = qobject_cast<QTcpSocket*>(sender());
    if(readSocket->bytesAvailable() > 0)
    {
        QByteArray readData = readSocket->readAll();
        QString message = QString::fromUtf8(readData);

        // 메시지를 저장하는 부분
        clientConversations[readSocket] += message + "\n";

        // 현재 선택된 클라이언트가 메시지를 보냈는 경우 UI에 메시지를 표시
        if (currentClient == readSocket) {
            ui->connMsgEdit->append("고객: "+message);
        }
    }
}
/*함수이름: getMyIP()
기능: 내 컴퓨터 ip찾기
반환값: 없음*/
QHostAddress Widget::getMyIP()
{
    QHostAddress myAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            //qDebug() << ipAddressesList.at(i);
            myAddress = ipAddressesList.at(i);
            break;
        }
    }
    if (myAddress.toString().isEmpty())
        myAddress = QHostAddress(QHostAddress::LocalHost);

    return myAddress;
}

void Widget::updateClientList()
{
    ui->clientListView->clear();
    foreach (QTcpSocket *clientSocket, list) {
        QString clientInfo = clientSocket->peerAddress().toString();
        QListWidgetItem *item = new QListWidgetItem(clientInfo);
        ui->clientListView->addItem(item);
        clientMap[clientSocket] = clientInfo; // 매핑 정보 업데이트
    }
}
void Widget::on_sendButton_clicked()
{
    if (currentClient && currentClient->isOpen()) {
        QString message = ui->lineEdit->text();
        currentClient->write(message.toUtf8());
        ui->connMsgEdit->append("상담사: " + message); // UI에 메시지 표시
    }
}


// widget.cpp에 추가
void Widget::on_clientListView_clicked(const QModelIndex &index)
{
    QString clientInfo = index.data().toString();
    foreach (QTcpSocket *socket, clientMap.keys()) {
        if (clientMap[socket] == clientInfo) {
            currentClient = socket; // 현재 선택된 클라이언트 업데이트

            // 선택된 클라이언트와의 대화 내용을 표시
            ui->connMsgEdit->clear();
            ui->connMsgEdit->append(clientConversations[socket]);
            break;
        }
    }
}
