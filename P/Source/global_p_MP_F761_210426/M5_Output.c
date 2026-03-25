/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Output.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M5_Output.h"

void Output(void);

U8 u8_system_init_timer;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Output(void)
{
    /*..hui [19-7-18오후 5:01:36] 센서 다 읽을때까지 기다린다..*/
    if(u8_system_init_timer < 50)
    {
        u8_system_init_timer++;
        return;
    }
    else
    {
        u8_system_init_timer = 50;
    }

    output_valve_feed();
    output_valve_nos();
    output_valve_extract();

    /*..hui [20-9-25오후 5:40:01] 외장 펌프.. R 타입만 적용..*/
    if( F_Model_Select == MODEL_R_TYPE )
    {
        output_pump();
    }
    else{}

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


