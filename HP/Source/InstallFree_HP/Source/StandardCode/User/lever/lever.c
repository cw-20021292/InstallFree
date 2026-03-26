#include "Global_Header.h"

#include "hal_key.h"
#include "lever.h"

#include <string.h>

U32 gu32KeyOut  = 0UL;       
#define  DEFAULT_COUNT      50

#define  HAL_KEY_PUSHED     LOW
#define  HAL_LEVER_PUSHED   LOW

/* Status */
#define  LEVER_STATUS_NONE            0      
#define  LEVER_STATUS_PUSHED          1
#define  LEVER_STATUS_POP             2
#define  LEVER_STATUS_TIME_OUT        3


/* Event Timeout condition */
#define  EVENT_TIME_OUT_8S_WATEROUT         800      // 8sec
#define  EVENT_TIME_OUT_2S_WATEROUT         200      // 2sec
#define  EVENT_TIME_OUT_SHORT_WATEROUT       10      // 100ms

typedef struct _key_
{
    U16  Val;           // PUSH LEVER VAL
    U16  ValPop;        // PUSH LEVER VAL
    U8   Status;        // PUSH or POP
    U16  PushedTime;    // PUSH TIME...
    U8   EventFlag;     // Event Flag..
} Lever_T;

Lever_T   Lever[ MAX_LEVER_ID ];


void InitLever(void)
{
    memset( &Lever, 0, sizeof( Lever ) );
}

U16 GetLeverVal(U8 mu8Id )
{
    return Lever[ mu8Id ].Val;
}

U16 GetLeverPopVal(U8 mu8Id )
{
    return Lever[ mu8Id ].ValPop;
}

void SetLeverEventFlag(U8 mu8Id, U8 mu8Event )
{
    Lever[ mu8Id ].EventFlag |= mu8Event;
}

void ClearLeverEventFlag(U8 mu8Id, U8 mu8Event )
{
    Lever[ mu8Id ].EventFlag &= ~mu8Event;
}

U8 IsSetLeverEventFlag(U8 mu8Id, U8 mu8Event )
{
    if( (Lever[ mu8Id ].EventFlag & mu8Event) ==  mu8Event )
    {
        return TRUE;
    }

    return FALSE;
}

#if 0
//������ ���ο� �޷� ���� �� ���
static void ScanKeyOut(void)
{
    static U16 mu16Count = 0;
    static U32 mu32PrevVal = 0;
    U32 mu32Val = 0;


    // SCAN KEY
    if( P_KEY_LEVER_RIGHT == HAL_LEVER_PUSHED )
    {
        mu32Val |= HAL_KEY_6;
    }
    if( P_KEY_LEVER_LEFT == HAL_LEVER_PUSHED )
    {
        mu32Val |= HAL_KEY_7;
    }


    // RESET KEY COUNT
    if( mu32PrevVal != mu32Val )
    {
        mu32PrevVal = mu32Val;
        mu16Count = DEFAULT_COUNT;

        return ;
    }

    if( mu16Count != 0 )
    {
        mu16Count--;
        return ;
    }

    // UPDATE NEW KEY
    gu32KeyOut = mu32Val;

    /* Update Lever */
    if( ((gu32KeyOut) & (HAL_KEY_6)) == HAL_KEY_6 )
    {
        HAL_SetLeverWater(TRUE);
    }
    else
    {
        HAL_SetLeverWater(FALSE);
    }
    
    if( ((gu32KeyOut) & (HAL_KEY_7)) == HAL_KEY_7 )
    {
        HAL_SetLeverHotWater(TRUE);
    }
    else
    {
        HAL_SetLeverHotWater(FALSE);
    }
}

void HAL_ScanKey(void)
{
    ScanKeyOut();
}
#endif

static void ScanLever(U8 mu8Id, U16 mu16Val);
void ProcessScanLever(void)
{
    ScanLever( LEVER_ID_WATER, HAL_GetLeverWater() );
    ScanLever( LEVER_ID_HOT_WATER, HAL_GetLeverHotWater() );
}

/*
 * timeout 10ms...
 *
 */
static void ScanLever(U8 mu8Id, U16 mu16Val)
{
    static U16 mu16PrevLeverVal[ MAX_LEVER_ID ];


    // 1. Get Lever value 
    if( mu16PrevLeverVal[ mu8Id ] != mu16Val )
    {
        mu16PrevLeverVal[ mu8Id ]   = mu16Val;
        Lever[ mu8Id ].Val = mu16Val;  
        if( mu16Val == 0 )
        {
            Lever[ mu8Id ].ValPop = mu16Val;  
        }

        if( mu16Val != 0 )
        {
            //Init Event
            Lever[ mu8Id ].Status        = LEVER_STATUS_PUSHED;
            Lever[ mu8Id ].PushedTime    = 0;  
            ClearLeverEventFlag( mu8Id, LEVER_EVENT_PUSEHD_ALL );
        }
        else 
        {
            if( Lever[ mu8Id ].PushedTime >= EVENT_TIME_OUT_SHORT_WATEROUT )
            {
                Lever[ mu8Id ].Status = LEVER_STATUS_POP;
                SetLeverEventFlag( mu8Id, LEVER_EVENT_POP );
            }
            else
            {
                Lever[ mu8Id ].Status = LEVER_STATUS_NONE;
            }
        }
    }
    
    if( Lever[ mu8Id ].Status == LEVER_STATUS_PUSHED )
    {
        Lever[ mu8Id ].PushedTime++;
		
        if( Lever[ mu8Id ].PushedTime == EVENT_TIME_OUT_8S_WATEROUT )
        {
            SetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_8S );
        }
        else if( Lever[ mu8Id ].PushedTime == EVENT_TIME_OUT_2S_WATEROUT )
        {
            SetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_2S );
        }
        else if( Lever[ mu8Id ].PushedTime == EVENT_TIME_OUT_SHORT_WATEROUT )
        {
            SetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_SHORT );
        }

        if( Lever[ mu8Id ].PushedTime > EVENT_TIME_OUT_8S_WATEROUT )
        {
            Lever[ mu8Id ].Status = LEVER_STATUS_TIME_OUT;
        }
    }
}

