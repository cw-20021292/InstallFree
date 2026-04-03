#include "Global_Header.h"

#include "water_out.h"
#include "flushing.h"
#include "hot_water.h"
#include "heater.h"

#define WAIT_TIME   5 //  5sec,  @1sec
#define WAIT_HEATING_TIME    60 // 1min,  @1sec

#define HOT_TEMP_RED   3

/* TEMP STATUS */
#define OVER_TEMP       0       
#define UNDER_TEMP      1
#define DEFAULT_TEMP_TIME   5   // @1sec, 5sec

/* TARGET TEMP - NORMAL */
// static const D64 OnTempList[ ALTITUDE_LEVEL_NUM ]  = { 68.0f, 68.0f, 68.0f, 68.0f };
// static const D64 OffTempList[ ALTITUDE_LEVEL_NUM ] = { 74.0f, 74.0f, 74.0f, 74.0f }; 

static const D64 OnTempList[ ALTITUDE_LEVEL_NUM ]  = { 75.0f, 68.0f, 68.0f, 68.0f };
static const D64 OffTempList[ ALTITUDE_LEVEL_NUM ] = { 85.0f, 74.0f, 74.0f, 74.0f }; 

static const D64 BoostOnTempList[ ALTITUDE_LEVEL_NUM ]  = { 75.0f, 73.0f, 73.0f, 73.0f };
static const D64 BoostOffTempList[ ALTITUDE_LEVEL_NUM ] = { 90.0f, 79.0f, 79.0f, 79.0f }; 


/* TARGET TEMP - Power Saving */
static const D64 OnTempPowerSavingList[ ALTITUDE_LEVEL_NUM ]  = { 75.0f, 75.0f, 75.0f, 75.0f };
static const D64 OffTempPowerSavingList[ ALTITUDE_LEVEL_NUM ] = { 94.0f, 91.0f, 88.0f, 85.0f };

/* TARGET TEMP - Unsued Power Saving */
static const D64 OnTempUnsuedSavingList[ ALTITUDE_LEVEL_NUM ]  = { 60.0f, 60.0f, 60.0f, 60.0f };
static const D64 OffTempUnusedSavingList[ ALTITUDE_LEVEL_NUM ] = { 85.0f, 82.0f, 79.0f, 76.0f };

HotWater_T Hot;

void  InitHotWater(void)
{
    Hot.InitWaitTime    = WAIT_TIME;           
    Hot.InitFull        = FALSE;
    Hot.Level           = HOT_WATER_LEVEL_LOW;
    Hot.ConfigMake      = FALSE;
    Hot.Make            = FALSE;
    Hot.MakeDelay       = WAIT_HEATING_TIME;
    Hot.Altitude        = ALTITUDE_LEVEL_0;
    Hot.TempLevel       = NONE_HEATING;          // for display "heating"   
}

void  GetHotWaterData( HotWater_T *pData )
{
    memcpy( pData, &Hot, sizeof( HotWater_T ));
}

void  SetHotWaterInitFull(U8 mu8Val)
{
    Hot.InitFull = mu8Val;
}

U8    GetHotWaterInitFull(void)
{
    return Hot.InitFull;
}

void  SetHotWaterLevel(U8 mu8Val )
{
    Hot.Level = mu8Val;
}

U8 GetHotWaterLevel(void)
{
    return Hot.Level;
}

void  SetHotWaterConfigMake(U8 mu8Val )
{
    if( mu8Val != TRUE && mu8Val != FALSE )
    {
        return ;
    }
    Hot.ConfigMake = mu8Val;

    // SaveEepromId( EEPROM_ID_CONF_MAKE_HOT );
}

U8    GetHotWaterConfigMake(void)
{
    return Hot.ConfigMake;
}

void  SetHotWaterMake(U8 mu8Val )
{
    Hot.Make = mu8Val;
}

U8    GetHotWaterMake(void)
{
    return Hot.Make;
}

void  SetHotWaterBoostMode(U8 mu8Val)
{
    Hot.Boost = mu8Val;
}

U8  GetHotWaterBoostMode(void)
{
    return Hot.Boost;
}

void  SetHotWaterAltidue(U8 mu8Val )
{
    if( mu8Val < ALTITUDE_LEVEL_NUM )
    {
        Hot.Altitude = mu8Val;
    }
}

U8 GetHotWaterAltidue(void)
{
    return Hot.Altitude;
}

void UpdateHotMakeDelay(void)
{
    Hot.MakeDelay = 0U;
}

static U8 IsValidMake(void)
{
    U8 mu8Level;

    if( Hot.InitWaitTime != 0 )
    {
        return FALSE;
    }

    /* Turn Off make, dont want to make */
    if( Hot.ConfigMake == FALSE )
    {
        return FALSE ;
    }

    /* 온수탱크가 만수위 아닐 때 */
#if 1
    if( Get_HotWaterLevel() == HOT_WATER_LEVEL_LOW )
    {
        return FALSE;
    }
#endif

    /* Turn Off make, error */
    if( Get_ErrorStatus(ERROR_ID_TANK_HOT_TEMP_E45) == TRUE )
    {
        return FALSE;
    }

    /* 추출중이면 히터 OFF */
    if(GetWaterOut() == TRUE)
    {
        return FALSE;
    }
	
#if 0
    /* LEAK ? YES -> Stop */
    if( GetLeakStatus() == TRUE )
    {
        return FALSE;
    }
#endif
    /* FLUSHING? YES -> Stop */
    if( GetFlushingConfig() == TRUE )
    {
        return FALSE;
    }

    /* Overheating */
    if( Get_Temp(ADC_ID_TH_HOT_TANK_TEMP) >= PROTECT_HOT_TEMP )
    {
        return FALSE;  
    }

    return TRUE;  // Yes, valid
}

