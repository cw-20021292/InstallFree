#include "Global_Header.h"

#include "error.h"
#include "process_error.h"


typedef U8 (*ErrFun_T)(U8 mu8Error);
typedef struct _error_list_
{
    ErrorId_T Id;           
    U8 PrevError;           
    U8 Error;              
    U8 SterActive;          
    U8 DispActive;      // ���� ������ �ϵ�, Display ���� 
    U8 CHPActive;       // CHP MODEL ?�??( TRUE?�면, CHP ?�??)


    ErrFun_T Check;         
    ErrFun_T Release;       
} ErrorList_T;

void InitErrorList(void)
{
    InitError();
}

static U8 ReleaseErrColdFeedEx(U8 mu8Error);
static U8 ReleaseErrColdHighEx(U8 mu8Error);
static U8 ReleaseErrColdMideEx(U8 mu8Error);
static U8 ReleaseErrColdLowEx(U8 mu8Error);

static U8 ReleaseErrRoomFeedEx(U8 mu8Error);
static U8 ReleaseErrRoomHighEx(U8 mu8Error);
static U8 ReleaseErrRoomLowEx(U8 mu8Error);


// �Ϲ� ���� ���ǿ��� ���� ����
ErrorList_T ErrList[] = 
{
                 /* ID                            PrevError Error   Ster       Disp     CHP(ONLY)    Check error                 Check release error */
	            //{ ERR_OVER_HOT_WATER,           FALSE,    FALSE,  FALSE,     TRUE,     TRUE,       CheckErrOverHotWater,        ReleaseErrOverHotWater },
                //{ ERR_ID_OUTAGE_WATER_DRAIN,    FALSE,    FALSE,  TRUE,      FALSE,    FALSE,      CheckErrorOutageDrainWater,  ReleaseErrorOutageDrainWater  }, 
                //{ ERR_ID_OUTAGE_WATER_OUT,      FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorOutageOutWater,    ReleaseErrorOutageOutWater    },    
                //{ ERR_ID_FLOW_METER_INNO,       FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorFlowMeterInno,     ReleaseErrorFlowMeterInno     }, 
// /* Priority 17 */ { ERR_ID_CIRCULATE_PUMP,        FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrCirculatePump,       ReleaseErrCirculatePump       }, 
// /* Priority 16 */ { ERR_ID_DRAIN_PUMP,            FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorDrainPump,         ReleaseErrorDrainPump         },     
// /* Priority 15 */ { ERR_ID_TEMP_AMBIENT,          FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrTempAmbient,         ReleaseErrTempAmbient         }, 
// /* Priority 14 */ { ERR_ID_TEMP_COLD_WATER,       FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrTempColdWater,       ReleaseErrTempColdWater       },  
/* Priority 13 */ { ERR_ID_TEMP_HOT_WATER,        FALSE,    FALSE,  FALSE,     TRUE,     TRUE,       NULL,        NULL        },  
/* Priority 12 */// { ERR_ID_COLD_COMPLEX_LOWMIDE,  FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrColdComplexLowMide,  ReleaseErrColdComplexLowMide  },  
/* Priority 11 */// { ERR_ID_COLD_FEED,             FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrColdFeed,            NULL                          },   // There is no release error   
/* Priority 10 */// { ERR_ID_COLD_HIGH_LEVEL,       FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrColdHigh,            ReleaseErrColdHigh            },   
/* Priority 9  */// { ERR_ID_COLD_MIDE_LEVEL,       FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrColdMide,            ReleaseErrColdMide            },   
// /* Priority 8  */ { ERR_ID_COLD_LOW_LEVEL,        FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrColdLow,             ReleaseErrColdLow             },    
// /* Priority 7  */ { ERR_ID_HOT_HIGH_LEVEL,        FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrHotHigh,             ReleaseErrHotHigh             },   // There is no release error  
// /* Priority 6  */// { ERR_ID_ROOM_FEED,             FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrRoomFeed,            NULL                          },   // There is no release error  
// /* Priority 5  */ { ERR_ID_ROOM_HIGH_LEVEL,       FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrRoomHigh,            ReleaseErrRoomHigh            },      
// /* Priority 4  */ { ERR_ID_ROOM_LOW_LEVEL,        FALSE,    FALSE,  FALSE,     TRUE,     FALSE,      CheckErrRoomLow,             ReleaseErrRoomLow             },   
// /* Priority 3  */ //{ ERR_ID_BOOST_PUMP,            FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorBoostPump,         ReleaseErrorBoostPump         },     
//                   //{ ERR_ID_FLOW_METER_NEO,        FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorFlowMeterNeo,      ReleaseErrorFlowMeterNeo      }, 
// /* Priority 2  */ { ERR_ID_OUTAGE_WATER,          FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrorOutageWater,       ReleaseErrorOutageWater       }, 
// /* Priority 1  */ { ERR_ID_LEAK,                  FALSE,    FALSE,  TRUE,      TRUE,     FALSE,      CheckErrLeak,                ReleaseErrLeak                },   
};
#define  SZ_ERR_LIST      (sizeof(ErrList)/sizeof(ErrorList_T))

