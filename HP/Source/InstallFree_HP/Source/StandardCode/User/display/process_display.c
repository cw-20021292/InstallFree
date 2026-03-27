#include "Global_Header.h"

#include "hal_led.h"
#include "display.h"
#include "process_display.h"
#include "hot_water.h"
#include "display.h"
#include "water_out.h"
#include "water_out.h"
#include "amount.h"
#include "flushing.h"
#include "hot_water_out.h"
#include "key_handler.h"
#include "display_lib.h"
#include "water_out_type.h"
#include "error.h"
#include "display_error.h"

static void DisplayWaterTempLevel(void);
static void DisplayColdLowWater(void);
static void DisplayRoomLowWater(void);
static void DisplayHotLowWater(void);
static void DisplayWaterLevel(void);
static void DisplayLowWaterTimeShort(void);
static void DisplayColdMakeBlink(void);
static void DisplayHotMakeBlink(void);
static void DisplayWaterOutPoint(void);
static void DisplayLock(void);
static void DisplayLockAll(void);
static void DisplayLockHot(void);
static void DisplayLockHotSet(void);
static void DisplayLockIcon(void);
static void DisplaySelWater(void);
static void DisplaySelHot(void);
static void DisplaySelAmount(void);
static void DisplayWaterOut(void);
static void DisplayTempLevelCold( U8 mu8OnOff, D64 mTemp );
static void DisplayTempLevelHot( U8 mu8OnOff, D64 mTemp );
static void DisplayHeating( D64 mTemp );
static void DisplayHotBlink(void);
static void DisplayColdRoomBlink(void);
static void DispFlushingProgress(void);
static void DispExtractDimmingBlink(void);
static void DisplayFilterFlushing(void);
static void DisplayReplaceFilter(void);

static void UpdateTimer(void);

static void ProcessDisplayBoot(void);
static void ProcessDisplayNormalMode(void);
static void ProcessDisplayErrorMode(void);
static void ProcessFlushingDisplayErrorMode(void);
static void ProcessDisplayVersionMode(void);
static void ProcessDisplayColdWeak(void);
static void ProcessDisplayUvTest(void);
static void ProcessDisplayFlushing(void);
static void ProcessDisplayCitricFlush(void);
static U16 GetWaterOutPercent(void);
static U16 GetHotWaterOutPercent(void);

static void InitDispBleParingTimer(void);
static U8 GetDispBlePairingTimer(void);

typedef struct _display_
{
    U8 Mode;       // NORMAL / VERSION / UART TEST / ...

    U8 Init;            /* FALSE : 초기화 전, TRUE : 초기화 완료 */
    U8 Version;         /* 버전 표시 FLAG */
    U8 VersionStep;
    U8 VersionOnTime;   /* 버전 표시 시간 @sec*/

    U16 BlinkTime_5s;   /* LED 점멸 타이머 0.5sec */
    U16 BlinkTime_1s;   /* LED 점멸 타이머 1sec */
    U16 BlinkTime_4s;   /* LED 점멸 타이머 3sec on, 1sec off */

    /* Setting Menu */
    U8 Setting;   

    /* 고도 설정 */
    U8  AltiConfigMode;              /* 고도 설정 동작 FLAG */
    U16 AltiConfigModeTimeOut;       /* 고도 설정 자동 해제 시간 타이머 ( @100ms ) */

    /* UV test mode 설정 */
    U8  UvTestMode;                  /* UV TEST MODE 설정 동작 FLAG */
    U16 UvTestModeTimeOut;           /* UV TEST MODE 설정 자동 해제 시간 타이머 ( @100ms ) */

    /* unused saving config mode 설정 */
    U8  SmartUnusedSaveConfigMode;         /* Smart unused saving config mode 설정 동작 FLAG */
    U16 SmartUnusedSaveConfigModeTimeOut;  /* Smart unused saving config mode 설정 자동 해제 시간 타이머 ( @100ms ) */

    /* cold weak config mode 설정 */
    U8  ColdWeakConfigMode;          /* cold weak config mode 설정 동작 FLAG */
    U16 ColdWeakConfigModeTimeOut;   /* cold weak config mode 설정 자동 해제 시간 타이머 ( @100ms ) */

    /* 살균 시간 변경 */
    U8  AdjustHourConfig;
    U16 AdjustHourTimeOut;
    
    /* 자동 배수 설정/해제 */
    U8  DrainWaterConfig;
    U16 DrainWaterTimeOut;
    
    /* Memento */
    U8 Memento;              /* 메멘토 동작 FLAG */
    U8 MementoStep;          /* 메멘토 표시 동작 STEP */
    U8 MementoTimer;         /* 메멘토 표시 동작 시간 타이머 */
    
    /* 온수 잠금 셋팅 */
    U8 HotLockSet;
    
    /* 온수 잠금 */
    U8 HotLock;              /* hot+warm lock 온수 잠금 시, 온수 선택 */
    U16 HotLockTime;         /* LED 표시 5초 타이머 */

    /* 온수 꺼짐 */
    U8 HotMake;              /* 온수 꺼짐 시, 온수 버튼 선택 시 점멸 */
    
    /* 냉수 꺼짐 */
    U8 ColdMake;             /* 냉수 꺼짐 시, 냉수 버튼 선택 시 점멸 */

    /* 잠금 아이콘 */
    U8 IconLock;             /* 온수 잠금, 얼음  잠금, 전체 잠금   시 같이 점멸   */

    /* 전체 잠금 셋팅 */
    U8 AllLockSet;

    /* 전체 잠금 */
    U8 AllLock;              /* not used */ /* 전체 잠금 시, 전체 버튼   Lock */

    /* 저수위 */
    U8 LowWater; 

    U8 HotWater; 
    U8 WarmWater; 
    U8 ColdWater;
    U8 RoomWater;

    DispSegState_T SegState;
        
    U16 ConfigTime;     /* 기능 설정 진입 제한 타이머 */

    U8 Fota;
} Display_T;

