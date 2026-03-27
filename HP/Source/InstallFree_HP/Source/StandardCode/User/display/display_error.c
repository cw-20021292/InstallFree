#include "Global_Header.h"

#include "hw.h"
#include "hal_led.h"
#include "display.h"
#include "display_error.h"
#include "error.h"

static void ErrTempCold(U8 mu8Cmd);
static void ErrTempHot(U8 mu8Cmd);
static void ErrTempOverHot(U8 mu8Cmd);
static void ErrColdFeed(U8 mu8Cmd);
static void ErrColdLow(U8 mu8Cmd);
static void ErrColdMide(U8 mu8Cmd);
static void ErrColdHigh(U8 mu8Cmd);
static void ErrColdComplexLowMide(U8 mu8Cmd);
static void ErrRoomFeed(U8 mu8Cmd);
static void ErrRoomLow(U8 mu8Cmd);
static void ErrRoomHigh(U8 mu8Cmd);
static void ErrHotHigh(U8 mu8Cmd);
static void ErrLeak(U8 mu8Cmd);
static void ErrTempAmb(U8 mu8Cmd);
static void ErrBoostPump(U8 mu8Cmd);
static void ErrDrainPump(U8 mu8Cmd);
static void ErrCirculatePump(U8 mu8Cmd);
static void ErrWaterOutage(U8 mu8Cmd);


typedef void(*Action_T)(U8 mu8Cmd);
typedef struct _error_display_list_
{
    ErrorId_T  Id;
    Action_T   DispAction;
} ErrDisplay_T;

ErrDisplay_T ErrDisplayList[] = 
{
   // { ERR_OVER_HOT_WATER,          ErrTempOverHot             },
    { ERR_ID_TEMP_COLD_WATER,         ErrTempCold              },      
    { ERR_ID_TEMP_HOT_WATER,          ErrTempHot               },       
    { ERR_ID_TEMP_AMBIENT,            ErrTempAmb               }, 
   // { ERR_ID_BOOST_PUMP,              ErrRoomFeed              }, 
    { ERR_ID_DRAIN_PUMP,              ErrDrainPump             },
    { ERR_ID_CIRCULATE_PUMP,          ErrCirculatePump         },
   // { ERR_ID_COLD_COMPLEX_LOWMIDE,    ErrColdComplexLowMide    },      
   // { ERR_ID_COLD_FEED,               ErrColdFeed              },       
   // { ERR_ID_COLD_HIGH_LEVEL,         ErrColdHigh              },       
   // { ERR_ID_COLD_MIDE_LEVEL,         ErrColdMide              },         
    { ERR_ID_COLD_LOW_LEVEL,          ErrColdLow               },      
    { ERR_ID_HOT_HIGH_LEVEL,          ErrHotHigh               },   
   // { ERR_ID_ROOM_FEED,               ErrRoomFeed              },       
    { ERR_ID_ROOM_HIGH_LEVEL,         ErrRoomHigh              },             
    { ERR_ID_ROOM_LOW_LEVEL,          ErrRoomLow               },   
    { ERR_ID_OUTAGE_WATER,            ErrWaterOutage           },   
    { ERR_ID_LEAK,                    ErrLeak                  },       
};

#define  SZ_LIST  ( sizeof(ErrDisplayList) / sizeof(ErrDisplay_T ))


void DisplayError(U8 mu8ErrCode, U8 mu8Cmd )
{
    U8 i;
    Action_T pAction = NULL;

    for( i = 0; i < SZ_LIST ; i++ )
    {
        if( ErrDisplayList[ i ].Id == mu8ErrCode )
        {
            pAction = ErrDisplayList[ i ].DispAction;
            if( pAction != NULL )
            {
                // ErrCommon();
                pAction( mu8Cmd );
            }
            //break;
        }
    }
}


/* Error occurred --> LED Blink */
/* Why use Hal_TurnOnOFFLED function instead of BlinkLED function? */
/* Because The blink function is performed in the DisplayError function.*/

/* Cold Water TH Error */
static void ErrTempCold(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_4, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_4, SEG_ON);
}

/* Hot Water TH Error */
static void ErrTempHot(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_4, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_5, SEG_ON);
}

static void ErrTempOverHot(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_4, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
}

static void ErrColdLow(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
}

static void ErrColdMide(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
}

static void ErrColdHigh(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_3, SEG_ON);
}

/* PUMP Error */
static void ErrBoostPump(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_9, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_5, SEG_ON);
}

static void ErrDrainPump(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_6, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
}

static void ErrCirculatePump(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_6, SEG_ON);
}

static void ErrWaterOutage(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_9, SEG_ON);
}

/* Feed valve Error */
static void ErrColdFeed(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_2, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
}

/* complex Error */
static void ErrColdComplexLowMide(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_5, SEG_ON);
}


static void ErrRoomLow(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
}

static void ErrRoomHigh(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_3, SEG_ON);
}

/* Feed valve Error */
static void ErrRoomFeed(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
}

static void ErrHotHigh(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_3, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_3, SEG_ON);
}


/* Leak Error */
static void ErrLeak(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_0, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_1, SEG_ON);
}

/* Ambient Sensor Error */
static void ErrTempAmb(U8 mu8Cmd)
{
    // HAL_TurnOnOffSeg(SEG4, PROTOCOL_SEG_LED_DATA_OFF, SEG_OFF);
    // HAL_TurnOnOffSeg(SEG3, PROTOCOL_SEG_LED_DATA_E, SEG_ON);
    // HAL_TurnOnOffSeg(SEG2, PROTOCOL_SEG_LED_DATA_4, SEG_ON);
    // HAL_TurnOnOffSeg(SEG1, PROTOCOL_SEG_LED_DATA_3, SEG_ON);
}

