/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _ERROR_CONTROL_H_
#define _ERROR_CONTROL_H_



extern void check_flow_error(void);
extern void check_error_water_level(void);

extern bit F_FW_Version_Display_State;

#define MAX_ERROR_NUM          32



#endif
