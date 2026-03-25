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
#include    "Buzzer_output.h"


void BuzStep(U8 mu8Step);
void BuzTimeCounter(void);
void Buz_Start( U16 Buzzer_data );
void Buz_Stop(void);
void BuzControl(void);


bit F_BuzPowOn;
bit F_BuzKey;
bit F_BuzSetup;
bit F_BuzCancel;
bit F_BuzLock;
bit F_BuzIce;
bit F_BuzCont;
bit F_BuzSter;
bit F_BuzWarn;

//----------------------------------------------------// Buzzer
U8 gu8BuzPow;
U8 gu8Pointer;
U16 gu16BuzTime;





U8 gu8Buzzer_Order;
U8 gu8Buzzer_Mode;
U16 gu16Buzzer_Time;


bit F_Mute_Enable;





/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void BuzStep(U8 mu8Step)
{
    gu16Buzzer_Time = 0;
    gu8Buzzer_Order = 1;
    gu8Buzzer_Mode = mu8Step;
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void BuzTimeCounter(void)
{
    if(gu16Buzzer_Time != 0)
    {
        gu16Buzzer_Time--;
    }
    else{}
}
/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void Buz_Start( U16 Buzzer_data )
{
    TDR05 = Buzzer_data;
    R_TAU0_Channel5_Start();
}

/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/
void Buz_Stop(void)
{
    TDR05 = 0;
    R_TAU0_Channel5_Stop();
}


/***********************************************************************************************************************
* Function Name: System_ini
* Description  :
***********************************************************************************************************************/

void BuzControl(void)
{
    if(F_Mute_Enable == CLEAR)
    {
        switch (gu8Buzzer_Mode)
        {
            case BUZZER_OFF:

                 pBUZZER_POWER = OFF;
                 gu16Buzzer_Time = 0;
                 Buz_Stop();
                 break;

            case BUZZER_POWER_ON:

                // Power On ************************************************************
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Si5);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 4;
                }
                if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 19;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Re6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 4;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 19;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 4;
                }
                if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 19;
                }
                if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Pas6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 5;
                }
                if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 65;
                }
                if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Re7);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 2;
                }
                if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 112;
                }
                if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_EFFLUENT:

               // 추출시작음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_EFFLUENT_END:

               // 추출종료음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Pas6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 30;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_COOL_SETUP:

               // 냉각 ON음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Pas6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_COOL_CANCEL:

               // 냉각 OFF음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sols5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Si5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_SELECT:

               // 선택음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 28;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_ERROR:

               // 에러(경고)음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 2;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 28;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 2;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 28;
               }
               if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_MUTE:
            case BUZZER_SETUP:

               // 설정음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sol6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_CANCEL:

               // 해제음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sol6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_EFFLUENT_CONTINUE:

               // 연속추출음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Dos7);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La5);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 12) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 13) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 14) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 15) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La6);
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if ((gu8Buzzer_Order == 16) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 17) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_STERILIZE_START:

               // 살균시작음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Dos6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_STERILIZE_END:

               // 살균종료음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 28;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Dos6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 8;
               }
               if((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 28;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Dos6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 21;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Pas6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 14;
               }
               if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 50;
               }
               if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_AP_CONNECT:

               // AP 접속 성공음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Do6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 40;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_SERVER_CONNECT:

               // 서버 접속 성공음 **********************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)La5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Si5);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 20;
               }
               if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Mi6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 3;
               }
               if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 40;
               }
               if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_MEMENTO_1:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_MEMENTO_2:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_MEMENTO_3:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_MEMENTO_4:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_MEMENTO_5:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            default:

               break;
        }
    }
    else    // 음소거모드 동작
    {
        switch(gu8Buzzer_Mode)
        {
            case BUZZER_MUTE:

               // 설정음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sol6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_SETUP_MUTE:

               // 설정음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sol6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_CANCEL_MUTE:

               // 해제음 **************************************************************
               if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Re7);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 5;
               }
               if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 19;
               }
               if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
               {
                   Buz_Start((U16)Sol6);  //buzzer start
                   pBUZZER_POWER = ON;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 10;
               }
               if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
               {
                   pBUZZER_POWER = OFF;
                   gu8Buzzer_Order++;
                   gu16Buzzer_Time = 38;
               }
               if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
               {
                   gu8Buzzer_Order = 0;
                   gu16Buzzer_Time = 0;
                   gu8Buzzer_Mode = 0;
                   Buz_Stop();
               }
               break;

            case BUZZER_MEMENTO_1_MUTE:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;

            case BUZZER_MEMENTO_5_MUTE:
                if ((gu8Buzzer_Order == 1) && (gu16Buzzer_Time == 0))
                {
                    Buz_Start((U16)Sol6);  //buzzer start
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 2) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 3) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 4) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 5) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 6) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 7) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 8) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 10;
                }
                if ((gu8Buzzer_Order == 9) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = ON;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 6;
                }
                if ((gu8Buzzer_Order == 10) && (gu16Buzzer_Time == 0))
                {
                    pBUZZER_POWER = OFF;
                    gu8Buzzer_Order++;
                    gu16Buzzer_Time = 50;
                }
                if ((gu8Buzzer_Order == 11) && (gu16Buzzer_Time == 0))
                {
                    gu8Buzzer_Order = 0;
                    gu16Buzzer_Time = 0;
                    gu8Buzzer_Mode = 0;
                    Buz_Stop();
                }
                break;


            default:

                pBUZZER_POWER = OFF;
                gu8Buzzer_Order = 0;
                gu16Buzzer_Time = 0;
                gu8Buzzer_Mode = 0;
                Buz_Stop();

                break;
        }
    }
}









