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

// 한 고객의 주문을 관리하는 장바구니
class Cart {
public:
    // TODO 1: 고객 이름을 받는 생성자를 작성하세요.
    //         - 형태: Cart(const std::string& name)
    //         - 멤버 초기화 리스트로 customerName을 name 값으로 초기화하세요.
    //         - 생성자 본문에서 "[Log] Cart created for 고객이름" 로그를 출력하세요.

    // TODO 2: 소멸자를 작성하세요.
    //         - 형태: ~Cart()
    //         - 소멸자 본문에서 "[Log] Cart destroyed for 고객이름" 로그를 출력하세요.

    void addOrder(const Order& order) {
        if (order.quantity <= 0) {
            return;
        }
        orders.push_back(order);
    }

    int getTotal() const {
        int total = 0;
        for (const Order& order : orders) {
            total += order.item.price * order.quantity;
        }
        return total;
    }

    void printReceipt() const {
        std::cout << "\nReceipt for " << customerName << "\n";
        for (const Order& order : orders) {
            std::cout << order.item.name << " x " << order.quantity
                      << " = " << order.item.price * order.quantity
                      << " won\n";
        }
        std::cout << "Final total: " << getTotal() << " won\n";
        std::cout << "Thank you for visiting C++ Cafe!\n";
    }

private:
    std::string customerName;
    std::vector<Order> orders;
};

// 기존 Kiosk에서 사용하던 입출력 함수
void printMenu(const std::vector<MenuItem>& menu);
std::string getCustomerName();
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

    std::string name = getCustomerName();

    {   // cart의 scope 시작
        // TODO 3: 생성자를 직접 정의하면 기본 생성자가 자동으로 만들어지지 않습니다.
        //         입력받은 name을 전달하여 Cart 객체를 생성하도록 수정하세요.
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

            const MenuItem& selectedItem = menu[menuNumber - 1];
            cart.addOrder({selectedItem, quantity});

            std::cout << "Added: " << selectedItem.name
                      << " x " << quantity << "\n";
            std::cout << "Current total: " << cart.getTotal() << " won\n\n";
        }

        cart.printReceipt();
    }   // cart의 scope 끝

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

std::string getCustomerName() {
    std::string name;
    std::cout << "Customer name: ";
    std::cin >> name;
    return name;
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
