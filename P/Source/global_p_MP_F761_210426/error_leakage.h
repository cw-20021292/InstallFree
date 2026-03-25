/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _ERR_LEAKAGE_H_
#define _ERR_LEAKAGE_H_


//
extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0    //E01
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1    //E13
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2    //E10

extern bit bit_pump_output;
//extern U8 gu8_Flow_1sec;
extern MODEL_SELECT F_Model_Select;

#define LEAKAGE_ERROR_DETECT_TIME        30
#define LEAKAGE_ERROR_CLEAR_TIME         30


#define BLOCKED_FLOW_HZ                  5
#define FLOW_CHECK_DELAY_TIME            1200



#endif
