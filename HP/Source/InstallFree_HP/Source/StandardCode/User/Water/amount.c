/**
 * File : amount.h
 *
 * Amount ( Ascending, Descending, Step, Qsort )
**/
#include "Global_Header.h"
#include "amount.h"

#include "water_out.h"
#include "water_out_type.h"
// #include "hot_water_out.h"


U16         gUarrSortingBuf[AMOUNT_ID_MAX];     // 오름차순 / 내림차순
EAmountId_T gEarrAmountBuf[AMOUNT_ID_MAX];

typedef struct _amount_
{
    U8 mUsorting;                  // 정렬 업데이트 시작 / 정지

    EUnitType_T mEunitType;        // oz / mL 단위
    ESortType_T mEsortType;        // 오름차순 / 내림차순

    U8 mUstep;                     // 용량 최대 단계

    EAmountId_T mEdefaultAmount;   // Default Amount Id
    U8 mUdefaultCursor;            // Default Amount Buffer Position

    U8 mUcursor;                   // Amount Buffer Position
    U8 BackupCursor;               // 물양 선택한 상황에서 디폴트 물양 세팅 하면 용량bar는 디폴트 물양을 표시하는데 이를 방지하기위해(SEG,실제 타겟용량은 현재선택한 물양 표시)

    U8 SkipCursorIncrease;         // 용량버튼 누를 때 디폴트 용량 한단계 위 용량이 선택됨을 방지 하기위해(TRUE : 디폴트 물량 설정한 직 후인 상황)
} SAmount_T;

SAmount_T gStAmount;

// @100ms
// 1Cup - 120ml
const static U32 gu32TimePerCup[ MAX_WATER_ID ] =
{
    480UL,      // ROOM
    540UL,      // COLD
    550UL,      // HOT 
};

/* Low level */
const static U32 gu32TankLowLevelAddTimeTable[AMOUNT_ID_MAX][MAX_WATER_ID] =  
{
                   //   ROOM    COLD    HOT  
/* 4OZ            */ {  40UL,   40UL,   40UL },     
/* 6OZ            */ {  60UL,   60UL,   60UL }, 
/* 8OZ            */ {  80UL,   80UL,   80UL }, 
/* 10OZ           */ { 100UL,  100UL,  100UL }, 	
/* 12OZ           */ { 120UL,  120UL,  120UL }, 
/* 14OZ           */ { 140UL,  140UL,  140UL }, 	
/* 16OZ           */ { 160UL,  160UL,  160UL }, 
/* 20OZ           */ { 200UL,  200UL,  200UL }, 	
/* 24OZ           */ { 240UL,  240UL,  240UL }, 
/* 28OZ           */ { 280UL,  280UL,  280UL }, 	
/* 32OZ           */ { 320UL,  320UL,  320UL }, 
/* 36OZ           */ { 360UL,  360UL,  360UL }, 	
/* 40OZ           */ { 400UL,  400UL,  400UL }, 
/* INFINITY       */ {   0UL,    0UL,    0UL }, 
/* LEVER          */ //{   0UL,    0UL,    0UL }, 
/* MYCUP          */ {  50UL,   50UL,   50UL }, 
/* 8585           */ {  50UL,   50UL,   50UL }, 	
/* 8585_HOT       */ {  50UL,   50UL,   50UL }, 
/* 8585_ROOM_COLD */ {  50UL,   50UL,   50UL }, 	
/* 8585FILTER     */ {  50UL,   50UL,   50UL }, 
};

/* Mid(room,hot tank) or Middle Low(cold tank) level */
const static U32 gu32TankMidLowLevelAddTimeTable[AMOUNT_ID_MAX][MAX_WATER_ID] =  
{
                   //   ROOM    COLD    HOT  
/* 4OZ            */ {  20UL,   20UL,   20UL },     
/* 6OZ            */ {  30UL,   30UL,   30UL }, 
/* 8OZ            */ {  40UL,   40UL,   40UL }, 
/* 10OZ           */ {  50UL,   50UL,   50UL }, 	
/* 12OZ           */ {  60UL,   60UL,   60UL }, 
/* 14OZ           */ {  70UL,   70UL,   70UL }, 	
/* 16OZ           */ {  80UL,   80UL,   80UL }, 
/* 20OZ           */ { 100UL,  100UL,  100UL }, 	
/* 24OZ           */ { 120UL,  120UL,  120UL }, 
/* 28OZ           */ { 140UL,  140UL,  140UL }, 	
/* 32OZ           */ { 160UL,  160UL,  160UL }, 
/* 36OZ           */ { 360UL,  360UL,  360UL }, 	
/* 40OZ           */ { 400UL,  400UL,  400UL }, 
/* INFINITY       */ {   0UL,    0UL,    0UL }, 
/* LEVER          */ //{   0UL,    0UL,    0UL }, 
/* MYCUP          */ {  50UL,   50UL,   50UL }, 
/* 8585           */ {  50UL,   50UL,   50UL }, 	
/* 8585_HOT       */ {  50UL,   50UL,   50UL }, 
/* 8585_ROOM_COLD */ {  50UL,   50UL,   50UL }, 	
/* 8585FILTER     */ {  50UL,   50UL,   50UL }, 
};

