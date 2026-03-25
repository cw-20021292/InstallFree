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
#include    "test_main.h"

void Test_Mode_Main(void);
void main_pba_test_start(void);
void Test_Mode_Key_Short_Input( U16 u16key_input_value);
void Test_Mode_Extract_Key_Short_Input(void);
void Test_NO_LOAD_Set(void);
void diplay_test_start(void);
void line_test_start(void);


TYPE_BYTE          U8FactoryTestModeB;
#define            u8FactoryTestMode                 U8FactoryTestModeB.byte
#define            Bit0_Pcb_Test_Mode                U8FactoryTestModeB.Bit.b0
#define            Bit1_Line_Test_Mode               U8FactoryTestModeB.Bit.b1
#define            Bit2_Display_Test_Mode            U8FactoryTestModeB.Bit.b2

U8 gu8_test_mode_timeout;

U8 gu8_half_cup_test_input;
U8 gu8_one_cup_test_input;
U8 gu8_two_cup_test_input;
U8 gu8_water_ext_test_input;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Test_Mode_Main(void)
{
    if(u8FactoryTestMode == PCB_TEST_MODE)
    {
        /*..hui [20-12-17오전 11:39:59] PCB 업체 메인 PBA 검사..*/
        Pcb_Test_Main();
    }
    else if(u8FactoryTestMode == DISPLAY_TEST_MODE)
    {
        /*..hui [20-12-17오전 11:40:14] 공장 라인 디스플레이 검사..*/
        Display_Test_Main();
    }
    else /*if(u8FactoryTestMode == LINE_TEST_MODE)*/
    {
        /*..hui [20-12-17오전 11:40:20] 공장 라인 제품 검사..*/
        Line_Test_Main();
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void main_pba_test_start(void)
{
    gu8_test_mode_timeout = 0;
    off_all_control_led();

    u8FactoryTestMode = PCB_TEST_MODE;
    Test_NO_LOAD_Set();

    F_FW_Version_Display_State = CLEAR;
    gu8_led_version_step = 1;
    gu8_version_display_Timer = 0;

    BuzStep(BUZZER_COOL_SETUP);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void diplay_test_start(void)
{
    gu8_test_mode_timeout = 0;
    off_all_control_led();

    u8FactoryTestMode = DISPLAY_TEST_MODE;
    Test_NO_LOAD_Set();

    F_FW_Version_Display_State = CLEAR;
    gu8_led_version_step = 1;
    gu8_version_display_Timer = 0;

    BuzStep(BUZZER_SELECT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void line_test_start(void)
{
    gu8_test_mode_timeout = 0;
    off_all_control_led();

    u8FactoryTestMode = LINE_TEST_MODE;
    Test_NO_LOAD_Set();

    F_FW_Version_Display_State = CLEAR;
    gu8_led_version_step = 1;
    gu8_version_display_Timer = 0;

    gu8T300ms = 0;
    gu8T500ms = 0;
    gu8T1000ms = 0;

    BuzStep(BUZZER_COOL_SETUP);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Test_Mode_Key_Short_Input( U16 u16key_input_value)
{
    U8 mu8_return = 0;

    switch(u16key_input_value)
    {
        /*..hui [19-7-18오전 10:49:52] 물량 선택..*/
        case KEY_HALF_CUP:
            //
             gu8_half_cup_test_input++;

             if(gu8_half_cup_test_input >= 2)
             {
                 gu8_half_cup_test_input = 0;
             }
             else{}

             BuzStep(BUZZER_SELECT);

        break;

        /*..hui [19-7-18오전 10:49:57] 냉수 선택..*/
        case KEY_ONE_CUP:
            //
             gu8_one_cup_test_input++;

             if(gu8_one_cup_test_input >= 2)
             {
                 gu8_one_cup_test_input = 0;
             }
             else{}

             BuzStep(BUZZER_SELECT);


        break;

        /*..hui [19-7-18오전 10:50:03] 정수 선택..*/
        case KEY_TWO_CUP:
            //
             gu8_two_cup_test_input++;

             if(gu8_two_cup_test_input >= 2)
             {
                 gu8_two_cup_test_input = 0;
             }
             else{}

             BuzStep(BUZZER_SELECT);


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
void Test_Mode_Extract_Key_Short_Input(void)
{
     gu8_water_ext_test_input++;

     if(gu8_water_ext_test_input >= 2)
     {
         gu8_water_ext_test_input = 0;
     }
     else{}

     BuzStep(BUZZER_SELECT);
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Test_NO_LOAD_Set(void)
{
    pVALVE_FEED = CLEAR;
    pVALVE_NOS = CLEAR;
    pVALVE_EXTRACT = CLEAR;

    pPUMP_R_TYPE = CLEAR;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

