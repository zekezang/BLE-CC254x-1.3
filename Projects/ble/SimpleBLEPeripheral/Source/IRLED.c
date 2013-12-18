#include <ioCC2540.h>
//#include "Common.h"
#include "hal_lcd.h"
#include "hal_board.h"
#include "IRLED.h"

//uint32 counter = 0;
//uint8  timeout = 0;
////////////////////////////////////

#define  IRLED P0_4
uint16 count;
uint16 endcount;
uint8 flag;

uint8 iraddr1;
uint8 iraddr2;
void SendIRdata(uint8 p_irdata);

////////////////////////////////////////////////
void HalTimer3Init() {
	//T3CTL &= ~0x03;
	T3CTL = 0xAE;
	T3CC0 = 0x1A;
	T3CCTL0 = 0x44;
	//P1IFG &= ~BV(0);
}

void HalTimer3Start() {
	T3CTL |= 0x10;
}

void HalTimer3Stop() {
	T3CTL &= ~0x10;
}

void HalTimer3EnableInt() {
	EA = 1;
	T3IE = 1;
	//IEN1 |= BV(3);
}

void HalTimer3DisableInt() {
	T3IE = 0;
	//IEN1 &= ~ BV(3);
}

void GPIO_LedsInit() {
	HAL_TURN_OFF_LED3();
	P0DIR |= BV(4);
	P0SEL &= ~(BV(4));
}
/*********************************LEDs*****************************************/

void IRLED_stop() {
	HalTimer3DisableInt();
	HalTimer3Stop();
}

////////////////////////////////////////////////////////////////////////////////////
void IRLED_init() {
	GPIO_LedsInit();
	HalTimer3Init();
	HalTimer3EnableInt();
	HalTimer3Start();

	//HalLcdWriteString( "Ok",  HAL_LCD_LINE_5 );

//////////////////////////////////////////
	count = 0;
	flag = 0;
	IRLED = 0;
	// P3_4 = 0;

	iraddr1 = 40;
	iraddr2 = 40;
	//SendIRdata(1);
////////////////////////////////////////////////////

}
void SendIRdata(uint8 p_irdata) {
	uint8 i;
	uint8 irdata = p_irdata;

	/***************************************************************/

	endcount = 3;
	flag = 1;
	count = 0;
	while (count < endcount) {
		HalLcdWriteStringValue("count111", count, 10, HAL_LCD_LINE_6);
	}

//	endcount = 5;
//	flag = 0;
//	count = 0;
//	while (count < endcount) {
//
//	}
//
//	/***************************************************************/
//	irdata = iraddr1;
//	for (i = 0; i < 8; i++) {
//
//		endcount = 21; //560us/26us = 21
//		flag = 1;
//		count = 0;
//		while (count < endcount);
//
//		if (irdata - (irdata / 2) * 2) {
//			endcount = 64;
//		} else {
//			endcount = 21;
//		}
//		flag = 0;
//		count = 0;
//
//		while (count < endcount);
//
//		irdata = irdata >> 1;
//
//	}
//
//	irdata = iraddr2;
//	for (i = 0; i < 8; i++) {
//		endcount = 21;
//		flag = 1;
//		count = 0;
//
//		while (count < endcount);
//
//		if (irdata - (irdata / 2) * 2) {
//			endcount = 64;
//
//		} else {
//			endcount = 21;
//		}
//
//		flag = 0;
//		count = 0;
//
//		while (count < endcount);
//
//		irdata = irdata >> 1;
//	}
//
//	irdata = p_irdata;
//
//	for (i = 0; i < 8; i++) {
//		endcount = 21;
//		flag = 1;
//		count = 0;
//
//		while (count < endcount);
//
//		if (irdata - (irdata / 2) * 2) {
//			endcount = 64;
//
//		} else {
//			endcount = 21;
//		}
//
//		flag = 0;
//		count = 0;
//
//		while (count < endcount);
//
//		irdata = irdata >> 1;
//	}
//
//	irdata = ~p_irdata;
//
//	for (i = 0; i < 8; i++) {
//		endcount = 21;
//		flag = 1;
//		count = 0;
//
//		while (count < endcount);
//
//		if (irdata - (irdata / 2) * 2) {
//			endcount = 64;
//		} else {
//			endcount = 21;
//		}
//
//		flag = 0;
//		count = 0;
//
//		while (count < endcount);
//
//		irdata = irdata >> 1;
//	}

}

HAL_ISR_FUNCTION( halTimer3Isr, T3_VECTOR) {
	HAL_ENTER_ISR();
	count++;
	HalLcdWriteStringValue("count", count, 10, HAL_LCD_LINE_5);
	if (flag == 1) {
		IRLED = ~IRLED;
	} else {
		IRLED = 0;
	}
	HAL_EXIT_ISR();
}
