import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic


#UI파일 연결
#단, UI파일은 Python 코드 파일과 같은 디렉토리에 위치해야한다.
form_class = uic.loadUiType("basket.ui")[0]

#화면을 띄우는데 사용되는 Class 선언
class basket(QWidget, form_class):
    def __init__(self, shared_data):
        super().__init__()
        self.setupUi(self)
        self.shared_data = shared_data
        self.total_sum_value = 0
        self.items = []

        self.sta.setCurrentIndex(0)
        self.btn_main_1.clicked.connect(self.reset_add_to_cart)




        self.add_to_cart.setColumnCount(3)  # 3개의 열: 이름, 가격, 수량
        self.add_to_cart.setHorizontalHeaderLabels(["이름", "가격", "수량"])


        #######0
        # #추천메뉴 화면으로 돌아감
        # self.btnWith1.clicked.connect(self.btnW1)
        # self.btnWith2.clicked.connect(self.btnW2)
        # self.btnWith3.clicked.connect(self.btnW3)
        # self.btnWith4.clicked.connect(self.btnW4)
        # self.btnWith5.clicked.connect(self.btnW5)
        # #선택 안함 선택 시 주문하기 화면으로
        self.btn_not.clicked.connect(self.not_st)

        #######1
        #주문 완료 선택 시 2page
        self.btn_pay.clicked.connect(self.pay)
        # #처음으로 선택 시 메인화면으로
        # self.btn_main_1.clicked.connect(self.main_1)
        # #도움기능 화면으로
        # self.btn_help_3.clicked.connect(self.help_3)
        # #추가주문 선택 시 홈 화면으로
        # self.btn_plus.clicked.connect(self.plus)
        # #포인트 적립 확면으로
        # self.btn_point_bas.clicked.connect(self.point_bas)

        ########2
        #주문 화면으로 돌아감
        self.btn_back.clicked.connect(self.back)
        # #테이블 서비스 선택시 저장 해뒀다가 결제화면 영수증과 대기번호 이후 화면출력
        # self.btn_table.clicked.connect(self.table)
        # #카운터에서 픽업 선택시 저장 해뒀다가 결제화면 영수증과 대기번호 이후 화면출력
        # self.btn_pickup.clicked.connect(self.pickup)
        # #처음으로 선택 시 메인화면으로
        # self.btn_main_2.clicked.connect(self.main_2)
        # #도움기능 화면으로
        # self.btn_help_4.clicked.connect(self.help_4)

    #########0
    # #추천메뉴 화면으로 돌아감
    # def btnW1(self):
    #     self.sta.setCurrentIndex()
    # def btnW2(self):
    #     self.sta.setCurrentIndex()
    # def btnW3(self):
    #     self.sta.setCurrentIndex()
    # def btnW4(self):
    #     self.sta.setCurrentIndex()
    # def btnW5(self):
    #     self.sta.setCurrentIndex()
    def not_st(self):
        self.sta.setCurrentIndex(1)

    #########1
    # 주문 완료 선택 시 2page
    def pay(self):
        self.sta.setCurrentIndex(2)
    # #메인 화면으로 돌아감
    # def main_1(self):
    #     self.sta.setCurrentIndex(0)
    # #도움기능 화면으로
    # def help_3(self):
    #     self.stackedWidget.setCurrentIndex()
    # #추가주문 선택 시 홈 화면으로
    # def plus(self):
    #     self.stackedWidget.setCurrentIndex()
    # #포인트 적립 확면으로
    # def point_bas(self):
    #     self.stackedWidget.setCurrentIndex()

    #########2
    #주문 화면으로 돌아감
    def back(self):
        self.sta.setCurrentIndex(1)
    # #테이블 서비스 선택시 저장 해뒀다가 결제화면 영수증과 대기번호 이후 화면출력
    # def table(self):
    #     self.sta.setCurrentIndex(1)
    # #카운터에서 픽업 선택시 저장 해뒀다가 결제화면 영수증과 대기번호 이후 화면출력
    # def pickup(self):
    #     self.sta.setCurrentIndex(1)
    # #메인 화면으로 돌아감
    # def main_2(self):
    #     self.sta.setCurrentIndex(0)
    # #도움기능 화면으로
    # def help_4(self):
    #     self.stackedWidget.setCurrentIndex()
    def update_add_to_cart(self):
        self.add_to_cart.setRowCount(len(self.shared_data.accumulated_items))
        for row, (name, price, quantity) in enumerate(self.shared_data.accumulated_items):
            self.add_to_cart.setItem(row, 0, QTableWidgetItem(name))
            self.add_to_cart.setItem(row, 1, QTableWidgetItem(str(price)))
            self.add_to_cart.setItem(row, 2, QTableWidgetItem(str(quantity)))
        self.update_total_sum()

    def update_total_sum(self):
        # 장바구니 총 합계를 계산합니다.
        total_sum = 0
        row_count = self.add_to_cart.rowCount()

        for row in range(row_count):
            price_item = self.add_to_cart.item(row, 1)
            quantity_item = self.add_to_cart.item(row, 2)

            if price_item and quantity_item:
                price = float(price_item.text())
                quantity = int(quantity_item.text())
                total_sum += price * quantity
        self.shared_data.set_total_sum(total_sum)

        self.total_sum_value = total_sum  # total_sum_value 업데이트
        self.shared_data.set_total_sum(self.total_sum_value)  # SharedData 객체 업데이트
        self.total_sum.setText(f"{int(total_sum)}원")  # QLabel 업데이트

    def reset_add_to_cart(self):
        # 누적된 아이템 리스트 초기화
        self.shared_data.accumulated_items.clear()
        # basket_main 테이블의 모든 행 제거
        self.add_to_cart.setRowCount(0)

    def update_item(self, item_name, new_quantity):
        # 장바구니에 있는 아이템의 수량을 업데이트

        found = False
        for item in self.items:
            if item['name'] == item_name:
                item['quantity'] = new_quantity
                found = True
                break
        if not found:
            print(f"Item '{item_name}' not found in the basket.")
        self.update_add_to_cart()




if __name__ == "__main__" :
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QApplication(sys.argv)

    #WindowClass의 인스턴스 생성
    myWindow = basket()

    #프로그램 화면을 보여주는 코드
    myWindow.show()

    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()