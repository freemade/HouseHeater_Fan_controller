#include <stdio.h>
#include <stdint.h>         //
#include <stdbool.h>        //
#include "sysctl.h" //
#include "hw_ints.h"
#include "hw_memmap.h"
#include "hw_types.h"
#include "rom.h"
#include "debug.h"
#include "fpu.h"
#include "gpio.h"
#include "interrupt.h"
#include "pin_map.h"
#include "rom_map.h"
#include "sysctl.h" //
#include "systick.h"    //
#include "uart.h"       //
#include "timer.h"
#include "uartstdio.h"  //
#include "ustdlib.h"
#include "string.h"
//#include "adc.h"
#include "ssi.h"
//#include "can.h"
//#include "hibernate.h"
//#include "qei.h"
#include "ustdlib.h"    //Micro Standard Library Module
//#include "lcd.h"
//#include "stdlib.h"
//#include "main.h"
//#include "time.h"
#include "pinout.h"
//#include "buttons.h"
#include "MAX31855.h"
#include "main.h"
#include "S900_Inverter.h"

bool g_tick_1s = false;
bool g_start_the_motor = false;
uint8_t g_rx_message[100];

float TC_Temperature;

struct T_SOLARFOKUS_SLAVE_MSG sf_slave_msg;
struct T_SOLARFOKUS_MASTER_MSG sf_master_msg;

void SysTickIntHandler(void)    // led blinking
{
    static uint8_t ms_tick_counter;
    static bool start_button_down;

    if (GPIOPinRead(GPIO_PORTF_BASE, GPIO_PIN_4) == 0)
    {
        start_button_down = true;
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //led on
    }
    else if(start_button_down == true)
    {
        start_button_down = false;
        g_start_the_motor = true;
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_4);
    }

    ++ms_tick_counter;
    if(ms_tick_counter == 100)
    {
        ms_tick_counter = 0;
//        g_tick_1s = true; // TODO: enable later..

//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
//      SysCtlDelay(MAP_SysCtlClockGet() / (10000 * 3));    // Delay for 0,1 millisecond.  Each SysCtlDelay is about 3 clocks.
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//      UARTprintf("RTC_counter %d\n\r",HibernateRTCGet());
    }
    // Update the Systick interrupt counter.
//    g_ui32Counter++;
//    ++systickcounter;
    // Turn off the LED
}

