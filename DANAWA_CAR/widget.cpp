#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent): QWidget(parent), ui(new Ui::Widget)
{
    //규비
    ui->setupUi(this);
    initializeDataBase(); //DB열고
    homeNews(); //홈 화면에서 뉴스출력 후 선택 시 링크 이동
    tableWidget_2DataBase(); //차량정보 화면에서 국산 신차 인기 모델 출력
    tableWidget_3DataBase(); //차량정보 화면에서 수입 신차 인기 모델 출력
    ADV(); //광고 선택 시 광고 링크로 연동 새창 팝업으로 출력

    //홍균
    UserInterface();
    //메인 제일위 (전체,브랜드별,모델별)
    connect(ui->all_btn, SIGNAL(pressed()), this, SLOT(AllSelect()));
    connect(ui->brand_btn, SIGNAL(pressed()), this, SLOT(AllBrandSelect()));
    connect(ui->model_btn, SIGNAL(pressed()), this, SLOT(ModelSelect()));

    //전체->국산차,수입차
    connect(ui->korea_btn, SIGNAL(pressed()), this, SLOT(KoreaCar()));
    connect(ui->foreign_btn, SIGNAL(pressed()), this, SLOT(ForeignCar()));

    //브랜드 아이콘 페이지 좌우 넘김 버튼,월 선택버튼, 기간선택 버튼
    connect(ui->before_bp, SIGNAL(pressed()), this, SLOT(BeforeBtn()));
    connect(ui->next_bp, SIGNAL(pressed()), this, SLOT(AfterBtn()));
    connect(ui->mon_btn, SIGNAL(pressed()), this, SLOT(MonthSelect()));
    connect(ui->period_btn, SIGNAL(pressed()), this, SLOT(PeriodSelect()));

    //상세브랜드 아이콘 선택
    connect(ui->HYUNDAI, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->KIA, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->GENESIS, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->CHEVROLET, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->RENAULT, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->KG_MOBILITY, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->TOYOTA, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->MINI, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->AUDI, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->FORD, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->VOLVO, SIGNAL(pressed()), this, SLOT(BrandSelect()));
    connect(ui->VOLKSWAGEN, SIGNAL(pressed()), this, SLOT(BrandSelect()));

    //월별 검색(콤보박스로 월 선택시),기간 선택(조회 버튼 누를시)
    connect(ui->m_mon_cb_2, SIGNAL(activated(int)), this, SLOT(MonthSearch(int)));
    connect(ui->search_btn_2, SIGNAL(pressed()), this, SLOT(PeriodSearch()));

    //차량별 아이콘 선택시
    connect(ui->type1_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type2_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type3_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type4_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type5_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type6_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type7_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type8_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type9_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type10_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type11_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));
    connect(ui->type12_btn, SIGNAL(pressed()), this, SLOT(TypeSelect()));

    //광선
    connect(ui->MiK_pbtn, SIGNAL(clicked()), this, SLOT(car_pedia_index_0())); // 차량정보 - 국산 연결
    connect(ui->MiK_pbtn_2, SIGNAL(clicked()), this, SLOT(car_pedia_index_0())); // 차량정보 - 수입 - 국산 연결
    connect(ui->Car_Company_prev_pbtn, SIGNAL(clicked()), this, SLOT(car_pedia_index_0())); // 차량정보 - < 연결
    connect(ui->Car_Company_prev_pbtn_2, SIGNAL(clicked()), this, SLOT(car_pedia_index_0())); // 차량정보 - 수입 - < 연결

    connect(ui->Imp_pbtn, SIGNAL(clicked()), this, SLOT(car_pedia_index_1())); // 차량정보 - 수입 연결
    connect(ui->Imp_pbtn_2, SIGNAL(clicked()), this, SLOT(car_pedia_index_1())); // 차량정보 - 국산 - 수입 연결
    connect(ui->Car_Company_next_pbtn, SIGNAL(clicked()), this, SLOT(car_pedia_index_1())); // 차량정보 - > 연결
    connect(ui->Car_Company_next_pbtn_2, SIGNAL(clicked()), this, SLOT(car_pedia_index_1())); // 차량정보 - 수입 - > 연결

    connect(ui->BRAND_Hometbtn, SIGNAL(clicked()), this, SLOT(Home_page())); // 차량정보 페이지 연결

    connect(ui->HYUNDAI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_HYUNDAI_page())); // 현대 브랜드 페이지 연결
    connect(ui->HYUNDAI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_HYUNDAI_info())); // 현대 브랜드 정보 연결
    connect(ui->HYUNDAI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_HYUNDAI_Salescar())); // 현대 판매중인 신차 연결

    connect(ui->KIA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KIA_page()));
    connect(ui->KIA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KIA_info()));
    connect(ui->KIA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KIA_Salescar()));

    connect(ui->GENESIS_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_GENESIS_page()));
    connect(ui->GENESIS_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_GENESIS_info()));
    connect(ui->GENESIS_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_GENESIS_Salescar()));

    connect(ui->CHEVROLET_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_CHEVROLET_page()));
    connect(ui->CHEVROLET_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_CHEVROLET_info()));
    connect(ui->CHEVROLET_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_CHEVROLET_Salescar()));

    connect(ui->RENAULT_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_RENAULT_page()));
    connect(ui->RENAULT_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_RENAULT_info()));
    connect(ui->RENAULT_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_RENAULT_Salescar()));

    connect(ui->KG_MOBILITY_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KG_MOBILITY_page()));
    connect(ui->KG_MOBILITY_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KG_MOBILITY_info()));
    connect(ui->KG_MOBILITY_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_KG_MOBILITY_Salescar()));

    connect(ui->AUDI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_AUDI_page()));
    connect(ui->AUDI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_AUDI_info()));
    connect(ui->AUDI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_AUDI_Salescar()));

    connect(ui->VOLVO_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLVO_page()));
    connect(ui->VOLVO_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLVO_info()));
    connect(ui->VOLVO_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLVO_Salescar()));

    connect(ui->VOLKSWAGEN_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLKSWAGEN_page()));
    connect(ui->VOLKSWAGEN_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLKSWAGEN_info()));
    connect(ui->VOLKSWAGEN_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_VOLKSWAGEN_Salescar()));

    connect(ui->TOYOTA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_TOYOTA_page()));
    connect(ui->TOYOTA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_TOYOTA_info()));
    connect(ui->TOYOTA_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_TOYOTA_Salescar()));

    connect(ui->FORD_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_FORD_page()));
    connect(ui->FORD_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_FORD_info()));
    connect(ui->FORD_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_FORD_Salescar()));

    connect(ui->MINI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_MINI_page())); // 미니 브랜드 페이지 연결
    connect(ui->MINI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_MINI_info())); // 미니 브랜드 정보 연결
    connect(ui->MINI_tbtn, SIGNAL(clicked()), this, SLOT(BRAND_MINI_Salescar())); // 미니 판매중인 신차 연결
    car();
}


