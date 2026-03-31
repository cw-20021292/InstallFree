#include "Global_Header.h"
#include "water_out_type.h"
#include "water_out.h"
#include "flushing.h"
#include "amount.h"

typedef struct _water_out_
{
    /* Select */
    U8  Select;
    U8  PrevSelect;
    U16 ReturnTime;
    U16 ReturnTimeAmount;

    /* Water Out Mode */
    U8  WaterOut;                // TRUE or FALSE
    U8  PrevWaterOut;
    U8  ConfAmount;              // default FIXED_AMOUINT
    U16 ImpossibleTimer;         // Unable to re-extract for 0.3 seconds after completion of extraction
	
    /* Fixed Amounted */
    U8  PressContinue;           // TRUE: Lever Mode, FALSE: Quantitative Extraction(120ML,250ML,500ML....) 
    U16 PressContinueReturnTime;  
    U8  InfinityAmount;          
    U8  LatestFixedAmount;        // Most recently selected volume
    U8  FixedAmountType;         // FIXED_AMOUNT
    U32 FixedAmountTargetTime;   // @10msec 
    U32 FixedAmountCurrentTime;  // @10msec
    U8  LongKeyOut;             
    U8  LongKeyBackUp;  
    U8  AmountKeyBackUp;
    
    /* For Default Amount*/
    U8 TriggerDefaultAmount;          // 용량 버튼 누른 후 PressContinueReturnTime 값이 0 이 될때 기본용량 세팅 해주기 위해

    /* Water Out Time */
    U32 LastedTime[ MAX_WATER_ID ];  // @10msec
    U32 DailyTime[ MAX_WATER_ID ];   // @10msec
    U32 TotalTime[ MAX_WATER_ID ];   // @10msec

    /* Aging Test */
    U8 AgingTestRepeatStatus;  // For Agint Test
    U8 DispAgingConfig;        // Display config about number of aging test cycle

    /* Reliability Test */
    U8 ColdTestRepeatStatus; 
    U8 HotTestRepeatStatus; 
    U8 AllTestRepeatStatus; // cold + hot + room + warm40
} WaterOut_T;

WaterOut_T Out;



void  InitWaterOut(void)
{
    Out.Select           = SEL_WATER_ROOM;
    Out.PrevSelect       = SEL_WATER_ROOM;
    Out.ReturnTime       = 0;
    Out.ReturnTimeAmount = 0;	

    Out.WaterOut         = FALSE;
    Out.PrevWaterOut     = FALSE;
   // Out.ConfAmount       = AMOUNT_ID_LEVER;

    Out.PressContinue    = FALSE;
    Out.PressContinueReturnTime  = 0;
    
    Out.InfinityAmount    = FALSE;

    // Out.FixedAmountType  = GetAmountDefault();
    Out.FixedAmountTargetTime  = 0UL;
    Out.FixedAmountCurrentTime = 0UL;
    
    Out.TriggerDefaultAmount = FALSE;

    Out.LastedTime[ SEL_WATER_ROOM ] = 0UL;
    // Out.LastedTime[ SEL_WATER_COLD ] = 0UL;
    Out.LastedTime[ SEL_WATER_HOT  ] = 0UL;

    Out.DailyTime[ SEL_WATER_ROOM ] = 0UL;
    // Out.DailyTime[ SEL_WATER_COLD ] = 0UL;
    Out.DailyTime[ SEL_WATER_HOT  ] = 0UL;
	
    Out.TotalTime[ SEL_WATER_ROOM ] = 0UL;
    // Out.TotalTime[ SEL_WATER_COLD ] = 0UL;
    Out.TotalTime[ SEL_WATER_HOT  ] = 0UL;

    Out.ImpossibleTimer  = 0UL;

    /* Reliability Test */
    Out.ColdTestRepeatStatus = FALSE;
    Out.HotTestRepeatStatus = FALSE;
    Out.AllTestRepeatStatus = FALSE;
	
    InitAmount();
}

