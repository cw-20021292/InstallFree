#ifndef __DISPLAY_H__
#define __DISPLAY_H__


#include "hal_led_protocol.h"

#define DISPLAY_CIRCLE     9999

/* Number 0 ~ 9 */
/* static ��� ���� static �Ⱦ��� �ٸ� ������� display.h ���� ��Ŭ����Ҷ����� ������ �Ǳ⶧��
   �� display.c ���� �ȿ����� ��� �Ҷ� static �ٸ����Ͽ����� ����ϰ� ������ extern �ؾ��� */
static U8 gu8Digit[10] = 
{
    PROTOCOL_SEG_LED_DATA_0,
    PROTOCOL_SEG_LED_DATA_1,
    PROTOCOL_SEG_LED_DATA_2,
    PROTOCOL_SEG_LED_DATA_3,
    PROTOCOL_SEG_LED_DATA_4,
    PROTOCOL_SEG_LED_DATA_5,
    PROTOCOL_SEG_LED_DATA_6,
    PROTOCOL_SEG_LED_DATA_7,
    PROTOCOL_SEG_LED_DATA_8,
    PROTOCOL_SEG_LED_DATA_9
};


/* Functinos */
void TurnOffAllLED(void);
void TurnOnAllLED(void);
void TurnOffAllSeg(void);
void TurnOnAllSeg(void);

void SetLedAllType(void);

void DispSegmentHour(U16 mu16Val);
void DispSegmentMin(U16 mu16Val);

void DispSegmentDigit(U16 mu16Val);
void DispSegOff(void);
void DispSegOn(void);

void DispPowerSaving( U8 mu8OnOff );
void DispFullWater( U8 mu8OnOff );
void DispMidWater( U8 mu8OnOff );
void DispLowWater( U8 mu8OnOff );
void DispHotWater( U8 mu8OnOff );
void DispRoomWater( U8 mu8OnOff );
void DispIconML( U8 mu8OnOff );
void DispIcon1( U8 mu8OnOff );
void DispIcon2( U8 mu8OnOff );
void DispIcon3( U8 mu8OnOff );
void DispDaysLeft( U8 mu8OnOff );
void DispIconAm( U8 mu8OnOff );
void DispIconPm( U8 mu8OnOff );
void DispReplaceFilter( U8 mu8OnOff );

void DispWaterSel(U8 mu8Sel);
void DispHotWaterSel(U8 mu8HotSel);
void DispWaterHot(U8 mu8Sel);

void DispHotConfig(U8 mu8OnOff);
void DispOnlyHotLock(U8 mu8OnOff);
void DispLockHotSetBlink( U8 mu8OnOff );

void DispAmountSel(U8 mu8AmountCusor, U8 mu8Dimming);
void DispAmountSelOff(void);
void DispAmountSelOffAll(void);
void DispRightBar1(U8 mu8OnOff);
void DispRightBar2(U8 mu8OnOff);
void DispRightBar4( U8 mu8OnOff );
void DispInfinity( U8 mu8OnOff );
void DispAmountInfinity(void);
void DispWifi( U8 mu8OnOff );

void DispWaterOutPointLeft( U8 mu8OnOff );
void DispWaterOutPointRight( U8 mu8OnOff );

void DispLockAllOnOff_CHP( U8 mu8OnOff );
void DispLockAllBlink( U8 mu8OnOff );
void DispLock( U8 mu8OnOff );
void DispAllLock(U8 mu8OnOff);
void TurnOffLED_LockAllMode(void);

void DispEolAmbientTempErr( U8 mu8OnOff );
void DispEolHotTempErr( U8 mu8OnOff );
void DispEolColdTempErr( U8 mu8OnOff );
void DispEolNeoFilter( U8 mu8OnOff );
void DispEolRoFilter( U8 mu8OnOff );
void DispEolInnoAndReplaceFilter( U8 mu8OnOff );
void DispEolCitricAcidFilter( U8 mu8OnOff );
void DispEolTankCover( U8 mu8OnOff );
void DispEolLevelElectrodeHotHigh( U8 mu8OnOff );

void DispUvCare(U8 mu8OnOff, U8 mu8ColdTank);
void DispSaving(U8 mu8OnOff);

void DispMainVersion(U8 mu8Val);
void DispFrontVersion(void);
U8   DispVersionOnTime(void);

void DispDevelopMassproduct(U8 mu8OnOff);
void DispProductInfromation(U8 mu8OnOff);
void DispSegmentOff(void);
void DispWaterOutProgress(U16 mu16WaterOutProgress );
void Disp7SegAmount(U16 mu16Val);
void DispInfinityOutAmount(void);
void DispLeverWaterOut(void);
void DispLeverHotWaterOut(void);

void DispHotWaterOutProgress(U16 mu16WaterOutProgress );

void DispPercent(U16 mu16Val);

void DispHeatingBlinkDimming( U8 mu8OnOff );
void DispCoolingBlinkDimming( U8 mu8OnOff );
void DispUvCareBlinkDimming( U8 mu8OnOff );

void DispAmount(void);

void CHP_DispVirtualLedAllOnOff(U8 mu8OnOff);

void ResetInfinityCount(void);
void ResetWaterLeverCount(void);
void ResetHotWaterLeverCount(void);

void ApplyLedPortOutput(void);


#endif /* __DISPLAY_H__ */
