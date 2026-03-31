#include "Global_Header.h"
#include "flushing.h"

static void InitOutEventList(void);
static void SetFlushingStepStatus(U8 Status);
static void SetFlushingCurrentMode(U32 mu32Val);
static void SetFlushOutMode( U32 xUmode );

static U8 DoFilterFlushingInit( U8 *xUptrStep );
static U8 DoFillHot( U8 *xUptrStep );
static U8 DoCloseValves( U8 *xUptrStep );
static U8 DoDone( U8 *xUptrStep );

SFlushing_T gStFlushing;

typedef U8 (*PFDoAction_T)(U8 *xUptrStep);
typedef struct _flush_out_event_
{
    U32           gu32Umode;
    U8            gu8mUstep;
    PFDoAction_T  mUptrFunAction;
} SFlushOutEvent_T;
static SFlushOutEvent_T gStOutEventList[] =
{
    // { FLUSH_OUT_PAIRING_WIFI,      0U, DoPairingWifi        },
    { FLUSH_OUT_INIT,              0U, DoFilterFlushingInit },
    // { FLUSH_OUT_FILTER_NEO,        0U, DoFilterFlushingNeo  },
    // { FLUSH_OUT_FILTER_RO,         0U, DoFilterFlushingRo   },
    // { FLUSH_OUT_FILTER_INNO_STEP1, 0U, DoFillHotAndRoom     },
    // { FLUSH_OUT_FILTER_INNO_STEP2, 0U, DoDrainHotAndRoom    },
    // { FLUSH_OUT_FILL_COLD,         0U, DoFillCold           },  // First or Change 123 - This loop run 4 times.
    { FLUSH_OUT_FILL_HOT,          0U, DoFillHot            },  // First or Change 123 - This loop run 4 times.
    // { FLUSH_OUT_FILL_ROOM,         0U, DoFillRoom           },  // First or Change 123 - This loop run 4 times. - Check drain setting
    // { FLUSH_OUT_DRAIN_COLD,        0U, DoDrainCold          },  // First or Change 123 - This loop run 3 times.
    // { FLUSH_OUT_DRAIN_ROOM,        0U, DoDrainRoom          },  // First or Change 123 - This loop run 3 times.
    // { FLUSH_OUT_DRAIN_HOT,         0U, DoDrainHot           },  // First or Change 123 - This loop run 3 times. - Check fill setting
    // { FLUSH_OUT_CLOSE_VALVE,       0U, DoCloseValves        },
    { FLUSH_OUT_DONE,              0U, DoDone               },
};
#define SZ_FLUSH_OUT_EVENT_LIST (sizeof(gStOutEventList) / sizeof(SFlushOutEvent_T))

/* First Flushing, Filter Change Flushing */
void InitFlushing(void)
{
    MEMSET( (void __FAR *)&gStFlushing, 0x00, sizeof(SFlushing_T) );

    gStFlushing.Config = TRUE;
    gStFlushing.RunStatus = FALSE;
    gStFlushing.PrevRunStatus = FALSE; 
    gStFlushing.Pause = FALSE; 
    
    gStFlushing.mUactTime = 0;
    gStFlushing.mUactHz = 0;
      
    gStFlushing.mEtype = FLUSHING_TYPE_FIRST;
    gStFlushing.mEstatus = FLUSHING_STATUS_WAIT;

    // gStFlushing.mUforcemodeLimitTimer = FLUSHING_FORCE_MODE_LIMIT_TIMER;
    // gStFlushing.mUresetLimitTimer = FLUSHING_FORCE_MODE_LIMIT_TIMER;

    gStFlushing.FilterChangeTypeMode = FALSE;
    // gStFlushing.FilterChangeTypeModeTimer = FILTER_CAHNGE_TYPE_MODEL_LIMIT_TIMER;

    gStFlushing.CancelDisable = FALSE;

    gStFlushing.SettingBackup = FALSE;

    InitOutEventList();

    // 부팅 시 온수히터 만수위부터 확인
    // TurnOnFlush();
    SetFlushOutMode(FLUSH_ALL_INSTALL_FREE);
}

