/*
Written by Eytan Mizrahi
*/
#include <ADC.h>
#include "msp.h"

volatile uint16_t _channel[32];
volatile uint16_t i = 0;

void ADC_start(){     //Starts the ADC Conversion
  ADC14->CTL0 |= ADC14_CTL0_ENC | ADC14_CTL0_SC;    //ADC14 Enables and Starts the conversion
}

void ADC_Initial() {
  while(REF_A->CTL0 & REF_A_CTL0_GENBUSY);          //Waits if reference generator is busy
  REF_A->CTL0 |= REF_A_CTL0_VSEL_0 | REF_A_CTL0_ON; //Enables the internal 1.2V reference
  ADC14->CTL1 |= ADC14_CTL1_RES__14BIT;             //14-bit resolution
  ADC14->CTL0 |= ADC14_CTL0_ENC;                    //Enables the conversions

  ADC14->CTL0 |= ADC14_CTL0_SHT0_2       //16 clock cycles as sample time
              | ADC14_CTL0_MSC           //ADC14 samples and conversions
              | ADC14_CTL0_SHP           //ADC14 Pulse Mode is selected
              | ADC14_CTL0_CONSEQ_3      //Repeats the sequence of channels
              | ADC14_CTL0_SSEL__MCLK    //Calls the ADC14 clock source MCLK
              | ADC14_CTL0_ON;           //Turning on the ADC14 module

  while(!(REF_A->CTL0 & REF_A_CTL0_GENRDY));  //Waiting for the reference generator to settle
  NVIC_EnableIRQ(ADC14_IRQn);   //Enables ADC interrupts in the NVIC Module
}

void ADC14_IRQHandler(void) {   //ADC14 interrupt service routine
   _channel[i] = ADC14->MEM[0]; //Saves and clears flag
  }