/* Middle High level - Only for cold tank, because only the cold tank has a middle sensor */
const static U32 gu32TankMidHighLevelAddTimeTable[AMOUNT_ID_MAX][MAX_WATER_ID] =  
{
                   //   ROOM    COLD    HOT  
/* 4OZ            */ {  20UL,   20UL,   20UL },     
/* 6OZ            */ {  30UL,   30UL,   30UL }, 
/* 8OZ            */ {  40UL,   40UL,   40UL }, 
/* 10OZ           */ {  50UL,   50UL,   50UL }, 	
/* 12OZ           */ {  60UL,   60UL,   60UL }, 
/* 14OZ           */ {  70UL,   70UL,   70UL }, 	
/* 16OZ           */ {  80UL,   80UL,   80UL }, 
/* 20OZ           */ { 100UL,  100UL,  100UL }, 	
/* 24OZ           */ { 120UL,  120UL,  120UL }, 
/* 28OZ           */ { 140UL,  140UL,  140UL }, 	
/* 32OZ           */ { 160UL,  160UL,  160UL }, 
/* 36OZ           */ { 360UL,  360UL,  360UL }, 	
/* 40OZ           */ { 400UL,  400UL,  400UL }, 
/* INFINITY       */ {   0UL,    0UL,    0UL }, 
/* LEVER          */ //{   0UL,    0UL,    0UL }, 
/* MYCUP          */ {  50UL,   50UL,   50UL }, 
/* 8585           */ {  50UL,   50UL,   50UL }, 	
/* 8585_HOT       */ {  50UL,   50UL,   50UL }, 
/* 8585_ROOM_COLD */ {  50UL,   50UL,   50UL }, 	
/* 8585FILTER     */ {  50UL,   50UL,   50UL }, 
};


//  HIGH or MID @10ms
//  INFINITY - 3min
/*
U32 gu32FixedAmountTimeTable[MAX_WATER_ID][MAX_FIXED_AMOUNT_NUM] = 
{
  //  120ml      250ml      500ml     1000ml    INFINITY     
    { 370UL,     750UL,    1500UL,    3050UL,   18000UL },    // ROOM
    { 370UL,     750UL,    1500UL,    3050UL,   18000UL },    // COLD
    { 470UL,    1000UL,    2000UL,    4200UL,   18000UL },    // HOT
};
*/


void InitAmount(void)
{
    MEMSET( (void __FAR *)&gStAmount, 0x00, sizeof(SAmount_T) );
    MEMSET( (void __FAR *)&gUarrSortingBuf, 0x00, sizeof(gUarrSortingBuf) );
    MEMSET( (void __FAR *)&gEarrAmountBuf, 0x00, sizeof(gEarrAmountBuf) );

    SetAmountConfig(AMOUNT_ID_8OZ,      TRUE);   // cursor 0 → 8oz  (235ml)
    SetAmountConfig(AMOUNT_ID_16OZ,     TRUE);   // cursor 1 → 16oz (475ml)
    SetAmountConfig(AMOUNT_ID_INFINITY, TRUE);   // cursor 2 → 무한
    
    SetAmountDefault(AMOUNT_ID_8OZ);

    gStAmount.mUsorting = TRUE;
    // gStAmount.SkipCursorIncrease -> EEPROM에서 값 넣어주는 중이라서 Init에서 값 넣어줘도 소용없음
}

void SetSkipCursorIncrease(U8 mu8Val)
{
    gStAmount.SkipCursorIncrease = mu8Val;
}