void  SetWaterOutSelect(U8 mu8Id )
{
    if( mu8Id >= MAX_WATER_ID )
    {
        return ;
    }

    if( Out.Select != mu8Id )
    {
        Out.PrevSelect = Out.Select;
    }
	
    ResetReturnTime();        // water key return time reset
    ResetReturnTimeAmount();  // amount key return time reset

    // StartDispTimerId( DISP_TIMER_KEY_AMOUNT );

    Out.Select = mu8Id;

    // SaveEepromId( EEPROM_ID_SEL_WATER );
}

U8 GetWaterOutSelect(void)
{
    return Out.Select;
}

/* 추출 시작 - Key */
void StartWaterOut(void)
{
    if( Out.WaterOut == FALSE )
    {
        Out.LastedTime[ Out.Select ] = 0;
    }
    
    Out.WaterOut = TRUE;
    
    // /* Auto Flushing */
    // if(GetAutoFlushingRun() == TRUE)
    // {
    //     ResetAutoFlushing();
    //     SetValveAutoFlushingOff();  //오토플러싱 중에 추출 할 경우, 오토플러싱 취소 및 초기화
    // }
    
    /* For stop Cooling led blink */
    // StopDispTimerId(DISP_TIMER_COOLING_DIMMING_BLINK);
}


/* 추출 중지 */
void  StopWaterOut(void)
{
    U8 mu8FixedAmount = 0;
    U8 mu8DefaultCursor;

    Out.WaterOut = FALSE;

    /* Cooling led on? yes -> Start Blink Timer for 7sec */
    // if( Out.Select == SEL_WATER_COLD )
    // {
        // if( GetColdTempLevel() == COOLING )
        // {
        //     StartDispTimerId( DISP_TIMER_COOLING_DIMMING_BLINK );	
        // }
    // }
    
    // /* 우선순위1 : 필터 잔여량 표시, 우선순위2 : uv 진행률 표시 */
    // if( IsExpiredFilterUsage() == TRUE )
    // {
    //     // StartDispTimerId( DISP_TIMER_REPLACE_FILTER );
    // }
    // else
    // {
    //     // /* If UV ~ING */
    //     // if( GetUvOnTime(UV_COLD_TANK) != 0 
    //     //     || GetUvOnTime(UV_ROOM_TANK) != 0 )
    //     // {       
    //     //     StartDispTimerId( DISP_TIMER_UVCARE );
    //     // //    StopDispTimerId( DISP_TIMER_KEY_HOT_TEMP );	
    //     // }
    // }

//     /* 정량으로 추출 중이었다면 물 용량 레버로 바로 회귀 */
//     if(IsWaterAmountSelected() == TRUE)
//     {   
//         Out.InfinityAmount  = FALSE;
//         SetWaterOutPressContinue(TRUE);

//         if(GetHotWaterOut()== FALSE)
//         {
//             SetHotWaterOutPressContinue(TRUE);
//         }   
//     }
    
//     /* 왼쪽 추출 안하고 있고, 용량 선택도 안했으면 DISP_TIMER_KEY_AMOUNT 바로 STOP */
//   //  if(GetHotWaterOut() == FALSE && IsHotWaterAmountSelected() != TRUE)
//   //  {
//  //       StopDispTimerId( DISP_TIMER_KEY_AMOUNT );
//  //   }

//     /* 왼쪽 추출 안하고 있을 때 */
//     if(GetHotWaterOut() == FALSE)
//     {
//         /* 좌측 정량 선택 되어있으면 우측 추출부 정량 동기화 */
//         if( IsHotWaterAmountSelected() == TRUE )
//         {
//             mu8FixedAmount = GetHotWaterOutFixedAmountType();
//             SetWaterOutFixedAmountType(mu8FixedAmount);
//         }
//         /* 용량 선택도 안했으면 DISP_TIMER_KEY_AMOUNT 바로 STOP */
//         else
//         {
//             // StopDispTimerId( DISP_TIMER_KEY_AMOUNT );

//             /* 디폴트 물양으로 세팅 */
//             mu8DefaultCursor = GetAmountDefaultCursor(); 
//             SetAmountCursor(mu8DefaultCursor);  // 추출 종료 후에 디폴트물양으로 세팅
//             SetSkipCursorIncrease(TRUE);
//         } 
//     }
}

