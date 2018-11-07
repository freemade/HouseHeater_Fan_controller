#ifndef S900_INVERTER_
#define S900_INVERTER_

#define COMMAND_READ        3
#define COMMAND_WRITE       6

#define ADDRESS_ON_OFF          0x2000
#define ADDRESS_FREQUENCY       0x2001
#define ADDRESS_MAX_FREQUENCY   0x0100  // 0.01Hz

// bits for COMMAND_ONOFF
#define COMMAND_BIT_BLAND           0
#define COMMAND_BIT_STOP_REFERENCE  1
#define COMMAND_BIT_RUN_REFERENCE   2
#define COMMAND_BIT_JOG_RUN         3
#define COMMAND_BIT_FWD             4
#define COMMAND_BIT_REV             8

void S900_send(uint32_t uart_base, uint8_t address, uint8_t command, uint16_t data_address, uint16_t data);


#endif
