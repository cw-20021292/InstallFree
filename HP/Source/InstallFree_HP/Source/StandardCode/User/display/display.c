#include "Global_Header.h"

#include "hal_led.h"
#include "display.h"
#include "display_lib.h"
#include "water_out.h"
#include "hot_water.h"
#include "amount.h"
#include "hot_water_out.h"
#include "water_out_type.h"

#define AmountDispStep1      0
#define AmountDispStep2      1
#define AmountDispStep3      2
#define AmountDispStep4      3
#define AmountDispInfinity   4

#define PROGRESS_75PERCENT    75
#define PROGRESS_50PERCENT    50
#define PROGRESS_25PERCENT    25

#define BAR4_DISPLAY_500MS    50   

#define AMOUNT_STEP_MAX      5

void DispSegmentHour(U16 mu16Val)
{
    U8 mu8Val_1000;
    U8 mu8Val_100;

    mu8Val_1000   = (U8)((mu16Val % 100) / 10);   
    mu8Val_100    = (U8)((mu16Val % 10));  

    if( mu8Val_1000 == 1 )
    {
        // HAL_TurnOnOffSeg( SEG4, gu8Digit[ mu8Val_1000 ], SEG_ON );
    }
    else
    {
        // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    }

    // HAL_TurnOnOffSeg( SEG3, gu8Digit[ mu8Val_100 ], SEG_ON );
}

void DispSegmentMin(U16 mu16Val)
{
    U8 mu8Val_10;
    U8 mu8Val_1;

    mu8Val_10   = (U8)((mu16Val % 100) / 10);   
    mu8Val_1    = (U8)((mu16Val % 10));  

    if( mu8Val_10 > 0 )
    {
        // HAL_TurnOnOffSeg( SEG2, gu8Digit[ mu8Val_10 ], SEG_ON );
    }
    else
    {
        // HAL_TurnOnOffSeg( SEG2, PROTOCOL_SEG_LED_DATA_0, SEG_ON );
    }

    // HAL_TurnOnOffSeg( SEG1, gu8Digit[ mu8Val_1 ], SEG_ON );
}


void DispSegmentDigit(U16 mu16Val)
{
    U8 mu8Val_1000;
    U8 mu8Val_100;
    U8 mu8Val_10;
    U8 mu8Val_1;

    mu8Val_1000 = (U8)(mu16Val / 1000);
    mu8Val_100  = (U8)((mu16Val % 1000) / 100); 
    mu8Val_10   = (U8)((mu16Val % 100) / 10);   
    mu8Val_1    = (U8)((mu16Val % 10));  

    if( mu8Val_1000 > 0 )
    {
        // HAL_TurnOnOffSeg( SEG4, gu8Digit[ mu8Val_1000 ], SEG_ON );
    }
    else
    {
        // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    }

    if( mu8Val_100 > 0 || mu8Val_1000 > 0)
    {
        // HAL_TurnOnOffSeg( SEG3, gu8Digit[ mu8Val_100 ], SEG_ON );
    }
    else
    {
        // HAL_TurnOnOffSeg( SEG3, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    }

    if( mu8Val_10 > 0 || mu8Val_100 > 0 || mu8Val_1000 > 0 )
    {
        // HAL_TurnOnOffSeg( SEG2, gu8Digit[ mu8Val_10 ], SEG_ON );
    }
    else
    {
        // HAL_TurnOnOffSeg( SEG2, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    }

    // HAL_TurnOnOffSeg( SEG1, gu8Digit[ mu8Val_1 ], SEG_ON );
}

void Disp7SegAmount(U16 mu16Val)
{	
    if( mu16Val >= DISPLAY_CIRCLE )
    {   /* CHAR CIRCLE */
        // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
        // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efad, SEG_ON);
        // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad, SEG_ON);
        // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd, SEG_ON);
    }
    else
    {
        DispSegmentDigit( mu16Val );
    }
}

void TurnOffAllLED(void)
{
    HAL_TurnOnOffLEDAll( LED_OFF );   
}

void TurnOnAllLED(void)
{
    HAL_TurnOnOffLEDAll( LED_ON );
}

void TurnOffAllSeg(void)
{
    // HAL_TurnOnOffSegAll( SEG_OFF );   
}

void TurnOnAllSeg(void)
{
    // HAL_TurnOnOffSegAll( SEG_ON );
}

void DispLowWater( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_LOW_WATER, mu8OnOff );
}

void DispHotWater( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_WATER, mu8OnOff );
}

void DispRoomWater (U8 mu8OnOff)
{
    HAL_TurnOnOffLED( ROOM_WATER, mu8OnOff );
}

void DispHotLock( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_LOCK, mu8OnOff );
}

void DispOnlyHotLock( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_WATER, mu8OnOff );
    HAL_TurnOnOffLED( HOT_LOCK, mu8OnOff );
}

