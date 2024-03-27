#include "service.h"
#include "ui_service.h"

Service::Service(QWidget *parent): QWidget(parent), ui(new Ui::Service)
{
    ui->setupUi(this);

//기존 위젯 화면이랑 연결위한 코드
    widget = new Widget();
    connect(widget, &Widget::signal_Info, this, &Service::slot_Info);
    widget->show();

    socket = new QTcpSocket(this); // 소켓 생성
    connect(socket, SIGNAL(connected()), this, SLOT(slot_sendMyName())); //고객센터 채팅창과 서버에게 데이터보내기
    connect(socket, SIGNAL(readyRead()), this, SLOT(slot_readMessage())); //서버에서 보낸 데이터 읽기 수신
    connect(ui->connect_btn, &QPushButton::pressed, this, &Service::connect_btn_clicked);
    connect(ui->lineEdit , &QLineEdit::returnPressed, ui->connect_btn, &QPushButton::pressed); //채팅 입력창에 입력 후 엔터 시 전송 버튼 눌린 것으로
    connect(socket, SIGNAL(disconnected()), this, SLOT(slot_disconnected())); //서버의 연결 종료 시 알려줌

}
/*함수이름: slot_Info()
기능: 서버의 아이피와 포트번호로 서버에게 연결요청하는 슬롯함수
반환값: 없음*/
void Service::slot_Info()
{
    socket->connectToHost(m_servIP, 50000);
    qDebug() << "<- 서버에게 연결 요청";
}
/*함수이름: slot_sendMyName()
기능: 고객센터 채팅창을 띄우며 서버에게 수신할 메세지 바이트로 변환 후 전송하는 슬롯함수
반환값: 없음*/
void Service::slot_sendMyName()
{
    this->window()->show();

    QString msg = "클라이언트 접속";
    QByteArray message(msg.toUtf8());
    socket->write(message); // 송신
    qDebug() << "서버채팅에 연결됨";
}
/*함수이름: slot_readMessage()
기능: 서버에서 클라이언트가 송신받은 메세지 스트링으로 변환 후 UI에 출력하는 슬롯 함수
반환값: 없음*/
void Service::slot_readMessage()
{
    QTcpSocket* readSocket = qobject_cast<QTcpSocket*>(sender());
    if(socket->bytesAvailable() >= 0)
    {
        QByteArray readData = readSocket->readAll();
        QString data = QString::fromUtf8(readData);

        ui->textEdit->append("<b style=\"color: rgb(58, 134, 255);\">" "SERVICE: </b>" + data);
        qDebug() << "서버 송신 메세지:" << data;
    }
}
/*함수이름: connect_btn_clicked()
기능: 클라이언트가 서버에게 수신할 메세지 UI에서 들고와 바이트로 변환 후 전송하는 슬롯 함수
반환값: 없음*/
void Service::connect_btn_clicked()
{
    QString msg = ui->lineEdit->text().trimmed();
    ui->textEdit->append("<b style=\"color: rgb(32, 178, 170);\">" "ME: </b>" + msg);
    QByteArray message(msg.toUtf8());
    qDebug() << "클라이언트 수신 메세지:" <<  message;
    socket->write(message); // 송신

    ui->lineEdit->clear();

}
/*함수이름: slot_disconnected()
기능: 서버가 연결 해제됨을 UI에 출력하는 슬롯 함수
반환값: 없음*/
void Service::slot_disconnected()
{
    ui->textEdit->append("-> 서버로부터 연결 해제");
    qDebug() << "서버로부터 접속 종료.";
}

Service::~Service()
{
    delete ui;
}

