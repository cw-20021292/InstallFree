/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _PUMP_CONTROL_H_
#define _PUMP_CONTROL_H_


//



extern TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0    //E01
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1    //E13
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2    //E10



extern bit F_WaterOut;
extern bit bit_feed_output;
extern bit F_Flow_Block_State;
extern bit F_Err_OVF_Check;


/*..hui [20-11-26오후 7:12:31] 피드 열리고 1초 후 펌프 가동..*/
#define PUMP_DELAY_TIME         10

/*#define PUMP_ON_40MIN           24000*/

/*..hui [21-4-1오전 11:36:43] 저소음 펌프로 변경됨에 따라 ON 시간 2시간으로 수정..*/
#define PUMP_ON_120MIN          72000

/*#define PUMP_ON_150MIN          90000*/
#define PUMP_ON_160MIN          96000


#define PUMP_OFF_20MIN          12000
#define PUMP_OFF_120MIN         72000

//#define PUMP_MAX_PWM            13600//28800 //0x3E80 * 2  //85%
#define PUMP_MAX_PWM            14400
#define PUMP_80_PERCENT_PWM     12800


#endif