/*함수이름: initializeDataBase()
기능: DANAWA DB 열기
반환값: 없음*/
void Widget::initializeDataBase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./DANAWA" );
    if( !db.open() )
        qDebug() << db.lastError();
}
/*함수이름: homeNews()
기능: 홈 화면에 뉴스출력 후 클릭 시 인터넷 팝업되며 해당 기사링크로 이동
반환값: 없음*/
void Widget::homeNews()
{
    ui->label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label->setOpenExternalLinks(true);
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setText("<a href=\"https://url.kr/clwr5i\" style=\"text-decoration: none;\"> [칼럼] 미래차 전문 인력 절실한데 정부는 국내 유일 양성 프로그램 폐기하나 </a>");

    ui->label_2->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_2->setOpenExternalLinks(true);
    ui->label_2->setTextFormat(Qt::RichText);
    ui->label_2->setText("<a href=\"https://url.kr/l4j6mo\"style=\"text-decoration: none;\"> 르노코리아,스타필드수원에 새로운 콘셉트의 신규 전시장 오픈</a>");

    ui->label_3->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_3->setOpenExternalLinks(true);
    ui->label_3->setTextFormat(Qt::RichText);
    ui->label_3->setText("<a href=\"https://url.kr/q41pnm\"style=\"text-decoration: none;\"> 현대차그룹, 설 명절 협력사 자금 부담 완화 납품대금 2조 1447억 원 조기 지급</a>");

    ui->label_4->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_4->setOpenExternalLinks(true);
    ui->label_4->setTextFormat(Qt::RichText);
    ui->label_4->setText("<a href=\"https://url.kr/usapk6\"style=\"text-decoration: none;\"> 기아 전기 픽업트럭 '타스만' 언제 나오길래… 국내서 첫 프로토타입 포착</a>");

    ui->label_5->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_5->setOpenExternalLinks(true);
    ui->label_5->setTextFormat(Qt::RichText);
    ui->label_5->setText("<a href=\"https://url.kr/siwhko\"style=\"text-decoration: none;\"> 소비자가 꼽은 LPG 트럭 인기 비결은 ‘경제성’</a>");

    ui->label_6->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_6->setOpenExternalLinks(true);
    ui->label_6->setTextFormat(Qt::RichText);
    ui->label_6->setText("<a href=\"https://https://url.kr/t2g4qd\"style=\"text-decoration: none;\"> BMW 그룹 코리아, 서일대학교와 자동차 산업 인재 양성 위한 MOU 체결</a>");

    ui->label_7->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_7->setOpenExternalLinks(true);
    ui->label_7->setTextFormat(Qt::RichText);
    ui->label_7->setText("<a href=\"https://url.kr/645t3j\"style=\"text-decoration: none;\"> 자동차 1월 수출액 사상 최대, 전년 동월 대비 24.8% 증가...친환경차 호조</a>");

    ui->label_8->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_8->setOpenExternalLinks(true);
    ui->label_8->setTextFormat(Qt::RichText);
    ui->label_8->setText("<a href=\"https://url.kr/aor51e\"style=\"text-decoration: none;\"> 대기보전법 개정, 불법 배출가스저감장치 7년 이하 징역 또는 1억 원 벌금</a>");

    ui->label_13->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_13->setOpenExternalLinks(true);
    ui->label_13->setTextFormat(Qt::RichText);
    ui->label_13->setText("<a href=\"https://url.kr/dgrck7\"style=\"text-decoration: none;\"> 아키오 도요타, “다이하츠 등 사기 행각에 대해 사과”</a>");

    ui->label_14->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_14->setOpenExternalLinks(true);
    ui->label_14->setTextFormat(Qt::RichText);
    ui->label_14->setText("<a href=\"https://url.kr/qe1mbw\"style=\"text-decoration: none;\"> GM, 플러그인 하이브리드 전기차 버전 추가한다</a>");

    ui->label_15->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_15->setOpenExternalLinks(true);
    ui->label_15->setTextFormat(Qt::RichText);
    ui->label_15->setText("<a href=\"https://url.kr/8lzhno\"style=\"text-decoration: none;\"> 람보르기니, 2030년까지 탄소 중립 확대 목표 발표</a>");

    ui->label_16->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label_16->setOpenExternalLinks(true);
    ui->label_16->setTextFormat(Qt::RichText);
    ui->label_16->setText("<a href=\"https://buly.kr/9MNfUUt\"style=\"text-decoration: none;\"> 6억 넘는 롤스로이스 전기차도 화재 위험… NHTSA '스펙터' 리콜 명령</a>");
}
/*함수이름: tableWidget_2DataBase()
기능: 차량정보 화면에서 국산 신차 인기 모델 출력
tableWidget_2 테이블 위젯에 SALES 테이블에서 BRAND, MODEL / CARINFO 테이블에서 PRICE, IMAGE 데이터 가져오기
반환값: 없음*/
void Widget::tableWidget_2DataBase()
{
    ui->tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model.setQuery("SELECT a.BRAND, a.MODEL, b.PRICE, b.IMAGE FROM SALES a JOIN CARINFO b ON (b.MODEL = a.MODEL) WHERE a.AREA = 0 ORDER BY a.DEC DESC LIMIT 5");
    for(int i =0; i < model.rowCount(); ++i)
    {
        QString BRAND = model.record(i).value("BRAND").toString();
        QString MODEL = model.record(i).value("MODEL").toString();
        QString PRICE = model.record(i).value("PRICE").toString();
        QString model_n = model.record(i).value("IMAGE").toString();
        QPushButton* mod = new QPushButton(MODEL);
        mod->setStyleSheet("color: rgb(0, 66, 199);");
        QPixmap image(":/Danawa_car_image_M/"+model_n+".png");
        QTableWidgetItem *model_p = new QTableWidgetItem();
        model_p->setData(Qt::DecorationRole, image);

        ui->tableWidget_2->insertRow(i);
        ui->tableWidget_2->setItem(i, 0, model_p);
        ui->tableWidget_2->setItem(i, 1, new QTableWidgetItem(BRAND));
        ui->tableWidget_2->setCellWidget(i, 2, mod);
        ui->tableWidget_2->setItem(i, 3, new QTableWidgetItem(PRICE));
        connect(mod, &QPushButton::clicked, this, &Widget::btn_click3);
    }
}
/*함수이름: tableWidget_3DataBase()
기능: 차량정보 화면에서 수입 신차 인기 모델 출력
tableWidget_3 테이블 위젯에 SALES 테이블에서 BRAND, MODEL / CARINFO 테이블에서 PRICE, IMAGE 데이터 가져오기
반환값: 없음*/
void Widget::tableWidget_3DataBase()
{
    ui->tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    model.setQuery("SELECT a.BRAND, a.MODEL, b.PRICE, b.IMAGE FROM SALES a JOIN CARINFO b ON (b.MODEL = a.MODEL) WHERE a.AREA = 1 ORDER BY a.DEC DESC LIMIT 5");
    for(int i =0; i < model.rowCount(); ++i)
    {
        QString BRAND = model.record(i).value("BRAND").toString();
        QString MODEL = model.record(i).value("MODEL").toString();
        QString PRICE = model.record(i).value("PRICE").toString();
        QString model_n = model.record(i).value("IMAGE").toString();
        QPushButton* mod = new QPushButton(MODEL);
        mod->setStyleSheet("color: rgb(0, 66, 199);");
        QPixmap image(":/Danawa_car_image_M/"+model_n+".png");
        QTableWidgetItem *model_p = new QTableWidgetItem();
        model_p->setData(Qt::DecorationRole, image);

        ui->tableWidget_3->insertRow(i);
        ui->tableWidget_3->setItem(i, 0, model_p);
        ui->tableWidget_3->setItem(i, 1, new QTableWidgetItem(BRAND));
        ui->tableWidget_3->setCellWidget(i, 2, mod);
        ui->tableWidget_3->setItem(i, 3, new QTableWidgetItem(PRICE));
        connect(mod, &QPushButton::clicked, this, &Widget::btn_click);
    }
}
/*함수이름: initializeDataBase()
기능: 광고 선택 시 광고 링크로 연동 새창 팝업으로 출력
반환값: 없음*/
void Widget::ADV()
{
    ui->adv_lb->setStyleSheet("border-image: url(/Users/lms/Downloads/광고1.png);");
}

