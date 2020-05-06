/*
 * UART.c
 *
 *  Created on: May 5, 2020
 *      Author: Blake Novak
 */


#include "msp.h"
#include <stdint.h>
#include <UART_driver.h>
#include "gpio.h"






//#define toWriteFlag (P6->OUT);
//
//extern uint8_t toWrite;
//
//
//// configurations for the UART eUSCI found on pg901 of tech ref manual.pdf
////want to use eUSCI A1 for UART to LCD.
//
void config_UART(void) {
    //set Tx (P3.3) pins.
    P3->SEL0 |= BIT3;
    P3->SEL1 &= ~BIT3;
    EUSCI_A1->CTLW0 &= ~BITD; // specific to UART for LSB 1st mode.

    EUSCI_A1->CTLW0 |= EUSCI_A_CTLW0_SWRST;         // UCSWRST = 1 freeze UART

    // configure UART
    EUSCI_A1->CTLW0 |= (EUSCI_A_CTLW0_MODE_0 |      // select UART mode
                        EUSCI_A_CTLW0_MST    |      // select master mode
                        EUSCI_A_CTLW0_SSEL__SMCLK);    // select SMCLK as clock source


    EUSCI_A1->MCTLW = EUSCI_A_MCTLW_OS16; //UCOS16 oversampling enable (pg925)
    EUSCI_A1->MCTLW |= (EUSCI_A_MCTLW_OS16 |
                        (0x8 << EUSCI_A_MCTLW_BRF_OFS) |
                         0x55 << EUSCI_A_MCTLW_BRS_OFS)
                        ; //UCOS16 enable (pg925)


            EUSCI_A1->BRW = 19;                              // set prescaler to have 9600hz

    config_UART_gpio();                              // gpio.c sets UART Rx & Tx


    //todo enable interrupt
        NVIC_EnableIRQ(EUSCIA1_IRQn);  // enable interrupts
        EUSCI_A1->IE  = (EUSCI_A_IE_TXIE | EUSCI_A_IE_RXIE);


    EUSCI_A1->CTLW0 &= ~(EUSCI_A_CTLW0_SWRST);      // clear UCSWRST (reactivate UART)
    EUSCI_A1->IFG = 0; //write flag lowered

}


void write_string(const char *value) {
    while(*value != '\0'){ //while value is a char
            while( !(EUSCI_A1->IFG & EUSCI_A_IFG_TXIFG)); //while the Tx write flag is NOT up do nothing
                EUSCI_A1->TXBUF = *value; //load into buffer
                value++;//next char
    }

}

//
//void write_string(char *value) {
//    //this function loads a string into the Tx buffer using interrupts.
//    //the interrupt will keep pushing characters into the buffer
//    //until the string pointer is null or terminator char.
//        //2) clears the LCD
//        //
//        //3) writes the new string to pwm 1 char at a time.
//
////raise flag
//    while(*value != '\0' || value == 0){ //while value is a char
// //       EUSCI_A1->TXBUF = *value; // 0
//        transmit_char_over_uart(*value);
//        value++;
//    }
//}
//
//
////    EUSCI_A1->TXBUF = reg;                          // send register being written to
////    while(!(EUSCI_A1->IFG  & EUSCI_A_IFG_TXIFG0));
////
////    EUSCI_A1->TXBUF = value;                        // send value being written to
////    while(!(EUSCI_A1->IFG  & EUSCI_A_IFG_TXIFG0));
////
////}
//
//
//using the LCD manual at SparkFun.com we find that typing the two characters "|" then "-"
//reset the LCD
void clear_lcd_screen(void){
    write_string("|");
    write_string("-");

}
//void transmit_char_over_uart(uint8_t value){
//    //clear_lcd_screen();
//    //this function transmits a single char over UART to the LCD screen.
//    //it waits until the flag is lowered, then buffers the next bit into the PWM register
//    volatile int i = 0;
//    //set high for a clock cycle, then low for a cycle
//    //to enable device and get ready to transmit a bit.
//    while (TIMER_A0->CCTL[0]!=TIMER_A_CCTLN_CCIFG);
//
//    if(~(TIMER_A0->CCTL[0])) //set true once ready for chars.
//    P6->OUT |= P6->OUT;
//    toWrite |= toWrite;
//
//    while(TIMER_A0->CCTL[0]!=TIMER_A_CCTLN_CCIFG);
//
//    if(~(TIMER_A0->CCTL[0])) //set to false once char has transmitted.
//    P6->OUT &= ~(P6->OUT) ;
//    toWrite &= ~(toWrite);
//
//    while(i < 8){ //send the 8 bits over UART least->most
//        if(TIMER_A0->CCTL[0]==TIMER_A_CCTLN_CCIFG){ //ready to write flag means next clk cycle ready
//            toWrite = ((7-i) & ( 1 << value )) >> value; //writes high to the i th bit of value
//            P6->OUT = ((7-i) & ( 1 << value )) >> value; //writes high to the i th bit of value
//            value++;
//            i++;
//        }
//    }
//    if(~(TIMER_A0->CCTL[0])) //set to false once char has transmitted.
//    P6->OUT |= P6->OUT ;
//    toWrite |= toWrite;
//
//}
//
//this is the simple irq handler that toggles the pin every 9600hz
void TA0_0_IRQHandler(void){ // name goes inside vector table
    TIMER_A0->CTL &= ~(TIMER_A_CTL_IE);     //turn off interrupts --don't have multiple interrupts
    //check flag(s)
    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG){ //if TIMER_A_CCTLN_CCIFG means on clock flag check

    }
    //toggle pin every 50ms
    //reset flag
    TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG); //reset flag
    TIMER_A0->CTL |= TIMER_A_CTL_IE; //enable interrupt for timer

}
//
//
////
////void EUSCIB0_IRQHandler(void) {
////    if(EUSCI_A1->IFG & //A1 Interrupt flag Register is high
////            !EUSCI_A_IFG_TXIFG)) // transmit interrupt flag is low
////        EUSCI_A1->TXBUF = value;        // send value being written to tx buffer.
////
////}
