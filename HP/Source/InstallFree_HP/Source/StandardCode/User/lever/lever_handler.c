#include "Global_Header.h"
#include "lever_handler.h"
#include "lever_common_handler.h"
#include "water_out.h"
#include "water_out_type.h"

//#include "ster.h"
//#include "drain.h"
//#include "health.h"



/* WATER OUT */
static U8 LeverOpenTapWater(void);
static U8 LeverCloseTapWater(void);
static U8 LeverHotOpenTapWater(void);
static U8 LeverHotCloseTapWater(void);
static U8 LeverOpenTapWaterLong(void);


const static LeverEventList_T LeverEventList[] =
{
    /* Short,                 Long 2sec,    Long 8sec,    Pop  */
    {  LeverOpenTapWater,     NULL,         NULL,         LeverCloseTapWater     }, // LEVER - WATER OUT
    {  LeverHotOpenTapWater,  NULL,         NULL,         LeverHotCloseTapWater  }, // LEVER - HOT WATER OUT
};

/* WATER OUT - START */
static U8 LeverOpenTapWater(void)
{
    U8 mu8Sound = BUZZER_EFFLUENT;
    static U8 mu8BlinkOnOff = ON; // static local variable => global variable

    /* 필터리드스위치 미감지 시 추출 불가능 */
    if(Get_ReedSW_Status(REED_SW_ID_FILTER_REED) == FALSE)
    {
        mu8Sound = BUZZER_ERROR;
        return mu8Sound;
    }

#if 0
    /* Time Short mode �ƴҶ�����(�Ϲ� ��� �� ��) */
    if(GetTimeShortStatus() != TRUE )
    {
        /* ���� ��ü�� �� �������� ���� ���� */
        if(GetFilterReplaceStatus() == FILTER_REPLACE_NEED)
        {
            PlayFilterAlarm();
            return BUZZER_OFF;
        }
    }
    
    /* Unable to re-extract for 0.3 seconds after completion of extraction */
    if( IsExpiredOutProtectTime() == FALSE )
    {
        return BUZZER_OFF;
    }
#endif
    // Now waterout ing?? yes --> stop waterout
    if( GetWaterOut() == TRUE )
    {
        StopWaterOut();
        return BUZZER_EFFLUENT_END;
    }

#if 0
    /* Time Short mode �ƴҶ�����(�Ϲ� ��� �� ��) */
    if(GetTimeShortStatus() != TRUE )
    {
        if( (GetRoomWaterLevel() == LEVEL_LOW && GetWaterOutSelect() == SEL_WATER_ROOM)
            || (GetColdWaterLevel() == LEVEL_LOW && GetWaterOutSelect() == SEL_WATER_COLD) )
        {
            StartDisplayLowWater();
        }
    }
#endif
    StartWaterOut();

#if 0
    /* �������� && �������� �϶��� ���������� �߻� */
    if( GetWaterOutAmountType() == AMOUNT_ID_INFINITY && IsWaterAmountSelected() == TRUE)
    {
        mu8Sound = SOUND_ID_EFFLUENT_CONTINUE;
    }
		
    /* Stop timer related to 7seg when water out */
    StopDisplaySegOff();
    StopDisplaySegOn();
#endif

    return mu8Sound;
}

/* WATER OUT - STOP */
static U8 LeverCloseTapWater(void)
{
    if( GetWaterOut() ==TRUE
    && GetWaterOutPressContinue() == TRUE )
    {
        StopWaterOut();
        return BUZZER_EFFLUENT_END;
    }

    return BUZZER_OFF;
}

/*
static U8 WaterOutInfinity(void)
{
    if( GetWaterOut() == TRUE )
    {
        // Skip long button when FLUSHING...
	    if( IsDoneFlushInitSetup() == FALSE )
        {
            return FALSE;
        }
       
        
        if( GetWaterOutAmountType() != AMOUNT_ID_INFINITY )
        {
            SetWaterOutInfinityLongKey();
            return TRUE;
        }
    }

    return FALSE;
}
*/

