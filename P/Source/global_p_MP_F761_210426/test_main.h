/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TEST_MAIN_H_
#define _TEST_MAIN_H_

//

extern void Pcb_Test_Main(void);
extern void off_all_control_led( void );
extern void Display_Test_Main(void);
extern void Line_Test_Main(void);
extern void BuzStep(U8 mu8Step);



extern bit F_FW_Version_Display_State;
extern U8 gu8_led_version_step;
extern U8 gu8_version_display_Timer;

extern U8 gu8T300ms;
extern U8 gu8T500ms;
extern U8 gu8T1000ms;
extern MODEL_SELECT F_Model_Select;




#endif
