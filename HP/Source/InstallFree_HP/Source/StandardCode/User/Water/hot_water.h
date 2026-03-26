#ifndef __HOT_WATER_H__
#define __HOT_WATER_H__

/* ALTITUDE */
#define  ALTITUDE_LEVEL_0    0
#define  ALTITUDE_LEVEL_1    1
#define  ALTITUDE_LEVEL_2    2
#define  ALTITUDE_LEVEL_3    3
#define  ALTITUDE_LEVEL_NUM  4

/* UNUSED SAVING */
#define  UNUSED_SAVING_ON_10HOUR    36000U // @1sec 
#define  UNUSED_SAVING_ON_6HOUR     21600U // @1sec
#define  UNUSED_SAVING_ON_9HOUR     32400U // @1sec

/* TARGET OFF TEMP - PROTECTION OVER-HEATING */
#define PROTECT_HOT_TEMP   100.0f
  
#define NONE_HEATING    0      
#define HEATING         1   

typedef enum _hot_temp_level_
{
    HOT_TEMP_LEVEL_NONE = 0,
    HOT_TEMP_LEVEL_WEAK,  
    HOT_TEMP_LEVEL_STRONG,  
} HotTempLevel_T;

typedef struct _hot_water_
{
    U8 InitWaitTime;    
    U8 InitFull;     
    U8 Level;            // hot tank level        
    U8 Select;  
    U8 ConfigMake;      
    U8 TempLevel;        // for display "heating"

    U8  Make;      
    U16 MakeDelay;

    /* Target Temperetrue as mode */
    U8 Altitude;    // Altitude4 = ���Ƹ��(HotWeakMode)
        
    /* TEMP */
    D64  TempTargetOn;    
    D64  TempTargetOff;      
    D64  TempCurrent;    
    D64  PipeTempCurrent;     

} HotWater_T;


void InitHotWater(void);

void GetHotWaterData( HotWater_T *pData );

U8 GetHotTempLevel(void);

void SetHotWaterInitFull(U8 mu8Val);
U8   GetHotWaterInitFull(void);

void SetHotWaterUnusedOnTime(U16 mu16OnTime);
U16  GetHotWaterUnusedOnTime(void);

void SetHotWaterLevel(U8 mu8Val);
U8   GetHotWaterLevel(void);

void SetHotWaterConfigMake(U8 mu8Val);
U8   GetHotWaterConfigMake(void);

void SetHotWaterMake(U8 mu8Val);
U8   GetHotWaterMake(void);

void SetHotWaterAltidue(U8 mu8Val);
U8   GetHotWaterAltidue(void);

void SetHotSelect(U8 mu8Sel);
U8   GetHotSelect(void);

U8   SetDisplayHotTempRed(U8 mu8Val);
U8   GetDisplayHotTempRed(void);

U8   GetHotTempLevel(void);

void UpdateHotMakeDelay(void);
void UpdateHotAirFlowTime(void);

void MakeHotWater(void);

U8 GetHotRangeMixing(void);

U16 GetHotSelectTemp(U8 mu8Sel);

D64   GetHotTargetOnTemp(U8 mu8Altitude);
D64   GetHotTargetOffTemp(U8 mu8Altitude);

void ProcessMakeHotWater(void);
void ControlHeater(U8 mu8OnOff);

#endif /* __HOT_WATER_H__ */
