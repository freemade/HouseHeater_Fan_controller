#include <stdint.h>         //
#include <stdbool.h>        //
#include "sysctl.h" //
#include "stdint.h"
#include "stdbool.h"
#include "main.h"
#include "stdlib.h"
#include "ustdlib.h"
#include "ctype.h"
#include "uart.h"

//#include "gpio.h"

void S900_send(uint32_t uart_base, uint8_t address, uint8_t command, uint16_t data_address, uint16_t data)
{
    char tx_buffer[60];
//    char tmp_buffer[5];
    uint8_t i;
    uint16_t crc = 0;

    tx_buffer[0] = ':';     // start caracter
    usprintf(&tx_buffer[1], "%02X",address);
    usprintf(&tx_buffer[3], "%02X",command);
    usprintf(&tx_buffer[5], "%04X",data_address);
    usprintf(&tx_buffer[9], "%04X",data);

    for (i=1; i<13; i++)
    {
        tx_buffer[i] = toupper(tx_buffer[i]);
    }

    crc += address;
    crc += command;
    crc += data_address & 0x00FF;       // only low byte
    crc += (data_address >> 8) & 0xFF;  // only high byte
    crc += data & 0x00FF;               // only low byte
    crc += (data >> 8) & 0xFF;          // only high byte

    crc &= 0x00FF;              // clear msb 8 bit
    crc = crc * -1;
    usprintf(&tx_buffer[13], "%02X",(uint8_t)crc);  // convert to ASCII
    tx_buffer[13] = toupper(tx_buffer[13]);
    tx_buffer[14] = toupper(tx_buffer[14]);

    tx_buffer[15] = '\r';
    tx_buffer[16] = '\n';
    tx_buffer[17] = 0;          // add the 0 caracter

    // send the command...
    nRE_UART2_HIGH; // enable the transmiter
    UARTsend(uart_base, tx_buffer, ustrlen(tx_buffer));
    while(UARTBusy(uart_base))
    {
        ;
    }
    nRE_UART2_LOW;  // disable
}