Display_T   Disp;

void InitDisplay(void)
{
    // TIMER 
    InitDispTimer();
    SetDispTimer( DISP_TIMER_CONFIG_TIME, TIMER_30SEC );
    //StartDispTimerId( DISP_TIMER_SLEEP );

    //Disp.Mode = DISP_MODE_VERSION;
    Disp.BlinkTime_5s = 0;
    Disp.BlinkTime_1s = 0;
    Disp.BlinkTime_4s = 0;

    /* Booting Display - Showing Blink Front Display */
    Disp.Init = FALSE;

    /* Hot Water Config Altitude mode */
    Disp.AltiConfigMode  = FALSE;
    Disp.AltiConfigModeTimeOut = 0;

    /* UV test mode */
    Disp.UvTestMode  = FALSE;
    Disp.UvTestModeTimeOut = 0;

    /* Unused saving config MODE */
    Disp.SmartUnusedSaveConfigMode  = FALSE;
    Disp.SmartUnusedSaveConfigModeTimeOut = 0;

    /* Cold weak config mode */
    Disp.ColdWeakConfigMode  = FALSE;  
    Disp.ColdWeakConfigModeTimeOut = 0;   
    
    /* 살균 시간 조정 */
    Disp.AdjustHourConfig  = FALSE;
    Disp.AdjustHourTimeOut = 0;

    /* Version */
    Disp.Version = TRUE;
    
    Disp.ConfigTime  = 300;

    Disp.LowWater = FALSE;
    Disp.HotWater = FALSE;
    Disp.WarmWater = FALSE;	
    Disp.ColdWater = FALSE;
    Disp.RoomWater = FALSE;	

    Disp.SegState = DISP_STATE_NONE;
    
    /* TURN OFF ALL LED */
    TurnOffAllLED();
    TurnOffAllSeg();
}

typedef struct _disp_id_time_
{
    U8 id;
    U16 mTime;
} DispTimerVal_T;

//static DispTimerVal_T DispTimerValTable[] = 
DispTimerVal_T DispTimerValTable[] = 
{
    { DISP_TIMER_CLOCK,                 TIMER_20SEC  },  
    //{ DISP_TIMER_ERROR,                 TIMER_3SEC },

    { DISP_TIMER_CONFIG_AMOUNT,         TIMER_2SEC  },     
    //{ DISP_TIMER_ALARM_SETTING,         TIMER_2SEC },
    //{ DISP_TIMER_ALARM_LOCK_ALL,        TIMER_2SEC },      
    //{ DISP_TIMER_ALARM_LOCK_HOT,        TIMER_2SEC },      
    //{ DISP_TIMER_ALARM_LOCK_ICE,        TIMER_2SEC },      
    //{ DISP_TIMER_ALARM_MAKE_OFF_ICE,    TIMER_2SEC },      
    //{ DISP_TIMER_ALARM_MAKE_OFF_COLD,   TIMER_2SEC },      

    //{ DISP_TIMER_WIFI_AP_ERROR,         TIMER_5SEC },

    //{ DISP_TIMER_UP,                    TIMER_1SEC },
    //{ DISP_TIMER_DOWN,                  TIMER_1SEC },
    //{ DISP_TIMER_NEXT,                  TIMER_1SEC },

    //{ DISP_TIMER_CUSTOMER_MENU,         TIMER_6SEC },
    //{ DISP_TIMER_SOUND_MENU,            TIMER_6SEC },

    //{ DISP_TIMER_KEY_ICE,               TIMER_7SEC },  
    { DISP_TIMER_KEY_AMOUNT,            TIMER_7SEC  },
    { DISP_TIMER_KEY_HOT,               TIMER_7SEC  },
    { DISP_TIMER_KEY_HOT_TEMP,          TIMER_7SEC  },
    { DISP_TIMER_UVCARE,                TIMER_30SEC },
    { DISP_TIMER_COOLING_DIMMING_BLINK, TIMER_7SEC  },	
    { DISP_TIMER_HEATING_DIMMING_BLINK, TIMER_7SEC  },	
    { DISP_TIMER_REPLACE_FILTER,        TIMER_7SEC  },	
        
    //{ DISP_TIMER_SETTING_MENU,          TIMER_20SEC },
    //{ DISP_TIMER_CLOCK_MENU,            TIMER_20SEC },
    //{ DISP_TIMER_SLEEP,                 TIMER_60MIN },

    //{ DISP_TIMER_ON,                    TIMER_2SEC },
    //{ DISP_TIMER_OFF,                   TIMER_2SEC },
    //{ DISP_TIMER_SETTING_CLOCK,         TIMER_2SEC }
};
#define SZ_DISP_TIMER_TABLE (sizeof(DispTimerValTable)/sizeof(DispTimerVal_T))


static U16 FindTimeVal(U8 id)
{
    U8 i;

    for( i = 0; i < SZ_DISP_TIMER_TABLE; i++ )
    {
        if( id == DispTimerValTable[ i ].id )
        {
            return DispTimerValTable[ i ].mTime;
        }
    }

    return 0;   // timer 0...
}

U8 GetDisplayInit(void)
{
    return Disp.Init;
}

U8 GetDispSegState(void)
{
    return Disp.SegState;
}

void SetDispSegState(U8 mu8Val)
{
    Disp.SegState = mu8Val;
}

// Display Timer start/stop
void StartDispTimerId(U8 id)
{
    U16 mTime;

    mTime = FindTimeVal( id );
    SetDispTimer( id, mTime );
}

void StopDispTimerId(U8 id)
{
    SetDispTimer( id, 0);
}

void StartDisplayInit(void)
{
    Disp.Init = FALSE;
}

