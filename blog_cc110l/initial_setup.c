/* This file conatins functions to initialise ports , peripherals and cc110l */
#include "includefiles.h"
void Init_Setup()
{
  setup_uart();
  SPISetup();
  PowerupResetCC110L();
  writeRFSettings();
  setup_io();
  _EINT();
}


void setup_io()
{
  int i=0;
  
  SWI_IES   =       SWI_1 + SWI_2;   //Int on falling edge
  SWI_IFG  &=   ~ ( SWI_1 + SWI_2 );     //Clr flags
  SWI_IE    =       SWI_1 + SWI_2;          //Activate enables
  
  LED_OUT &= ~(LED_1 + LED_2 +LED_3 + LED_4); //Outputs
  LED_DIR =    LED_1 + LED_2 +LED_3 +LED_4; //Outputs
 
  for(i=0;i<9000;i++);
  LED_OUT = LED_1;
  for(i=0;i<9000;i++);
  LED_OUT = LED_2;
  for(i=0;i<9000;i++);
  LED_OUT = LED_3;
  for(i=0;i<9000;i++);
  LED_OUT = LED_4;
  for(i=0;i<9000;i++);
  LED_OUT=0X00;
 
  GDO0_IES  |=   GDO0_PIN;       // Int on falling edge (end of pkt)
  GDO0_IFG  &=  ~GDO0_PIN;      // Clear flag
  GDO0_IE   |=   GDO0_PIN;        // Enable int on end of packet
  
  GDO2_DIR &= ~GDO2_PIN;
  
}
