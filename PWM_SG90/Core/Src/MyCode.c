
#include "main.h"
#include "stm32f1xx_hal.h"

extern TIM_HandleTypeDef  htim1; // call main.c defined external variable htim1
//extern UART_HandleTypeDef huart1;
//extern TIM_HandleTypeDef  *htim;

#define TURN_PWM_MAX 200 // for device SG90 turn MAX
#define TURN_PWM_MIN 100 // for device SG90 turn MAX

int duty = 0;

uint16_t ICValue1=0;
uint16_t ICValue2=0;
uint16_t DiffICValue=0;
uint8_t CaptureIndex=0;

/*
int __io_putchar(int ch)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}*/

void MyCode(){
	while (1){
		// output PWM signal for SG20
		for (int count = TURN_PWM_MIN ; count < TURN_PWM_MAX ; count++ ){
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 , count);
			HAL_Delay(5);
		}
		for (int count1 = TURN_PWM_MAX ; count1 >= TURN_PWM_MIN; count1-- ){
			__HAL_TIM_SET_COMPARE(&htim1 , TIM_CHANNEL_1 , count1);
			HAL_Delay(5);
		}
/*
		//input PWM print time
		if(htim -> Channel == HAL_TIM_ACTIVE_CHANNEL_2){
			if (CaptureIndex == 0){
				ICValue1 = HAL_TIM_ReadCapturedValue(htim , TIM_CHANNEL_2);
				CaptureIndex = 1;
			}
			else if (CaptureIndex == 1){
				ICValue2 = HAL_TIM_ReadCapturedValue(htim , TIM_CHANNEL_2);
				if (ICValue2 > ICValue1)
					DiffICValue = ICValue2 - ICValue1;
				else if (ICValue2 < ICValue1)
					DiffICValue = ((0xFFFF - ICValue1) + ICValue2)+1;

					printf("Time = %d (ms)\r\n" , DiffICValue/10);
					CaptureIndex = 0;
			}
		}*/
	}
}
