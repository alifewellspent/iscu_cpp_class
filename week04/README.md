# Week 04 실습 — 함수로 리팩토링하기

3주차의 주문 프로그램을 여러 함수로 나누어 리팩토링합니다.

`main()`은 이미 완성되어 있습니다.  
아래 Code Bank의 코드 블록을 보고, 각 함수의 역할에 맞는 코드를 찾아 `main.cpp`의 함수 몸체에 붙여 넣으세요.

## 완성할 함수

```cpp
void printMenu();
int getMenuChoice();
int getQuantity();
int getPrice(int menuNumber);
int calculateItemTotal(int price, int quantity);
void printFinalTotal(int total);
```

함수 이름뿐 아니라 **반환형과 매개변수**도 보고 어떤 코드가 들어갈지 판단하세요.

## Code Bank

코드 블록의 순서는 함수 순서와 관계없습니다.

### Code A

```cpp
std::cout << "\nFinal total: " << total << " won\n";
std::cout << "Thank you for visiting C++ Cafe!\n";
```

### Code B

```cpp
return price * quantity;
```

### Code C

```cpp
int quantity;

std::cout << "Quantity: ";
std::cin >> quantity;

return quantity;
```

### Code D

```cpp
switch (menuNumber) {
    case 1:
        return 3500;
    case 2:
        return 5000;
    case 3:
        return 4000;
    default:
        return 0;
}
```

### Code E

```cpp
std::cout << "<< Menu >>\n";
std::cout << "1. Americano - 3500 won\n";
std::cout << "2. Latte      - 5000 won\n";
std::cout << "3. Tea        - 4000 won\n";
std::cout << "0. Checkout\n\n";
```

### Code F

```cpp
int menuNumber;

std::cout << "Select menu number: ";
std::cin >> menuNumber;

return menuNumber;
```

## 먼저 생각해 보기

다음 코드를 보고 값이 어떻게 이동하는지 확인하세요.

```cpp
menuNumber = getMenuChoice();

int quantity = getQuantity();
int price = getPrice(menuNumber);
int itemTotal = calculateItemTotal(price, quantity);

total += itemTotal;
```

- `getMenuChoice()`는 왜 `int`를 반환할까요?
- `getPrice()`에는 왜 `menuNumber`가 필요할까요?
- `calculateItemTotal()`에는 왜 두 개의 매개변수가 필요할까요?
- `printFinalTotal()`은 왜 `void`일까요?

## 실행 결과 확인

```text
Select menu number: 1
Quantity: 2
Added: Americano x 2
Current total: 7000 won

Select menu number: 2
Quantity: 1
Added: Latte x 1
Current total: 12000 won

Select menu number: 0

Final total: 12000 won
Thank you for visiting C++ Cafe!
```
