/*
 * MAX31855.c
 *
 *  Created on: 16.02.2018
 *      Author: Franz
 */

#include "MAX31855.h"
#include "stdint.h"
#include "stdbool.h"
#include "rom_map.h"
#include "ssi.h"

union MAX31855_REG max31855_reg;

float max31855_read_temp(uint32_t ssi_base)
{
    uint32_t tmp_spi;
    uint32_t tmp;
    nCS_max31855_low;
    SSIDataPut(ssi_base, 0);    // send 32 bit to the SPI
    SSIDataPut(ssi_base, 0);
    while(SSIBusy(ssi_base))    // wait for SPI
    {
        ;
    }
    nCS_max31855_high;
    SSIDataGet(ssi_base, &tmp_spi);
    tmp = tmp_spi << 16;
    SSIDataGet(ssi_base, &tmp_spi);
    tmp |= tmp_spi;
    max31855_reg.all = tmp;
    if (max31855_reg.bit.tc_temp &0x2000 == 1)   // if the sign bit is set
    {
        max31855_reg.bit.tc_temp | 0xE000;      // set all sign bits
    }

    return (float)max31855_reg.bit.tc_temp / 4;
}
