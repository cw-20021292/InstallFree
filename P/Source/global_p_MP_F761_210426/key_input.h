/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_H_
#define _KEY_INPUT_H_

extern void key_input_water_extract(void);
extern void key_cup_select_half(void);
extern void key_cup_select_one(void);
extern void key_cup_select_two(void);
extern void default_setting_cup_level( U8 mu8_setting_cup );
extern void Test_Mode_Key_Short_Input( U16 u16key_input_value);
extern void main_pba_test_start(void);
extern void diplay_test_start(void);
extern void line_test_start(void);
extern void mute_setting_job(void);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Line_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


//
#define UControl_Key_Mask                    0x07
#define UWater_Extract_Key                   0x02
#define UIce_Extract_Key                     0x01

#define UWater_Extract_Long_Key              0x02
#define UIce_Extract_Long_Key               0x01


extern bit F_FW_Version_Display_State;
extern bit F_All_Lock;
extern bit F_WaterOut;

extern U8 gu8_test_mode_timeout;
extern bit F_Model_Select_Finish;
extern MODEL_SELECT F_Model_Select;






#endif

