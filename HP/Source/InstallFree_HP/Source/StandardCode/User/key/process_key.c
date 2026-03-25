#include "Global_Header.h"
#include "hw.h"
#include "process_key.h"
#include "key.h"
#include "key_common_handler.h"
#include "key_handler.h"
#include "water_out.h"
#include "flushing.h"

/*
 *
 * Param :
 *  -. pValidFunc, : ?????�????�수 ?��???
 *  -. pList, : ??�????�벤??리�???
 *  -. mu8Size : ??�????�벤??리�????�기
 * 
 * Return :
 *  -. FALSE : ??????처리?? ?�게 ????.
 *  -. TRUE : ??????처리?? ?�게 ????.
 */

/**
 * @brief Ű �Է¿� ���� ǥ��
 * 
 * @param pValidFunc 
 * @param pList 
 * @param mu8Size 
 * @return U8 
 */
static U8 KeyEventHandler(KeyValidFun_T pValidFunc, KeyEventList_T *pList, U8 mu8Size )
{
    U8   i;
    U16  mu16KeyVal;
    U16  mu16KeyPopVal;
    U8   mu8Sound;
    static U16 mu16PrevKeyVal = K_NONE;
    static U8 mu8ErrKeySkip = FALSE;

   
    mu16KeyVal    = GetKeyVal();
    mu16KeyPopVal = GetKeyPopVal();


    if( mu16KeyVal != K_NONE )
    {
#if 0
        StartDisplayWaterOutPointLeft();
        StartDisplayWaterOutPointRight();
        
        /* Reset Sleep Mode UnusedTime */
        ResetSleepMode();

        /* Reset Smart Saving Unused Time */
        ResetSmartUnusedSavingTime();
        ResetSmartUnusedForGreenWeekTimer();

        /* Reset Auto Drain UnusedTime */
        if(GetTimeShortStatus() == FALSE)
        {
            ResetAutoDrainAllTank();
        }
        
        /* ���� �ֱ� ��ü ��� */
        if(GetFlushingFilterChangeTypeMode() == TRUE)
        {
            ResetFlushingFilterChangeTypeModeTimer();
        }
#endif
    }
	
    if( mu16KeyVal != mu16PrevKeyVal )
    {
        mu16PrevKeyVal = mu16KeyVal;
        mu8ErrKeySkip = FALSE;
    }

    if( mu8ErrKeySkip == TRUE )
    {
        return TRUE;
    }

    if( pList == NULL || mu8Size == 0 )
    {
        return TRUE;
    }

    /* Check Pop Key */
    if( mu16KeyVal == K_NONE 
    && IsSetKeyEventFlag( KEY_EVENT_POP ) == TRUE )
    {
        ClearKeyEventFlag( KEY_EVENT_POP );
        for( i = 0; i < mu8Size ; i++ )
        {
            if( (pList+i)->Key == mu16KeyPopVal )
            {
                if( (pList+i)->actionEvent[KEY_ACTION_POP] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[KEY_ACTION_POP]();
                    
                    return TRUE;
                }
            }
        }
    }
    
    /* Check Pusehd Key */
    for( i = 0; i < mu8Size ; i++ )
    {
        if( (pList+i)->Key == mu16KeyVal )
        {
            if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_SHORT ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_SHORT );

#if 0
                if( ResetDrainWater() == TRUE )
                {
                    Sound( SOUND_CANCEL );
                }

                ResetMenuSettingTimer();

                if( SetSterDone( FALSE ) == TRUE )
                {
                    Sound( SOUND_SELECT );
                }
#endif

                if( mu16KeyVal != K_NONE 
                        && pValidFunc != NULL )
                {
                    if( pValidFunc( mu16KeyVal ) == FALSE )
                    {
                        // Sound( SOUND_ID_ERROR );
                        mu8ErrKeySkip = TRUE;
                        return TRUE;
                    }
                }

                if( (pList+i)->actionEvent[KEY_ACTION_SHORT] != NULL )
                {					
                    mu8Sound = (pList+i)->actionEvent[KEY_ACTION_SHORT]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
            else if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_LONG_7S ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_LONG_7S );

                if( (pList+i)->actionEvent[KEY_ACTION_7_SEC] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[KEY_ACTION_7_SEC]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
            /*
            else if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_LONG_5S ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_LONG_5S );

                if( (pList+i)->actionEvent[KEY_ACTION_5_SEC] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[KEY_ACTION_5_SEC]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
            */
            else if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_LONG_3S ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_LONG_3S );

                if( (pList+i)->actionEvent[ KEY_ACTION_3_SEC ] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[ KEY_ACTION_3_SEC ]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
            else if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_LONG_2S ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_LONG_2S );

                if( (pList+i)->actionEvent[ KEY_ACTION_2_SEC ] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[ KEY_ACTION_2_SEC ]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
            else if( IsSetKeyEventFlag( KEY_EVENT_PUSHED_LONG_1S ) == TRUE )
            {
                ClearKeyEventFlag( KEY_EVENT_PUSHED_LONG_1S );

                if( (pList+i)->actionEvent[ KEY_ACTION_1_SEC ] != NULL )
                {
                    mu8Sound = (pList+i)->actionEvent[ KEY_ACTION_1_SEC ]();
                    // Sound( mu8Sound );
                    return TRUE;
                }
                break;
            }
        }
    }

    return FALSE;
}

void ProcessKeyEventHandler(void)
{
    U8 mu8Ret = FALSE;
    static U16 mu16Delay = 0;     
    KeyValidFun_T  pKeyValidFun = NULL;
    KeyEventList_T  *pKeyEventList = NULL;
    U8 mu8KeyEventSize = 0;


    // if( GetDisplayInit() == FALSE )
    // {
    //     return ;
    // }

    if( mu16Delay != 0 )
    {
        mu16Delay--;
        return ;
    }

    // Get Event Handler by case..
    // if( GetEolStatus() == TRUE )
    // {
    //     // EOL
    //     pKeyValidFun = IsValidEolKeyCondition;
    //     pKeyEventList = (KeyEventList_T *)GetEolKeyEventList();
    //     mu8KeyEventSize = GetEolKeyEventListSize();
    // }
    // else if( GetFctStatus() == TRUE )
    // {
    //     // FCT
    //     pKeyValidFun = IsValidFctKeyCondition;
    //     pKeyEventList = (KeyEventList_T *)GetFctKeyEventList();
    //     mu8KeyEventSize = GetFctKeyEventListSize();
    // }
    // else
    // {
        // NORMAL
        pKeyValidFun = IsValidKeyCondition;
        pKeyEventList = (KeyEventList_T *)GetKeyEventList();
        mu8KeyEventSize = GetKeyEventListSize();
    // }

    // Call Key Event Handler
    mu8Ret = KeyEventHandler( pKeyValidFun, pKeyEventList, mu8KeyEventSize );
    if( mu8Ret == TRUE )
    {
        //SetMenuRefresh();
        //WakeUpStandby();
        mu16Delay = 30; // wait.. 300ms...
    }
}
