/* 
 * File:   hal_ds1307.c
 * Author: mokhtar
 *
 * Created on March 21, 2024, 6:01 PM
 */

#include"hal_ds1307.h"

uint8 return_data_array[6];

void ds1307_read_values(const mssp_i2c_t *i2c_obj, uint8 address_1,uint8 *return_data_array,uint8 *_ack){
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x00,return_data_array++,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x01,return_data_array++,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x02,return_data_array++,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x04,return_data_array++,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x05,return_data_array++,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
        MSSP_I2C_Master_Send_Start(i2c_obj);
        MSSP_I2C_Master_read_data_in_register(i2c_obj,address_1,0x06,return_data_array,_ack);
        MSSP_I2C_Master_Send_Stop(i2c_obj);
}
