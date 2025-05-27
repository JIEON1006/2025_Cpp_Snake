# 2025_Cpp_Snake

---

## 📁 프로젝트 구조

```bash
SnakeGame/o
├── main.cpp # 프로그램 시작점
├── include/
│ ├── block.h # Block 클래스 및 서브클래스 정의
│ └── start_screen.h # 시작 화면 출력 함수
├── map/
│ ├── map.cpp # Map 클래스 구현 (맵 로딩, 출력)
│ └── map.h # Map 클래스 정의
├── map.txt # 정수형 맵 정의 파일
├── Makefile # 빌드 스크립트
└── README.md # 프로젝트 설명

🧩 코드 흐름 요약
------------------------------------------------------------------------
main() 함수에서 Map 객체 생성

map.txt 로드 → 정수 맵 map[][] 생성 -> `Block` 객체로 변환 (createBlockMatrix()로 Block*[][] 생성 (mapArray))

printMap() 또는 printColoredMap()으로 출력

printBlockAt() 내부에서 ncurses의 mvprintw() 사용
---


## 🔨 빌드 방법

### 필수 패키지 (Ubuntu 기준)

```bash
(작업할 경로로 이동)
sudo apt update (한 번만 하면 됨)
sudo apt install g++ libncursesw5-dev (한 번만 하면 됨)
make (코드 수정 후 -> 저장 -> make 입력)
./snake_game (실행)
