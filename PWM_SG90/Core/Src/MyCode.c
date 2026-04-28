
#include "main.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef  htim1; //call main.c defined external variable htim1

#define TURN_PWM 200 //for device SG90 turn MAX

void MyCode(){
	while (1){
		for (int count = 100 ; count < TURN_PWM ; count++ ){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1 , count);
			HAL_Delay(5);
		}
		for (int count1 = TURN_PWM ; count1 > 99 ; count1-- ){
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1 , count1);
			HAL_Delay(5);
		}
		if
	}
}
