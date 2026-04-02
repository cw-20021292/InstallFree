#ifndef __HAL_LED_H__
#define __HAL_LED_H__

#include "Type_Define.h"

#define  MAX_SEG_LED_BUF   12

/* 0 ~ 100 Brightness control */
#define LED_ON    100
#define LED_ON_2  50
#define LED_OFF   0
#define LED_OFF2  30


#define SEG_ON    100  // brightness level 0 ~ 100
#define SEG_OFF     0

#define SEG1                0
#define SEG2                1
#define SEG3                2 
#define SEG4                3 
#define MAX_SEG_UNIT_NUM    4

#define LOCATION       0
#define CHAR           1
#define DUTY           2  
#define TYPE           3  
#define MAX_SEG_VAL    4 

#define LED_TYPE_DUTY_DIM   (0x10)
#define LED_TYPE_DUTY       (0x00)

#define SEG_TYPE_DUTY_DIM   (0x10)
#define SEG_TYPE_DUTY       (0x00)


// LedProtocol_T LedProtocolDataTable[] �� ���� �������
typedef enum
{	 
    // Front LED
    ICON_HEATING,           // 0
    HOT_LOCK,               // 3  
    HOT_WATER,              // 4
    ROOM_WATER,             // 6	
    RIGHT_BAR1,             // 10    Display UI : �� ��  bar
    RIGHT_BAR2,             // 9     Display UI : �� ������ �Ʒ� bar
    ICON_INFINITY,          // 11    AMOUNT_INFINITY
    ICON_LOW_WATER,         // 12 	
    ICON_REPLACE_FILTER,    // 19 
    LED_WATER_OUT,  // 29   Shoot led from above the extractor right so that the cup can be clearly seen

    MAX_LED_NUM	            // 30
} LedId_T;




void HAL_InitLed(void);
void HAL_TurnOnOffLEDAll(U8 mu8Duty);
U8 HAL_GetProtocolId(LedId_T id);
U8 HAL_GetProtocolCommand(LedId_T id);
U8 HAL_GetProtocolIdValue(LedId_T id);
void HAL_TurnOnOffLED(LedId_T id, U8 mu8Duty);
void SetLedType(LedId_T id, U8 mu8Type );
U8 GetLedType(LedId_T id);


void HAL_InitSeg(void);

// void SetSegChar(U8 mu8Location, U8 mu8Char);
// U8 GetSegChar(U8 mu8Location);
// void SetSegDuty(U8 mu8Location, U8 mu8Duty);
// U8 GetSegDuty(U8 mu8Location);
// void SetSegType(U8 mu8Location, U8 mu8Type);
// U8 GetSegType(U8 mu8Location);
// U8 GetSegVal(U8 mu8Location);

#endif /* __HAL_LED_H__ */