//홍균
// 테이블 모델 크기 조정
void Widget::UserInterface()
{
    ui->all_tbl->setColumnWidth(0,50);
    ui->all_tbl->setColumnWidth(1,200);
    ui->all_tbl->horizontalHeader()->setStretchLastSection(true);
    ui->korea_tbl->setColumnWidth(0,50);
    ui->korea_tbl->setColumnWidth(1,200);
    ui->korea_tbl->setColumnWidth(2,90);
    ui->korea_tbl->horizontalHeader()->setStretchLastSection(true);
    ui->foreign_tbl->setColumnWidth(0,50);
    ui->foreign_tbl->setColumnWidth(1,200);
    ui->foreign_tbl->setColumnWidth(2,90);
    ui->foreign_tbl->horizontalHeader()->setStretchLastSection(true);
    ui->model_tbl->setColumnWidth(0,50);
    ui->model_tbl->setColumnWidth(1,200);
    ui->model_tbl->setColumnWidth(2,90);
    ui->model_tbl->horizontalHeader()->setStretchLastSection(true);
    ui->br_tbl->setColumnWidth(0,50);
    ui->br_tbl->setColumnWidth(1,200);
    ui->br_tbl->setColumnWidth(2,90);
    ui->br_tbl->horizontalHeader()->setStretchLastSection(true);
}

// 광선
void Widget::BRAND_MINI_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(11);
}

void Widget::BRAND_FORD_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(10);
}

void Widget::BRAND_TOYOTA_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(9);
}

void Widget::BRAND_VOLKSWAGEN_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(8);
}

void Widget::BRAND_VOLVO_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(7);
}

void Widget::BRAND_AUDI_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(6);
}

void Widget::BRAND_KG_MOBILITY_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(5);
}

void Widget::BRAND_RENAULT_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(4);
}

void Widget::BRAND_CHEVROLET_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(3);
}

void Widget::BRAND_GENESIS_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(2);
}

void Widget::BRAND_KIA_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(1);
}

