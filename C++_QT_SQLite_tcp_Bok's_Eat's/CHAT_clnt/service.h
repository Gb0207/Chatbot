#ifndef SERVICE_H
#define SERVICE_H

#include <QWidget>
#include <QTcpSocket>
#include <QtNetwork>
#include <QDebug>
#include "widget.h"

namespace Ui {
class Service;
}

class Service : public QWidget
{
    Q_OBJECT

public:
    explicit Service(QWidget *parent = nullptr);
    ~Service();

private:
    Ui::Service *ui;
    Widget *widget;
    QTcpSocket *socket;
    // QString m_servIP = "10.10.20.121";
    QString m_servIP = "10.10.20.99";

private slots:
    void slot_Info();
    void slot_sendMyName();
    void slot_readMessage();
    void connect_btn_clicked();
    void slot_disconnected();

};

#endif // SERVICE_H
