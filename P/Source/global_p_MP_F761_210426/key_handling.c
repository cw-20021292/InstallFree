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
#include    "key_handling.h"


void key_cup_select_half(void);
void key_cup_select_one(void);
void key_cup_select_two(void);
void default_setting_cup_level( U8 mu8_setting_cup );
void mute_setting_job(void);

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cup_select_half(void)
{
    if(F_WaterOut != SET)
    {
        gu8Cup_level = CUP_LEVEL_HALF;
        BuzStep(BUZZER_SELECT);
        gu8_cup_level_time_init = SET;
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cup_select_one(void)
{
    if(F_WaterOut != SET)
    {
        gu8Cup_level = CUP_LEVEL_ONE;
        BuzStep(BUZZER_SELECT);
        gu8_cup_level_time_init = SET;
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_cup_select_two(void)
{
    if(F_WaterOut != SET)
    {
        gu8Cup_level = CUP_LEVEL_TWO;
        BuzStep(BUZZER_SELECT);
        gu8_cup_level_time_init = SET;
    }
    else
    {
        BuzStep(BUZZER_ERROR);
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void default_setting_cup_level( U8 mu8_setting_cup )
{
    /*..hui [17-12-19오후 2:25:35] 현재 디폴트 상태랑 동일한 키 입력시 패스....*/
    if(mu8_setting_cup == gu8Cup_level_Default)
    {
        //
    }
    else
    {
        gu8Cup_level_Default = mu8_setting_cup;
        /*..hui [21-1-4오후 2:09:30] 컵 디폴트 설정 시 부저가 없기 때문에 설정이 됐는지 알수가 없음..*/
        /*..hui [21-1-4오후 2:09:46] 설정된 컵 LED를 500ms 잠깐 OFF 해주는걸로 우선 변경..*/
        bit_cup_level_change = SET;

        if(F_Mute_Enable == CLEAR)
        {
            BuzStep(BUZZER_SETUP);
        }
        else
        {
            BuzStep(BUZZER_SETUP_MUTE);
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void mute_setting_job(void)
{
    if(F_WaterOut != SET)
    {
        if(F_Mute_Enable != SET)
        {
            F_Mute_Enable = SET;
        }
        else
        {
            F_Mute_Enable = CLEAR;
        }

        BuzStep(BUZZER_MUTE);
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


