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
#include    "error_water_level.h"


void check_error_water_level(void);
void check_error_over_flow(void);


U16 u16_water_in_check_timer_sec;
U16 u16_water_in_check_timer_min;

bit F_Err_OVF_Check;
U8 gu8_feed_error_count;
U8 gu8_high_level_error_count;
U8 gu8ErrOVLEVCnt;

U8 gu8OVFOnDelay;
U8 gu8OVFOffDelay;

bit bit_ovf_clear;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_water_level(void)
{
    /*..hui [19-12-18오후 10:13:29] 물넘침센서 관련 에러 추가..*/
    check_error_over_flow();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_over_flow(void)
{
    if(bit_overflow_level == SET && F_Err_OVF_Check != SET)
    {
        if(gu8_Room_Water_Level == ROOM_LEVEL_FULL)
        {
            /*..hui [20-2-11오후 5:36:41] 피드 밸브 에러..*/
            gu8_feed_error_count++;
        }
        else /*if(gu8_Room_Water_Level == ROOM_LEVEL_LOW)*/
        {
            /*..hui [20-2-11오후 5:36:52] 만수위 센서 에러..*/
            gu8_high_level_error_count++;
        }

        F_Err_OVF_Check = SET;                 //오버플로우 셋
    }
    else{}

    if( bit_overflow_level == CLEAR && gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        F_Err_OVF_Check = CLEAR;
    }
    else{}

    if( bit_overflow_level == CLEAR && gu8_Room_Water_Level == ROOM_LEVEL_FULL)
    {
        /*..hui [20-2-11오후 5:36:08] 만수위 센서 에러..*/
        /*..hui [20-11-26오후 2:18:42] 물넘침 해제 상태에서 만수위센서 정상 감지되면..*/
        /*..hui [20-11-26오후 2:18:47] 만수위 센서 에러 카운트 초기화..*/
        gu8_high_level_error_count = 0;
    }
    else{}

    if( gu8_feed_error_count >= 3 )
    {
        /*..hui [19-12-18오후 10:25:10] 피드밸브 에러..*/
        Bit2_Feed_Valve_Error = SET;
    }
    else{}

    if( gu8_high_level_error_count >= 3 )
    {
        /*..hui [19-12-18오후 10:25:15] 만수위 센서 에러..*/
        Bit1_Room_High_Water_Level_Error = SET;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



