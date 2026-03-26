/**
 * File : amount.h
 *
 * Amount ( Ascending, Descending, Step, Qsort )
**/
#ifndef __AMOUNT_H__
#define __AMOUNT_H__

#define  CURSOR_AMOUNT_LEVER      5   

#define HOT_WATER_AMOUT_CORRECTION_RATIO        (1.15f)
#define HOT_WATER_AMOUT_CORRECTION_RATIO_2      (1.05f)

#define AMOUNT_TIME_3MIN       18000   // 3min @10ms

#define AMOUNT_ROOM_TIME_4OZ         520    // 118mL  //@10ms
#define AMOUNT_ROOM_TIME_6OZ         800    // 177mL  //@10ms
#define AMOUNT_ROOM_TIME_8OZ        1050    // 237mL  //@10ms
#define AMOUNT_ROOM_TIME_10OZ       1300    // 296mL  //@10ms
#define AMOUNT_ROOM_TIME_12OZ       1570    // 355mL  //@10ms
#define AMOUNT_ROOM_TIME_14OZ       1830    // 414mL  //@10ms
#define AMOUNT_ROOM_TIME_16OZ       2090    // 473mL  //@10ms
#define AMOUNT_ROOM_TIME_20OZ       2615    // 591mL  //@10ms
#define AMOUNT_ROOM_TIME_24OZ       3100    // 710mL  //@10ms
#define AMOUNT_ROOM_TIME_28OZ       3600    // 828mL  //@10ms
#define AMOUNT_ROOM_TIME_32OZ       4150    // 946mL  //@10ms
#define AMOUNT_ROOM_TIME_36OZ       4670    // 1065mL //@10ms
#define AMOUNT_ROOM_TIME_40OZ       5190    // 1180mL //@10ms
#define AMOUNT_ROOM_TIME_68OZ       8800    // 2012mL //@10ms
#define AMOUNT_ROOM_TIME_1L         4400    // 1000mL //@10ms

#define AMOUNT_COLD_TIME_4OZ         480    // 118mL  //@10ms
#define AMOUNT_COLD_TIME_6OZ         700    // 177mL  //@10ms
#define AMOUNT_COLD_TIME_8OZ         950    // 237mL  //@10ms
#define AMOUNT_COLD_TIME_10OZ       1150    // 296mL  //@10ms
#define AMOUNT_COLD_TIME_12OZ       1380    // 355mL  //@10ms
#define AMOUNT_COLD_TIME_14OZ       1600    // 414mL  //@10ms
#define AMOUNT_COLD_TIME_16OZ       1900    // 473mL  //@10ms
#define AMOUNT_COLD_TIME_20OZ       2305    // 591mL  //@10ms
#define AMOUNT_COLD_TIME_24OZ       2750    // 710mL  //@10ms
#define AMOUNT_COLD_TIME_28OZ       3200    // 828mL  //@10ms
#define AMOUNT_COLD_TIME_32OZ       3600    // 946mL  //@10ms
#define AMOUNT_COLD_TIME_36OZ       4050    // 1065mL //@10ms
#define AMOUNT_COLD_TIME_40OZ       4500    // 1180mL //@10ms
#define AMOUNT_COLD_TIME_68OZ       7800    // 2012mL //@10ms
#define AMOUNT_COLD_TIME_1L         3900    // 1000mL //@10ms

#define AMOUNT_HOT_TIME_4OZ          620    // 118mL  //@10ms
#define AMOUNT_HOT_TIME_6OZ          920    // 177mL  //@10ms
#define AMOUNT_HOT_TIME_8OZ         1250    // 237mL  //@10ms
#define AMOUNT_HOT_TIME_10OZ        1600    // 296mL  //@10ms
#define AMOUNT_HOT_TIME_12OZ        1850    // 355mL  //@10ms
#define AMOUNT_HOT_TIME_14OZ        2200    // 414mL  //@10ms
#define AMOUNT_HOT_TIME_16OZ        2500    // 473mL  //@10ms
#define AMOUNT_HOT_TIME_20OZ        3200    // 591mL  //@10ms
#define AMOUNT_HOT_TIME_24OZ        3700    // 710mL  //@10ms
#define AMOUNT_HOT_TIME_28OZ        4400    // 828mL  //@10ms
#define AMOUNT_HOT_TIME_32OZ        5000    // 946mL  //@10ms
#define AMOUNT_HOT_TIME_36OZ        5600    // 1065mL //@10ms
#define AMOUNT_HOT_TIME_40OZ        6200    // 1180mL //@10ms
#define AMOUNT_HOT_TIME_68OZ        9500    // 2012mL //@10ms
#define AMOUNT_HOT_TIME_1L          5400    // 1000mL //@10ms

