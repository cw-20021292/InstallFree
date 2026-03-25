/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "led_output.h"



void led_output(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_output(void)
{
    pLED_HALF_CUP = Bit0_Half_Cup_Led_White;
    pLED_ONE_CUP = Bit1_One_Cup_Led_White;
    pLED_TWO_CUP = Bit2_Two_Cup_Led_White;
    pLED_EXTRACT = Bit3_Extract_Led_White;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



