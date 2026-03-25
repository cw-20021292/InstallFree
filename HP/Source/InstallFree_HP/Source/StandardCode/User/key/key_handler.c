#include "Global_Header.h"
#include "key_handler.h"
#include "key.h"
#include "key_common_handler.h"
#include "flushing.h"
#include "water_out_type.h"

static U8 SelHot(void);
static U8 SelRoom(void);
static U8 SelCold(void);
static U8 SelAmount(void);


static KeyEventList_T KeyEventList[] =
{
    /* KEY,                   Short,             2sec,               3sec,                 7sec,            Pop,      1sec */
    /* SINGLE KEY */
    { K_HOT,                  SelHot,            NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_ROOM,                 SelRoom,           NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_COLD,                 SelCold,           NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_HOT_LOCK,             NULL,              NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_AMOUNT,               SelAmount,         NULL,               NULL,                 NULL,            NULL,     NULL },  
};


/* TEST MODE */
const static KeyEventList_T KeyEventTimeShortList[] =
{
    /* KEY,                 Short,               2sec,            3sec,                    7sec,         Pop,     TS */
    /* SINGLE KEY */
    { K_HOT,                SelHot,              NULL,            NULL,               NULL,         NULL,    NULL }, 
    { K_ROOM,               SelRoom,             NULL,            NULL,                    NULL,         NULL,    NULL },
    { K_COLD,               SelCold,             NULL,            NULL,                    NULL,         NULL,    NULL },
    { K_AMOUNT,             SelAmount,           NULL,            NULL,                    NULL,         NULL,    NULL },

    /* MULTI KEY */
    { K_TEST_AGING,         NULL,            NULL,                NULL,    NULL,         NULL,    NULL },
};

