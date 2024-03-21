/* 
 * File:   hal_ds1307.h
 * Author: mokhtar
 *
 * Created on March 21, 2024, 6:01 PM
 */

#ifndef HAL_DS1307_H
#define	HAL_DS1307_H

#include"../../MKAL_layer/I2C/hal_i2c.h"

#define DS13_ADDRESS 0xD0

typedef struct {
    uint8 seconds;
    uint8 minutes;
    uint8 hours;
    uint8 date;
    uint8 month;
    uint8 year;
}return_data_t;

void ds1307_read_values(const mssp_i2c_t *i2c_obj, uint8 address_1,uint8 *return_data_array,uint8 *_ack);

#endif	/* HAL_DS1307_H */

