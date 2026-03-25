/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _RXTRACT_CONTROL_H_
#define _RXTRACT_CONTROL_H_

//


extern void BuzStep(U8 mu8Step);

extern bit F_WaterOut;
extern U16 gu16Water_Extract_Timer;
extern U16 u16Efluent_Time;
extern U8 u8Extract_Continue;
extern bit F_WaterOut_Disable_State;

extern U8 gu8Cup_level;
extern MODEL_SELECT F_Model_Select;
extern U8 gu8_Room_Water_Level;



#define WATER_EXTRACT_CHECK_TIME       6000

#define WATER_COMPENSATION_MAX_TIME    15000




/*..hui [21-2-25ø¿»ƒ 8:22:05] 1.2√ ..*/
/*#define WATER_EXTRACT_CMST_TIME      12*/
//#define WATER_EXTRACT_CMST_TIME_HALF_ONE         8
//#define WATER_EXTRACT_CMST_TIME_TWO_1LITGER      11

#define WATER_EXTRACT_CMST_TIME_HALF             5
#define WATER_EXTRACT_CMST_TIME_ONE              10
#define WATER_EXTRACT_CMST_TIME_TWO              23
#define WATER_EXTRACT_CMST_TIME_1LITGER          33





#endif