// 냉수 꺼짐 점멸 시작/정지
void StartDisplayColdMake(void)
{
    Disp.ColdMake      = TRUE;
    SetDispTimer( DISP_TIMER_COLDMAKE, TIMER_5SEC);
}

void StopDisplayColdMake(void)
{
    Disp.ColdMake     = FALSE;
    SetDispTimer( DISP_TIMER_COLDMAKE, 0);
}

// 온수 꺼짐 점멸 시작/정지_5sec
void StartDisplayHotMake(void)
{
    Disp.HotMake      = TRUE;
    SetDispTimer( DISP_TIMER_HOTMAKE, TIMER_5SEC);
}

void StopDisplayHotMake(void)
{
    Disp.HotMake     = FALSE;
    SetDispTimer( DISP_TIMER_HOTMAKE, 0);
}

// "OFF" 점등 시작/정지_5sec
void StartDisplaySegOff(void)
{
    SetDispTimer( DISP_TIMER_SEGOFF, TIMER_5SEC);
}

void StopDisplaySegOff(void)
{
    SetDispTimer( DISP_TIMER_SEGOFF, 0);
}

// "ON" 점등 시작/정지_5sec
void StartDisplaySegOn(void)
{
    SetDispTimer( DISP_TIMER_SEGON, TIMER_5SEC);
}
void StopDisplaySegOn(void)
{
    SetDispTimer( DISP_TIMER_SEGON, 0);
}


// 온수 점멸 시작/정지_2sec
void StartDisplayHotWater(void)
{
    Disp.HotWater      = TRUE;
    SetDispTimer( DISP_TIMER_HOW_WATER, TIMER_2SEC);
}

void StopDisplayHotWater(void)
{
    Disp.HotWater     = FALSE;
    SetDispTimer( DISP_TIMER_HOW_WATER, 0);
}

// 냉수 점멸 시작/정지_2sec
void StartDisplayColdWater(void)
{
    Disp.ColdWater      = TRUE;
    SetDispTimer( DISP_TIMER_COLD_WATER, TIMER_2SEC);
}

void StopDisplayColdWater(void)
{
    Disp.ColdWater     = FALSE;
    SetDispTimer( DISP_TIMER_COLD_WATER, 0);
}

// 정수 점멸 시작/정지_2sec
void StartDisplayRoomWater(void)
{
    Disp.RoomWater     = TRUE;
    SetDispTimer( DISP_TIMER_ROOM_WATER, TIMER_2SEC);
}

void StopDisplayRoomWater(void)
{
    Disp.RoomWater     = FALSE;
    SetDispTimer( DISP_TIMER_ROOM_WATER, 0);
}

// 온수 잠금 설정 점멸 시작/정지
void StartDisplayHotLockSet(void)
{
    Disp.HotLockSet = TRUE;
    SetDispTimer( DISP_TIMER_HOTLOCK_SET, TIMER_2SEC);
}

void StopDisplayHotLockSet(void)
{
    Disp.HotLockSet = FALSE;
    SetDispTimer( DISP_TIMER_HOTLOCK_SET, 0);
}

// hot 잠금 점멸 시작/정지
void StartDisplayHotLock(void)
{
    Disp.HotLock     = TRUE;
    SetDispTimer( DISP_TIMER_HOTLOCK, TIMER_2SEC);
}

void StopDisplayHotLock(void)
{
    Disp.HotLock     = FALSE;
    SetDispTimer( DISP_TIMER_HOTLOCK, 0);
}


/* Water Out LEFT */
void StartDisplayWaterOutPointLeft(void)
{
    SetDispTimer( DISP_TIMER_WATER_OUT_POINT_LEFT, TIMER_7SEC);
}

void StopDisplayWaterOutPointLeft(void)
{
    SetDispTimer( DISP_TIMER_WATER_OUT_POINT_LEFT, 0);
}

/* Water Out RIGHT */
void StartDisplayWaterOutPointRight(void)
{
    SetDispTimer( DISP_TIMER_LED_WATER_OUT, TIMER_7SEC);
}

void StopDisplayWaterOutPointRight(void)
{
    SetDispTimer( DISP_TIMER_LED_WATER_OUT, 0);
}

/* Water Out LEFT + RIGHT */
void StopDisplayWaterOutPoint(void)
{
	StopDisplayWaterOutPointLeft(); 
    StopDisplayWaterOutPointRight();
}


// 전체 잠금 설정 점멸 시작/정지
void StartDisplayLockAllSet(void)
{
    Disp.AllLockSet     = TRUE;
    SetDispTimer( DISP_TIMER_ALLLOCK_SET, TIMER_2SEC);
}

void StopDisplayLockAllSet(void)
{
    Disp.AllLockSet     = FALSE;
    SetDispTimer( DISP_TIMER_ALLLOCK_SET, 0);
}

// 전체 잠금 점멸 시작/정지
void StartDisplayLockAll(void)
{
    Disp.AllLock     = TRUE;
    SetDispTimer( DISP_TIMER_ALLLOCK, TIMER_2SEC);
}

void StopDisplayLockAll(void)
{
    Disp.AllLock     = FALSE;
    SetDispTimer( DISP_TIMER_ALLLOCK, 0);
}

// LOCK 아이콘 점멸 시작/정지
void StartDisplayLockIcon(void)
{
    Disp.IconLock     = TRUE;
    SetDispTimer( DISP_TIMER_ICONLOCK, TIMER_2SEC);
}

void StopDisplayLockIcon(void)
{
    Disp.IconLock     = FALSE;
    SetDispTimer( DISP_TIMER_ICONLOCK, 0);
}

// 저수위 점멸 시작/정지
void StartDisplayLowWater(void)
{
    Disp.LowWater      = TRUE;
    SetDispTimer( DISP_TIMER_LOW_WATER, TIMER_2SEC);
}

