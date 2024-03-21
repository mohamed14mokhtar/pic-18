/* 
 * File:   ecu_24c02c.h
 * Author: mokhtar
 *
 * Created on March 20, 2024, 12:13 AM
 */

#include"ecu_24c02c.h"

void write_byte_24c02c (mssp_i2c_t *mssp_i2c ,uint8 _address,uint8 internal_address,uint8 data,uint8 *ack){
    MSSP_I2C_Master_Send_Start(&mssp_i2c);
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c,_address,ack);
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c,internal_address,ack);
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c,data,ack);
    MSSP_I2C_Master_Send_Stop(&mssp_i2c);
}

void read_byte_24c02c (mssp_i2c_t *mssp_i2c ,uint8 _address,uint8 *data_ret,uint8 internal_address,uint8 *ack){
    uint8 l_counter =0;
    while(internal_address >= l_counter){
    l_counter++;
    MSSP_I2C_Master_Send_Start(&mssp_i2c);
    MSSP_I2C_Master_Write_Blocking(&mssp_i2c,_address,ack);
    MSSP_I2C_Master_Read_Blocking(&mssp_i2c,I2C_MASTER_SEND_NACK,data_ret);
    MSSP_I2C_Master_Send_Stop(&mssp_i2c);
    }
}
