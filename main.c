

/**
 * main.c
 */

#include <UART_driver.h>
#include "msp.h"
#include "drv2605l.h"
#include "pwm.h"
#include "gpio.h"



/*
Main.c Written by Blake Novak
this main tests the UART screen to display hello world
*/

void main_UART_TEST(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    TIMER_A0->CTL &= ~(TIMER_A_CTL_MC_MASK); //halt timer
      config_UART();
    config_UART_gpio();
 //   NVIC_EnableIRQ(TA0_0_IRQn); //found in table
 //   config_pwm_gpio();
 //   configA0_Timer(); //configure timer & start

    start_pwm(50);
    // config_drv2605l();
    clear_lcd_screen();
    write_string("hello world");
 //   while(1);

}




/*
//This main is writen by written by Michael Rosado
 The UART and ADC config code is to be inserted in the main below
 to check threshold of sensed values, then print if the readings indicate a bacterial infection.
 
*/


//this code will take the serial data given by the sensors and determine the calibration levels of gas
//once calibrated, it will compare the calibration level to the level once the wound is introduced
//based on the difference, it will tell you whether or not bacteria is present

#include "msp.h"
//dummy variables due to other code not working
int button
int threshold1
int threshold2
int threshold3
int data1 //data1-3 are the binary values read from the sensors through the adc driver
int data2
int data3
int calvalue1
int calvalue2
int calvalue3

void main(void)
{
	main_UART_TEST();
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;        // stop watchdog timer
    printf("WAIT 30 MINUTES THEN PRESS BUTTON");
    for(!button) { //Calibration loop that stores the final value into a calibration value 
        calvalue1 = data1; 
        calvalue2 = data2;
        calvalue3 = data3;
        delay(1000)
    }
    threshold1 = calvalue1 * 1.5; //threshold will be the calibration value multiplied by a value
    threshold2 = calvalue2 * 1.5;
    threshold3 = calvalue3 * 1.5;
    printf("INSERT WOUND INTO ENCLOSURE AND WAIT 5 MINUTES THEN PRESS BUTTON");
    for(!button) { //Loop will store the data value from when the wound in introduced
        calvalue1 = data1; 
        calvalue2 = data2;
        calvalue3 = data3;
        delay(1000)
    }
    if(calvalue1 >= threshold1 | |  calvalue2 >= threshold2 || calvalue3 >= threshold3) //If any of the new values are higher than the threshold, bacteria is detected
        printf("BACTERIA DETECTED");
    else
        printf("NO BACTERIA DETECTED")
)


}


