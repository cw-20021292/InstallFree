#ifndef __WATER_OUT_H__
#define __WATER_OUT_H__

typedef enum _temp_level_
{
    TEMP_LEVEL_NONE = 0,
    TEMP_LEVEL_WEAK,  
    TEMP_LEVEL_STRONG,  
} ETempLevel_T;

void  InitWaterOut(void);

void  SetWaterOutSelect(U8 mu8Id );
U8    GetWaterOutSelect(void);
U8    GetWaterOutLastedSelect(void);

U8 SetSelectWater( U8 mu8Id );
void  SetWaterOutSelect(U8 mu8Id );

void SetLatestFixedAmount(U8 mu8Val);

void  StartWaterOut(void);
void  StopWaterOut(void);

U8 GetWaterOut(void);

U8 IsExpiredOutProtectTime(void);

/* using now amount */
void SetWaterOutFixedAmountType(U8 mu8Type );
U8   GetWaterOutFixedAmountType(void);
U8 GetWaterOutHotFixedAmountType(void);

void SetWaterOutFixedAmountTypeRightLever(U8 mu8Type);
void SetWaterOutFixedAmountTypeLeftLever(U8 mu8Type);


/* Functions for default amount */
void SetWaterOutConfFixedAmountType(U8 mu8Type);
U8   GetWaterOutConfFixedAmountType(void);

// void SetWaterOutFixedAmountDefaultType(EAmountId_T xEid);

U8    GetWaterOutAmountType(void);
U8    GetWaterOutHotAmoutType(void);

void  ClearWaterOutInfinityAmout(void);

void  SetWaterOutFixedAmountTargetTime(U32 mu32Time );
U32   GetWaterOutFixedAmountTargetTime(void);

void  SetWaterOutFixedAmountCurrentTime(U32 mu32Time );
U32   GetWaterOutFixedAmountCurrentTime(void);

/* Riht Water Out LEVER */
void SetWaterOutPressContinue(U8 mu8Mode);
U8   GetWaterOutPressContinue(void);

void SetLatestFixedAmount(U8 mu8Type);

void SetWaterOutInfinityLongKey(void);
void ClearWaterOutInfinityLongKey(void);

void  SetWaterOutLastedTime(U8 mu8Id, U32 mu32Time );
U32   GetWaterOutLastedTime(U8 mu8Id );

void  SetWaterOutDailyTime(U8 mu8Id, U32 mu32Time );
U32   GetWaterOutDailyTime(U8 mu8Id );

void  SetWaterOutTotalTime(U8 mu8Id, U32 mu32Time );
U32   GetWaterOutTotalTime(U8 mu8Id );

void SetWaterOutTime(U8 mu8Type, U8 mu8Id, U32 mu32Time );
U32  GetWaterOutTime(U8 mu8Type, U8 mu8Id );
void ResetWaterOutTime(U8 mu8Type, U8 mu8Id );

void ResetReturnTimePressContinue(void);
void ResetReturnTimeAmount(void);
void ResetReturnTime(void);

U16 GetReturnTimePressContinue(void);

void SetReturnTimeAmount(U16 mu16Time );
void SetReturnTime(U16 mu16Time );

U8 GetWaterOutLastedCupNum(U8 mu8Id);    
U8 GetWaterOutDailyCupNum(U8 mu8Id);    
U8 GetWaterOutTotalCupNum(U8 mu8Id);    

U8 IsWaterAmountSelected(void);

void  ControlWaterOut(void);

/* Aging Test */
void SetAgingTestRepeatStatus(U8 mu8Val );
U8 GetAgingTestRepeatStatus(void);
void SetDispAgingConfig(U8 mu8Val);
U8 GetDispAgingConfig(void);

U8 IsValidMakeAmountSelect(void);

/* Reliability Test */
void SetTestColdRepeatStatus(U8 mu8Val);
U8 GetTestColdRepeatStatus(void);
void SetTestHotRepeatStatus(U8 mu8Val);
U8 GetTestHotRepeatStatus(void);
void SetTestAllRepeatStatus(U8 mu8Val);
U8 GetTestAllRepeatStatus(void);

void SetWaterOutAccumulateAmount(U32 xUamount);
void ClearWaterOutAccumulateAmount(void);
U16 GetWaterOutAccumulateAmount(void);
void SetWaterOutAccumulateAmountFlushing(U32 xUamount);
void ClearWaterOutAccumulateAmountFlushing(void);
U16 GetWaterOutAccumulateAmountFlushing(void);
U8 IsWaterOutMaxAmountFlushing(void);

U8 GetHotTempCondition( D64 xDtemp );
U8 GetColdTempCondition( D64 xDtemp );


#endif /* __WATER_OUT_H__ */
