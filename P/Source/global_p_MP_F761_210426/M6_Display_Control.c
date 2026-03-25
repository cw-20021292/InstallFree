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
#include    "M6_Display_Control.h"



void Display_Control(void);
void led_control_mode_decesion(void);
void front_led_value_prepare(void);
void display_version( void );
void display_extract_state(void);
void display_normal_state(void);
void display_error_state(void);
void on_all_control_led( void );
void off_all_control_led( void );
void led_blink_timer(void);


TYPE_BYTE          U8FrontLEDB;
#define            u8FrontLED                             U8FrontLEDB.byte
#define            Bit0_Half_Cup_Led_White                U8FrontLEDB.Bit.b0
#define            Bit1_One_Cup_Led_White                 U8FrontLEDB.Bit.b1
#define            Bit2_Two_Cup_Led_White                 U8FrontLEDB.Bit.b2
#define            Bit3_Extract_Led_White                 U8FrontLEDB.Bit.b3

U8 gu8T300ms;
bit F_Wink_300ms;

U8 gu8T300ms_Test;
bit F_Wink_300ms_Test;

U8 gu8T500ms;
bit F_Wink_500ms;

U8 gu8T1000ms;
bit F_Wink_1000ms;

U8 gu8T2000ms;
bit F_Wink_2000ms;

U16 gu16T3000ms;
bit F_Wink_3000ms;



U8 gu8_Control_led_State;
U8 gu8_led_version_step;
U8 gu8_version_display_Timer;
U8 gu8_version_display_count;
bit F_FW_Version_Display_State;

bit F_Extract_Led_OnOff;

bit bit_cup_level_change;
U8 gu8TCup100ms;
bit bit_cup_level_flick;

U8 gu8_cont_display_timer;
U8 gu8_move_cup;

