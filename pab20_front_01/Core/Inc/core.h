#ifndef INC_CORE_H_
#define INC_CORE_H_

#include "include.h"

#define TIMER_PERIOD_16BIT  0xFFFF
#define TIMER_PERIOD_32BIT  0xFFFFFFFF

#define TICK_PERIOD         100 //100ms



// printf >> DBG_RX4 (usart4)
#ifdef __GNUC__
// With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
// set to 'Yes') calls __io_putchar()
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif // __GNUC__

#define LED_RS_TOGGLE()		HAL_GPIO_TogglePin(LED_ON_RS_GPIO_Port, LED_ON_RS_Pin)
#define LED_RS_OFF()        HAL_GPIO_WritePin(LED_ON_RS_GPIO_Port, LED_ON_RS_Pin, GPIO_PIN_SET)
#define LED_RS_ON()         HAL_GPIO_WritePin(LED_ON_RS_GPIO_Port, LED_ON_RS_Pin, GPIO_PIN_RESET)

#define LED_WW_TOGGLE()		HAL_GPIO_TogglePin(LED_ON_WW_GPIO_Port, LED_ON_WW_Pin)
#define LED_WW_OFF()        HAL_GPIO_WritePin(LED_ON_WW_GPIO_Port, LED_ON_WW_Pin, GPIO_PIN_SET)
#define LED_WW_ON()         HAL_GPIO_WritePin(LED_ON_WW_GPIO_Port, LED_ON_WW_Pin, GPIO_PIN_RESET)

#define PWR_HOLD_ON()       HAL_GPIO_WritePin(PWR_HOLD_GPIO_Port, PWR_HOLD_Pin, GPIO_PIN_SET)
#define PWR_HOLD_OFF()      HAL_GPIO_WritePin(PWR_HOLD_GPIO_Port, PWR_HOLD_Pin, GPIO_PIN_RESET)

#define PWR_KEY()           HAL_GPIO_ReadPin(PWR_KEY_GPIO_Port, PWR_KEY_Pin)

void core_tick_init(void);
uint8_t core_tick(void);
uint8_t key_pressed_event(void);
uint16_t change_color(void);


#endif /* INC_CORE_H_ */