void DispWaterOutPointRight( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( LED_WATER_OUT, mu8OnOff );
}

void DispSegOff(void)
{
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, PROTOCOL_SEG_LED_DATA_O, SEG_ON );  
    // HAL_TurnOnOffSeg( SEG2, PROTOCOL_SEG_LED_DATA_F, SEG_ON );  
    // HAL_TurnOnOffSeg( SEG1, PROTOCOL_SEG_LED_DATA_F, SEG_ON );
}

void DispSegOn(void)
{
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );   
    // HAL_TurnOnOffSeg( SEG2, PROTOCOL_SEG_LED_DATA_O, SEG_ON );  
    // HAL_TurnOnOffSeg( SEG1, PROTOCOL_SEG_LED_DATA_n, SEG_ON );
}

void DispAllLock(U8 mu8OnOff)
{
 //   HAL_TurnOnOffLED( LOCK_ALL, mu8OnOff );
}

void DispEolAmbientTempErr( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ROOM_WATER, mu8OnOff );
    HAL_TurnOnOffLED( ICON_INFINITY, mu8OnOff );
}

void DispEolHotTempErr( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_WATER, mu8OnOff );
    HAL_TurnOnOffLED( ICON_INFINITY, mu8OnOff );
}

void DispEolColdTempErr( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_INFINITY, mu8OnOff );
}

void DispReplaceFilter( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_REPLACE_FILTER, mu8OnOff );
}

void DispEolInnoAndReplaceFilter( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_REPLACE_FILTER, mu8OnOff );
}

void DispEolLevelElectrodeHotHigh( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_INFINITY, mu8OnOff );
    HAL_TurnOnOffLED( RIGHT_BAR1, mu8OnOff );
    HAL_TurnOnOffLED( RIGHT_BAR2, mu8OnOff );
}

void TurnOffLED_LockAllMode(void)
{
    HAL_TurnOnOffLED( RIGHT_BAR1, LED_OFF );	
    HAL_TurnOnOffLED( RIGHT_BAR2, LED_OFF );
    HAL_TurnOnOffLED( ICON_INFINITY, LED_OFF );
    HAL_TurnOnOffLED( ROOM_WATER, LED_OFF );
    HAL_TurnOnOffLED( HOT_WATER,  LED_OFF );
    HAL_TurnOnOffLED( HOT_LOCK,  LED_OFF );

    HAL_TurnOnOffLED( ICON_REPLACE_FILTER, LED_OFF );

    // HAL_TurnOnOffSegAll( SEG_OFF );
}

void DispFrontVersion(void)
{
    U16 mu16Val;

    // mu16Val = (U16)GetFrontVersion();
	
    DispSegmentDigit(mu16Val);
}


void DispMainVersion(U8 mu8Val)
{
    switch( mu8Val )
    {
        case 0:
            break;
		
        case 1:
            DispRightBar1(LED_OFF);
            DispRightBar2(LED_OFF);
            break;
		
        case 2:
            DispRightBar1(LED_OFF);
            DispRightBar2(LED_OFF);
            break;
			
        case 3:
            DispRightBar1(LED_OFF);
            DispRightBar2(LED_OFF);
            break;
		
        case 4:
            DispRightBar1(LED_OFF);
            DispRightBar2(LED_ON);
            break;
		
        case 5:
            DispRightBar1(LED_OFF);
            DispRightBar2(LED_ON);
            break; 

        default :
            break;
    }
}