U8 GetSkipCursorIncrease(void)
{
    return gStAmount.SkipCursorIncrease;
}

void SetArrangeAmount( U8 xUsort )
{
    gStAmount.mUsorting = xUsort;
}

U8 GetArrangeAmount( void )
{
    return gStAmount.mUsorting;
}

void SetAmountUnitType( EUnitType_T xEtype )
{
    if( xEtype >= UNIT_TYPE_MAX )
    {
        return;
    }

    if( gStAmount.mEunitType != xEtype )
    {
        // SaveEepromId(EEPROM_ID_AMOUNT_UNIT_TYPE);
    }

    gStAmount.mEunitType = xEtype;
}

EUnitType_T GetAmountUnitType( void )
{
    return gStAmount.mEunitType;
}

void SetAmountSortType( ESortType_T xEtype )
{
    if( xEtype >= SORT_TYPE_MAX )
    {
        return;
    }

    if( gStAmount.mEsortType != xEtype )
    {
        // SaveEepromId(EEPROM_ID_AMOUNT_SORT_TYPE);
    }

    gStAmount.mEsortType = xEtype;
    SetArrangeAmount(TRUE);
}

ESortType_T GetAmountSortType( void )
{
    return gStAmount.mEsortType;
}

void SetAmountStep( U8 xUstep )
{
    gStAmount.mUstep = xUstep;
}

U8 GetAmountStep( void )
{
    return gStAmount.mUstep;
}

void SetAmountDefault( EAmountId_T xEid )
{
    if( xEid >= AMOUNT_ID_MAX )
    {
        return;
    }

    if( gStAmount.mEdefaultAmount != xEid )
    {
        // SaveEepromId(EEPROM_ID_AMOUNT_DEFAULT);
    }

    gStAmount.SkipCursorIncrease = TRUE;
    gStAmount.mEdefaultAmount = xEid;
    SetArrangeAmount(TRUE);
}

EAmountId_T GetAmountDefault( void )
{
    return gStAmount.mEdefaultAmount;
}

void SetAmountDefaultCursor( U8 xUcursor )
{
    gStAmount.mUdefaultCursor = xUcursor;
}

U8 GetWifiAmountDefault(void)
{
    if(gStAmount.mEdefaultAmount == AMOUNT_ID_16OZ)
    {
        return 0;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_20OZ)
    {
        return 1;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_24OZ)
    {
        return 2;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_28OZ)
    {
        return 3;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_32OZ)
    {
        return 4;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_36OZ)
    {
        return 5;
    }
    else if(gStAmount.mEdefaultAmount == AMOUNT_ID_40OZ)
    {
        return 6;
    }
    else
    {
        return 7;
    }
}

U8 GetAmountDefaultCursor( void )
{
    return gStAmount.mUdefaultCursor;
}

static U8 IsFinalAmountStep(void)
{
#if 0
    /* 우측 추출 중 */
    if(GetWaterOut() == TRUE)
    {
        if( gStAmount.mUcursor == (gStAmount.mUstep - 1) )
        {
            if( GetHotWaterOutPressContinue() == FALSE)
            {
                SetHotWaterOutPressContinue(TRUE);
                return TRUE;
            }
        }
    }
    /* 좌측 추출 중 */
    else if(GetHotWaterOut() == TRUE)
    {
        if( gStAmount.mUcursor == (gStAmount.mUstep - 1) )
        {
            if(GetWaterOutPressContinue() == FALSE)
            {
                SetWaterOutPressContinue(TRUE);
                return TRUE;
            }
        }
    }
    /* 좌측, 우측 모두 추출 안하고있을 때 */
    else if(GetWaterOut() == FALSE
        && GetHotWaterOut() == FALSE)
    {
        if( gStAmount.mUcursor == (gStAmount.mUstep - 1) )
        {
            if(GetWaterOutPressContinue() == FALSE
                && GetHotWaterOutPressContinue() == FALSE)
            {
                SetWaterOutPressContinue(TRUE);
                SetHotWaterOutPressContinue(TRUE);
                return TRUE;
            }
        }
    }
#endif
    return FALSE;
}