U8 IsValidKeyCondition(U16 mu16Key)
{
    // /* CONFIG HOT UNUSED SAVE */
    // if( GetSmartUnusedSaveConfigMode() == TRUE )
    // {
    //     if( mu16Key != K_SMART_UNUSED_SAVE 
    //             && mu16Key != K_HOT )
    //     {
    //         return FALSE;
    //     }
    // }

    // /* CONFIG COLD WEAK */
    // if( GetColdWeakConfigMode() == TRUE )
    // {
    //     if( mu16Key != K_COLD_WEAK
    //        && mu16Key != K_HOT_LOCK )
    //     {
    //         return FALSE;
    //     }
    // }

    // /* CONFIG HOT ALTITUDE */
    // if( GetAltidueConfigMode() == TRUE )
    // {
    //     if( mu16Key != K_ALTITUDE 
    //             && mu16Key != K_HOT )
    //     {
    //         return FALSE;
    //     }
    // }

    // /* UV TEST MODE */
    // if( GetUvTestMode() == TRUE )
    // {
    //     if( mu16Key != K_TEST_UV 
    //             && mu16Key != K_ROOM )
    //     {
    //         return FALSE;
    //     }
    // }	

    // /* MEMENTO DISPLAY */
    // if( GetMementoDisp() == TRUE )
    // {
    //     if( mu16Key != K_MEMENTO )
    //     {
    //         return FALSE;
    //     }
    // }

    // /* Flushing Change Type Mode */
    // if( GetFlushingFilterChangeTypeMode() == TRUE )
    // {
    //     if( mu16Key != K_COLD 
    //         && mu16Key != K_FILTER_TYPE_CHANGE )
    //     {
    //         return FALSE;
    //     }
    // }

    // /* Fist Init Flushing or Filter Change Flushing */
    // if( GetFlushingConfig() == TRUE )
    // {
    //     // 정수키와 냉수키(플러싱 취소 냉수3초), 플러싱강제완료 키는 제외
    //     if( mu16Key != K_ROOM
    //         && mu16Key != K_COLD 
    //          && mu16Key != K_FLUSHING_COMPLETE )
    //     {
    //         return FALSE;
    //     }
    // }
        
    // /* Citric Acod Flushing */
    // if( GetCitricFlushConfig() == TRUE )
    // {
    //     return FALSE;   // 모든 키 터치 x
    // }
        
    // /* 전체 장금 중 */
    // if( GetLockAll() == LOCK )
    // {
    //     /* 플러싱, 구연산 세척 일때는 전체잠금 안되도록 */
    //     if( GetFlushingConfig() == FALSE
    //        && GetCitricFlushConfig() == FALSE )
    //     {
    //         if( mu16Key != K_LOCK_ALL )
    //         {
    //              StartDisplayLockAll();  // chp lock all -> blink hotlock, room_water
    //             //StartDisplayHotLock();
    //             //StartDisplayRoomWater();
    //             return FALSE;
    //         }
    //     }
    // }
        
    // /* 우측(정수,냉수) 추출 중 */
    // if( GetWaterOut() == TRUE )
    // {    
    //     if( GetHotWaterOutSelect() == SEL_WATER_HOT )
    //     {    
    //         /* 레버로 추출 중일 때는 동시추출을 위해 온수,정량 선택 가능 */
    //         if( GetWaterOutPressContinue() == TRUE ) 
    //         {
    //             if( mu16Key != K_HOT
    //                   && mu16Key != K_AMOUNT )
    //             {
    //                 return FALSE;
    //             }
    //         }
    //         /* 정량 추출 중일 때는 동시추출을 위해 온수 선택 가능  */
    //         else
    //         {
    //             if( mu16Key != K_HOT )
    //             {
    //                 return FALSE;
    //             }
    //         }
    //     }
    //     /* 온수 선택 안되어 있을 때, 온수 잠금,온수 키만 선택 가능 */
    //     else
    //     {
    //         if( mu16Key != K_HOT_LOCK
    //             && mu16Key != K_HOT )
    //         {
    //             return FALSE;
    //         }
    //     }           
    // }
    
    // /* 좌측(온수) 추출 중 */
    // if( GetHotWaterOut() == TRUE )
    // {
    //     /* 레버로 추출 중일 때는 동시추출을 위해 정수,냉수,정량 선택 가능  */
    //     if( GetHotWaterOutPressContinue() == TRUE ) 
    //     {
    //         if( mu16Key != K_ROOM
    //               && mu16Key != K_COLD
    //                  && mu16Key != K_AMOUNT )
    //         {
    //             return FALSE;
    //         }
    //     }
    //     /* 정량 추출 중일 때는 동시추출을 위해 정수,냉수 선택 가능  */
    //     else
    //     {
    //         if( mu16Key != K_ROOM
    //               && mu16Key != K_COLD )
    //         {
    //             return FALSE;
    //         }
    //     }
    // }

    // /* 우측,좌측 모두 추출 중일 때 */
    // if( GetWaterOut() == TRUE && GetHotWaterOut() == TRUE )
    // {
    //     return FALSE;
    // }

    return TRUE;
}

void* GetKeyEventList(void)
{
    // if( GetTimeShortStatus() == TRUE )
    // {
    //     return KeyEventTimeShortList;
    // }

    return KeyEventList;
}

U8 GetKeyEventListSize(void)
{
    // if( GetTimeShortStatus() == TRUE )
    // {
    //     return ( sizeof(KeyEventTimeShortList) / sizeof(KeyEventList_T) );
    // }

    return ( sizeof(KeyEventList) / sizeof(KeyEventList_T) );
}

U8 SetSelectWater( U8 mu8Id )
{
    SetWaterOutSelect( mu8Id );
    return TRUE;
}

U8 SetSelectHotWater( U8 mu8Id )
{
    // SetHotWaterOutSelect( mu8Id );
    return TRUE;
}

static void SetFixedAmount(U8 eAmountId)
{
    // /* 우측(정수or냉수) 추출 중 */
    // if(GetWaterOut() == TRUE)
    // {
    //     SetHotWaterOutFixedAmountType( eAmountId );
    // }
    // /* 우측(정수or냉수) 추출 중이지 않을 때 */
    // else
    // {
    //     SetWaterOutFixedAmountType( eAmountId );
    // }    
     
    //  /* 좌측(온수) 추출 중 */
    // if(GetHotWaterOut() == TRUE)
    // {
    //     SetWaterOutFixedAmountType( eAmountId );
    // }
    // /* 좌측(온수) 추출 중이지 않을 때 */
    // else
    // {
    //     SetHotWaterOutFixedAmountType( eAmountId );
    // }
}

