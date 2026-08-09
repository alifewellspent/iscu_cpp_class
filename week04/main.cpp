#include <iostream>

// 함수 선언
void printMenu();
int getMenuChoice();
int getQuantity();
int getPrice(int menuNumber);
int calculateItemTotal(int price, int quantity);
void printFinalTotal(int total);

int main() {
    std::cout << "================================\n";
    std::cout << "            C++ Kiosk\n";
    std::cout << "================================\n";
    std::cout << "Welcome to C++ Cafe!\n\n";

    printMenu();

    int total = 0;
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
            int price = getPrice(menuNumber);
            int itemTotal = calculateItemTotal(price, quantity);

            total += itemTotal;

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

            std::cout << "Current total: " << total << " won\n\n";
        }
    }

    printFinalTotal(total);

    return 0;
}

void printMenu() {
    // TODO
}

int getMenuChoice() {
    // TODO
    return 0;  // TODO를 완성한 뒤 삭제
}

int getQuantity() {
    // TODO
    return 0;  // TODO를 완성한 뒤 삭제
}

int getPrice(int menuNumber) {
    // TODO
    return 0;  // TODO를 완성한 뒤 삭제
}

int calculateItemTotal(int price, int quantity) {
    // TODO
    return 0;  // TODO를 완성한 뒤 삭제
}

void printFinalTotal(int total) {
    // TODO
}