U8 UpdateAmountCursor( void )
{
#if 0
    /* 용량 마지막 단계에서는 Lever로 전환 하기 위해 레버세팅(함수안에서)하고 return; */
    if(IsFinalAmountStep() == TRUE)
    {
        gStAmount.mUcursor = ( gStAmount.mUcursor % ( gStAmount.mUstep) );
        return gStAmount.mUcursor;
    }
#endif

    /* 우측 추줄중이지 않을  때 */
    if(GetWaterOut() == FALSE)
    {
        // SetWaterOutPressContinue(FALSE); // 우측 레버 해제
    }
#if 0
    /* 좌측 추줄중이지 않을 때 */
    if(GetHotWaterOut() == FALSE)
    {
        // SetHotWaterOutPressContinue(FALSE); // 좌측 레버 해제
    }
#endif

    /* 디폴트 물양 한 단계 위 물양이 선택되는걸 방지 */
    if( gStAmount.SkipCursorIncrease == TRUE )
    {
        gStAmount.SkipCursorIncrease = FALSE;
        gStAmount.mUcursor = ( gStAmount.mUcursor % ( gStAmount.mUstep) );
        gStAmount.BackupCursor = gStAmount.mUcursor;
        return gStAmount.mUcursor;
    }

    gStAmount.mUcursor++;
    gStAmount.mUcursor = ( gStAmount.mUcursor % ( gStAmount.mUstep) );
    gStAmount.BackupCursor = gStAmount.mUcursor;
    
    return gStAmount.mUcursor;
}

/* 용량이 레버인 Step 값 */
U8 GetAmountLeverCursor( void )
{
    return (gStAmount.mUstep - 1);
}

U8 GetAmountCursor( void )
{
    return gStAmount.mUcursor;
}

void SetAmountCursor( U8 xUcursor )
{
    gStAmount.mUcursor = xUcursor;
}

U8 GetAmountBackupCursor( void )
{
    return gStAmount.BackupCursor;
}

void SetAmountBackupCursor(U8 mu8Val)
{
    gStAmount.BackupCursor = mu8Val;
}

EAmountId_T GetAmountId( U8 xUcursor )
{
    return gEarrAmountBuf[xUcursor];
}

