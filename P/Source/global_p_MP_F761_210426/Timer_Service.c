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
#include    "Timer_Service.h"

/**********************************************************************************************************************/
void Timer_250us_Service(void);

/**********************************************************************************************************************/
bit F_250us;
bit F_1ms;
bit F_2ms;
bit F_2_5ms;
bit F_3ms;
bit F_10ms;
bit F_50ms;
bit F_100ms;
bit F_1sec;
bit F_1min;
U8 u8Count_1ms;
U8 u8Count_2ms;
U8 u8Count_2_5ms;
U8 u8Count_3ms;
U8 u8Count_10ms;
U8 u8Count_50ms;
U8 u8Count_100ms;
U8 u8Count_1sec;
U8 u8Count_1min;
U8 u8CountSync;
U8 u8CountSync_50Ms;

/**********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Timer_250us_Service(void)
{

    F_250us = SET;

    u8Count_2_5ms++;
    u8Count_3ms++;

    u8Count_1ms++;

    if(u8Count_1ms >= 4)
    {
        /*1ms*/
        F_1ms = SET;

        #if 0
        if( F_Model_Select == MODEL_R_TYPE )
        {
            flow_input_count();
        }
        else{}
        #endif

        BuzControl();
        Key_Input();

        u8CountSync++;

        if(u8CountSync >= 250)
        {
            u8CountSync = 250;
        }
        else{}

        u8CountSync_50Ms++;
        if(u8CountSync_50Ms >= 250)
        {
            u8CountSync_50Ms = 250;
        }
        else{}

        u8Count_2ms++;
        u8Count_1ms = CLEAR;
    }
    else{}

    if(u8Count_2ms >= 2)
    {
        /*2ms*/
        F_2ms = SET;
        u8Count_2ms = CLEAR;

        u8Count_10ms++;
    }
    else{}

    if(u8Count_2_5ms >= 10)
    {
        /* 2.5ms*/
        F_2_5ms = SET;
        u8Count_2_5ms = CLEAR;
    }
    else{}

    if(u8Count_3ms >= 12)
    {
        /*3ms*/
        F_3ms = SET;
        u8Count_3ms = CLEAR;
    }
    else{}

    if(u8Count_10ms >= 5)
    {
        /*10ms*/
        F_10ms = SET;
        u8Count_10ms = CLEAR;
        u8Count_50ms++;
        u8Count_100ms++;

/***********************************************************************************************************************/
        BuzTimeCounter();       // Buzzer 음 제어 시간 Counter
/***********************************************************************************************************************/

        /*Lcd_Communication();*/
        led_output();
    }
    else{}

    if(u8Count_50ms >= 5)
    {
        F_50ms = SET;
        u8Count_50ms = 0;
    }
    else{}


    if(u8Count_100ms >= 10)
    {
        /*100ms*/
        F_100ms = SET;
        u8Count_100ms = CLEAR;

        u8Count_1sec++;
    }
    else{}

    if(u8Count_1sec >= 10)
    {
        /*1s*/
        F_1sec = SET;
        u8Count_1sec = CLEAR;

        if(gu8_test_mode_timeout > 0)
        {
            gu8_test_mode_timeout--;                    //nfc test key delay  20150410
        }
        else{}

        u8Count_1min++;
    }
    else{}

    if(u8Count_1min >= 60)
    {
        /*1min*/
        F_1min = SET;
        u8Count_1min = CLEAR;
        //power_saving_timer();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

