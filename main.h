/*
 * main.h
 *
 *  Created on: 10.02.2018
 *      Author: Franz
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "gpio.h"
#include "hw_memmap.h"

#define STOP    0
#define HEATUP  1
#define BURN    2

#define ON      1
#define OFF     0

void SysTickIntHandler(void);
extern void UART0IntHandler(void);
extern void UART2IntHandler(void);
void UARTsend(uint32_t uart_base, const char *pui8Buffer, uint32_t ui32Count);
void motor(uint8_t on_off);

#define nCS1_HIGH    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, GPIO_PIN_3)
#define nCS1_LOW     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_3, 0)
#define nCS2_HIGH    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, GPIO_PIN_6)
#define nCS2_LOW     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_6, 0)
#define nCS3_HIGH    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, GPIO_PIN_7)
#define nCS3_LOW     GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_7, 0)
#define nCS4_HIGH    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, GPIO_PIN_2)
#define nCS4_LOW     GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_2, 0)

#define nRE_UART2_HIGH  GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7)   // not receiver enable
#define nRE_UART2_LOW   GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0)

typedef struct T_SOLARFOKUS_SLAVE_MSG
{
    uint8_t start_byte;     // 1 always 0x02
    uint8_t byte_2;         // 2 if 0x02 msg is from slave; if not 0x02 or 0x00 msg is from master
    uint8_t lenght;         // 3 massage lenght
    uint8_t reciver_id;     // 4 reciver address ID 0x11=Motherboard 13=Solar1 14=solar2 17=Frischwasserz
    uint8_t byte_5;             // 5 same as byte4 of master massage
    uint8_t byte_6;             // 6 always 0x80
    uint8_t byte_7;             // 7 same as byte5 om master massage
    uint8_t byte_8;             // 8
    uint8_t byte_9;             // 9
    uint8_t byte_10;            // 10
    uint8_t byte_11;            // 11
    union {                     //12+13 Abgastemperatur
        uint16_t Word;
        struct
        {
            uint8_t L;
            uint8_t H;
        }byte;
    }exhaust_gas_tmp;
    uint8_t byte_14;        // 14 sensor x30
    uint8_t byte_15;        // 15
    union {                 //16+17 Kesseltemperatur
        uint16_t Word;
        struct
        {
            uint8_t L;
            uint8_t H;
        }byte;
    }kessel_tmp;
    union {                 //18+19 Rücklauftemperatur
        uint16_t Word;
        struct
        {
            uint8_t L;
            uint8_t H;
        }byte;
    }rucklauf_tmp;
    uint8_t byte_20;        // 20 unbekannt
    uint8_t byte_21;        // 21

    uint8_t byte_22;        // 22
    uint8_t byte_23;        // 23

    uint8_t byte_24;        // 24
    uint8_t byte_25;        // 25

    uint8_t byte_26;        // 26
    uint8_t byte_27;        // 27

    uint8_t byte_28;        // 28
    uint8_t byte_29;        // 29

    uint8_t byte_30;        // 30
    uint8_t byte_31;        // 31

    uint8_t byte_32;        // 32
    uint8_t byte_33;        // 33

    uint8_t byte_35;        // 35
    uint8_t byte_36;        // 36

    uint8_t byte_37;        // 37
    uint8_t byte_38;        // 38

    uint8_t byte_39;        // 39
    uint8_t byte_40;        // 40

    uint8_t byte_41;        // 41
    uint8_t byte_42;        // 42

    uint8_t byte_43;        // 43
    uint8_t byte_44;        // 44

    uint8_t byte_45;        // 45
    uint8_t byte_46;        // 46

    uint8_t byte_47;        // 47
    uint8_t byte_48;        // 48

    uint8_t byte_49;        // 49
    uint8_t byte_50;        // 50

    uint8_t byte_51;        // 51
    uint8_t byte_52;        // 52

    uint8_t byte_53;        // 53
    uint8_t byte_54;        // 54

    uint8_t byte_55;        // 55
    uint8_t byte_56;        // 56

    uint8_t byte_57;        // 57
    uint8_t byte_58;        // 58

    uint8_t byte_59;        // 59
    uint8_t byte_60;        // 60

}slave_message;

#endif /* MAIN_H_ */
