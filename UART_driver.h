/*
 * UART.h
 *
 *  Created on: Apr 10, 2020
 *      Author: Blake Novak
 */

#ifndef UART_DRIVER_H_
#define UART_DRIVER_H_

#include <stdint.h>

/*
 * P1.6 --> SDA
 * P1.7 -> SCL
 * EUSCI_B0
 */
//not needed bc using custom PWM signal.
void config_UART(void);

//writes string to LCD
void write_string(const char *value);

//writes a char 1 bit at a time to pwm.
void transmit_char_over_uart(uint8_t value);

//clears LCD for next print
void clear_lcd_screen(void);

void TA0_0_IRQHandler(void); // name goes inside vector table


#endif /* UART_DRIVER_H_ */