void Widget::BRAND_HYUNDAI_Salescar()
{
    ui->SALES_stackedWidget->setCurrentIndex(0);
}
// 차량정보에서 차량 버튼 클릭 시 차량 상세 페이지로 이동 전환
void Widget::car()
{
    connect(ui->A3, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->A4, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->A5, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->A6, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->A7, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->etronGT, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->A8, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q2, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q3, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q4etron, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q5, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q7, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Q8, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->etron, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->colorado, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->equinox, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->tahoe, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->trailblazer, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->traverse, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->traxcrossover, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Bronco, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Expedition, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Explorer, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Mustang, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Ranger, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ElectrifiedG80, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ElectrifiedGV70, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->G70, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->G80, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->G90, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->GV60, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->GV70, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->newG80, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->newGV80, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->avante, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->avanteN, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->casper, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->county, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->countyelectric, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->grandeur, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ioniq5, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ioniq5N, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ioniq6, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->kona, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->konaelectric, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->mighty, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->newtucson, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->nexo, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->palisade, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->pavise, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->porest, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->porter2, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->porter2electric, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->santafe, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->solati, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->sonata, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->staria, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->tucson, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->venue, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->korando, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->rextonnewarena, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->rextonsports, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->rextonsportskhan, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->tivoli, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->tivoliair, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->torres, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->torresevx, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->bongo3, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->bongo3ev, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->carnival, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ev6, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ev9, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->k3, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->k5, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->k8, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->k9, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->mohave, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->morning, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->niro, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->niroev, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->niroplus, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ray, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->rayev, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->seltos, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->sorento, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->sportage, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Clubman, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Convertible, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Countryman, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Electric, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Hatch, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->master, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->qm6, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->sm6, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->xm3, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Alphard, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Camry, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Crown, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->GR86, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->GRSUPRA, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Highlander, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Prius, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->RAV4, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Sienna, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Arteon, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Golf, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->ID4, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->TheNewJetta, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->TheTouareg, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->Tiguan, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->C40Recharge, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->S60, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->S90, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->V60CrossCountry, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->V90Cross_Country, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->XC40, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->XC40Recharge, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->XC60, SIGNAL(clicked()), this, SLOT(btn_click2()));
    connect(ui->XC90, SIGNAL(clicked()), this, SLOT(btn_click2()));
}
//규비 슬롯
/*함수이름: btn_click()
기능: 차량 선택 시 차량 상세 화면 출력
CARINFO 테이블에서 IMAGE, MODEL, PRICE, START, TYPE, FUEL, EFF 데이터 가져오기
반환값: 없음*/
void Widget::btn_click()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(1); //페이지전환
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString namee = btn->text();
    if(namee == "The New Jetta")
        namee = "TheNewJetta";
    model.setQuery("SELECT IMAGE, BRAND, MODEL, PRICE, START, TYPE, FUEL, EFF FROM CARINFO WHERE IMAGE = \""+namee+"\"");
    for(int i =0; i < model.rowCount(); ++i)
    {
        QString IMAGE = model.record(i).value("IMAGE").toString();
        QString BRAND = model.record(i).value("BRAND").toString();
        QString MODEL = model.record(i).value("MODEL").toString();
        QString PRICE = model.record(i).value("PRICE").toString();
        QString START = model.record(i).value("START").toString();
        QString TYPE = model.record(i).value("TYPE").toString();
        QString FUEL = model.record(i).value("FUEL").toString();
        QString EFF = model.record(i).value("EFF").toString();

        ui->label_17->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+IMAGE+".png);");
        ui->label_18->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+BRAND+".png);");
        ui->label_19->setText(MODEL);
        ui->label_20->setText(PRICE);
        ui->label_21->setText(START);
        ui->label_22->setText(TYPE);
        ui->label_23->setText(FUEL);
        ui->label_24->setText(EFF);
    }
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::btn_backClick);
}
/*함수이름: btn_click2()
기능: 차량 선택 시 차량 상세 화면 출력
CARINFO 테이블에서 IMAGE, MODEL, PRICE, START, TYPE, FUEL, EFF 데이터 가져오기
반환값: 없음*/
void Widget::btn_click2()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(1); //페이지전환
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString namee = btn->objectName();
    model.setQuery("SELECT IMAGE, BRAND, MODEL, PRICE, START, TYPE, FUEL, EFF FROM CARINFO WHERE IMAGE = '"+namee+"';");
    for(int i =0; i < model.rowCount(); ++i)
    {
        QString IMAGE = model.record(i).value("IMAGE").toString();
        QString BRAND = model.record(i).value("BRAND").toString();
        QString MODEL = model.record(i).value("MODEL").toString();
        QString PRICE = model.record(i).value("PRICE").toString();
        QString START = model.record(i).value("START").toString();
        QString TYPE = model.record(i).value("TYPE").toString();
        QString FUEL = model.record(i).value("FUEL").toString();
        QString EFF = model.record(i).value("EFF").toString();

        ui->label_17->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+IMAGE+".png);");
        ui->label_18->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+BRAND+".png);");
        ui->label_19->setText(MODEL);
        ui->label_20->setText(PRICE);
        ui->label_21->setText(START);
        ui->label_22->setText(TYPE);
        ui->label_23->setText(FUEL);
        ui->label_24->setText(EFF);
    }
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::btn_backClick);
}
/*함수이름: btn_click()
기능: 차량 선택 시 차량 상세 화면 출력
CARINFO 테이블에서 IMAGE, MODEL, PRICE, START, TYPE, FUEL, EFF 데이터 가져오기
반환값: 없음*/
void Widget::btn_click3()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(1); //페이지전환
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    QString namee = btn->text();
    if(namee == "The New Jetta")
        namee = "TheNewJetta";
    model.setQuery("SELECT IMAGE, BRAND, MODEL, PRICE, START, TYPE, FUEL, EFF FROM CARINFO WHERE MODEL = \""+namee+"\"");
    for(int i =0; i < model.rowCount(); ++i)
    {
        QString IMAGE = model.record(i).value("IMAGE").toString();
        QString BRAND = model.record(i).value("BRAND").toString();
        QString MODEL = model.record(i).value("MODEL").toString();
        QString PRICE = model.record(i).value("PRICE").toString();
        QString START = model.record(i).value("START").toString();
        QString TYPE = model.record(i).value("TYPE").toString();
        QString FUEL = model.record(i).value("FUEL").toString();
        QString EFF = model.record(i).value("EFF").toString();

        ui->label_17->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+IMAGE+".png);");
        ui->label_18->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+BRAND+".png);");
        ui->label_19->setText(MODEL);
        ui->label_20->setText(PRICE);
        ui->label_21->setText(START);
        ui->label_22->setText(TYPE);
        ui->label_23->setText(FUEL);
        ui->label_24->setText(EFF);
    }
    connect(ui->pushButton, &QPushButton::clicked, this, &Widget::btn_backClick);
}
/*함수이름: btn_backClick()
기능: 뒤로가기 버튼 클릭 시 차량정보 페이지로 전환
반환값: 없음*/
void Widget::btn_backClick()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(0);
}
/*함수이름: on_pushButton_2_clicked()
 기능: 광고 클릭 시 링크이동
빈환값 없음*/
void Widget::on_pushButton_2_clicked()
{
    QDesktopServices::openUrl(QUrl("https://direct.samsungfire.com/ria/pc/product/car/?state=Front"));
}

