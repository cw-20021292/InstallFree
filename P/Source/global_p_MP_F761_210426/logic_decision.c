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
#include    "logic_decision.h"

void logic_decision(void);
void cup_select_return_decision(void);
void water_out_disable_time_check(void);



U8 gu8Cup_level;
U8 gu8Cup_level_Default;
U16 gu16_cup_level_default_return_time;


U8 gu8_waterout_disable_time;
bit F_WaterOut_Disable_State;

U8 gu8_cup_level_time_init;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void logic_decision(void)
{
    /*..hui [17-12-19오후 2:03:31] 정량추출 복귀..*/
    cup_select_return_decision();

    /*..hui [18-3-14오후 3:54:53] 정량 추출 후 500ms 물 추출 disable..*/
    water_out_disable_time_check();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void cup_select_return_decision(void)
{
    /*..hui [19-8-22오후 2:23:13] 물량은 냉/온/정/사용자/물량 눌렸을때만 초기화.. 캐럿 참조..*/
    if(gu8_cup_level_time_init == SET)
    {
        /*..hui [19-2-8오후 3:49:45] 같은 키 계속 눌렀을때도 시간 초기화 추가..*/
        gu8_cup_level_time_init = CLEAR;
        gu16_cup_level_default_return_time = 0;
    }
    else{}


    if(gu8Cup_level != gu8Cup_level_Default)
    {
        /*..hui [17-12-19오후 2:07:16] 추출중에는 시간 초기화..*/
        if(F_WaterOut == SET)
        {
            gu16_cup_level_default_return_time = 0;
        }
        else
        {
            gu16_cup_level_default_return_time++;
        }

        if(gu16_cup_level_default_return_time >= CUP_LEVEL_RETURN_TIME)
        {
            gu8Cup_level = gu8Cup_level_Default;
        }
        else{}
    }
    else
    {
        gu16_cup_level_default_return_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_out_disable_time_check(void)
{
    /*..hui [18-3-14오후 12:48:04] 물 추출 시 추출 종료되는 순간부터 500ms 동안 물 추출 입력 받지 않는다..*/
    /*..hui [18-3-14오후 12:48:47] 추출 종료 버튼 눌렀는데 종료되는 순간과 겹쳐서 한번 더 추출되는 현상때문..*/
    /*..hui [18-3-14오후 12:49:16] 품질팀 요청사항.. 별 효과는 없을 것 같다..*/
    if(F_WaterOut_Disable_State == SET)
    {
        gu8_waterout_disable_time++;

        if(gu8_waterout_disable_time >= 5)
        {
            gu8_waterout_disable_time = 5;
            F_WaterOut_Disable_State = CLEAR;
        }
        else
        {
            /*F_WaterOut_Disable_State = SET;*/
        }
    }
    else
    {
        gu8_waterout_disable_time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


