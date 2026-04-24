
#include "main.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef  htim1; //call main.c defined external variable htim1

int count = 0;
int duty = 0;
int COUNT_MAX = 20;

void MyCode(){
	while (1){
		for(count = 0 ; count < 20 ; count++){
			duty = (10 * count / (float)COUNT_MAX + 2.5) / 100.0 * 2000;
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1 , duty);
			HAL_Delay(10);
		}
	}
}