//홍균 슬롯
// 브랜드버튼, 차량아이콘 이전버튼
void Widget::BeforeBtn()
{
    int pagecount = ui->stack_brand->currentIndex();
    if (pagecount > 0)
        ui->stack_brand->setCurrentIndex(pagecount - 1);
    else
        ui->stack_brand->setCurrentIndex(3);
}
// 다음으로 버튼
void Widget::AfterBtn()
{
    int pagecount = ui->stack_brand->currentIndex();
    if (pagecount < 3)
        ui->stack_brand->setCurrentIndex(pagecount + 1);
    else
        ui->stack_brand->setCurrentIndex(0);
}
// 판매실적 (월) / 기간 선택
void Widget::MonthSelect()
{
    ui->period_stack->setCurrentIndex(0);
}
// 판매실적 월 / (기간) 선택
void Widget::PeriodSelect()
{
    ui->period_stack->setCurrentIndex(1);
}
// 판매실적 (전체)/ 브랜드별/ 모델별
void Widget::AllSelect() //변경
{
    ui->all_btn->setStyleSheet("QPushButton:checked { color: blue; }");
    sc = 0;
    int bm = 0;
    if (ui->all_tbl->columnCount()==4)
        ui->all_tbl->removeColumn(3);
    ui->page_stack->setCurrentIndex(0);
    ui->all_tbl->setRowCount(0);
    ui->all_tbl->insertColumn(3);
    ui->all_tbl->setColumnWidth(0,50);
    ui->all_tbl->setColumnWidth(1,200);
    ui->all_tbl->setColumnWidth(2,90);
    ui->all_tbl->horizontalHeader()->setStretchLastSection(true);
    ui->all_tbl->setHorizontalHeaderItem(3,new QTableWidgetItem("CHANGE"));
    QSqlQueryModel qry;
    QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    qry.setQuery("SELECT MODEL,"+Month[ui->m_mon_cb_2->currentIndex()]+" FROM SALES WHERE AREA = "+QString::number(div)+" ORDER BY "+Month[ui->m_mon_cb_2->currentIndex()]+" DESC LIMIT 10;");
    for (int i = 0; i < qry.rowCount(); i++)
    {
        QString car = qry.record(i).value("MODEL").toString();
        int sale = qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toInt();
        ui->all_tbl->insertRow(i);
        ui->all_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->all_tbl->setItem(i,1,new QTableWidgetItem(car));
        ui->all_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
    }
    if (ui->m_mon_cb_2->currentIndex() != 0)
    {
        qry.setQuery("SELECT "+Month[ui->m_mon_cb_2->currentIndex()]+","+Month[ui->m_mon_cb_2->currentIndex()-1]+" FROM SALES WHERE AREA = "+QString::number(div)+" ORDER BY "+Month[ui->m_mon_cb_2->currentIndex()]+" DESC LIMIT 10;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            bm = qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toInt();
            bm -= qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()-1]).toInt();
            if (bm > 0)
            {
                QTableWidgetItem *item = new QTableWidgetItem("▲" + QString::number(bm));
                QColor color(QColor("red"));
                item->setData(Qt::ForegroundRole,color);
                ui->all_tbl->setItem(i,3,item);
            }
            else
            {
                QTableWidgetItem *item = new QTableWidgetItem("▼" + QString::number(bm*(-1)));
                QColor color(QColor("blue"));
                item->setData(Qt::ForegroundRole,color);
                ui->all_tbl->setItem(i,3,item);
            }
        }
    }

}
// 판매실적 전체/ (브랜드별)/ 모델별
void Widget::AllBrandSelect()
{
    ui->brand_btn->setStyleSheet("QPushButton:checked { color: blue; }");
    sc = 0;
    ui->page_stack->setCurrentIndex(1);
    ui->korea_tbl->setRowCount(0);
    ui->foreign_tbl->setRowCount(0);
    ui->korea_lb->setText("국산차 2023." + ui->m_mon_cb_2->currentText());
    ui->foreign_lb->setText("수입차 2023." + ui->m_mon_cb_2->currentText());
    QSqlQueryModel qry;
    QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    qry.setQuery("SELECT SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES WHERE AREA = 0;");
    double sum1 = qry.record(0).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toDouble();
    ui->korea_total_lb->setText("총합 : " + QString::number(sum1));
    qry.setQuery("SELECT BRAND,SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES GROUP BY BRAND HAVING AREA = 0 ORDER BY SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") DESC;");
    for (int i = 0; i < qry.rowCount(); i++)
    {
        QString namebrand = qry.record(i).value("BRAND").toString();
        int sale = qry.record(i).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toInt();
        double rate = round((sale/sum1)*100*10)/10;
        ui->korea_tbl->insertRow(i);
        ui->korea_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->korea_tbl->setItem(i,1,new QTableWidgetItem(namebrand));
        ui->korea_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
        ui->korea_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
    }
    qry.setQuery("SELECT SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES WHERE AREA = 1;");
    double sum2 = qry.record(0).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toDouble();
    ui->foreign_total_lb->setText("총합 : " + QString::number(sum2));
    qry.setQuery("SELECT BRAND,SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES GROUP BY BRAND HAVING AREA = 1 ORDER BY SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") DESC;");
    for (int i = 0; i < qry.rowCount(); i++)
    {
        QString namebrand = qry.record(i).value("BRAND").toString();
        int sale = qry.record(i).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toInt();
        double rate = round((sale/sum2)*100*10)/10;
        ui->foreign_tbl->insertRow(i);
        ui->foreign_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        ui->foreign_tbl->setItem(i,1,new QTableWidgetItem(namebrand));
        ui->foreign_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
        ui->foreign_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
    }
}
// 판매실적 전체/ 브랜드별/ (모델별)
void Widget::ModelSelect()
{
    ui->model_btn->setStyleSheet("QPushButton:checked { color: blue; }");
    sc = 0;
    ui->model_tbl->setRowCount(0);
    ui->page_stack->setCurrentIndex(2);
    QSqlQueryModel qry;
    QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    qry.setQuery("SELECT SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES;");
    double sum = qry.record(0).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toDouble();
    qry.setQuery("SELECT MODEL,"+Month[ui->m_mon_cb_2->currentIndex()]+" FROM SALES ORDER BY "+Month[ui->m_mon_cb_2->currentIndex()]+" DESC;");
    for (int i = 0; i < qry.rowCount(); i++)
    {
        QString car = qry.record(i).value("MODEL").toString();
        int sale = qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toInt();
        double rate = round((sale/sum)*100*10)/10;
        if (sale != 0)
        {
            ui->model_tbl->insertRow(i);
            ui->model_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->model_tbl->setItem(i,1,new QTableWidgetItem(car));
            ui->model_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
            ui->model_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
        }
    }
}
// 판매실적 상세 브랜드 선택 버튼
void Widget::BrandSelect()
{
    ui->brand_btn->setChecked(true);
    ui->brand_btn->setStyleSheet("QPushButton:checked { color: blue; }");
    ui->br_tbl->setRowCount(0);
    ui->page_stack->setCurrentIndex(3);
    if (maincount == 0)
    {
        QPushButton *btnName = qobject_cast<QPushButton*>(sender());
        brandN = btnName->objectName();
    }
    ui->br_lb->setStyleSheet("border-image: url(:/danawa_car/Danawa_car_image/"+brandN+".png);");
    QSqlQueryModel qry;
    QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    qry.setQuery("SELECT SUM("+Month[ui->m_mon_cb_2->currentIndex()]+") FROM SALES WHERE BRAND = '"+brandN+"';");
    double sum = qry.record(0).value("SUM("+Month[ui->m_mon_cb_2->currentIndex()]+")").toDouble();
    ui->br_total_lb->setText("판매량 : " + QString::number(sum));
    qry.setQuery("SELECT MODEL,"+Month[ui->m_mon_cb_2->currentIndex()]+" FROM SALES WHERE BRAND = '"+brandN+"' ORDER BY "+Month[ui->m_mon_cb_2->currentIndex()]+" DESC;");
    for (int i =0,j=0; i < qry.rowCount(); i++)
    {
        QString car = qry.record(i).value("MODEL").toString();
        int sale = qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toInt();
        double rate = round((sale/sum)*100*10)/10;
        if (sale != 0)
        {
            ui->br_tbl->insertRow(j);
            ui->br_tbl->setItem(j,0,new QTableWidgetItem(QString::number(j+1)));
            ui->br_tbl->setItem(j,1,new QTableWidgetItem(car));
            ui->br_tbl->setItem(j,2,new QTableWidgetItem(QString::number(sale)));
            ui->br_tbl->setItem(j,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
            j++;
        }
    }
    if (ui->m_mon_cb_2->currentIndex() != 0)
    {
        int bm = 0;
        for(int i = ui->m_mon_cb_2->currentIndex(),cnt = 0;i > ui->m_mon_cb_2->currentIndex()-2;i--,cnt++)
        {
            qry.setQuery("SELECT SUM("+Month[i]+") FROM SALES WHERE BRAND = '"+brandN+"';");
            if (bm <= 0)
                bm = qry.record(0).value("SUM("+Month[i]+")").toInt();
            else
                bm -= qry.record(0).value("SUM("+Month[i]+")").toInt();
            if (cnt == 1)
                ui->br_bf_lb->setText("전월대비 : " + QString::number(qry.record(0).value("SUM("+Month[i]+")").toInt()));
        }
        if (bm > 0)
        {
            ui->br_cr_lb->setText("▲" + QString::number(bm));
            ui->br_cr_lb->setStyleSheet("color: rgb(255,0,0);");
        }
        else if (bm < 0)
        {
            ui->br_cr_lb->setText("▼" + QString::number(bm*(-1)));
            ui->br_cr_lb->setStyleSheet("color: rgb(0,0,255);");
        }
    }
    maincount = 0;
}
// 판매 실적 차종 선택 버튼
void Widget::TypeSelect()
{
    ui->model_btn->setChecked(true);
    ui->model_btn->setStyleSheet("QPushButton:checked { color: blue; }");
    sc = 2;
    ui->model_tbl->setRowCount(0);
    ui->page_stack->setCurrentIndex(2);
    if (maincount == 0)
    {
        QPushButton *btnName = qobject_cast<QPushButton*>(sender());
        brandN = btnName->objectName();
    }
    QSqlQueryModel qry;
    QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
    qry.setQuery("SELECT SALES."+Month[ui->m_mon_cb_2->currentIndex()]+" FROM TYPENAME INNER JOIN SALES ON SALES.TYPE = TYPENAME.TYPE WHERE NAME = '"+brandN+"';");
    double sum = 0;
    for (int i = 0; i < qry.rowCount(); i++)
        sum += qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toDouble();
    qry.setQuery("SELECT SALES.MODEL,SALES."+Month[ui->m_mon_cb_2->currentIndex()]+" FROM TYPENAME INNER JOIN SALES ON SALES.TYPE = TYPENAME.TYPE WHERE NAME = '"+brandN+"' ORDER BY 2 DESC;");
    for (int i =0,j=0; i < qry.rowCount(); i++)
    {
        QString car = qry.record(i).value("MODEL").toString();
        int sale = qry.record(i).value(Month[ui->m_mon_cb_2->currentIndex()]).toInt();
        double rate = round((sale/sum)*100*10)/10;
        if (sale != 0)
        {
            ui->model_tbl->insertRow(j);
            ui->model_tbl->setItem(j,0,new QTableWidgetItem(QString::number(j+1)));
            ui->model_tbl->setItem(j,1,new QTableWidgetItem(car));
            ui->model_tbl->setItem(j,2,new QTableWidgetItem(QString::number(sale)));
            ui->model_tbl->setItem(j,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
            j++;
        }
    }
    maincount = 0;
}
// 판매 실적 월 선택 버튼
void Widget::MonthSearch(int n) //변경
{
    qDebug() << n;
    if (ui->page_stack->currentIndex() == 0)
        AllSelect();
    else if (ui->page_stack->currentIndex() == 1)
        AllBrandSelect();
    else if (ui->page_stack->currentIndex() == 2 && sc == 2)
    {
        maincount = 1;
        TypeSelect();
    }
    else if (ui->page_stack->currentIndex() == 2)
        ModelSelect();
    else
    {
        sc = 1;
        maincount = 1;
        BrandSelect();
    }
}
// 판매 실적 (기간 선택) 조회 버튼
void Widget::PeriodSearch() //변경
{
    if (ui->page_stack->currentIndex() == 0)
    {
        ui->all_tbl->setRowCount(0);
        ui->page_stack->setCurrentIndex(0);
        ui->all_tbl->setColumnCount(3);
        ui->all_tbl->setColumnWidth(0,50);
        ui->all_tbl->setColumnWidth(1,200);
        ui->all_tbl->horizontalHeader()->setStretchLastSection(true);

        ui->page_stack->setCurrentIndex(0);
        QSqlQueryModel qry;
        QString plusqry = "";
        QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
        for (int i = ui->p_fmon_cb_2->currentIndex(); i <= ui->p_lmon_cb_2->currentIndex(); i++)
        {
            plusqry += Month[i];
            if (i != ui->p_lmon_cb_2->currentIndex())
                plusqry += "+";
        }
        qry.setQuery("SELECT MODEL,"+plusqry+" FROM SALES WHERE AREA = "+QString::number(div)+" ORDER BY "+plusqry+" DESC LIMIT 10;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString car = qry.record(i).value("MODEL").toString();
            int sumsale = qry.record(i).value(plusqry).toInt();
            ui->all_tbl->insertRow(i);
            ui->all_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->all_tbl->setItem(i,1,new QTableWidgetItem(car));
            ui->all_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sumsale)));
        }
    }
    else if (ui->page_stack->currentIndex() == 1)
    {
        ui->korea_tbl->setRowCount(0);
        ui->foreign_tbl->setRowCount(0);
        ui->korea_lb->setText("국산차");
        ui->foreign_lb->setText("수입차");
        QSqlQueryModel qry;
        QString plusqry = "";
        QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
        for (int i = ui->p_fmon_cb_2->currentIndex(); i <= ui->p_lmon_cb_2->currentIndex(); i++)
        {
            plusqry += Month[i];
            if (i != ui->p_lmon_cb_2->currentIndex())
                plusqry += " + ";
        }
        qry.setQuery("SELECT SUM("+plusqry+") FROM SALES WHERE AREA = 0;");
        double sum1 = qry.record(0).value("SUM("+plusqry+")").toDouble();
        qry.setQuery("SELECT BRAND,SUM("+plusqry+") FROM SALES WHERE AREA = 0 GROUP BY BRAND ORDER BY SUM("+plusqry+") DESC;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString namebrand = qry.record(i).value("BRAND").toString();
            int sale = qry.record(i).value("SUM("+plusqry+")").toInt();
            double rate = round((sale/sum1)*100*10)/10;
            ui->korea_tbl->insertRow(i);
            ui->korea_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->korea_tbl->setItem(i,1,new QTableWidgetItem(namebrand));
            ui->korea_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
            ui->korea_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
        }
        qry.setQuery("SELECT SUM("+plusqry+") FROM SALES WHERE AREA = 1;");
        double sum2 = qry.record(0).value("SUM("+plusqry+")").toDouble();
        qry.setQuery("SELECT BRAND,SUM("+plusqry+") FROM SALES WHERE AREA = 1 GROUP BY BRAND ORDER BY SUM("+plusqry+") DESC;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString namebrand = qry.record(i).value("BRAND").toString();
            int sale = qry.record(i).value("SUM("+plusqry+")").toInt();
            double rate = round((sale/sum2)*100*10)/10;
            ui->foreign_tbl->insertRow(i);
            ui->foreign_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            ui->foreign_tbl->setItem(i,1,new QTableWidgetItem(namebrand));
            ui->foreign_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
            ui->foreign_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
        }
    }
    else if (ui->page_stack->currentIndex() == 2 && sc == 0)
    {
        ui->model_tbl->setRowCount(0);
        ui->page_stack->setCurrentIndex(2);
        QSqlQueryModel qry;
        QString plusqry = "";
        QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
        for (int i = ui->p_fmon_cb_2->currentIndex(); i <= ui->p_lmon_cb_2->currentIndex(); i++)
        {
            plusqry += Month[i];
            if (i != ui->p_lmon_cb_2->currentIndex())
                plusqry += " + ";
        }
        qry.setQuery("SELECT SUM("+plusqry+") FROM SALES;");
        double sum = qry.record(0).value("SUM("+plusqry+")").toDouble();
        qry.setQuery("SELECT MODEL,"+plusqry+" FROM SALES ORDER BY "+plusqry+" DESC;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString car = qry.record(i).value("MODEL").toString();
            int sale = qry.record(i).value(plusqry).toInt();
            double rate = round((sale/sum)*100*10)/10;
            if (sale != 0)
            {
                ui->model_tbl->insertRow(i);
                ui->model_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
                ui->model_tbl->setItem(i,1,new QTableWidgetItem(car));
                ui->model_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
                ui->model_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
            }
        }
    }
    else if (ui->page_stack->currentIndex() == 2 && sc == 2)
    {
        ui->model_tbl->setRowCount(0);
        ui->page_stack->setCurrentIndex(2);
        QSqlQueryModel qry;
        QString plusqry = "";
        QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
        for (int i = ui->p_fmon_cb_2->currentIndex(); i <= ui->p_lmon_cb_2->currentIndex(); i++)
        {
            plusqry += Month[i];
            if (i != ui->p_lmon_cb_2->currentIndex())
                plusqry += " + ";
        }
        qry.setQuery("SELECT SALES."+plusqry+" FROM TYPENAME INNER JOIN SALES ON SALES.TYPE = TYPENAME.TYPE WHERE NAME = '"+brandN+"';");
        double sum = 0;
        for (int i = 0; i < qry.rowCount(); i++)
            sum += qry.record(i).value("SALES."+plusqry+"").toDouble();

        qry.setQuery("SELECT SALES.MODEL,SALES."+plusqry+" FROM TYPENAME INNER JOIN SALES ON SALES.TYPE = TYPENAME.TYPE WHERE NAME = '"+brandN+"' ORDER BY "+plusqry+" DESC;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString car = qry.record(i).value("MODEL").toString();
            int sale = qry.record(i).value("SALES."+plusqry+"").toInt();
            double rate = round((sale/sum)*100*10)/10;
            qDebug() << car << sale;
            if (sale != 0)
            {
                ui->model_tbl->insertRow(i);
                ui->model_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
                ui->model_tbl->setItem(i,1,new QTableWidgetItem(car));
                ui->model_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
                ui->model_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
            }
        }
    }
    else
    {
        ui->model_tbl->setRowCount(0);
        ui->page_stack->setCurrentIndex(2);
        QSqlQueryModel qry;
        QString plusqry = "";
        QStringList Month = QStringList() << "JAN" << "FEB" << "MAR" << "APR" << "MAY" << "JUN" << "JUL" << "AUG" << "SEP" << "OCT" << "NOV" << "DEC";
        for (int i = ui->p_fmon_cb_2->currentIndex(); i <= ui->p_lmon_cb_2->currentIndex(); i++)
        {
            plusqry += Month[i];
            if (i != ui->p_lmon_cb_2->currentIndex())
                plusqry += " + ";
        }
        qry.setQuery("SELECT SUM("+plusqry+") FROM SALES WHERE BRAND = '"+brandN+"';");
        double sum = qry.record(0).value("SUM("+plusqry+")").toDouble();
        qry.setQuery("SELECT MODEL,"+plusqry+" FROM SALES WHERE BRAND = '"+brandN+"' ORDER BY "+plusqry+" DESC;");
        for (int i = 0; i < qry.rowCount(); i++)
        {
            QString car = qry.record(i).value("MODEL").toString();
            int sale = qry.record(i).value(plusqry).toInt();
            double rate = round((sale/sum)*100*10)/10;
            if (sale != 0)
            {
                ui->model_tbl->insertRow(i);
                ui->model_tbl->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
                ui->model_tbl->setItem(i,1,new QTableWidgetItem(car));
                ui->model_tbl->setItem(i,2,new QTableWidgetItem(QString::number(sale)));
                ui->model_tbl->setItem(i,3,new QTableWidgetItem(tr("%1%").arg(rate,0,'f',1)));
            }
        }
    }
}
void Widget::ForeignCar() //추가
{
    div = 1;
    qDebug() << ui->all_tbl->columnCount();
    if(ui->all_tbl->columnCount() == 4)
        AllSelect();
    else
        PeriodSearch();
}

