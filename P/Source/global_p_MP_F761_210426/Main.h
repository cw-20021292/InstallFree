/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _MAIN_H_
#define _MAIN_H_


extern void R_WDT_Restart(void);
extern void System_ini(void);
extern void Input(void);
extern void Output(void);
extern void Mode_Control(void);
extern void Display_Control(void);
extern void Error_Control(void);
extern void Test_Mode_Main(void);

extern TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Line_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2


extern U8  u8CountSync;





#endif