/* WATER OUT - START */
static U8 LeverHotOpenTapWater(void)
{
    U8 mu8Sound = BUZZER_EFFLUENT;  // ���� ��� - "�¼��� �߰ſ�� �����ϼ���"
    static U8 mu8BlinkOnOff = ON; // static local variable => global variable
    #if 0

    /* Time Short mode �ƴҶ�����(�Ϲ� ��� �� ��) */
    if(GetTimeShortStatus() != TRUE )
    {
        /* ���� ��ü�� �� �������� ���� ���� */
        if(GetFilterReplaceStatus() == FILTER_REPLACE_NEED)
        {
            PlayFilterAlarm();
            return ;
        }
    }   

    if( Get_HotKeyLockStatus() == LOCK )
    {
        StartDisplayHotLock();
        return SOUND_ID_ALARM_LOCK_HOT;
    }

    /* Time Short mode �ƴҶ�����(�Ϲ� ��� �� ��) */
    if(GetTimeShortStatus() != TRUE )
    {
        if( GetRoomWaterLevel() == LEVEL_LOW )
        {
            StartDisplayLowWater();
            return SOUND_ID_ERROR;
        }

        /* ������ǥ�� �߿��� ���� ���� �Ұ�(�¼���ũ�� �������� �ƴϾ) ������ ǥ�ô� �ϳ� �̱� ������ �ü� �������
           ������ ǥ�ø� �ϰ� �ֱ� ������, �¼� �ü� ���� ���� �� �¼� ������ ǥ�÷� ȥ�� �Ҽ� �ֱ� ������ �̸� �����ϱ� ���� */
        if( GetWaterOut() == TRUE 
            && GetWaterOutSelect() == SEL_WATER_COLD
              && GetColdWaterLevel() == LEVEL_LOW )
        {
            StartDisplayLowWater();
            return SOUND_ID_ERROR;
        }
    }
	
    /* Unable to re-extract for 0.3 seconds after completion of extraction */
    if( IsExpiredHotOutProtectTime() == FALSE )
    {
        return BUZZER_OFF;
    }

    // Now Hot waterout ing?? yes --> stop waterout
    if( GetHotWaterOut() == TRUE )
    {
        StopHotWaterOut();
        return BUZZER_EFFLUENT_END;
    }  

    StartHotWaterOut();

    /* �������� && �������� �϶��� ���������� �߻� */
    if( GetHotWaterOutAmountType() == AMOUNT_ID_INFINITY && IsHotWaterAmountSelected() == TRUE)
    {
        mu8Sound = SOUND_ID_HOT_OUT_CONTINU;  // ���� ��� - �¼� ���� ���� ����
    }

    /* Stop timer related to 7seg when water out */
    StopDisplaySegOff();
    StopDisplaySegOn();
#endif
    return mu8Sound;
}

/* WATER OUT - STOP */
static U8 LeverHotCloseTapWater(void)
{
#if 0
    if( Get_HotKeyLockStatus() == ON )
    {
        return BUZZER_OFF;  // Avoid sound duplication
    }
	
     /* Time Short mode ?? ?? */
    if(GetTimeShortStatus() != TRUE )
    {
        if(GetRoomWaterLevel() == LEVEL_LOW)
        {
            return BUZZER_OFF;  // Avoid sound duplication
        }
    }
    
    if( GetHotWaterOut() ==TRUE
        && GetHotWaterOutPressContinue() == TRUE)
    {
        StopHotWaterOut();
        return BUZZER_EFFLUENT_END;
    }
#endif
    return BUZZER_OFF;
}

/*
static U8 LeverOpenTapWaterLong(void)
{
    U8 mu8Sound = BUZZER_OFF;

    if( WaterOutInfinity() == TRUE )
    {
        mu8Sound =  SOUND_ID_EFFLUENT_CONTINUE;
    }

    SetSettingDisp( FALSE );
    return mu8Sound;
}
*/

void* GetLeverEventList(void)
{
    // Return address of lever event table 
    return (void *)LeverEventList;
}

