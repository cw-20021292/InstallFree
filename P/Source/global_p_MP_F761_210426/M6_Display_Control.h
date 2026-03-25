/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _DISPLAY_CONTROL_H_
#define _DISPLAY_CONTROL_H_


extern void led_output(void);


extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0    //E01
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1    //E13
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2    //E10


#define PROC_VERSION               0
#define PROC_ERROR                 1
#define PROC_NORMAL                2

//#define PROC_EXTRACT               3
//#define PROC_SETTING               4
//#define PROC_CODY_INSPECT          5
//#define PROC_DEVELOPER             6
//#define PROC_POPUP                 7
//#define PROC_DEBUG                 8


#define PROC_START                 0
#define PROC_1                     1
#define PROC_2                     2
#define PROC_END                   3



extern bit F_FW_Version_Display_State;
extern bit F_WaterOut;
extern U8 gu8Cup_level;
extern U8 u8Extract_Continue;
extern U8 gu8_Error_Code;


#endif
