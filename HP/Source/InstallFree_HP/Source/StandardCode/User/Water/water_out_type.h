#ifndef __WATER_OUT_TYPE_H__
#define __WATER_OUT_TYPE_H__

#define TIME_SEC(x) ( x * 100UL )
#define TIME_100MS(x) ( x * 10UL )

#define  OUT_PROTECT_TIME     30  // 300ms @10ms

#define  SEL_WATER_ROOM         0
// #define  SEL_WATER_COLD         1
#define  SEL_WATER_HOT          2
#define  SEL_WATER_NOTHING      3

#define  MAX_WATER_ID           3    // room(hot input buffer tank), cold, hot

#define  NONE_WATER_OUT      0
#define  FIRST_WATER_OUT     1
#define  SECOND_WATER_OUT    2

#define  RETURN_IMMEDIATELY_AFTER_WATER_OUT      1   // 10ms @10ms
#define  RETURN_TIME_AFTER_WATER_OUT           500   // 5sec @10ms
#define  DEFAULT_RETURN_TIME                   700   // 7sec @10ms
#define  DEFAULT_RETURN_AMOUNT_TIME            700   // 7sec @10ms

#define  TYPE_LASTED  0x01
#define  TYPE_DAILY   0x02
#define  TYPE_TOTAL   0x04
#define  TYPE_ALL     0x07


/*************************** room direct out ****************************/
typedef struct _room_water_out_common_
{
    U8  Out;     // TRUE : Room Water Out By Flow Sensor, FALSE : Room Water Out By Tank Or Cold Water Out Or Hot Water Out
    U8  PrevOut;    
    U8  Type;                 // Room Water Out Type 1.By Flow Sesnsor, 2.Tank
    U8  TypeChangeRequest;    // TRUE: Request change the type

    // EAmountId_T  Amount;   
    U32 TargetAmount;  
    U32 PaddingAmount;  
    U32 CurrentAmount;  

    U8 OpenStep;
    U8 CloseStep;
    U16 WaitTime;

} RoomWaterOut_T;


// xx_WATER_OUT RETURN VALUE
enum
{
    WATER_OUT_GOING,
    WATER_OUT_DONE,
};
/*************************** room direct out ****************************/

#endif /* __WATER_OUT_TYPE_H__ */