/* 추출 상태 반환
 * Return
 *  -TRUE : 추출 중
 *  -FALSE : 추출 중지 상태
 * */
U8 GetWaterOut(void)
{
    return Out.WaterOut;
}


/* LeverMode Setting */
void SetWaterOutPressContinue(U8 mu8Mode )
{
    if( mu8Mode != TRUE && mu8Mode != FALSE )
    {
        return ;
    }

    if( mu8Mode == FALSE )
    {
        Out.PressContinue = FALSE;
        Out.PressContinueReturnTime = DEFAULT_RETURN_TIME;  
       // SetAmountCursor(0); // 값 세팅 하면 꼬임
    }
    else
    {
        Out.InfinityAmount = FALSE;
        Out.PressContinue = TRUE;
       // Out.FixedAmountType  = AMOUNT_ID_LEVER;
       //  SetAmountCursor(GetAmountLeverCursor());  //용량cursor 레버로 세팅  
    }

    //SaveEepromId( EEP_ID_CONF_CONTY );
}

/* LEVER */
U8 GetWaterOutPressContinue(void)
{
    return Out.PressContinue;
}

/* 우측 추출부(정수or냉수) 정량 선택 여부 확인 함수 */
U8 IsWaterAmountSelected(void)
{
    if( GetWaterOutPressContinue() == FALSE)
    {
        return TRUE;
    }

    return FALSE;
}

void SetWaterOutFixedAmountDefaultType( EAmountId_T xEid )
{
    SetWaterOutFixedAmountType(xEid);
    SetHotWaterOutFixedAmountType(xEid);
    SetAmountDefault(xEid);
}

/*
void  SetWaterOutFixedAmountType(U8 mu8Type )
{
    if( mu8Type >= AMOUNT_ID_MAX )
    {
        return ;
    }

    SetWaterOutPressContinue(FALSE);
    if( mu8Type == AMOUNT_ID_INFINITY )
    {
        Out.InfinityAmount = TRUE;
        Out.FixedAmountType  = AMOUNT_ID_INFINITY;   
    }
    else if( mu8Type == AMOUNT_ID_LEVER )
    {
        Out.InfinityAmount  = FALSE;
        Out.FixedAmountType  = AMOUNT_ID_LEVER;
        SetWaterOutPressContinue(TRUE);
    }
    else
    {
        Out.InfinityAmount  = FALSE;
        Out.FixedAmountType  = mu8Type;
    }
	
    Out.AmountKeyBackUp = GetWaterOutFixedAmountType();
    Out.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;
   // Out.FixedAmountTargetTime = gu32FixedAmountTimeTable[ Out.Select ][ mu8Type ]; // 코드 살리면 꼬임 -> 동시 추출 하기 위해 한쪽 추출 중에 다른 쪽 정량 선택할 때 문제 됨
   // SaveEepromId( EEPROM_ID_CONF_FIXED_AMOUNT );
}*/

void  SetWaterOutFixedAmountType(U8 mu8Type )
{
    if( mu8Type >= AMOUNT_ID_MAX )
    {
        return ;
    }

//    SetWaterOutPressContinue(FALSE);
    if( mu8Type == AMOUNT_ID_INFINITY )
    {
        Out.InfinityAmount = TRUE;
        Out.FixedAmountType  = AMOUNT_ID_INFINITY;   
    }
 //   else if( mu8Type == AMOUNT_ID_LEVER )
 //   {
 //       Out.InfinityAmount  = FALSE;
  //      Out.FixedAmountType  = AMOUNT_ID_LEVER;
  //      SetWaterOutPressContinue(TRUE);
  //  }
    else
    {
        Out.InfinityAmount  = FALSE;
        Out.FixedAmountType  = mu8Type;
    }
	
    Out.AmountKeyBackUp = GetWaterOutFixedAmountType();
    Out.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;
   // Out.FixedAmountTargetTime = gu32FixedAmountTimeTable[ Out.Select ][ mu8Type ]; // 코드 살리면 꼬임 -> 동시 추출 하기 위해 한쪽 추출 중에 다른 쪽 정량 선택할 때 문제 됨
   // SaveEepromId( EEPROM_ID_CONF_FIXED_AMOUNT );
}

