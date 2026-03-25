#include "Global_Header.h"
#include "hw.h"
#include "key.h"

#include <string.h>


/**
 * @brief 키 입력 판단에 대한 전체 로직 구조체
 * 
 */
typedef struct _key_
{
    KeyStatus_T   Status;  

    U16  Val;           // PUSH KEY VAL
    U16  ValPop;        // POP KEY VAL
    U16  PushedTime;    // PUSH TIME...
    U8   EventFlag;     // Event Flag..

} Key_T;

Key_T   Key;


void InitKey(void)
{
    memset( &Key, 0, sizeof( Key ) );
}

U8 GetKeyStatus( void )
{
    return Key.Status;
}

U16 GetKeyPushedTime( void )
{
    return Key.PushedTime;
}

U16 GetKeyVal( void )
{
    return Key.Val;
}

U16 GetKeyPopVal(void)
{
    return Key.ValPop;
}

void SetKeyEventFlag(U8 mu8Event )
{
    Key.EventFlag |= mu8Event;
}

void ClearKeyEventFlag(U8 mu8Event )
{
    Key.EventFlag &= ~mu8Event;
}

U8 IsSetKeyEventFlag( U8 mu8Event )
{
    if( (Key.EventFlag & mu8Event) ==  mu8Event )
    {
        return TRUE;
    }

    return FALSE;
}

/**
 * @brief 키 상세 이벤트에 대한 테이블 구조체
 * 
 */
typedef struct _KeyEvent_
{
    U16 u16EventTime;
    U8  u8Event;
} KeyEvent_T;

/**
 * @brief 키 상세 이벤트 처리 구조체
 * 
 */
const static KeyEvent_T KeyEventList[] = 
{
    { EVENT_TIME_OUT_7S,    KEY_EVENT_PUSHED_LONG_7S },
    //{ EVENT_TIME_OUT_5S,    KEY_EVENT_PUSHED_LONG_5S },
    { EVENT_TIME_OUT_3S,    KEY_EVENT_PUSHED_LONG_3S },
    { EVENT_TIME_OUT_2S,    KEY_EVENT_PUSHED_LONG_2S },
    { EVENT_TIME_OUT_1S,    KEY_EVENT_PUSHED_LONG_1S },
    { EVENT_TIME_OUT_SHORT, KEY_EVENT_PUSHED_SHORT },

};
#define SZ_KEY_EVENT_LIST   (sizeof(KeyEventList)/sizeof(KeyEvent_T))

/**
 * @brief 실제 눌린시간과 등록된 이벤트의 시간이 같으면 event 플래그 set함
 * 
 * @param mu16PushedTime 
 */
static void FindSetKeyEvent(U16 mu16PushedTime)
{
    U8 mu8Index;

    for( mu8Index = 0; mu8Index < SZ_KEY_EVENT_LIST ; mu8Index++ )
    {
        if( KeyEventList[ mu8Index ].u16EventTime == mu16PushedTime )
        {
            SetKeyEventFlag( KeyEventList[ mu8Index ].u8Event );
            return ;
        } 
    }
}

static void ParseKeyVal(void)
{
    U32 mu32KeyVal = HAL_KEY_NONE;

    if( KEY_HOT     == LOW ) { mu32KeyVal |= K_HOT;             }
    if( KEY_AMBIENT == LOW ) { mu32KeyVal |= K_ROOM;            }
    if( KEY_EXTRACT == LOW ) { mu32KeyVal |= HAL_KEY_WATER_OUT; }
    if( KEY_AMOUNT  == LOW ) { mu32KeyVal |= K_AMOUNT;          }
    if( KEY_LOCK    == LOW ) { mu32KeyVal |= K_HOT_LOCK;        }

    HAL_SetKeyVal( mu32KeyVal );
}

void ProcessScanKey(void)
{
    static U16 mu16PrevKeyVal;
    U16  mu16KeyVal;

    // 1. Parse Key Value
    ParseKeyVal();

    // 2. Get Key value
    mu16KeyVal = HAL_GetKeyVal();
    if( mu16PrevKeyVal != mu16KeyVal )
    {  
        /* Prevent - while pushing one, push the other */
        if( mu16KeyVal != HAL_KEY_NONE && mu16PrevKeyVal != HAL_KEY_NONE)
        {			
            Key.Status = KEY_STATUS_NONE;
            Key.PushedTime = 0;  

            return;
        }
    	
        if( mu16KeyVal == HAL_KEY_NONE )
        {
            Key.ValPop      = mu16PrevKeyVal;
        }
	
        mu16PrevKeyVal  = mu16KeyVal;
        Key.Val         = mu16KeyVal;  
			
        if( mu16KeyVal != HAL_KEY_NONE )
        {
            Key.Status        = KEY_STATUS_PUSHED;
            Key.PushedTime    = 0;  
            ClearKeyEventFlag( KEY_EVENT_ALL );
        }
        else 
        {
            if( Key.PushedTime > EVENT_TIME_OUT_SHORT )
            {
                Key.Status = KEY_STATUS_POP;
                SetKeyEventFlag( KEY_EVENT_POP );
            }
            else
            {
                Key.Status = KEY_STATUS_NONE;
            }
        }
    }
    
    if( Key.Status == KEY_STATUS_PUSHED )
    {
        Key.PushedTime++;
        FindSetKeyEvent( Key.PushedTime );

        if( Key.PushedTime > MAX_EVENT_TIME_OUT )
        {
            Key.Status = KEY_STATUS_TIME_OUT;
        }
    }
}

