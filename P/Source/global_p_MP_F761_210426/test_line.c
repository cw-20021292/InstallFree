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
#include    "test_line.h"


void Line_Test_Main(void);
void line_test_job(void);


U8 gu8_line_test_step;
U16 gu16_line_test_timer;
U8 u8_flow_line_test;
U16 gu16_flow_fail_teimr;
U16 gu17_flow_test_timer;
U8 gu8_line_test_step_old;
U8 gu8_step_change_timer;
bit bit_step_change;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Line_Test_Main(void)
{
    if(F_FW_Version_Display_State != SET)
    {
        display_version();
    }
    else
    {
        line_test_job();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void line_test_job(void)
{
    led_blink_timer();

    if( bit_step_change == SET )
    {
        Bit3_Extract_Led_White ^= 1;

        gu8_step_change_timer++;

        if( gu8_step_change_timer >= 15 )
        {
            gu8_step_change_timer = 0;
            bit_step_change = CLEAR;
        }
        else{}
    }
    else
    {
        Bit3_Extract_Led_White = F_Wink_500ms;
        gu8_step_change_timer = 0;
    }

    switch( gu8_line_test_step )
    {
        case 0:

            gu16_line_test_timer++;

            if( gu16_line_test_timer >= 10 )
            {
                Test_NO_LOAD_Set();
                gu16_line_test_timer = 0;
                gu8_line_test_step++;
            }
            else{}

        break;

        case 1:

            if( pLEVEL_HIGH == SET )
            {
                Bit0_Half_Cup_Led_White = F_Wink_500ms;
            }
            else
            {
                Bit0_Half_Cup_Led_White = 1;
            }

            if( pLEVEL_OVERFLOW == SET )
            {
                Bit1_One_Cup_Led_White = F_Wink_500ms;
            }
            else
            {
                Bit1_One_Cup_Led_White = 1;
            }

            if( pLEVEL_HIGH == CLEAR
                && pLEVEL_OVERFLOW == CLEAR
                && pLEAKAGE_SENSOR == SET )
            {
                gu16_line_test_timer = 0;
                gu8_line_test_step++;
                gu8_water_ext_test_input = 0;
                bit_step_change = SET;
                BuzStep(BUZZER_SELECT);
            }
            else{}

            pVALVE_EXTRACT = CLEAR;
            pVALVE_NOS = SET;
            pVALVE_FEED = CLEAR;

        break;

        case 2:

            pVALVE_EXTRACT = CLEAR;
            pVALVE_NOS = SET;
            pVALVE_FEED = CLEAR;

            /*if( pKEY_EXTRACT == CLEAR )*/
            if( gu8_water_ext_test_input == 1 )
            {
                gu16_line_test_timer = 0;
                gu8_line_test_step++;
                gu8_two_cup_test_input = 0;
                bit_step_change = SET;
                //BuzStep(BUZZER_SELECT);
            }
            else
            {
                gu16_line_test_timer = 0;
            }

        break;

        case 3:

            pVALVE_EXTRACT = SET;
            pVALVE_NOS = SET;
            pVALVE_FEED = CLEAR;

            /*if( pKEY_TWO_CUP == CLEAR )*/
            if( gu8_two_cup_test_input == 1 )
            {
                gu16_line_test_timer = 0;
                gu8_line_test_step++;
                gu17_flow_test_timer = 0;
                gu16_flow_fail_teimr = 0;
                bit_step_change = SET;
                //BuzStep(BUZZER_SELECT);
            }
            else
            {
                gu16_line_test_timer = 0;
            }

        break;

        case 4:

            /*..hui [21-4-26오후 2:22:30] R타입은 전류가 낮아서 검사가 안됨.. 밸브 2개 켠 상태 유지.. 전류 상승 확인..*/
            /*..hui [21-4-26오후 2:22:33] 설희석 차장님 요청..*/
            if( F_Model_Select == MODEL_R_TYPE )
            {
                pVALVE_EXTRACT = SET;
            }
            else
            {
                pVALVE_EXTRACT = CLEAR;
            }

            pVALVE_NOS = CLEAR;
            pVALVE_FEED = SET;

            if( F_Model_Select == MODEL_R_TYPE )
            {
                pPUMP_R_TYPE = 1;
                gu8_line_test_step++;

                #if 0
                calculate_flow_input();

                if( gu8_Flow_1sec > 5 )
                {
                    gu17_flow_test_timer++;

                    if( gu17_flow_test_timer >= 10 )
                    {
                        u8_flow_line_test = 1;
                        gu8_line_test_step++;
                        BuzStep(BUZZER_SELECT);
                    }
                    else{}
                }
                else
                {
                    gu17_flow_test_timer = 0;

                    gu16_flow_fail_teimr++;

                    if( gu16_flow_fail_teimr >= 100 )
                    {
                        u8_flow_line_test = 2;
                        gu8_line_test_step++;
                        BuzStep(BUZZER_ERROR);
                    }
                    else{}
                }
                #endif
            }
            else
            {
                /*..hui [20-12-17오후 7:19:55] L 타입은 점등상태로 유지..*/
                gu8_line_test_step++;
            }

        break;

        case 5:

            if( F_Model_Select == MODEL_R_TYPE )
            {
                #if 0
                if( u8_flow_line_test == 1 )
                {
                    Bit2_Two_Cup_Led_White = 1;
                    pPUMP_R_TYPE = 1;
                }
                else if( u8_flow_line_test == 2 )
                {
                    Bit2_Two_Cup_Led_White = F_Wink_500ms;
                    pPUMP_R_TYPE = 0;
                }
                else
                {
                    Bit2_Two_Cup_Led_White = 0;
                    pPUMP_R_TYPE = 0;
                }
                #endif

                Bit2_Two_Cup_Led_White = 1;
                pPUMP_R_TYPE = 1;
            }
            else
            {
                /*..hui [20-12-17오후 7:19:55] L 타입은 점등상태로 유지..*/
                Bit2_Two_Cup_Led_White = 1;
            }

        break;

        default:

            gu8_line_test_step = 0;
            gu16_line_test_timer = 0;

        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


