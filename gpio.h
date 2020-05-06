/*
 * gpio.h
 *
 *  Created on: May 5, 2020
 *      Author: Blake Novak
 */

#ifndef GPIO_H_
#define GPIO_H_

/* P1.2 -> EN
 * Configure P1.2 to be an output (initialized as LOW) to
 * control the DRV's EN pin */
void config_drv_gpio(void);

/* Toggles the DRV's EN pin */
void toggle_drv_enable_pin(void);

/* Configure UART GPIO */
void config_UART_gpio(void);

/* Configure PWM GPIO */
void config_pwm_gpio(void);

#endif /* GPIO_H_ */
