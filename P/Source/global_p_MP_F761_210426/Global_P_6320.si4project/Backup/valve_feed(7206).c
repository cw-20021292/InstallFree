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
#include    "valve_feed.h"

void output_valve_feed(void);


/***********************************************************************************************************************/
TYPE_BYTE          U8FeedValveONB;
#define            u8FeedValveON                             U8FeedValveONB.byte
#define            Bit0_FV_Low_Water_Filling_State           U8FeedValveONB.Bit.b0




TYPE_BYTE          U8FeedValveOFFB;
#define            u8FeedValveOFF                            U8FeedValveOFFB.byte
#define            Bit0_FV_Water_Level_Error_Off_State       U8FeedValveOFFB.Bit.b0
#define            Bit1_FV_Overflow_Off_State                U8FeedValveOFFB.Bit.b1


/***********************************************************************************************************************/
bit bit_feed_output;

bit bit_before_level;
U16 gu16_filling_delay_timer;

U16 gu16_feed_off_delay_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_valve_feed(void)
{
/***********************************************************************************************/
/**********************************************on***********************************************/

    if( gu8_Room_Water_Level == ROOM_LEVEL_LOW )
    {
        #if 0
        if( F_Model_Select == MODEL_R_TYPE )
        {
            gu16_filling_delay_timer++;
        }
        else
        {
            /*..hui [21-3-4오전 9:30:20] L 타입은 즉시 재정수..*/
            /*..hui [21-3-4오전 9:30:27] 필드테스트 내용..*/
            gu16_filling_delay_timer = ROOM_FILLING_DELAY_TIME;
        }

        /*..hui [20-11-20오후 3:47:31] 만수위 -> 저수위시 3분간 지연 후 입수..*/
        /*..hui [20-11-20오후 3:47:46] 사용자 물 먹은 후 펌프 가동 소리에 놀랄 수 있음.. 신뢰성 요청..*/
        if( gu16_filling_delay_timer >= ROOM_FILLING_DELAY_TIME )
        {
            gu16_filling_delay_timer = ROOM_FILLING_DELAY_TIME;
            Bit0_FV_Low_Water_Filling_State = SET;
        }
        else{}
        #endif

        Bit0_FV_Low_Water_Filling_State = SET;
    }
    else
    {
        Bit0_FV_Low_Water_Filling_State = CLEAR;
        gu16_filling_delay_timer = 0;
    }


/***********************************************************************************************/
/**********************************************off**********************************************/

    if( Bit0_Leakage_Sensor_Error == SET
        || Bit1_Room_High_Water_Level_Error == SET
        || Bit2_Feed_Valve_Error == SET )
    {
        Bit0_FV_Water_Level_Error_Off_State = SET;
    }
    else
    {
        Bit0_FV_Water_Level_Error_Off_State = CLEAR;
    }

    Bit1_FV_Overflow_Off_State = F_Err_OVF_Check;

/***********************************************************************************************/
    if (u8FeedValveOFF > 0)             /*off*/
    {
        if( gu16_feed_off_delay_timer >= FEED_OFF_DELAY_TIME )
        {
            pVALVE_FEED = CLEAR;
        }
        else{}

        bit_feed_output = CLEAR;
    }
    else
    {
        if (u8FeedValveON > 0)          /*on*/
        {
            pVALVE_FEED = SET;
            bit_feed_output = SET;
        }
        else                             /*off*/
        {
            if( gu16_feed_off_delay_timer >= FEED_OFF_DELAY_TIME )
            {
                pVALVE_FEED = CLEAR;
            }
            else{}

            bit_feed_output = CLEAR;
        }
    }

    if( F_Model_Select == MODEL_R_TYPE )
    {
        if( bit_feed_output == CLEAR )
        {
            gu16_feed_off_delay_timer++;

            if( gu16_feed_off_delay_timer >= FEED_OFF_DELAY_TIME )
            {
                gu16_feed_off_delay_timer = FEED_OFF_DELAY_TIME;
            }
            else{}
        }
        else
        {
            gu16_feed_off_delay_timer = 0;
        }
    }
    else
    {
        gu16_feed_off_delay_timer = FEED_OFF_DELAY_TIME;
    }
/***********************************************************************************************/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



