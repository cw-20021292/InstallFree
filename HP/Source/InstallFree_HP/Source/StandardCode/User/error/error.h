#ifndef __ERROR_H__
#define __ERROR_H__

/* Error Id List
 *
 * Top - Low priority for error display 
 * Bottom - Top Priority for error dispaly
 */
typedef enum _error_id_
{
    ERR_NONE,

    ERR_ID_COLD_COMPLEX_LOWMIDE,    /* low non, mide non, high detected */
    ERR_ID_COLD_HIGH_LEVEL,         /* Cold Tank - high */
    ERR_ID_COLD_MIDE_LEVEL,         /* Cold Tank - mide */ 
    ERR_ID_COLD_LOW_LEVEL,          /* Cold Tank - low */
    ERR_ID_COLD_FEED,               /* feed valve */

    ERR_ID_ROOM_HIGH_LEVEL,         /* Room Tank - high */
    ERR_ID_ROOM_LOW_LEVEL,          /* Room Tank - low */
    ERR_ID_ROOM_FEED,               /* feed valve */
    
	ERR_ID_HOT_HIGH_LEVEL,          /* Hot Tank - high */

    ERR_ID_TEMP_COLD_WATER,
    ERR_ID_TEMP_HOT_WATER,

    ERR_ID_OUTAGE_WATER,          
    ERR_ID_OUTAGE_WATER_DRAIN,      
    ERR_ID_OUTAGE_WATER_OUT,        

    ERR_ID_FLOW_METER_NEO,      
    ERR_ID_FLOW_METER_INNO,         

    ERR_ID_BOOST_PUMP,      
    ERR_ID_DRAIN_PUMP,
    ERR_ID_CIRCULATE_PUMP,
    
    ERR_ID_TEMP_AMBIENT,
    ERR_ID_LEAK,

    ERR_NUM              
} ErrorId_T;  // 에러 중 큰 카테고리에 속해있는 작은 에러들의 카테고리

typedef enum _error_type_
{
    ERROR_TYPE_NONE = 0,  
    ERROR_TYPE_FLUSHING,     
    ERROR_TYPE_COLD_MAKE, 
    ERROR_TYPE_HOT_MAKE,   
    ERROR_TYPE_CITRIC_ACID_STER,
    ERR_TYPE_ROOM_WATER_OUT,

    ERROR_TYPE_MAX,     
} EErrorType_T;    // 에러 중 큰 카테고리 

/* ERROR ISSUED DATE */
typedef struct _error_date_
{
    U16 u16Year;
    U8 u8Month;
    U8 u8Date;
} ErrorDate_T;

typedef struct _memento_
{
    ErrorId_T   Error;
    ErrorDate_T Date;
} Memento_T;

/* ERROR TYPE */
#define  MEMENTO_LIST_NUM   5
typedef struct _error_
{
    ErrorId_T PrevErrorId;    /* Previous ERROR STATUS */
    ErrorId_T ErrorId;        /* Current ERROR STATUS */
    ErrorDate_T ErrorDate;    /* Current ERROR ISSUED DATE */

    U8 Status[ ERR_NUM ];     /* TRUE : ERROR, FALSE : NORMAL */
    ErrorDate_T StatusDate[ ERR_NUM ];

    /* Memento */
    //ErrorId_T MementoList[ MEMENTO_LIST_NUM ];  
    Memento_T MementoList[ MEMENTO_LIST_NUM ];  
}Error_T;


void InitError(void);

void GetErrorData(Error_T *pData);

void SetErrorStatus(ErrorId_T mId, U8 mu8Status);
void SetErrorStatusDate(ErrorId_T mId, U8 mu8Status, ErrorDate_T *pDate);

U8 GetErrorStatus(ErrorId_T mId);
void GetErrorStatusDate(ErrorId_T mId, ErrorDate_T *pDate);

ErrorId_T GetErrorId(void);
void SetErrorId(ErrorId_T mErrId);
U8   GetErrorDisplayId(ErrorId_T mErrId);
void GetErrorDate(ErrorDate_T *pDate);


U8 IsEmptyMementoError(void);
U8 GetMementoError(U8 mu8Index, Memento_T *pMemento);
void SetMementoError(U8 mu8Index, ErrorId_T mError, ErrorDate_T *pDate );
void ClearMementoError(void);

U8 IsErrorType( EErrorType_T xEtype );
U8 IsError(ErrorId_T mId );
U8 IsErrorTypeNosFeed(void);
U8 IsErrorTypeRoomTankNosFeed(void);
U8 IsErrorTypeColdTankNosFeed(void);
U8 IsErrorTypeColdWater(void);
U8 IsErrorTypeHotWater(void);
U8 IsErrorTypeDrainWater(void);


void UpdateNewError(U8 mu8Error);

#endif /* _ERROR_H__ */