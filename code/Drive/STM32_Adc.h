#ifndef __STM32_Adc_H_
#define __STM32_Adc_H_
#include "config.h" 


#define DISABLE_ALL_CHANNEL     9

extern u16 ADC_VAL;
void ADC1_SingleChannel(uint8_t ADC_Channel_x);
u16 ADC1_SingleChannel_Get(uint8_t ADC_Channel_x);
u16 Get_Adc_Average(uint8_t ADC_Channel_x,uint8_t times);

#endif
