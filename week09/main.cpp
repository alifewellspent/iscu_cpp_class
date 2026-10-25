#include <iostream>
#include <string>
#include <vector>

// 메뉴 하나의 정보
struct MenuItem {
    std::string name;
    int price;
};

// 주문 한 건의 정보
struct Order {
    MenuItem item;
    int quantity;
};

// 여러 주문을 관리하는 장바구니
class Cart {
public:
    void addOrder(const Order& order) {
        // TODO 1: 수량이 0 이하라면 추가하지 않고 함수를 종료하세요.
        //         정상적인 주문이라면 private 멤버 orders에 저장하세요.
    }

    int getTotal() const {
        int total = 0;

        // TODO 2: orders의 각 주문을 읽어
        //         (메뉴 가격 * 수량)을 total에 더하세요.

        return total;
    }

    void printReceipt() const {
        std::cout << "\nReceipt\n";

        // TODO 3: orders의 각 주문에 대해
        //         "Americano x 2 = 9000 won" 형식으로 출력하세요.

        std::cout << "Final total: " << getTotal() << " won\n";
        std::cout << "Thank you for visiting C++ Cafe!\n";
    }

private:
    std::vector<Order> orders;
};

// 기존 Kiosk에서 사용하던 입출력 함수
void printMenu(const std::vector<MenuItem>& menu);
int getMenuChoice();
int getQuantity();

int main() {
    const std::vector<MenuItem> menu = {
        {"Americano", 4500},
        {"Latte", 5000},
        {"Tea", 4000}
    };

    std::cout << "================================\n";
    std::cout << "            C++ Kiosk\n";
    std::cout << "================================\n";
    std::cout << "Welcome to C++ Cafe!\n\n";

    printMenu(menu);

    Cart cart;
    int menuNumber = -1;

    while (menuNumber != 0) {
        menuNumber = getMenuChoice();

        if (menuNumber == 0) {
            break;
        }

        if (menuNumber < 1 || menuNumber > 3) {
            std::cout << "Invalid menu number. Please try again.\n\n";
            continue;
        }

        int quantity = getQuantity();

        if (quantity <= 0) {
            std::cout << "Invalid quantity. Please try again.\n\n";
            continue;
        }

        // TODO 4: 메뉴 번호 1, 2, 3을 menu의 인덱스 0, 1, 2에 대응시키세요.
        const MenuItem& selectedItem = menu[0];  // TODO: menu[0] 수정

        // TODO 5: selectedItem과 quantity로 Order를 만들어
        //         Cart의 public 멤버 함수 addOrder()를 호출하세요.

        std::cout << "Added: " << selectedItem.name
                  << " x " << quantity << "\n";
        std::cout << "Current total: " << cart.getTotal() << " won\n\n";
    }

    cart.printReceipt();
    return 0;
}

void printMenu(const std::vector<MenuItem>& menu) {
    std::cout << "Menu\n";
    int menuNumber = 1;
    for (const MenuItem& item : menu) {
        std::cout << menuNumber << ". " << item.name
                  << " - " << item.price << " won\n";
        menuNumber++;
    }
    std::cout << "0. Checkout\n\n";
}

int getMenuChoice() {
    int menuNumber = 0;
    std::cout << "Select menu number: ";
    std::cin >> menuNumber;
    return menuNumber;
}

int getQuantity() {
    int quantity = 0;
    std::cout << "Quantity: ";
    std::cin >> quantity;
    return quantity;
}
