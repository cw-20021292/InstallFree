#include "Global_Header.h"
#include "key_handler.h"
#include "key.h"
#include "key_common_handler.h"
#include "flushing.h"
#include "water_out.h"
#include "water_out_type.h"
#include "hot_water_out.h"
#include "process_display.h"
#include "display_lib.h"

static U8 SelHot(void);
static U8 SelRoom(void);
static U8 SelCold(void);
static U8 SelAmount(void);
static U8 SelHotLockOn(void);
static U8 SelHotLockOff(void);
static U8 SelHotBoostModeOnoff(void);
static U8 SelHotConfigOn(void);
static U8 SelHotConfigOff(void);
static U8 SelExtract(void);

static KeyEventList_T KeyEventList[] =
{
    /* KEY,                   Short,             2sec,               3sec,                 7sec,            Pop,      1sec */
    /* SINGLE KEY */
    { K_HOT,                  SelHot,            NULL,               SelHotBoostModeOnoff, NULL,            NULL,     NULL },
    { K_ROOM,                 SelRoom,           NULL,               NULL,                 NULL,            NULL,     NULL },
    // { K_COLD,                 SelCold,           NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_AMOUNT,               SelAmount,         NULL,               SelHotConfigOn,       NULL,            NULL,     NULL },  
    { K_HOT_LOCK,             NULL,              NULL,               NULL,                 NULL,            NULL,     NULL },
    { K_EXTRACT,             SelExtract,              NULL,          NULL,                 NULL,            NULL,     NULL },
};


/* TEST MODE */
const static KeyEventList_T KeyEventTimeShortList[] =
{
    /* KEY,                 Short,               2sec,            3sec,                    7sec,         Pop,     TS */
    /* SINGLE KEY */
    { K_HOT,                SelHot,              NULL,            NULL,               NULL,         NULL,    NULL }, 
    { K_ROOM,               SelRoom,             NULL,            NULL,                    NULL,         NULL,    NULL },
    // { K_COLD,               SelCold,             NULL,            NULL,                    NULL,         NULL,    NULL },
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
    SetHotWaterOutSelect( mu8Id );
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
        SetWaterOutFixedAmountType( eAmountId );
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
    ResetReturnTime();
    ResetReturnTimeAmount();
    ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();

    // if(GetHotWaterOutSelect() == SEL_WATER_HOT)
    // {
    //     ReSetLockHotDelayTime();
    // }
}

/* 여러개의 disp 타이머 변수들 리셋 */
static void UpdateDispTimer(void)
{
    StartDispTimerId( DISP_TIMER_KEY_AMOUNT );
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
    U8 mu8Sound = BUZZER_SELECT;

    U8           uCursor = 0U;
    EAmountId_T  eAmountId;

    /* 추출중일 땐 물선택 바뀌면 안됨 */
    if(GetWaterOut() == TRUE)
    {
        return BUZZER_OFF;
    }

    // /* 용량 업데이트 */
    uCursor = UpdateAmountCursor();
    eAmountId = GetAmountId(uCursor);
    SetFixedAmount(eAmountId);
    
    // /* 관련된 여러개의 disp 타이머 변수들 세팅 */
    UpdateDispTimer();

    // /* 관련된 여러개의 타이머 변수들 리셋 */
    ResetVariousTimer();

    return mu8Sound;
}

