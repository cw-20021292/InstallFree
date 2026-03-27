#ifndef __PROCESS_DISPLAY_H__
#define __PROCESS_DISPLAY_H__



typedef enum _disp_seg_state_
{
    DISP_STATE_NONE = 0,           // 0 : None
    DISP_STATE_CLOCK,              // 1 : 
    DISP_STATE_WIFI_PARING,        // 2 :
    DISP_STATE_BLE_PARING,         // 3 : 
    DISP_STATE_UV_PROGRESS,        // 4 : 
    DISP_STATE_FILTER_DAYSLEFT,    // 5 : 
    DISP_STATE_AMOUNT,             // 6 : 
    DISP_STATE_WATER_OUT_PROGRESS, // 7 : 
} DispSegState_T;


void InitDisplay(void);

U8 GetDisplayInit(void);
void StartDisplayInit(void);

// Display Timer start/stop
void StartDispTimerId(U8 id);
void StopDispTimerId(U8 id);

void StartDisplayHotLockSet(void);
void StopDisplayHotLockSet(void);

void StartDisplayHotLock(void);
void StopDisplayHotLock(void);
	
void StartDisplayWaterOutPointLeft(void);
void StopDisplayWaterOutPointLeft(void);

void StartDisplayWaterOutPointRight(void);
void StopDisplayWaterOutPointRight(void);

void StartDisplayLockAllSet(void);
void StopDisplayLockAllSet(void);

void StartDisplayLockAll(void);
void StopDisplayLockAll(void);

void StartDisplayLockIcon(void);
void StopDisplayLockIcon(void);

void StartDisplaySegOff(void);
void StopDisplaySegOff(void);

void StartDisplaySegOn(void);
void StopDisplaySegOn(void);

void StartDisplayHotMake(void);
void StopDisplayHotMake(void);

void StartDisplayColdMake(void);
void StopDisplayColdMake(void);

void StartDisplayMyCup(void);
void StopDisplayMyCup(void);

void StartDisplayLowWater(void);
void StopDisplayLowWater(void);

void StartDisplayHotWater(void);
void StopDisplayHotWater(void);

void StartDisplayColdWater(void);
void StopDisplayColdWater(void);

void StartDisplayRoomWater(void);
void StopDisplayRoomWater(void);

U16 IsExpiredConfigTime(void);

U8 GetAltidueConfigMode(void);
void SetAltitudeConfigMode(U8 mu8Conf);

U8 GetSmartUnusedSaveConfigMode(void);
void SetSmartUnusedSaveConfigMode(U8 mu8Conf);
void RefreshSmartUnusedSaveConfigModeCancelTime(voide);

U8 GetColdWeakConfigMode(void);
void SetColdWeakConfigMode(U8 mu8Conf);
void RefreshColdWeakConfigModeCancelTime(void);

U8 GetUvTestMode(void);
void SetUvTestMode(U8 mu8Conf);
void RefreshUvTestModeCancelTime(voide);

U8 GetDispAdjustHourConfig(void);
void SetDispAdjustHourConfig(U8 mu8Conf );

U8 GetDispDrainWaterConfig(void);
void SetDispDrainWaterConfig(U8 mu8Conf );

void SetVersionDisp(U8 mu8DispSec);

U8 GetMementoDisp(void);
void SetMementoDisp(U8 mu8Conf );

void ProcessDisplay(void);

U8 GetDispDrainWaterConfig(void);
void SetDispDrainWaterConfig(U8 mu8Conf );

U8 GetSettingDisp(void);
void SetSettingDisp(U8 mu8Conf);

U8 GetFotaDisp(void);
void SetFotaDisp(U8 mu8Conf);

U8 GetDispSegState(void);
void SetDispSegState(U8 mu8Val);

void UpdateDispBlePairingTimer(void);

#endif /* __PROCESS_DISPLAY_H__ */
