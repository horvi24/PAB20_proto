#include "core.h"

uint32_t core_next_tick;
uint16_t color_cnt = 0;

// printf >> DBG_RX4 (usart2)
PUTCHAR_PROTOTYPE {
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART4 and Loop until the end of transmission */
	HAL_UART_Transmit(&huart4, (uint8_t*) &ch, 1, 0xFFFF);
	return ch;
}

void core_tick_init(){
    core_next_tick = HAL_GetTick() + TICK_PERIOD;
}

// true every 100ms
uint8_t core_tick(void){
    uint32_t tick = HAL_GetTick();

    if(tick >= core_next_tick){
        if (tick <= (TIMER_PERIOD_32BIT - TICK_PERIOD)){
            core_next_tick =  core_next_tick + TICK_PERIOD;
        } else {
            core_next_tick =  TICK_PERIOD - core_next_tick;
        }
        return 1;
    }
    else return 0;
}

uint8_t key_pressed_event(void)
{
    static uint8_t prev = 0;
    uint8_t now = PWR_KEY();
    uint8_t event = now && !prev;
    prev = now;
    return event;
}

uint16_t change_color_rgb(void){
	uint16_t c = 0;

	switch(color_cnt){
	case 0:
		c = COLOR_RGB565_RED;
		break;
	case 1:
		c = COLOR_RGB565_GREEN;
		break;
	case 2:
		c = COLOR_RGB565_BLUE;
		break;
	default:
		break;
	}
	printf("%1d\n", color_cnt);
	if(color_cnt == 2) printf("\r\n");
	color_cnt = (color_cnt + 1) % 3;
	//if (color_cnt++ > 2) color_cnt = 0;
	return c;
}

uint16_t change_color(void){
	uint16_t c = 0;

	switch(color_cnt){
	case 0:
		c = COLOR_RGB565_RED;
		break;
	case 1:
		c = COLOR_RGB565_GREEN;
		break;
	case 2:
		c = COLOR_RGB565_BLUE;
		break;
	case 3:
		c = COLOR_RGB565_WHITE;
		break;
	case 4:
		c = COLOR_RGB565_ORANGE;
		break;
	case 5:
		c = COLOR_RGB565_CRIMSON;
		break;
	case 6:
		c = COLOR_RGB565_PINK;
		break;
	default:
		break;
	}

	printf("%1d\n", color_cnt);
	if(color_cnt == 6) printf("\r\n");
	color_cnt = (color_cnt + 1) % 7;
	//if (color_cnt++ > 5) color_cnt = 0;
	return c;
}
