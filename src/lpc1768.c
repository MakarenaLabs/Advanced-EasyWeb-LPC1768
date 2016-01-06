/*
===============================================================================
 Name        : lpc1768.c
 Author      : Enrico Giordano - MakarenaLabs
 Version     : 1.0
 Copyright   : Copyright (C) 2013
 Description : lpc1768 basic functions
===============================================================================
*/

#include "lpc1768.h"


void Delay(int delay)
{
	while(delay)
		delay--;
}


void resetGPIO(void)
{
	LPC_PINCON->PINSEL4 &= ~(0xFFFF); 	// Reset P2[0..7] = GPIO
	LPC_PINCON->PINSEL3 &= ~(3UL<<30); 	// Reset P1.31 = GPIO
	LPC_PINCON->PINSEL4 &= ~(0x03<<20);	// Reset P2.10 = GPIO
	LPC_PINCON->PINSEL3 &= ~(0x03<<18);
	LPC_PINCON->PINSEL3 &= ~(0x03<<20);
	LPC_PINCON->PINSEL3 &= ~(0x03<<24);
	LPC_PINCON->PINSEL3 &= ~(0x03<<26);
	LPC_PINCON->PINSEL7 &= ~(3 << 20);



}


void setOutput_LEDint(void)
{
	// Configurazione Pin GPIO = P2[0..7] Drive LED
		LPC_GPIO2->FIODIR |= 0xFF;			// P2[0..7] = Outputs
}

void setInput_P2(void)
{
	// Configurazione Pin GPIO = P2[0..7] Drive LED
		LPC_GPIO2->FIODIR &= 0x00;			// P2[0..7] = Input

}

void setButton_reset(void)
{
	LPC_GPIO2->FIODIR &= ~(1UL<<10);	
}



void setOutput_ADC_Rint(void)
{
	// A/D configuration
		LPC_PINCON->PINSEL3 |= (3UL << 30);		//configure pin1.31 for current interceptor
		LPC_SC->PCONP |= (1UL << 12); 			//current activation for AD
		LPC_ADC->ADCR = (1UL << 5)				//select AD 0.5 
					  | (1UL << 8)				//18 MHz / 2 conversion
					  | (1UL << 21);			//ADC activation

}


void setBeep(void)
{
	LPC_PINCON->PINSEL7 &= ~(3 << 20);
	LPC_GPIO3->FIODIR |= (1UL<<26);
	LPC_GPIO3->FIOPIN ^= (1 << 26);

}

void stop_beep(void)
{
	if(!LPC_GPIO3->FIOPIN)
		LPC_GPIO3->FIOPIN ^= (1 << 26);
}

void setJoySwitch(void)
{
	LPC_GPIO1->FIODIR &= ~((1UL<<25)|(1UL<<26)|(1UL<<28)|(1UL<<29));	//P1.25,26,28,29=In

}

void turn_off_the_LEDS(void)
{
	LPC_GPIO2->FIOCLR =	0xFF;			
}


void turn_on_single_LED(int led)
{
	LPC_GPIO2->FIOSET = (1<<led);		// ON LED[led]
}


void turn_off_single_LED(int led)
{
	LPC_GPIO2->FIOCLR = (1<<led);		// OFF LED[led]
}


int reset_is_pressed(void)
{
	if ((LPC_GPIO2->FIOPIN >> 10) & 0x01)	//if released
		return 0;
	else					//if pressed
		return 1;

}


int joyswitch_up(void)
{
	if ((LPC_GPIO1->FIOPIN >> 25) & 0x01)
		return 0;
	else
		return 1;
}


int joyswitch_down(void)
{
	if ((LPC_GPIO1->FIOPIN >> 26) & 0x01)
		return 0;
	else
		return 1;
}

int joyswitch_right(void)
{
	if ((LPC_GPIO1->FIOPIN >> 28) & 0x01)
		return 0;
	else
		return 1;
}


int joyswitch_left(void)
{
	if ((LPC_GPIO1->FIOPIN >> 29) & 0x01)
		return 0;
	else
		return 1;
}

int joyswitch_pressed(void)
{
	if ((LPC_GPIO3->FIOPIN >> 25) & 0x01)
		return 0;
	else
		return 1;
}


void beep(int durata, int frequenza)
{
	while(durata)
	{
			LPC_GPIO3->FIOPIN ^= (1 << 26);
			Delay(frequenza);
			durata--;
	}
}


int convert_from_ADC_VR(void)
{
	int val;
	LPC_ADC->ADCR |= (1<<24);				// activate conversion
	while (!(LPC_ADC->ADGDR & (1UL<<31)));	//wait while conversion finished
	val = ((LPC_ADC->ADGDR >> 4) & 0xFFF);	//get value
	LPC_ADC->ADCR &= ~(7<<24);				//deactivate function

	return val;
}
