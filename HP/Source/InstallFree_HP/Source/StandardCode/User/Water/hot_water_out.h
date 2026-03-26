#ifndef __HOT_WATER_OUT_H__
#define __HOT_WATER_OUT_H__

void  InitHotWaterOut(void);

void SetHotReturnTime(U16 mu16Val);
void ResetHotReturnTime(void);
void ResetHotReturnTimeAmount(void);
void ResetHotReturnTimePressContinue(void);
/* using now amount */
void  SetHotWaterOutFixedAmountType(U8 mu8Type );
U8 GetHotWaterOutFixedAmountType(void);

void  SetHotWaterOutFixedAmountTargetTime(U32 mu32Time);
U32   GetHotWaterOutFixedAmountTargetTime(void);

void  SetHotWaterOutFixedAmountCurrentTime(U32 mu32Time);
U32   GetHotWaterOutFixedAmountCurrentTime(void);

U8 GetHotWaterOutAmountType(void);

U8 GetHotWaterOutFixedAmountType(void);

void  SetHotWaterOutSelect(U8 mu8Id );
U8 GetHotWaterOutSelect(void);

U8 GetHotWaterOutPressContinue(void);
void SetHotWaterOutPressContinue(U8 mu8Mode );

void  StartHotWaterOut(void);
void  StopHotWaterOut(void);

U8 GetHotWaterOut(void);

U8 IsExpiredHotOutProtectTime(void);

U8 IsHotWaterAmountSelected(void);

void  ControlHotWaterOut(void);

#endif /* __HOT_WATER_OUT_H__ */