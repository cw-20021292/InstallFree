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
#include    "error_leakage.h"

void check_flow_error(void);
void check_error_leakage_sensor(void);
void check_error_flow_block(void);

U8 u8_leakage_on_decision_cnt;
U8 u8_leakage_off_decision_cnt;

U16 gu16_flow_block_check_timer;
U16 gu16_flow_block_clear_timer;

bit F_Flow_Block_State;

U16 gu16_flow_check_delay_timer;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_flow_error(void)
{
    /*..hui [18-11-22오후 3:36:39] 누수 센서 에러..*/
    check_error_leakage_sensor();

    if( F_Model_Select == MODEL_R_TYPE )
    {
        check_error_flow_block();
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_leakage_sensor(void)
{
    if( pLEAKAGE_SENSOR == CLEAR )
    {
        u8_leakage_on_decision_cnt = 0;
        u8_leakage_off_decision_cnt++;

        if( u8_leakage_off_decision_cnt >= LEAKAGE_ERROR_CLEAR_TIME )
        {
            u8_leakage_off_decision_cnt = LEAKAGE_ERROR_CLEAR_TIME;
            Bit0_Leakage_Sensor_Error = CLEAR;
        }
        else{}
    }
    else
    {
        u8_leakage_off_decision_cnt = 0;
        u8_leakage_on_decision_cnt++;

        if( u8_leakage_on_decision_cnt >= LEAKAGE_ERROR_DETECT_TIME )
        {
            u8_leakage_on_decision_cnt = LEAKAGE_ERROR_DETECT_TIME;
            Bit0_Leakage_Sensor_Error = SET;
        }
        else{}
    }


}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void check_error_flow_block(void)
{
    U8 u8_check_enable = CLEAR;
    U8 u8_block_error_fix = CLEAR;
    U16 mu16_err_check_time = 0;
    U8 mu8_err_check_hz = 0;
    U16 mu16_err_clear_time = 0;

    if( bit_pump_output == SET  )
    {
        gu16_flow_check_delay_timer++;

        /*..hui [20-12-15오후 3:02:40] 초기 전원 인가 후 2분 동안은 감지하지 않는다..*/
        if( gu16_flow_check_delay_timer >= FLOW_CHECK_DELAY_TIME )
        {
            gu16_flow_check_delay_timer = FLOW_CHECK_DELAY_TIME;

            u8_check_enable = SET;
            mu16_err_check_time = 600;
            mu16_err_clear_time = 300;
            mu8_err_check_hz = BLOCKED_FLOW_HZ;
        }
        else{}
    }
    else{}

    if( u8_check_enable == SET )
    {
        /*..hui [19-8-28오후 7:15:10] 5Hz 이하일 경우..*/
        if( gu8_Flow_1sec <= mu8_err_check_hz )
        {
            gu16_flow_block_clear_timer = 0;
            gu16_flow_block_check_timer++;

            if( gu16_flow_block_check_timer >= mu16_err_check_time )
            {
                F_Flow_Block_State = SET;
                gu16_flow_block_check_timer = mu16_err_check_time;
            }
            else{}
        }
        else
        {
            gu16_flow_block_check_timer = 0;
            gu16_flow_block_clear_timer++;

            if( gu16_flow_block_clear_timer >= mu16_err_clear_time )
            {
                F_Flow_Block_State = CLEAR;
                gu16_flow_block_clear_timer = mu16_err_clear_time;
            }
            else{}
        }
    }
    else
    {
        gu16_flow_block_check_timer = 0;
        gu16_flow_block_clear_timer = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/