void StopDisplayLowWater(void)
{
    Disp.LowWater     = FALSE;
    SetDispTimer( DISP_TIMER_LOW_WATER, 0);
}

U8 GetSettingDisp(void)
{
    return Disp.Setting;
}

void SetSettingDisp(U8 mu8Conf)
{
    Disp.Setting = mu8Conf;
}

/* 온수 고도 설정 모드 */
U8 GetAltidueConfigMode(void)
{
    return Disp.AltiConfigMode;
}

void SetAltitudeConfigMode(U8 mu8Conf )
{
    Disp.AltiConfigMode = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.AltiConfigModeTimeOut = 100;  // 10sec..
    }
}

/* 미사용 절전 설정 모드 */
U8 GetSmartUnusedSaveConfigMode(void)
{
    return Disp.SmartUnusedSaveConfigMode;
}
void SetSmartUnusedSaveConfigMode(U8 mu8Conf )
{
    Disp.SmartUnusedSaveConfigMode = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.SmartUnusedSaveConfigModeTimeOut = 100;  // 10sec..
    }
}
void RefreshSmartUnusedSaveConfigModeCancelTime(void)
{
    Disp.SmartUnusedSaveConfigModeTimeOut = 100;	// 10sec..
}

/* cold weak 설정 모드 */
U8 GetColdWeakConfigMode(void)
{
    return Disp.ColdWeakConfigMode;
}
void SetColdWeakConfigMode(U8 mu8Conf )
{
    Disp.ColdWeakConfigMode = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.ColdWeakConfigModeTimeOut = 100;  // 10sec..
    }
}
void RefreshColdWeakConfigModeCancelTime(void)
{
    Disp.ColdWeakConfigModeTimeOut = 100;	// 10sec..
}

/* uv test mode */
U8 GetUvTestMode(void)
{
    return Disp.UvTestMode;
}
void SetUvTestMode(U8 mu8Conf)
{
    Disp.UvTestMode = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.UvTestModeTimeOut = 3000;  // 5min..
    }
}
void RefreshUvTestModeCancelTime(void)
{
    Disp.UvTestModeTimeOut = 3000;	// 5min..
}

/* 살균 시간 보정1 */
U8 GetDispAdjustHourConfig(void)
{
    return Disp.AdjustHourConfig;
}

void SetDispAdjustHourConfig(U8 mu8Conf )
{
    Disp.AdjustHourConfig = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.AdjustHourTimeOut = 50;  // 5sec..
    }
}

/* 살균 시간 보정2 */
U8 GetDispDrainWaterConfig(void)
{
    return Disp.DrainWaterConfig;
}

void SetDispDrainWaterConfig(U8 mu8Conf )
{
    Disp.DrainWaterConfig = mu8Conf;
    if ( mu8Conf == TRUE )
    {
        Disp.DrainWaterTimeOut = 50;  // 5sec..
    }
}

U16 IsExpiredConfigTime(void)
{
    if( Disp.ConfigTime != 0 )
    {
        return FALSE;   // 만료 안됨.
    }

    return TRUE;  // 만료됨.
}

/* 버전 표시 */
void SetVersionDisp(U8 mu8DispSec)
{
    Disp.Version = TRUE;
    
    SetDispTimer( DISP_TIMER_VERSION, mu8DispSec);
}

/* FOTA */
U8 GetFotaDisp(void)
{
    return Disp.Fota;
}

void SetFotaDisp(U8 mu8Conf )
{
    Disp.Fota = mu8Conf;
}

/* 메멘토 설정 */
U8 GetMementoDisp(void)
{
    return Disp.Memento;
}

void SetMementoDisp(U8 mu8Conf )
{
    Disp.Memento        = mu8Conf;
    Disp.MementoStep    = 0;
    Disp.MementoTimer   = 0;
    
    SetDispTimer( DISP_TIMER_MEMENTO, 0);
}

void ProcessDisplay(void)
{
    UpdateTimer();
    UpdateDisplayTimer();
    SetLedAllType();
    ApplyLedPortOutput();           // PROTOCOL TO PORT COVERSION
        
    /* BOOT */
    if( Disp.Init == FALSE )
    {
        ProcessDisplayBoot();
        return ;
    }
	
    /*
    if( GetTestFilterStatus() == TRUE )
    {
        BlinkLED( DispHotWater,     Disp.BlinkTime_1s, 5 );
        BlinkLED( DispColdWater,    Disp.BlinkTime_1s, 5 );

        DispLowWater( LED_OFF );
        DispPowerSaving( LED_OFF );
        return ;
    }
    */

#if CONFIG_TEST_CHECK_FRONT
    return ;
#endif
    /* DISPLAY VERSION */
    if( Disp.Version == TRUE )
    {
        ProcessDisplayVersionMode();
        return ;
    }

    // /* TEST - EOL */
    // if( GetEolStatus() == TRUE )
    // {
    //     Disp.Init = TRUE;
    //     ProcessDisplayEol();
    //     return ;
    // }

    // /* TEST - FCT */
    // if( GetFctStatus() == TRUE )
    // {
    //     Disp.Init = TRUE;
    //     return ;
    // }


    /* Fist Init Flushing or Filter Change Flushing */
    if( GetFlushingConfig() == TRUE )
    {
        ProcessDisplayFlushing();
        ProcessFlushingDisplayErrorMode();
        return;
    }
    
    // /* CONFIG - HOT WATER ALTITUDE */
    // if( GetAltidueConfigMode() == TRUE )
    // {
    //     ProcessDisplayConfHotAltitude();
    //     return ;
    // }

    /* CONFIG - SMART UNUSED SAVE */
    // if( GetSmartUnusedSaveConfigMode() == TRUE )
    // {
    //     ProcessDisplayConfUnusedSave();
    //     return ;
    // }

    // /* 강제 수동 배수 */
    // if(GetForceDrainAllTankStatus() == TRUE)
    // {
    //     ProcessDisplayForceDrain();
    //     return ;
    // }
    
    /* NORMAL MODE */
    ProcessDisplayNormalMode();
	
    /* ERRROR MODE */
    ProcessDisplayErrorMode();

    /* If front pba type and main pba type do not match */
    /*
    if(GetFrontSystem() != GetSystem())
    {
        TurnOffAllLED();
        return ;
    }
    */
}

