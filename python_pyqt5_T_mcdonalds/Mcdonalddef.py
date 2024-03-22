import sys
from PyQt5.QtWidgets import *
from PyQt5 import uic
from shared_data import SharedData
from basket import basket

form_class = uic.loadUiType("MCorder.ui")[0]

class Mcdonald(QWidget, form_class):
    def __init__(self,shared_data,basket) :
        super().__init__()
        self.setupUi(self)
        self.shared_data=shared_data
        self.basket=basket
        self.Stack_out.setCurrentIndex(0)
        self.Stack_in.setCurrentIndex(0)
        self.setup_quantity_buttons()

        self.btn_first4.clicked.connect(self.reset_)


        self.basket_main.setColumnCount(5) # 3개의 열: 이름, 가격, 수량
        self.basket_main.setHorizontalHeaderLabels(["이름", "가격","수량","+","-"])



        self.btn_oribg1.clicked.connect(self.handle_btn_oribg1_click)
        self.btn_cancelhome4.clicked.connect(self.reset_basket_main)
        self.accumulated_items = []
        self.update_price_label()






        #Home_page
        #self.btn_ToFirst.clicked.connect(self.Home) 메인화면으로 가는 버

        self.btn_hMcLunch.clicked.connect(self.Mclunch_page)
        self.btn_htmHS.clicked.connect(self.HappySnack_page)
        self.btn_hRecoMenu.clicked.connect(self.recoMenu_page)
        self.btn_hcf_ds.clicked.connect(self.Coffe_page)

        self.btn_Home.clicked.connect(self.Home)
        self.btn_McLunch.clicked.connect(self.Mclunch_page)
        self.btn_RecoMenu1.clicked.connect(self.recoMenu_page)
        self.btn_Burger.clicked.connect(self.Burger_page)
        self.btn_HappySnack.clicked.connect(self.HappySnack_page)
        self.btn_Side.clicked.connect(self.Side_page)
        self.btn_Coffee.clicked.connect(self.Coffe_page)
        self.btn_Dessert.clicked.connect(self.Dessert_page)
        self.btn_Drink.clicked.connect(self.Drink_page)
        self.btn_HappyMeal.clicked.connect(self.HappyMeal_page)

        #recoMenu page
        self.btn_re2.clicked.connect(self.MenuCheck_page)
        self.btn_re3.clicked.connect(self.MenuCheck_page)
        self.btn_re4.clicked.connect(self.MenuCheck_page)
        self.btn_re5.clicked.connect(self.MenuCheck_page)
        self.btn_re6.clicked.connect(self.MenuCheck_page)
        self.btn_re7.clicked.connect(self.MenuCheck_page)
        self.btn_re8.clicked.connect(self.MenuCheck_page)
        self.btn_re9.clicked.connect(self.MenuCheck_page)
        self.btn_re10.clicked.connect(self.MenuCheck_page)



        #Mclunch page
        self.btn_mcL1.clicked.connect(self.LaSe_page)
        self.btn_mcL2.clicked.connect(self.LaSe_page)
        self.btn_mcL3.clicked.connect(self.LaSe_page)
        self.btn_mcL4.clicked.connect(self.LaSe_page)
        self.btn_mcL5.clicked.connect(self.LaSe_page)
        self.btn_mcL6.clicked.connect(self.LaSe_page)
        self.btn_mcL7.clicked.connect(self.LaSe_page)
        self.btn_mcL8.clicked.connect(self.LaSe_page)


        #Burger page
        self.btn_oribg1.clicked.connect(self.SetCh_page)
        self.btn_bg2.clicked.connect(self.SetCh_page)
        self.btn_bg3.clicked.connect(self.SetCh_page)
        self.btn_bg4.clicked.connect(self.SetCh_page)
        self.btn_bg5.clicked.connect(self.SetCh_page)
        self.btn_bg6.clicked.connect(self.SetCh_page)
        self.btn_bg7.clicked.connect(self.SetCh_page)
        self.btn_bg8.clicked.connect(self.SetCh_page)
        self.btn_bg9.clicked.connect(self.SetCh_page)
        self.btn_bg10.clicked.connect(self.SetCh_page)
        self.btn_bg11.clicked.connect(self.SetCh_page)
        self.btn_bg12.clicked.connect(self.SetCh_page)

        self.btn_burgerpv1.clicked.connect(self.Burger1_page)
        self.btn_burger2.clicked.connect(self.Burger2_page)

        self.btn_bg13.clicked.connect(self.SetCh_page)
        self.btn_bg14.clicked.connect(self.SetCh_page)
        self.btn_bg15.clicked.connect(self.SetCh_page)
        self.btn_bg16.clicked.connect(self.SetCh_page)
        self.btn_bg17.clicked.connect(self.SetCh_page)
        self.btn_bg18.clicked.connect(self.SetCh_page)
        self.btn_bg19.clicked.connect(self.SetCh_page)
        self.btn_bg20.clicked.connect(self.SetCh_page)
        self.btn_bg21.clicked.connect(self.SetCh_page)

        #HappySnack page
        self.btn_hs1.clicked.connect(self.MenuCheck_page)
        self.btn_hs2.clicked.connect(self.MenuCheck_page)
        self.btn_hs3.clicked.connect(self.MenuCheck_page)
        self.btn_hs4.clicked.connect(self.MenuCheck_page)
        self.btn_hs5.clicked.connect(self.MenuCheck_page)
        self.btn_hs6.clicked.connect(self.MenuCheck_page)
        self.btn_hs7.clicked.connect(self.MenuCheck_page)



        # Side page
        self.btn_si1.clicked.connect(self.MenuCheck_page)
        self.btn_si2.clicked.connect(self.MenuCheck_page)
        self.btn_si3.clicked.connect(self.MenuCheck_page)
        self.btn_si4.clicked.connect(self.MenuCheck_page)
        self.btn_si5.clicked.connect(self.MenuCheck_page)
        self.btn_si6.clicked.connect(self.MenuCheck_page)
        self.btn_si7.clicked.connect(self.MenuCheck_page)
        self.btn_si8.clicked.connect(self.MenuCheck_page)

        # Coffee page
        self.btn_cf1.clicked.connect(self.MenuCheck_page)
        self.btn_cf2.clicked.connect(self.MenuCheck_page)
        self.btn_cf3.clicked.connect(self.MenuCheck_page)
        self.btn_cf4.clicked.connect(self.MenuCheck_page)
        self.btn_cf5.clicked.connect(self.MenuCheck_page)
        self.btn_cf6.clicked.connect(self.MenuCheck_page)
        self.btn_cf7.clicked.connect(self.MenuCheck_page)
        self.btn_cf8.clicked.connect(self.MenuCheck_page)
        self.btn_cf9.clicked.connect(self.MenuCheck_page)
        self.btn_cf10.clicked.connect(self.MenuCheck_page)
        self.btn_cf11.clicked.connect(self.MenuCheck_page)
        self.btn_cf12.clicked.connect(self.MenuCheck_page)

        self.btn_coffee2.clicked.connect(self.Coffee2_page)
        self.btn_coffeepv.clicked.connect(self.Coffee1_page)

        self.btn_cf13.clicked.connect(self.MenuCheck_page)
        self.btn_cf14.clicked.connect(self.MenuCheck_page)
        self.btn_cf15.clicked.connect(self.MenuCheck_page)
        self.btn_cf16.clicked.connect(self.MenuCheck_page)



        # Dessert page
        self.btn_ds1.clicked.connect(self.MenuCheck_page)
        self.btn_ds2.clicked.connect(self.MenuCheck_page)
        self.btn_ds3.clicked.connect(self.MenuCheck_page)
        self.btn_ds4.clicked.connect(self.MenuCheck_page)
        self.btn_ds5.clicked.connect(self.MenuCheck_page)
        self.btn_ds6.clicked.connect(self.MenuCheck_page)
        self.btn_ds7.clicked.connect(self.MenuCheck_page)
        self.btn_ds8.clicked.connect(self.MenuCheck_page)
        self.btn_ds9.clicked.connect(self.MenuCheck_page)
        self.btn_ds10.clicked.connect(self.MenuCheck_page)
        self.btn_ds11.clicked.connect(self.MenuCheck_page)

        # Drink page
        self.btn_dr1.clicked.connect(self.MenuCheck_page)
        self.btn_dr2.clicked.connect(self.MenuCheck_page)
        self.btn_dr3.clicked.connect(self.MenuCheck_page)
        self.btn_dr4.clicked.connect(self.MenuCheck_page)
        self.btn_dr5.clicked.connect(self.MenuCheck_page)
        self.btn_dr6.clicked.connect(self.MenuCheck_page)
        self.btn_dr7.clicked.connect(self.MenuCheck_page)
        self.btn_dr8.clicked.connect(self.MenuCheck_page)
        self.btn_dr9.clicked.connect(self.MenuCheck_page)

        # Happymeal page
        self.btn_hm1.clicked.connect(self.MenuCheck_page)
        self.btn_hm2.clicked.connect(self.MenuCheck_page)
        self.btn_hm3.clicked.connect(self.MenuCheck_page)
        self.btn_hm4.clicked.connect(self.MenuCheck_page)
        self.btn_hm5.clicked.connect(self.MenuCheck_page)
        self.btn_hm6.clicked.connect(self.MenuCheck_page)
        self.btn_hm7.clicked.connect(self.MenuCheck_page)
        self.btn_hm8.clicked.connect(self.MenuCheck_page)
        self.btn_hm9.clicked.connect(self.MenuCheck_page)
        self.btn_hm10.clicked.connect(self.MenuCheck_page)
        self.btn_hm11.clicked.connect(self.MenuCheck_page)



        # Setch page
        self.btn_setch.clicked.connect(self.SetSide_page)
        self.set_sinch.clicked.connect(self.MenuCheck_page)
        self.btn_cancel.clicked.connect(self.Home)

        # Lase page
        self.btn_justset.clicked.connect(self.SetSide_page)
        self.btn_largeset.clicked.connect(self.SetSide_page)
        self.btn_cancelhome1.clicked.connect(self.Home)
        self.btn_back12p.clicked.connect(self.SetCh_page)

        # Setside page
        self.btn_sesi1.clicked.connect(self.SetDrink_page)
        self.btn_sesi2.clicked.connect(self.SetDrink_page)
        self.btn_sesi3.clicked.connect(self.SetDrink_page)
        self.btn_sesi4.clicked.connect(self.SetDrink_page)
        self.btn_backpage11.clicked.connect(self.LaSe_page)
        self.btn_cancelhome2.clicked.connect(self.Home)
        #self.btn_first2.clicked.connect(self.Home)

        # SetDrink page
        self.btn_backpage13.clicked.connect(self.SetSide_page)
        self.btn_cancelhome3.clicked.connect(self.Home)
        #self.btn_first3.clicked.connect(self.Home)

        self.btn_sedr1.clicked.connect(self.MenuCheck_page)
        self.btn_sedr2.clicked.connect(self.MenuCheck_page)
        self.btn_sedr3.clicked.connect(self.MenuCheck_page)
        self.btn_sedr4.clicked.connect(self.MenuCheck_page)
        self.btn_sedr5.clicked.connect(self.MenuCheck_page)
        self.btn_sedr6.clicked.connect(self.MenuCheck_page)
        self.btn_sedr7.clicked.connect(self.MenuCheck_page)
        self.btn_sedr8.clicked.connect(self.MenuCheck_page)
        self.btn_sedr9.clicked.connect(self.MenuCheck_page)

        self.btn_setdrinkinnext_1.clicked.connect(self.SetDrink2_page)

        self.btn_sedr10.clicked.connect(self.MenuCheck_page)
        self.btn_sedr11.clicked.connect(self.MenuCheck_page)
        self.btn_sedr12.clicked.connect(self.MenuCheck_page)
        self.btn_sedr13.clicked.connect(self.MenuCheck_page)
        self.btn_sedr14.clicked.connect(self.MenuCheck_page)
        self.btn_sedr15.clicked.connect(self.MenuCheck_page)
        self.btn_sedr16.clicked.connect(self.MenuCheck_page)
        self.btn_sedr17.clicked.connect(self.MenuCheck_page)
        self.btn_sedr18.clicked.connect(self.MenuCheck_page)

        self.btn_setdrinkinnext_2.clicked.connect(self.SetDrink3_page)
        self.btn_setdrinkinpv_1.clicked.connect(self.SetDrinkinpv1_page)
        self.btn_setdrinkinpv_2.clicked.connect(self.SetDrinkinpv2_page)

        self.btn_sedr19.clicked.connect(self.MenuCheck_page)
        self.btn_sedr20.clicked.connect(self.MenuCheck_page)
        self.btn_sedr21.clicked.connect(self.MenuCheck_page)
        self.btn_sedr22.clicked.connect(self.MenuCheck_page)
        self.btn_sedr23.clicked.connect(self.MenuCheck_page)
        self.btn_sedr24.clicked.connect(self.MenuCheck_page)

        self.btn_setdrinkinpv_2.clicked.connect(self.SetDrink2_page)

        # 세트 메뉴 선택
        self.btn_sesi1.clicked.connect(self.handle_sesi1_click)
        self.btn_sesi2.clicked.connect(self.handle_sesi2_click)
        self.btn_sesi3.clicked.connect(self.handle_sesi3_click)
        self.btn_sesi4.clicked.connect(self.handle_sesi4_click)

        # SetDrink page
        # self.btn_first3.clicked.connect(self.Home)

        self.btn_sedr1.clicked.connect(self.handle_sedr1_click)
        self.btn_sedr2.clicked.connect(self.handle_sedr2_click)
        self.btn_sedr3.clicked.connect(self.handle_sedr3_click)
        self.btn_sedr4.clicked.connect(self.handle_sedr4_click)
        self.btn_sedr5.clicked.connect(self.handle_sedr5_click)
        self.btn_sedr6.clicked.connect(self.handle_sedr6_click)
        self.btn_sedr7.clicked.connect(self.handle_sedr7_click)
        self.btn_sedr8.clicked.connect(self.handle_sedr8_click)
        self.btn_sedr9.clicked.connect(self.handle_sedr9_click)

        self.btn_sedr10.clicked.connect(self.handle_sedr10_click)
        self.btn_sedr11.clicked.connect(self.handle_sedr11_click)
        self.btn_sedr12.clicked.connect(self.handle_sedr12_click)
        self.btn_sedr13.clicked.connect(self.handle_sedr13_click)
        self.btn_sedr14.clicked.connect(self.handle_sedr14_click)
        self.btn_sedr15.clicked.connect(self.handle_sedr15_click)
        self.btn_sedr16.clicked.connect(self.handle_sedr16_click)
        self.btn_sedr17.clicked.connect(self.handle_sedr17_click)
        self.btn_sedr18.clicked.connect(self.handle_sedr18_click)

        self.btn_sedr19.clicked.connect(self.handle_sedr19_click)
        self.btn_sedr20.clicked.connect(self.handle_sedr20_click)
        self.btn_sedr21.clicked.connect(self.handle_sedr21_click)
        self.btn_sedr22.clicked.connect(self.handle_sedr22_click)
        self.btn_sedr23.clicked.connect(self.handle_sedr23_click)
        self.btn_sedr24.clicked.connect(self.handle_sedr24_click)









        #MenuCheck page
        # self.btn_backpage13.clicked.connect(self.Home)
        # self.btn_toBasket.clicked.connect(self.Home)
        self.btn_cancelhome4.clicked.connect(self.Home)
        #self.btn_first4.clicked.connect(self.Home)

    def Home(self):
        self.Stack_out.setCurrentIndex(0)
        self.Stack_in.setCurrentIndex(0)

    def recoMenu_page(self):
        self.Stack_in.setCurrentIndex(1)

    def Mclunch_page(self):
        self.Stack_in.setCurrentIndex(2)

    def Burger_page(self):
        self.Stack_in.setCurrentIndex(3)


    def Burger2_page(self):
        self.Stack_ininbg.setCurrentIndex(1)

    def Burger1_page(self):
        self.Stack_ininbg.setCurrentIndex(0)

    def HappySnack_page(self):
        self.Stack_in.setCurrentIndex(4)

    def Side_page(self):
        self.Stack_in.setCurrentIndex(5)

    def Coffe_page(self):
        self.Stack_in.setCurrentIndex(6)

    def Coffee2_page(self):
        self.Stack_inincf.setCurrentIndex(1)

    def Coffee1_page(self):
        self.Stack_inincf.setCurrentIndex(0)

    def Dessert_page(self):
        self.Stack_in.setCurrentIndex(7)

    def Drink_page(self):
        self.Stack_in.setCurrentIndex(8)

    def HappyMeal_page(self):
        self.Stack_in.setCurrentIndex(9)

    def SetCh_page(self):
        self.Stack_out.setCurrentIndex(1)

    def LaSe_page(self):
        self.Stack_out.setCurrentIndex(2)

    def SetSide_page(self):
        self.Stack_out.setCurrentIndex(3)

    def SetDrink_page(self):
        self.Stack_out.setCurrentIndex(4)

    def SetDrink2_page(self):
        self.Stack_inindr.setCurrentIndex(1)

    def SetDrink3_page(self):
        self.Stack_inindr.setCurrentIndex(2)

    def SetDrinkinpv1_page(self):
        self.Stack_inindr.setCurrentIndex(0)

    def SetDrinkinpv2_page(self):
        self.Stack_inindr.setCurrentIndex(1)

    def MenuCheck_page(self):
        self.Stack_out.setCurrentIndex(5)

    def handle_btn_oribg1_click(self):
        # 아이템 정보 설정
        item_name = "상하이버거"
        item_price = 5000  # 예시 가격
        item_quantity = 1  # 예시 수량

        # QLabel 업데이트
        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))
        # QLabel 업데이트
        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        self.basket.update_item(item_name, item_quantity)

        if self.basket:
            self.basket.update_add_to_cart()

    def update_basket_main(self):
        # 현재 테이블의 행 수를 누적된 아이템의 수와 동기화
        self.basket_main.setRowCount(len(self.shared_data.accumulated_items))

        for row, (name, price, quantity) in enumerate(self.shared_data.accumulated_items):
            # 각 셀에 데이터 추가
            self.basket_main.setItem(row, 0, QTableWidgetItem(name))
            self.basket_main.setItem(row, 1, QTableWidgetItem(str(price)))
            self.basket_main.setItem(row, 2, QTableWidgetItem(str(quantity)))

            self.setup_quantity_buttons()
    def reset_basket_main(self):
        # 누적된 아이템 리스트 초기화
        self.shared_data.accumulated_items.clear()

        # basket_main 테이블의 모든 행 제거
        self.basket_main.setRowCount(0)

    def handle_sesi1_click(self):
        item_name = "후렌치 후라이"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sesi2_click(self):
        item_name = "맥너겟"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sesi3_click(self):
        item_name = "맥스파이시 치킨 텐더"
        item_price = 1500
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sesi4_click(self):
        item_name = "해쉬 브라운"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr1_click(self):
        item_name = "코카 콜라"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr2_click(self):
        item_name = "코카 콜라 제로"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr3_click(self):
        item_name = "스프라이트"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr4_click(self):
        item_name = "환타"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr5_click(self):
        item_name = "바닐라 쉐이크Medium"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr6_click(self):
        item_name = "딸기 쉐이크Medium"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr7_click(self):
        item_name = "초코 쉐이크Medium"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr8_click(self):
        item_name = "오렌지 주스"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr9_click(self):
        item_name = "생수"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr10_click(self):
        item_name = "자두 천도복숭아 칠러"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr11_click(self):
        item_name = "제주 한라봉 칠러"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr12_click(self):
        item_name = "바닐라 라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr13_click(self):
        item_name = "아이스 바닐라 라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr14_click(self):
        item_name = "카페라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr15_click(self):
        item_name = "디카페인 카페라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr16_click(self):
        item_name = "아이스 카페라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr17_click(self):
        item_name = "디카페인 아이스 카페라떼"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr18_click(self):
        item_name = "아메리카노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr19_click(self):
        item_name = "디카페인 아메리카노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr20_click(self):
        item_name = "아이스 아메리카노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr21_click(self):
        item_name = "디카페인 아이스 아메리카노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr22_click(self):
        item_name = "카푸치노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr23_click(self):
        item_name = "디카페인 카푸치노"
        item_price = 1000
        item_quantity = 1

        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))

        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def handle_sedr24_click(self):
        item_name = "드립커피"
        item_price = 1000
        item_quantity = 1

        # 아이템 정보를 리스트에 추가
        self.accumulated_items.append((item_name, item_price, item_quantity))
        self.shared_data.add_item((item_name, item_price, item_quantity))
        # QLabel 업데이트
        self.update_basket_main()
        self.basket.update_add_to_cart()
        self.update_price_label()
        if self.basket:
            self.basket.update_add_to_cart()

    def switch_to_page(self, page_name):
        # page_name에 해당하는 위젯의 인덱스를 찾습니다.
        page_index = self.find_page_index(page_name)
        if page_index != -1:
            # 찾은 인덱스로 스택 위젯을 전환합니다.
            self.Stack_out.setCurrentIndex(page_index)
        else:
            print(f"Page '{page_name}' not found")

    def find_page_index(self, page_name):
        for i in range(self.Stack_out.count()):
            if self.Stack_out.widget(i).objectName() == page_name:
                return i
        return -1

    def some_method_to_update_price_label(self):
        # SharedData 객체에서 total_sum 값을 검색
        total_sum_value = self.shared_data.get_total_sum()

        # price QLabel에 값을 설정
        self.price.setText(str(total_sum_value))

    def update_price_label(self):
        total_sum = self.shared_data.get_total_sum()
        self.price.setText(f"{total_sum}원")

    def setup_quantity_buttons(self):
        # 각 행에 대한 수량 조절 버튼 설정
        for i in range(self.basket_main.rowCount()):
            item_widget = self.basket_main.item(i, 0)
            if item_widget is not None:
                item_name = item_widget.text()
            else:
                continue  # 아이템이 없으므로 이 행에 대한 버튼을 설정하지 않습니다.

            btn_num_plus = QPushButton('+')
            btn_num_minus = QPushButton('-')
            btn_num_plus.clicked.connect(lambda _, row=i, name=item_name: self.change_item_quantity(name, 1, row))
            btn_num_minus.clicked.connect(lambda _, row=i, name=item_name: self.change_item_quantity(name, -1, row))

            self.basket_main.setCellWidget(i, 3, btn_num_plus)
            self.basket_main.setCellWidget(i, 4, btn_num_minus)

    def change_item_quantity(self, item_name, quantity_change, row):
        current_quantity = int(self.basket_main.item(row, 2).text())
        new_quantity = max(current_quantity + quantity_change, 0)
        self.basket_main.item(row, 2).setText(str(new_quantity))
        self.shared_data.update_item_quantity(item_name, new_quantity)
        self.add_to_cart()

    def add_to_cart(self):
        for i in range(self.basket_main.rowCount()):
            item_name = self.basket_main.item(i, 0).text()
            item_quantity = int(self.basket_main.item(i, 2).text())
            self.basket.update_item(item_name, item_quantity)  # 장바구니에 아이템 업데이트
            self.update_price_label()

    def reset_(self):
        self.shared_data.accumulated_items.clear()
        # basket_main 테이블의 모든 행 제거

if __name__ == "__main__" :
    app = QApplication(sys.argv)
    Mcdonald = Mcdonald()
    Mcdonald.show()
    app.exec_()