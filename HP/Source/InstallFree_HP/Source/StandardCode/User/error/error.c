#include "Global_Header.h"

#include "error.h"

Error_T  Err;

void InitError(void)
{
    memset( &Err, 0, sizeof( Error_T ));
}

void GetErrorData(Error_T *pData)
{
    memcpy( pData, &Err, sizeof( Error_T));
}

void SetErrorStatus(ErrorId_T mId, U8 mu8Status)
{
    if( mId < ERR_NUM ) 
    {
        Err.Status[ mId ] = mu8Status;
    }
}

/* If an error occurred, set the error that occurred */
void SetErrorStatusDate(ErrorId_T mId, U8 mu8Status, ErrorDate_T *pDate)
{
    if( mId < ERR_NUM ) 
    {
        Err.Status[ mId ] = mu8Status;
        memcpy( &Err.StatusDate[ mId ], pDate, sizeof( ErrorDate_T ));
    }
}

U8 GetErrorStatus(ErrorId_T mId)
{
    return Err.Status[ mId ];
}

void GetErrorStatusDate(ErrorId_T mId, ErrorDate_T *pDate)
{
    if( mId < ERR_NUM ) 
    {
        memcpy(  pDate, &Err.StatusDate[ mId ], sizeof( ErrorDate_T ));
    }
}

U8 IsError(ErrorId_T mId )
{
    return Err.Status[ mId ];
}

ErrorId_T GetErrorId(void)
{
    return Err.ErrorId;
}

void SetErrorId(ErrorId_T mErrId)
{
    Err.ErrorId = mErrId;
}
#if 0

U8  GetErrorDisplayId(ErrorId_T mErrId)
{
    U8 mu8ErrorCode = 0;

#if 0
    switch( mErrId )
    {
        case ERR_ROOM_LOW_LEVEL:        mu8ErrorCode = 11; break;
        case ERR_ROOM_HIGH_LEVEL:       mu8ErrorCode = 13; break;
        case ERR_ROOM_COMPLEX:          mu8ErrorCode = 14; break;
        case ERR_ROOM_OVF:              mu8ErrorCode = 10; break;
        case ERR_LEAK:                  mu8ErrorCode = 1; break;
        case ERR_TEMP_COLD_WATER:       mu8ErrorCode = 44; break;
        case ERR_TEMP_ROOM_WATER:       mu8ErrorCode = 42; break;
        case ERR_TEMP_AMBIENT:          mu8ErrorCode = 43; break;

        case ERR_DRAIN_PUMP:            mu8ErrorCode = 60; break;
        case ERR_TEMP_EVA_2:            mu8ErrorCode = 63; break;
        case ERR_TEMP_EVA_1:            mu8ErrorCode = 63; break;
        case ERR_COLD_LOW_LEVEL:        mu8ErrorCode = 20; break;
        case ERR_SODA_PUMP:             mu8ErrorCode = 94; break;
        case ERR_MICRO_SW_DETECT:       mu8ErrorCode = 61; break;
        case ERR_MICRO_SW_MOVE:         mu8ErrorCode = 62; break;

        //case ERR_COMM_FRONT_DISPLAY:    mu8ErrorCode = 11; break;
        //case ERR_COMM_LCD:              mu8ErrorCode = 11; break;
        default:                        mu8ErrorCode = 0; break;
                                        
    }

#endif
    return mu8ErrorCode;
}

void GetErrorDate(ErrorDate_T *pDate)
{
#if 0
    TimeData_T mTime;

    if( pDate != NULL )
    {
        GetRtcTime( &mTime );

        pDate->u16Year = mTime.Year + 2000;
        pDate->u8Month = mTime.Month;
        pDate->u8Date = mTime.Date;
    }
#endif
}

U8 IsEmptyMementoError(void)
{
    U8 mu8Num;
    Memento_T mMemento;

    mu8Num = MEMENTO_LIST_NUM - 1;
    GetMementoError( mu8Num, &mMemento );
    if( mMemento.Error == ERR_NONE )
    {
        return TRUE;
    }

    return FALSE;
}

U8	GetMementoError(U8 mu8Index, Memento_T *pMemento)
{
    if( mu8Index < MEMENTO_LIST_NUM )
    {
        memcpy( pMemento, &Err.MementoList[ mu8Index ], sizeof( Memento_T ));
        return TRUE;
    }

    return FALSE;
}

