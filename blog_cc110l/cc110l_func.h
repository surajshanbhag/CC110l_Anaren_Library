char RFReceivePacket(char *rxBuffer, char *length);
void RFSendPacket(char *txBuffer, char size);
void writeRFSettings(void);
void sendbyte(char);
#define CC110L_BUFFER_LENGTH 64