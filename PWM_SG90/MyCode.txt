#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

extern TIM_HandleTypeDef  htim1; // call main.c defined external variable htim1
extern TIM_HandleTypeDef  *htim;

uint32_t number = 0;
uint16_t ICValue1 = 0;
uint16_t ICValue2 = 0;
uint8_t DiffICValue = 0;
uint8_t CaptureIndex = 0;

#define TURN_PWM_MAX 200 // for device SG90 turn MAX
#define TURN_PWM_MIN 100 // for device SG90 turn MAX

int flagPWM = 0;

//PWM PIN-A8

void MyCode(){
	while (1){
		// output PWM signal for SG20
		for (int count = TURN_PWM_MIN ; count < TURN_PWM_MAX ; count++ ){
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 , count); //change Pulse
			HAL_Delay(5);
		}
		for (int count1 = TURN_PWM_MAX ; count1 >= TURN_PWM_MIN; count1-- ){
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 , count1); //change Pulse
			HAL_Delay(5);
		}

		if(__HAL_TIM_GET_FLAG(&htim1 , TIM_FLAG_CC1) != RESET){ //when LOW -> HIGH RESET change
			printf("Read PWM %ld\n", number);
			number++;
		}

		/*// SWV TEST
		printf("Hello world! ");
		printf("I'm in Cycle %ld\n", number);
		number++;
		HAL_Delay(100);*/
	}
}