void UART0IntHandler(void) // debug UART
{
    uint32_t ui32Status;
    uint32_t ui32_rx_char;
    uint32_t i;
    uint8_t tx_buffer[80];

    static uint8_t rx_char[100];
    static uint8_t char_cnt = 0; // count the amount of chars of one message
    static uint8_t message_state = 0;

    // Get the interrrupt status.
    ui32Status = MAP_UARTIntStatus (UART0_BASE, true);
    // Clear the asserted interrupts.
    MAP_UARTIntClear (UART0_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
        while (MAP_UARTCharsAvail (UART0_BASE))// Loop while there are characters in the receive FIFO.
        {
            rx_char[char_cnt] = (uint8_t)MAP_UARTCharGetNonBlocking (UART0_BASE);// Read the next character from the UART and write it back to the UART.

            switch (message_state)
            {
            case 0:
                if ( rx_char[0] == 0x02)   // start of message -> go to next state
                {
                    message_state = 1;
                    ++char_cnt;
                }
                break;
            case 1:
                if ( rx_char[1] == 0x02)   // start of message -> go to next state
                {
                    message_state = 2;
                    ++char_cnt;
                }
                else
                {
                    message_state = 0;
                    char_cnt = 0;
                }
                break;
            case 2:
                if ( rx_char[2] == 0x3A)   // message lenght start with address to end -> go to next state
                {
                    message_state = 3;
                    ++char_cnt;
                }
                else
                {
                    message_state = 0;
                    char_cnt = 0;
                }
                break;
            case 3:
                ++char_cnt;
                if (char_cnt == 0x3A -3)   // check if length is 3A-3 (02 02 3A) ->message finish
                {
                    char_cnt = 0;
                    message_state = 0;
                    strncpy((char*)g_rx_message, (const char*)rx_char, 0x3A);  // copy message into global buffer

                }
                break;
            }
        }// while

//        if ( ui32_rx_char == 'r') // read the buffer
//        {
//            UARTSend((uint8_t *)"s1_vl\ts2_vl\tbu_o\tbu_u\r\n", 23);
//            for (i=0; i<logger_counter; i++)
//            {
//                usprintf((char*)tx_buffer,"%03d\t%03d\t%03d\t%03d\r\n",logger[i].s1_vl, logger[i].s2_vl, logger[i].bu_o, logger[i].bu_u);
//                UARTSend(tx_buffer, ustrlen((const char*)tx_buffer));
//            }
//            logger_counter = 0; // restart logger
//        }
//      MAP_UARTCharPutNonBlocking (UART2_BASE, MAP_UARTCharGetNonBlocking (UART2_BASE));
        // Blink the LED to show a character transfer is occuring.
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
//      SysCtlDelay(MAP_SysCtlClockGet() / (1000 * 3));
        // Turn off the LED
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
//    }
}

void UART1IntHandler(void)// Solarfocus RS485
{
    uint32_t ui32Status;
    static uint8_t rx_char[100];
    static uint8_t char_cnt = 0; // count the amount of chars of one message
    static uint8_t message_state = 0;

    ui32Status = MAP_UARTIntStatus (UART1_BASE, true);// Get the interrupt status.

    MAP_UARTIntClear (UART1_BASE, ui32Status);// Clear the asserted interrupts.

    while (MAP_UARTCharsAvail (UART1_BASE))// Loop while there are characters in the receive FIFO.
    {
        rx_char[char_cnt] = (uint8_t)MAP_UARTCharGetNonBlocking (UART1_BASE);// Read the next character from the UART and write it back to the UART.

        switch (message_state)
        {
        case 0:
            if ( rx_char[0] == 0x02)   // start of message -> go to next state
            {
                message_state = 1;
                ++char_cnt;
            }
            break;
        case 1:
            if ( rx_char[1] == 0x02)   // start of message -> go to next state
            {
                message_state = 2;
                ++char_cnt;
            }
            else
            {
                message_state = 0;
                char_cnt = 0;
            }
            break;
        case 2:
            if ( rx_char[2] == 0x3A)   // message lenght start with address to end -> go to next state
            {
                message_state = 3;
                ++char_cnt;
            }
            else
            {
                message_state = 0;
                char_cnt = 0;
            }
            break;
        case 3:
            ++char_cnt;
            if (char_cnt == 0x3A -3)   // check if length is 3A-3 (02 02 3A) ->message finish
            {
                char_cnt = 0;
                message_state = 0;
                strncpy((char*)g_rx_message, (const char*)rx_char, 0x3A);  // copy message into global buffer

            }
            break;
        }


//            UARTSend((uint8_t *)"s1_vl\ts2_vl\tbu_o\tbu_u\r\n", 23);
//            for (i=0; i<logger_counter; i++)
//            {
//                usprintf((char*)tx_buffer,"%03d\t%03d\t%03d\t%03d\r\n",logger[i].s1_vl, logger[i].s2_vl, logger[i].bu_o, logger[i].bu_u);
//                UARTSend(tx_buffer, ustrlen((const char*)tx_buffer));
//            }
//            logger_counter = 0; // restart logger
    }
//      MAP_UARTCharPutNonBlocking (UART2_BASE, MAP_UARTCharGetNonBlocking (UART2_BASE));
        // Blink the LED to show a character transfer is occuring.
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);
        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
//      SysCtlDelay(MAP_SysCtlClockGet() / (1000 * 3));
        // Turn off the LED
//      GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);
}