#if 0
U8 dbgIotErr = 0U;
static ErrorId_T FindCheckError(  ErrorList_T *pErrList, U16 mu16Size )
{
    U8 i;
    ErrFun_T pCheck;
    ErrFun_T pRelease;
    ErrorId_T mId = ERR_NONE;
    ErrorId_T mNewId = ERR_NONE;
    U8 mu8Error = FALSE;
    ErrorDate_T mDate;
    ErrorList_T *pList = NULL;
    U8 mu8IsChangedErrorStatus = FALSE;


    GetErrorDate( &mDate );
    for( i = 0; i < mu16Size; i++ ) 
    {
        pList = (pErrList + i );

        // Mapping error status..
        mId      = pList->Id;
        mu8Error = pList->Error;
        pCheck   = pList->Check;
        pRelease = pList->Release;

#if CONFIG_STER
        if( IsStartSter() == TRUE )
        {
            if( pList->SterActive == FALSE )
            {
                continue;
            }
        }
#endif

        if( GetSystem() == SYSTEM_CP )
        {
            if( pList->CHPActive == TRUE )
            {
                continue;
            }
        }


        if( mu8Error == TRUE )
        {
#if CONFIG_STER
            if( GetSterErrWaterOut() == FALSE )
#endif
            {
                if( pRelease != NULL )
                {
                    mu8Error = pRelease( mu8Error );
                }
            }
        }
        else
        {
            if( pCheck != NULL )
            {
                mu8Error = pCheck( mu8Error );
            }
        }

        // Update new error status
        if( pList->PrevError != mu8Error )
        {
            pList->PrevError = pList->Error;
            pList->Error = mu8Error;

            //SetErrorStatus( mId, pList->Error );
            /* If an error occurred, set the error that occurred */
            SetErrorStatusDate( mId, pList->Error, &mDate );

            // WIFI (ȭ�鿡 ǥ�õǴ� ������ ������ ���� )
            if( pList->DispActive == TRUE )
            {
               mu8IsChangedErrorStatus = TRUE; 
            }
        }

        if( pList->DispActive == TRUE )
        {
            //  Top priority Error
            if( GetErrorStatus( mId ) == TRUE )
            {
                mNewId = mId;
            }
        }

    }

    // WIFI 
    if( mu8IsChangedErrorStatus == TRUE )
    {
        WifiSendData(WIFI_DATA_ERROR);
        dbgIotErr++;
    }

    return mNewId;
}


void ProcessError(void)
{
#if CONFIG_ERR_ALL
    ErrorId_T mNewId = ERR_NONE;

    // Check Error
    mNewId = FindCheckError( &ErrList[0], SZ_ERR_LIST );

    // Update New Error Id
    UpdateNewError( mNewId );
#endif  // CONFIG_ERR_ALL
}


static U8 ReleaseErrColdFeedEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;
    }

    return ReleaseErrColdFeed( mu8Error );
}

static U8 ReleaseErrColdHighEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;
    }

    return ReleaseErrColdHigh( mu8Error );
}

static U8 ReleaseErrColdMideEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;
    }

    return ReleaseErrColdMide( mu8Error );
}

static U8 ReleaseErrColdLowEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;    
    }

    return ReleaseErrColdLow( mu8Error );
}


static U8 ReleaseErrRoomFeedEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;
    }

    return ReleaseErrRoomFeed( mu8Error );
}

static U8 ReleaseErrRoomHighEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;
    }

    return ReleaseErrRoomHigh( mu8Error );
}

static U8 ReleaseErrRoomLowEx(U8 mu8Error)
{
    if( GetTimeShortStatus() == FALSE )
    {
        return mu8Error;    
    }

    return ReleaseErrRoomLow( mu8Error );
}
#endif