/* 타이머 제어 함수  @100ms */
static void UpdateTimer(void)
{
    /* Update Blink Timer */
    if( Disp.BlinkTime_5s == 0 )
    {
        Disp.BlinkTime_5s = 6;
    }
    Disp.BlinkTime_5s--;

    if( Disp.BlinkTime_1s == 0 )
    {
        Disp.BlinkTime_1s = 11;
    }
    Disp.BlinkTime_1s--;

    if( Disp.BlinkTime_4s == 0 )
    {
        Disp.BlinkTime_4s = 41;
    }
    Disp.BlinkTime_4s--;
    
    if( Disp.ConfigTime != 0 )
    {
        Disp.ConfigTime--;
    }

}

/* 디스플레이 초기화 표시 */
static void ProcessDisplayBoot(void)
{
    static U8 mu8Count = 5;
    static U8 mu8Toggle = 0;

    if( Disp.BlinkTime_5s == 0 )
    {
        mu8Toggle = !mu8Toggle;

        mu8Count--;
        if( mu8Count == 0 )
        {
            mu8Count = 5;
            Disp.Init = TRUE;
            return;
        }
    }

    if( mu8Toggle == 0 )
    {
        TurnOffAllLED();
        TurnOffAllSeg();
    }
    else
    {
        TurnOnAllLED();
        TurnOnAllSeg();
    }
}

/* Flushing Progress Display */
static void ProcessDisplayFlushing(void)
{
    if( GetFlushingStatus() == FLUSHING_STATUS_WAIT )
    { 
        TurnOffAllSeg();
        TurnOffAllLED();
        DispWaterOutPointRight( LED_OFF );
    } 
    else if(GetFlushingStatus() == FLUSHING_STATUS_ING )
    {
        TurnOffAllSeg();
        TurnOffAllLED();
        // DispWaterOutPointRight( LED_ON );
        DispExtractDimmingBlink();
    }

    /* 플러싱 진행률 표시 */
    DispFlushingProgress();
}

static void DispFlushingProgress(void)
{
    U16 mu16Val = 0;
    
    // mu16Val = (U16)GetFlushingProgress();
        
    if( GetFlushingRun() == TRUE )
    {
        // DispPercent(mu16Val);
    }
}

static void DispExtractDimmingBlink(void)
{
    static U8 mu8BlinkOnOff = LED_ON; // static local variable => Used like global variable

    SetLedType(LED_WATER_OUT, LED_TYPE_DUTY_DIM);	// set dimming
    
    mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispWaterOutPointRight, DISP_TIMER_ID_500MS );
}

static void DisplaySelWater(void)
{
    U8 mu8Sel;
    U8 mu8HotSel;

    /* COLD, ROOM */
    mu8Sel = GetWaterOutSelect();
    DispWaterSel( mu8Sel ); 

    /* HOT */
    mu8HotSel = GetHotWaterOutSelect();
    DispHotWaterSel( mu8HotSel );     
}

static void DispSelAmount_WaterOut(void)
{
    U8 mu8Amount;
    U16 mu16Val = 0;

    mu8Amount = GetWaterOutAmountType();
    if( mu8Amount == AMOUNT_ID_INFINITY )
    {
        DispAmountInfinity();
        return;
    }
	
    mu16Val = GetWaterOutPercent();
    DispWaterOutProgress(mu16Val);
}

static void DispSelAmount_HotWaterOut(void)
{
    U8 mu8Amount;
    U16 mu16Val = 0;

    mu8Amount = GetHotWaterOutAmountType();
    if( mu8Amount == AMOUNT_ID_INFINITY )
    {
        DispAmountInfinity();
        return;
    }
	
    mu16Val = GetHotWaterOutPercent();
    DispHotWaterOutProgress(mu16Val);
}

/* 용량 선택한 상황에 디폴트물량 설정하면 bar는 디폴트 물량이 표시됨(실제 TargetAmount와 세그표시는 현재 선택한 물양 표시함) 
-> ex) Cursor = 0 으로 정량 1번째 bar 표시 중 디폴트 물양 셋팅해서 Cursor = 2 가 되버리면서 bar는 Cursor 2 에 해당하든 bar 표시 
       그러나 세그먼트와 실제 TargetAmount는 Cursor0 에 해당하는 물양 표시 함 이에 BackupCursor 활용 */
// 디폴트 물량 표시는 설정한 즉시 표시하지 않고 정량표시 취소 되고 레버타입 전환 되고 난 이후 시점부터 적용
static void DispSelAmount_Normal(void)
{
    U8 mu8AmountCusor;
    
    // 타이머가 만료되었으면 디스플레이를 끄고 함수 종료
    if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == TRUE )
    {
        DispAmountSelOff();
        return;
    }

    // 디폴트 물량 설정 상황인 경우, 백업 커서 사용
    if(GetSkipCursorIncrease() == TRUE)
    {
        mu8AmountCusor = GetAmountBackupCursor();
    }
    // 일반적인 상황인 경우, 일반 커서 사용
    else
    {
        mu8AmountCusor = GetAmountCursor();
    }

    // 선택된 물량 디스플레이 켜기
    DispAmountSel(mu8AmountCusor, LED_ON);
}

static void DisplaySelAmount(void)
{
    /* 오른쪽 정량 선택 */
    if( IsWaterAmountSelected() == TRUE )
    {
        /* 오른쪽 정량 추출 */
        if( GetWaterOut() == TRUE )
        {
            DispSelAmount_WaterOut();
            return;
        }
    }
    
    /* 왼쪽, 오른쪽 둘다 추출 안할 때 */
    DispSelAmount_Normal();
}

