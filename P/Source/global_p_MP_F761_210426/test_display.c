/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Main.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "test_display.h"

void Display_Test_Main(void);
void display_test_job(void);




/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Test_Main(void)
{
    if(F_FW_Version_Display_State != SET)
    {
        display_version();
    }
    else
    {
        display_test_job();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_test_job(void)
{
    if( F_Model_Select == MODEL_R_TYPE )
    {
        led_blink_timer();
    }
    else
    {
        F_Wink_300ms = 1;
    }

    if(gu8_half_cup_test_input == 1)
    {
        Bit0_Half_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit0_Half_Cup_Led_White = CLEAR;
    }

    if(gu8_one_cup_test_input == 1)
    {
        Bit1_One_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit1_One_Cup_Led_White = CLEAR;
    }

    if(gu8_two_cup_test_input == 1)
    {
        Bit2_Two_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit2_Two_Cup_Led_White = CLEAR;
    }

    if(gu8_water_ext_test_input == 1)
    {
        Bit3_Extract_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit3_Extract_Led_White = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