/* 여러개의 타이머 변수들 리셋 */
static void ResetVariousTimer(void)
{
    // ResetReturnTime();
    // ResetReturnTimeAmount();
    // ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();

    // if(GetHotWaterOutSelect() == SEL_WATER_HOT)
    // {
    //     ReSetLockHotDelayTime();
    // }
}

/* 여러개의 disp 타이머 변수들 리셋 */
static void UpdateDispTimer(void)
{
//     StartDispTimerId( DISP_TIMER_KEY_AMOUNT );
//    // StartDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
//     StopDispTimerId( DISP_TIMER_UVCARE );
//     StopDisplaySegOff();
//     StopDisplaySegOn();
}


/* 용량 -> 레버 로 넘어갈때 효과음 */
static U8 SoundEffectLever(void)
{
    // if(GetWaterOut() == TRUE && GetWaterOutPressContinue() == TRUE )
    // {
    //    // if(GetHotWaterOutFixedAmountType() == AMOUNT_ID_LEVER)
    //     if(GetHotWaterOutPressContinue() == TRUE)
    //     {
    //         return TRUE;
    //     }
    // }

    // if(GetHotWaterOut() == TRUE && GetHotWaterOutPressContinue() == TRUE )
    // {
       // if(GetWaterOutFixedAmountType() == AMOUNT_ID_LEVER)
        // if(GetWaterOutPressContinue() == TRUE)
        // {
        //     return TRUE;
        // }
    // }

    // if(GetWaterOut() == FALSE && GetHotWaterOut() == FALSE )
    // {
    //   //  if(GetHotWaterOutFixedAmountType() == AMOUNT_ID_LEVER
    //   //      || GetWaterOutFixedAmountType() == AMOUNT_ID_LEVER)
    //     if(GetWaterOutPressContinue() == TRUE
    //     || GetHotWaterOutPressContinue() == TRUE)
    //     {
    //         return TRUE;
    //     }
    // }

    return FALSE;
}

static U8 SelAmount(void)
{
    // U8 mu8Sound = SOUND_ID_SELECT;

    // U8           uCursor = 0U;
    // EAmountId_T  eAmountId;

    // /* 용량 업데이트 */
    // uCursor = UpdateAmountCursor();
    // eAmountId = GetAmountId(uCursor);
    // SetFixedAmount(eAmountId);
    
    // /* 관련된 여러개의 disp 타이머 변수들 세팅 */
    // UpdateDispTimer();

    // /* 관련된 여러개의 타이머 변수들 리셋 */
    // ResetVariousTimer();

    // /* 용량 -> 레버 로 넘어갈때 효과음 */
    // if( SoundEffectLever() == TRUE )
    // {
    //     mu8Sound = SOUND_ID_CANCEL;
    // }
   
    // return mu8Sound;

    return 0;
}

