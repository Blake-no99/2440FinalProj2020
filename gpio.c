/*
 * gpio.c
 *
 *  Created on: Sep 30, 2019
 *      Author: jack + arielle
 */


#include "msp.h"
#include <stdint.h>

#include "gpio.h"
/*
 * P1.5 -> EN
 */
void config_drv_gpio(void) {
    P1->DIR |= BIT5;            // EN pin
    P1->OUT &= ~BIT5;           // initialize LOW
}

void toggle_drv_enable_pin(void) {
    P1->OUT ^= BIT5;
}

void config_UART_gpio(void){

    //set Tx (P3.3) pins.
    P3->SEL0 |= BIT3;
    P3->SEL1 &= ~BIT3;


    // Configure ports
    P6->DIR |= BIT4;

    // Select Alternate Function 1
    P6->SEL0 |= BIT4;       // SEL0 = 0b01
    P6->SEL1 &= ~BIT4;      // SEL1 = 0b00

    //UART: TODO finsish this
}

/* configure P2.4 to output the waveform produced by TAO.1 */
void config_pwm_gpio(void) {
    P2->DIR |= BIT4;        // output

    // Select Alternate Function 1
    P2->SEL0 |= BIT4;       // SEL0 = 0b01
    P2->SEL1 &= ~BIT4;      // SEL1 = 0b00
}
