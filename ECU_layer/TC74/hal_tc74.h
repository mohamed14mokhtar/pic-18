/* 
 * File:   hal_tc74.h
 * Author: mokhtar
 *
 * Created on March 21, 2024, 5:32 PM
 */

#ifndef HAL_TC74_H
#define	HAL_TC74_H

#include"../../MKAL_layer/I2C/hal_i2c.h"

#define ADDRESS_A3  0x96
#define ADDRESS_A4  0x98
#define ADDRESS_A5  0x9A
#define ADDRESS_A6  0x9C
#define ADDRESS_A7  0X9E //USED THIS FOR ADDRESS ONE AT FUNCTION

#define REDISTER_READ_0  0x00  //USED THIS FOR ADDRESS TWO AT FUNCTION
#define REDISTER_READ_1  0x01

void tc74_read_value(const mssp_i2c_t *i2c_obj, uint8 i2c_data_1, uint8 i2c_data_2,uint8 *ret_data,uint8 *_ack);


#endif	/* HAL_TC74_H */

