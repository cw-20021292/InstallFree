/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _Timer_Service_H_
#define _Timer_Service_H_



extern void Key_Input(void);
extern void led_output(void);
extern void flow_input_count(void);
extern void BuzControl(void);
extern void BuzTimeCounter(void);


extern U8 gu8_test_mode_timeout;
extern MODEL_SELECT F_Model_Select;



#endif
