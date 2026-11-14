# 12주차 실습: C++ Kiosk 영수증 파일 저장하기

12주차 실습은 이 수업에서 제출해야 하는 두 번째 과제입니다. TODO 1~4를 모두 완성한 `main.cpp`를 제출합니다. 제출 방법과 평가 방법은 [8. 제출과 평가](#8-제출과-평가)에 있습니다.

## 1. 실습 목표

지금까지 `Cart`는 `printReceipt()`로 영수증을 화면에만 출력했습니다. 이번 주에는 영수증을 **파일에 저장하는 기능**과 저장된 파일을 **다시 읽어 출력하는 기능**을 추가합니다. 또한 `Cart` 객체를 `unique_ptr`로 관리하도록 `main()`을 수정합니다.

- `Cart`의 `saveReceipt()`에서 `std::ofstream`으로 영수증을 `receipt.txt`에 저장합니다.
- `printSavedReceipt()`에서 `std::ifstream`과 `std::getline()`으로 저장된 파일을 읽어 화면에 출력합니다.
- `printSavedReceipt()`에서 파일을 열지 못한 경우를 처리합니다.
- `main()`의 `Cart` 객체를 `std::make_unique`로 만들어 `unique_ptr`로 관리합니다.
- 프로그램을 실행한 뒤 `receipt.txt`가 만들어진 위치를 확인합니다.
- `saveReceipt()`가 끝날 때 파일이 자동으로 닫히는 이유를 RAII와 연결하여 설명합니다.

### 10주차와 비교

| 10주차 | 12주차 |
| --- | --- |
| 영수증을 화면에만 출력 | 영수증을 화면에 출력하고 `receipt.txt`에도 저장 |
| 프로그램이 끝나면 주문 내역이 사라짐 | `receipt.txt`가 남아 있어 다음 실행에서 다시 읽을 수 있음 |
| 파일 입출력 코드 없음 | `std::ofstream`, `std::ifstream` 사용 |
| `Cart`를 지역 객체로 선언 | `Cart`를 `std::make_unique`로 만들어 `unique_ptr`로 관리 |

교안의 표에는 `saveReceipt()`로 적혀 있습니다. 실습 코드에서는 저장할 파일 이름을 매개변수로 받는 `saveReceipt(const std::string& filename) const` 형태로 작성합니다.

10주차 TODO 1~3(생성자, 소멸자, 고객 이름으로 `Cart` 객체 생성)은 이번 주 `main.cpp`에 이미 구현되어 있습니다. 이번 주에는 파일 입출력과 `unique_ptr`에 집중합니다.

## 2. 준비 및 실행

GitHub Codespaces에서 이 저장소를 열고 터미널에서 다음을 실행합니다.

```bash
cd week12
make run
```

실습 파일은 `main.cpp`입니다. 빌드 명령은 `Makefile`에 정의되어 있습니다. `main.cpp`를 저장하고 `make run`을 다시 실행하면 수정한 코드로 빌드됩니다.

시작 코드도 **컴파일과 실행은 되지만**, TODO를 완성하기 전에는 `receipt.txt`가 만들어지지 않고 `Previous receipt:`와 `Saved receipt:` 아래에 아무 내용도 출력되지 않습니다. 이는 실습을 위한 의도적인 상태입니다. 컴파일할 때 표시되는 `unused parameter 'filename'` 경고는 TODO를 완성하면 사라집니다.

## 3. 시작 전 확인: 수정할 코드와 TODO 위치

### TODO 위치

| TODO | 위치 | 할 일 |
| --- | --- | --- |
| TODO 1 | `Cart` 클래스의 `saveReceipt()` 본문 | 영수증을 파일에 저장 |
| TODO 2 | `main()` 아래에 있는 `printSavedReceipt()` 본문 | 파일을 한 줄씩 읽어 화면에 출력 |
| TODO 3 | `printSavedReceipt()` 본문 | 파일을 열지 못한 경우 안내 메시지 출력 |
| TODO 4 | `main()`의 `Cart cart{name};`과 `cart`의 멤버 함수 호출 코드 | `std::make_unique`를 사용하는 코드로 수정 |

### `main()`의 실행 흐름

`main()`에는 두 함수를 호출하는 코드가 이미 작성되어 있습니다. `main()`에서는 TODO 4에 해당하는 코드만 수정합니다.

```cpp
std::cout << "Previous receipt:\n";
printSavedReceipt("receipt.txt");       // 1. 직전 실행에서 저장한 영수증 읽기

// ... 메뉴 출력과 고객 이름 입력 ...

{   // cart의 scope 시작
    Cart cart{name};                    // TODO 4에서 수정

    // ... 주문 반복문 ...

    cart.printReceipt();                // 2. 영수증을 화면에 출력
    cart.saveReceipt("receipt.txt");    // 3. 영수증을 파일에 저장
}   // cart의 scope 끝

std::cout << "\nSaved receipt:\n";
printSavedReceipt("receipt.txt");       // 4. 저장한 파일 다시 읽기
```

4번 코드는 `cart`가 소멸한 뒤에 실행됩니다. `cart` 객체는 이미 사라졌지만, 파일에 저장한 내용은 남아 있으므로 다시 읽을 수 있습니다.

### 수정하지 않는 코드

- TODO 1~4를 완성하는 데 필요하지 않은 코드는 특별한 이유 없이 수정하지 않습니다. 특히 메뉴의 이름과 가격, 입력을 받는 순서는 시작 코드와 같아야 합니다.
- 파일 이름은 폴더 경로 없이 시작 코드와 같이 `"receipt.txt"`를 사용합니다.
- 시작 코드의 `main()`에 있는 `Previous receipt:`, `Saved receipt:` 안내 문구와 `[Log]` 출력은 수정하지 않습니다.

### `printReceipt()`와 `saveReceipt()` 비교

| 멤버 함수 | 영수증이 출력되는 곳 | 출력에 사용하는 객체 |
| --- | --- | --- |
| `printReceipt()` | 화면 | `std::cout` |
| `saveReceipt()` | `receipt.txt` | `std::ofstream` 객체 |

두 함수 모두 `<<`로 데이터를 출력합니다. 어느 출력 스트림 객체를 사용하는가에 따라 출력되는 곳이 달라집니다.

## 4. TODO 구현하기

`main.cpp`에 있는 TODO를 번호순으로 완성하세요.

### TODO 1: `Cart::saveReceipt()` (영수증을 파일에 저장)

- `std::ofstream` 객체를 만들어 `filename` 파일을 엽니다.
- `printReceipt()`처럼 `<<`를 사용하되, `std::cout` 대신 방금 만든 객체에 출력합니다.
- `orders`의 각 주문을 순회하여, 주문 한 건의 메뉴 이름, 수량, 주문 금액을 한 줄에 저장합니다.
- 고객 이름과 최종 금액을 포함하여 다음 형식으로 저장합니다. 첫 줄 앞의 빈 줄과 감사 문구는 저장하지 않습니다.

```text
Receipt for Mina
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
```

`receipt.txt`의 저장 형식은 반드시 위 예시와 같아야 합니다. 고객 이름, 주문 내역, 금액만 입력에 따라 달라집니다.

`receipt.txt`에는 이번 실행의 영수증만 저장합니다. 이전 실행에서 저장된 내용은 남기지 않습니다.

`close()`는 호출하지 않아도 됩니다.

### TODO 2: `printSavedReceipt()` (저장된 파일 읽기)

- `std::ifstream` 객체를 만들어 `filename` 파일을 엽니다.
- 읽은 내용을 저장할 `std::string` 변수를 선언합니다.
- `std::getline()`으로 파일을 한 줄씩 읽어 그대로 화면에 출력합니다.

### TODO 3: `printSavedReceipt()` (파일을 열지 못한 경우 처리)

프로그램을 처음 실행할 때에는 `receipt.txt`가 아직 없으므로 `printSavedReceipt()`가 파일을 열지 못합니다. 이는 프로그램의 오류가 아니라, 저장된 영수증이 아직 없는 정상적인 상황입니다.

`printSavedReceipt()`에서 파일을 열지 못한 경우에는 저장된 영수증이 없다는 것을 알리는 안내 메시지를 출력한 뒤, 프로그램을 종료하지 않고 이후 주문을 계속 진행해야 합니다. 5장의 실행 예시에서는 `No saved receipt.`가 안내 메시지입니다.

안내 메시지의 문구는 자유롭게 작성해도 됩니다. 다만 안내 메시지는 파일을 열지 못한 경우에만 출력해야 합니다. 파일이 있을 때에도 출력되는 문구는 안내 메시지로 인정하지 않습니다.

`saveReceipt()`에서 파일을 열지 못한 경우의 처리는 추가해도 되지만 평가하지 않습니다.

### TODO 4: `main()` (`unique_ptr`로 `Cart` 관리)

- `main()`의 `Cart cart{name};`을 `std::make_unique`를 사용하는 코드로 바꾸고, 그에 맞게 멤버 함수 호출 코드를 수정해야 합니다.
- `main()`의 `{ }` 블록(`cart`의 scope)은 그대로 둡니다. `Cart`는 5장의 실행 예시와 같이 `Saved receipt:`가 출력되기 전에 소멸해야 합니다.
- `new`와 `delete`는 사용하지 않습니다.
- 필요한 헤더는 직접 추가합니다.

TODO 4는 `unique_ptr`의 문법을 연습하고, `unique_ptr`이 관리하는 객체가 소멸하는 시점을 확인하기 위한 것입니다.

## 5. 실행 결과 확인

### 처음 실행하기

이전에 만든 파일이 남아 있을 수 있으므로 먼저 다음 명령으로 삭제합니다.

```bash
rm -f receipt.txt
make run
```

다음 순서로 입력해 보세요.

1. 고객 이름 **Mina**
2. 메뉴 번호 **1**, 수량 **2**
3. 메뉴 번호 **2**, 수량 **1**
4. 메뉴 번호 **0** (Checkout)

TODO를 모두 완성했다면 출력이 다음과 같아야 합니다. 아래 예시에서 프로그램 제목과 메뉴 안내는 생략했습니다.

```text
Previous receipt:
No saved receipt.

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

Saved receipt:
Receipt for Mina
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
```

아직 `receipt.txt`가 없으므로 `Previous receipt:` 아래에는 TODO 3에서 작성한 안내 메시지가 출력됩니다. 위 예시의 `No saved receipt.`는 안내 메시지의 예입니다.

### 저장된 파일 확인하기

```bash
cat receipt.txt
```

```text
Receipt for Mina
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
```

### 다시 실행하기

`make run`을 한 번 더 실행하면 첫 화면에 직전 실행의 영수증이 표시됩니다. 이번에는 파일이 있으므로 안내 메시지가 출력되지 않아야 합니다.

```text
Previous receipt:
Receipt for Mina
Americano x 2 = 9000 won
Latte x 1 = 5000 won
Final total: 14000 won
```

### 추가 확인

| 입력 시나리오 | 확인할 결과 |
| --- | --- |
| `Jisu → 3 → 수량 1 → 0` | `receipt.txt`에 `Jisu`의 영수증만 남고 합계 `4000 won` (기존 내용은 지워짐) |
| `Mina → 0` | 주문 없이 `receipt.txt`에 합계 `0 won` 저장 |
| `Mina → 9 → 1 → 수량 0 → 0` | 잘못된 입력 안내, `receipt.txt`에 합계 `0 won` 저장 |
| `Mina → 1 → 수량 2 → 1 → 수량 1 → 0` | `receipt.txt`에 아메리카노가 두 줄로 저장되고 합계 `13500 won` |

### `receipt.txt`가 만들어지는 위치 확인하기

`"receipt.txt"`는 상대 경로이므로 프로그램을 실행한 **현재 작업 폴더**에 만들어집니다. `make run`은 `week12` 폴더에서 프로그램을 실행하므로 지금까지는 `week12`에 파일이 만들어졌습니다. 이번에는 상위 폴더에서 실행해 봅니다.

```bash
cd ..
./week12/main
```

프로그램이 시작되면 고객 이름(예: Mina)과 0을 입력해 주문을 마친 뒤, 다음 명령으로 파일을 확인합니다.

```bash
ls receipt.txt
```

상위 폴더에 `receipt.txt`가 새로 만들어진 것을 확인할 수 있습니다. 확인한 뒤 다음 명령으로 파일을 삭제하고 `week12` 폴더로 돌아옵니다.

```bash
rm receipt.txt
cd week12
```

## 6. 자가 점검

- [ ] `saveReceipt()`가 `std::ofstream`으로 영수증을 저장한다.
- [ ] `printSavedReceipt()`가 `std::ifstream`과 `std::getline()`으로 파일을 읽어 출력한다.
- [ ] `receipt.txt`에 고객 이름, 주문 내역, 최종 금액이 저장된다.
- [ ] 프로그램을 다시 실행하면 직전 실행의 영수증이 첫 화면에 표시된다.
- [ ] `receipt.txt`가 없을 때 안내 메시지가 출력되고, 주문이 끝까지 진행된다.
- [ ] `receipt.txt`가 있을 때에는 안내 메시지가 출력되지 않는다.
- [ ] `Cart`를 `std::make_unique`로 만들었고, `new`와 `delete`를 사용하지 않았다.
- [ ] `[Log] Cart destroyed`가 `Saved receipt:`보다 먼저 출력된다.
- [ ] 상위 폴더에서 실행하여 `receipt.txt`가 만들어지는 위치가 달라지는 것을 확인했다.
- [ ] `close()`를 호출하지 않아도 파일이 닫히는 이유를 설명할 수 있다.

## 7. 오류가 발생했다면

| 현상 | 확인할 항목 |
| --- | --- |
| `receipt.txt`가 보이지 않음 | `pwd`로 프로그램을 실행한 폴더를 확인 |
| 영수증이 화면에 두 번 출력되고 파일은 비어 있음 | TODO 1에서 `std::cout`이 아니라 `std::ofstream` 객체에 출력하는지 확인 |
| `Saved receipt:` 아래에 아무 내용도 없음 | TODO 1의 파일 저장 코드와 TODO 2의 읽기 반복문을 확인 |
| `return-statement with a value` 컴파일 오류 | 교안 예제의 `return 1;`은 `main()`의 코드임. `void` 함수에서는 값을 반환할 수 없으므로 `return 1;`을 사용하지 않음 |
| 수정한 코드가 실행되지 않음 | 파일 저장 후 `make run` 다시 실행 (`make clean` 후 재시도 가능) |

> **참고:** 10주차와 마찬가지로 고객 이름은 `Mina`처럼 공백 없이 입력하고, 메뉴 번호와 수량에는 숫자를 입력하세요.

> 핵심 질문: `saveReceipt()`에는 `close()`를 호출하는 코드가 없습니다. 그런데도 `printSavedReceipt()`가 저장된 내용을 모두 읽을 수 있는 이유는 무엇일까요? `std::ofstream` 객체의 생명주기와 RAII를 연결하여 설명해 보세요.

## 8. 제출과 평가

### 제출 방법

- TODO 1~4를 모두 완성한 `main.cpp` 파일 하나만 LMS에 제출합니다.

### 주의 사항

- `.cpp` 파일로 제출하지 않으면 예외 없이 0점입니다. 코드를 캡처한 이미지, 문서 파일, 압축 파일(`.zip` 등)로 제출한 경우도 0점입니다.
- 반드시 12주차 시작 코드(starter code)인 `main.cpp`에서 시작합니다. 직접 새로 작성한 코드나 다른 주차의 코드를 수정한 코드는 제출하지 않습니다.
- 시작 코드에서 TODO 1~4를 완성하는 데 필요하지 않은 코드는 특별한 이유 없이 수정하지 않습니다. 평가는 시작 코드의 메뉴, 입력 순서, 출력 문구를 기준으로 진행하므로, 이 부분이 달라지면 테스트에 실패하여 감점될 수 있습니다.
- 제출 전에 반드시 Codespaces에서 `make run`으로 컴파일과 실행을 확인합니다. 평가는 Codespaces와 같은 환경에서 진행하므로, 다른 환경에서 컴파일되는 코드도 평가에서는 컴파일되지 않을 수 있습니다. 컴파일이 되지 않으면 5점입니다.

### 평가 방법

제출된 프로그램은 여러 가지 입력 조합으로 총 5개의 테스트를 수행합니다. 테스트에서는 화면 출력과 `receipt.txt`의 내용을 함께 확인합니다.

5장의 실행 예시와 실제 평가에 사용되는 입력 조합은 다를 수 있으며, 정상적인 주문뿐 아니라 잘못된 메뉴 번호, 잘못된 수량, `receipt.txt`가 없는 경우와 이미 있는 경우도 테스트할 수 있습니다. 고객 이름은 공백 없이 입력하고, 메뉴 번호와 수량은 숫자로 입력합니다.

- 5개 테스트 모두 통과: 15점
- 테스트 1개 실패할 때마다 2점 감점
- `std::make_unique`로 `Cart`를 관리하지 않은 경우(`new` 또는 `delete`를 사용하거나 `Cart`를 일반 지역 객체로 선언한 경우 포함), 3점을 감점합니다.
- `saveReceipt()`와 `printSavedReceipt()` 중 하나라도 완성되어 있지 않은 경우(`std::ofstream`, `std::ifstream`, `std::getline()`을 사용하지 않은 경우 포함), 실행 테스트 결과와 상관없이 최종 점수는 최대 7점입니다.
- 컴파일이 되지 않는 경우, 최종 점수는 5점입니다. 컴파일이 되는 경우의 최저 점수도 5점입니다.
- `.cpp` 파일로 제출하지 않은 경우, 0점입니다.
