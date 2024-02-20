/* 
 * File:   mkal_std_types.h
 * Author: mokhtar
 *
 * Created on October 15, 2023, 7:00 AM
 */

#ifndef MKAL_STD_TYPES_H
#define	MKAL_STD_TYPES_H
/*section : includes */
#include"compiler.h"
#include"std_library.h"
/*section : data type declarations  */
typedef unsigned char        boolean;
typedef unsigned char        uint8;
typedef unsigned short       uint16;
typedef unsigned long        uint32;
typedef signed char          sint8;
typedef signed short         sint16;
typedef signed long          sint32;
typedef float                float32;
 
typedef unsigned char Std_ReturnType;

/*section : macro declarations  */
#define STD_HIGH     0x00
#define STD_LOW      0x01

#define STD_ON       0x01
#define STD_OFF      0x00

#define STD_ACTIVE   0x01
#define STD_IDEL     0x00

#define E_OK       (Std_ReturnType)0x01
#define E_not_ok   (Std_ReturnType)0x00

#define CONFIG_ENABLE      0X01
#define CONFIG_DESABLE     0X00

/*section : macro declaration functions  */

/*section : functions declarations  */

#endif	/* MKAL_STD_TYPES_H */

