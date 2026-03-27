#include "Global_Header.h"

#include "hw.h"
#include "water_out.h"
#include "hot_water.h"
#include "key_handler.h"
#include "amount.h"
#include "water_out_type.h"
#include "hot_water_out.h"
#include "flushing.h"

typedef struct _hot_water_out_
{
    U8  Select;                  // Sel_hot_water, Sel_Nothing
    U8  WaterOut;                // TRUE or FALSE  
    U8  PrevWaterOut;
    U16 ReturnTime;
    U16 ReturnTimeAmount;
    U16 ImpossibleTimer;         // Unable to re-extract for 0.3 seconds after completion of extraction

    U8  PressContinue;           // TRUE: Lever Mode, FALSE: Quantitative Extraction(120ML,250ML,500ML....) 
    U16 PressContinueReturnTime; 
    U8  FixedAmountType;         // FIXED_AMOUNT_120ml,250,500,1000,infinity
    U32 FixedAmountTargetTime;   // @10msec 
    U32 FixedAmountCurrentTime;  // @10msec
    
    /* For Default Amount*/
    U8 TriggerDefaultAmount;          // �뷮 ��ư ���� �� PressContinueReturnTime ���� 0 �� �ɶ� �⺻�뷮 ���� ���ֱ� ����

    U8  AmountKeyBackUp;
    U8  InfinityAmount; 
} HotWaterOut_T;

HotWaterOut_T HotOut;

void  InitHotWaterOut(void)
{
    /* Hot - Left Lever */
    HotOut.Select           = SEL_WATER_NOTHING;
    HotOut.WaterOut         = FALSE;
    HotOut.PrevWaterOut     = FALSE;
    HotOut.ReturnTime       = 0;
    HotOut.PressContinue    = TRUE;
    HotOut.ReturnTime	    = 0;
    HotOut.ReturnTimeAmount = 0;	
    HotOut.PressContinueReturnTime = 0;
    HotOut.InfinityAmount   = FALSE;
    HotOut.FixedAmountType  = GetAmountDefault();
    HotOut.FixedAmountTargetTime  = 0UL;
    HotOut.FixedAmountCurrentTime = 0UL;
    HotOut.ImpossibleTimer  = 0UL;
    HotOut.TriggerDefaultAmount = FALSE;
}

/* ���� ���� */
void StartHotWaterOut(void)
{
    if( HotOut.WaterOut == FALSE )
    {
        SetWaterOutTime(TYPE_LASTED, HotOut.Select, 0 );
    }
    HotOut.WaterOut = TRUE;
#if 0
    /* Auto Flushing */
    if(GetAutoFlushingRun() == TRUE)
    {
        ResetAutoFlushing();
        SetValveAutoFlushingOff();  //�����÷��� �߿� ���� �� ���, �����÷��� ��� �� �ʱ�ȭ
    }
#endif
    /* For stop Heating led blink */
    // StopDispTimerId(DISP_TIMER_HEATING_DIMMING_BLINK);
}

/* ���� ���� */
void  StopHotWaterOut(void)
{
    U8 mu8FixedAmount = 0;
    U8 mu8DefaultCursor;
    
    HotOut.WaterOut = FALSE;

    // �׻� HOT LOCK -> �¼� ���� �� ������ LOCK Ǯ����� -> �¼� ���� ���� 7�� �� �ٽ� �ڵ� LOCK (�̽Ż� pl ��� ���� ����)
    if( HotOut.Select == SEL_WATER_HOT )
    {
        /* 온수잠금 대설정타이머 설정 */
        // ReSetLockHotDelayTime();

        if( GetHotTempLevel() == HEATING )
        {
            // StartDispTimerId( DISP_TIMER_HEATING_DIMMING_BLINK );	
        }
    }

    /* Heating led on? yes -> Start Blink Timer for 7sec */
    if( HotOut.Select == SEL_WATER_HOT )
    {
        if( GetHotTempLevel() == HEATING )
        {
            // StartDispTimerId( DISP_TIMER_HEATING_DIMMING_BLINK );	
        }
    }

    /* �������� ���� ���̾��ٸ� �� �뷮 ������ �ٷ� ȸ��, ����Ʈ ���� ���ñ��� */
    if(IsHotWaterAmountSelected() == TRUE)
    {
        HotOut.InfinityAmount  = FALSE;
        SetHotWaterOutPressContinue(TRUE);

        if(GetWaterOut()== FALSE)
        {          
            SetWaterOutPressContinue(TRUE);
        }    
    }
    
    /* ������ ���� ���ϰ� ���� �� */
    if(GetWaterOut() == FALSE)
    {
        /* ���� ���� ���� �Ǿ������� ���� ����� ���� ����ȭ */
        if( IsWaterAmountSelected() == TRUE )
        {
            mu8FixedAmount = GetWaterOutFixedAmountType();
            SetHotWaterOutFixedAmountType(mu8FixedAmount);
        }
        /* ���� �뷮 ���� �ȵǾ������� DISP_TIMER_KEY_AMOUNT �ٷ� STOP */
        else
        {            
            // StopDispTimerId( DISP_TIMER_KEY_AMOUNT );

            /* ����Ʈ �������� ���� */
            mu8DefaultCursor = GetAmountDefaultCursor(); 
            SetAmountCursor(mu8DefaultCursor);  // ���� ���� �Ŀ� ����Ʈ�������� ����
            SetSkipCursorIncrease(TRUE);
        } 
    }
}