void DispWaterSel(U8 mu8Sel)
{
    if( mu8Sel == SEL_WATER_HOT )
    {
        HAL_TurnOnOffLED( HOT_WATER,      LED_OFF );
    }
    else
    {
        // SEL_WATER_ROOM
        HAL_TurnOnOffLED( ROOM_WATER,      LED_ON  );
    }
}

void DispHotWaterSel(U8 mu8HotSel)
{
    // if(Get_HotKeyLockStatus() == TRUE)
    // {
    //     HAL_TurnOnOffLED( HOT_WATER,       LED_OFF );
    //     return;
    // }
    
    if( mu8HotSel == SEL_WATER_HOT )
    {
        HAL_TurnOnOffLED( HOT_WATER,       LED_ON  );	
    }
    else
    {
        HAL_TurnOnOffLED( HOT_WATER,       LED_OFF );
    }
}

void DispAmount(void)
{
    if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == FALSE )
    {
        // HAL_TurnOnOffLED( AMOUNT, LED_ON );
    }
}

// 0% ~ 100%
void DispPercent(U16 mu16Val)
{
    DispSegmentDigit( mu16Val );
}

void DispBarProgress(U16 mu16WaterOutProgress, U32 mu32DiffrentTime)
{
    /* bar4 display for 0.5 sec */
    if( mu32DiffrentTime <= (U32)(BAR4_DISPLAY_500MS) )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,		LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR2,		LED_ON );
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_ON );
        return;
    }
	
    if( mu16WaterOutProgress >= PROGRESS_75PERCENT )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_ON );
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_ON );
    }
    else if( mu16WaterOutProgress >= PROGRESS_50PERCENT )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_ON );
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_OFF );
    }
    else if( mu16WaterOutProgress >= PROGRESS_25PERCENT )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_OFF );
    }
    else
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_OFF );
    }

}

void DispWaterOutProgress(U16 mu16WaterOutProgress )
{
    U32 mu32DiffrentTime;

    mu32DiffrentTime = ( GetWaterOutFixedAmountTargetTime() - GetWaterOutFixedAmountCurrentTime() );
    DispBarProgress(mu16WaterOutProgress, mu32DiffrentTime);
}

/* 용량 선택 최대 5(정량4개,레버1개) */
static void DispAmountBarByStep(void)
{
    if( GetAmountStep() == (AMOUNT_STEP_MAX - 1) )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
    }
    else if( GetAmountStep() == (AMOUNT_STEP_MAX - 2) )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }
    else if( GetAmountStep() == (AMOUNT_STEP_MAX - 3) )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }
    else if( GetAmountStep() == (AMOUNT_STEP_MAX - 4) )
    {
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }  
}

void DispHotWaterOutProgress(U16 mu16WaterOutProgress )
{
    U32 mu32DiffrentTime;
    
    mu32DiffrentTime = ( GetHotWaterOutFixedAmountTargetTime() - GetHotWaterOutFixedAmountCurrentTime() );
    
    DispBarProgress(mu16WaterOutProgress, mu32DiffrentTime);
}

static void DispAmountSelAscending(U8 mu8AmountCusor)
{
    // AMOUNT TYPE
    if( GetWaterOutPressContinue() == TRUE)
    {
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR1,		LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,		LED_OFF );
    }
    else if( GetWaterOutAmountType() == AMOUNT_ID_INFINITY )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_ON   );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }
    else if( mu8AmountCusor == AmountDispStep2 )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_ON );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
    }
    else if( mu8AmountCusor == AmountDispStep1 )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_ON );
    }
    else
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }

    /* 현재 용량 선택 단계에 따라서 현재 선택 단계 이후의 led bar 들을 off */
    // DispAmountBarByStep();
}

