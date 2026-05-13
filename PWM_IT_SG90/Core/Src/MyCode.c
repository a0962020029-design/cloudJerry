#include "main.h"
#include "stm32f1xx_hal.h"
#include <stdio.h>

#define TURN_PWM_MAX 200 // for device SG90 turn MAX
#define TURN_PWM_MIN 100 // for device SG90 turn MAX

extern TIM_HandleTypeDef  htim1; // call main.c defined external variable htim1
extern TIM_HandleTypeDef  htim3;
extern TIM_HandleTypeDef  *htim;


uint32_t ICValue1 = 0;
uint32_t ICValue2 = 0;
uint32_t DiffICValue = 0;
uint8_t CaptureIndex = 0;
uint8_t cycle = 0;


int flagPWM = 0;

//PWM PIN-A8

//for Interrupt
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim){
	if (HAL_TIM_GetActiveChannel(htim) == HAL_TIM_ACTIVE_CHANNEL_1){
		if (CaptureIndex == 0){
			ICValue1 = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);
			CaptureIndex = 1;
		}
		else if (CaptureIndex == 1){
			ICValue2 = HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);
			if (ICValue2 > ICValue1)
				DiffICValue = ICValue2 - ICValue1;
			else if (ICValue2 < ICValue1)
				DiffICValue = ((65535 - ICValue1) + ICValue2) + 1;

			cycle = DiffICValue/100; // cycle = CCR / (Inside CLK / Prescaler)
			CaptureIndex = 0;
			flagPWM = 1;
		}
	}
}


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

		// print cycle and frequency
		if (flagPWM == 1){
			printf("PWM cycle: %d (ms) \r\n", cycle);
			printf("PWM frequency: %.2f (kHz) \r\n", 1.0/cycle); //float

			flagPWM = 0;
		}
/*
		// SWV TEST
		printf("Hello world! ");
		printf("I'm in Cycle %ld\n", number);
		number++;
		HAL_Delay(100);*/
	}
}

