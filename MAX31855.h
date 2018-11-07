/*
 * MAX31855.h
 *
 *  Created on: 16.02.2018
 *      Author: Franz
 */

#ifndef MAX31855_H_
#define MAX31855_H_

#include "stdint.h"
#include "stdbool.h"
#include "main.h"

#define nCS_max31855_high   nCS1_HIGH;
#define nCS_max31855_low    nCS1_LOW;

struct MAX31855_STR
{
    bool        oc_fault    :1;
    bool        scg_fault   :1;
    bool        scv_fault   :1;
    bool                    :1;
    uint16_t    cj_temp     :12;    //1 lsb = 0,0625°C
    bool        fault       :1;
    bool                    :1;
    int16_t    tc_temp     :14;     //1 lsb = 0,25°C
};

union MAX31855_REG
{
    uint32_t    all;
    struct      MAX31855_STR bit;
};


float max31855_read_temp(uint32_t ssibase);

#endif /* MAX31855_H_ */
