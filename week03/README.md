# Week 03 실습 — 조건문과 반복문으로 주문 기능 완성하기

## 실습 목표

2주차까지 작성한 C++ Kiosk에 다음 기능을 추가합니다.

- 메뉴 번호를 반복해서 입력받기
- `0`을 입력하면 주문 종료하기
- 잘못된 메뉴 번호 처리하기
- 메뉴에 따라 서로 다른 가격 계산하기
- 여러 주문의 금액을 `total`에 누적하기

이번 실습에서는 완성 코드를 제공하지 않습니다.

`main.cpp`의 TODO 영역에 아래 **Code Bank**에서 필요한 조각을 선택하여 적절한 순서로 배치하세요.

> **주의:** 모든 코드 조각을 사용하는 것은 아닙니다.  
> 일부 조각은 그대로 사용할 수 있고, 일부는 빈칸을 완성하거나 수정해야 합니다.

---

# 목표 실행 결과

다음과 비슷하게 동작하도록 프로그램을 완성하세요.

```text
================================
            C++ Kiosk
================================
Welcome to C++ Cafe!

<< Menu >>
1. Americano - 3500 won
2. Latte      - 5000 won
3. Tea        - 4000 won
0. Checkout

Select menu number: 1
Quantity: 2
Added: Americano x 2
Current total: 7000 won

Select menu number: 2
Quantity: 1
Added: Latte x 1
Current total: 12000 won

Select menu number: 9
Invalid menu number. Please try again.

Select menu number: 0

Final total: 12000 won
Thank you for visiting C++ Cafe!
```

---

# 1. 먼저 프로그램의 흐름을 생각하기

코드를 작성하기 전에 다음 질문에 답해 보세요.

1. 메뉴 번호 입력은 한 번만 받아야 할까요, 반복해서 받아야 할까요?
2. `0`을 입력했는지는 수량을 입력받기 전과 후 중 언제 검사해야 할까요?
3. 잘못된 메뉴 번호를 입력하면 그 아래의 수량 입력 코드를 실행해야 할까요?
4. 메뉴 번호에 따라 서로 다른 코드를 실행하려면 어떤 문법이 적합할까요?
5. 한 번 주문한 뒤 다시 메뉴 선택으로 돌아가려면 어떤 구조 안에 주문 코드를 넣어야 할까요?

---

# 2. Code Bank

아래 코드 조각에서 **필요한 것만 골라** `main.cpp`의 TODO 영역에 배치하세요.

코드 조각의 순서는 실제 프로그램에서 사용해야 하는 순서와 관계없습니다.

---

### Code A

```cpp
std::cout << "Quantity: ";
std::cin >> quantity;
```

### Code B

```cpp
if (menuNumber < 1 || menuNumber > 3) {
    std::cout << "Invalid menu number. Please try again.\n\n";
    continue;
}
```

### Code C

```cpp
while (menuNumber != 0) {

}
```

### Code D

```cpp
std::cout << "Current total: " << total << " won\n\n";
```

### Code E

```cpp
if (menuNumber == 0) {
    break;
}
```

### Code F

```cpp
std::cout << "Select menu number: ";
std::cin >> menuNumber;
```

### Code G

```cpp
switch (menuNumber) {
    case 1:
        total += 3500 * quantity;
        std::cout << "Added: Americano x " << quantity << "\n";
        break;

    case 2:
        total += 5000 * quantity;
        std::cout << "Added: Latte x " << quantity << "\n";
        break;

    case 3:
        total += 4000 * quantity;
        std::cout << "Added: Tea x " << quantity << "\n";
        break;
}
```

### Code H

```cpp
if (menuNumber >= 1 || menuNumber <= 3) {
    std::cout << "Valid menu\n";
}
```

### Code I

```cpp
while (menuNumber == 0) {

}
```

### Code J

```cpp
total = 3500 * quantity;
```

### Code K

```cpp
if (menuNumber == 0) {
    continue;
}
```

---

# 3. 배치 조건

프로그램의 흐름이 다음 조건을 만족하도록 코드를 구성하세요.

### 조건 1
프로그램은 `0`을 입력하기 전까지 계속 메뉴 번호를 입력받아야 합니다.

### 조건 2
메뉴 번호 `0`을 입력하면 `Quantity:`를 출력하지 않고 주문을 종료해야 합니다.

### 조건 3
`1`, `2`, `3` 이외의 메뉴 번호를 입력하면 다음 메시지를 출력하고 다시 메뉴 번호를 입력받아야 합니다.

```text
Invalid menu number. Please try again.
```

### 조건 4
정상적인 메뉴 번호를 입력한 경우에만 수량을 입력받아야 합니다.

### 조건 5
메뉴별 가격은 다음과 같습니다.

```text
Americano : 3500 won
Latte     : 5000 won
Tea       : 4000 won
```

### 조건 6
여러 번 주문하면 이전 주문 금액이 사라지지 않고 계속 누적되어야 합니다.

---

# 4. 중간 확인

프로그램을 완성한 뒤 다음 입력을 순서대로 테스트하세요.

## 테스트 1 — 한 번 주문

입력:

```text
1
2
0
```

기대되는 최종 금액:

```text
Final total: 7000 won
```

---

## 테스트 2 — 여러 번 주문

입력:

```text
1
2
2
1
0
```

기대되는 최종 금액:

```text
Final total: 12000 won
```

---

## 테스트 3 — 잘못된 메뉴 번호

입력:

```text
9
0
```

확인할 것:

```text
Invalid menu number. Please try again.
```

`9`를 입력한 뒤에는 `Quantity:`가 나오면 안 됩니다.

---


# 5. 완료 체크

프로그램이 완성되었다면 다음을 확인하세요.

- [ ] `while`을 사용하여 주문을 반복한다.
- [ ] `0`을 입력하면 바로 반복문을 종료한다.
- [ ] 잘못된 메뉴 번호에서는 수량을 입력받지 않는다.
- [ ] `switch`로 세 메뉴를 구분한다.
- [ ] `total`이 주문할 때마다 누적된다.
- [ ] `break`와 `continue`의 차이를 설명할 수 있다.
- [ ] Code Bank에서 사용하지 않아야 하는 코드를 구분할 수 있다.