typedef struct _amount_Data_
{
    EAmountId_T mUid;
    U16 mUoz;           // display
    U16 mUml;           // display
    U16 mUtime;         // output time
    // U32 mUroomHz;       // FlowMeter room output Hz   
    U32 mUroomTime;     // Room Tank Time     
    U32 mUcoldTime;     // Cold Tank Time    
    U32 mUhotTime;      // Hot Tank Time
} SAmountData_T;
const static SAmountData_T gStAmountData[] =
{
  /*  Id                      Oz    Ml   Time                       Room Time              Cold Time               Hot Time             */
  { AMOUNT_ID_4OZ,            4,   120,  0,                         AMOUNT_ROOM_TIME_4OZ,  AMOUNT_COLD_TIME_4OZ,   AMOUNT_HOT_TIME_4OZ  },
  { AMOUNT_ID_6OZ,            6,   175,  0,                         AMOUNT_ROOM_TIME_6OZ,  AMOUNT_COLD_TIME_6OZ,   AMOUNT_HOT_TIME_6OZ  },
  { AMOUNT_ID_8OZ,            8,   235,  0,                         AMOUNT_ROOM_TIME_8OZ,  AMOUNT_COLD_TIME_8OZ,   AMOUNT_HOT_TIME_8OZ  },
  { AMOUNT_ID_10OZ,           10,  295,  0,                         AMOUNT_ROOM_TIME_10OZ, AMOUNT_COLD_TIME_10OZ,  AMOUNT_HOT_TIME_10OZ },
  { AMOUNT_ID_12OZ,           12,  355,  0,                         AMOUNT_ROOM_TIME_12OZ, AMOUNT_COLD_TIME_12OZ,  AMOUNT_HOT_TIME_12OZ },
  { AMOUNT_ID_14OZ,           14,  415,  0,                         AMOUNT_ROOM_TIME_14OZ, AMOUNT_COLD_TIME_14OZ,  AMOUNT_HOT_TIME_14OZ },
  { AMOUNT_ID_16OZ,           16,  475,  0,                         AMOUNT_ROOM_TIME_16OZ, AMOUNT_COLD_TIME_16OZ,  AMOUNT_HOT_TIME_16OZ },
  { AMOUNT_ID_20OZ,           20,  590,  0,                         AMOUNT_ROOM_TIME_20OZ, AMOUNT_COLD_TIME_20OZ,  AMOUNT_HOT_TIME_20OZ },
  { AMOUNT_ID_24OZ,           24,  710,  0,                         AMOUNT_ROOM_TIME_24OZ, AMOUNT_COLD_TIME_24OZ,  AMOUNT_HOT_TIME_24OZ },  
  { AMOUNT_ID_28OZ,           28,  830,  0,                         AMOUNT_ROOM_TIME_28OZ, AMOUNT_COLD_TIME_28OZ,  AMOUNT_HOT_TIME_28OZ },     
  { AMOUNT_ID_32OZ,           32,  945,  0,                         AMOUNT_ROOM_TIME_32OZ, AMOUNT_COLD_TIME_32OZ,  AMOUNT_HOT_TIME_32OZ },
  { AMOUNT_ID_36OZ,           36, 1065,  0,                         AMOUNT_ROOM_TIME_36OZ, AMOUNT_COLD_TIME_36OZ,  AMOUNT_HOT_TIME_36OZ },     
  { AMOUNT_ID_40OZ,           40, 1180,  0,                         AMOUNT_ROOM_TIME_40OZ, AMOUNT_COLD_TIME_40OZ,  AMOUNT_HOT_TIME_40OZ },
  { AMOUNT_ID_INFINITY,       68, 2000,  1800,                      AMOUNT_TIME_3MIN,      AMOUNT_TIME_3MIN,       AMOUNT_TIME_3MIN     },
  //{ AMOUNT_ID_LEVER,          69, 2001,  AMOUNT_INNO_TIME_INFINITE, AMOUNT_INNO_HZ_68OZ,  AMOUNT_TIME_3MIN,      AMOUNT_TIME_3MIN,       AMOUNT_TIME_3MIN     },
  { AMOUNT_ID_MY,             11,  300,  0,                         AMOUNT_TIME_3MIN,      AMOUNT_TIME_3MIN,       AMOUNT_TIME_3MIN     },

  // For Durability Testing Of Reliability Team
  { AMOUNT_ID_8585,          34,  1000,   0,                        AMOUNT_ROOM_TIME_1L,   AMOUNT_COLD_TIME_1L,    AMOUNT_HOT_TIME_1L   },
  { AMOUNT_ID_8585_HOT,       2,   60,   0,                         AMOUNT_ROOM_TIME_4OZ,  AMOUNT_COLD_TIME_4OZ,   AMOUNT_HOT_TIME_4OZ  },
  { AMOUNT_ID_8585_ROOM_COLD, 7,   200,  0,                         AMOUNT_COLD_TIME_4OZ,   AMOUNT_HOT_TIME_4OZ  },
  { AMOUNT_ID_8585_FILTER,    51,  1500, 0,                         AMOUNT_ROOM_TIME_4OZ,  AMOUNT_COLD_TIME_4OZ,   AMOUNT_HOT_TIME_4OZ  },
};

static U16 GetAmountOz( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUoz;
}

static U16 GetAmountMl( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUml;
}

U16 GetAmount( EAmountId_T xEid )
{
    if( gStAmount.mEunitType == UNIT_TYPE_ML )
    {
        return GetAmountMl( xEid );
    }
    else
    {
        return GetAmountOz( xEid );
    }
}

U16 GetAmountUser( EAmountId_T xEid )
{
    return GetAmountMl( xEid );
}

U8 GetAmountDataId( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUid;
}

U16 GetAmountTime( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUtime;
}

#if 0
U32 GetAmountRoomHz( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUroomHz;
}
#endif

U32 GetAmountRoomTime( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUroomTime;
}

U32 GetAmountColdTime( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUcoldTime;
}

U32 GetAmountHotTime( EAmountId_T xEid )
{
    return gStAmountData[xEid].mUhotTime;
}

// 추출량 반환 ( percent )
U8 CalcPercent( U32 xUtarget, U32 xUcurrent )
{
    return (U8)(( (F32)xUcurrent / (F32)xUtarget ) * 100.0f);
}

// 추출량 oz 단위 반환
#define OZ_UNIT   (1U) /* 최소 단위 1oz = 29.5735 [ml] */
#if 0
U16 CalcOz(U32 xUamount)
{
    U32 uTargetAmount;

    uTargetAmount = AMOUNT_INNO_HZ_1OZ;

    if( xUamount >= uTargetAmount )
    {
        xUamount = xUamount / uTargetAmount;
        xUamount *= OZ_UNIT;
    }
    else
    {
        xUamount = 0UL;
    }

    return (U16)(xUamount);
}