static U8 SelRoom(void)
{
    // ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();

    /* Flushing */
    if(GetFlushingConfig() == TRUE)
    {
        #if 0
        /* 플러싱 관련 에러 인 상태에서는 플러싱 시작 불가 */
        if( IsErrorType(ERROR_TYPE_FLUSHING) == TRUE )
        {
            return BUZZER_ERROR;
        }
        #endif

        #if 0
        /* 강제 플러싱 일 때 */
        if(GetFlushingForceMode() == TRUE)
        {
            SetFlushingSkipChangeType(TRUE);  // 강제 플러싱 모드에서는 필터 플러싱  주기 안바뀜 
        }
        /* 일반적인 플러싱 일 때 */
        else
        {
            /* 필터 교체를 다 안했으면 플러싱 시작 못함 */
            if(GetFilterReplaceStatus() == FILTER_REPLACE_NEED)
            {
                PlayFilterAlarm();
                return BUZZER_OFF;
            }
        }
        #endif

        return BUZZER_OFF;
    }
    
    // if(GetUvTestMode() == TRUE)
    // {
    //     RefreshUvTestModeCancelTime( );  // Refreseh UV TEST MODE time
    //     if( GetTestUvOnOff() == TRUE )
    //     {
    //         SetTestUvOnOff( FALSE );     
    //         return BUZZER_SELECT;
    //     }
    //     else
    //     {
    //         SetTestUvOnOff( TRUE );   
    //         return BUZZER_SELECT;
    //     }
    // }

    // if( GetMementoDisp() == TRUE )
    // {
    //     return BUZZER_OFF;
    // }
    
    /* 추출중일 땐 물선택 바뀌면 안됨 */
    if(GetWaterOut() == TRUE)
    {
        return BUZZER_OFF;
    }

    if( SetSelectWater( SEL_WATER_ROOM ) == TRUE )
    {	
      //  StopDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
#if 0
        StopDisplaySegOff();
        StopDisplaySegOn();
        StopDispTimerId( DISP_TIMER_REPLACE_FILTER );
#endif
        return BUZZER_SELECT;
    }
    
    return BUZZER_ERROR;
}

static U8 SelHot(void)
{
    U8 mu8SelHot;

    ResetReturnTimePressContinue();
    // ResetHotReturnTimePressContinue();
    // ReSetLockHotDelayTime();

#if 0
    /* Unused save config */
    if(GetSmartUnusedSaveConfigMode() == TRUE )
    {
        RefreshSmartUnusedSaveConfigModeCancelTime();
		
        if( GetSmartUnusedSavingConfig() == TRUE )
        {
            SetSmartUnusedSavingConfig( FALSE );      
            SaveEepromId( EEPROM_ID_CONF_UNUSED_SAVE );

            return BUZZER_CANCEL;
        }
        else
        {
            SetSmartUnusedSavingConfig( TRUE );       
            SaveEepromId( EEPROM_ID_CONF_UNUSED_SAVE );
			
            return BUZZER_SETUP;
        }
    }
#endif

#if 0
    /* Altitude */
    if( GetAltidueConfigMode() == TRUE )
    {
        U8 mu8Altitude;

        mu8Altitude = GetHotWaterAltidue();
        mu8Altitude++;
        if( mu8Altitude >= ALTITUDE_LEVEL_NUM )
        {
            mu8Altitude = ALTITUDE_LEVEL_0;
        }
        
        SetHotWaterAltidue( mu8Altitude );
        SetAltitudeConfigMode( TRUE );  // Refreseh Altitude setup time
        SaveEepromId( EEPROM_ID_HOT_ALTITUDE );
    }
#endif

#if 0
	/* hot lock */
    if( Get_HotKeyLockStatus() == ON )
    {
        StartDisplayHotLock();
        return SOUND_ID_ALARM_LOCK_HOT;
    }

    /* Hot OFF -> Hot select? yes -> blink hot water */
    if( GetHotWaterConfigMake() == FALSE)
    {
        StartDisplayHotMake();
        StartDisplaySegOff();
        return SOUND_ID_ALARM_HOT_OFF;
    }
#endif

    /* 온수 에러 발생 */
    if( Get_ErrorStatus ( ERROR_ID_TANK_HOT_TEMP_E45 ) == TRUE )
    {
        return BUZZER_ERROR;
    }

    /* 추출중일 땐 물선택 바뀌면 안됨 */
    if(GetWaterOut() == TRUE)
    {
        return BUZZER_OFF;
    }

    /* 온수잠금 중에는 선택 불가능 */
    if(Get_HotKeyLockStatus() == HOT_KEY_LOCK_ON)
    {
        StartDisplayHotLockSet();
        return BUZZER_ERROR;
    }

    if( SetSelectWater( SEL_WATER_HOT ) == TRUE )
    {
     //   StartDispTimerId( DISP_TIMER_KEY_HOT_TEMP );
#if 0
        StopDispTimerId( DISP_TIMER_UVCARE );
        StopDisplaySegOff();
        StopDisplaySegOn();
        StopDispTimerId( DISP_TIMER_REPLACE_FILTER );

        /* Heating led on? yes -> Start Blink Timer for 7sec */
        if( GetHotTempLevel() == HEATING )
        {
            StartDispTimerId( DISP_TIMER_HEATING_DIMMING_BLINK );	
        }
#endif
        return BUZZER_SELECT;
    }

    return BUZZER_SELECT;
}

