/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _ERR_WATER_LEVEL_H_
#define _ERR_WATER_LEVEL_H_

//


extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2




extern U8 gu8_Room_Water_Level;
extern bit F_WaterOut;
extern bit bit_overflow_level;










#endif
