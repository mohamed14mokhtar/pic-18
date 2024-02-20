# pic-18
microcontroller pic18f4620 drivers
this drive contains 
#for MKAL_layer
gpio
interrupt
timer0
timer1
timer2
timer3
ADC (analog to digital converter)
ccp1 and ccp2 (capture - compare - PWM)
USART (unit synchronous asynchronous reciever transmitter)
EEPROM 

#for ECU_layer
led 
button
7_segment
dc_motor
relay
lcd
matrix keypad

if you use any of this driver ,you must take file "mkal_std_types.h" because it contain some of Abbreviations use at the project .
Std_ReturnType >> typedef char use for debug .


