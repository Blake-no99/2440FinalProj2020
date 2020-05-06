/*
 * pwm.h
 *
 *  Created on: May 5 2020
 *      Author: Blake Novak
 */

#ifndef PWM_H_
#define PWM_H_


void configA0_Timer(void);
//void TA0_0_IRQHandler(void); // name goes inside vector table
/*   D E F I N E S  */
#define SYSTEM_CLOCK        3000000             // [Hz] taken from system_msp432p401r.c
#define PWM_FREQUENCY       9600              // [Hz] PWM frequency desired for BAUD with LCD
#define CALC_PERIOD(X)      (SYSTEM_CLOCK / X)  // calculates the number of ticks in a period, X is in ms

#define BUTTON_BITS         (BIT1 | BIT4)       // for clearing and setting
#define MAX_SELECT_POSITION     5
#define MIN_SELECT_POSITION     0

/* Configure TIMER_A0 to produce a PWM waveform
 *
 * - reset the R (timer counter) register
 * - select the SMCLK (3MHz) in the CTL register
 * - select the Reset/Set output mode for the T0.1 timer using CCTL[1]
 */
void config_pwm_timer(void);

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
void start_pwm(uint8_t duty_cycle);

/* clear all Mode Control bits in TAxCTL register to put into stop mode */
void stop_pwm(void);

/* configure P2.4 to output the waveform produced by TAO.1 */
void config_pwm_gpio(void);

#endif /* PWM_H_ */
