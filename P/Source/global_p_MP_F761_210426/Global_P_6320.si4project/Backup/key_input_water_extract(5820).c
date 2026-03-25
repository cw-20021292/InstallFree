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
#include    "key_input_water_extract.h"

void input_water_extract_key(void);
void extract_key_management(void);

void Extract_Key_Short_Input(void);
void water_extract_key(void);
void effluent_time_decision(void);
void Extract_Key_Long_Input(void);

void water_extract_long_key(void);

void key_input_water_extract(void);
void Extract_Key_Very_Long_Input(void);

U8 u8Extract_Key_Input;
U8 gu8_Key_Water_Extract;
U8 u8Extract_Key_Buffer;
U16 u16Extract_Key_Sampling_Counter;
bit F_Extract_Key_Short_Push_State;
bit F_Extract_Key_Long_Push_State;
bit F_Extract_Key_Very_Long_Push_State;

U16 u16Extract_Key_Long_Counter;
U16 u16Extract_Key_Short_Counter;

U8  u8Extract_Continue;
U16 u16Efluent_Time;


U16 gu16Water_Extract_Timer;
bit F_WaterOut;
//bit F_Effluent_OK;
//bit F_LineTest;
bit F_All_Lock;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void key_input_water_extract(void)
{
    input_water_extract_key();
    extract_key_management();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void input_water_extract_key(void)
{
    gu8_Key_Water_Extract = ((U8)((pKEY_EXTRACT * 1) & UExtract_Key_Mask));


    if(gu8_Key_Water_Extract == u8Extract_Key_Buffer)
    {
        if(u8Extract_Key_Buffer == UExtract_Key_Mask)
        {
            u16Extract_Key_Sampling_Counter = 0;
            F_Extract_Key_Short_Push_State = CLEAR;
            F_Extract_Key_Long_Push_State = CLEAR;
            F_Extract_Key_Very_Long_Push_State = CLEAR;
        }
        else
        {
            u16Extract_Key_Sampling_Counter++;
        }

        if(u16Extract_Key_Sampling_Counter >= 10)
        {
            u16Extract_Key_Short_Counter = u16Extract_Key_Sampling_Counter;
            u16Extract_Key_Long_Counter++;
        }
        else{}
    }
    else
    {
        u8Extract_Key_Buffer = gu8_Key_Water_Extract;

        u16Extract_Key_Sampling_Counter = 0;
        u16Extract_Key_Long_Counter = 0;
        u16Extract_Key_Short_Counter = 0;
    }
}
/***********************************************************************************************************************/

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void extract_key_management(void)
{
    if(F_Extract_Key_Short_Push_State == CLEAR)
    {
        if( (u16Extract_Key_Short_Counter >= 80) && (u16Extract_Key_Short_Counter < 2000) )
        {
            if(u8FactoryTestMode == NONE_TEST_MODE)
            {
                Extract_Key_Short_Input();
            }
            else
            {
                Test_Mode_Extract_Key_Short_Input();
            }

            F_Extract_Key_Short_Push_State = SET;
            u16Extract_Key_Short_Counter = 0;
        }
        else{}
    }
    else
    {
        if(F_Extract_Key_Long_Push_State == CLEAR)
        {
            if( u16Extract_Key_Long_Counter >= 2000 )
            {
                F_Extract_Key_Long_Push_State = SET;

                if(u8FactoryTestMode == NONE_TEST_MODE)
                {
                    Extract_Key_Long_Input();
                }
                else{}
            }
            else{}
        }
        else
        {
            if(F_Extract_Key_Very_Long_Push_State == CLEAR)
            {
                if( u16Extract_Key_Long_Counter >= 8000 )
                {
                    F_Extract_Key_Very_Long_Push_State = SET;
                    u16Extract_Key_Long_Counter = 0;

                    Extract_Key_Very_Long_Input();
                }
                else{}
            }
            else{}
        }
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Short_Input(void)
{
    water_extract_key();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_key(void)
{
    if(F_All_Lock == SET)
    {
        return;
    }
    else{}

    /*..hui [18-3-14오후 3:07:31] 정량추출 완료되고 500ms 동안 물 추출 버튼 disable..*/
    if(F_WaterOut_Disable_State == SET)
    {
        return;
    }
    else{}

    if( F_WaterOut == CLEAR )
    {
        F_WaterOut = SET;
        BuzStep(BUZZER_EFFLUENT);
    }
    else
    {
        F_WaterOut = CLEAR;
        u8Extract_Continue = CLEAR;
        BuzStep(BUZZER_EFFLUENT_END);
    }

    if(F_WaterOut == SET)
    {
        effluent_time_decision();
    }
    else
    {
        u16Efluent_Time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void effluent_time_decision(void)
{
    /*..hui [20-12-14오전 10:53:17] R타입은 250/500/1000, L타입은 120/250/500..*/
    switch(gu8Cup_level)
    {
        case CUP_LEVEL_HALF:

            if( F_Model_Select == MODEL_R_TYPE )
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_ONE;
            }
            else
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_HALF;
            }

            break;

        case CUP_LEVEL_ONE:

            if( F_Model_Select == MODEL_R_TYPE )
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_TWO;
            }
            else
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_ONE;
            }

            break;

        case CUP_LEVEL_TWO:

            if( F_Model_Select == MODEL_R_TYPE )
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_1LITER;
            }
            else
            {
                u16Efluent_Time = EXTRACT_TIME_PURE_WATER_TWO;
            }

            break;

        default:

            u16Efluent_Time = EXTRACT_TIME_PURE_WATER_HALF;

            break;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Long_Input(void)
{
    /*..hui [19-9-25오전 9:41:46] 연속 추출이 메뉴속으로..*/
    /*..hui [19-11-8오후 12:50:23] 다시 추가.. 없으니까 넘 불편..*/
    water_extract_long_key();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void water_extract_long_key(void)
{
    if( F_WaterOut == SET )
    {
        u16Efluent_Time = EXTRACT_TIME_CONTINUE;
        BuzStep(BUZZER_EFFLUENT_CONTINUE);
        u8Extract_Continue = SET;
    }
    else
    {
        u16Efluent_Time = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Extract_Key_Very_Long_Input(void)
{
    if( F_WaterOut == SET )
    {
        /*..hui [19-11-18오후 1:36:04] 7초 이상 추출키 눌려있을경우 즉시 추출 종료..*/
        gu16Water_Extract_Timer = u16Efluent_Time;
    }
    else{}
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


