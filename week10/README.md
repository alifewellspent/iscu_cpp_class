# 10주차 실습: C++ Kiosk 생성자와 소멸자로 객체 생명주기 확인하기

## 1. 실습 목표

9주차에는 `Cart` 클래스로 주문 목록을 관리했습니다. 이번 주에는 `Cart`에 **생성자와 소멸자**를 추가하고, 실행 중에 출력되는 로그를 보며 `cart` 객체가 **언제 만들어지고 언제 사라지는지** 직접 확인합니다.

- `Cart` 클래스의 생성자에서 객체 생성 로그를 출력합니다.
- `Cart` 클래스의 소멸자에서 객체 소멸 로그를 출력합니다.
- 실행 결과의 로그로 객체가 생성되고 소멸되는 시점을 확인합니다.

### 9주차와 비교

| 9주차 | 10주차 |
| --- | --- |
| `Cart cart;` | `Cart cart{name};` |
| 생성자를 작성하지 않음 (컴파일러가 기본 생성자를 제공) | `Cart(const std::string& name)` 생성자를 직접 작성 |
| 소멸자를 작성하지 않음 (컴파일러가 기본 소멸자를 제공) | `~Cart()` 소멸자를 직접 작성 |
| 고객 정보 없음 | `customerName` 멤버에 고객 이름을 저장 |
| 영수증 제목: `Receipt` | 영수증 제목: `Receipt for Mina` |
| `cart`가 `main()`이 끝날 때까지 존재 | `cart`가 중괄호 블록 `{ }` 안에서만 존재 |

9주차 TODO 1~5(주문 추가, 총액 계산, 영수증 출력, 메뉴 선택, 주문 저장)는 이번 주 `main.cpp`에 이미 구현되어 있습니다. 이번 주에는 **`Cart` 객체의 생명주기**에만 집중합니다.

## 2. 준비 및 실행

GitHub Codespaces에서 이 저장소를 열고 터미널에서 다음을 실행합니다.

```bash
cd week10
make run
```

실습 파일은 `main.cpp`입니다. 빌드 명령은 `Makefile`에 정의되어 있습니다. `main.cpp`를 저장하고 `make run`을 다시 실행하면 수정한 코드로 빌드됩니다.

시작 코드도 **컴파일과 실행은 되지만**, TODO를 완성하기 전에는 생성 로그와 소멸 로그가 출력되지 않고, 영수증 제목에 고객 이름이 비어 있습니다(`Receipt for `). 이는 실습을 위한 의도적인 상태입니다.

## 3. 시작 전 확인: 수정할 코드와 TODO 위치

### TODO 위치

| TODO | 위치 | 할 일 |
| --- | --- | --- |
| TODO 1 | `Cart` 클래스의 `public:` 바로 아래 | 생성자를 작성하고 생성 로그를 출력 |
| TODO 2 | TODO 1 바로 아래 | 소멸자를 작성하고 소멸 로그를 출력 |
| TODO 3 | `main()`의 중괄호 블록 안에 있는 `Cart cart;` | 입력받은 고객 이름을 전달하여 `Cart` 객체를 생성 |

### `Cart`의 멤버 변수

```cpp
private:
    std::string customerName;
    std::vector<Order> orders;
```

`customerName`은 이번 주에 새로 추가된 멤버입니다. `printReceipt()`는 영수증 제목에 이 값을 출력하지만, 시작 코드에서는 아직 어디에서도 값을 설정하지 않기 때문에 빈 문자열로 출력됩니다. 이 값은 TODO 1에서 작성할 생성자가 초기화합니다.

### `cart`가 선언된 scope

`main()`에서 `cart`는 별도의 중괄호 블록 안에 선언되어 있습니다.

```cpp
std::string name = getCustomerName();

{   // cart의 scope 시작
    Cart cart;

    // ... 주문 반복문 ...

    cart.printReceipt();
}   // cart의 scope 끝
```

교안 2.1에서 본 예제처럼, `cart`는 이 블록 안에서 선언되었으므로 블록의 닫는 중괄호 `}`를 벗어나면 생명주기가 끝납니다.

## 4. 추가할 생성자와 소멸자의 형태

`Cart` 클래스 안에 다음 형태의 생성자와 소멸자를 추가합니다. 본문 `{ }` 안의 출력 코드는 직접 작성합니다.

```cpp
class Cart {
public:
    // 생성자: 객체가 생성될 때 자동으로 호출됨
    Cart(const std::string& name)
        : customerName(name) {
        // 생성 로그 출력
    }

    // 소멸자: 객체의 생명주기가 끝날 때 자동으로 호출됨
    ~Cart() {
        // 소멸 로그 출력
    }

    // ... addOrder(), getTotal(), printReceipt() ...

private:
    std::string customerName;
    std::vector<Order> orders;
};
```

| 구분 | 생성자 | 소멸자 |
| --- | --- | --- |
| 이름 | 클래스 이름과 같음 (`Cart`) | 클래스 이름 앞에 `~` (`~Cart`) |
| 반환형 | 작성하지 않음 | 작성하지 않음 |
| 매개변수 | 받을 수 있음 (`const std::string& name`) | 받을 수 없음 |
| 호출 시점 | 객체가 생성될 때 자동 호출 | 객체의 생명주기가 끝날 때 자동 호출 |

출력할 로그의 형식은 다음과 같습니다.

