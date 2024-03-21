/* 
 * File:   hal_tc74.c
 * Author: mokhtar
 *
 * Created on March 21, 2024, 5:32 PM
 */

#include"hal_tc74.h"


void tc74_read_value(const mssp_i2c_t *i2c_obj, uint8 i2c_data_1, uint8 i2c_data_2,uint8 *ret_data,uint8 *_ack){
    
    MSSP_I2C_Master_Send_Start(i2c_obj);
    MSSP_I2C_Master_read_data_in_register(i2c_obj,i2c_data_1,i2c_data_2,ret_data,_ack);
    MSSP_I2C_Master_Send_Stop(i2c_obj);
}