/* using now amount */
U8 GetWaterOutFixedAmountType(void)
{
    return Out.FixedAmountType;
}

U8 GetWaterOutAmountType(void)
{
    if( Out.InfinityAmount == TRUE )
    {
        return AMOUNT_ID_INFINITY;
    }

    return GetWaterOutFixedAmountType();
}

/* Functions for default amount */
U8 GetWaterOutConfFixedAmountType(void)
{
    return Out.ConfAmount;
}
void SetWaterOutConfFixedAmountType(U8 mu8Type)
{
    Out.ConfAmount = mu8Type;

   // SaveEepromId( EEPROM_ID_CONF_FIXED_AMOUNT );
}

void ClearWaterOutInfinityAmount(void)
{
    Out.InfinityAmount = FALSE;
}

void  SetWaterOutFixedAmountTargetTime(U32 mu32Time )
{
    Out.FixedAmountTargetTime = mu32Time;
}

U32   GetWaterOutFixedAmountTargetTime(void)
{
    return Out.FixedAmountTargetTime;
}

void  SetWaterOutFixedAmountCurrentTime(U32 mu32Time )
{
    Out.FixedAmountCurrentTime = mu32Time;
}

U32   GetWaterOutFixedAmountCurrentTime(void)
{
    return Out.FixedAmountCurrentTime;
}

void  SetWaterOutLastedTime(U8 mu8Id, U32 mu32Time )
{
    Out.LastedTime[ mu8Id ] = mu32Time;;
}

U32  GetWaterOutLastedTime(U8 mu8Id )
{
    return Out.LastedTime[ mu8Id ];
}

void  SetWaterOutDailyTime(U8 mu8Id, U32 mu32Time )
{
    Out.DailyTime[ mu8Id ] = mu32Time;
}

U32  GetWaterOutDailyTime(U8 mu8Id )
{
    return Out.DailyTime[ mu8Id ];
}

void  SetWaterOutTotalTime(U8 mu8Id, U32 mu32Time )
{
    Out.TotalTime[ mu8Id ] = mu32Time;
}

U32  GetWaterOutTotalTime(U8 mu8Id )
{
    return Out.TotalTime[ mu8Id ];
}

void SetWaterOutTime(U8 mu8Type, U8 mu8Id, U32 mu32Time )
{
    if( mu8Type == TYPE_LASTED )
    {
        Out.LastedTime[ mu8Id ] = mu32Time;
    }
    else if( mu8Type == TYPE_DAILY )
    {
        Out.DailyTime[ mu8Id ] = mu32Time;
    }
    else
    {
        Out.TotalTime[ mu8Id ] = mu32Time;
    }
}

U32  GetWaterOutTime(U8 mu8Type, U8 mu8Id )
{
    U32 mu32Time = 0;

    if( (mu8Type & TYPE_LASTED) != 0 )
    {
        mu32Time += Out.LastedTime[ mu8Id ];
    }

    if( (mu8Type & TYPE_DAILY) != 0 )
    {
        mu32Time += Out.DailyTime[ mu8Id ];
    }

    if( (mu8Type & TYPE_TOTAL) != 0 )
    {
        mu32Time += Out.TotalTime[ mu8Id ];
    }

    return mu32Time;
}

void ResetWaterOutTime(U8 mu8Type, U8 mu8Id )
{
    if( (mu8Type & TYPE_LASTED) != 0 )
    {
        Out.LastedTime[ mu8Id ] = 0;
    }

    if( (mu8Type & TYPE_DAILY) != 0 )
    {
        Out.DailyTime[ mu8Id ] = 0;
    }

    if( (mu8Type & TYPE_TOTAL) != 0 )
    {
        Out.TotalTime[ mu8Id ] = 0;
    }
}

void SetReturnTimeAmount(U16 mu16Time)
{
    Out.ReturnTimeAmount = mu16Time;
}