static void DispAmountSelDescending(U8 mu8AmountCusor)
{
    // AMOUNT TYPE
    if( GetWaterOutPressContinue() == TRUE )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,	LED_ON	 );
        HAL_TurnOnOffLED( RIGHT_BAR1,		LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,		LED_OFF );
    }
    else if( GetWaterOutAmountType() == AMOUNT_ID_INFINITY )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_ON   );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }
    else if( mu8AmountCusor == AmountDispStep1 )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_ON   );
    }
    else if( mu8AmountCusor == AmountDispStep2 )
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_ON   );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
    }
    else
    {
        HAL_TurnOnOffLED( ICON_INFINITY,    LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR1,       LED_OFF );
        HAL_TurnOnOffLED( RIGHT_BAR2,       LED_OFF );
    }

    /* 현재 용량 선택 단계에 따라서 현재 선택 단계 이후의 led bar 들을 off */
    // DispAmountBarByStep();
}

void DispAmountSel(U8 mu8AmountCusor, U8 mu8Dimming )
{
    U8 mu8AmountSortType;

    mu8AmountSortType = GetAmountSortType();

    if( mu8AmountSortType == SORT_TYPE_ASCENDING )
    {
        DispAmountSelAscending(mu8AmountCusor);
    }
    else
    {
        DispAmountSelDescending(mu8AmountCusor);
    }
}

void DispAmountSelOff(void)
{
    // HAL_TurnOnOffLED( AMOUNT,    LED_OFF );
	
    HAL_TurnOnOffLED( ICON_INFINITY, LED_OFF );
    HAL_TurnOnOffLED( RIGHT_BAR2,    LED_OFF );
    HAL_TurnOnOffLED( RIGHT_BAR1,    LED_OFF );
}

void DispAmountSelOffAll(void)
{
    // AMOUNT 
    HAL_TurnOnOffLED( ICON_INFINITY,     LED_OFF );
    HAL_TurnOnOffLED( RIGHT_BAR2,        LED_OFF );
    HAL_TurnOnOffLED( RIGHT_BAR1,        LED_OFF );

    // HAL_TurnOnOffLED( AMOUNT,         LED_OFF );
}

void DispRightBar1(U8 mu8OnOff)
{
    HAL_TurnOnOffLED( RIGHT_BAR1,       mu8OnOff );
}

void DispRightBar2(U8 mu8OnOff)
{
    HAL_TurnOnOffLED( RIGHT_BAR2,       mu8OnOff );
}

void DispInfinity( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_INFINITY,    mu8OnOff );
}

// AMOUNT inifinity
void DispAmountInfinity(void)
{
    // AMOUNT 
    HAL_TurnOnOffLED( ICON_INFINITY,     LED_ON );
    HAL_TurnOnOffLED( RIGHT_BAR2,        LED_OFF );
    HAL_TurnOnOffLED( RIGHT_BAR1,        LED_OFF );
}

void DispLockHotSetBlink( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_LOCK, mu8OnOff );
}

void DispLockAllOnOff_CHP( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( HOT_LOCK,  mu8OnOff );
    HAL_TurnOnOffLED( ROOM_WATER,  mu8OnOff );	
}

void CHP_DispVirtualLedAllOnOff( U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_LOW_WATER,  mu8OnOff );
    HAL_TurnOnOffLED( HOT_WATER, mu8OnOff );
    HAL_TurnOnOffLED( HOT_LOCK, mu8OnOff );
}

void DispHeatingBlinkDimming( U8 mu8OnOff )
{
    SetLedType(ICON_HEATING, LED_TYPE_DUTY_DIM);	// set dimming

    HAL_TurnOnOffLED( ICON_HEATING, mu8OnOff );
}

void DispLock( U8 mu8OnOff )
{
//    HAL_TurnOnOffLED( LOCK_ALL, mu8OnOff );
}

