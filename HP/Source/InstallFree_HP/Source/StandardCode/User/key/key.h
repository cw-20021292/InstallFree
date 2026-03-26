#ifndef __KEY_H__
#define __KEY_H__

#include "hal_key.h"

void InitKey(void);

/* SINGLE KEY */
#define  K_NONE                 HAL_KEY_NONE
#define  K_COLD                 HAL_KEY_NONE

#define  K_HOT                  HAL_KEY_1
#define  K_ROOM                 HAL_KEY_2
#define  K_AMOUNT               HAL_KEY_3
#define  K_HOT_LOCK             HAL_KEY_4
//#define  K_HOT_LOCK       HAL_KEY_6  -> Lever(Right)�� ����� #define HAL_KEY_WATER_OUT       HAL_KEY_6
//#define  K_SAVE           HAL_KEY_7  -> Lever(Left)����� #define HAL_KEY_HOT_WATER_OUT   HAL_KEY_7

//#define  K_ALL          HAL_KEY_ALL

#define K_EXTRACT               HAL_KEY_5
/************************************ MULTI KEY ************************************/
//#define K_VERSION       ( K_COLD | K_HOT )
#define K_SMART_UNUSED_SAVE  ( K_ROOM | K_AMOUNT | K_HOT_LOCK  )
#define K_MUTE               ( K_ROOM | K_AMOUNT )
#define K_ALTITUDE           ( K_HOT  | K_AMOUNT )
#define K_LOCK_ALL           ( K_ROOM | K_HOT_LOCK )
#define K_HOT_OFF            ( K_ROOM | K_HOT  | K_AMOUNT ) 
#define K_COLD_OFF           ( K_ROOM | K_COLD | K_AMOUNT ) 
#define K_MEMENTO            ( K_ROOM | K_COLD | K_HOT ) 
#define K_COLD_WEAK          ( K_ROOM | K_COLD | K_HOT_LOCK | K_AMOUNT)
#define K_TEST_UV            ( K_HOT  | K_COLD | K_AMOUNT )     // UV TEST 
// #define K_SAVE               ( K_HOT  | K_ROOM ) �������� ����, ��ħ��� ��� ����

/* WIFI */
#define K_WIFI_PARING        ( K_COLD  | K_ROOM )   
#define K_WIFI_POWER         ( K_COLD  | K_AMOUNT ) 

/* FORCE ALL TANK DRAINE */
#define K_ALL_TANK_DRAIN     ( K_HOT_LOCK | K_HOT | K_AMOUNT )

/* FLUSHING SHORT MODE */
#define K_FLUSHING_SHORT     ( K_HOT | K_COLD | K_ROOM | K_AMOUNT )

/* FLUSHING END Immediately */
#define K_FLUSHING_COMPLETE  ( K_HOT_LOCK | K_AMOUNT ) 

/* FLUSHING FORCE SETTING */
#define K_FLUSHING_FORCE_MODE ( K_HOT  | K_ROOM )  

/* FLUSHING Filter Type Change */
#define K_FILTER_TYPE_CHANGE  ( K_HOT_LOCK | K_COLD ) 

/* FUNCTION KEY - TEST */
#define K_TEST_FCT           ( K_COLD | K_HOT )                  // TEST MAIN PBA
#define K_TEST_FRONT         ( K_COLD | K_AMOUNT | K_HOT_LOCK )  // TEST EOL - FRONT
//#define K_TEST_WATER_LEVEL   ( K_COLD | K_HOT_LOCK )             // TEST EOL - WATER_LEVEL
//#define K_TEST_KEY           ( K_SAVE | K_HOT_LOCK )             // TEST EOL - KEY
#define K_TEST_EOL           ( K_HOT  | K_HOT_LOCK )             // TEST EOL - LOAD 
#define K_TEST_TS            ( K_ROOM | K_COLD | K_HOT_LOCK )    // TEST MODE ( TIME SHORT ) 

/* AGING TEST */
#define K_TEST_AGING         ( K_HOT | K_COLD | K_HOT_LOCK )     // TEST MODE ( Available only use IN TIME SHORT ) 
#define K_TEST_AGING_DISPLAY ( K_ROOM | K_HOT | K_HOT_LOCK )     // Display number of aging cycle

/* Reliability Test */
/* cold repeat TEST */
#define K_TEST_COLD_OUT_REPEAT     ( K_HOT | K_COLD | K_ROOM | K_HOT_LOCK ) // COLD WATER OUT REPEAT INFINITE
/* hot repeat TEST */
#define K_TEST_HOT_OUT_REPEAT      ( K_HOT | K_COLD | K_AMOUNT | K_HOT_LOCK ) // HOT WATER OUT REPEAT INFINITE
/* cold+hot+room+warm40 repeat TEST */
#define K_TEST_ALL_OUT_REPEAT      ( K_HOT | K_AMOUNT | K_ROOM | K_HOT_LOCK ) // COLD + HOT + ROOM + WARM40 WATER OUT REPEAT INFINITE






/* EvnetFlag Index */
#define  KEY_EVENT_PUSHED_SHORT     0x01
#define  KEY_EVENT_PUSHED_LONG_7S   0x02
//#define  KEY_EVENT_PUSHED_LONG_5S   0x04
#define  KEY_EVENT_PUSHED_LONG_3S   0x04
#define  KEY_EVENT_PUSHED_LONG_2S   0x08
#define  KEY_EVENT_PUSHED_LONG_1S   0x10
#define  KEY_EVENT_POP              0x20
#define  KEY_EVENT_ALL              0x1F


/* Event Timeout condition @10ms */
#define  EVENT_TIME_OUT_7S          700     // 7sec
//#define  EVENT_TIME_OUT_5S          500     // 5sec
#define  EVENT_TIME_OUT_3S          300     // 3sec
#define  EVENT_TIME_OUT_2S          200     // 2sec
#define  EVENT_TIME_OUT_1S          100     // 1sec
#define  EVENT_TIME_OUT_SHORT        10     // 100ms
#define  MAX_EVENT_TIME_OUT         EVENT_TIME_OUT_7S


/* Status */
typedef enum
{
    KEY_STATUS_NONE,
    KEY_STATUS_PUSHED, 
    KEY_STATUS_POP,    
    KEY_STATUS_TIME_OUT
}KeyStatus_T;


void SetKeyEventFlag(U8 mu8Event );
void ClearKeyEventFlag(U8 mu8Event );
U8 IsSetKeyEventFlag( U8 mu8Event );
void ProcessScanKey(void);
U16 GetKeyVal( void );
U16 GetKeyPopVal( void );
U8 GetKeyStatus( void );
U16 GetKeyPushedTime( void );


#endif /* __KEY_H__ */
