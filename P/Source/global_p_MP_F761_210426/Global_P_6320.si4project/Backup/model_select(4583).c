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
#include    "model_select.h"


void model_select(void);




U8 gu8_R_type_select_timer;
U8 gu8_L_type_select_timer;

MODEL_SELECT F_Model_Select;
bit F_Model_Select_Finish;





U16 U16_KEY_SETTING;
U16 U16_KEY_REDO;
U16 U16_KEY_LEFT_MOVE;
U16 U16_KEY_RIGHT_MOVE;
U16 U16_KEY_CUP_SELECT;
U16 U16_KEY_COLD_SELECT;
U16 U16_KEY_PRUTIFY_SELECT;
U16 U16_KEY_HOT_SELECT;
U16 U16_KEY_USER_SELECT;
U16 U16_KEY_ALL_LOCK;


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void model_select(void)
{
    //F_Model_Select = MODEL_L_TYPE;
    //F_Model_Select = MODEL_R_TYPE;
    //F_Model_Select_Finish = SET;

    if(F_Model_Select_Finish == SET)
    {
        return;
    }
    else{}

    if(pMODEL_SELECT == SET)
    {
        gu8_L_type_select_timer = 0;
        gu8_R_type_select_timer++;

        if(gu8_R_type_select_timer >= MODEL_SELECT_TIME)
        {
            gu8_R_type_select_timer = MODEL_SELECT_TIME;
            F_Model_Select = MODEL_R_TYPE;
            F_Model_Select_Finish = SET;
        }
        else{}
    }
    else
    {
        gu8_R_type_select_timer = 0;
        gu8_L_type_select_timer++;

        if(gu8_L_type_select_timer >= MODEL_SELECT_TIME)
        {
            gu8_L_type_select_timer = MODEL_SELECT_TIME;
            F_Model_Select = MODEL_L_TYPE;
            F_Model_Select_Finish = SET;
        }
        else{}
    }
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/