void SetReturnTime(U16 mu16Val)
{
    Out.ReturnTime = mu16Val;
}

void ResetReturnTime(void)
{
    Out.ReturnTime = DEFAULT_RETURN_TIME;
}

void ResetReturnTimeAmount(void)
{
    Out.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;
}

void ResetReturnTimePressContinue(void)
{
    Out.PressContinueReturnTime = DEFAULT_RETURN_TIME;
}

U16 GetReturnTimePressContinue(void)
{
    return Out.PressContinueReturnTime;
}

static U8 ConvWaterOut_Time2Cup(U32 mu32Time, U32 mu32CupTime)
{
    U32 mu32CupSize;


    if( mu32Time < (mu32CupTime/3) )
    {
        mu32CupSize = 0;    // 0-cup under 1/3
    }
    else if( mu32Time <= mu32CupTime )
    {
        mu32CupSize = 1;
        return 1;    // 1-cup over 1/3
    }
    else
    {
        // Round Up
        mu32Time += (mu32CupTime / 2);    
        mu32CupSize = mu32Time / mu32CupTime;
    }

    return (U8)mu32CupSize;
}

// U8 GetWaterOutLastedCupNum(U8 mu8Id)
// {
//     U8 mu8Num;
//     U32 mu32TimerPerCup;

//     mu32TimerPerCup = GetTimerPerCup(mu8Id);

//     mu8Num = ConvWaterOut_Time2Cup( 
//             Out.LastedTime[ mu8Id ],
//             mu32TimerPerCup
//             );

//     return mu8Num;
// }

// U8 GetWaterOutDailyCupNum(U8 mu8Id)
// {
//     U8 mu8Num;
//     U32 mu32TimerPerCup;

//     mu32TimerPerCup = GetTimerPerCup(mu8Id);

//     mu8Num = ConvWaterOut_Time2Cup( 
//             Out.DailyTime[ mu8Id ],
//             mu32TimerPerCup
//             );

//     return mu8Num;
// }

// U8 GetWaterOutTotalCupNum(U8 mu8Id)
// {
//     U8 mu8Num;
//     U32 mu32TimerPerCup;

//     mu32TimerPerCup = GetTimerPerCup(mu8Id);

//     mu8Num = ConvWaterOut_Time2Cup( 
//             Out.TotalTime[ mu8Id ],
//             mu32TimerPerCup
//             );

//     return mu8Num;
    
// }

U8 IsExpiredOutProtectTime(void)
{
    if( Out.ImpossibleTimer != 0 )
    {
        return FALSE;   
    }

    return TRUE;    
}

void SetWaterOutInfinityLongKey(void)
{
    Out.LongKeyOut = TRUE;

    Out.LongKeyBackUp = GetWaterOutFixedAmountType();
    SetWaterOutFixedAmountType( AMOUNT_ID_INFINITY );
}

/* After Infinity water out, it immediately returns to the before amount state. */
void ClearWaterOutInfinityLongKey(void)
{
    if( Out.WaterOut == FALSE && Out.LongKeyOut == TRUE )
    {
        Out.LongKeyOut = FALSE;

        SetWaterOutFixedAmountType( Out.LongKeyBackUp );
    }
}

//U32 GetFixedAmoutTimeTable(U8 mu8select, U8 mu8AmountType)
//{
//    U32 mu32FixedAmountTimeTable;
//
//    mu32FixedAmountTimeTable = gu32FixedAmoutTimeTable[ mu8select ][ mu8AmountType ];
//    
//    return mu32FixedAmountTimeTable;
//}

