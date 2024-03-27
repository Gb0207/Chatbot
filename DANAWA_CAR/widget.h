#ifndef WIDGET_H
#define WIDGET_H

#include <QAction>
#include <QDebug>
#include <QDesktopServices>
#include <QGroupBox>
#include <QHeaderView>
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QString>
#include <QStackedWidget>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QTableView>
#include <QUrl>
#include <QWidget>

namespace Ui {class Widget;}

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    //규비
    Ui::Widget *ui;
    QSqlDatabase db;
    QSqlQueryModel model;
    void initializeDataBase();
    void homeNews();
    void tableWidget_2DataBase();
    void tableWidget_3DataBase();

    //홍균
    QString brandN;
    int maincount = 0;
    int sc = 0;
    void DatabaseOpen();
    void UserInterface();
    int div = 0;

    //광선
    // 브랜드 정보 쿼리위한 각 브랜드 QSqlQueryModel 객체
    QSqlQueryModel HYUNDAI_qry, KIA_qry, GENESIS_qry, CHEVROLET_qry, RENAULT_qry, KG_MOBILITY_qry, AUDI_qry, VOLVO_qry, VOLKSWAGEN_qry, TOYOTA_qry, FORD_qry, MINI_qry;

    // 판매중인 신차 쿼리위한 각 브랜드 QSqlQueryModel 객체
    QSqlQueryModel HYUNDAI_Sales_qry, KIA_Sales_qry, GENESIS_Sales_qry, CHEVROLET_Sales_qry, RENAULT_Sales_qry, KG_MOBILITY_Sales_qry, AUDI_Sales_qry, VOLVO_Sales_qry,
        VOLKSWAGEN_Sales_qry, TOYOTA_Sales_qry, FORD_Sales_qry, MINI_Sales_qry;


private slots:
    //규비
    void btn_click();
    void btn_click2();
    void btn_click3();
    void btn_backClick();
    void ADV();

    //홍균
    void AllSelect();
    void AllBrandSelect();
    void ModelSelect();
    void BrandSelect();
    void MonthSearch(int n);
    void BeforeBtn();
    void AfterBtn();
    void MonthSelect();
    void PeriodSelect();
    void PeriodSearch();
    void TypeSelect();
    void ForeignCar();
    void KoreaCar();

    //광선
    void car_pedia_index_0(); // 차량정보 - 국산
    void car_pedia_index_1(); // 차량정보 - 수입

    void BRAND_HYUNDAI_page(); // 현대 브랜드 페이지 연결
    void BRAND_HYUNDAI_info(); // 현대 브랜드 정보 연결
    void BRAND_HYUNDAI_Salescar(); // 현대 판매중인 신차

    void BRAND_KIA_page();
    void BRAND_KIA_info();
    void BRAND_KIA_Salescar();

    void BRAND_GENESIS_page();
    void BRAND_GENESIS_info();
    void BRAND_GENESIS_Salescar();

    void BRAND_CHEVROLET_page();
    void BRAND_CHEVROLET_info();
    void BRAND_CHEVROLET_Salescar();

    void BRAND_RENAULT_page();
    void BRAND_RENAULT_info();
    void BRAND_RENAULT_Salescar();

    void BRAND_KG_MOBILITY_page();
    void BRAND_KG_MOBILITY_info();
    void BRAND_KG_MOBILITY_Salescar();

    void BRAND_AUDI_page();
    void BRAND_AUDI_info();
    void BRAND_AUDI_Salescar();

    void BRAND_VOLVO_page();
    void BRAND_VOLVO_info();
    void BRAND_VOLVO_Salescar();

    void BRAND_VOLKSWAGEN_page();
    void BRAND_VOLKSWAGEN_info();
    void BRAND_VOLKSWAGEN_Salescar();

    void BRAND_TOYOTA_page();
    void BRAND_TOYOTA_info();
    void BRAND_TOYOTA_Salescar();

    void BRAND_FORD_page();
    void BRAND_FORD_info();
    void BRAND_FORD_Salescar();

    void BRAND_MINI_page(); // 미니 브랜드 페이지 연결
    void BRAND_MINI_info(); // 미니 브랜드 정보 연결
    void BRAND_MINI_Salescar(); // 미니 판매중인 신차
    void car();


    void on_pushButton_2_clicked();
};
#endif // WIDGET_H
