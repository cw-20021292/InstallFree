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
#include    "water_level.h"



void input_water_level(void);
void input_room_water_level(void);
void input_overflow(void);


U8 u8_room_full_level_on_decision_cnt;
U8 u8_room_full_level_off_decision_cnt;

U8 gu8_Room_Water_Level;


U8 u8_overflow_on_decision_cnt;
U8 u8_overflow_off_decision_cnt;

bit bit_overflow_level;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_water_level(void)
{
    /*..hui [19-6-26오후 1:12:15] 정수탱크 수위센서 입력..*/
    input_room_water_level();

    /*..hui [19-12-18오후 9:30:18] 물넘침 센서 추가..*/
    input_overflow();

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_room_water_level(void)
{
    if( pLEVEL_HIGH == CLEAR )
    {
        u8_room_full_level_on_decision_cnt = 0;
        u8_room_full_level_off_decision_cnt++;

        if( u8_room_full_level_off_decision_cnt >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            u8_room_full_level_off_decision_cnt = ROOM_WATER_LEVEL_DETECT_TIME;
            gu8_Room_Water_Level = ROOM_LEVEL_LOW;
        }
        else{}
    }
    else
    {
        u8_room_full_level_off_decision_cnt = 0;
        u8_room_full_level_on_decision_cnt++;

        if( u8_room_full_level_on_decision_cnt >= ROOM_WATER_LEVEL_DETECT_TIME )
        {
            u8_room_full_level_on_decision_cnt = ROOM_WATER_LEVEL_DETECT_TIME;
            gu8_Room_Water_Level = ROOM_LEVEL_FULL;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_overflow(void)
{
    if(pLEVEL_OVERFLOW == CLEAR)
    {
        u8_overflow_on_decision_cnt = 0;
        u8_overflow_off_decision_cnt++;

        if( u8_overflow_off_decision_cnt >= OVERFLOW_LEVEL_DETECT_TIME )
        {
            u8_overflow_off_decision_cnt = OVERFLOW_LEVEL_DETECT_TIME;

            /*..hui [20-9-25오후 5:23:40] 물넘침 한번 감지되면 해제되고 만수위 미만일때까지 기다렸다 해제..*/
            /*..hui [20-9-25오후 5:23:49] 사양 한번 더 확인 필요 꼭~~~~~~~~~..*/
            #if 0
            if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
            {
                bit_overflow_level = CLEAR;
            }
            else{}
            #endif

            bit_overflow_level = CLEAR;
        }
        else{}
    }
    else
    {
        u8_overflow_off_decision_cnt = 0;
        u8_overflow_on_decision_cnt++;

        if ( u8_overflow_on_decision_cnt >= OVERFLOW_LEVEL_DETECT_TIME )
        {
            u8_overflow_on_decision_cnt = OVERFLOW_LEVEL_DETECT_TIME;
            bit_overflow_level = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



