#include "includefiles.h"
extern char rxbuffer[80];
extern char mspfound;
void setup_uart()
{
  BCSCTL1 = CALBC1_1MHZ;                    // Set DCO
  DCOCTL = CALDCO_1MHZ;
  P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  P1SEL2 = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
  UCA0CTL1 |= UCSSEL_2;                     // SMCLK
  UCA0BR0 = 104;                            // 1MHz 9600
  UCA0BR1 = 0;                              // 1MHz 9600
  UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
  UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
  IE2 |= UCA0RXIE;//+UCA0TXIE;                          // Enable USCI_A0 RX interrupt
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  write_string("$msp",4);
}


void write_char(char a)
{
  while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
  UCA0TXBUF=a;
}

void write_string(char a[],int length)
{
int i;
for(i=0;i<length;i++)
{
write_char(a[i]);
}
}