void CompleteFlushing(void)
{
    if( GetFlushingType() == FLUSHING_TYPE_FIRST )
    {
        SetFlushingType(FLUSHING_TYPE_FILTER);
    }

    /* 플러싱 관련 동작들 stop */
    StopAllFlushingOperation();  // 강제로 취소시켰을 때 동작하고있던 것들 Stop 해줘야함

    /* 플러싱 관련 변수들 초기화 */
    ResetFlushing();

    /* 필터 관련 변수들 초기화 */
    // SetFlushingCompleted(TRUE);
    // SetFilterChangedStatusMounted();
}

/* 플러싱 관련 변수들 초기화 */
void ResetFlushing(void)
{
    SetFlushingConfig(FALSE);
    // SetFlushingSettingBackup(FALSE);

    gStFlushing.mEstatus = FLUSHING_STATUS_NONE;
    gStFlushing.StepStatus = 0;
    gStFlushing.mUmode = 0;  // 플러싱 모드 종류
    gStFlushing.mUactTime = 0;  // 플러싱 동작 시간 관련
    gStFlushing.mUactHz = 0;
    gStFlushing.mUprogress = 0;  // 진행률 관련
    gStFlushing.CurrentMode = 0;
    gStFlushing.RunStatus = FALSE;
    gStFlushing.PrevRunStatus = FALSE;
    gStFlushing.Pause = FALSE;
    gStFlushing.CancelDisable = FALSE;
}

void SetFlushingConfig( U8 xUflushing )
{
    if( gStFlushing.Config != xUflushing )
    {
        // SaveEepromId(EEPROM_ID_FLUSHING);
    }

    gStFlushing.Config = xUflushing;
}

U8 GetFlushingConfig( void )
{
    return gStFlushing.Config;
}


/**
 * @ brief               Function For Set Flushing Type
 * @ detail              none
 * @ param    xEstatus   Flushing Type ( FIRST, FILTER )
 * @ return              none
**/
void SetFlushingType( EFlushingType_T xUtype )
{
    if( xUtype >= FLUSHING_TYPE_MAX )
    {
        return;
    }

    if( gStFlushing.mEtype != xUtype )
    {
        if( gStFlushing.mEtype != FLUSHING_TYPE_NONE )
        {
            // SaveEepromId(EEPROM_ID_FLUSHING_TYPE);
        }
    }

    gStFlushing.mEtype = xUtype;
}

static void ValveFlushInit(void)
{
    Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, OFF, 0);

    Set_ValveControl(VALVE_ID_AMBIENT_OUT, FEED, CLOSE, 0);
    Set_ValveControl(VALVE_ID_HOT_OUT, FEED, CLOSE, 0);
    Set_ValveControl(VALVE_NOS_ID_HOT_TANK_OVERFLOW, NOS, OPEN, 0);   
    Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, CLOSE, 0);
}

static void ValveHotTankFill(void)
{
    Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, ON, 0);

    Set_ValveControl(VALVE_ID_AMBIENT_OUT, FEED, CLOSE, 0);
    Set_ValveControl(VALVE_ID_HOT_OUT, FEED, CLOSE, 0);
    Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, OPEN, 0);
    Set_ValveControl(VALVE_NOS_ID_HOT_TANK_OVERFLOW, NOS, OPEN, 0);   
}

/**
 * @brief 플러싱(여기선 온수탱크 채우기) 전에 처리해야 할 부분 (부팅음 등)
 */
static U8 DoFilterFlushingInit( U8 *xUptrStep )
{
    switch(*xUptrStep)
    {
        case FLUSH_INIT_SOUND:

            (*xUptrStep)++;
            break;

        case FLUSH_INIT_DONE:
            ValveFlushInit();
            (*xUptrStep) = 0;
            return TRUE;
            break;

        default:
            (*xUptrStep) = 0;
            break;
    }

    SetFlushingStepStatus((*xUptrStep));
    SetFlushingCurrentMode(FLUSH_OUT_INIT);

    return FALSE;
}