static void DisplayLockHotSet(void)
{
    static U8 mu8BlinkOnOff = LED_ON;

    /* 온수 잠금 설정 시, 점멸 */
    if( Disp.HotLockSet == TRUE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_HOTLOCK_SET ) == FALSE )
        {
            mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispLockHotSetBlink, DISP_TIMER_ID_500MS );
        }
        else
        {
            mu8BlinkOnOff = LED_ON;
            Disp.HotLockSet = FALSE;
        }
    }
}

/* Aging test -> blink hot lock */
static void DisplayHotLockBlink(void)
{
    static U8 mu8BlinkOnOff = LED_ON; // static local variable => global variable

    if( GetAgingTestRepeatStatus() == TRUE )
    {
        mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispHotLock, DISP_TIMER_ID_500MS );
    }
}

/* Aging test -> blink hot lock */
static void DisplayAgingTest(void)
{
    DisplayHotLockBlink();
}

static void DisplayHotMakeBlink(void)
{
    static U8 mu8BlinkOnOff = LED_ON; // static local variable => global variable

    /*  꺼짐 상태에서 선택 시, 점멸 */
    if( Disp.HotMake == TRUE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_HOTMAKE ) == FALSE )
        {
            mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispHotWater, DISP_TIMER_ID_500MS );
            return ;
        }

        mu8BlinkOnOff = LED_ON;
        Disp.HotMake = FALSE;
    }
}

static U32 TransNumAging(U32 mu32Val)
{
    mu32Val = (mu32Val / 10); 

    return mu32Val ;
}

enum
{
    DISP_VERSION_START,
    DISP_VERSION_VERSION,
    DISP_VERSION_END,
};
static void ProcessDisplayVersionMode(void)
{
    if( IsExpiredDispTimer( DISP_TIMER_VERSION ) == FALSE )
    {
        return ;
    }

    // 1. ALL OFF LED - 1 SEC
    // 2. DISPLAY VERSION - 1 SEC
    // 3. DISPLAY SYSTEM TYPE(CHP or CP) - 1 SEC
    // 1. ALL OFF LED
    switch( Disp.VersionStep )
    {
        case DISP_VERSION_START: 
            /* 1. TURN OFF ALL LED */
            TurnOffAllLED();	
            TurnOffAllSeg();	

            SetDispTimer( DISP_TIMER_VERSION, TIMER_1SEC );
            Disp.VersionStep++;
            break;

        case DISP_VERSION_VERSION:
            /* 2. VERSION */
            DispMainVersion( MAIN_VERSION ); 

            SetDispTimer( DISP_TIMER_VERSION, TIMER_1SEC );
            Disp.VersionStep++;
            break;

        case DISP_VERSION_END:
            TurnOffAllLED();	
            TurnOffAllSeg();	
            Disp.Version     = FALSE;
            Disp.VersionStep = 0;
            break;

        default:
            Disp.Version     = FALSE;
            Disp.VersionStep = 0;
            break;

    }
}

static void ProcessDisplayErrorMode(void)
{
    static ErrorId_T mu8PrevErr = 0;
    ErrorId_T mu8CurErr = 0;

    static U8 mu8Cmd = LED_OFF;
    static U8 mu8Counter = 10;

    /* Get error code */
    mu8CurErr = GetErrorId();

    /* Display error code */
    if( mu8CurErr == ERR_NONE )
    {
        mu8Cmd = LED_OFF;
        mu8Counter = 10;
    }
    else
    { 
     /* Blink related code */
        mu8Counter--;
        if( mu8Counter == 0 )
        {
            mu8Counter = 10;
        }

        if( mu8Counter <= 5 )
        {
            mu8Cmd = LED_OFF;
        }
        else
        {
            mu8Cmd = LED_ON;
        }
/* How to blink?? Up to mu8Counter 1~5 is mu8Cmd = 0 --> led off */
               /* Up to mu8Counter 6~10 is mu8Cmd = 1 --> led on */
        DisplayError( mu8CurErr, mu8Cmd );
    }

    /* Sound new error code */
    if( mu8PrevErr != mu8CurErr )
    {
        mu8PrevErr = mu8CurErr;
    }
}

static void ProcessFlushingDisplayErrorMode(void)
{
    static ErrorId_T mu8PrevErr = 0;
    ErrorId_T mu8CurErr = 0;

    static U8 mu8Cmd = LED_OFF;
    static U8 mu8Counter = 10;

    /* 플러싱 중에는 해당 에러 제외한 에러들은 표시 x */
    // if( IsErrorType(ERROR_TYPE_FLUSHING) == FALSE )
    // {
    //     if( GetFlushingStatus() == FLUSHING_STATUS_WAIT )  // WAIT(에러아닌상황)에서는 세그먼트 표시 x
    //     {
    //         TurnOffAllSeg();
    //         return;
    //     }
    //     else if( GetFlushingStatus() == FLUSHING_STATUS_ING )  // ING 일때는 해당 에러 제외한 에러들은 표시 x -> 진행률 표시하기위해 세그먼트 끄지 않고 return
    //     {
    //         return;
    //     }
    // }

    /* Get error code */
    mu8CurErr = GetErrorId();

    /* Display error code */
    if( mu8CurErr == ERR_NONE )
    {
        mu8Cmd = LED_OFF;
        mu8Counter = 10;///
    }
    else
    { 
     /* Blink related code */
        mu8Counter--;
        if( mu8Counter == 0 )
        {
            mu8Counter = 10;
        }

        if( mu8Counter <= 5 )
        {
            mu8Cmd = LED_OFF;
        }
        else
        {
            mu8Cmd = LED_ON;
        }
/* How to blink?? Up to mu8Counter 1~5 is mu8Cmd = 0 --> led off */
               /* Up to mu8Counter 6~10 is mu8Cmd = 1 --> led on */
        DisplayError( mu8CurErr, mu8Cmd );
    }

    /* Sound new error code */
    if( mu8PrevErr != mu8CurErr )
    {
        mu8PrevErr = mu8CurErr;
    }
}

