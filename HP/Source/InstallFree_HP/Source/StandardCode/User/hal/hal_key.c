#include "Global_Header.h"
#include "hw.h"
#include "hal_key.h"


#define  HAL_KEY_PUSHED     LOW
#define  HAL_LEVER_PUSHED   LOW

#define  DEFAULT_COUNT      50

typedef struct _hal_key_
{
    U32 Key;
    U16  WaterOut;
    U16  HotWaterOut;
} TKeyVal;

TKeyVal HalKey;

void HAL_InitKey(void)
{
    HalKey.Key      = 0UL;
    HalKey.WaterOut = 0UL;
    HalKey.HotWaterOut = 0UL;
}

void HAL_SetKeyVal(U32 mu32Val)
{
    HalKey.Key = mu32Val;
}


U16 HAL_GetKeyVal(void)
{
    return HalKey.Key;
}


void HAL_SetLeverWater(U8 mu8Val)
{
    HalKey.WaterOut = mu8Val;
}

U8 HAL_GetLeverWater(void)
{
    return HalKey.WaterOut;
}

void HAL_SetLeverHotWater(U8 mu8Val)
{
    HalKey.HotWaterOut = mu8Val;
}

U8 HAL_GetLeverHotWater(void)
{
    return HalKey.HotWaterOut;
}

