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
#include    "M7_Error_Control.h"


void Error_Control(void);
void error_check(void);
void search_error_code(void);
void error_management(void);



TYPE_LONG       U32ControlErrorsD;
#define         u32ControlErrors                         U32ControlErrorsD.dward
#define         Bit0_Leakage_Sensor_Error                U32ControlErrorsD.Bit.b0    //E01
#define         Bit1_Room_High_Water_Level_Error         U32ControlErrorsD.Bit.b1    //E13
#define         Bit2_Feed_Valve_Error                    U32ControlErrorsD.Bit.b2    //E10

const U8 gu8_error_code[3] = {1, 13, 10};

U8 gu8_Error_Code;
U32 gu32_error_state_old;

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Error_Control(void)
{
    /*..hui [20-2-11오후 5:29:15] 버전 표시 완료후부터 동작하도록..*/
    if( F_FW_Version_Display_State == CLEAR )
    {
        return;
    }
    else{}

    error_check();
    search_error_code();
    error_management();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_check(void)
{
    /*..hui [19-6-26오전 11:36:25] 누수 관련 에러..*/
    check_flow_error();

    /*..hui [19-6-26오전 11:41:48] 수위 관련 에러..*/
    check_error_water_level();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void search_error_code(void)
{
    U8 mu8_error_count = 0;
    U8 mu8_detect_error = 0;

    ////////////////////////////////////////////////////////////////////////////
    /*..hui [20-11-26오후 4:30:54] 에러 1 : 누수센서 에러..*/
    /*..hui [20-11-26오후 4:30:59] 에러 2: 만수위센서 에러..*/
    /*..hui [20-11-26오후 4:31:06] 에러 3 : 피드밸브 에러..*/
    ////////////////////////////////////////////////////////////////////////////

    if(u32ControlErrors > 0)
    {
        for(mu8_error_count = 0; mu8_error_count < MAX_ERROR_NUM; mu8_error_count++)
        {
            mu8_detect_error = (U8)(((U32)(u32ControlErrors) >> mu8_error_count) & 0x01);

            if(mu8_detect_error == 0x01)
            {
                gu8_Error_Code = gu8_error_code[mu8_error_count];
                return;
            }
            else{}
        }
    }
    else
    {
        gu8_Error_Code = 0;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void error_management(void)
{
    ///////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////
    if( gu8_Error_Code != 0 )
    {
        if(u32ControlErrors > gu32_error_state_old)
        {
            /*..hui [19-3-26오전 11:22:16] 에러 걸렸을때 부저음 출력은 안하는걸로..*/
            /*..hui [19-8-2오후 6:40:37] LCD 완성되기전에 에러 발생한지 확인하기위해.....*/
            /*BuzStep(BUZZER_ERROR);*/
            /*gu8_error_popup_enable = SET;*/
        }
        else{}

        gu32_error_state_old = u32ControlErrors;
    }
    else
    {
        gu32_error_state_old = 0;
    }

    /*ErrorSaveStart( gu8_Error_Code );*/
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/



