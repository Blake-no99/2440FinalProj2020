# 2440 Final Project 2020
Hazardous Bacteria Sensor Final Project

each file description can be found below:
##adc.c/.h
  This file utilizes the ADC14 to read the gas sensor values.
  
##gpio.c/.h
  This file contains the gpio initialization functions.
  
##main.c
  This file has both the initilization function calls as well as the threshold detection code for informing the user of their wound's state
  
##pwm.c/.h
  This file contains the functions to create our own UART Tx PWM driver. Unfortuantely this was not able to be fully operational.
  
##UART_drive.c/.h
  This file contains the functions to create our own UART Tx PWM driver. Unfortuantely this was not able to be fully operational.
  
##startup_msp432p401r_ccs.c / system_msp432p401r.c
  Redistributible files which are for the MSp432p401r to operate correctly.



full details found at https://www.hackster.io/michael-rosado/detection-of-gases-being-emitted-by-bacteria-bf6635
