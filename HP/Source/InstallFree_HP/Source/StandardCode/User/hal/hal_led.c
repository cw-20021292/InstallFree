// #pragma interrupt INTTM01 r_tau0_channel1_interrupt
#include "Global_Header.h"

#include "hal_led_protocol.h"
#include "hw.h"
#include "hal_led.h"


#define ALL_ON      0xFFU
#define ALL_OFF     0x00U


typedef struct _led_protocol_
{
    U8 Id;
    U8 Command;
    U8 Type;   // on off speed
} LedProtocol_T;
LedProtocol_T LedProtocolDataTable[] =    
{
    // LED Data Id                          // Just an initial setting
    { PROTOCOL_NORMAL_LED_HOT_HEATING,          0x00,    LED_TYPE_DUTY },
    { PROTOCOL_NORMAL_LED_HOT_LOCK,             0x00,    LED_TYPE_DUTY },
    { PROTOCOL_NORMAL_LED_HOT,                  0x00,    LED_TYPE_DUTY },
    { PROTOCOL_NORMAL_LED_AMBI,                 0x00,    LED_TYPE_DUTY },
    { PROTOCOL_NORMAL_LED_QUENTITY_STEP1,       0x00,    LED_TYPE_DUTY },   //RIGHT_BAR2
    { PROTOCOL_NORMAL_LED_QUENTITY_STEP2,       0x00,    LED_TYPE_DUTY },   //RIGHT_BAR1
    { PROTOCOL_NORMAL_LED_QUENTITY_CONTINUE,    0x00,    LED_TYPE_DUTY },   //ICON_INFINITY
    { PROTOCOL_NORMAL_LED_LOW_WATER,            0x00,    LED_TYPE_DUTY },
    { PROTOCOL_NORMAL_LED_FILTER_CHANGE,        0x00,    LED_TYPE_DUTY },   // Replace Filter
    { PROTOCOL_NORMAL_LED_WATEROUT_POINT_RIGHT, 0x00,    LED_TYPE_DUTY }, 
}; 


/*
void SetLedType( U8 mu8Id, U8 mu8Type )
{
    U8 mu8Duty;
	
	mu8Duty = LedProtocolDataTable[mu8Id].Command;

	mu8Duty = mu8Duty + mu8Type;

    LedProtocolDataTable[mu8Id].Command = mu8Duty;   
}*/

void SetLedType(LedId_T id, U8 mu8Type )
{
    LedProtocolDataTable[id].Type = mu8Type;
}
U8 GetLedType(LedId_T id)
{
    return LedProtocolDataTable[id].Type;
}

void HAL_InitLed(void)
{
    HAL_TurnOnOffLEDAll( LED_OFF );
}

void HAL_TurnOnOffLEDAll(U8 mu8Duty)
{
    U8 i;
	
    for(i = 0; i < MAX_LED_NUM; i++ )
    {
        LedProtocolDataTable[ i ].Command = mu8Duty;
    }
}

U8 HAL_GetProtocolId(LedId_T id)
{
    return LedProtocolDataTable[id].Id;
}

U8 HAL_GetProtocolCommand(LedId_T id)
{
    return LedProtocolDataTable[id].Command;
}

void HAL_TurnOnOffLED(LedId_T id, U8 mu8Duty)
{
    LedProtocolDataTable[id].Command = mu8Duty;
}

U8 HAL_GetProtocolIdValue(LedId_T id)
{
    U8 mu8Type = 0U;
    U8 mu8Duty = 0U;
    U8 mu8Value = 0U;

    mu8Type = GetLedType(id);
    mu8Duty = HAL_GetProtocolCommand(id);

	mu8Value = (PROTOCOL_NORMAL_LED_0_DUTY | (mu8Duty/10)) + mu8Type; // LED bright setting

    return mu8Value;
}

#if 0

U8 SegTable[MAX_SEG_UNIT_NUM][MAX_SEG_VAL] =
{
// LOCATION,   CHAR initial value,           DUTY initial value           TYPE for dimming
    { SEG1,    PROTOCOL_SEG_LED_DATA_OFF,    PROTOCOL_SEG1_LED_0_DUTY,    SEG_TYPE_DUTY },
    { SEG2,    PROTOCOL_SEG_LED_DATA_OFF,    PROTOCOL_SEG2_LED_0_DUTY,    SEG_TYPE_DUTY },
    { SEG3,    PROTOCOL_SEG_LED_DATA_OFF,    PROTOCOL_SEG3_LED_0_DUTY,    SEG_TYPE_DUTY },
    { SEG4,    PROTOCOL_SEG_LED_DATA_OFF,    PROTOCOL_SEG4_LED_0_DUTY,    SEG_TYPE_DUTY }
};   

void SetSegChar(U8 mu8Location, U8 mu8Char)
{
    SegTable[mu8Location][CHAR] = mu8Char;
}

U8 GetSegChar(U8 mu8Location)
{
    return SegTable[mu8Location][CHAR];
}

void SetSegDuty(U8 mu8Location, U8 mu8Duty)
{
    SegTable[mu8Location][DUTY] = mu8Duty;
}

U8 GetSegDuty(U8 mu8Location)
{
    return SegTable[mu8Location][DUTY];
}

void SetSegType(U8 mu8Location, U8 mu8Type )
{
    SegTable[mu8Location][TYPE] = mu8Type;
}

U8 GetSegType(U8 mu8Location)
{
    return SegTable[mu8Location][TYPE];
}

U8 GetSegVal(U8 mu8Location)
{
    if( mu8Location == SEG1)
    {                                                  // 0x00 or 0x10
       SegTable[SEG1][DUTY] = SegTable[SEG1][DUTY] - SegTable[SEG1][TYPE];
    }
    
    return SegTable[mu8Location][DUTY];
}

void HAL_InitSeg(void)
{
    // HAL_TurnOnOffSegAll( SEG_OFF );
}



U8 TransSegDutyProtocol(U8 mu8Location, U8 mu8Duty)
{
    U8 mu8Protocol;
	
    mu8Protocol = (PROTOCOL_SEG1_LED_0_DUTY + (16 * mu8Location)) | mu8Duty/10; // Increases by 16 as the number of segment changes

    return mu8Protocol;
}

void // HAL_TurnOnOffSegAll(U8 mu8Val)
{
    U8 i;
    U8 mu8Char;
    U8 mu8Duty;

    /* Convert to protocol format */
    if( mu8Val != SEG_OFF )
    {
        mu8Char = SEG_LED_ALL_ON;
    }
    else
    {
        mu8Char = PROTOCOL_SEG_LED_DATA_OFF;
    }

	
    for(i = 0; i < MAX_SEG_UNIT_NUM; i++ )
    {
        mu8Duty = TransSegDutyProtocol(i, mu8Val); // Seg LED bright setting
		
        SegTable[ i ][CHAR] = mu8Char;
        SegTable[ i ][DUTY] = mu8Duty;
    }
	
}

void HAL_TurnOnOffSeg( U8 mu8Location, U8 mu8Val, U8 mu8Duty )
{
    if(	mu8Location >= MAX_SEG_UNIT_NUM )
    {
        mu8Location = SEG4;
    }

    mu8Duty = (PROTOCOL_SEG1_LED_0_DUTY + (16 * mu8Location)) | mu8Duty/10; // Increases by 16(0x10) as the number of segment location changes
    SetSegChar(mu8Location, mu8Val);
    SetSegDuty(mu8Location, mu8Duty);
}
#endif