/**
 * @brief 온수탱크 채우기 부팅 시 (매번 확인)
 */
static U8 DoFillHot( U8 *xUptrStep )
{
    switch(*xUptrStep)
    {
        case FLUSH_HOT_FILL_EXE_CHECK:
            if(Get_ADC_Data(ADC_ID_TH_HOT_TANK_WATER_LEVEL) < 500)
            // if(WATER_LV_HIGH == LOW)
            {
                // 온수탱크에 물이 가득 차있지 않으면
                (*xUptrStep)++;
            }
            else
            {
                // 온수탱크에 물이 가득 차있으면
                (*xUptrStep) = FLUSH_HOT_FILL_VALVE_CLOSE;
            }
            break;

        case FLUSH_HOT_FILL_EXE:
            if(Get_ADC_Data(ADC_ID_TH_HOT_TANK_WATER_LEVEL) > 500)
            // if(WATER_LV_HIGH == LOW)
            {
                ValveHotTankFill();
            }
            else
            {
                (*xUptrStep)++;
            }
            break;

        case FLUSH_HOT_FILL_VALVE_CLOSE:
            Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, OFF, 0);
            Drv_AllFeedValve_Close();
            Set_ValveControl(VALVE_NOS_ID_HOT_TANK_OVERFLOW, NOS, OPEN, 0);
            (*xUptrStep)++;
            break;

        case FLUSH_HOT_FILL_DONE:

            // 이걸로 완료시킴
            SetFlushOutMode(FLUSH_OUT_DONE);
            (*xUptrStep) = 0;
            return TRUE;
            break;

        default:
            (*xUptrStep) = 0;
            break;
    }

    SetFlushingStepStatus((*xUptrStep));
    SetFlushingCurrentMode(FLUSH_OUT_FILL_HOT);


    return FALSE;
}

static U8 DoDone( U8 *xUptrStep )
{
    SetFlushingStepStatus((*xUptrStep));
    SetFlushingCurrentMode(FLUSH_OUT_DONE);

    CompleteFlushing();

    return TRUE;
}

static void InitOutEventList(void)
{
    U8 uIndex = 0U;

    for( uIndex = 0; uIndex < SZ_FLUSH_OUT_EVENT_LIST; uIndex++ )
    {
        gStOutEventList[uIndex].gu8mUstep = 0U;
    }
}

static void SetFlushingStepStatus(U8 Status)
{
    gStFlushing.StepStatus = Status;
}

static void SetFlushOutMode( U32 xUmode )
{
    gStFlushing.mUmode |= xUmode;
}

static void ClearFlushOutMode( U32 xUmode )
{
    gStFlushing.mUmode &= ~xUmode;
}

static U8 IsSetFlushOutMode( U32 xUmode )
{
    if( (gStFlushing.mUmode & xUmode ) == xUmode )
    {
        return TRUE;
    }

    return FALSE;
}

static U32 GetFlushOutMode( void )
{
    return gStFlushing.mUmode;
}

static void SetFlushingCurrentMode(U32 mu32Val)
{
    gStFlushing.CurrentMode = mu32Val;
}

static void FlushingPause(void)
{
    U32 mu32CurrentMode = 0;

    // StopCheckNeoOutage();      // 단수 검사 중지 
    StopAllFlushingOperation(); // 모든 동작 중지
    InitOutEventList();  // 처음 step부터 다시 시작 (MODE는 이어서 시작 해야함)
}

void TurnOnFlush(void)
{
    gStFlushing.RunStatus = TRUE;
    SetFlushingPause(FALSE);
}

void TurnOffFlush(void)
{
    gStFlushing.RunStatus = FALSE;
  //  SetFlushingPause(TRUE); 살리면 플러싱 완료돼도 pause 가 true 로 잡힘 - CompleteFlushing()
}

void SetFlushingStatus(EFlushingStatus_T Status)
{
    gStFlushing.mEstatus = Status;
}