```text
[Log] Cart created for Mina
[Log] Cart destroyed for Mina
```

## 5. TODO 구현하기

`main.cpp`에 있는 TODO를 번호순으로 완성하세요.

### TODO 1: 생성자 작성 (생성 로그 출력)

- 생성자의 이름은 클래스 이름과 같은 `Cart`이며, 반환형을 작성하지 않습니다.
- 매개변수로 고객 이름 `const std::string& name`을 받습니다.
- 멤버 초기화 리스트 `: customerName(name)`으로 `customerName`을 초기화합니다.
- 생성자 본문에서 `[Log] Cart created for ` 뒤에 `customerName`을 이어서 출력하고 줄을 바꿉니다.

> **주의:** TODO 1을 작성한 뒤 바로 `make run`을 실행하면 다음과 비슷한 컴파일 오류가 발생합니다.
>
> ```text
> error: no matching function for call to 'Cart::Cart()'
> ```
>
> 생성자를 하나라도 직접 정의하면 컴파일러가 매개변수 없는 기본 생성자를 자동으로 만들어 주지 않기 때문에, `main()`의 `Cart cart;`를 더 이상 컴파일할 수 없습니다. 이 오류는 TODO 3에서 해결합니다.

### TODO 2: 소멸자 작성 (소멸 로그 출력)

- 소멸자의 이름은 클래스 이름 앞에 `~`를 붙인 `~Cart`입니다.
- 반환형과 매개변수를 작성하지 않습니다.
- 소멸자 본문에서 `[Log] Cart destroyed for ` 뒤에 `customerName`을 이어서 출력하고 줄을 바꿉니다.
- 소멸자는 직접 호출하지 않습니다. `cart`가 선언된 scope를 벗어날 때 자동으로 호출됩니다.

### TODO 3: 고객 이름으로 `Cart` 객체 생성

- `main()`의 중괄호 블록 안에 있는 `Cart cart;`를 수정합니다.
- `getCustomerName()`으로 입력받은 `name`을 생성자에 전달하여 `cart`를 생성합니다.

## 6. 실행 결과 확인

다음 순서로 입력해 보세요.

1. 고객 이름 **Mina**
2. 메뉴 번호 **1**, 수량 **2**
3. 메뉴 번호 **2**, 수량 **1**
4. 메뉴 번호 **0** (Checkout)

TODO를 완성했다면 메뉴 안내 아래의 출력이 다음과 같아야 합니다.

```text
Customer name: Mina
[Log] Cart created for Mina
Select menu number: 1
Quantity: 2
Added: Americano x 2
Current total: 9000 won

Select menu number: 2
Quantity: 1
Added: Latte x 1
Current total: 14000 won

Select menu number: 0

Receipt for Mina
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
Thank you for visiting C++ Cafe!
[Log] Cart destroyed for Mina
```

### 로그의 위치를 scope와 비교하기

로그가 출력된 위치를 `main()`의 코드와 나란히 놓고 비교해 보세요.

| 출력 | 출력되는 시점의 코드 |
| --- | --- |
| `[Log] Cart created for Mina` | 블록 안의 `Cart cart{name};` (객체 생성, 생명주기 시작) |
| `Added: ...`, `Current total: ...` | 블록 안의 주문 반복문 (객체 사용) |
| `Receipt for Mina` ~ `Thank you ...` | 블록의 마지막 문장인 `cart.printReceipt();` |
| `[Log] Cart destroyed for Mina` | 블록의 닫는 중괄호 `}` (scope를 벗어남, 생명주기 종료) |

- 생성 로그는 메뉴를 고르기 전에, `Cart cart{name};`가 실행되는 순간 출력됩니다.
- 소멸 로그는 영수증 출력이 끝난 뒤, 블록의 닫는 중괄호 `}`에 도달할 때 출력됩니다. 코드에 소멸자를 호출하는 문장이 없어도, `cart`가 선언된 scope를 벗어나면 소멸자가 자동으로 호출됩니다.

### 추가 확인

| 입력 시나리오 | 확인할 결과 |
| --- | --- |
| `Jisu → 3 → 수량 1 → 0` | `created for Jisu`와 `destroyed for Jisu`가 출력되고 합계 `4000 won` |
| `Mina → 0` | 주문이 없어도 생성 로그와 소멸 로그가 한 번씩 출력되고 합계 `0 won` |
| `Mina → 9 → 0` | 잘못된 메뉴 번호 안내, 생성 로그와 소멸 로그가 한 번씩 출력 |
| `Mina → 1 → 2잔 → 1 → 1잔 → 0` | 주문을 여러 번 추가해도 생성 로그와 소멸 로그는 한 번씩만 출력되고 합계 `13500 won` |

주문을 몇 번 추가하든 `Cart` 객체는 하나이므로, 생성 로그와 소멸 로그는 각각 **한 번씩만** 출력됩니다.

> **참고:** 이번 실습은 생성자와 소멸자에 집중하기 위해 입력 오류를 따로 처리하지 않습니다. 메뉴 번호의 범위와 0 이하의 수량은 확인하지만, 메뉴 번호나 수량에 숫자가 아닌 값을 입력하거나 고객 이름에 공백을 넣으면 주문을 더 받지 않고 영수증이 출력됩니다. 고객 이름은 `Mina`처럼 공백 없이 입력하고, 메뉴 번호와 수량에는 숫자를 입력하세요.
