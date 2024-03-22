
class SharedData:
    def __init__(self):
        self.accumulated_items = []
        self.total_sum=0
    def add_item(self, item):
        self.accumulated_items.append(item)

    def clear_items(self):
        self.accumulated_items.clear()

    def get_items(self):
        return self.accumulated_items

    def set_total_sum(self, value):
        self.total_sum = value

    def get_total_sum(self):
        return self.total_sum

    def update_item_quantity(self, item_name, new_quantity):
        # 'accumulated_items'는 아이템 명, 가격, 수량을 포함하는 튜플의 리스트라고 가정합니다.
        for idx, (name, price, quantity) in enumerate(self.accumulated_items):
            if name == item_name:
                # 아이템의 수량을 업데이트합니다.
                self.accumulated_items[idx] = (name, price, new_quantity)
                break