static U8 SelHotLockOn(void)
{
    if(Get_HotKeyLockStatus() == HOT_KEY_LOCK_OFF)
    {
        Set_HotKeyLock(HOT_KEY_LOCK_ON);
        return BUZZER_SETUP;
    }

    return BUZZER_OFF;
}

static U8 SelHotLockOff(void)
{
    if(Get_HotKeyLockStatus() == HOT_KEY_LOCK_ON)
    {
        Set_HotKeyLock(HOT_KEY_LOCK_OFF);
        return BUZZER_CANCEL;
    }

    return BUZZER_OFF;
}

static U8 SelHotBoostModeOnoff(void)
{
    if(GetHotWaterBoostMode() == FALSE)
    {
        SetHotWaterBoostMode(TRUE);
        return BUZZER_SETUP;
    }
    else if(GetHotWaterBoostMode() == TRUE)
    {
        SetHotWaterBoostMode(FALSE);
        return BUZZER_CANCEL;
    }

    return BUZZER_OFF;
}

static U8 SelExtract(void)
{
    // 플러싱이 필요할 때
    if(GetFlushingConfig() == TRUE)
    {
        if(GetFlushingRun() == TRUE)
        {
            TurnOffFlush();
            SetFlushingPause(TRUE);  // 플러싱 일시 정지
            SetFlushingStatus(FLUSHING_STATUS_WAIT);
            
            return BUZZER_CANCEL;
        }
        else
        {
            // /* 온수온도센서 에러중이면 안됨 */
            // if( Get_ErrorStatus ( ERROR_ID_TANK_HOT_TEMP_E45 ) == TRUE )
            // {
            //     return BUZZER_ERROR;
            // }

            /* 필터체크 */
            if(Get_ReedSW_Status(REED_SW_ID_FILTER_REED) == FALSE)
            {
                return BUZZER_ERROR;
            }
            
            TurnOnFlush(); 
            SetFlushingStatus(FLUSHING_STATUS_ING);
            
            return BUZZER_SETUP;
        }
    }
    
    /* 추출중일 땐 물선택 바뀌면 안됨 */
    if(GetWaterOut() == TRUE)
    {
        StopWaterOut();
        return BUZZER_EFFLUENT_END;
    }
    else
    {
        StartWaterOut();
    }

    return BUZZER_EFFLUENT;
}

static U8 SelHotConfigOn(void)
{
    if(GetHotWaterConfigMake() == FALSE)
    {
        SetHotWaterConfigMake(TRUE);
        return BUZZER_SETUP;
    }
    else if(GetHotWaterConfigMake() == TRUE)
    {
        SetHotWaterConfigMake(FALSE);
        return BUZZER_CANCEL;
    }

    return BUZZER_OFF;
}

static U8 SelHotConfigOff(void)
{
    if(GetHotWaterConfigMake() == TRUE)
    {
        SetHotWaterConfigMake(FALSE);
        return BUZZER_CANCEL;

    }

    return BUZZER_OFF;
}