U8 DispVersionOnTime(void)
{
    static U16 mu16Delay = 200;    // 2sec.. @10ms..

    if( mu16Delay != 0)
    {
        mu16Delay--;

        DispMainVersion( MAIN_VERSION );
        //DispFrontVersion();

        return FALSE;
    }

    return TRUE;
}

/* CHP : ON , CP : OFF */
void DispProductInfromation(U8 mu8OnOff )
{
    HAL_TurnOnOffLED( ICON_LOW_WATER, mu8OnOff );
}

void SetLedAllType(void)
{
    U8 i;
	
    for(i = 0; i < MAX_LED_NUM; i++ )
    {
        SetLedType( i, LED_TYPE_DUTY );
    }
}


typedef struct _seg_
{
    U8 Seg_100;
    U8 Seg_10;
    U8 Seg_1;
} InfinityList_T;

const static InfinityList_T EffectInifinity[] = 
{
    { PROTOCOL_SEG_LED_DATA_OFF,                 PROTOCOL_SEG_LED_DATA_OFF,                PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_e,      PROTOCOL_SEG_LED_DATA_OFF,                PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ef,     PROTOCOL_SEG_LED_DATA_OFF,                PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_OFF,                PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a    },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ab   },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abc  },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efad,   PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_fad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_bcd  },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_cd   },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d    },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,     PROTOCOL_SEG_LED_DATA_OFF               },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d,      PROTOCOL_SEG_LED_DATA_OFF,                PROTOCOL_SEG_LED_DATA_OFF               }
};
#define SZ_INFINITY_LIST    (sizeof(EffectInifinity)/sizeof(InfinityList_T))

#define DELAY_INFINITY   2  // 200ms @100ms
U8 gu8InfinityCount = 0U;
U8 gu8InfinityDelay = DELAY_INFINITY;
void ResetInfinityCount(void)
{
    gu8InfinityCount = 0;
    gu8InfinityDelay = DELAY_INFINITY;
}

void DispInfinityOutAmount(void)
{
    InfinityList_T *pVal;

    pVal = &EffectInifinity[ gu8InfinityCount ];
	
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, pVal->Seg_100, SEG_ON );
    // HAL_TurnOnOffSeg( SEG2, pVal->Seg_10,  SEG_ON );
    // HAL_TurnOnOffSeg( SEG1, pVal->Seg_1,   SEG_ON );

    if( gu8InfinityDelay != 0 )
    {
        gu8InfinityDelay--;
        return ;
    }

    gu8InfinityDelay = DELAY_INFINITY;
    gu8InfinityCount++;

    if( gu8InfinityCount >= SZ_INFINITY_LIST )
    {
        gu8InfinityCount = 0;
    }
}

typedef struct _lever_seg_
{
    U8 Seg_100;
    U8 Seg_10;
    U8 Seg_1;
} LeverList_T;

const static LeverList_T EffectLever[] = 
{
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,      PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a    },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ag,     PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ag,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ag   },
    { PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_agd,    PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_agd,   PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_agd  },
};
#define SZ_LEVER_LIST    (sizeof(EffectLever)/sizeof(LeverList_T))

#define DELAY_LEVER_WATER  5  // 500ms @100ms
U8 gu8WaterLeverCount = 0U;
U8 gu8WaterLeverDelay = DELAY_LEVER_WATER;
void ResetWaterLeverCount(void)
{
    gu8WaterLeverCount = 0;
    gu8WaterLeverDelay = DELAY_LEVER_WATER;
}

#define DELAY_LEVER_HOT_WATER  5  // 500ms @100ms
U8 gu8HotWaterLeverCount = 0U;
U8 gu8HotWaterLeverDelay = DELAY_LEVER_HOT_WATER;
void ResetHotWaterLeverCount(void)
{
    gu8HotWaterLeverCount = 0;
    gu8HotWaterLeverDelay = DELAY_LEVER_HOT_WATER;
}