U8 GetHotWaterOut(void)
{
    return HotOut.WaterOut;
}

void  SetHotWaterOutSelect(U8 mu8Id )
{
    if( mu8Id >= MAX_WATER_ID )
    {
        return ;
    }

    ResetHotReturnTime();        // water key return time reset
    ResetHotReturnTimeAmount();

    // StartDispTimerId( DISP_TIMER_KEY_AMOUNT );

    // HotOut.Select = mu8Id;

    SetWaterOutSelect(mu8Id);

    // SaveEepromId( EEPROM_ID_SEL_WATER );
}

U8 GetHotWaterOutSelect(void)
{
    return HotOut.Select;
}

/* LeverMode Setting */
void SetHotWaterOutPressContinue(U8 mu8Mode )
{
    if( mu8Mode != TRUE && mu8Mode != FALSE )
    {
        return ;
    }

    if( mu8Mode == FALSE )
    {
        HotOut.PressContinue = FALSE;
        HotOut.PressContinueReturnTime = DEFAULT_RETURN_TIME;
       // SetAmountCursor(0); // �� ���� �ϸ� ����
    }
    else
    {
        HotOut.InfinityAmount  = FALSE;
        HotOut.PressContinue = TRUE;
       // HotOut.FixedAmountType = AMOUNT_ID_LEVER; // ������ �뷮��� ���� ���ڵ�
       // SetAmountCursor(GetAmountLeverCursor()); //�뷮cursor ������ ���� - ������ �뷮 ��� ���� ���� �ڵ�
    }

    //SaveEepromId( EEP_ID_CONF_CONTY );
}

U8 IsExpiredHotOutProtectTime(void)
{
    if( HotOut.ImpossibleTimer != 0 )
    {
        return FALSE;   
    }

    return TRUE;    
}

void ClearHotWaterOutInfinityAmount(void)
{
    HotOut.InfinityAmount = FALSE;
}

void SetHotReturnTime(U16 mu16Val)
{
    HotOut.ReturnTime = mu16Val;
}

void ResetHotReturnTime(void)
{
    HotOut.ReturnTime = DEFAULT_RETURN_TIME;
}

void ResetHotReturnTimeAmount(void)
{
    HotOut.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;
}

void ResetHotReturnTimePressContinue(void)
{
    HotOut.PressContinueReturnTime = DEFAULT_RETURN_TIME;
}

U16 GetReturnTimeHotPressContinue(void)
{
    return HotOut.PressContinueReturnTime;
}

/* LEVER */
U8 GetHotWaterOutPressContinue(void)
{
    return HotOut.PressContinue;
}

/* ���� �����(�¼�) ���� ���� ���� Ȯ�� �Լ� */
U8 IsHotWaterAmountSelected(void)
{
    if( GetHotWaterOutPressContinue() == FALSE)
    {
        return TRUE;
    }

    return FALSE;
}

/* using now amount */
U8 GetHotWaterOutFixedAmountType(void)
{
    return HotOut.FixedAmountType;
}

U8 GetHotWaterOutAmountType(void)
{
    if( HotOut.InfinityAmount == TRUE )
    {
        return AMOUNT_ID_INFINITY;
    }

    return GetHotWaterOutFixedAmountType();
}

void  SetHotWaterOutFixedAmountType(U8 mu8Type )
{
    if( mu8Type >= AMOUNT_ID_MAX )
    {
        return ;
    }

    // SetHotWaterOutPressContinue(FALSE);
    if( mu8Type == AMOUNT_ID_INFINITY )
    {
        HotOut.InfinityAmount = TRUE;
        HotOut.FixedAmountType  = AMOUNT_ID_INFINITY;
    }
 //   else if( mu8Type == AMOUNT_ID_LEVER )
//    {
 //       HotOut.InfinityAmount  = FALSE;
  //      HotOut.FixedAmountType  = AMOUNT_ID_LEVER;
  //      SetHotWaterOutPressContinue(TRUE);
  //  }
    else
    {
        HotOut.InfinityAmount  = FALSE;
        HotOut.FixedAmountType  = mu8Type;
    }
	
    HotOut.AmountKeyBackUp = GetHotWaterOutFixedAmountType();
    HotOut.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;
    
   // SaveEepromId( EEPROM_ID_CONF_FIXED_AMOUNT );
}