static void RightLeverOutValve(void)
{
    U8 mu8Select;

    mu8Select = Out.Select;

    // 플러싱 진행중이거나 플러싱 필요하면 추출 처리 x
    if((GetFlushingConfig() == TRUE)
    || (GetFlushingRun() == TRUE)
    )
    {
        return;
    }

    // 필터리드 열려있으면 추출 취소
    if(Get_ReedSW_Status(REED_SW_ID_FILTER_REED) == FALSE)
    {
        StopWaterOut();
    }

    /* TURN OFF WATER OUT */
    if( Out.WaterOut == FALSE )
    {
#if 0
        /* ROOM */
        SetValveQueue(VALVE_CMD_TANK_ROOM_OUT_CLOSE); //이거로 제어하면 queue때문에 딜레이 생길 수있음
        ValveClose( VALVE_ROOM_OUT );
        
        /* COLD */
        TurnOffCirculatePumpWaterOut();
#endif
        Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, OFF, 0);

        Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, CLOSE, 0);
        Set_ValveControl(VALVE_ID_AMBIENT_OUT, FEED, CLOSE, 1);
        Set_ValveControl(VALVE_ID_HOT_OUT, FEED, CLOSE, 1);
        Set_ValveControl(VALVE_NOS_ID_HOT_TANK_OVERFLOW, NOS, OPEN, 0);
        return;
    }

    if( Out.WaterOut == TRUE ) 
    {
        Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, ON, 1);

        /* TURN ON WATER OUT - COLD */
        if( mu8Select == SEL_WATER_HOT )
        {
            Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, OPEN, 1);
            Set_ValveControl(VALVE_ID_HOT_OUT, FEED, OPEN, 0);
            Set_ValveControl(VALVE_NOS_ID_HOT_TANK_OVERFLOW, NOS, CLOSE, 0);
        }
        /* TURN ON WATER OUT - ROOM */
        else
        {
            Set_ValveControl(VALVE_ID_AMBIENT_OUT, FEED, OPEN, 0);
        }
    }
}

static void  RightLeverOutSelect(void)
{
    /* 1. 온수 선택 후  7sec 후에 다시 냉수 또는 정수로 물 선택을 복귀 시킨다.
     * 2. 단, 냉수 사용이 해제되어 있는 경우에는 정수를 선택한다.
     * 3. 냉수 선택 시 냉수 사용이 해제되어 있는 경우에는 정수로 물 선택을 복귀 시킨다.
     *
     * 물이 추출 중인 경우에는, 물 추출 이후에 5초 타이머가 적용될 수 있도록
     * 타이머를 reset 한다.
     */

    if( Out.WaterOut == TRUE )
    {	
        /* Make Cold Off, Select Cold */
        if( (Out.Select == SEL_WATER_ROOM) 
        // && GetColdWaterConfigMake() == FALSE )
        )
        {
            Out.ReturnTime = RETURN_TIME_AFTER_WATER_OUT;
        }
    }
	
    if( Out.ReturnTime != 0 )
    {
        Out.ReturnTime--;
    }

    if( Out.PressContinueReturnTime != 0 )
    {
        Out.PressContinueReturnTime--;
        Out.TriggerDefaultAmount = TRUE;
    }
}

