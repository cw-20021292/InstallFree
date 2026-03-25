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
typedef enum
{
    STEP0_STANDBY,
    STEP1_120MIN_ON,
    STEP2_20MIN_OFF,
    STEP3_120MIN_ON,
    STEP4_120MIN_OFF
}PUMP_RETRY_STEP;





extern bit F_WaterOut;
extern bit bit_feed_output;
extern bit F_Flow_Block_State;


/*..hui [20-11-26오후 7:12:31] 피드 열리고 1초 후 펌프 가동..*/
#define PUMP_DELAY_TIME         10

/*#define PUMP_ON_40MIN           24000*/

/*..hui [21-4-1오전 11:36:43] 저소음 펌프로 변경됨에 따라 ON 시간 2시간으로 수정..*/
#define PUMP_ON_120MIN          72000

#define PUMP_OFF_20MIN          12000
#define PUMP_OFF_120MIN         72000

//#define PUMP_MAX_PWM            13600//28800 //0x3E80 * 2  //85%
#define PUMP_MAX_PWM            14400
#define PUMP_80_PERCENT_PWM     12800


#endif