U8 gu8_water_out_led_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Display_Control(void)
{
    led_blink_timer();
    led_control_mode_decesion();
    front_led_value_prepare();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_control_mode_decesion(void)
{
    if( F_FW_Version_Display_State != SET )
    {
        gu8_Control_led_State = PROC_VERSION;
    }
    else if(gu8_Error_Code != 0)
    {
        /*..hui [17-12-28오후 8:32:21] 전체 잠금일때.. 에러 걸리면 표시 추가해야함..*/
        gu8_Control_led_State = PROC_ERROR;
    }
    else
    {
        gu8_Control_led_State = PROC_NORMAL;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void front_led_value_prepare(void)
{
    switch(gu8_Control_led_State)
    {
        case PROC_VERSION:

            display_version();

            break;

        case PROC_ERROR:

            display_normal_state();
            display_error_state();

            break;

        case PROC_NORMAL:

            display_normal_state();

            break;

        default:

            display_normal_state();

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_version( void )
{
    switch(gu8_led_version_step)
    {
        case PROC_START:

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_version_display_Timer = 0;

                gu8_version_display_count++;

                if((BIT)(gu8_version_display_count & 1) == (BIT)0)
                {
                    on_all_control_led();
                }
                else
                {
                    off_all_control_led();
                }

                if(gu8_version_display_count > 6)
                {
                    gu8_led_version_step++;
                    gu8_version_display_count = 0;
                    gu8_version_display_Timer = 0;
                }
                else{}
            }
            else{}

            break;

        case PROC_1:

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_version_display_Timer = 0;
                gu8_led_version_step++;
            }
            else{}

            break;

        case PROC_2:

            /*..hui [20-1-14오후 1:54:06] 좀 더 알아보기 쉽게 변경 우선 9까지만..*/
            if(Main_FW_Version_Main == 1)
            {
                Bit0_Half_Cup_Led_White = SET;
            }
            else if(Main_FW_Version_Main == 2)
            {
                Bit1_One_Cup_Led_White = SET;
            }
            else if(Main_FW_Version_Main == 3)
            {
                Bit2_Two_Cup_Led_White = SET;
            }
            else if(Main_FW_Version_Main == 4)
            {
                Bit3_Extract_Led_White = SET;
            }
            else if(Main_FW_Version_Main == 5)
            {
                Bit0_Half_Cup_Led_White = SET;
                Bit1_One_Cup_Led_White = SET;
            }
            else if(Main_FW_Version_Main == 6)
            {
                Bit0_Half_Cup_Led_White = SET;
                Bit2_Two_Cup_Led_White = SET;
            }
            else
            {
                Bit1_One_Cup_Led_White = SET;
                Bit2_Two_Cup_Led_White = SET;
            }

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_led_version_step++;
                gu8_version_display_Timer = 0;
            }
            else{}

            break;

        case PROC_END:

            /*..hui [17-4-4오후 2:20:26] 마지막으로 500ms OFF하고 종료..*/
            off_all_control_led();

            gu8_version_display_Timer++;

            if(gu8_version_display_Timer >= 5)
            {
                gu8_led_version_step = 0;
                gu8_version_display_Timer = 0;
                F_FW_Version_Display_State = SET;
            }
            else{}

            break;

        default:
            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_extract_state(void)
{
    #if 0
    /*..hui [20-11-20오후 3:49:46] 연속 추출일때는 우선은 추출 LED 500ms 점멸로..*/
    if( u8Extract_Continue == SET )
    {
        Bit3_Extract_Led_White = F_Wink_300ms;
    }
    else
    {
        if( F_WaterOut == SET )
        {
            /*..hui [21-1-5오후 7:03:25] 부저가 없으므로 우선 추출할때 1초 점멸로 변경..*/
            /*..hui [21-1-5오후 7:03:40] 추출은 1초 점멸..연속추출은 0.5초 점멸로.. 우선~~~..*/
            Bit3_Extract_Led_White = F_Wink_500ms;
        }
        else
        {
            Bit3_Extract_Led_White = SET;
        }
    }
    #endif

    if( F_WaterOut == SET )
    {
        if( u8Extract_Continue == SET )
        {
            //Bit3_Extract_Led_White = F_Wink_300ms;
            Bit3_Extract_Led_White = SET;
        }
        else
        {
            /*..hui [21-1-5오후 7:03:25] 부저가 없으므로 우선 추출할때 1초 점멸로 변경..*/
            /*..hui [21-1-5오후 7:03:40] 추출은 1초 점멸..연속추출은 0.5초 점멸로.. 우선~~~..*/
            //Bit3_Extract_Led_White = F_Wink_500ms;

            gu8_water_out_led_timer++;

            if( gu8_water_out_led_timer >= 5 )
            {
                gu8_water_out_led_timer = 0;
                Bit3_Extract_Led_White ^= SET;
            }
            else{}
        }
    }
    else
    {
        Bit3_Extract_Led_White = SET;
        gu8_water_out_led_timer = 0;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_normal_state(void)
{
    display_extract_state();

    if( F_WaterOut == SET && u8Extract_Continue == SET )
    {
        gu8_cont_display_timer++;

        if( gu8_cont_display_timer >= 3 )
        {
            gu8_cont_display_timer = 0;

            if( gu8_move_cup == 4 )
            {
                gu8_move_cup = 1;
            }
            else
            {
                gu8_move_cup = gu8_move_cup << 1;
            }

            Bit0_Half_Cup_Led_White = gu8_move_cup & 1;
            Bit1_One_Cup_Led_White = (gu8_move_cup >> 1)  & 1;
            Bit2_Two_Cup_Led_White = (gu8_move_cup >> 2) & 1;
        }
        else{}
    }
    else
    {
        gu8_cont_display_timer = 0;
        gu8_move_cup = gu8Cup_level;

        if(gu8Cup_level == CUP_LEVEL_HALF)
        {
            Bit0_Half_Cup_Led_White = bit_cup_level_flick;
            Bit1_One_Cup_Led_White = CLEAR;
            Bit2_Two_Cup_Led_White = CLEAR;
        }
        else if(gu8Cup_level == CUP_LEVEL_ONE)
        {
            Bit0_Half_Cup_Led_White = CLEAR;
            Bit1_One_Cup_Led_White = bit_cup_level_flick;
            Bit2_Two_Cup_Led_White = CLEAR;
        }
        else
        {
            Bit0_Half_Cup_Led_White = CLEAR;
            Bit1_One_Cup_Led_White = CLEAR;
            Bit2_Two_Cup_Led_White = bit_cup_level_flick;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void display_error_state(void)
{
    if( u8Extract_Continue != SET )
    {
        if( Bit0_Leakage_Sensor_Error == SET )
        {
            Bit0_Half_Cup_Led_White = F_Wink_500ms;
        }
        else if( Bit1_Room_High_Water_Level_Error == SET )
        {
            Bit1_One_Cup_Led_White = F_Wink_500ms;
        }
        else if( Bit2_Feed_Valve_Error == SET )
        {
            Bit2_Two_Cup_Led_White = F_Wink_500ms;
        }
        else{}
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void on_all_control_led( void )
{
    u8FrontLED = 0x0F;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void off_all_control_led( void )
{
    u8FrontLED = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void led_blink_timer(void)
{
    gu8T300ms++;

    if(gu8T300ms >= 3)
    {
        gu8T300ms = 0;
        F_Wink_300ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T500ms++;

    if(gu8T500ms >= 5)
    {
        gu8T500ms = 0;
        F_Wink_500ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T1000ms++;

    if(gu8T1000ms >= 10)
    {
        gu8T1000ms = 0;
        F_Wink_1000ms ^= SET;          // 300msec Wink
    }
    else{}

    gu8T2000ms++;

    if(gu8T2000ms >= 20)
    {
        gu8T2000ms = 0;
        F_Wink_2000ms ^= SET;          // 300msec Wink
    }
    else{}

    gu16T3000ms++;

    if(gu16T3000ms >= 30)
    {
        gu16T3000ms = 0;
        F_Wink_3000ms ^= SET;          // 300msec Wink
    }
    else{}

    /*..hui [21-1-4오후 7:21:29] 부저가 없으므로 물량 설정시 2회 깜빡임으로 알림주도록 개선..*/
    if( bit_cup_level_change == SET )
    {
        gu8TCup100ms++;

        if( gu8TCup100ms > 15 )
        {
            bit_cup_level_change = CLEAR;
            bit_cup_level_flick = SET;
        }
        else
        {
            if( gu8TCup100ms % 5 == 1 )
            {
                bit_cup_level_flick ^= SET;
            }
            else{}
        }
    }
    else
    {
        gu8TCup100ms = 0;
        bit_cup_level_flick = SET;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


