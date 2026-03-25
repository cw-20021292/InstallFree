/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _KEY_INPUT_WATER_EXT_H_
#define _KEY_INPUT_WATER_EXT_H_


//

extern void Test_Mode_Extract_Key_Short_Input(void);
extern void BuzStep(U8 mu8Step);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Line_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


#define UExtract_Key_Mask                    0x01

#define EXTRACT_TIME_CONTINUE                1800
#define EXTRACT_TIME_CONTINUE_LINE_TEST      6000

extern U8 gu8Cup_level;
extern bit F_WaterOut_Disable_State;
extern MODEL_SELECT F_Model_Select;




 #endif