D64   GetHotTargetOnTemp(U8 mu8Altitude)
{
    if( mu8Altitude >= ALTITUDE_LEVEL_NUM )
    {
        mu8Altitude = 0;
    }
	
    // if( GetSmartUnusedSavingStatus() == TRUE )
    // {		
    //     return OnTempUnsuedSavingList[ mu8Altitude ];
    // }
    
    if(GetHotWaterBoostMode() == TRUE)
    {
        return BoostOnTempList[ mu8Altitude ];
    }
    else
    {
        return OnTempList[ mu8Altitude ];
    }
}

D64   GetHotTargetOffTemp(U8 mu8Altitude)
{
    if( mu8Altitude >= ALTITUDE_LEVEL_NUM )
    {
        mu8Altitude = 0;
    }
        
    // if( GetSmartUnusedSavingStatus() == TRUE )
    // {	
    //     return OffTempUnusedSavingList[ mu8Altitude ];
    // }
    
    if(GetHotWaterBoostMode() == TRUE)
    {
        return BoostOffTempList[ mu8Altitude ];
    }
    else
    {
        return OffTempList[ mu8Altitude ];
    }
}


/* After the low water level detection is released, the delay time is counted and the heater is turned on*/
static U8 CheckLevelOnHeating(void)
{
    static U8 mu8PrevStatus = HOT_WATER_LEVEL_LOW;
    U8 mu8CurStatus;


    // Check condi, detect low level
    /* 수위가 저수위에서 중수위 이상으로 올라왔을 때 히팅 대기 */
    mu8CurStatus = Get_HotWaterLevel();
    if( mu8PrevStatus != mu8CurStatus )
    {
        if( mu8PrevStatus == HOT_WATER_LEVEL_LOW 
        && mu8CurStatus != HOT_WATER_LEVEL_LOW )
        {
            Hot.MakeDelay = WAIT_HEATING_TIME;
        }
        mu8PrevStatus = mu8CurStatus;
    }
    
    // Counting delay..
    if( Hot.MakeDelay != 0 )
    {
        Hot.MakeDelay--;
        Hot.Make = FALSE;

        return FALSE;   // Wait Heating..
    }

    return TRUE;    // Ok heating..
}

static void UpdateTime(void)
{
    /* FLUSHING? YES -> Stop */
    if( GetFlushingConfig() == TRUE )
    {
        return;
    }

    if( Hot.InitWaitTime != 0 )
    {
        Hot.InitWaitTime--;
    }
}

U8 GetHotTempLevel(void)
{
    return Hot.TempLevel;
}

/* for display Heating, Warming */
static void SetHotTempLevel(D64 HotTemp)
{
#if 0
    if(GetHotWaterOut() == TRUE)
    {
        return;
    }
	
    if( Hot.TempLevel == NONE_HEATING )
    {
        if( HotTemp <= Hot.TempTargetOn ) 
        {
            Hot.TempLevel = HEATING;
        }
    }
    else
    {
        if( HotTemp >= Hot.TempTargetOff ) 
        {
            Hot.TempLevel = NONE_HEATING;
        }
    }
#endif
}

void  MakeHotWater(void)
{
    UpdateTime();

    // Get Target On , Target Off, Current Temp 
    Hot.TempTargetOn  = GetHotTargetOnTemp( Hot.Altitude );
    Hot.TempTargetOff = GetHotTargetOffTemp( Hot.Altitude );
    Hot.TempCurrent   = Get_Temp( ADC_ID_TH_HOT_TANK_TEMP );
    // SetHotTempLevel(Hot.TempCurrent);      // for display "Heating"

    // return;
	
    /* Heater on delay, in the case of low water level is released */
    if( CheckLevelOnHeating() == FALSE )
    {
        Hot.Make = FALSE;
        return ;
    }

    if( IsValidMake() == FALSE )
    {
        Hot.Make = FALSE;
        return ;
    }

    // Check Turn Off 
    if( Hot.Make == TRUE )
    {
        if( Hot.TempTargetOff <= Hot.TempCurrent )
        {
            Hot.Make = FALSE;
        }
    }
    // Check Turn On 
    else
    {
        if( Hot.TempTargetOn >= Hot.TempCurrent )
        {
            Hot.Make = TRUE;
        }
    }

    /* Protection, OVER-HEAINTG */
    /* 온수탱크온도 상한치 제한 */
    if( Hot.TempCurrent >= PROTECT_HOT_TEMP )
    {
        Hot.Make = FALSE;
    }
}

/* hot water generation control */
void ProcessMakeHotWater(void)
{
    U8 mu8OnOff = OFF;

    /* MAKE ON/OFF */
    if( GetHotWaterMake() == TRUE )
    {
        mu8OnOff = ON;
    }
    ControlHeater( mu8OnOff );
}
