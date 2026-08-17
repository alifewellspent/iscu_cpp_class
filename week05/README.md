# Week 05 실습 — `std::vector`로 장바구니 만들기

4주차에 함수로 리팩토링한 주문 프로그램에 `std::vector`를 사용한 장바구니를 추가합니다.

이번 주에는 기존 함수들을 새로 구현하지 않습니다.  
`main.cpp`에 준비된 코드의 흐름을 확인하고, **선택한 메뉴 번호를 주문 수량만큼 `cart`에 저장하는 부분만 완성**하세요.

## 이번 주 달라진 점

4주차에는 주문할 때마다 금액을 `total`에 바로 누적했습니다.

```cpp
int price = getPrice(menuNumber);
int itemTotal = calculateItemTotal(price, quantity);

total += itemTotal;
```

5주차에는 주문한 메뉴 번호를 `std::vector<int>`에 하나씩 저장합니다.

```cpp
std::vector<int> cart;
```

예를 들어 Americano 2잔과 Tea 1잔을 주문하면 장바구니에는 다음과 같이 저장됩니다.

```text
cart = {1, 1, 3}
```

결제할 때 `printFinalTotal(cart)`이 장바구니의 모든 원소를 순회하면서 최종 금액을 계산합니다.

## 완성할 부분

`main.cpp`에서 다음 TODO 부분을 찾으세요.

```cpp
for (int count = 0; count < quantity; count++) {
    // TODO: 선택한 메뉴 번호를 cart에 추가

}
```

반복문이 한 번 실행될 때마다 **현재 선택한 메뉴 번호 하나**가 `cart`의 뒤에 추가되어야 합니다.

이번 실습에서 직접 작성할 코드는 이 부분뿐입니다.

## `cart.size()`로 저장 결과 확인

메뉴를 추가한 뒤 프로그램은 현재 장바구니에 저장된 원소 수를 출력합니다.

```cpp
std::cout << "Items in cart: " << cart.size() << "\n\n";
```

예를 들어 Americano를 2잔 주문했다면:

```text
Items in cart: 2
```

그 다음 Latte를 1잔 주문하면:

```text
Items in cart: 3
```

이 값이 예상과 다르다면 `push_back()`이 주문 수량만큼 실행되고 있는지 확인하세요.

## 결제할 때 일어나는 일

주문이 끝나면 다음 함수가 호출됩니다.

```cpp
printFinalTotal(cart);
```

`printFinalTotal()`은 이미 완성되어 있습니다.

```cpp
void printFinalTotal(std::vector<int> cart) {
    int total = 0;

    for (int menuNumber : cart) {
        int price = getPrice(menuNumber);
        total += calculateItemTotal(price, 1);
    }

    std::cout << "\nFinal total: " << total << " won\n";
    std::cout << "Thank you for visiting C++ Cafe!\n";
}
```

다음 부분은 `cart`에 저장된 메뉴 번호를 처음부터 끝까지 하나씩 꺼내는 **범위 기반 for문**입니다.

```cpp
for (int menuNumber : cart)
```

따라서 장바구니가 다음과 같다면:

```text
cart = {1, 1, 2}
```

반복 중 `menuNumber`에는 차례대로 다음 값이 들어갑니다.

```text
1
1
2
```

각 메뉴 번호의 가격을 구해 더하면 최종 금액을 계산할 수 있습니다.

## 실행 결과 확인

다음과 같이 주문해 보세요.

```text
Select menu number: 1
Quantity: 2
Added: Americano x 2
Items in cart: 2

Select menu number: 2
Quantity: 1
Added: Latte x 1
Items in cart: 3

Select menu number: 0

Final total: 14000 won
Thank you for visiting C++ Cafe!
```

결과가 다르다면 다음을 확인하세요.

- `push_back()`에 `menuNumber`를 추가했는가?
- `push_back()`이 `for` 반복문 안에 있는가?
- 수량이 2이면 메뉴 번호가 두 번 저장되는가?
- `cart.size()`가 주문 수량만큼 증가하는가?

## 실습 완료 조건

다음 세 가지를 확인하면 실습 완료입니다.

1. Americano 2잔을 주문했을 때 `Items in cart: 2`가 출력된다.
2. 이어서 Latte 1잔을 주문했을 때 `Items in cart: 3`이 출력된다.
3. Checkout을 선택했을 때 `Final total: 14000 won`이 출력된다.
