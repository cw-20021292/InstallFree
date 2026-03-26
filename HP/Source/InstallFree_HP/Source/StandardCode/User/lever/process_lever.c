#include "Global_Header.h"

#include "lever_common_handler.h"
#include "key.h"
#include "water_out.h"
#include "flushing.h"
#include "lever.h"
#include "process_lever.h"
#include "lever_handler.h"



static U8 IsValidLeverCondition(U8 mu8Id )
{

#if 0
    if( GetLockAll() == ON )
    {
        StartDisplayLockAll();
        return FALSE;
    }
#endif

#if 0
    if( GetSmartUnusedSaveConfigMode() == TRUE )
    {
        return FALSE;
    }
#endif

#if 0
    if( GetColdWeakConfigMode() == TRUE )
    {
        return FALSE;
    }
#endif

#if 0
    if( GetAltidueConfigMode() == TRUE )
    {
        return FALSE;
    }
#endif

#if 0
    if( GetUvTestMode() == TRUE )
    {
        return FALSE;
    }
#endif
    /* Flushing */
    if( GetFlushingConfig() == TRUE )
    {
        return FALSE;
    }
#if 0
    /* Flushing Change Type Mode */
    if( GetFlushingFilterChangeTypeMode() == TRUE )
    {
        return FALSE;
    }
#endif

#if 0
    /* Citric Acid Flush */
    if( GetCitricFlushConfig() == TRUE )
    {
        return FALSE;
    }
#endif
    /*
    if( IsStartSter() == TRUE )
    {
        StartDisplaySter();
        return FALSE;
    }

    if( GetDispAdjustHourConfig() == TRUE )
    {
        return FALSE;
    }

    if( GetDispDrainWaterConfig() == TRUE )
    {
        return FALSE;
    }
    */

    return TRUE;
}

static void EventHandler(U8 mu8Id, LeverEventList_T *pList)
{
    U8 mu8Sound;
    static U8 mu8ErrSkip[ MAX_LEVER_ID ]  = {FALSE};


    if( IsSetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_SHORT ) == TRUE )
    {
        ClearLeverEventFlag( mu8Id,  LEVER_EVENT_PUSHED_SHORT );

        if( IsValidLeverCondition( mu8Id ) == FALSE )
        {
            mu8ErrSkip[ mu8Id ] = TRUE;
            Sound( BUZZER_ERROR );
        }
        else if( (pList + mu8Id )->actionEvent_1 != NULL )
        {
            mu8Sound = (pList + mu8Id)->actionEvent_1();
            Sound( mu8Sound );
        }
#if 0
        /* For Sleep Mode - ����,Ű push�� ���� */
        ResetSleepMode();

        /* SmartUnusedSaving - Reset Smart Saving Unused Time */
        ResetSmartUnusedSavingTime();
        ResetSmartUnusedForGreenWeekTimer();
       
        /* Auto Drain - Reset Auto Drain UnusedTime */
        ResetAutoDrainAllTank();

        /* Silver Care - Reset Water Out UnusedTime */
        ResetUnusedTime();
#endif
    } 
    else if( IsSetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_2S ) == TRUE )
    {
        ClearLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_2S );

        if( (pList + mu8Id )->actionEvent_2 != NULL )
        {
            mu8Sound = (pList + mu8Id )->actionEvent_2();
            Sound( mu8Sound );
        }
    }
    else if( IsSetLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_8S ) == TRUE )
    {
        ClearLeverEventFlag( mu8Id, LEVER_EVENT_PUSHED_LONG_8S );

        if( (pList + mu8Id )->actionEvent_3 != NULL )
        {
            mu8Sound = (pList + mu8Id )->actionEvent_3();
            Sound( mu8Sound );
          
        }
    }
    // e??e��? i?��e?�� POP
    else if( IsSetLeverEventFlag( mu8Id, LEVER_EVENT_POP ) == TRUE )
    {
        ClearLeverEventFlag( mu8Id, LEVER_EVENT_POP );

        // i?��e?��i?�� i??e?�� e�Ʃ�i??e??e�Ϣ�, POP i?��e����i?��e�͢� Skipi?��e?��.
        if( mu8ErrSkip[ mu8Id ] == TRUE )
        {
            mu8ErrSkip[ mu8Id ] = FALSE;
            return ;
        }

        if( (pList + mu8Id )->actionEvent_4 != NULL )
        {
            mu8Sound = (pList + mu8Id )->actionEvent_4();
            Sound( mu8Sound );
        }
    }
}

void ProcessLeverEventHandler(void)
{
    LeverEventList_T  *pEventList = NULL;
    U8 mu8KeyEventSize = 0;

#if 0
    if( GetDisplayInit() == FALSE )
    {
        return ;
    }

    if( GetEolStatus() == TRUE )
    {
        // EOL
        pEventList = (LeverEventList_T *)GetEolLeverEventList();
    }
    else if( GetFctStatus() == TRUE )
    {
        // FCT
        pEventList = (LeverEventList_T *)GetFctLeverEventList();
    }
    else
    {
        // NORMAL
        pEventList = (LeverEventList_T *)GetLeverEventList();
    }
#endif

    pEventList = (LeverEventList_T *)GetLeverEventList();

    EventHandler( LEVER_ID_WATER, pEventList );
    EventHandler( LEVER_ID_HOT_WATER, pEventList );
}
