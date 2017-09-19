//This file contains the register addresses of CC110l , access byte details and access definitions


// Configuration Registers
#define CC110L_IOCFG2       0x00        // GDO2 output pin configuration
#define CC110L_IOCFG1       0x01        // GDO1 output pin configuration
#define CC110L_IOCFG0       0x02        // GDO0 output pin configuration
#define CC110L_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CC110L_SYNC1        0x04        // Sync word, high byte
#define CC110L_SYNC0        0x05        // Sync word, low byte
#define CC110L_PKTLEN       0x06        // Packet length
#define CC110L_PKTCTRL1     0x07        // Packet automation control
#define CC110L_PKTCTRL0     0x08        // Packet automation control
#define CC110L_ADDR         0x09        // Device address
#define CC110L_CHANNR       0x0A       
#define CC110L_FSCTRL1      0x0B        // Frequency synthesizer control
#define CC110L_FSCTRL0      0x0C        // Frequency synthesizer control
#define CC110L_FREQ2        0x0D        // Frequency control word, high byte
#define CC110L_FREQ1        0x0E        // Frequency control word, middle byte
#define CC110L_FREQ0        0x0F        // Frequency control word, low byte
#define CC110L_MDMCFG4      0x10        // Modem configuration
#define CC110L_MDMCFG3      0x11        // Modem configuration
#define CC110L_MDMCFG2      0x12        // Modem configuration
#define CC110L_MDMCFG1      0x13        // Modem configuration
#define CC110L_MDMCFG0      0x14        // Modem configuration
#define CC110L_DEVIATN      0x15        // Modem deviation setting
#define CC110L_MCSM2        0x16        // Main Radio Cntrl State Machine config
#define CC110L_MCSM1        0x17        // Main Radio Cntrl State Machine config
#define CC110L_MCSM0        0x18        // Main Radio Cntrl State Machine config
#define CC110L_FOCCFG       0x19        // Frequency Offset Compensation config
#define CC110L_BSCFG        0x1A        // Bit Synchronization configuration
#define CC110L_AGCCTRL2     0x1B        // AGC control
#define CC110L_AGCCTRL1     0x1C        // AGC control
#define CC110L_AGCCTRL0     0x1D        // AGC control
#define CC110L_WOREVT1      0x1E        // 
#define CC110L_WOREVT0      0x1F        // 
#define CC110L_WORCTRL      0x20        // 
#define CC110L_FREND1       0x21        // Front end RX configuration
#define CC110L_FREND0       0x22        // Front end TX configuration
#define CC110L_FSCAL3       0x23        // Frequency synthesizer calibration
#define CC110L_FSCAL2       0x24        // Frequency synthesizer calibration
#define CC110L_FSCAL1       0x25        // Frequency synthesizer calibration
#define CC110L_FSCAL0       0x26        // Frequency synthesizer calibration
#define CC110L_RCCTRL1      0x27        // 
#define CC110L_RCCTRL0      0x28        // 
#define CC110L_FSTEST       0x29        // 
#define CC110L_PSTEST       0x2A        // 
#define CC110L_AGCTEST      0x2B        // 
#define CC110L_TEST2        0x2C        // Various test settings
#define CC110L_TEST1        0x2D        // Various test settings
#define CC110L_TEST0        0x2E        // Various test settings

// Strobe commands
#define CC110L_SRES         0x30        // Reset chip.
#define CC110L_SFSTXON      0x31        // Enable/calibrate freq synthesizer
#define CC110L_SXOFF        0x32        // Turn off crystal oscillator.
#define CC110L_SCAL         0x33        // Calibrate freq synthesizer & disable
#define CC110L_SRX          0x34        // Enable RX.
#define CC110L_STX          0x35        // Enable TX.
#define CC110L_SIDLE        0x37        // 
#define CC110L_RESERVED     0x36        // Exit RX / TX
#define CC110L_RESERVED     0x38        // 
#define CC110L_SPWD         0x39        // Enter pwr down mode when CSn goes hi
#define CC110L_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CC110L_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CC110L_RESERVED     0x3C        // 
#define CC110L_SNOP         0x3D        // No operation.

// Status registers
#define CC110L_PARTNUM      0x30      // Part number
#define CC110L_VERSION      0x31      // Current version number
#define CC110L_FREQEST      0x32      // Frequency offset estimate
#define CC110L_CRC_REG      0x33      // CRC OK
#define CC110L_RSSI         0x34      // Received signal strength indication
#define CC110L_MARCSTATE    0x35      // Control state machine state
#define CC110L_RESERVED     0x36      // 
#define CC110L_RESERVED     0x37      // 
#define CC110L_PKTSTATUS    0x38      // Current GDOx status and packet status
#define CC110L_RESERVED     0x39      // 
#define CC110L_TXBYTES      0x3A      // Underflow and # of bytes in TXFIFO
#define CC110L_RXBYTES      0x3B      // Overflow and # of bytes in RXFIFO
#define CC110L_NUM_RXBYTES  0x7F      // Mask "# of bytes" field in _RXBYTES

// Other memory locations
#define CC110L_PATABLE      0x3E
#define CC110L_TXFIFO       0x3F
#define CC110L_RXFIFO       0x3F

//Masks for appended status bytes
#define CC110L_LQI_RX       0x01        // Position of LQI byte
#define CC110L_CRC_OK       0x80        // Mask "CRC_OK" bit within LQI byte

// Definitions to support burst/single access:
#define CC110L_WRITE_BURST  0x40
#define CC110L_READ_SINGLE  0x80
#define CC110L_READ_BURST   0xC0 