void DispLeverWaterOut(void)
{
    LeverList_T *pVal;

    pVal = &EffectLever[ gu8WaterLeverCount ];
	
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, pVal->Seg_100, SEG_ON );
    // HAL_TurnOnOffSeg( SEG2, pVal->Seg_10,  SEG_ON );
    // HAL_TurnOnOffSeg( SEG1, pVal->Seg_1,   SEG_ON );

    if( gu8WaterLeverDelay != 0 )
    {
        gu8WaterLeverDelay--;
        return;
    }

    gu8WaterLeverDelay = DELAY_LEVER_WATER;
    gu8WaterLeverCount++;

    if( gu8WaterLeverCount >= SZ_LEVER_LIST )
    {
        gu8WaterLeverCount = 0;
    }
}

void DispLeverHotWaterOut(void)
{
    LeverList_T *pVal;

    pVal = &EffectLever[ gu8HotWaterLeverCount ];
	
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, pVal->Seg_100, SEG_ON );
    // HAL_TurnOnOffSeg( SEG2, pVal->Seg_10,  SEG_ON );
    // HAL_TurnOnOffSeg( SEG1, pVal->Seg_1,   SEG_ON );

    if( gu8HotWaterLeverDelay != 0 )
    {
        gu8HotWaterLeverDelay--;
        return;
    }

    gu8HotWaterLeverDelay = DELAY_LEVER_HOT_WATER;
    gu8HotWaterLeverCount++;

    if( gu8HotWaterLeverCount >= SZ_LEVER_LIST )
    {
        gu8HotWaterLeverCount = 0;
    }
}

void DispSegmentOff(void)
{
    // HAL_TurnOnOffSeg( SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
    // HAL_TurnOnOffSeg( SEG3, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );	
    // HAL_TurnOnOffSeg( SEG2, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );	
    // HAL_TurnOnOffSeg( SEG1, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF );
}

/*
 * LedProtocolDataTable의 Command 값을 읽어 hw.h에 정의된 LED 포트에 반영한다.
 * Command > 0 : LED 포트 ON (1)
 * Command == 0 : LED 포트 OFF (0)
 * ICON_LOW_WATER / ICON_REPLACE_FILTER / LED_WATER_OUT 은 직접 GPIO 포트가 없으므로 제외.
 */
void ApplyLedPortOutput(void)
{
    U8 mu8Cmd;

    /* ICON_HEATING → LED_HOT_1 (P0.2) */
    mu8Cmd = HAL_GetProtocolCommand(ICON_HEATING);
    LED_HOT_1 = (mu8Cmd > 0) ? 1 : 0;

    /* HOT_LOCK → LED_LOCK (P1.2) */
    mu8Cmd = HAL_GetProtocolCommand(HOT_LOCK);
    LED_LOCK = (mu8Cmd > 0) ? 1 : 0;

    /* HOT_WATER → LED_HOT_2 (P0.3) */
    mu8Cmd = HAL_GetProtocolCommand(HOT_WATER);
    LED_HOT_2 = (mu8Cmd > 0) ? 1 : 0;

    /* ROOM_WATER → LED_AMOUNT (P0.1) */
    mu8Cmd = HAL_GetProtocolCommand(ROOM_WATER);
    LED_AMBIENT = (mu8Cmd > 0) ? 1 : 0;
    
    /* RIGHT_BAR1 → LED_AMOUNT_1 (P1.3) */
    mu8Cmd = HAL_GetProtocolCommand(RIGHT_BAR1);
    LED_AMOUNT_2 = (mu8Cmd > 0) ? 1 : 0;
    
    /* RIGHT_BAR2 → LED_AMOUNT_2 (P1.4) */
    mu8Cmd = HAL_GetProtocolCommand(RIGHT_BAR2);
    LED_AMOUNT_1 = (mu8Cmd > 0) ? 1 : 0;
    
    /* ICON_INFINITY → LED_AMOUNT_3 (P6.3) */
    mu8Cmd = HAL_GetProtocolCommand(ICON_INFINITY);
    LED_AMOUNT_3 = (mu8Cmd > 0) ? 1 : 0;
}
