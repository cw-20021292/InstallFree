/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _TEST_PCB_H_
#define _TEST_PCB_H_

//
extern void led_blink_timer(void);
extern void calculate_flow_input(void);
extern void display_version( void );








extern TYPE_BYTE          U8FrontLEDB;
#define            u8FrontLED                             U8FrontLEDB.byte
#define            Bit0_Half_Cup_Led_White                U8FrontLEDB.Bit.b0
#define            Bit1_One_Cup_Led_White                 U8FrontLEDB.Bit.b1
#define            Bit2_Two_Cup_Led_White                 U8FrontLEDB.Bit.b2
#define            Bit3_Extract_Led_White                 U8FrontLEDB.Bit.b3


extern bit F_FW_Version_Display_State;
extern bit F_Wink_300ms;
extern U8 gu8_half_cup_test_input;
extern U8 gu8_one_cup_test_input;
extern U8 gu8_two_cup_test_input;
extern U8 gu8_water_ext_test_input;
extern U8 gu8_Flow_1sec;
extern MODEL_SELECT F_Model_Select;


#endif
