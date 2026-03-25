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
#include    "pump_r_type.h"


void output_pump(void);
/*U8 pump_retry_proc( U8 mu8_flow_block );*/
U8 pump_retry_proc( void );
void start_boost_pump( U16 u16_data );
void stop_boost_pump( void );


/***********************************************************************************************************************/
TYPE_BYTE          U8PumpONB;
#define            u8PumpON                               U8PumpONB.byte
#define            Bit0_Pump_Feed_Operation_State         U8PumpONB.Bit.b0




TYPE_BYTE          U8PumpOFFB;
#define            u8PumpOFF                              U8PumpOFFB.byte
#define            Bit0_Water_Level_Error_Off_State       U8PumpOFFB.Bit.b0
#define            Bit1_FV_Hot_Cooling_Off_State          U8PumpOFFB.Bit.b1
#define            Bit2_Overflow_Off_State                U8PumpOFFB.Bit.b2
#define            Bit3_Tray_Water_Input_State            U8PumpOFFB.Bit.b3
#define            Bit4_System_Init_State                 U8PumpOFFB.Bit.b4
#define            Bit5_Hot_Drain_Off_State               U8PumpOFFB.Bit.b5
#define            Bit6_Drain_Operation_Off_State         U8PumpOFFB.Bit.b6
#define            Bit7_Hot_Filling_Off_State             U8PumpOFFB.Bit.b7

bit bit_pump_output;
U8 gu8_pump_delay_timer;

PUMP_RETRY_STEP gu8_pump_retry_step;
U32 gu32_pump_retry_timer;

U16 gu16_current_pump_pwm;

/***********************************************************************************************************************/



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void output_pump(void)
{
    /*..hui [20-9-25오후 5:39:12] 피드밸브 동작중에 같이 동작..*/
    if( bit_feed_output == SET )
    {
        gu8_pump_delay_timer++;

        if( gu8_pump_delay_timer >= PUMP_DELAY_TIME )
        {
            gu8_pump_delay_timer = PUMP_DELAY_TIME;
            /*Bit0_Pump_Feed_Operation_State = bit_feed_output;*/

            /*Bit0_Pump_Feed_Operation_State = pump_retry_proc( (U8)F_Flow_Block_State );*/
            /*Bit0_Pump_Feed_Operation_State = pump_retry_proc();*/
            Bit0_Pump_Feed_Operation_State = SET;
        }
        else{}
    }
    else
    {
        gu8_pump_delay_timer = 0;
        Bit0_Pump_Feed_Operation_State = CLEAR;
        /*gu8_pump_retry_step = STEP0_STANDBY;*/
    }


/***********************************************************************************************/
    if (u8PumpOFF > 0)
    {
        pPUMP_R_TYPE = CLEAR;      /*off*/
        bit_pump_output = CLEAR;
    }
    else
    {
        if (u8PumpON > 0)
        {
            pPUMP_R_TYPE = SET;    /*on*/
            bit_pump_output = SET;
        }
        else
        {
            pPUMP_R_TYPE = CLEAR;  /*off*/
            bit_pump_output = CLEAR;
        }
    }
/***********************************************************************************************/

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
U8 pump_retry_proc( void )
{
    U8 mu8_return = 0;

    /*..hui [21-4-20오후 12:58:42] 펌프쪽에서 피드밸브 쪽으로 함수 호출 이동되면서 추가..*/
    if( Bit0_Leakage_Sensor_Error == SET
        || Bit1_Room_High_Water_Level_Error == SET
        || Bit2_Feed_Valve_Error == SET
        || F_Err_OVF_Check == SET )
    {
        gu8_pump_retry_step = STEP0_STANDBY;
        gu32_pump_retry_timer = 0;

        return mu8_return;
    }
    else{}

    switch( gu8_pump_retry_step )
    {
        case STEP0_STANDBY:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = STEP1_160MIN_ON;
            mu8_return = SET;

        break;

        case STEP1_160MIN_ON:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_ON_160MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP2_20MIN_OFF;
            }
            else
            {
                mu8_return = SET;
            }

        break;

        case STEP2_20MIN_OFF:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_OFF_20MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP1_160MIN_ON;
            }
            else{}

        break;

        default:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = 0;

        break;
    }

    return mu8_return;
}



#if 0
U8 pump_retry_proc( U8 mu8_flow_block )
{
    U8 mu8_return = 0;

    /*..hui [20-12-15오후 5:17:48] 유량센서 정상 감지될 경우 정상 동작..*/
    if( mu8_flow_block == CLEAR )
    {
        gu8_pump_retry_step = STEP0_STANDBY;
        gu32_pump_retry_timer = 0;
        mu8_return = SET;

        return mu8_return;
    }
    else{}

    switch( gu8_pump_retry_step )
    {
        case STEP0_STANDBY:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = STEP1_120MIN_ON;
            mu8_return = SET;

        break;

        case STEP1_120MIN_ON:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_ON_120MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP2_20MIN_OFF;
            }
            else
            {
                mu8_return = SET;
            }

        break;

        case STEP2_20MIN_OFF:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_OFF_20MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP3_120MIN_ON;
            }
            else{}

        break;

        case STEP3_120MIN_ON:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_ON_120MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP4_120MIN_OFF;
            }
            else
            {
                mu8_return = SET;
            }

        break;

        case STEP4_120MIN_OFF:

            gu32_pump_retry_timer++;

            if( gu32_pump_retry_timer >= PUMP_OFF_120MIN )
            {
                gu32_pump_retry_timer = 0;
                gu8_pump_retry_step = STEP3_120MIN_ON;
            }
            else{}

        break;

        default:

            gu32_pump_retry_timer = 0;
            gu8_pump_retry_step = 0;

        break;
    }

    return mu8_return;
}
#endif

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void start_boost_pump( U16 u16_data )
{
    //R_TAU0_Channel0_Start();
    //TDR01 = u16_data;
    //gu16_current_pump_pwm = u16_data;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void stop_boost_pump( void )
{
    //R_TAU0_Channel0_Stop();
    //TDR01 = 0;
    //gu16_current_pump_pwm = 0;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