// 추출량 ml 단위 반환
#define ML_UNIT_5ML   (5U) /* 최소 단위 5ml */
U16 CalcLiter5ml(U32 xUamount)
{
    U32 uTargetAmount;

    uTargetAmount = AMOUNT_INNO_HZ_5ML;

    /*
    if( GetWaterOutSelect() == SEL_WATER_HOT )
    {
        if( GetHotEffluentExtra() == TRUE )
        {
            uTargetAmount *= HOT_WATER_AMOUT_CORRECTION_RATIO;
        }
    }
    */
    
    if( xUamount >= uTargetAmount )
    {
        xUamount = xUamount / uTargetAmount;
        xUamount *= ML_UNIT_5ML;
    }
    else
    {
        xUamount = 0UL;
    }

    return (U16)(xUamount);
}

// 추출량 ml 단위 반환
#define ML_UNIT_10ML   (10U) /* 최소 단위 10ml */
U16 CalcLiter10ml(U32 xUamount)
{
    U32 uTargetAmount;

    uTargetAmount = AMOUNT_INNO_HZ_10ML;

    /*
    if( GetWaterOutSelect() == SEL_WATER_HOT )
    {
        if( GetHotEffluentExtra() == TRUE )
        {
            uTargetAmount *= HOT_WATER_AMOUT_CORRECTION_RATIO;
        }
    }
    */
    
    if( xUamount >= uTargetAmount )
    {
        xUamount = xUamount / uTargetAmount;
        xUamount *= ML_UNIT_10ML;
    }
    else
    {
        xUamount = 0UL;
    }

    return (U16)(xUamount);
}


// ml를 추출양으로 변환
U32 CalcAmount(U16 mLiter)
{
    U32 mu32Amount;

    mLiter /= ML_UNIT_10ML;
    mu32Amount = mLiter * AMOUNT_HZ_10ML;

    return mu32Amount;
}
/*
U32 CalcUserAmount(U32 RoomWaterOutTime, U32 ColdWaterOutTime, U32 HotWaterOutTime)
{
    U32 uTargetAmount;

    if( GetWaterOutSelect() == SEL_WATER_HOT )
    {
        if( GetHotEffluentExtra() == TRUE )
        {
            uTargetAmount *= HOT_WATER_AMOUT_CORRECTION_RATIO;
        }
    }


    if( uTargetAmount != 0UL )
    {
        xUamount = xUamount / uTargetAmount;
        xUamount *= 10UL;
    }
    else
    {
        xUamount = 0UL;
    }

    return xUamount;
}
*/
U32 CalcUserFlushingAmount(U32 xUamount)
{
    U32 uTargetAmount;

    uTargetAmount = AMOUNT_HZ_10ML;
    if( uTargetAmount != 0UL )
    {
        xUamount = xUamount / uTargetAmount;
        xUamount *= 10UL;
    }
    else
    {
        xUamount = 0UL;
    }

    return xUamount;
}
#endif

/**
 * @brief : Function For Compare Data Of Buffer
 * @detail : 오름차순으로 정렬할 때 사용하는 비교함수
 * @param :
 * @return :
**/
static int Ascending(const void *first, const void *second)
{
    if( *(int*)first > *(int*)second )
    {
        return 1;
    }
    else if( *(int*)first < *(int*)second )
    {
        return -1;
    }

    return 0;
}

static int Descending(const void *first, const void *second)
{
    if( *(int*)first < *(int*)second )
    {
        return 1;
    }
    else if( *(int*)first > *(int*)second )
    {
        return -1;
    }

    return 0;
}

typedef struct _amount_config_
{
    EAmountId_T mEid;
    // EepromId_T mEeepromId;
    U8          mUconfig;
} SAmountConfig_T;
SAmountConfig_T gStAmountConfigList[] =
{
    { AMOUNT_ID_4OZ,                FALSE },
    { AMOUNT_ID_6OZ,                FALSE },
    { AMOUNT_ID_8OZ,                TRUE },
    { AMOUNT_ID_10OZ,              FALSE },
    { AMOUNT_ID_12OZ,              FALSE },
    { AMOUNT_ID_14OZ,              FALSE },
    { AMOUNT_ID_16OZ,              TRUE  },
    { AMOUNT_ID_20OZ,              FALSE  },
    { AMOUNT_ID_24OZ,              FALSE  },
    { AMOUNT_ID_28OZ,              FALSE },  
    { AMOUNT_ID_32OZ,              FALSE  },
    { AMOUNT_ID_36OZ,              FALSE },  
    { AMOUNT_ID_40OZ,              FALSE },
    { AMOUNT_ID_INFINITY,          TRUE  },
   // { AMOUNT_ID_LEVER,           EEPROM_ID_NONE,              TRUE  },
    { AMOUNT_ID_MY,                            FALSE },

    // For Durability Testing Of Reliability Team
    { AMOUNT_ID_8585,                          FALSE },
    { AMOUNT_ID_8585_HOT,                      FALSE },
    { AMOUNT_ID_8585_ROOM_COLD,                FALSE },
    { AMOUNT_ID_8585_FILTER,                   FALSE },
    
};