void UART2IntHandler(void)
{
    uint32_t ui32Status;
    uint32_t ui32_rx_char;
    uint32_t i;
    uint8_t tx_buffer[80];
    // Get the interrrupt status.
    ui32Status = MAP_UARTIntStatus (UART2_BASE, true);
    // Clear the asserted interrupts.
    MAP_UARTIntClear (UART2_BASE, ui32Status);
    // Loop while there are characters in the receive FIFO.
    while (MAP_UARTCharsAvail (UART2_BASE))
    {
        // Read the next character from the UART and write it back to the UART.
        ui32_rx_char = MAP_UARTCharGetNonBlocking (UART2_BASE);
//        UARTCharPut(UART0_BASE, (char)ui32_rx_char);       //write rx data of UART2 to UART0
//        if ( ui32_rx_char == 'r') // read the buffer
//        {
//            UARTSend((uint8_t *)"s1_vl\ts2_vl\tbu_o\tbu_u\r\n", 23);
//            for (i=0; i<logger_counter; i++)
//            {
//                usprintf((char*)tx_buffer,"%03d\t%03d\t%03d\t%03d\r\n",logger[i].s1_vl, logger[i].s2_vl, logger[i].bu_o, logger[i].bu_u);
//                UARTSend(tx_buffer, ustrlen((const char*)tx_buffer));
//            }
//            logger_counter = 0; // restart logger
//        }
    }
//    UARTCharPut(UART0_BASE, '\n');
//    UARTCharPut(UART0_BASE, '\r');
}


void UARTsend(uint32_t uart_base, const char* pui8Buffer, uint32_t ui32Count)
{
    uint8_t tx_buffer_was_full;
    while (ui32Count--)         // Loop while there are more characters to send.
    {
        while (UARTSpaceAvail(uart_base) == 0)  // look if we have space in the FIFO
        {
            tx_buffer_was_full = true;
        }
        MAP_UARTCharPut (uart_base, *pui8Buffer++); // Write the next character to the UART.
    }
}

void motor(uint8_t on_off)
{
    if (on_off == ON)
    {
        S900_send(UART2_BASE, 1, COMMAND_WRITE, ADDRESS_ON_OFF, 2); // motor on ok
    }
    else if (on_off == OFF)
    {
        S900_send(UART2_BASE, 1, COMMAND_WRITE, ADDRESS_ON_OFF, 0); // motor off ok
    }
}

int main(void)
{
    uint8_t state_machine_state = 0;
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN); // 40 MHz
    PinoutSet();
    MAP_FPUEnable();
// debug uart
    UARTStdioConfig(0, 115200, MAP_SysCtlClockGet());  // g_ui32Base is set in this function and is used in UARTwrite, UARTprint
    MAP_UARTFIFOEnable(INT_UART0);
    while (MAP_UARTCharsAvail (UART0_BASE));        // clear buffer
    MAP_IntEnable (INT_UART0);      // Enable the UART interrupt.
    MAP_UARTIntEnable (UART0_BASE, UART_INT_RX);
// RS485 Solarfocus
    UARTStdioConfig(1, 19200, MAP_SysCtlClockGet());  // g_ui32Base is set in this function and is used in UARTwrite, UARTprint
    MAP_UARTFIFOEnable(INT_UART1);
    while (MAP_UARTCharsAvail (UART1_BASE));        // clear buffer
    MAP_IntEnable (INT_UART1);      // Enable the UART interrupt.
    MAP_UARTIntEnable (UART1_BASE, UART_INT_RX);
// RS485 Sunch FU
    UARTStdioConfig(2, 9600, MAP_SysCtlClockGet());
    MAP_UARTFIFOEnable(INT_UART2);
    MAP_IntEnable (INT_UART2);      // Enable the UART interrupt.
    while (MAP_UARTCharsAvail (UART2_BASE));        // clear buffer
    MAP_UARTIntEnable (UART2_BASE, UART_INT_RX);
    nRE_UART2_LOW;  // enable the receiver

    // Set up the period for the SysTick timer.  The SysTick timer period will be equal to the system clock, resulting in a period of 1 second.
    MAP_SysTickPeriodSet(MAP_SysCtlClockGet() / 100);   // tick=10ms max 16.777,216
    MAP_SysTickIntEnable();     // Enable the SysTick Interrupt.
    MAP_SysTickEnable();        // Enable SysTick.

