## 개요
이 프로젝트는 STM32 마이크로컨트롤러를 사용하여 엘리베이터를 제어하는 펌웨어입니다. 스텝 모터를 이용한 엘리베이터의 층간 이동 및 도어 개폐 기능을 포함하고 있으며, 버튼 및 센서를 이용하여 엘리베이터를 조작할 수 있습니다.

## 기능
- 엘리베이터 이동 제어 (스텝 모터 사용)
- 문 개폐 제어
- 내부 및 외부 버튼 입력 처리
- 7세그먼트 디스플레이를 통한 층 표시
- I2C LCD를 이용한 상태 표시
- 타이머 기반 인터럽트 처리
- 광학 센서를 이용한 문 개폐 감지

## 시스템 구성
### 1. 주요 모듈
- **main.c**: 시스템 초기화 및 메인 루프 실행
- **motor.c/motor.h**: 스텝 모터 제어
- **7SEG.c/7SEG.h**: 7세그먼트 디스플레이 제어
- **i2c_lcd.c/i2c_lcd.h**: I2C LCD 디스플레이 제어
- **btn.c/btn.h**: 버튼 입력 처리
- **Ele_And_Door.c/Ele_And_Door.h**: 엘리베이터 및 문 제어

### 2. 주요 변수
```c
volatile SystemStatus sysStatus;
ElevatorStatus elevatorStatus;
```
- `sysStatus`: 시스템 상태 (문 개폐, 센서 감지 등) 관리
- `elevatorStatus`: 엘리베이터의 현재 층과 동작 상태 관리

### 3. 주요 함수
- `moveElevatorTo(uint8_t floor)`: 엘리베이터를 지정한 층으로 이동
- `openDoors(void)`: 엘리베이터 문 열기
- `closeDoors(void)`: 엘리베이터 문 닫기
- `HandleButtonPress(Button* btn)`: 버튼 입력 처리
- `HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)`: 외부 인터럽트 콜백
- `HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)`: 타이머 인터럽트 처리

## 하드웨어 구성
- **MCU**: STM32 시리즈 마이크로컨트롤러
- **모터**: 스텝 모터 3개 (엘리베이터 이동 및 문 개폐)
- **디스플레이**: 7세그먼트 디스플레이, I2C LCD
- **버튼**: 내부/외부 호출 버튼
- **센서**: 광학 센서 (문 개폐 감지)

## 개발 환경
- **IDE**: STM32CubeIDE
- **프로그래밍 언어**: C

## 빌드 및 실행 방법
1. STM32CubeIDE에서 프로젝트를 엽니다.
2. 빌드 후 MCU에 펌웨어를 다운로드합니다.
3. 시스템 전원을 켜고 실행합니다.

## 추가 사항
- 향후 기능 추가 및 개선 예정
- 오류 발생 시 `Error_Handler()` 함수에서 디버깅 가능
- 사용자는 인터럽트 콜백 및 상태 변수를 수정하여 기능을 확장할 수 있음


