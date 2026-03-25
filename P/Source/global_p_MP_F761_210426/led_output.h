/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _LED_OUTPUT_H_
#define _LED_OUTPUT_H_



//
extern TYPE_BYTE          U8FrontLEDB;
#define            u8FrontLED                             U8FrontLEDB.byte
#define            Bit0_Half_Cup_Led_White                U8FrontLEDB.Bit.b0
#define            Bit1_One_Cup_Led_White                 U8FrontLEDB.Bit.b1
#define            Bit2_Two_Cup_Led_White                 U8FrontLEDB.Bit.b2
#define            Bit3_Extract_Led_White                 U8FrontLEDB.Bit.b3



#endif

