/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _SYSTEM_INIT_H_
#define _SYSTEM_INIT_H_

//extern void R_INTC4_Start(void);
extern void Delay_MS( U16 ms );
extern void BuzStep(U8 mu8Step);
extern void R_TAU0_Channel2_Start(void);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Line_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


extern U8 gu8Cup_level;
extern U8 gu8Cup_level_Default;

extern U16 gu16_filling_delay_timer;

extern U8 gu8_test_mode_timeout;



#endif