EFlushingStatus_T GetFlushingStatus( void )
{
    return gStFlushing.mEstatus;
}

void SetFlushingPause(U8 mu8Val)
{
    gStFlushing.Pause = mu8Val;
}

U8 GetFlushingPause(void)
{
    return gStFlushing.Pause;
}

U8 GetFlushingRun(void)
{
    return gStFlushing.RunStatus;
}

EFlushingType_T GetFlushingType( void )
{
    return gStFlushing.mEtype;
}

static U8 IsValidFlushing(void)
{
    /* 플러싱 유무 */
    // if( GetFlushingConfig() == FALSE )
    // {
    //     return FALSE;
    // }

    // /* 탱크 탐 커버 체결 유무 */
    // if( GetCurrentInputVal(INPUT_ID_COLD_TANK_COVER) == OPEN )
    // {
    //     return FALSE;
    // }

    // /* 필터 커버 체결 유무 */
    // if( GetFilterCoverOpenStatus() == OPEN )
    // {
    //     return FALSE;
    // }

    // /* NEO, RO, INNO 필터 체크 */
    // if( GetFilterOpenStatus() == FILTER_OPEN )
    // {
    //     return FALSE;
    // }

    // /* 에러 유무 */
    // if( IsErrorType(ERROR_TYPE_FLUSHING) == TRUE )
    // {
    //     return FALSE;
    // }

    // 상태 체크
    // if( gStFlushing.mEstatus != FLUSHING_STATUS_ING
    //   && gStFlushing.mEstatus != FLUSHING_STATUS_DONE
    //   && gStFlushing.mEstatus != FLUSHING_STATUS_END )
    // {
    //     return FALSE;
    // }    
    
    return TRUE;
}

static void OutFlow(void)
{
    U8 uIndex = 0U;
    U8 uRet = FALSE;
    U8 uStep = 0U;
    U16 uMode = 0U;
    SFlushOutEvent_T *ptrFunList = NULL;

    for( uIndex = 0; uIndex < SZ_FLUSH_OUT_EVENT_LIST; uIndex++ )
    {
        ptrFunList = &gStOutEventList[uIndex];

        if( IsSetFlushOutMode( ptrFunList->gu32Umode ) == TRUE )
        {
            uRet = ptrFunList->mUptrFunAction( &ptrFunList->gu8mUstep );
            
            // UpdateFlushingProgress(); // for display %
            if( uRet == TRUE )
            {
                ClearFlushOutMode( ptrFunList->gu32Umode );
            }
            break;
        }
    }
}

static void ControlWaterFlushOut(void)
{
    if( GetFlushingConfig() == TRUE )
    {
        // 일시정지 -> 다시 시작하면 이어서 시작
        if( GetFlushingPause() == TRUE )
        {
            FlushingPause();
            return;
        }
        
        // if(IsChangedOutStatus() == TRUE )
        // {
        //     if( gStFlushing.RunStatus == FALSE )  // 플러싱 동작 취소  -> 관련 모드 Clear -> 이후 처음부터 다시 플러싱
        //     {
        //         StopFlushOut();
        //         StopCheckNeoOutage();
        //         StopAllFlushingOperation(); // 모든 동작 중지
        //         SetFlushingStatus(FLUSHING_STATUS_WAIT);
        //     }
        // }
    }
    
    if( gStFlushing.RunStatus == TRUE )
    {
        /* 플러싱 중단 시켜야 할 때 */
        if( IsValidFlushing() == FALSE )
        {
            /* 플러싱 중단 -> 처음부터 다시 시작해야함 */
            if( GetFlushingStatus() != FLUSHING_STATUS_NONE )
            {
                TurnOffFlush();
                // dbg_PrevCurrentMode = GetFlushingCurrentMode();
                SetFlushingCurrentMode(0);   // 처음 MODE 부터 다시 시작
                InitOutEventList();          // 처음 step부터 다시 시작
                return;
            }
        }
        /* 플러싱 완료 되면 */
        else if( IsSetFlushOutMode(FLUSH_OUT_DONE) == TRUE )
        {
            gStFlushing.RunStatus = FALSE;
        }

        OutFlow();  // flushing 동작
    }
}


