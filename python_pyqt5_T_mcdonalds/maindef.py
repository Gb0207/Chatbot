import sys

from PyQt5.QtWidgets import QApplication, QMainWindow, QStackedWidget

from Mcdonald import Mcdonald
from basket import basket
from maindisplay import maindisplay
from method import method
from pointmember import pointmember
from shared_data import SharedData


class IntegratedKiosk(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setGeometry(800,1000,450,750)
        self.stackedWidget = QStackedWidget(self)

        self.shared_data = SharedData()
        self.basket = basket(self.shared_data)
        self.Mcdonald = Mcdonald(self.shared_data, self.basket)
        # 각 클래스의 인스턴스를 생성하고 스택 위젯에 추가합니다.
        self.method = method()
        self.pointmember = pointmember()
        self.maindisplay = maindisplay()


        self.stackedWidget.addWidget(self.method)
        self.stackedWidget.addWidget(self.pointmember)
        self.stackedWidget.addWidget(self.maindisplay)
        self.stackedWidget.addWidget(self.basket)
        self.stackedWidget.addWidget(self.Mcdonald)

        self.setCentralWidget(self.stackedWidget)






        #첫번째화면
        self.stackedWidget.setCurrentWidget(self.maindisplay)
        self.maindisplay.btn_point.clicked.connect(self.switch_to_pointmember_form)
        self.pointmember.back_to_the_main.clicked.connect(self.switch_to_maindisplay_page)
        self.pointmember.point_add.clicked.connect(self.switch_to_maindisplay_page)
        self.maindisplay.btn_point_2p.clicked.connect(self.switch_to_pointmember_form)
        self.maindisplay.btn_in.clicked.connect(self.switch_to_Mcdonald_form)
        self.maindisplay.btn_out.clicked.connect(self.switch_to_Mcdonald_form)
        self.Mcdonald.btn_ToFirst.clicked.connect(self.switch_to_maindisplay_first_page)
        self.Mcdonald.btn_point.clicked.connect(self.switch_to_pointmember_form)
        self.Mcdonald.btn_toBasket.clicked.connect(self.switch_to_basket_form)

        self.basket.btn_main_1.clicked.connect(self.switch_to_maindisplay_first_page)

        self.basket.btn_table.clicked.connect(self.switch_method_form)
        self.basket.btn_plus.clicked.connect(self.switch_to_Mcdonald_form)
        self.Mcdonald.btn_first4.clicked.connect(self.switch_to_maindisplay_first_page)
        self.Mcdonald.btn_first4.clicked.connect(self.Mcdonald_price_reset)
        self.Mcdonald.btn_first4.clicked.connect(self.reset_)
        self.basket.btn_main_1.clicked.connect(self.Mcdonald_price_reset)
        self.basket.btn_main_1.clicked.connect(self.reset_)

        self.Mcdonald.btn_checkpay.clicked.connect(self.switch_to_basket_form)
        self.basket.btn_point_bas.clicked.connect(self.switch_to_pointmember_form)
        self.basket.btn_pickup.clicked.connect(self.switch_method_form)
        self.method.back_.clicked.connect(self.switch_to_basket_form)
        self.basket.btn_main_2.clicked.connect(self.switch_to_maindisplay_first_page)
        self.basket.btn_main_2.clicked.connect(self.Mcdonald_price_reset)
        self.basket.btn_main_2.clicked.connect(self.reset_)
        self.method.reset.clicked.connect(self.switch_to_maindisplay_first_page)
        self.method.reset.clicked.connect(self.Mcdonald_price_reset)
        self.method.reset.clicked.connect(self.reset_)
        self.Mcdonald.btn_cancelhome4.clicked.connect(self.Mcdonald_price_reset)
        self.Mcdonald.btn_cancelhome4.clicked.connect(self.reset_)





    def switch_to_pointmember_form(self):
        # pointmember 클래스 인스턴스로 화면 전환
        index = self.stackedWidget.indexOf(self.pointmember)
        self.stackedWidget.setCurrentIndex(index)

    def switch_to_maindisplay_page(self):
        # pointmember 클래스 인스턴스로 화면 전환
        index = self.stackedWidget.indexOf(self.maindisplay)
        self.stackedWidget.setCurrentIndex(index)
    def switch_to_maindisplay_form(self):
        # pointmember 클래스 인스턴스로 화면 전환
        index = self.stackedWidget.indexOf(self.maindisplay)
        self.stackedWidget.setCurrentIndex(index)
    def switch_to_maindisplay_page1(self):
        # pointmember 클래스 인스턴스로 화면 전환
        index = self.stackedWidget.indexOf(self.maindisplay)
        self.stackedWidget.setCurrentIndex(index)




    def switch_to_maindisplay_first_page(self):
        # Mcdonald 클래스 인스턴스의 인덱스를 찾아서 설정
        index_maindisplay = self.stackedWidget.indexOf(self.maindisplay)
        self.stackedWidget.setCurrentIndex(index_maindisplay)
        self.maindisplay.switch_to_page('page_1')

    def switch_to_basket_form(self):
        self.stackedWidget.setCurrentWidget(self.basket)
        # 이벤트 연결 및 화면 전환 로직을 여기에 구현합니다.

    def switch_method_form(self):
        # 'method' 위젯의 인덱스를 가져옵니다.
        index = self.stackedWidget.indexOf(self.method)
        # 해당 인덱스로 스택 위젯을 전환합니다.
        self.stackedWidget.setCurrentIndex(index)

    def switch_to_Mcdonald_form(self):
        # Mcdonald 위젯으로 전환합니다.
        index_mcdonald = self.stackedWidget.indexOf(self.Mcdonald)
        self.stackedWidget.setCurrentIndex(index_mcdonald)
        # Mcdonald 내부의 특정 페이지(예: 'home')로 전환합니다.
        self.Mcdonald.switch_to_page('page_1')
    def Mcdonald_price_reset(self):
        self.Mcdonald.price.clear()

    def reset_(self):
        self.shared_data.accumulated_items.clear()





if __name__ == "__main__":
    app = QApplication(sys.argv)

    mainWin = IntegratedKiosk()
    mainWin.show()
    sys.exit(app.exec_())
