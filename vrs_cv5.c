/*
 * vrs_cv5.c
 *
 *  Created on: 20. 10. 2016
 *      Author: Smoli
 */
#include <vrs_cv5.h>
#include <stddef.h>
#include "stm32l1xx.h"

void Init()
{
    // Init structures
    GPIO_InitTypeDef GPIO_InitStructure;
    ADC_InitTypeDef  ADC_InitStructure;

    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE); // Enable GPIO clock
    /* Configure ADCx Channel 0 as analog input */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_HSICmd(ENABLE); // Enable the HSI oscillator
    while(RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET); // Check that HSI oscillator is ready
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); // Enable ADC clock
    ADC_StructInit(&ADC_InitStructure); // Initialize ADC structure
    /* ADC1 configuration */
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    /* ADCx regular channel8 configuration */
    ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_16Cycles);
    /* Enable the ADC */
    ADC_Cmd(ADC1, ENABLE);
    /* Wait until the ADC1 is ready */
    while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADONS) == RESET)
    {
    }
    /* Start ADC Software Conversion */
    ADC_SoftwareStartConv(ADC1);

}

void Intpre()
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_IRQn; //zoznam prerušení nájdete vsúbore stm32l1xx.h
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);




}



//prerusenie

