#include "Global_Header.h"

#include "display_lib.h"
#include "hal_led.h"


typedef struct _disp_timer_
{
    U8 Blink[ MAX_DISP_TIMER_BLINK_ID ];          /* BLINK ON/OFF */
    U16 TimerBlink[ MAX_DISP_TIMER_BLINK_ID ];
    U16 TimerCount[ MAX_DISP_TIMER_BLINK_ID ];
    U16 TimerOnCount[ MAX_DISP_TIMER_BLINK_ID ];
    U16 TimerOffCount[ MAX_DISP_TIMER_BLINK_ID ];
    U16 Timer[ MAX_DISP_KEY_TIMER_ID ];
} DispTimer_T;

DispTimer_T DispTimer;


void InitDispTimer(void)
{
    memset( (void __far *)&DispTimer, 0, sizeof(DispTimer_T) );

    DispTimer.TimerCount[ DISP_TIMER_ID_500MS ]  = TIMER_500MS;
    DispTimer.TimerCount[ DISP_TIMER_ID_1SEC ]   = TIMER_1SEC;

    /* In order to set each on the blink "on time" and "off time" separately */
    DispTimer.TimerOnCount[ DISP_TIMER_ID_500MS ]  = TIMER_500MS;
    DispTimer.TimerOnCount[ DISP_TIMER_ID_1SEC ]   = TIMER_1SEC;
    DispTimer.TimerOnCount[ DISP_TIMER_ID_3SEC ]   = TIMER_3SEC;
    DispTimer.TimerOnCount[ DISP_TIMER_ID_4SEC ]   = TIMER_4SEC;
    DispTimer.TimerOnCount[ DISP_TIMER_ID_100MS ]  = TIMER_100MS;

    DispTimer.TimerOffCount[ DISP_TIMER_ID_500MS ]  = TIMER_500MS;
    DispTimer.TimerOffCount[ DISP_TIMER_ID_1SEC ]   = TIMER_1SEC;
    DispTimer.TimerOffCount[ DISP_TIMER_ID_3SEC ]   = TIMER_1SEC;  // ID is 3SEC, Why is the value TIMER_1SEC?  POWER SAVING ENTER -> LED ON for 1sec but, LED OFF for 3sec
    DispTimer.TimerOffCount[ DISP_TIMER_ID_4SEC ]   = TIMER_4SEC;
    DispTimer.TimerOffCount[ DISP_TIMER_ID_100MS ]  = TIMER_100MS;
}

U8 IsExpiredDispTimer(U8 id)
{
    if( DispTimer.Timer[ id ] == 0 )
    {
        return TRUE;
    }

    return FALSE;
}

void SetDispTimer(U8 id, U16 time)
{
    DispTimer.Timer[ id ] = time;
}


U8 IsExpiredDispBlinkTimer(U8 id)
{

    if( DispTimer.TimerBlink[ id ] == 0 )
    {
        return TRUE;
    }

    return FALSE;
}

static void ResetDispBlinkTimer( mu8TimerId )
{
    DispTimer.TimerBlink[ mu8TimerId ] = DispTimer.TimerCount[ mu8TimerId ];
}

 
U8 BlinkLED( U8 mu8OnOff, void (*pFun)(U8 mu8OnOff), U8 mu8TimerId )
{
    if( pFun == NULL )
    {
        return ;  
    }
#if 1
    if( DispTimer.Blink[ mu8TimerId ] != mu8OnOff  )
    {
        DispTimer.Blink[ mu8TimerId ] = mu8OnOff;
    }
#endif

    if( IsExpiredDispBlinkTimer( mu8TimerId ) == TRUE )
    {
        if( mu8OnOff == LED_OFF )
        {
            mu8OnOff = LED_ON;
        }
        else
        {
            mu8OnOff = LED_OFF;
        }
    }

    if( pFun != NULL )
    {
        pFun( mu8OnOff );  
    }

    return mu8OnOff;
}



U8 BlinkLEDDuty( U8 mu8OnOff, void (*pFun)(U8 mu8OnOff), U8 mu8TimerId )
{
    if( pFun == NULL )
    {
        return ;  
    }
#if 1
    if( DispTimer.Blink[ mu8TimerId ] != mu8OnOff  )
    {
        DispTimer.Blink[ mu8TimerId ] = mu8OnOff;
    }
#endif

    if( IsExpiredDispBlinkTimer( mu8TimerId ) == TRUE )
    {
        if( mu8OnOff == LED_OFF )
        {
            mu8OnOff = LED_ON;
        }
        else
        {
            mu8OnOff = LED_OFF;
        }
    }

    if( pFun != NULL )
    {
        pFun( mu8OnOff );  
    }

    return mu8OnOff;
}

void UpdateDisplayTimer(void)
{
    U8 i;


    /* Update Blink Timer */
    for( i = 0; i < MAX_DISP_TIMER_BLINK_ID; i++ )
    {
        if( DispTimer.TimerBlink[ i ] == 0 )
        {
            // Toggle Blink LED 
            if( DispTimer.Blink[ i ] == LED_ON )
            {
                DispTimer.TimerBlink[ i ] = DispTimer.TimerOffCount[ i ];
                DispTimer.Blink[ i ] = OFF;
            }
            else
            {
                DispTimer.TimerBlink[ i ] = DispTimer.TimerOnCount[ i ];
                DispTimer.Blink[ i ] = LED_ON;
            }
        }
        else
        {
            DispTimer.TimerBlink[ i ]--;
        }
    }

    /* Update Key Timer */
    for( i = 0; i < MAX_DISP_KEY_TIMER_ID; i++ )
    {
        if( DispTimer.Timer[ i ] != 0 )
        {
            DispTimer.Timer[ i ]--;
        }
    }
}