void  SetHotWaterOutFixedAmountTargetTime(U32 mu32Time )
{
    HotOut.FixedAmountTargetTime = mu32Time;
}

U32   GetHotWaterOutFixedAmountTargetTime(void)
{
    return HotOut.FixedAmountTargetTime;
}

void  SetHotWaterOutFixedAmountCurrentTime(U32 mu32Time )
{
    HotOut.FixedAmountCurrentTime = mu32Time;
}

U32   GetHotWaterOutFixedAmountCurrentTime(void)
{
    return HotOut.FixedAmountCurrentTime;
}

// ���� ���� ���� �˻�
// Precondition 
//  -. ��ũ ��� ����� �ƴ� ��,
//  -. �� ���� ���� ?,
static void CheckHotWaterOutStopCondition(void)
{
    if( GetWaterOut() == FALSE )
    {
        return;
    }

    /* Hot water extraction is not possible in the hot low level. */
    if( GetWaterOutSelect() == SEL_WATER_HOT )
    {
        // 온수탱크 수위가 낮아졌으면, 온수추출 취소
        if( Get_HotWaterLevel() == HOT_WATER_LEVEL_LOW )
        {
            StopWaterOut();
            Sound( BUZZER_ERROR );
            return;
        }
    }

    // 필터리드 열려있으면, 온수추출 취소
    if(Get_ReedSW_Status(REED_SW_ID_FILTER_REED) == FALSE)
    {
        StopWaterOut();
        Sound( BUZZER_ERROR );
        return;
    }

    // 온수탱크 온도센서 에러나면, 온수추출 취소
    if( Get_ErrorStatus(ERROR_ID_TANK_HOT_TEMP_E45) == TRUE )
    {
        StopWaterOut();
        SetHotWaterOutSelect(SEL_WATER_NOTHING);
        return;
    }
}

static void LeftWaterOut(void)
{
    U8 mu8AmoutType;
    U8 mu8DefaultCursor;

    /* 플러싱이 필요하면 추출불가 */
    if((GetFlushingConfig() == TRUE)
    // || (GetCitricFlushConfig() == TRUE))
    )
    {
        StopHotWaterOut();  // ���� �߿� ���ͱ�ü�ؼ� �÷��� �����ϰԵǸ� ��� �������ᰡ �ȵǴ� ���� �߻��ؼ� �߰��� 
    }

    if( HotOut.WaterOut == TRUE )
    {
        HotOut.ReturnTimeAmount = DEFAULT_RETURN_AMOUNT_TIME;    
    }
    	
    // ���� �߿��� �ð� reload
    if( HotOut.WaterOut == TRUE
    && HotOut.PressContinue == FALSE )
    {
        ResetHotReturnTimePressContinue();
        ResetReturnTimePressContinue();
    }

    // ���� ���� ��� ���� 
    if( HotOut.PressContinue == FALSE && HotOut.PressContinueReturnTime == 0 )
    {
        SetHotWaterOutPressContinue( TRUE );
        ClearHotWaterOutInfinityAmount();
    }

    if(GetHotWaterOutPressContinue() == TRUE)
    {     
        mu8DefaultCursor = GetAmountDefaultCursor(); 
        SetAmountBackupCursor(mu8DefaultCursor);  //���� ���� �� ������ ��ȯ �� �� ����Ʈ Ŀ�� ������ set(����Ʈ ���� ���� �� �뷮bar,seg ��ġ�����ֱ�����)
    }

    /* �����⺻ �뷮 ���� */
    if(HotOut.PressContinueReturnTime == 0 && HotOut.TriggerDefaultAmount == TRUE)
    {
        HotOut.TriggerDefaultAmount = FALSE; // 1���� ���� �ϱ� ����

        HotOut.FixedAmountType = GetAmountDefault();
        SetAmountCursor(GetAmountDefaultCursor());
        SetSkipCursorIncrease(TRUE);
    }
    
    // ���� ���� ��ǥ �ð� �� ���� �ð� ���...
    mu8AmoutType = GetHotWaterOutAmountType();
    if( HotOut.WaterOut == FALSE || HotOut.PressContinue == TRUE )
    {
        if( HotOut.Select == SEL_WATER_HOT)
        {
            HotOut.FixedAmountTargetTime = GetAmountHotTime(mu8AmoutType);
        }

        AddHotWaterOutTime();   // Add water out time based on water level

        HotOut.FixedAmountCurrentTime = 0;
		
        return ;
    }

    if( HotOut.FixedAmountCurrentTime < HotOut.FixedAmountTargetTime )
    {
        HotOut.FixedAmountCurrentTime++;
    }
    else
    {
        StopHotWaterOut();
        // ���� ���� �ð� ����Ǹ� ���� ����...
        Sound( BUZZER_EFFLUENT_END );
    }
}

