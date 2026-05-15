#include "main.h"
#include "stm32f1xx_hal.h"

extern ADC_HandleTypeDef hadc1;

int value = 0;
float voltage = 0;

void MyCode(){
	HAL_ADCEx_Calibration_Start(&hadc1); // 校準
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1,HAL_MAX_DELAY); // for continue ask change is finish

	while(1){
		value = HAL_ADC_GetValue(&hadc1);
		voltage = (value / 4095.0)*3.3;
		printf("voltage: %.2f\n",voltage);
		HAL_Delay(500);
	}
}
