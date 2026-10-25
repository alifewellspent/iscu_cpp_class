# 9주차 실습: C++ Kiosk 구조체와 클래스 리팩토링

## 1. 실습 목표

이전 주차의 Kiosk는 `std::vector<int>`에 메뉴 번호를 저장했습니다. 이번에는 **사용자에게 보이는 주문 흐름은 유지**하면서 프로그램 내부 표현을 바꿉니다.

- `MenuItem` 구조체로 **메뉴 이름과 가격**을 표현합니다.
- `Order` 구조체로 **메뉴와 수량**을 함께 표현합니다.
- `Cart` 클래스로 **주문 목록과 관련 기능**을 관리합니다.
- `public`, `private`, 멤버 함수 뒤의 `const`가 어떤 역할을 하는지 확인합니다.

### 이전 주차와 비교

| 이전 주차 | 9주차 |
| --- | --- |
| `std::vector<int> cart` | `Cart cart` |
| 메뉴 번호 `1`을 수량만큼 반복 저장 | `Order{MenuItem, quantity}` 한 건으로 저장 |
| 메뉴 번호에서 가격을 별도 조회 | `order.item.price`에서 가격 확인 |
| `printFinalTotal(cart)` | `cart.getTotal()`과 `cart.printReceipt()` |

예를 들어, 아메리카노 2잔과 라테 1잔은 다음과 같이 표현할 수 있습니다.

```cpp
MenuItem americano{"Americano", 4500};
MenuItem latte{"Latte", 5000};

Cart cart;
cart.addOrder({americano, 2});
cart.addOrder({latte, 1});
cart.printReceipt();
```

## 2. 준비 및 실행

GitHub Codespaces에서 이 저장소를 열고 터미널에서 다음을 실행합니다.

```bash
cd week09
make run
```

실습 파일은 `main.cpp`입니다. 빌드 명령은 `Makefile`에 정의되어 있습니다. `main.cpp`를 저장하고 `make run`을 다시 실행하면 수정한 코드로 빌드됩니다.

시작 코드도 **컴파일은 되지만**, TODO를 완성하기 전에는 주문이 저장되지 않거나 총액이 0으로 표시됩니다. 이는 실습을 위한 의도적인 상태입니다.

## 3. 제공된 코드 확인

`main.cpp`에서 다음 구성을 찾습니다.

```cpp
struct MenuItem {
    std::string name;
    int price;
};

struct Order {
    MenuItem item;
    int quantity;
};
```

`Cart`에는 다음 세 가지 `public` 멤버 함수가 준비되어 있습니다.

```cpp
void addOrder(const Order& order);
int getTotal() const;
void printReceipt() const;
```

주문 목록은 `private`에 있습니다.

```cpp
private:
    std::vector<Order> orders;
```

**주의:** `main()`에서 `cart.orders`에 직접 접근하지 않습니다. 주문은 반드시 `addOrder()`를 이용해 추가합니다.

## 4. TODO 구현하기

`main.cpp`에 있는 TODO를 번호순으로 완성하세요. 코드를 모두 새로 작성할 필요는 없습니다.

### TODO 1 — `Cart::addOrder()` (주문 추가)

- `order.quantity`가 **0 이하**라면 주문을 저장하지 않습니다.
- 정상적인 주문이면 `orders`에 추가합니다.
- `orders`는 `private`이지만 `Cart`의 멤버 함수 안에서는 접근할 수 있습니다.

힌트: `if`, `return`, `push_back()`을 사용할 수 있습니다.

### TODO 2 — `Cart::getTotal() const` (총액 계산)

- `orders`에 저장된 주문들을 순회합니다.
- 각 주문의 `item.price`와 `quantity`를 곱합니다.
- 계산한 값을 `total`에 누적합니다.
- 이미 작성된 `return total;`은 그대로 사용합니다.

힌트: `for (const Order& order : orders)`를 사용할 수 있습니다.

### TODO 3 — `Cart::printReceipt() const` (영수증 출력)

