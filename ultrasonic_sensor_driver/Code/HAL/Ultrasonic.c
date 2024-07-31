/******************************************************************************
 *
 * File Name: Main.c
 *
 * Created on: 10/10/2023
 *
 * Description:  Fan Controller System
 *
 * Author: Mohamed A. Abdelmoati
 *
 *******************************************************************************/

#include "../MCAL/gpio.h"
#include "../MCAL/icu.h"
#include <util/delay.h>
#include "Ultrasonic.h"


uint16 g_edgeCounter=0;
float64 g_timeHigh=0;
float64 g_distance=0;
ICU_ConfigType config={F_CPU_8,RAISING};

void Ultrasonic_edgeProcessing(void)
{
	g_edgeCounter++;
	if(g_edgeCounter==1)
	{
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(FALLING);
	}
	else if(g_edgeCounter==2)
	{
		g_timeHigh=ICU_getInputCaptureValue();
		ICU_clearTimerValue();
		ICU_setEdgeDetectionType(RAISING);
	}
}


void Ultrasonic_init(void)
{
	ICU_init(&config);
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	GPIO_setupPinDirection(ULTRA_SONIC_TRIGGER_PORT_ID, ULTRA_SONIC_TRIGGER_PIN_ID,PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{
	GPIO_writePin( ULTRA_SONIC_TRIGGER_PORT_ID, ULTRA_SONIC_TRIGGER_PIN_ID,LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin( ULTRA_SONIC_TRIGGER_PORT_ID, ULTRA_SONIC_TRIGGER_PIN_ID,LOGIC_LOW);
}


uint32 Ultrasonic_readDistance(void)
{
	Ultrasonic_Trigger();
	while(1)
	{
		if(g_edgeCounter==2)
		{
			g_edgeCounter=0;
			g_distance = (g_timeHigh/57.8);

			if(g_distance<60)
			{
				g_distance+=1;
			}
			else if(g_distance>348)
			{
				g_distance-=(0.3);
			}

			return g_distance;
		}
	}
}

