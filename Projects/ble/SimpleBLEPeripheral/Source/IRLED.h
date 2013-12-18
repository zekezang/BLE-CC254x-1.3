#ifndef IR_LED_H
#define IR_LED_H

/*********************************************************************
 * INCLUDES
 */
#include "hal_board.h"
#define  IRLED P0_4

void SendIRdata(uint8 p_irdata);
void IRLED_init(void);
void IRLED_stop();

#endif
