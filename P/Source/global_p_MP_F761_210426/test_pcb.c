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
#include    "test_pcb.h"



void Pcb_Test_Main(void);
void pcb_test_job(void);
void sensor_test(void);
void watertank_high_water(void);
void watertank_over_water(void);
void water_leak(void);
void output_test(void);
void valve_output_one(void);
void flow_sensor(void);



U8 gu8_flow_test_timer;

bit bit_flow_input;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Pcb_Test_Main(void)
{
    if(F_FW_Version_Display_State != SET)
    {
        display_version();
    }
    else
    {
        pcb_test_job();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void pcb_test_job(void)
{
    sensor_test();
    output_test();

    if( F_Model_Select == MODEL_R_TYPE )
    {
        #if 0
        if( bit_flow_input == 1 )
        {
            led_blink_timer();
        }
        else
        {
            F_Wink_300ms = 1;
        }

        /*..hui [19-7-22오후 7:36:53] 유량센서..*/
        //calculate_flow_input();
        //flow_sensor();
        #endif

        led_blink_timer();
    }
    else
    {
        /*..hui [20-12-17오후 7:19:55] L 타입은 점등상태로 유지..*/
        bit_flow_input = 1;
        F_Wink_300ms = 1;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void sensor_test(void)
{
    watertank_high_water();
    watertank_over_water();
    water_leak();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_high_water(void)
{
    if(pLEVEL_HIGH == SET)
    {
        Bit1_One_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit1_One_Cup_Led_White = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void watertank_over_water(void)
{
    if(pLEVEL_OVERFLOW == SET)
    {
        Bit2_Two_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit2_Two_Cup_Led_White = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_leak(void)
{
    if(pLEAKAGE_SENSOR == SET)
    {
        Bit0_Half_Cup_Led_White = F_Wink_300ms;
    }
    else
    {
        Bit0_Half_Cup_Led_White = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_test(void)
{
    valve_output_one();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void valve_output_one(void)
{
    if(gu8_half_cup_test_input == 0)
    {
        pVALVE_FEED = 0;
    }
    else
    {
        pVALVE_FEED = 1;
    }

    if(gu8_one_cup_test_input == 0)
    {
        pVALVE_NOS = 0;
    }
    else
    {
        pVALVE_NOS = 1;
    }


    if(gu8_two_cup_test_input == 0)
    {
        pVALVE_EXTRACT = 0;
    }
    else
    {
        pVALVE_EXTRACT = 1;
    }

    if( F_Model_Select == MODEL_R_TYPE )
    {
        if(gu8_water_ext_test_input == 0)
        {
            Bit3_Extract_Led_White = 0;
            pPUMP_R_TYPE = 0;
        }
        else
        {
            Bit3_Extract_Led_White ^= 1;
            pPUMP_R_TYPE = 1;
        }
    }
    else
    {
        if(gu8_water_ext_test_input == 0)
        {
            Bit3_Extract_Led_White = 0;
        }
        else
        {
            Bit3_Extract_Led_White = 1;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void flow_sensor(void)
{
    #if 0
    if( gu8_Flow_1sec > 5 )
    {
        gu8_flow_test_timer++;

        if( gu8_flow_test_timer >= 10 )
        {
            bit_flow_input = 1;
        }
        else{}
    }
    else
    {
        bit_flow_input = 0;
        gu8_flow_test_timer = 0;
    }
    #endif
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