static U8 SelRoom(void)
{
    // ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();

    // /* Flushing */
    // if(GetFlushingConfig() == TRUE)
    // {    
    //     /* 플러싱 관련 에러 인 상태에서는 플러싱 시작 불가 */
    //     if( IsErrorType(ERROR_TYPE_FLUSHING) == TRUE )
    //     {
    //         return SOUND_ID_ERROR;
    //     }
    
    //     /* 강제 플러싱 일 때 */
    //     if(GetFlushingForceMode() == TRUE)
    //     {
    //         SetFlushingSkipChangeType(TRUE);  // 강제 플러싱 모드에서는 필터 플러싱  주기 안바뀜 
    //     }
    //     /* 일반적인 플러싱 일 때 */
    //     else
    //     {
    //         /* 필터 교체를 다 안했으면 플러싱 시작 못함 */
    //         if(GetFilterReplaceStatus() == FILTER_REPLACE_NEED)
    //         {
    //             PlayFilterAlarm();
    //             return SOUND_ID_NONE;
    //         }
    //     }

    //     if(GetFlushingRun() == TRUE)
    //     {
    //         TurnOffFlush();
    //         SetFlushingPause(TRUE);  // 플러싱 일시 정지
    //         SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //         return SOUND_ID_CANCEL;
    //     }
    //     else
    //     {
    //         /* 탱크 탐 커버 체결 유무 */
    //         if( GetCurrentInputVal(INPUT_ID_COLD_TANK_COVER) == OPEN )
    //         {
    //             return SOUND_ID_COVER_OPEN_TOP;
    //         }

    //         /* 프론트 필터커버 체결 유무 */
    //         if(IsOpenFilter(FILTER_ID_COVER_FRONT) == FILTER_OPEN)
    //         {
    //             return SOUND_ID_ALARM_COVER_OPEN_FRONT;
    //         }

    //         /* NEO, RO, INNO 필터 체크 */
    //         if( GetFilterOpenStatus() == FILTER_OPEN )
    //         {
    //             return SOUND_ID_ERROR;
    //         }

    //         if(IsOpenFilter(FILTER_ID_RO) == FILTER_OPEN) // 예외 상황 1,3필터주기에 2번필터 장착 안한상태로 플러싱 시도할 경우
    //         {
    //             /* 띠링띠링 -> 다음과 같은 음성 있으면 더 좋을거 같음 "2번 필터가 장착되어있지 않습니다" */
    //             return SOUND_ID_ERROR;    
    //         }
            
    //         TurnOnFlush(); 
    //         SetFlushingStatus(FLUSHING_STATUS_ING);
    //         SetFlushingCancelDisable(TRUE);  // 한 번 시작하면 취소 불가능(전원 재인가하더라도 불가능)

    //         return SOUND_ID_SETUP;
    //     }
    // }
    
    // if(GetUvTestMode() == TRUE)
    // {
    //     RefreshUvTestModeCancelTime( );  // Refreseh UV TEST MODE time
    //     if( GetTestUvOnOff() == TRUE )
    //     {
    //         SetTestUvOnOff( FALSE );     
    //         return SOUND_ID_SELECT;
    //     }
    //     else
    //     {
    //         SetTestUvOnOff( TRUE );   
    //         return SOUND_ID_SELECT;
    //     }
    // }

    // if( GetMementoDisp() == TRUE )
    // {
    //     return SOUND_ID_NONE;
    // }

    // if( SetSelectWater( SEL_WATER_ROOM ) == TRUE )
    // {	
    //   //  StopDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
    //     StopDisplaySegOff();
    //     StopDisplaySegOn();
    //     StopDispTimerId( DISP_TIMER_REPLACE_FILTER );

    //     return SOUND_ID_SELECT;
    // }
    
    // return SOUND_ID_ERROR;
    return 0;
}

static U8 SelCold(void)
{
#if 0
    ResetReturnTimePressContinue();
    ResetHotReturnTimePressContinue();

   // StopDispTimerId( DISP_TIMER_KEY_HOT_TEMP );

    /* 플러싱 취소 불가능해지고나서부터는 선택하면 에러음 발생 */
    if(GetFlushingConfig() == TRUE)
    {
        if( GetFlushingCancelDisable() == TRUE   // 최초 1회만 취소 가능 // TRUE : 취소 불가능
             || GetFlushingType() == FLUSHING_TYPE_FIRST )  
        {
            return SOUND_ID_ERROR;
        }
             
        return SOUND_ID_SELECT;            
    }
    
    /* TIME SHORT모드(기밀 검사모드로 사용 중) */
    if (GetTimeShortStatus() == TRUE)
    {
        SetSelectWater( SEL_WATER_COLD );
        return SOUND_ID_NONE;
    }

    /* Flushing Change Type Mode */
    if( GetFlushingFilterChangeTypeMode() == TRUE )
    {
        UpdateFilterChangeType();
        return SOUND_ID_SETUP;
    }

    if( GetColdWaterConfigMake() == FALSE)
    {
        StartDisplayColdMake();
        StartDisplaySegOff();
        SetSelectWater( SEL_WATER_COLD );
        return SOUND_ID_ERROR;
    }

    /* 냉수 약 */
    if( GetColdWeakConfigMode() == TRUE )
    {		
        RefreshColdWeakConfigModeCancelTime();
        if( GetColdWeakConfig() == TRUE )
        {
            SetColdWeakConfig( FALSE );      
            SaveEepromId( EEPROM_ID_COLD_WEAK );

            return SOUND_ID_CANCEL;
        }
        else
        {
            SetColdWeakConfig( TRUE );       
            SaveEepromId( EEPROM_ID_COLD_WEAK );
			
            return SOUND_ID_SETUP;
        }
    }

    if( SetSelectWater( SEL_WATER_COLD ) == TRUE )
    {
      //  StopDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
        StopDisplaySegOff();
        StopDisplaySegOn();
        StopDispTimerId( DISP_TIMER_REPLACE_FILTER );

        /* Cooling led on? yes -> Start Blink Timer for 7sec */
        if( GetColdTempLevel() == COOLING )
        {
            StartDispTimerId( DISP_TIMER_COOLING_DIMMING_BLINK );	
        }        

        return SOUND_ID_SELECT;
    }

    return SOUND_ID_ERROR;
#endif
    return 0;
}