void Widget::KoreaCar() //추가
{
    div = 0;
    if(ui->all_tbl->columnCount() == 4)
        AllSelect();
    else
        PeriodSearch();
}

//광선 슬롯
// 브랜드 정보 추가 미니
void Widget::BRAND_MINI_info()
{
    QString loc, parent, est, fou, slog, ind;
    MINI_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'MINI';");

    for(int i = 0; i < MINI_qry.rowCount(); i++)
    {
        loc = "소재지 " + MINI_qry.record(i).value("LOC").toString();
        parent = "모기업 " + MINI_qry.record(i).value("PARENT").toString();
        est = "창립일 " + MINI_qry.record(i).value("EST").toString();
        fou = "창립자 " + MINI_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + MINI_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + MINI_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 포드
void Widget::BRAND_FORD_info()
{
    QString loc, parent, est, fou, slog, ind;
    FORD_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'FORD';");

    for(int i = 0; i < FORD_qry.rowCount(); i++)
    {
        loc = "소재지 " + FORD_qry.record(i).value("LOC").toString();
        parent = "모기업 " + FORD_qry.record(i).value("PARENT").toString();
        est = "창립일 " + FORD_qry.record(i).value("EST").toString();
        fou = "창립자 " + FORD_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + FORD_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + FORD_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 도요타
void Widget::BRAND_TOYOTA_info()
{
    QString loc, parent, est, fou, slog, ind;
    TOYOTA_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'TOYOTA';");

    for(int i = 0; i < TOYOTA_qry.rowCount(); i++)
    {
        loc = "소재지 " + TOYOTA_qry.record(i).value("LOC").toString();
        parent = "모기업 " + TOYOTA_qry.record(i).value("PARENT").toString();
        est = "창립일 " + TOYOTA_qry.record(i).value("EST").toString();
        fou = "창립자 " + TOYOTA_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + TOYOTA_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + TOYOTA_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 폭스바겐
void Widget::BRAND_VOLKSWAGEN_info()
{
    QString loc, parent, est, fou, slog, ind;
    VOLKSWAGEN_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'VOLKSWAGEN';");

    for(int i = 0; i < VOLKSWAGEN_qry.rowCount(); i++)
    {
        loc = "소재지 " + VOLKSWAGEN_qry.record(i).value("LOC").toString();
        parent = "모기업 " + VOLKSWAGEN_qry.record(i).value("PARENT").toString();
        est = "창립일 " + VOLKSWAGEN_qry.record(i).value("EST").toString();
        fou = "창립자 " + VOLKSWAGEN_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + VOLKSWAGEN_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + VOLKSWAGEN_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 볼보
void Widget::BRAND_VOLVO_info()
{
    QString loc, parent, est, fou, slog, ind;
    VOLVO_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'VOLVO';");

    for(int i = 0; i < VOLVO_qry.rowCount(); i++)
    {
        loc = "소재지 " + VOLVO_qry.record(i).value("LOC").toString();
        parent = "모기업 " + VOLVO_qry.record(i).value("PARENT").toString();
        est = "창립일 " + VOLVO_qry.record(i).value("EST").toString();
        fou = "창립자 " + VOLVO_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + VOLVO_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + VOLVO_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 아우디
void Widget::BRAND_AUDI_info()
{
    QString loc, parent, est, fou, slog, ind;
    AUDI_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'AUDI';");

    for(int i = 0; i < AUDI_qry.rowCount(); i++)
    {
        loc = "소재지 " + AUDI_qry.record(i).value("LOC").toString();
        parent = "모기업 " + AUDI_qry.record(i).value("PARENT").toString();
        est = "창립일 " + AUDI_qry.record(i).value("EST").toString();
        fou = "창립자 " + AUDI_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + AUDI_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + AUDI_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 모빌리티
void Widget::BRAND_KG_MOBILITY_info()
{
    QString loc, parent, est, fou, slog, ind;
    KG_MOBILITY_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'KG_MOBILITY';");

    for(int i = 0; i < KG_MOBILITY_qry.rowCount(); i++)
    {
        loc = "소재지 " + KG_MOBILITY_qry.record(i).value("LOC").toString();
        parent = "모기업 " + KG_MOBILITY_qry.record(i).value("PARENT").toString();
        est = "창립일 " + KG_MOBILITY_qry.record(i).value("EST").toString();
        fou = "창립자 " + KG_MOBILITY_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + KG_MOBILITY_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + KG_MOBILITY_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 르노
void Widget::BRAND_RENAULT_info()
{
    QString loc, parent, est, fou, slog, ind;
    RENAULT_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'RENAULT';");

    for(int i = 0; i < RENAULT_qry.rowCount(); i++)
    {
        loc = "소재지 " + RENAULT_qry.record(i).value("LOC").toString();
        parent = "모기업 " + RENAULT_qry.record(i).value("PARENT").toString();
        est = "창립일 " + RENAULT_qry.record(i).value("EST").toString();
        fou = "창립자 " + RENAULT_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + RENAULT_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + RENAULT_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 쉐보레
void Widget::BRAND_CHEVROLET_info()
{
    QString loc, parent, est, fou, slog, ind;
    CHEVROLET_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'CHEVROLET';");

    for(int i = 0; i < CHEVROLET_qry.rowCount(); i++)
    {
        loc = "소재지 " + CHEVROLET_qry.record(i).value("LOC").toString();
        parent = "모기업 " + CHEVROLET_qry.record(i).value("PARENT").toString();
        est = "창립일 " + CHEVROLET_qry.record(i).value("EST").toString();
        fou = "창립자 " + CHEVROLET_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + CHEVROLET_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + CHEVROLET_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 제네시스
void Widget::BRAND_GENESIS_info()
{
    QString loc, parent, est, fou, slog, ind;
    GENESIS_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'GENESIS';");

    for(int i = 0; i < GENESIS_qry.rowCount(); i++)
    {
        loc = "소재지 " + GENESIS_qry.record(i).value("LOC").toString();
        parent = "모기업 " + GENESIS_qry.record(i).value("PARENT").toString();
        est = "창립일 " + GENESIS_qry.record(i).value("EST").toString();
        fou = "창립자 " + GENESIS_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + GENESIS_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + GENESIS_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 기아
void Widget::BRAND_KIA_info()
{
    QString loc, parent, est, fou, slog, ind;
    KIA_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'KIA';");

    for(int i = 0; i < KIA_qry.rowCount(); i++)
    {
        loc = "소재지 " + KIA_qry.record(i).value("LOC").toString();
        parent = "모기업 " + KIA_qry.record(i).value("PARENT").toString();
        est = "창립일 " + KIA_qry.record(i).value("EST").toString();
        fou = "창립자 " + KIA_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + KIA_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + KIA_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 브랜드 정보 추가 현대
void Widget::BRAND_HYUNDAI_info()
{
    QString loc, parent, est, fou, slog, ind;
    HYUNDAI_qry.setQuery("SELECT * FROM BRANDINFO WHERE BRAND = 'HYUNDAI';");

    for(int i = 0; i < HYUNDAI_qry.rowCount(); i++)
    {
        loc = "소재지 " + HYUNDAI_qry.record(i).value("LOC").toString();
        parent = "모기업 " + HYUNDAI_qry.record(i).value("PARENT").toString();
        est = "창립일 " + HYUNDAI_qry.record(i).value("EST").toString();
        fou = "창립자 " + HYUNDAI_qry.record(i).value("FOU").toString();
        slog = "슬로건 " + HYUNDAI_qry.record(i).value("SLOGAN").toString();
        ind = "주업종 " + HYUNDAI_qry.record(i).value("IND").toString();
    }
    ui->BRANDINFO_textBrowser->setPlainText(loc);
    ui->BRANDINFO_textBrowser->append(parent);
    ui->BRANDINFO_textBrowser->append(est);
    ui->BRANDINFO_textBrowser->append(fou);
    ui->BRANDINFO_textBrowser->append(slog);
    ui->BRANDINFO_textBrowser->append(ind);
}
// 로고 경로 지정 미니
void Widget::BRAND_MINI_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/MINI.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 포드
void Widget::BRAND_FORD_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/FORD.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 도요타
void Widget::BRAND_TOYOTA_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/TOYOTA.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 폭스바겐
void Widget::BRAND_VOLKSWAGEN_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/VOLKSWAGEN.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 볼보
void Widget::BRAND_VOLVO_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/VOLVO.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 아우디
void Widget::BRAND_AUDI_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/AUDI.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 모빌리티
void Widget::BRAND_KG_MOBILITY_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/KG_MOBILITY.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 르노
void Widget::BRAND_RENAULT_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/RENAULT.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 쉐보레
void Widget::BRAND_CHEVROLET_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/CHEVROLET.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 제네시스
void Widget::BRAND_GENESIS_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/GENESIS.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 기아
void Widget::BRAND_KIA_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/KIA.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}
// 로고 경로 지정 현대
void Widget::BRAND_HYUNDAI_page()
{
    ui->CARINFO_stackedWidget->setCurrentIndex(2);

    QString filename = "border-image: url(:/danawa_car/Danawa_car_image/HYUNDAI.png);";

    ui->Brand_logo_graphicsView->setStyleSheet(filename);
}

// 브랜드 로고 첫페이지
void Widget::car_pedia_index_1()
{
    ui->Car_Company_stackedWidget->setCurrentIndex(1);
}
// 브랜드 로고 두번째페이지
void Widget::car_pedia_index_0()
{
    ui->Car_Company_stackedWidget->setCurrentIndex(0);
}

Widget::~Widget()
{
    delete ui;
}



