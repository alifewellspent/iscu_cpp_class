#include <iostream>
#include <vector>

// 함수 선언
void printMenu();
int getMenuChoice();
int getQuantity();
int getPrice(int menuNumber);
int calculateItemTotal(int price, int quantity);
void printFinalTotal(std::vector<int> cart);

int main() {
    std::cout << "================================\n";
    std::cout << "            C++ Kiosk\n";
    std::cout << "================================\n";
    std::cout << "Welcome to C++ Cafe!\n\n";

    printMenu();

    std::vector<int> cart;
    int menuNumber = -1;

    while (menuNumber != 0) {
        menuNumber = getMenuChoice();

        if (menuNumber == 0) {
            break;
        }

        if (menuNumber < 1 || menuNumber > 3) {
            std::cout << "Invalid menu number. Please try again.\n\n";
        }
        else {
            int quantity = getQuantity();
            
            for (int count = 0; count < quantity; count++) {
                // TODO: 선택한 메뉴 번호를 cart에 추가
                
            }

            switch (menuNumber) {
                case 1:
                    std::cout << "Added: Americano x " << quantity << "\n";
                    break;

                case 2:
                    std::cout << "Added: Latte x " << quantity << "\n";
                    break;

                case 3:
                    std::cout << "Added: Tea x " << quantity << "\n";
                    break;
            }

            std::cout << "Items in cart: " << cart.size() << "\n\n";
        }
    }

    printFinalTotal(cart);

    return 0;
}

void printMenu() {
    std::cout << "Menu\n";
    std::cout << "1. Americano - 4500 won\n";
    std::cout << "2. Latte     - 5000 won\n";
    std::cout << "3. Tea       - 4000 won\n";
    std::cout << "0. Checkout\n\n";
}

int getMenuChoice() {
    int menuNumber;

    std::cout << "Select menu number: ";
    std::cin >> menuNumber;

    return menuNumber;
}

int getQuantity() {
    int quantity;

    std::cout << "Quantity: ";
    std::cin >> quantity;

    return quantity;
}

int getPrice(int menuNumber) {
    switch (menuNumber) {
        case 1:
            return 4500;
        case 2:
            return 5000;
        case 3:
            return 4000;
        default:
            return 0;
    }
}

int calculateItemTotal(int price, int quantity) {
    return price * quantity;
}

void printFinalTotal(std::vector<int> cart) {
    int total = 0;

    for (int menuNumber : cart) {
        int price = getPrice(menuNumber);
        total += calculateItemTotal(price, 1);
    }

    std::cout << "\nFinal total: " << total << " won\n";
    std::cout << "Thank you for visiting C++ Cafe!\n";
}