typedef enum _unit_type_
{
    UNIT_TYPE_OZ = 0,
    UNIT_TYPE_ML,
    UNIT_TYPE_MAX,
} EUnitType_T;

typedef enum _sort_type_
{
    SORT_TYPE_ASCENDING = 0,
    SORT_TYPE_DESCENDING,
    SORT_TYPE_MAX,
} ESortType_T;

typedef enum _amount_id_
{
    AMOUNT_ID_4OZ = 0,        // 0 :
    AMOUNT_ID_6OZ,            // 1 :
    AMOUNT_ID_8OZ,            // 2 :
    AMOUNT_ID_10OZ,           // 3 :
    AMOUNT_ID_12OZ,           // 4 :
    AMOUNT_ID_14OZ,           // 5 :
    AMOUNT_ID_16OZ,           // 6 :
    AMOUNT_ID_20OZ,           // 7 :
    AMOUNT_ID_24OZ,           // 8 :
    AMOUNT_ID_28OZ,           // 9 :
    AMOUNT_ID_32OZ,           // 10 :
    AMOUNT_ID_36OZ,           // 11 :
    AMOUNT_ID_40OZ,           // 12 :
    AMOUNT_ID_INFINITY,       // 13 :
  //  AMOUNT_ID_LEVER,          // 14
    AMOUNT_ID_MY,             // 14 :
    AMOUNT_ID_8585,           // 15 :
    AMOUNT_ID_8585_HOT,       // 16 : 
    AMOUNT_ID_8585_ROOM_COLD, // 17 :
    AMOUNT_ID_8585_FILTER,    // 18 :
    
    AMOUNT_ID_MAX,            // 19 :
} EAmountId_T;



void InitAmount(void);
void SetSkipCursorIncrease(U8 mu8Val);
U8 GetSkipCursorIncrease(void);
void SetArrangeAmount( U8 xUsort );
U8 GetArrangeAmount( void );
void SetAmountUnitType( EUnitType_T xEtype );
EUnitType_T GetAmountUnitType( void );
void SetAmountSortType( ESortType_T xEtype );
ESortType_T GetAmountSortType( void );
U8 GetAmountStep( void );
void SetAmountDefault( EAmountId_T xEid );
EAmountId_T GetAmountDefault( void );
U8 GetWifiAmountDefault( void );
void SetAmountDefaultCursor( U8 xUcursor );
U8 GetAmountDefaultCursor( void );
void SetAmountCursor( U8 xUcursor );
U8 GetAmountCursor( void );
U8 UpdateAmountCursor( void );
U8 GetAmountLeverCursor( void );
U8 GetAmountBackupCursor( void );
void SetAmountBackupCursor(U8 mu8Val);

EAmountId_T GetAmountId( U8 xUcursor );

U16 GetAmount( EAmountId_T xEid );
U8 GetAmountDataId( EAmountId_T xEid );
U16 GetAmountTime( EAmountId_T xEid );
U32 GetAmountRoomHz( EAmountId_T xEid );
U32 GetAmountRoomTime( EAmountId_T xEid );
U32 GetAmountColdTime( EAmountId_T xEid );
U32 GetAmountHotTime( EAmountId_T xEid );

U8 CalcPercent( U32 xUtarget, U32 xUcurrent );
U16 CalcOz(U32 xUamount);
U16 CalcLiter5ml(U32 xUamount);
U16 CalcLiter10ml(U32 xUamount);
U32 CalcAmount(U16 mLiter);
U16 GetAmountUser( EAmountId_T xEid );
U32 CalcUserAmount(U32 xUamount);
U32 CalcUserFlushingAmount(U32 xUamount);

void SetAmountConfig( EAmountId_T xEid, U8 xUconfig );
U8 GetAmountConfig( EAmountId_T xEid );

void ControlAmountConfig(void);

U32 GetTimerPerCup(U8 mu8OutSelect);
U32 GetLowLevelAddTime(U8 mu8AmoutType, U8 mu8OutSelect);
U32 GetMidLowLevelAddTime(U8 mu8AmoutType, U8 mu8OutSelect);
U32 GetMidHighLevelAddTime(U8 mu8AmoutType, U8 mu8OutSelect);

void SetInitCursor(U8 mu8Val);
U8 GetInitCursor(void);

void AddWaterOutTime(void);
void AddHotWaterOutTime(void);

#endif  /* __AMOUNT_H__ */