static void RightWaterOut(void)
{
    U8 mu8AmoutType;
    U8 mu8DefaultCursor;
    
    /* 플러싱, 구연산 세척 모드 진입시 추출 즉시 중지 */
    if((GetFlushingConfig() == TRUE)
    || (GetFlushingRun() == TRUE)
    )
    {
        StopWaterOut();  // 추출 중에 필터교체해서 플러싱 진입하게되면 즉시 추출종료가 안되는 문제 발생해서 추가함 
    }

    if( Out.WaterOut == TRUE )
    {
        Out.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;    
    }
    	
    // 추출 중에는 레버로 돌아가는 시간 reload
    if( (Out.WaterOut == TRUE)
    && (Out.PressContinue == FALSE)
    )
    {
        ResetReturnTimePressContinue();
        // ResetHotReturnTimePressContinue();
    }

    // 연속 추출 기능 해제 
    // if( (Out.PressContinue == FALSE) 
    // && (Out.PressContinueReturnTime == 0)
    // )
    // {
    //     SetWaterOutPressContinue( TRUE );
    //     ClearWaterOutInfinityAmount();
    // }

    if(GetWaterOutPressContinue() == TRUE)
    {     
        mu8DefaultCursor = GetAmountDefaultCursor(); 
        SetAmountBackupCursor(mu8DefaultCursor);  //물양 선택 후 레버로 전환 될 때 디폴트 커서 값으로 set(디폴트 물양 설정 시 용량bar,seg 일치시켜주기위해)
    }

    /* 설정기본 용량 세팅 */
    if((Out.PressContinueReturnTime == 0) 
    && (Out.TriggerDefaultAmount == TRUE)
    )
    {
        Out.TriggerDefaultAmount = FALSE; // 1번만 수행 하기 위해

        Out.FixedAmountType = GetAmountDefault();
        SetAmountCursor(GetAmountDefaultCursor());
        ClearWaterOutInfinityAmount();
        // SetSkipCursorIncrease(TRUE);
    }

    // 연속 추출 목표 시간 및 현재 시간 계산...
    mu8AmoutType = GetWaterOutAmountType();
    if( Out.WaterOut == FALSE || Out.PressContinue == TRUE )
    {
        if( Out.Select == SEL_WATER_ROOM)
        {
            Out.FixedAmountTargetTime = GetAmountRoomTime(mu8AmoutType);
        }    
        else if( Out.Select == SEL_WATER_HOT)
        {
            Out.FixedAmountTargetTime = GetAmountHotTime(mu8AmoutType);
        }     

        AddWaterOutTime();   // Add water out time based on water level

        Out.FixedAmountCurrentTime = 0;
		
        return ;
    }

    if( Out.FixedAmountCurrentTime < Out.FixedAmountTargetTime )
    {
        Out.FixedAmountCurrentTime++;
    }
    else
    {
        StopWaterOut();
        // 연속 추출 시간 만료되면 추출 중지...
        Sound( BUZZER_EFFLUENT_END );
    }
}

static void SyncWaterOutAmount(void)
{
    U8 mu8SyncAmount;

    // /* 좌측 추출o, 우측 추출x */
    // if(GetHotWaterOut() == TRUE && GetWaterOut() == FALSE)
    // {
    //     /* 좌측 정량 추출 중 */
    //     if(IsHotWaterAmountSelected() == TRUE)
    //     {
    //         /* 좌측이 정량 추출 중이라면, 우측 추출은 정량이 아닌 레버로 추출 해야 함 */
    //         SetWaterOutPressContinue(TRUE);
    //         //  SetWaterOutFixedAmountType(AMOUNT_ID_LEVER);
    //     }            
    // }

    // /* 우측 추출 직후 정량 동기화 및 재추출 방지 */
    // if( Out.PrevWaterOut != Out.WaterOut)
    // {
    //     Out.PrevWaterOut = Out.WaterOut;
    //     if( Out.WaterOut== FALSE )
    //     {
    //         /* 1. 정량동기화 : 우측 추출 종료한 시점에 좌측 정량 선택 한 상태라면 우측도 좌측처럼 정량 세팅
    //            둘다 추출 중이지 않고, 정량 선택된 상태라면 먼저 추출하는 쪽이 정량추출됨 */
    //         if(GetHotWaterOut() == FALSE
    //             && GetHotWaterOutPressContinue() == FALSE)
    //         {
    //             SetWaterOutPressContinue(FALSE);
    //         }

    //         /* 2. Unable to re-extract for 0.3 seconds after completion of extraction */
    //         Out.ImpossibleTimer = OUT_PROTECT_TIME;
    //     }
    // }

    // if( Out.ImpossibleTimer != 0 )
    // {
    //     Out.ImpossibleTimer--;  
    // }
}

void  ControlWaterOut(void)
{  
    // SyncWaterOutAmount();           // 좌,우 추출부 정량 동기화
    RightLeverOutSelect();          // Control 냉/정 선택 
    RightLeverOutValve();           // Control Valve
    RightWaterOut();                // 정량 추출 기능 standard
}

void SetTestColdRepeatStatus(U8 mu8Val)
{
    Out.ColdTestRepeatStatus = mu8Val;
}
U8 GetTestColdRepeatStatus(void)
{
    return Out.ColdTestRepeatStatus;
}

void SetTestHotRepeatStatus(U8 mu8Val)
{
    Out.HotTestRepeatStatus = mu8Val;
}
U8 GetTestHotRepeatStatus(void)
{
    return Out.HotTestRepeatStatus;
}