- 각 주문의 메뉴 이름, 수량, 주문 금액을 출력합니다.
- 주문별 금액은 **가격 × 수량**입니다.
- 예: `Americano x 2 = 9000 won`
- 마지막 합계와 감사 문구는 이미 제공되어 있습니다.

### TODO 4 — `main()`에서 메뉴 선택

- `menu` 벡터에는 메뉴 1, 2, 3이 **인덱스 0, 1, 2**에 들어 있습니다.
- `selectedItem`이 실제 선택한 메뉴를 가리키도록 초기화 코드를 수정합니다.
- 메뉴 번호 2를 입력했다면 `Latte`가 선택되어야 합니다.

### TODO 5 — `main()`에서 `Cart`에 주문 추가

- `selectedItem`과 `quantity`로 `Order` 한 건을 만듭니다.
- `cart`의 `addOrder()`를 사용하여 주문을 저장합니다.
- 아메리카노 2잔을 주문해도 `Order`는 한 건만 추가합니다. 수량은 그 주문의 `quantity`에 저장됩니다.

힌트: 교안에 나온 `cart.addOrder({americano, 2});`와 같은 형태를 참고하세요.

## 5. 실행 결과 확인

다음 순서로 입력해 보세요.

1. 메뉴 번호 **1**, 수량 **2**
2. 메뉴 번호 **2**, 수량 **1**
3. 메뉴 번호 **0** (Checkout)

TODO를 완성했다면 핵심 출력이 다음과 같아야 합니다.

```text
Added: Americano x 2
Current total: 9000 won

Added: Latte x 1
Current total: 14000 won

Receipt
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
Thank you for visiting C++ Cafe!
```

실제 화면에는 메뉴 안내와 입력 프롬프트도 함께 표시됩니다.

### 추가 확인

| 입력 시나리오 | 확인할 결과 |
| --- | --- |
| `1 → 수량 2 → 0` | 합계 `9000 won` |
| `3 → 수량 1 → 0` | 합계 `4000 won` |
| `9 → 0` | 잘못된 메뉴 번호 안내, 합계 `0 won` |
| `1 → 수량 0 → 0` | 잘못된 수량 안내, 합계 `0 won` |
| 바로 `0` | 주문 없이 합계 `0 won` |
| `1 → 2잔 → 1 → 1잔 → 0` | 영수증에 아메리카노가 두 줄로 표시되고 합계 `13500 won` |

## 6. 자가 점검

- [ ] `MenuItem`에는 `name`, `price`가 들어 있다.
- [ ] `Order`에는 `item`, `quantity`가 들어 있다.
- [ ] `Cart`의 `orders`는 `private`으로 선언되어 있다.
- [ ] `addOrder()`는 0 이하의 수량을 저장하지 않는다.
- [ ] `getTotal() const`가 모든 주문의 총액을 계산한다.
- [ ] `printReceipt() const`가 각 주문과 총액을 출력한다.
- [ ] `main()`은 `cart.orders`에 직접 접근하지 않고 `addOrder()`를 호출한다.
- [ ] `make run`으로 실행해 여러 메뉴와 수량을 시험했다.

## 7. 오류가 발생했다면

| 현상 | 확인할 항목 |
| --- | --- |
| 항상 Americano가 추가됨 | TODO 4의 메뉴 번호와 벡터 인덱스 관계 |
| 합계가 계속 0원임 | TODO 1, 2, 5의 주문 저장·합계 누적 코드 |
| 영수증에 주문 항목이 없음 | TODO 3의 `orders` 순회 코드 |
| `orders is private` 컴파일 오류 | `main()`에서 `cart.orders`에 직접 접근하지 않았는지 확인 |
| `const` 관련 컴파일 오류 | `getTotal()`, `printReceipt()`가 주문을 변경하지 않는지 확인 |
| 수정한 코드가 실행되지 않음 | 파일 저장 후 `make run` 다시 실행 (`make clean` 후 재시도 가능) |

> 핵심 질문: 이전에는 아메리카노 두 잔을 `1, 1`로 저장했습니다. 이번에는 왜 `Order{americano, 2}`로 표현하는 것이 더 명확할까요?