static void  LeftLeverOutSelect(void)
{
    U8 mu8SelHot;

    /* ������ ����
    if( HotOut.WaterOut == TRUE )
    {	
        HotOut.ReturnTime = RETURN_TIME_AFTER_WATER_OUT;
    }
	*/

    #if 0
    /* 1. �Ϲ� ���� �϶� �� (��а˻� , Aging �� TimeShort, �¼� ���� �ŷڼ� ������ �׽�Ʈ �϶��� X) */
    if( GetTimeShortStatus() == FALSE
        && GetTestHotRepeatStatus() == FALSE
         && GetTestAllRepeatStatus() == FALSE )
    {
        if( Get_HotKeyLockStatusDelayTime() == 0 ) 
        {  
            HotOut.Select = SEL_WATER_NOTHING;
        }
    }
#endif
    
    if( HotOut.PressContinueReturnTime != 0 )
    {
        HotOut.PressContinueReturnTime--;
        HotOut.TriggerDefaultAmount = TRUE;
    }
}

static void LeftLeverOutValve(void)
{
    U8 mu8Select;
    U8 mu8HotSelect;

    mu8HotSelect = HotOut.Select;

    /* TURN OFF WATER OUT */
    if( HotOut.WaterOut == FALSE )
    {
#if 0
        /* HOT */
        ValveClose( VALVE_HOT_OUT );
#endif
        Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, OFF, 0);
        Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, CLOSE, 0);
        Set_ValveControl(VALVE_ID_HOT_OUT, FEED, CLOSE, 1);
        return ;
    }

    /* TURN ON WATER OUT - HOT */
    if( HotOut.WaterOut == TRUE ) 
    {
        if( mu8HotSelect == SEL_WATER_HOT )
        {
#if 0
            ValveOpen( VALVE_AIR );  
            ValveOpen( VALVE_HOT_OUT );
#endif

            Set_DC_PumpControl(DC_PUMP_ID_WATER_IN, ON, 2);
            Set_ValveControl(VALVE_ID_HOT_TANK_IN, FEED, OPEN, 1);
            Set_ValveControl(VALVE_ID_HOT_OUT, FEED, OPEN, 0);
        }	
    }
}

static void SyncHotWaterOutAmount(void)
{
    U8 mu8SyncAmount;
    
    /* ���� ����x, ���� ����o */
    if(GetHotWaterOut() == FALSE && GetWaterOut() == TRUE)
    {
        /* ���� ���� ���� �� */
        if(IsWaterAmountSelected() == TRUE)
        {
            /* ������ ���� ���� ���̶��, ���� ������ ������ �ƴ� ������ ���� �ؾ� �� */
          //  SetHotWaterOutFixedAmountType(AMOUNT_ID_LEVER);
          
            HotOut.InfinityAmount  = FALSE;
            SetHotWaterOutPressContinue(TRUE);
        }            
    }

    /* ���� ���� ���� ���� ����ȭ �� ������ ���� */
    if( HotOut.PrevWaterOut != HotOut.WaterOut)
    {
        HotOut.PrevWaterOut = HotOut.WaterOut;
        if( HotOut.WaterOut== FALSE )
        {
            /* 1. ��������ȭ : ���� ���� ������ ������ ���� ���� ���� �� ���¶�� ������ ����ó�� ���� ����
               �Ѵ� ���� ������ �ʰ�, ���� ���õ� ���¶�� ���� �����ϴ� ���� ��������� */
            if(GetWaterOut() == FALSE
                && GetWaterOutPressContinue() == FALSE)
            {
                SetHotWaterOutPressContinue(FALSE);
            }

            /* 2. Unable to re-extract for 0.3 seconds after completion of extraction */
            HotOut.ImpossibleTimer = OUT_PROTECT_TIME;
        }
    }

    if( HotOut.ImpossibleTimer != 0 )
    {
        HotOut.ImpossibleTimer--;  
    }
}

void  ControlHotWaterOut(void)
{  
    // SyncHotWaterOutAmount();        // ��,�� ����� ���� ����ȭ
    // LeftLeverOutSelect();           // Control �¼� ���� 
    // LeftLeverOutValve();            // Control Valve
    // LeftWaterOut();                 // ���� ���� ��� standard
    CheckHotWaterOutStopCondition();  // �¼� ���� ���� ����
} 