void SetTestAllRepeatStatus(U8 mu8Val)
{
    Out.AllTestRepeatStatus = mu8Val;
}
U8 GetTestAllRepeatStatus(void)
{
    return Out.AllTestRepeatStatus;
}

void SetAgingTestRepeatStatus(U8 mu8Val)
{
    Out.AgingTestRepeatStatus = mu8Val;
}
U8 GetAgingTestRepeatStatus(void)
{
    return Out.AgingTestRepeatStatus;
}

void SetDispAgingConfig(U8 mu8Val)
{
    Out.DispAgingConfig = mu8Val;
}

U8 GetDispAgingConfig(void)
{
    return Out.DispAgingConfig;
}

/* For Wifi, hysteresis */
#define TEMP_OFFSET   (2.0f)
U8 GetHotTempCondition( D64 xDtemp )
{
    static U8 uLevel = TEMP_LEVEL_NONE;
    // U8 mu8Altitude =  ALTITUDE_LEVEL_0;

    // mu8Altitude = GetHotWaterAltidue();

    // if( GetHotWaterConfigMake() == FALSE )
    // {
    //     uLevel = TEMP_LEVEL_NONE;
    //     return uLevel;
    // }

    // if( IsErrorType(ERROR_TYPE_HOT_MAKE) == TRUE )
    // {
    //     uLevel = TEMP_LEVEL_WEAK;
    //     return uLevel;
    // }

    // if( uLevel == TEMP_LEVEL_NONE )
    // {
    //     if( xDtemp >= (GetHotTargetOffTemp(mu8Altitude) - TEMP_OFFSET) )
    //     {
    //         uLevel = TEMP_LEVEL_STRONG;     // strong
    //     }
    //     else
    //     {
    //         uLevel = TEMP_LEVEL_WEAK;      // weak
    //     }
    // }
    // else if( uLevel == TEMP_LEVEL_WEAK )
    // {
    //     if( xDtemp >= (GetHotTargetOffTemp(mu8Altitude) - TEMP_OFFSET) )
    //     {
    //         uLevel = TEMP_LEVEL_STRONG;
    //     }
    // }
    // else if( uLevel == TEMP_LEVEL_STRONG )
    // {
    //     if( xDtemp < ((GetHotTargetOffTemp(mu8Altitude) - TEMP_OFFSET)-(2.0f)) )
    //     {
    //         uLevel = TEMP_LEVEL_WEAK;
    //     }
    // }
    
    return uLevel;
}

/* For Wifi, hysteresis */ 
U8 GetColdTempCondition( D64 xDtemp )
{
    static U8 uLevel = TEMP_LEVEL_NONE;

#if 0
    if(  ( GetConfigCold() == FALSE )
             || ( IsErrorType(ERROR_TYPE_COLD_MAKE) == TRUE ) )
    {
        uLevel = TEMP_LEVEL_NONE;
        return uLevel;
    }
#endif

    // if( GetColdWaterConfigMake() == FALSE )             
    // {
    //     uLevel = TEMP_LEVEL_NONE;
    //     return uLevel;
    // }

    // if( IsErrorType(ERROR_TYPE_COLD_MAKE) == TRUE )
    // {
    //     uLevel = TEMP_LEVEL_WEAK;
    //     return uLevel;
    // }

    // if( uLevel == TEMP_LEVEL_NONE )
    // {
    //     if( xDtemp > 6.0f )    // 6도 기준
    //     {
    //         uLevel = TEMP_LEVEL_WEAK;
    //     }
    //     else
    //     {
    //         uLevel = TEMP_LEVEL_STRONG;
    //     }
    // }
    // else if( uLevel == TEMP_LEVEL_WEAK )
    // {
    //     if( xDtemp <= 6.0f )
    //     {
    //         uLevel = TEMP_LEVEL_STRONG;
    //     }
    // }
    // else if( uLevel == TEMP_LEVEL_STRONG )
    // {
    //     if( xDtemp > ((6.0f)+(2.0f)) )
    //     {
    //         uLevel = TEMP_LEVEL_WEAK;
    //     }
    // }

    return uLevel;
}