#define	SZ_AMOUNT_CONFIG_LIST		( sizeof( gStAmountConfigList ) / sizeof( SAmountConfig_T ) )

void SetAmountConfig( EAmountId_T xEid, U8 xUconfig )
{
    if( xEid >= AMOUNT_ID_MAX )
    {
        return;
    }

    if( gStAmountConfigList[xEid].mUconfig != xUconfig )
    {
        // SaveEepromId(gStAmountConfigList[xEid].mEeepromId);
    }

    gStAmountConfigList[xEid].mUconfig = xUconfig;

    if( GetArrangeAmount() == FALSE )
    {
        SetArrangeAmount(TRUE);
    }
}

U8 GetAmountConfig( EAmountId_T xEid )
{
    return gStAmountConfigList[xEid].mUconfig;
}

static void ArrangeAmountConfig(void)
{
    U8 uIndex = 0U;
    U8 uStep = 0U;

    for( uIndex=0; uIndex<SZ_AMOUNT_CONFIG_LIST; uIndex++ )
    {
        if( gStAmountConfigList[uIndex].mUconfig == TRUE )
        {
            gUarrSortingBuf[uStep] = GetAmountOz(gStAmountConfigList[uIndex].mEid);
            uStep++;
            SetAmountStep(uStep);
        }
    }

    if( GetAmountSortType() == SORT_TYPE_ASCENDING )
    {
        QSORT(gUarrSortingBuf, (uStep-2), sizeof(U16), Ascending);   // WHY uStep-2? -> Except Infinity, Lever
    }
    else
    {
        QSORT(gUarrSortingBuf, (uStep-2), sizeof(U16), Descending);  // WHY uStep-2? -> Except Infinity, Lever
    }
}

static void ReplaceAmountConfig(void)
{
    U8  uIndex = 0U;
    U8  uIndex2 = 0U;
    U8  uStep = 0U;
    U16 uSortData = 0U;
    U8  uLen = GetAmountStep();
    
    for( uIndex=0; uIndex<AMOUNT_ID_MAX; uIndex++ )
    {
        for( uIndex2=0; uIndex2<uLen; uIndex2++ )
        {
            uSortData = gStAmountData[uIndex].mUoz;

            if( uSortData == gUarrSortingBuf[uIndex2] )
            {
                gEarrAmountBuf[uIndex2] = gStAmountData[uIndex].mUid;

                if( GetAmountDefault() == gStAmountData[uIndex].mUid )
                {
                    SetAmountCursor(uIndex2);
                    SetAmountDefaultCursor(uIndex2);
                }
            }
        }
    }
}

void ControlAmountConfig(void)
{
    if( GetArrangeAmount() == FALSE )
    {
        return;
    }
    else
    {
        MEMSET( (void __FAR *)&gUarrSortingBuf, 0x00, sizeof(gUarrSortingBuf) );
        MEMSET( (void __FAR *)&gEarrAmountBuf, 0x00, sizeof(gEarrAmountBuf) );
    }

    ArrangeAmountConfig();  // 활성화된 용량 기준으로 오름차순 / 내림차순 정렬됨 ( 용량 크기 기반 )
    ReplaceAmountConfig();  // 정렬된 용량 크기를 용량 ID 로 치환

    SetArrangeAmount(FALSE);
}

U32 GetTimerPerCup(U8 mu8OutSelect)
{
    return gu32TimePerCup[ mu8OutSelect ];
}

U32 GetLowLevelAddTime(U8 mu8AmoutType,U8 mu8OutSelect)
{
    return gu32TankLowLevelAddTimeTable[ mu8AmoutType ][ mu8OutSelect ];
}

