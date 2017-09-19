
#include "includefiles.h"
char rxBuffer[CC110L_BUFFER_LENGTH];
int main( void )
{ 
  unsigned int rand;
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  Init_Setup();
  SPIStrobe(CC110L_SRX);
  __delay_cycles(200000);
 LPM0;
}

#pragma vector=PORT1_VECTOR
__interrupt void port1isr (void )
{
  char length = CC110L_BUFFER_LENGTH;
  if(GDO0_IFG & GDO0_PIN)
  {
    if(RFReceivePacket(rxBuffer, &length))
      {
      rxBuffer[0]=0;
      write_char(rxBuffer[1]);
      //sendbyte(rxBuffer[1]);
      rxBuffer[1]=0;
      }
  }
GDO0_IFG &= ~ GDO0_PIN;
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void rxisr (void)
{
  char a;
while(!(IFG2&UCA0TXIFG));
a=UCA0RXBUF;
sendbyte(a);
write_char('-');
}