// config SSI for MAX31855
    MAP_SSIConfigSetExpClk(SSI0_BASE, MAP_SysCtlClockGet(), SSI_FRF_MOTO_MODE_0, SSI_MODE_MASTER, 1000000, 16); // SSI with 1MHz
    MAP_SSIEnable(SSI0_BASE);

    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_4MA, GPIO_PIN_TYPE_STD_WPU);    // enable pull up for button

    UARTprintf("Ofen Lüftersteuerung mit S900 inverter V0.0\n\r");  // UARTprintf prints to the uart which was last initialized
    UARTsend (UART0_BASE, "--------------------\n\r", 22);

//    S900_send(UART2_BASE, 1, COMMAND_WRITE, ADDRESS_MAX_FREQUENCY, 5500); // send a command to the FU S900 ok
//    S900_send(UART2_BASE, 0x01, 0x06, 0x0100, 0x1770); // send a command to the FU S900
    S900_send(UART2_BASE, 1, COMMAND_WRITE, 0x0907, 0); // RS485 response delay to minimum
    SysCtlDelay(400000);                               // wait for the answer is sent
    S900_send(UART2_BASE, 1, COMMAND_WRITE, 0x0200, 4); // set "master frequency input source" = by RS485
    SysCtlDelay(400000);                               // wait for the answer is sent
    S900_send(UART2_BASE, 1, COMMAND_WRITE, 0x0203, 3); // set "operation method" = by RS485 + stop key is working
    SysCtlDelay(400000);                               // wait for the answer is sent
    S900_send(UART2_BASE, 1, COMMAND_WRITE, ADDRESS_FREQUENCY, 70); // send a command to the FU S900 ok
    SysCtlDelay(400000);                               // wait for the answer is sent
    S900_send(UART2_BASE, 1, COMMAND_WRITE, ADDRESS_ON_OFF, 2); // motor on ok

    while (1)
    {
        char tx_buffer[80];
        if (g_rx_message[0] == 0x02)    // we got a message from solarfocus
        {
            // TODO: do something with the new information
            if (g_rx_message[3] == 0x10)    // we got a slave message
            {
                sf_slave_msg.start_byte =               g_rx_message[0];
                sf_slave_msg.lenght =                   g_rx_message[2];
                sf_slave_msg.address =                  g_rx_message[3];

                sf_slave_msg.exhaust_gas_tmp.byte.H =   g_rx_message[12];   // not checked
                sf_slave_msg.exhaust_gas_tmp.byte.L =   g_rx_message[13];

                sf_slave_msg.kessel_tmp.byte.H =        g_rx_message[14];   // not checked
                sf_slave_msg.kessel_tmp.byte.L =        g_rx_message[15];
            }
            else if (g_rx_message[2] == 0x11) // we got a master message
            {
                sf_master_msg.start_byte =   g_rx_message[0];
                sf_master_msg.lenght =       g_rx_message[1];
                sf_master_msg.address =      g_rx_message[2];
                sf_master_msg.fan =         g_rx_message[12];   // 94=on 0=0ff
            }
            g_rx_message[0] = 0;    // clear message information
        }

        if( g_tick_1s == true)
        {
            g_tick_1s = false;
            TC_Temperature = max31855_read_temp(SSI0_BASE); // read the TC temperature every sec.
            usprintf((char*)tx_buffer,"%03d.%02d°C\r\n",(uint16_t)TC_Temperature, ((uint16_t)(TC_Temperature*100)) % 100);
            UARTsend( UART0_BASE, tx_buffer, ustrlen(tx_buffer));

            switch (state_machine_state)
            {
            case STOP:
                if (g_start_the_motor == true)
                {
                    g_start_the_motor = false;
                    motor(ON);
                    state_machine_state = HEATUP;
                }
                break;

            case HEATUP:
                if (TC_Temperature > 180)
                {
                    state_machine_state = BURN;
                }
                break;
            case BURN:
                if (TC_Temperature < 110)
                {
                    state_machine_state = STOP;
                    motor(OFF);
                }
                break;
            }
        }
    }
}