U32 GetMidLowLevelAddTime(U8 mu8AmoutType,U8 mu8OutSelect)
{
    return gu32TankMidLowLevelAddTimeTable[ mu8AmoutType ][ mu8OutSelect ];
}

U32 GetMidHighLevelAddTime(U8 mu8AmoutType,U8 mu8OutSelect)
{
    return gu32TankMidHighLevelAddTimeTable[ mu8AmoutType ][ mu8OutSelect ];
}

/* Room tank(Hot input buffer tank)*/
static void CheckRoomWaterLevel(U8 mu8AmoutType)
{
#if 0
    U8 mu8OutSelect = 0;
    U32 mu32FixedAmountTargetTime = 0;

    mu32FixedAmountTargetTime = GetWaterOutFixedAmountTargetTime();
    mu8OutSelect = GetWaterOutSelect();

    // 추가 입수 ( 저수위 조건 ) 
    if( GetRoomWaterLevel() == LEVEL_LOW )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetLowLevelAddTime( mu8AmoutType, mu8OutSelect );
        SetWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
    // 추가 입수 ( 중수위 조건 ) 
    else if(GetRoomWaterLevel() == LEVEL_MID )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetMidLowLevelAddTime( mu8AmoutType, mu8OutSelect );
        SetWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
#endif
}

/* Room tank(Hot input buffer tank)*/
static void CheckHotWaterLevel(U8 mu8AmoutType)
{
#if 0
    U8 mu8OutSelect = 0;
    U32 mu32FixedAmountTargetTime = 0;

    mu32FixedAmountTargetTime = GetHotWaterOutFixedAmountTargetTime();
    mu8OutSelect = GetHotWaterOutSelect();

    // 추가 입수 ( 저수위 조건 ) 
    if( GetRoomWaterLevel() == LEVEL_LOW )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetLowLevelAddTime( mu8AmoutType, mu8OutSelect );
        SetHotWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
    // 추가 입수 ( 중수위 조건 ) 
    else if(GetRoomWaterLevel() == LEVEL_MID )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetMidLowLevelAddTime( mu8AmoutType, mu8OutSelect );
        SetHotWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
#endif
}

/* Cold tank */
static void CheckColdWaterLevel(U8 mu8AmoutType)
{
#if 0
    U32 mu32FixedAmountTargetTime = 0;

    mu32FixedAmountTargetTime = GetWaterOutFixedAmountTargetTime();

    // 추가 입수 ( 저수위 조건 ) 
    if( GetColdWaterLevel() == LEVEL_LOW )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetLowLevelAddTime( mu8AmoutType, SEL_WATER_COLD );
        SetWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
    // 추가 입수 ( 중수위 하 조건 ) 
    else if(GetColdWaterLevel() == LEVEL_MID )
    {
        mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetMidLowLevelAddTime( mu8AmoutType, SEL_WATER_COLD );
        SetWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
    }
    // 추가 입수 ( 중수위 상 조건 ) 
   // else if(GetColdWaterLevel() == LEVEL_MID_HIGH )
   // {
   //       mu32FixedAmountTargetTime = mu32FixedAmountTargetTime + GetMidHighLevelAddTime( mu8AmoutType, SEL_WATER_COLD );
   //       SetWaterOutFixedAmountTargetTime(mu32FixedAmountTargetTime);
   // }       
   
#endif
}

void AddWaterOutTime(void)
{
    U8 mu8AmountType;
    U8 mu8OutSelect;
    
    mu8AmountType = GetWaterOutAmountType();
    mu8OutSelect = GetWaterOutSelect();
#if 0
    /* Cold */
    if(mu8OutSelect == SEL_WATER_COLD)
    {
        CheckColdWaterLevel(mu8AmountType);
    }
    /* Room(Tank), Hot */
    else
    {
        CheckRoomWaterLevel(mu8AmountType);
    }
#endif
}

void AddHotWaterOutTime(void)
{
#if 0
    U8 mu8HotAmountType;
    U8 mu8HotOutSelect;
    
    mu8HotAmountType = GetHotWaterOutAmountType();
    mu8HotOutSelect = GetHotWaterOutSelect();
 
    /* Room(Tank), Hot */
    if(mu8HotOutSelect == SEL_WATER_HOT)
    {
        CheckHotWaterLevel(mu8HotAmountType);
    }
#endif
}


