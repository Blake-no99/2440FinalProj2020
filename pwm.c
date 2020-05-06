/*
 * @author: May 5 2020.
 * Blake Novak
 *
 *  pwm.c
 */

#include "msp.h"
#include <stdint.h>
#include "pwm.h"


/* Global Variables */
extern uint8_t pwm_values[6];
extern uint8_t pwm_select;

/* Configure TIMER_A0 to produce a PWM waveform
 *
 * - reset the R (timer counter) register
 * - select the SMCLK (3MHz) in the CTL register
 * - select the Reset/Set output mode for the T0.1 timer using CCTL[1]
 */

void config_pwm_timer(void) {
    TIMER_A0->R = 0x00;                         // reset the counter
    TIMER_A0->CTL = (TIMER_A_CTL_SSEL__SMCLK);  // SMCLK- 3 MHz
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;  // select Reset/set Output Mode
    /* Note: Timer is in Compare Mode by default, so we don't need to set it */
}

/* Starts a PWM signal on Pin XX at the specified duty_cycle at 100kHz,
 * Note: the DRV2605L PWM input frequency is 10kHz-250kHz
 *
 * - calculate and set the amount of ticks needed in CCR[0] (capture and compare reg. 0) for the desired PWM frequency's period
 * - calculate and set the amount of ticks needed in CCR[1] (capture and compare reg. 1) for the desired duty cycle
 * - enable/start timer by putting it in the Up counter mode
 *      - TIMER_A0->R will count from 0 to CCR[1] and the output will be HIGH
 *      - then, TIMER_A0->R will count from CCR[1] to CCR[0] and the output will be LOW
 *      - after TIMER_A0->R == CCR[0], TIMER_A0->R will reset from CCR[0] to 0
 *
 * @param uint8_t duty_cycle: 0-100, percentage of PWM period output will be HIGH
 */
void start_pwm(uint8_t duty_cycle) {
    TIMER_A0->CCR[0] = CALC_PERIOD(PWM_FREQUENCY);  // calculate and set the value of the period
    TIMER_A0->CCR[1] = (duty_cycle * CALC_PERIOD(PWM_FREQUENCY)) / 100;  // set length according to duty cycle
    TIMER_A0->CTL |= TIMER_A_CTL_MC__UP;    // up mode - counts to TAxCCR0, starts timer
}

/* clear all Mode Control bits in TAxCTL register to put into stop mode */
void stop_pwm(void) {
    // use the CTL reg's MC mask to clear all bits in the portion of the register
    TIMER_A0->CTL &= ~(TIMER_A_CTL_MC_MASK);
}

void configA0_Timer(void){
    __enable_irq();// enable global interrupts
    TIMER_A0->R = 0x00;                         // reset the counter
    TIMER_A0->CTL |= TIMER_A_CTL_CLR; //clear default values
    TIMER_A0->CTL |= (TIMER_A_CTL_SSEL__SMCLK);  // SMCLK- 3 MHz
    TIMER_A0->CTL |= TIMER_A_CTL_ID__1; //divide

    TIMER_A0->CTL |= TIMER_A_CTL_IE; //enable interrupt for timer
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_CCIE; // Capture/compare interrupt enable
    TIMER_A0->CCTL[1] |= TIMER_A_CCTLN_OUTMOD_7;  // select Reset/set Output Mode
    /* Note: Timer is in Compare Mode by default, so we don't need to set it */

    TIMER_A0->CTL |= TIMER_A_CTL_MC_1; // set timer to 'up' mode w/ bitmask
}
////this is the simple irq handler that toggles the pin every 50ms (NOT NEEDED)
//void TA0_0_IRQHandler(void){ // name goes inside vector table
//    TIMER_A0->CTL &= ~(TIMER_A_CTL_IE);     //turn off interrupts --don't have multiple interrupts
//    //check flag(s)
//    if(TIMER_A0->CCTL[0] & TIMER_A_CCTLN_CCIFG){ //if TIMER_A_CCTLN_CCIFG means on clock flag check
//        if(P6->OUT) //if value should write high
//            P2->OUT |= P2->OUT; //toggle on pwm
//            else
//            P2->OUT &= ~(P2->OUT);    //toggle off pwm
//    }
//    //toggle pin every 50ms
//    //reset flag
//    TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG); //reset flag
//    TIMER_A0->CTL |= TIMER_A_CTL_IE; //enable interrupt for timer
//
//}
//this is the handler for UART
//void TA1_0_IRQHandler(void){ // name goes inside vector table
//    TIMER_A1->CTL &= ~(TIMER_A_CTL_IE);     //turn off interrupts --don't have multiple interrupts
//    //check flag(s)
//    if(TIMER_A1->CCTL[0] & //function flag check
//            TIMER_A_CCTLN_CCIFG){ //if TIMER_A_CCTLN_CCIFG (timer A flag)
//        //load string into the buffer
//    }
//    //toggle pin every 50ms
//    //reset flag
//    TIMER_A0->CCTL[0] &= ~(TIMER_A_CCTLN_CCIFG); //reset flag
//    TIMER_A0->CTL |= TIMER_A_CTL_IE; //enable interrupt for timer
//
//}

