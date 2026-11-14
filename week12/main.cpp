#include <fstream>
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
    Cart(const std::string& name)
        : customerName(name) {
        std::cout << "[Log] Cart created for " << customerName << "\n";
    }

    ~Cart() {
        std::cout << "[Log] Cart destroyed for " << customerName << "\n";
    }

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

    void saveReceipt(const std::string& filename) const {
        // TODO 1: std::ofstream으로 filename 파일을 열고,
        //         다음 형식으로 영수증을 파일에 저장하세요.
        //
        //         Receipt for Mina
        //         Americano x 2 = 9000 won
        //         Latte x 1 = 5000 won
        //         Final total: 14000 won
    }

private:
    std::string customerName;
    std::vector<Order> orders;
};

// 저장된 영수증 파일을 읽어 화면에 출력하는 함수
void printSavedReceipt(const std::string& filename);

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

    // 직전 실행에서 저장한 영수증을 읽어 출력
    std::cout << "Previous receipt:\n";
    printSavedReceipt("receipt.txt");
    std::cout << "\n";

    printMenu(menu);

    std::string name = getCustomerName();

    {   // cart의 scope 시작
        // TODO 4: 아래의 Cart cart{name};을 std::make_unique를 사용하는 코드로 바꾸고,
        //         그에 맞게 cart의 멤버 함수 호출 코드를 수정하세요.
        //         new와 delete는 사용하지 않습니다.
        Cart cart{name};

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
        cart.saveReceipt("receipt.txt");
    }   // cart의 scope 끝

    // cart가 소멸한 뒤에 저장된 파일을 다시 읽어 출력
    std::cout << "\nSaved receipt:\n";
    printSavedReceipt("receipt.txt");

    return 0;
}

void printSavedReceipt(const std::string& filename) {
    // TODO 2: std::ifstream으로 filename 파일을 열고,
    //         std::getline()으로 한 줄씩 읽어 화면에 출력하세요.
    //
    // TODO 3: 파일을 열지 못한 경우에는 저장된 영수증이 없다는 안내 메시지를 출력하세요.
    //         프로그램을 종료하지 않고 이후 주문이 계속 진행되어야 합니다.
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