void	SetMementoError(U8 mu8Index, ErrorId_T mError, ErrorDate_T *pDate )
{
    if( mu8Index >= MEMENTO_LIST_NUM )
    {
        return ;
    }

    if( mError >= ERR_NUM )
    {
        return ;
    }

    Err.MementoList[ mu8Index ].Error = mError;
    memcpy( &Err.MementoList[ mu8Index ].Date, pDate, sizeof( ErrorDate_T ));
}

void ClearMementoError(void)
{
    U8 i;
    ErrorDate_T mDate;

    memset( &mDate, 0, sizeof( ErrorDate_T ));
    for( i = 0; i < MEMENTO_LIST_NUM ; i++ )
    {
        SetMementoError( i, ERR_NONE, &mDate );
        SaveEepromId( EEPROM_ID_MEMENTO_1 );
        SaveEepromId( EEPROM_ID_MEMENTO_2 );
        SaveEepromId( EEPROM_ID_MEMENTO_3 );
        SaveEepromId( EEPROM_ID_MEMENTO_4 );
        SaveEepromId( EEPROM_ID_MEMENTO_5 );
    }
}

static void UpdateMementoError( Memento_T *pMemento )
{
    if( pMemento->Error != ERR_NONE )
    {
        /* If the previous error and the current error are the same, it is not added to the memento list. */
        if( Err.MementoList[ MEMENTO_LIST_NUM - 1 ].Error != pMemento->Error )
        {
        
            // MementoList[ 0 ] is the last error
            // MementoList[ MEMENTO_LIST_NUM - 1 ] is the most recent error
            memcpy( &Err.MementoList[ 0 ], &Err.MementoList[1], sizeof( Memento_T ) * (MEMENTO_LIST_NUM - 1) ); 
            memcpy( &Err.MementoList[ MEMENTO_LIST_NUM - 1 ], pMemento, sizeof( Memento_T ) );

            SaveEepromId( EEPROM_ID_MEMENTO_1 );
            SaveEepromId( EEPROM_ID_MEMENTO_2 );
            SaveEepromId( EEPROM_ID_MEMENTO_3 );
            SaveEepromId( EEPROM_ID_MEMENTO_4 );
            SaveEepromId( EEPROM_ID_MEMENTO_5 );
        }
    }
}

U8 IsErrorTypeRoomTankNosFeed(void)
{
    if( IsError( ERR_ID_ROOM_LOW_LEVEL ) == TRUE 
         || IsError( ERR_ID_ROOM_HIGH_LEVEL ) == TRUE
           || IsError( ERR_ID_HOT_HIGH_LEVEL ) == TRUE )
            // || IsError( ERR_ID_ROOM_FEED ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}


U8 IsErrorTypeColdTankNosFeed(void)
{
    if( IsError( ERR_ID_COLD_LOW_LEVEL ) == TRUE )
       // || IsError( ERR_ID_COLD_FEED ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}

/* Stop making cold water when an error occurs */
U8 IsErrorTypeColdWater(void)
{
    if( GetTimeShortStatus() == FALSE )
    {
        if( IsErrorTypeColdTankNosFeed() == TRUE )
        {
            return TRUE;
        }
    }

    if( IsError( ERR_ID_TEMP_COLD_WATER ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}


U8 IsErrorTypeHotWater(void)
{
    if( GetTimeShortStatus() == FALSE )
    {
        if( IsErrorTypeRoomTankNosFeed() == TRUE )  // Room Tank = Hot Input Buffer Tank
        {
            return TRUE;
        }
    }

    if( IsError( ERR_ID_TEMP_HOT_WATER ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}



/**
 * @ brief            Function For Check Error For Stop Water Out
 * @ detail           ����, �ܼ�, ����� ����
 * @ param            none
 * @ return           TRUE : Error, False : None
**/
static U8 IsErrorWaterOut(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_OUTAGE_WATER_OUT ) == TRUE
        || IsError( ERR_ID_FLOW_METER_NEO ) == TRUE
        || IsError( ERR_ID_FLOW_METER_INNO ) == TRUE
        || IsError( ERR_ID_BOOST_PUMP ) == TRUE
        )
    {
        return TRUE;
    }

    return FALSE;    
}

/**
 * @ brief            Function For Check Error For Stop Flushing
 * @ detail           ����, �ܼ�, ����� ����
 * @ param            none
 * @ return           TRUE : Error, False : None
**/
static U8 IsErrorFlushing(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_OUTAGE_WATER ) == TRUE
        || IsError( ERR_ID_DRAIN_PUMP ) == TRUE
        || IsError( ERR_ID_ROOM_LOW_LEVEL ) == TRUE
        || IsError( ERR_ID_ROOM_HIGH_LEVEL ) == TRUE
        || IsError( ERR_ID_HOT_HIGH_LEVEL ) == TRUE
        || IsError( ERR_ID_COLD_LOW_LEVEL ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}

static U8 IsErrorBlueE(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_OUTAGE_WATER_DRAIN ) == TRUE
        || IsError( ERR_ID_BOOST_PUMP ) == TRUE
        )
    {
        return TRUE;
    }

    return FALSE;
}

static U8 IsErrorTankIn(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_OUTAGE_WATER ) == TRUE
        || IsError( ERR_ID_BOOST_PUMP ) == TRUE
        )
    {
        return TRUE;
    }

    return FALSE;
}