/*
static void ProcessDisplaySavingMode(void)
{
    DispLedDuty();

    TurnOffAllLED();


    DispPowerSaving( GetSavingConfig() );

    
    DisplayWaterOut();
    DisplayIceOut();
}
*/

static void UpdateDispState(void)
{
    /* 우선순위 1 : WATER OUT progress */
    if(GetWaterOut() == TRUE || GetHotWaterOut() == TRUE)
    {
        SetDispSegState(DISP_STATE_WATER_OUT_PROGRESS);
        return;
    }

    SetDispSegState(DISP_STATE_NONE);  // 아무것도 표시 안할 때
}

static void ProcessDisplayNormalMode(void)
{
    TurnOffAllLED();

    /* 현재 화면 어떤 걸 표시 해야 하는지에 대한 상태 업데이트 */
    UpdateDispState();
    
    /* Water Level */
    DisplayWaterLevel();
   
    /* Select Water */
    DisplaySelWater();

    /* Amount */
    DisplaySelAmount();

    /* Hot Make 꺼짐 점멸 */
    DisplayHotMakeBlink();

    /* Lock Hot Water */
    DisplayLockHot();
	
    /* Filter Flushing */
    DisplayFilterFlushing();

    /* Replace Filter */
    DisplayReplaceFilter();

    /* Lock 점멸 */
    DisplayLock();  

}

static void DisplayWaterTempLevel(void)
{
    D64  HotTemp;

    HotTemp = Get_Temp( ADC_ID_TH_HOT_TANK_TEMP );       /* HOT WATER TEMP LEVEL and Display icon heating*/

    /* Heating */
    if(GetHotWaterConfigMake() == TRUE && Get_ErrorStatus(ERROR_ID_TANK_HOT_TEMP_E45) == FALSE )
    {
        DisplayHeating(HotTemp);
    }
    else
    {
        HAL_TurnOnOffLED( ICON_HEATING, LED_OFF );
    }
}

static void DisplayHeating( D64 mTemp )
{
    U8 mu8HotTempLevel = NONE_HEATING;
    static U8 mu8BlinkOnOff = LED_ON;
	
    mu8HotTempLevel = GetHotTempLevel();

    if( mu8HotTempLevel == HEATING )
    {
        if(GetHotWaterOutSelect() == SEL_WATER_HOT)
        {
            if( IsExpiredDispTimer( DISP_TIMER_HEATING_DIMMING_BLINK ) == FALSE )
            { 
                mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispHeatingBlinkDimming, DISP_TIMER_ID_500MS );
            }
            else
            {
                HAL_TurnOnOffLED( ICON_HEATING, LED_ON ); 
            }			
        }
        else
        {
            HAL_TurnOnOffLED( ICON_HEATING, LED_ON );
        }
    }
    else
    {
        HAL_TurnOnOffLED( ICON_HEATING, LED_OFF );
    }
}

static void DisplayLockHot(void)
{
    U8 mu8OnOff = LED_OFF;

    /* 온수 잠금 LED ON/OFF */
    if( Get_HotKeyLockStatus() == HOT_KEY_LOCK_ON  )
    {
        mu8OnOff = LED_ON;
    }
  
    DispHotLock( mu8OnOff );
}

static void DisplayFilterFlushing(void)
{

}

static void DisplayReplaceFilter(void)
{
    // if( IsExpiredFilterUsage() == TRUE )
    // {
    //     HAL_TurnOnOffLED( ICON_REPLACE_FILTER, LED_ON );
    // }
}

static void DisplayLock(void)
{
    U8 mu8OnOff = LED_OFF;
    static U8 mu8BlinkOnOffHotLock = LED_ON;
    static U8 mu8BlinkOnOffOnlyHotLock = LED_ON;
    static U8 mu8BlinkOnOffAllLock = LED_ON;

    /* hot lock 온수 잠금 상태에서 선택 시, 점멸 */
    if( IsExpiredDispTimer( DISP_TIMER_HOTLOCK ) == FALSE )
    {
        mu8BlinkOnOffHotLock = BlinkLED( mu8BlinkOnOffHotLock, DispHotLock, DISP_TIMER_ID_500MS );
    }
}

/*
static void DisplayLockAllSet(void)
{
    U8 mu8OnOff = LED_OFF;
    static U8 mu8BlinkOnOff = LED_ON;

    // 전체 잠금 설정 시, 점멸 
    if( Disp.AllLockSet == TRUE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_ALLLOCK_SET ) == FALSE )
        {
            mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispLock, DISP_TIMER_ID_500MS );
        }
        else
        {
            mu8BlinkOnOff = LED_ON;
            Disp.AllLockSet = FALSE;
        }
    }
}
*/

static void DisplayHotLowWater(void)
{
    static U8 mu8BlinkOnOff = LED_ON; // static local variable => global variable

    /* 저수위 중 온수 선택 후 좌측 레버시 2번 점멸 */
    if( IsExpiredDispTimer( DISP_TIMER_LOW_WATER ) == FALSE )
    {
        mu8BlinkOnOff = BlinkLED( mu8BlinkOnOff, DispLowWater, DISP_TIMER_ID_500MS );
        return ;
    }

    if( Get_HotWaterLevel() == HOT_WATER_LEVEL_LOW )
    {
        DispLowWater( LED_ON );
    }
    else
    {
        DispLowWater( LED_OFF );
    }
}

