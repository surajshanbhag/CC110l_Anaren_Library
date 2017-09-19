void Wait(unsigned int);
void SPISetup(void);
void SPIWriteReg(char, char);
void SPIWriteBurstReg(char, char*, char);
char SPIReadReg(char);
void SPIReadBurstReg(char, char *, char);
void PowerupResetCC110L(void);
char SPIReadStatus(char);
char SPIReadStatusByte(void);
void SPIStrobe(char);

char SPIStatusByte();
