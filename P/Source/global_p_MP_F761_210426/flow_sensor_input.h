/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _FLOW_SENSOR_INPUT_HOT_H_
#define _FLOW_SENSOR_INPUT_HOT_H_


//

extern void R_INTC4_Start(void);
extern void R_INTC4_Stop(void);

extern void clac_hot_percent(void);



extern TYPE_BYTE          U8WaterOutStateB;
#define            u8WaterOutState                           U8WaterOutStateB.byte
#define            Bit0_Pure_Water_Select_State                U8WaterOutStateB.Bit.b0
#define            Bit1_Cold_Water_Select_State                 U8WaterOutStateB.Bit.b1
#define            Bit2_Hot_Water_Select_State                U8WaterOutStateB.Bit.b2




extern bit F_Effluent_OK;
extern U8 u8Extract_Continue;
extern bit F_WaterOut;
extern U8 gu8_Hot_Effluent_Step;
extern bit F_First_Hot_Effluent;
extern U8 gu8_Hot_Filling_Step;
extern bit F_WaterOut_Disable_State;
extern U16 gu16_Ice_Tray_Fill_Hz;
extern U16 u16_user_effluent_hz;
extern U16 gu16_hot_display_hz;
extern MODEL_SELECT F_Model_Select;
extern ICE_STEP gu8IceStep;

extern bit F_Hot_Filling_Finish;
extern U16 gu16_Filling_Hz;



extern bit bit_hot_filling_start;














#endif

