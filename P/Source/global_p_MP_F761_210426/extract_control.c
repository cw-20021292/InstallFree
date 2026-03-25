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
#include    "extract_control.h"


void water_extract_control(void);
void calc_water_acc(void);

U16 u16_user_effluent_time;
U16 u16_user_effluent_total_time;
U16 u16_user_effluent_cup_size;

U32 gu32_calc_one_day_user_none;

U16 gu16_10min_timer;
U8 gu8_Effluent_Add_Time_Half;
U8 gu8_Effluent_Add_Time_One;
U8 gu8_Effluent_Add_Time_Two;
U8 gu8_Effluent_Add_Time_1Liter;

U8 gu8_before_water_level;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_control(void)
{
    U16 mu16_effluent_time = 0;

    calc_water_acc();

    if(F_WaterOut == SET)
    {
        if( u8Extract_Continue == SET )
        {
            mu16_effluent_time = u16Efluent_Time;
        }
        else
        {
            if( F_Model_Select == MODEL_R_TYPE )
            {
                /*..hui [21-3-4오후 5:27:00] R 타입 한컵..*/
                /*..hui [21-4-2오후 3:50:09] 120/250 1초, 500 2.3초, 1000 3.3초 추가로 변경..*/
                /*..hui [21-4-2오후 3:50:12] 서재식..*/
                if( gu8Cup_level == CUP_LEVEL_HALF )
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_One;
                }
                else if( gu8Cup_level == CUP_LEVEL_ONE )
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_Two;
                }
                else
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_1Liter;
                }
            }
            else
            {
                /*..hui [21-3-4오후 5:26:52] L 타입 반컵 / 한컵..*/
                if( gu8Cup_level == CUP_LEVEL_HALF )
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_Half;
                }
                else if( gu8Cup_level == CUP_LEVEL_ONE )
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_One;
                }
                else
                {
                    mu16_effluent_time = u16Efluent_Time + gu8_Effluent_Add_Time_Two;
                }
            }
        }

        gu16Water_Extract_Timer++;

        if( gu16Water_Extract_Timer >= mu16_effluent_time )
        {
            F_WaterOut = CLEAR;
            gu16Water_Extract_Timer = 0;
            u16Efluent_Time = 0;

            BuzStep(BUZZER_EFFLUENT_END);

            /*..hui [18-1-11오후 11:12:11] 연속추출 정지..*/
            u8Extract_Continue = CLEAR;

            /*..hui [18-3-14오후 3:50:40] 정량추출 종료..*/
            F_WaterOut_Disable_State = SET;
        }
        else{}
    }
    else
    {
        gu16Water_Extract_Timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void calc_water_acc(void)
{
    U16 mu16_water_acc = 0;

    if( gu8_Room_Water_Level == ROOM_LEVEL_FULL )
    {
        u16_user_effluent_time = 0;
        u16_user_effluent_total_time = 0;
        u16_user_effluent_cup_size = 0;
        gu32_calc_one_day_user_none = 0;
        gu16_10min_timer = 0;
        gu8_Effluent_Add_Time_Half = 0;
        gu8_Effluent_Add_Time_One = 0;
        gu8_Effluent_Add_Time_Two = 0;
        gu8_Effluent_Add_Time_1Liter = 0;

        gu8_before_water_level = SET;
    }
    else
    {
        if( gu8_before_water_level == SET )
        {
            gu16_10min_timer++;

            /*..hui [21-2-25오후 8:17:15] 10분동안 3리터 추출했는지 확인..*/
            if( gu16_10min_timer >= WATER_EXTRACT_CHECK_TIME )
            {
                /*..hui [21-2-26오전 9:25:33] 10분 지났는데 3리터 미만 추출했으면 그 이후로 더이상 확인하지 않는다..*/
                /*..hui [21-3-4오후 5:19:53] 2리터로 변경..*/
                if( gu32_calc_one_day_user_none < 2000 )
                {
                    gu8_before_water_level = CLEAR;
                }
                else{}

                if( gu16_10min_timer >= WATER_COMPENSATION_MAX_TIME )
                {
                    gu16_10min_timer = WATER_COMPENSATION_MAX_TIME;
                    gu8_before_water_level = CLEAR;
                }
                else{}
            }
            else
            {
                if( gu32_calc_one_day_user_none >= 2000 )
                {
                    gu8_Effluent_Add_Time_Half = WATER_EXTRACT_CMST_TIME_HALF;
                    gu8_Effluent_Add_Time_One = WATER_EXTRACT_CMST_TIME_ONE;
                    gu8_Effluent_Add_Time_Two = WATER_EXTRACT_CMST_TIME_TWO;
                    gu8_Effluent_Add_Time_1Liter = WATER_EXTRACT_CMST_TIME_1LITGER;

                    /*..hui [21-2-25오후 8:25:28] 3리터 추출된 시점부터 15분간만 보상..*/
                    gu16_10min_timer = WATER_EXTRACT_CHECK_TIME;
                }
                else{}
            }
        }
        else
        {
            gu8_Effluent_Add_Time_Half = 0;
            gu8_Effluent_Add_Time_One = 0;
            gu8_Effluent_Add_Time_Two = 0;
            gu8_Effluent_Add_Time_1Liter = 0;
        }
    }

    if(F_WaterOut == SET)
    {
        u16_user_effluent_time++;
        u16_user_effluent_total_time = u16Efluent_Time;

        if(u8Extract_Continue == SET)
        {
            /*..hui [19-8-23오후 1:33:33] 연속추출 했을때 물 양.. 나중에 계산해서 변경해야 함..*/
            /*..hui [21-2-25오전 9:48:31] 연속 추출은 5리터로..*/
            u16_user_effluent_cup_size = 5000;
        }
        else
        {
            if(gu8Cup_level == CUP_LEVEL_HALF)
            {
                if( F_Model_Select == MODEL_R_TYPE )
                {
                    u16_user_effluent_cup_size = 250;
                }
                else
                {
                    u16_user_effluent_cup_size = 120;
                }
            }
            else if(gu8Cup_level == CUP_LEVEL_ONE)
            {
                if( F_Model_Select == MODEL_R_TYPE )
                {
                    u16_user_effluent_cup_size = 500;
                }
                else
                {
                    u16_user_effluent_cup_size = 250;
                }
            }
            else
            {
                if( F_Model_Select == MODEL_R_TYPE )
                {
                    u16_user_effluent_cup_size = 1000;
                }
                else
                {
                    u16_user_effluent_cup_size = 500;
                }
            }
        }
    }
    else
    {
        if(u16_user_effluent_time != 0)
        {
            mu16_water_acc =
                (U16)(((U32)u16_user_effluent_time * (U32)u16_user_effluent_cup_size) / u16_user_effluent_total_time);

            gu32_calc_one_day_user_none += mu16_water_acc;

            if(gu32_calc_one_day_user_none >= 5000)
            {
                gu32_calc_one_day_user_none = 5000;
            }
            else{}

            u16_user_effluent_time = 0;
        }
        else
        {
            u16_user_effluent_time = 0;
            u16_user_effluent_total_time = 0;
            u16_user_effluent_cup_size = 0;
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

