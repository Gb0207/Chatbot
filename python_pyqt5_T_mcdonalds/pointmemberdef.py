import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic

#UI파일 연결
#단, UI파일은 Python 코드 파일과 같은 디렉토리에 위치해야한다.
form_class = uic.loadUiType("pointmember.ui")[0]

#화면을 띄우는데 사용되는 Class 선언
class pointmember(QMainWindow, form_class) :
    def __init__(self) :
        super().__init__()

        self.setupUi(self)
        self.numsum=""
        self.member=[]

        self.num1.clicked.connect(lambda: self.num_click("1"))
        self.num2.clicked.connect(lambda: self.num_click("2"))
        self.num3.clicked.connect(lambda: self.num_click("3"))
        self.num4.clicked.connect(lambda: self.num_click("4"))
        self.num5.clicked.connect(lambda: self.num_click("5"))
        self.num6.clicked.connect(lambda: self.num_click("6"))
        self.num7.clicked.connect(lambda: self.num_click("7"))
        self.num8.clicked.connect(lambda: self.num_click("8"))
        self.num9.clicked.connect(lambda: self.num_click("9"))
        self.num0.clicked.connect(lambda: self.num_click("0"))
        self.btn_del.clicked.connect(self.num_del)  # 단일 삭제
        self.btn_alldel.clicked.connect(self.num_alldel)  # 전체 삭제
        self.point_add.clicked.connect(self.add_point)
        self.point_add.setEnabled(False)  # 초기에는 포인트 적립하기 버튼을 비활성화합니다.


    def num_click(self, text):
        if len(self.numsum) < 13:  # 숫자와 하이픈을 합쳐서 12자를 초과하지 않도록 합니다.
            self.numsum += text
            if len(self.numsum) == 3 or len(self.numsum) == 8:
                self.numsum += "-"  # 자릿수에 맞추어 하이픈을 추가합니다.
            self.text_num.setText(self.numsum)  # text_num은 QLineEdit 위젯의 objectName이어야 합니다.
            self.validate_phone_number()  # 전화번호 형식을 검증하고 포인트 적립하기 버튼을 활성화합니다.

    def validate_phone_number(self):
        # 전화번호 형식이 올바른지 확인하고, 포인트 적립하기 버튼을 활성화하거나 비활성화합니다.
        if len(self.numsum) == 13 and all(x.isdigit() or x == '-' for x in self.numsum):
            self.point_add.setEnabled(True)
        else:
            self.point_add.setEnabled(False)

    def num_alldel(self):
        self.numsum = ""
        self.text_num.setText(self.numsum)
        self.point_add.setEnabled(False)  # 전화번호가 삭제되면 포인트 적립하기 버튼을 비활성화합니다.

    def num_del(self):
        if self.numsum.endswith('-'):
            self.numsum = self.numsum[:-2]  # 하이픈과 숫자를 함께 삭제합니다.
        else:
            self.numsum = self.numsum[:-1]
        self.text_num.setText(self.numsum)
        self.validate_phone_number()  # 전화번호 형식을 검증하고 포인트 적립하기 버튼을 활성화합니다.

    def add_point(self):
        # 포인트 적립 로직을 구현합니다. 여기에서는 단순히 콘솔에 출력하도록 되어 있습니다.
        print(f"포인트가 적립된 휴대폰 번호: {self.numsum}")
        # 포인트 적립 후 초기화
        self.num_alldel()





if __name__ == "__main__" :
    #QApplication : 프로그램을 실행시켜주는 클래스
    app = QApplication(sys.argv)

    #WindowClass의 인스턴스 생성
    myWindow = pointmember()

    #프로그램 화면을 보여주는 코드
    myWindow.show()

    #프로그램을 이벤트루프로 진입시키는(프로그램을 작동시키는) 코드
    app.exec_()