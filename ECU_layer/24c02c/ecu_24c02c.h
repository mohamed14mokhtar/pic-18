/* 
 * File:   ecu_24c02c.h
 * Author: mokhtar
 *
 * Created on March 20, 2024, 12:13 AM
 */

#ifndef ECU_24C02C_H
#define	ECU_24C02C_H

#include"../../MKAL_layer/I2C/hal_i2c.h"

void write_byte_24c02c (mssp_i2c_t *mssp_i2c ,uint8 _address,uint8 internal_address,uint8 data,uint8 *ack);
void read_byte_24c02c (mssp_i2c_t *mssp_i2c ,uint8 _address,uint8 *data_ret,uint8 internal_address,uint8 *ack);
#endif	/* ECU_24C02C_H */