static void DisplayWaterLevel(void)
{
    // if(GetWaterOutSelect() == SEL_WATER_ROOM)
    // {
    //     DisplayRoomLowWater();
    // }

    // if( GetHotWaterOutSelect() == SEL_WATER_HOT)
    // {
        DisplayHotLowWater();
    // }
}

static U16 GetWaterOutPercent(void)
{
    /*
    if( GetRoomOut() == TRUE )  
    {
        return (U16)CalcPercent( GetRoomOutTargetAmount(), GetRoomOutCurrentAmount() ); // room water out by flow sensor (Not Tank)
    }*/
    
    return (U16)CalcPercent( GetWaterOutFixedAmountTargetTime(), GetWaterOutFixedAmountCurrentTime() ); // water out by tank
}

static U16 GetHotWaterOutPercent(void)
{    
    return (U16)CalcPercent( GetHotWaterOutFixedAmountTargetTime(), GetHotWaterOutFixedAmountCurrentTime() ); // water out by tank
}

/* 추출 진행 상황 퍼센트로 표시
static void DisplayWaterOutPercent(void)
{
    if( GetWaterOut() == TRUE )
    {
        U16 mu16Percent;
        U16 mu16Val;

        mu16Percent = GetWaterOutPercent();  
        mu16Val = (mu16Percent / 10U) * 10U; 

        DispPercent( mu16Val );
    }
}
*/

static void Disp7SegWaterAmount(void)
{
    U8  i;
    U8  mu8AmountId;
    U16 mu16AmountDisp;	

    mu8AmountId = GetWaterOutAmountType();
    
    for( i = 0; i < AMOUNT_ID_MAX; i++ )
    {
        if( mu8AmountId == GetAmountDataId(i) )
        {
            mu16AmountDisp = GetAmount(mu8AmountId);
        }
    }

    if( mu8AmountId == AMOUNT_ID_INFINITY )
    {
        mu16AmountDisp = DISPLAY_CIRCLE ;
    }
    
    Disp7SegAmount( mu16AmountDisp ); 
}

static void Disp7SegHotWaterAmount(void)
{
    U8  i;
    U8  mu8AmountId;
    U16 mu16AmountDisp;	

    mu8AmountId = GetHotWaterOutAmountType();
	
    for( i = 0; i < AMOUNT_ID_MAX; i++ )
    {
        if( mu8AmountId == GetAmountDataId(i) )
        {
            mu16AmountDisp = GetAmount(mu8AmountId);
        }
    }
    
    if( mu8AmountId == AMOUNT_ID_INFINITY )
    {
        mu16AmountDisp = DISPLAY_CIRCLE ;
    }
    
    Disp7SegAmount( mu16AmountDisp ); 
}

/* 우측 정량 추출 */
static void Disp7SegAmountWaterOut(void)
{
    U8 mu8Amount;	
	
    StartDispTimerId( DISP_TIMER_KEY_AMOUNT ); // Water out ing? YES -> continue refresh

    mu8Amount  = GetWaterOutAmountType();
    if( mu8Amount == AMOUNT_ID_INFINITY )
    {
        DispInfinityOutAmount();
    }
    else
    {
        Disp7SegWaterAmount();
    }
}

/* 좌측 정량 추출 */
static void Disp7SegAmountHotWaterOut(void)
{
    U8 mu8Amount;	
	
    StartDispTimerId( DISP_TIMER_KEY_AMOUNT ); // Water out ing? YES -> continue refresh

    mu8Amount  = GetHotWaterOutAmountType();
    if( mu8Amount == AMOUNT_ID_INFINITY )
    {
        DispInfinityOutAmount();
    }
    else
    {
        Disp7SegHotWaterAmount();
    }
}

static void Disp7SegLeverWaterOut(void)
{
    /* 오른쪽 추출부 레버로(정량x) 추출 중, 좌측(온수) 정량 선택 하면 정량 표시 O, 레버추출 표시x (정량 표시가 우선) */
    if( IsHotWaterAmountSelected() == TRUE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == FALSE)
        {
            Disp7SegHotWaterAmount();
            return;
        }
    }

    DispLeverWaterOut();
}

static void Disp7SegLeverHotWaterOut(void)
{
    /* 왼쪽 추출부 레버로(정량x) 추출 중, 우측(정수or냉수) 정량 선택 하면 정량 표시 O, 레버추출 표시x (정량 표시가 우선) */
   if( IsWaterAmountSelected() == TRUE )
   {
       if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == FALSE)
        {
            Disp7SegWaterAmount();
            return;
        }
    }
    
    DispLeverHotWaterOut();
}

static void Disp7SegWaterNormal(void)
{
    if( GetWaterOutPressContinue() == FALSE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == FALSE )
        {
            Disp7SegWaterAmount();
        }
    }
}

static void Disp7SegHotWaterNormal(void)
{
    if( GetHotWaterOutPressContinue() == FALSE )
    {
        if( IsExpiredDispTimer( DISP_TIMER_KEY_AMOUNT ) == FALSE )
        {
            Disp7SegHotWaterAmount();
        }
    }
}

static void Disp7SegNormal(void)
{
    U8 mu8DispState = 0;

    ResetInfinityCount();   
    ResetWaterLeverCount();
    ResetHotWaterLeverCount();

    /* SEG OFF 표시 해야 할 상황 일 때 */
    if( IsExpiredDispTimer( DISP_TIMER_SEGOFF ) == FALSE )
    {
        DispSegOff();
        return;
    }

    /* SEG ON 표시 해야 할 상황 일 때 */
    if( IsExpiredDispTimer( DISP_TIMER_SEGON ) == FALSE )
    {
        DispSegOn();
        return;
    }

    mu8DispState = GetDispSegState();
    switch (mu8DispState)
    {
        /* 아무 표시 x */
        case DISP_STATE_NONE:
            TurnOffAllSeg();
            break;

        default:
            break;
    }
}


