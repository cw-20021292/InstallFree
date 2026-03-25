/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : System_init.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#include    "Macrodriver.h"
#include    "Global_Variable.h"
#include    "Port_Define.h"
#include    "M0_System_init.h"


void System_ini(void);
void Ram_Init(void);
void Variable_Init(void);
void system_reset(void);



bit F_PowerOn;

bit F_System_Init_Finish;
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void System_ini(void)
{
    Ram_Init();

    Variable_Init();

    R_TAU0_Channel2_Start();      //timer

    R_INTC4_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Ram_Init(void)
{
    /* ram initialize */
    U32 ram_addr = 0;
    U8 *p_ram_addr = 0;
/*
    for(ram_addr = 0xFCF00; ram_addr < 0xFFC20; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }
*/

    //for(ram_addr = 0xFCF00; ram_addr < 0xFFE20; ram_addr++)
    //for(ram_addr = 0xFCF00; ram_addr < 0xFFE1B; ram_addr++)

    //for(ram_addr = 0xFCF00; ram_addr < 0xFFE00; ram_addr++)
    //for(ram_addr = 0xFF900; ram_addr < 0xFFE0A; ram_addr++)
    //for(ram_addr = 0xFF900; ram_addr < 0xFFEDF; ram_addr++)

    //for(ram_addr = 0xFF900; ram_addr < 0xFFE00; ram_addr++)
    for(ram_addr = 0xFEF00; ram_addr < 0xFFE00; ram_addr++)
    {
        p_ram_addr = (U8 *)ram_addr;
        *p_ram_addr = 0;
    }

}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Variable_Init(void)
{
    BuzStep(BUZZER_POWER_ON);

    Delay_MS( 500 );

    gu8Cup_level = CUP_LEVEL_HALF;
    gu8Cup_level_Default = CUP_LEVEL_HALF;

    gu16_filling_delay_timer = 1800;

    gu8_test_mode_timeout = 30;
    u8FactoryTestMode = NONE_TEST_MODE;
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void system_reset(void)
{
    DI();

    while(1)
    {
        ;
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


