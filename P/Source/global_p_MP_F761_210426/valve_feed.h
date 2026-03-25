/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _VALVE_FEED_H_
#define _VALVE_FEED_H_

//
extern U8 pump_retry_proc( void );


extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2


extern PUMP_RETRY_STEP gu8_pump_retry_step;


extern bit bit_overflow_level;
extern U8 gu8_Room_Water_Level;
extern bit F_Err_OVF_Check;
extern MODEL_SELECT F_Model_Select;


#define ROOM_FILLING_DELAY_TIME        1800
#define FEED_OFF_DELAY_TIME            10






#endif
