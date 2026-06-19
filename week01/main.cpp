#include <iostream>

int main() {
    int quantity = 0;

    std::cout << "Welcome to C++ Cafe\n";
    std::cout << "How many coffees would you like? ";
    std::cin >> quantity;

    if (quantity <= 0) {
        std::cout << "Invalid quantity\n";
    } else {
        int price = 3000;
        int total = quantity * price;

        std::cout << "Coffee x " << quantity << '\n';
        std::cout << "Total: " << total << " KRW\n";
    }

    return 0;
}