/* 1,3 or 1,2,3 플러싱만 가능 */
static void HandleSetFlushing(void)
{
    EFlushingType_T eFlushType = FLUSHING_TYPE_NONE;

    // /* 구연산 필터 장착 or 구연산 세척 플러싱 중에는 return */
    // if(GetCitricFlushConfig() == TRUE
    //     || IsOpenFilter(FILTER_ID_CITRIC_ACID) == FILTER_CLOSE )
    // {
    //    // ResetFlushing();  // 살리면안됨 -> 최초 전원 인가할때 값을 바로 못읽고 IsOpenFilter(FILTER_ID_CITRIC_ACID) == FILTER_CLOSE 되면서 들어와지기?문
    //     return;
    // }

    if( (GetFlushingRun() == TRUE    // 플러싱 진행 중에는 모드 세팅 되면 안됨(mode가 clear 안되고 계속 같은 모드 반복 되기 때문)
    || GetFlushingPause() == TRUE)   // 플러싱 일시정지 중에는 모드 세팅 되면 안됨(처음부터 다시 다 하기 때문)
    // && (GetFilterReplaceStatus() == FILTER_REPLACE_DONE)           // 필터를 올바르게 교체 안했을때는 return하면 안됨 -> 밑에서 mode 세팅해줘야 해서 
    )
    {
        return;
    }

    // /* 강제 플러싱 모드일 때는 1개의 필터만 교체해도 무조건 123 플러싱 해야함 */
    // if(GetFlushingSkipChangeType() == TRUE)
    // {
    //     if(IsFilterChanged() == TRUE)
    //     {
    //         if( GetFilterStatus( FILTER_ID_COVER_FRONT ) == FILTER_CLOSE )
    //         {
    //             SetFlushOutMode(FLUSH_FILTER_NEO_RO_INNO);
    //             SetFlushingConfig(TRUE);
    //             SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //             SetFilterReplaceStatus(FILTER_REPLACE_DONE);
    //             return;
    //         }
    //     }
    // }

    /* 최초 설치 플러싱 */
    eFlushType = GetFlushingType();
    if( eFlushType == FLUSHING_TYPE_FIRST )  // 최초 제품 설치 시, Flushing mode 세팅 (설치플러싱은 최초에 Config = TRUE,mEstatus = FLUSHING_STATUS_WAIT 때문에 mode만 세팅)
    {
        // if( GetFlushingShort() == TRUE )
        // {
        //     SetFlushOutMode(FLUSH_ALL_INSTALL_FREE);
        //     return;
        // }

        SetFlushOutMode(FLUSH_ALL_INSTALL_FREE);
        // SetFilterReplaceStatus(FILTER_REPLACE_DONE);
    }
    // /* 필터 교체 플러싱 */
    // else if( eFlushType == FLUSHING_TYPE_FILTER )  // 필터 교체 후, 필터 커버 닫으면 Flushing Config,mode,status 세팅 
    // {
    //     if( GetFilterStatus( FILTER_ID_COVER_FRONT ) == FILTER_CLOSE 
    //         && IsFilterChanged() == TRUE ) // 필터교체 도래일 안에 들어올때만 플러싱 세팅
    //     {
    //         if( IsExpiredFilterUsage() == TRUE     // 필터교체 도래일 안에 들어올때만 플러싱 세팅
    //             || GetFlushingSettingBackup() == TRUE) // 필터교체 도래일 안에 플러싱 시작 후 전원재인가 및 에러 발생 후 다시 플러싱 모드 세팅 해줘야할 때
    //         {
    //             /* 1,3 교체 주기에는 1,3 or 1,2,3만 가능(안그러면 추출 불가) */
    //             if( GetFilterChangeType() == FILTER_CHANGE_TYPE_1_3 )
    //             {
    //                 if( GetNeoFilterChangedStatus() == FILTER_CHANGED   
    //                   && GetRoFilterChangedStatus() == FILTER_MOUNTED     
    //                   && GetInnoFilterChangedStatus() == FILTER_CHANGED)
    //                 {
    //                     SetFlushOutMode(FLUSH_FILTER_NEO_INNO);
    //                     SetFlushingConfig(TRUE);
    //                     SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //                     SetFilterReplaceStatus(FILTER_REPLACE_DONE);
    //                 }
    //                 else if( GetNeoFilterChangedStatus() == FILTER_CHANGED
    //                     && GetRoFilterChangedStatus() == FILTER_CHANGED
    //                     && GetInnoFilterChangedStatus() == FILTER_CHANGED )
    //                 {
    //                     SetFlushOutMode(FLUSH_FILTER_NEO_RO_INNO);
    //                     SetFlushingConfig(TRUE);
    //                     SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //                     SetFilterReplaceStatus(FILTER_REPLACE_DONE);
    //                 }
    //                 /* 그외에 필터교체 잘못 하면 */
    //                 else
    //                 {
    //                     SetFlushingConfig(TRUE);
    //                     SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //                     SetFilterReplaceStatus(FILTER_REPLACE_NEED);
    //                 }
    //             }
    //             /* 1,2,3 교체주기 일때는 1,2,3 플러싱만 가능(안그러면 추출 불가) */
    //             else
    //             {
    //                 if( GetNeoFilterChangedStatus() == FILTER_CHANGED
    //                   && GetRoFilterChangedStatus() == FILTER_CHANGED
    //                   && GetInnoFilterChangedStatus() == FILTER_CHANGED )
    //                 {
    //                     SetFlushOutMode(FLUSH_FILTER_NEO_RO_INNO);
    //                     SetFlushingConfig(TRUE);
    //                     SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //                     SetFilterReplaceStatus(FILTER_REPLACE_DONE);
    //                 }
    //                 /* 그외에 필터교체 잘못 하면 */
    //                 else
    //                 {
    //                     SetFlushingConfig(TRUE);
    //                     SetFlushingStatus(FLUSHING_STATUS_WAIT);
    //                     SetFilterReplaceStatus(FILTER_REPLACE_NEED);
    //                 }
    //             }
    //         }
    //     }
    // }
}

