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
#include    "key_input.h"

void Key_Input(void);
void Key_Input_Sampling( U16 u16key_input_value);
void Key_Management( U16 u16key_input_value);
void Key_Short_Input( U16 u16key_input_value );

void Key_1sec_Middle_Input( U16 u16key_input_value);
void Key_2sec_Long_Input( U16 u16key_input_value);

void Key_3sec_Normal_Long_Input( U16 u16key_input_value);
void Key_4sec_Very_Long_Input( U16 u16key_input_value);




U16  gu16_Key_Input;

U16  u16Key_Buffer;

U16  u16Key_Sampling_Counter;
bit F_Key_Short_Push_State;
bit F_Key_Middle_Push_State;
bit F_Key_Long_Push_State;
bit F_Key_Very_Long_Push_State;
bit F_Key_Normal_Long_Push_State;

U8  u8Key_Input_Value;

U16  u16Key_Long_Counter;
U16  u16Key_Short_Counter;
U16 u16LedOutValue;



/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input(void)
{
    gu16_Key_Input = ((U16)( (pKEY_HALF_CUP * 1) + (pKEY_ONE_CUP * 2 ) + (pKEY_TWO_CUP * 4) ) & UControl_Key_Mask);

    /*..hui [19-11-7오전 9:55:18] 초기 키 막음..*/
    if(F_FW_Version_Display_State != SET)
    {
        /*..hui [21-1-7오전 10:53:47] 라인테스트, 디스플레이 테스트 모드는 버전표시중에 버튼 눌리면 바로 진입하도록..*/
        /*..hui [21-1-7오전 10:53:54] 생산 시간 단축.. 생산팀 요청..*/
        if( gu16_Key_Input != LONG_KEY_DISPLAY_TEST_MODE
            && gu16_Key_Input != LONG_KEY_LINE_TEST_MODE_R_TYPE
            && gu16_Key_Input != LONG_KEY_LINE_TEST_MODE_L_TYPE )
        {
            return;
        }
        else{}
    }
    else{}

    Key_Input_Sampling(gu16_Key_Input);
    Key_Management(gu16_Key_Input);

    key_input_water_extract();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Input_Sampling( U16 u16key_input_value)
{
    U8 mu8_filter = 0;

    if(u16key_input_value == u16Key_Buffer)
    {
        if(u16Key_Buffer == UControl_Key_Mask)
        {
            u16Key_Sampling_Counter = 0;
            F_Key_Short_Push_State = CLEAR;
            F_Key_Middle_Push_State = CLEAR;
            F_Key_Long_Push_State = CLEAR;
            F_Key_Very_Long_Push_State = CLEAR;
            F_Key_Normal_Long_Push_State = CLEAR;
        }
        else
        {
            u16Key_Sampling_Counter++;
        }

        if(u16Key_Sampling_Counter >= 10)
        {
            u16Key_Short_Counter = u16Key_Sampling_Counter;
            u16Key_Long_Counter++;
        }
        else{}
    }
    else
    {
        u16Key_Buffer = u16key_input_value;
        u16Key_Sampling_Counter = 0;
        u16Key_Long_Counter = 0;
        u16Key_Short_Counter = 0;

        //F_Key_Short_Push_State = CLEAR;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Management( U16 u16key_input_value)
{
    if(F_Key_Short_Push_State == CLEAR)
    {
        if( (u16Key_Short_Counter >= 80) && (u16Key_Short_Counter < 1000) )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                Key_Short_Input( u16key_input_value );
            }
            else
            {
                Test_Mode_Key_Short_Input( u16key_input_value );
            }

            F_Key_Short_Push_State = SET;
            u16Key_Short_Counter = 0;
        }
        else{}
    }
    else
    {
        if(F_Key_Middle_Push_State == CLEAR)
        {
            if( (u16Key_Long_Counter >= 1000 && u16Key_Long_Counter < 2000) )
            {
                F_Key_Middle_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    Key_1sec_Middle_Input( u16key_input_value );
                }
                else{}
            }
            else{}
        }
        else
        {
            if(F_Key_Long_Push_State == CLEAR)
            {
                if( (u16Key_Long_Counter >= 2000 && u16Key_Long_Counter < 3000) )
                {
                    F_Key_Long_Push_State = SET;

                    if(u8FactoryTestMode == NONE_TEST_MODE)
                    {
                        Key_2sec_Long_Input( u16key_input_value );
                    }
                    else{}
                }
                else{}
            }
            else
            {
                if(F_Key_Normal_Long_Push_State == CLEAR)
                {
                    if( (u16Key_Long_Counter >= 3000 && u16Key_Long_Counter < 5000) )
                    {
                        F_Key_Normal_Long_Push_State = SET;

                        if(u8FactoryTestMode == NONE_TEST_MODE)
                        {
                            Key_3sec_Normal_Long_Input( u16key_input_value );
                        }
                        else{}
                    }
                    else{}
                }
                else
                {
                    if(F_Key_Very_Long_Push_State == CLEAR)
                    {
                        if( u16Key_Long_Counter >= 5000 )
                        {
                            F_Key_Very_Long_Push_State = SET;
                            u16Key_Long_Counter = 0;

                            if(u8FactoryTestMode == NONE_TEST_MODE)
                            {
                                Key_4sec_Very_Long_Input( u16key_input_value );
                            }
                            else{}
                        }
                        else{}
                    }
                    else{}
                }
            }
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_Short_Input( U16 u16key_input_value )
{
    U8 mu8_return = 0;

    switch( u16key_input_value )
    {
        case KEY_HALF_CUP:
            //
            key_cup_select_half();

        break;

        case KEY_ONE_CUP:
            //
            key_cup_select_one();

        break;

        case KEY_TWO_CUP:
            //
            key_cup_select_two();

        break;

        default:
            NOP();
        break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_1sec_Middle_Input( U16 u16key_input_value)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    switch(u16key_input_value)
    {
        //

        default:

            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_2sec_Long_Input( U16 u16key_input_value)
{
    //power_saving_init();

    switch(u16key_input_value)
    {
        //
        case LONG_KEY_PCB_TEST_MODE:
            //
            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0
                && pLEAKAGE_SENSOR == SET
                && pLEVEL_HIGH == CLEAR
                && pLEVEL_OVERFLOW == SET
                && F_Model_Select_Finish == SET )
            {
                main_pba_test_start();
            }
            else
            {
                mute_setting_job();
            }

        break;

        case LONG_KEY_DISPLAY_TEST_MODE:
            //
            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0
                && pLEAKAGE_SENSOR == CLEAR
                && pLEVEL_HIGH == CLEAR
                && pLEVEL_OVERFLOW == CLEAR
                && F_Model_Select_Finish == SET )
            {
                diplay_test_start();
            }
            else{}

        break;

#if 0
#ifdef CONFIG_R_TYPE
        case LONG_KEY_LINE_TEST_MODE_R_TYPE:
#else
        case LONG_KEY_LINE_TEST_MODE_L_TYPE:
#endif
#endif


        case LONG_KEY_LINE_TEST_MODE_R_TYPE:

            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0
                && F_Model_Select_Finish == SET
                && F_Model_Select == MODEL_R_TYPE )
            {
                line_test_start();
            }
            else{}

        break;


        case LONG_KEY_LINE_TEST_MODE_L_TYPE:

            /*..hui [17-12-28오후 10:45:49] Uart 테스트 모드 진입 상태에서는 진입 불가..*/
            /*..hui [19-10-30오전 9:25:44] LCD MAIN화면으로 부팅 완료 후부터 진입 가능..*/
            if( gu8_test_mode_timeout > 0
                && u8FactoryTestMode == 0
                && F_Model_Select_Finish == SET
                && F_Model_Select == MODEL_L_TYPE)
            {
                line_test_start();
            }
            else{}

        break;

        default:

            NOP();
        break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_3sec_Normal_Long_Input( U16 u16key_input_value)
{
    if(F_WaterOut == SET)
    {
        return;
    }
    else{}

    switch(u16key_input_value)
    {
        //
        case KEY_HALF_CUP:
            //
            default_setting_cup_level(CUP_LEVEL_HALF);

        break;

        case KEY_ONE_CUP:
            //
            default_setting_cup_level(CUP_LEVEL_ONE);

        break;

        case KEY_TWO_CUP:
            //
            default_setting_cup_level(CUP_LEVEL_TWO);

        break;

        default:

            NOP();
        break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Key_4sec_Very_Long_Input( U16 u16key_input_value)
{
    switch(u16key_input_value)
    {
        //

        default:

            NOP();
        break;
    }

}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