static U8 IsErrorColdMake(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_TEMP_COLD_WATER ) == TRUE
        )
    {
        return TRUE;
    }

    return FALSE;
}

static U8 IsErrorHotMake(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_TEMP_HOT_WATER ) == TRUE
        )
    {
        return TRUE;
    }

    return FALSE;
}

/* ���� �ʾ��� (�켱 �÷����̶� �Ȱ��� �س�)*/
static U8 IsErrorCitricAcidSter(void)
{
    if( IsError( ERR_ID_LEAK ) == TRUE
        || IsError( ERR_ID_OUTAGE_WATER ) == TRUE
        || IsError( ERR_ID_BOOST_PUMP ) == TRUE
        || IsError( ERR_ID_DRAIN_PUMP ) == TRUE
        || IsError( ERR_ID_ROOM_LOW_LEVEL ) == TRUE
        || IsError( ERR_ID_ROOM_HIGH_LEVEL ) == TRUE
        || IsError( ERR_ID_HOT_HIGH_LEVEL ) == TRUE
        || IsError( ERR_ID_COLD_LOW_LEVEL ) == TRUE )
    {
        return TRUE;
    }

    return FALSE;
}

static void SoundError( U8 mu8Error )
{
    switch( mu8Error )
    {
        case ERR_ID_LEAK :
            // ���� ���� ����
            // Sound(SOUND_ID_ERROR_LEAK);
            break;

        case ERR_ID_OUTAGE_WATER :
            // �ܼ� ���� ����
            // Sound(SOUND_ID_ERROR_OUTAGE);
            break;    
        
        /*
        case ERR_ID_OUTAGE_WATER_OUT  :
            // �ܼ� ���� ����
            Sound(SOUND_ID_ERROR_OUTAGE);
            break;
        */

        case ERR_ID_TEMP_COLD_WATER :
            // �ü� ���� ����
            // Sound(SOUND_ID_ERROR_COLD);
            break;

        case ERR_ID_TEMP_HOT_WATER :
            // �¼� ���� ����
            Sound(BUZZER_ERROR);
            break;

        default :        
            break;
    }
}


void UpdateNewError(U8 mu8Error)
{
    Memento_T mMemento;

#if 0
    // EVA error Skip
    if( mu8Error == ERR_TEMP_EVA_1 
            || mu8Error == ERR_TEMP_EVA_2 )
    {
        return ;
    }
#endif

    if( Err.ErrorId != mu8Error ) 
    {
        Err.PrevErrorId = Err.ErrorId;

        mMemento.Error = mu8Error;
        GetErrorStatusDate( mMemento.Error, &mMemento.Date );

        UpdateMementoError( &mMemento );
                
        SoundError( mu8Error );
    }

    Err.ErrorId = mu8Error;
}

U8 IsErrorType( EErrorType_T xEtype )
{
    U8 uIsError = FALSE;
    
    switch( xEtype )
    {
        case ERROR_TYPE_FLUSHING :
        uIsError = IsErrorFlushing();
        break;
        
        case ERROR_TYPE_COLD_MAKE :
        uIsError = IsErrorColdMake();
        break;
        
        case ERROR_TYPE_HOT_MAKE :
        uIsError = IsErrorHotMake();
        break;
        
        case ERROR_TYPE_CITRIC_ACID_STER :
        uIsError = IsErrorCitricAcidSter();
        break;
        
        default :
        break;
    }
    
    return uIsError;
}

#endif
