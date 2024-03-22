import sys
import random
from PyQt5.QtWidgets import QApplication, QMainWindow,QLabel,QStackedWidget
from PyQt5 import uic

# UI 파일 연결
form_class = uic.loadUiType("method.ui")[0]


class method(QMainWindow, form_class):
    def __init__(self):
        super().__init__()
        self.setupUi(self)  # UI 파일로부터 위젯을 설정합니다.
        self.setCentralWidget(self.stackedWidget)

        # 버튼에 클릭 이벤트를 연결합니다.
        self.kakao_btn.clicked.connect(self.show_barcode_screen)
        self.mobile_btn.clicked.connect(self.show_barcode_screen)
        self.card_btn.clicked.connect(self.show_card_result_screen)
        self.back1.clicked.connect(self.go_back_from_barcode)
        self.back2.clicked.connect(self.go_back_from_cardresult)
        self.finish1.clicked.connect(self.show_result_screen)
        self.finish2.clicked.connect(self.show_result_screen)
        self.back3.clicked.connect(self.go_back_from_page)

        # 결제 완료 버튼 혹은 다른 메커니즘에 대한 연결을 추가하세요.
        # 예: self.complete_payment_btn.clicked.connect(self.show_result_screen)

    # 카카오페이나 모바일 상품권 버튼을 클릭했을 때 호출됩니다.
    def show_barcode_screen(self):
        barcode_screen_index = self.get_screen_index('barcode')
        self.stackedWidget.setCurrentIndex(barcode_screen_index)

    # 카드결제 버튼을 클릭했을 때 호출됩니다.
    def show_card_result_screen(self):
        card_result_screen_index = self.get_screen_index('cardresult')
        self.stackedWidget.setCurrentIndex(card_result_screen_index)

    # 결제 완료 후 호출됩니다.
    def show_result_screen(self):
        result_screen_index = self.get_screen_index('result')
        self.stackedWidget.setCurrentIndex(result_screen_index)

    # 오브젝트 네임으로부터 해당 스크린의 인덱스를 얻습니다.
    def get_screen_index(self, object_name):
        for i in range(self.stackedWidget.count()):
            if self.stackedWidget.widget(i).objectName() == object_name:
                return i
        return -1  # 오브젝트 네임이 없으면 -1을 반환합니다.

    def go_back_from_barcode(self):
        # 여기서 0은 기본 화면의 인덱스입니다.
        # 실제 인덱스 번호는 사용자의 UI 디자인에 따라 다를 수 있습니다.
        self.stackedWidget.setCurrentIndex(0)

    # cardresult 화면에서 '뒤로' 버튼을 클릭했을 때 호출됩니다.
    def go_back_from_cardresult(self):
        # 여기서 0은 기본 화면의 인덱스입니다.
        # 실제 인덱스 번호는 사용자의 UI 디자인에 따라 다를 수 있습니다.
        self.stackedWidget.setCurrentIndex(0)
    def go_back_from_page(self):
        self.stackedWidget.setCurrentIndex(0)

    def show_result_screen(self):
        result_screen_index = self.get_screen_index('result')
        self.stackedWidget.setCurrentIndex(result_screen_index)
        self.update_receipt_number()

    # 랜덤 영수증 번호를 업데이트합니다.
    def update_receipt_number(self):
        # 랜덤 영수증 번호를 생성합니다. 여기서는 예시로 8자리 숫자를 사용합니다.
        receipt_number = str(random.randint(100, 999))
        # QLabel의 인스턴스를 찾습니다.
        random_number_label = self.findChild(QLabel, 'random_number')
        if random_number_label:
            random_number_label.setText(f"영수증 번호: {receipt_number}")
        else:
            print("Error: 'random_number' label not found")

    def setupConnections(self):
        # 예를 들어, 어떤 버튼이 클릭되었을 때 methodWidget으로 전환하도록 설정
        self.someButton.clicked.connect(self.switchToMethod)

    def switchToMethod(self):
        # methodWidget으로 전환
        index = self.stackedWidget.indexOf(self.methodWidget)
        self.stackedWidget.setCurrentIndex(index)

# 애플리케이션 실행
if __name__ == "__main__":
    app = QApplication(sys.argv)
    main_window = method()
    main_window.show()
    sys.exit(app.exec_())
