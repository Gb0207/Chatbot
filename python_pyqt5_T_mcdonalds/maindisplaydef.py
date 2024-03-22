import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic

#UI파일 연결
#단, UI파일은 Python 코드 파일과 같은 디렉토리에 위치해야한다.
form_class = uic.loadUiType("main.ui")[0]

#화면을 띄우는데 사용되는 Class 선언
class maindisplay(QWidget, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)
        self.sta.setCurrentIndex(0)

        self.btn_order.clicked.connect(self.order)
        self.btn_main.clicked.connect(self.main)
        self.btn_main_adve1.clicked.connect(self.main_adve1)
        self.btn_main_adve2.clicked.connect(self.main_adve2)
        self.btn_help_1.clicked.connect(self.help_event)
        self.btn_help_2.clicked.connect(self.help_event)

        # #포인트 적립 확면으로
        # self.btn_point.clicked.connect(self.point_add)
        # #포인트 적립 확면으로
        # self.btn_point_2p.clicked.connect(self.point_2p)
        # #도움기능 화면으로
        # self.btn_help_1.clicked.connect(self.help_1)
        # #도움기능 화면으로
        # self.btn_help_2.clicked.connect(self.help_2)
        # #주문 화면으로
        # self.btn_in.clicked.connect(self.in_st)
        # #주문 화면으로
        # self.btn_out.clicked.connect(self.out_st)



    def order(self):
        self.sta.setCurrentIndex(1)
    def main(self):
        self.sta.setCurrentIndex(0)
    def main_adve1(self):
        self.sta_2.setCurrentIndex(1)
    def main_adve2(self):
        self.sta_2.setCurrentIndex(0)

    def help_event(self):
        QMessageBox.information(self,"help","직원을 호출하였습니다. 잠시만 기다려주세요.")


    def switch_to_page(self, page_name):
        # page_name에 해당하는 위젯의 인덱스를 찾습니다.
        page_index = self.find_page_index(page_name)
        if page_index != -1:
            # 찾은 인덱스로 스택 위젯을 전환합니다.
            self.sta.setCurrentIndex(page_index)
        else:
            print(f"Page '{page_name}' not found")

    def find_page_index(self, page_name):
        for i in range(self.sta.count()):
            if self.sta.widget(i).objectName() == page_name:
                return i
        return -1




    # #포인트 적립 확면으로
    # def point(self):
    #     self.stackedWidget.setCurrentIndex()
    # #포인트 적립 확면으로
    # def point_2p(self):
    #     self.stackedWidget.setCurrentIndex()
    # #도움기능 화면으로
    # def help_1(self):
    #     self.stackedWidget.setCurrentIndex()
    # #도움기능 화면으로
    # def help_2(self):
    #     self.stackedWidget.setCurrentIndex()
    # #주문 화면으로
    # def in_st(self):
    #     self.stackedWidget.setCurrentIndex()
    # #주문 화면으로
    # def out_st(self):
    #     self.stackedWidget.setCurrentIndex()

if __name__ == "__main__" :
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QApplication(sys.argv)

    #WindowClass의 인스턴스 생성
    myWindow = maindisplay()

    #프로그램 화면을 보여주는 코드
    myWindow.show()

    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()