static U8 SelHot(void)
{
    // U8 mu8SelHot;

    // ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();
    // ReSetLockHotDelayTime();

    // /* Unused save config */
    // if(GetSmartUnusedSaveConfigMode() == TRUE )
    // {
    //     RefreshSmartUnusedSaveConfigModeCancelTime();
		
    //     if( GetSmartUnusedSavingConfig() == TRUE )
    //     {
    //         SetSmartUnusedSavingConfig( FALSE );      
    //         SaveEepromId( EEPROM_ID_CONF_UNUSED_SAVE );

    //         return SOUND_ID_CANCEL;
    //     }
    //     else
    //     {
    //         SetSmartUnusedSavingConfig( TRUE );       
    //         SaveEepromId( EEPROM_ID_CONF_UNUSED_SAVE );
			
    //         return SOUND_ID_SETUP;
    //     }
    // }
   
    // /* Altitude */
    // if( GetAltidueConfigMode() == TRUE )
    // {
    //     U8 mu8Altitude;

    //     mu8Altitude = GetHotWaterAltidue();
    //     mu8Altitude++;
    //     if( mu8Altitude >= ALTITUDE_LEVEL_NUM )
    //     {
    //         mu8Altitude = ALTITUDE_LEVEL_0;
    //     }
        
    //     SetHotWaterAltidue( mu8Altitude );
    //     SetAltitudeConfigMode( TRUE );  // Refreseh Altitude setup time
    //     SaveEepromId( EEPROM_ID_HOT_ALTITUDE );
    // }

	// /* hot lock */
    // if( GetLockHot() == LOCK )
    // {
    //     StartDisplayHotLock();
    //     return SOUND_ID_ALARM_LOCK_HOT;
    // }

    // /* Hot OFF -> Hot select? yes -> blink hot water */
    // if( GetHotWaterConfigMake() == FALSE)
    // {
    //     StartDisplayHotMake();
    //     StartDisplaySegOff();
    //     return SOUND_ID_ALARM_HOT_OFF;
    // }

    // /* 온수 에러 발생 */
    // if( IsError( ERR_ID_TEMP_HOT_WATER ) == TRUE )
    // {
    //     return SOUND_ID_ERROR_HOT;
    // }

    // if( SetSelectHotWater( SEL_WATER_HOT ) == TRUE )
    // {
    //  //   StartDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
    //     StopDispTimerId( DISP_TIMER_UVCARE );
    //     StopDisplaySegOff();
    //     StopDisplaySegOn();
    //     StopDispTimerId( DISP_TIMER_REPLACE_FILTER );

    //     /* Heating led on? yes -> Start Blink Timer for 7sec */
    //     if( GetHotTempLevel() == HEATING )
    //     {
    //         StartDispTimerId( DISP_TIMER_HEATING_DIMMING_BLINK );	
    //     }
    //     return SOUND_ID_SELECT;
    // }

    // return SOUND_ID_SELECT;
    return 0;
}


