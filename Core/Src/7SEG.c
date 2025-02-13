

#include "7SEG.h"
#include "delayus.h"

// 0~9까지의 숫자에 해당하는 세그먼트 조합 (0은 A-G)
const uint8_t segmentDigits[] = {
    0x3F,  // 0 -> a, b, c, d, e, f
        0x06,  // 1 -> b, c
        0x5E,  // 2 -> a, b, d, e, g
        0x7A,  // 3 -> a, b, c, d, g
        0x66,  // 4 -> b, c, f, g
        0x6B,  // 5 -> a, c, d, f, g
        0x7B,  // 6 -> a, c, d, e, f, g
        0x0E,  // 7 -> a, b, c
        0x7F,  // 8 -> a, b, c, d, e, f, g
        0x6F   // 9 -> a, b, c, d, f, g
};



// 숫자를 세그먼트 디스플레이에 출력하는 함수
void Display_Number(uint8_t number) {
    if (number > 9) return;  // 0-9 범위의 숫자만 허용

    uint8_t segments = segmentDigits[number];  // 숫자에 해당하는 세그먼트 패턴

    // 각 세그먼트 핀에 대한 설정
    HAL_GPIO_WritePin(GPIOA, SEG_A_PIN, (segments & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, SEG_B_PIN, (segments & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, SEG_C_PIN, (segments & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, SEG_D_PIN, (segments & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, SEG_E_PIN, (segments & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, SEG_F_PIN, (segments & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA, SEG_G_PIN, (segments & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void clearDisplay()
{
  HAL_GPIO_WritePin(GPIOA, SEG_A_PIN, 0);
  HAL_GPIO_WritePin(GPIOB, SEG_B_PIN, 0);
  HAL_GPIO_WritePin(GPIOA, SEG_C_PIN, 0);
  HAL_GPIO_WritePin(GPIOA, SEG_D_PIN, 0);
  HAL_GPIO_WritePin(GPIOC, SEG_E_PIN, 0);
  HAL_GPIO_WritePin(GPIOA, SEG_F_PIN, 0);
  HAL_GPIO_WritePin(GPIOA, SEG_G_PIN, 0);
}

void display_1()
{
  HAL_GPIO_WritePin(GPIOB, SEG_B_PIN, 1);
  HAL_GPIO_WritePin(GPIOA, SEG_C_PIN, 1);
}

void display_2()
{
  HAL_GPIO_WritePin(GPIOA, SEG_A_PIN, 1);
  HAL_GPIO_WritePin(GPIOB, SEG_B_PIN, 1);
  HAL_GPIO_WritePin(GPIOA, SEG_G_PIN, 1);
  HAL_GPIO_WritePin(GPIOC, SEG_E_PIN, 1);
  HAL_GPIO_WritePin(GPIOA, SEG_D_PIN, 1);
}


void display_0()
{
    // 세그먼트를 켠다.
    HAL_GPIO_WritePin(GPIOA, SEG_A_PIN, 1);
    HAL_GPIO_WritePin(GPIOB, SEG_B_PIN, 1);
    HAL_GPIO_WritePin(GPIOA, SEG_C_PIN, 1);
    HAL_GPIO_WritePin(GPIOA, SEG_D_PIN, 1);
    HAL_GPIO_WritePin(GPIOC, SEG_E_PIN, 1);
    HAL_GPIO_WritePin(GPIOA, SEG_F_PIN, 1);

}

