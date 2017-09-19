#include "includefiles.h"


//------------------------------------------------------------------------------
//  void SPISetup(void)
//  Configures the assigned interface to function as a SPI port and
//  initializes it.
//------------------------------------------------------------------------------
//  void SPIWriteReg(char addr, char value)
//  Writes "value" to a single configuration register at address "addr".
//------------------------------------------------------------------------------
//  void SPIWriteBurstReg(char addr, char *buffer, char count)
//  Writes values to multiple configuration registers, the first register being
//  at address "addr".  First data byte is at "buffer", and both addr and
//  buffer are incremented sequentially (within the CCxxxx and MSP430,
//  respectively) until "count" writes have been performed.
//------------------------------------------------------------------------------
//  char SPIReadReg(char addr)
//  Reads a single configuration register at address "addr" and returns the
//  value read.
//------------------------------------------------------------------------------
//  void SPIReadBurstReg(char addr, char *buffer, char count)
//  Reads multiple configuration registers, the first register being at address
//  "addr".  Values read are deposited sequentially starting at address
//  "buffer", until "count" registers have been read.
//------------------------------------------------------------------------------
//  char SPIReadStatus(char addr)
//  Special read function for reading status registers.  Reads status register
//  at register "addr" and returns the value read.
//------------------------------------------------------------------------------
//  char SPIReadStatusByte()
//  Special read function for reading status byte.
//------------------------------------------------------------------------------
//  void SPIStrobe(char strobe)
//  Special write function for writing to command strobe registers.  Writes
//  to the strobe at address "addr".
//------------------------------------------------------------------------------

// Delay function. # of CPU cycles delayed is similar to "cycles". Specifically,
// it's ((cycles-15) % 6) + 15.  Not exact, but gives a sense of the real-time
// delay.  Also, if MCLK ~1MHz, "cycles" is similar to # of useconds delayed.
void Wait(unsigned int cycles)
{
  while(cycles>15)                          // 15 cycles consumed by overhead
    cycles = cycles - 6;                    // 6 cycles consumed each iteration
}

void SPISetup(void)
{
  SPI_UB0_SEL |= SPI_UB0_SIMO| SPI_UB0_SOMI| SPI_UB0_UCLK;
  SPI_UB0_SEL2 |= SPI_UB0_SIMO| SPI_UB0_SOMI| SPI_UB0_UCLK;
                                            // SPI option select
  SPI_UB0_DIR |= SPI_UB0_SIMO | SPI_UB0_UCLK;
  CSn_OUT |= CSn_PIN;
  CSn_DIR |= CSn_PIN;         // /CS disable

  UCB0CTL1 |= UCSWRST;                      // **Disable USCI state machine**
  UCB0CTL0 |= UCMODE_0+UCMST+UCCKPH+UCMSB+UCSYNC;    // 3-pin, 8-bit SPI master
  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
  UCB0BR0 = 1 && 0xff;				//0x02;              // UCLK/2
  UCB0BR1 = 1 >> 8;
                                              // SPI TXD out direction
  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
}

void SPIWriteReg(char addr, char value)
{
   CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = addr;                         // Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = value;                        // Send data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_OUT |= CSn_PIN;         // /CS disable
}

void SPIWriteBurstReg(char addr, char *buffer, char count)
{
  unsigned int i;

  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = addr | CC110L_WRITE_BURST; // Send address
  for (i = 0; i < count; i++)
  {
    while (!(IFG2&UCB0TXIFG));              // Wait for TXBUF ready
    UCB0TXBUF = buffer[i];                  // Send data
  }
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_OUT |= CSn_PIN;         // /CS disable
}

char SPIReadReg(char addr)
{
  char x;

  CSn_OUT &= ~CSn_PIN;               // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | CC110L_READ_SINGLE);// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 1;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  x = UCB0RXBUF;                            // Read data
  CSn_OUT |= CSn_PIN;         // /CS disable
  return x;
 
}

void SPIReadBurstReg(char addr, char *buffer, char count)
{
  char i;
  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | CC110L_READ_BURST);// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  for (i = 0; i < count; i++)
  {
    UCB0TXBUF = 1;                          //Initiate next data RX, meanwhile..
	while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
    buffer[i] = UCB0RXBUF;                  // Store data from last data RX
  }
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_OUT |= CSn_PIN;         // /CS disable
}

char SPIReadStatus(char addr)
{
  char status;
  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = (addr | CC110L_READ_BURST);// Send address
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 0X01;                            // Dummy write so we can read data
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  status = UCB0RXBUF;                       // Read data
  CSn_OUT |= CSn_PIN;         // /CS disable
  return status;
}


char SPIReadStatusByte()
{
  char status;

  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = 0x01;                         // Send dummy var
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  status = UCB0RXBUF;                       // Read data
  CSn_OUT |= CSn_PIN;         // /CS disable
  return status;
}

void SPIStrobe(char strobe)
{
  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while((GDO2_IN & GDO2_PIN));       // Wait for chip ready 
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = strobe;                       // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_OUT |= CSn_PIN;         // /CS disable
}

void PowerupResetCC110L(void)
{
  CSn_OUT |= CSn_PIN;
  Wait(60);
  CSn_OUT &= ~CSn_PIN;
  Wait(60);
  CSn_OUT |= CSn_PIN;
  Wait(60);
  CSn_OUT &= ~CSn_PIN;        // /CS enable
  while (!(IFG2&UCB0TXIFG));                // Wait for TXBUF ready
  UCB0TXBUF = CC110L_SRES;               // Send strobe
  // Strobe addr is now being TX'ed
  while (UCB0STAT & UCBUSY);                // Wait for TX to complete
  CSn_OUT |= CSn_PIN;         // /CS disable
}