// @100ms )
static void FlushingActTimeCounter(void)
{
    if( gStFlushing.Pause == TRUE 
    || gStFlushing.RunStatus == FALSE )
    {
        return;
    }

    if(gStFlushing.mUactTime)
    {
        gStFlushing.mUactTime--;
    }
}

void StopAllFlushingOperation(void)
{
    ValveFlushInit();
    // TurnOffDrainPump();
    // SetValveQueue(VALVE_CMD_BOOST_PUMP_OFF);  
    // SetValveQueue(VALVE_CMD_FEED_CLOSE);
    // SetValveQueue(VALVE_CMD_ROOM_IN_CLOSE); 
    // SetValveQueue(VALVE_CMD_HOT_DRAIN_CLOSE); 
    // SetValveQueue(VALVE_CMD_AIR_CLOSE); 
    // SetValveQueue(VALVE_CMD_COLD_DRAIN_CLOSE); 
    // SetValveQueue(VALVE_CMD_WATER_FLOW_CYCLE_CLOSE); 
    // SetValveQueue(VALVE_CMD_FLUSHING_FEED_CLOSE); 
    // SetValveQueue(VALVE_CMD_AUTO_FLUSHING_CLOSE); 
    // SetValveQueue(VALVE_CMD_UTILITY_WATER_CLOSE); 
}


/**
 * @brief First Setup Flsuhing Or Fiter Change Flushing, @100ms
 */
void ProcessWaterFlushing(void)
{
    HandleSetFlushing();       // 설치플러싱, 필터 교체 플러싱 mode,config Set
    ControlWaterFlushOut();    // 플러싱 동작
    FlushingActTimeCounter();  // Flushing Act Timer Count
}