#ifndef __DISPLAY_LIB_H__
#define __DISPLAY_LIB_H__



#define DISP_VER_START        0    

// TIMER COUNTER 
#define TIMER_100MS    1U
#define TIMER_500MS    5U
#define TIMER_1SEC     10U
#define TIMER_2SEC     20U
#define TIMER_3SEC     30U
#define TIMER_4SEC     40U
#define TIMER_5SEC     50U
#define TIMER_6SEC     60U
#define TIMER_7SEC     70U
#define TIMER_20SEC    200U
#define TIMER_30SEC    300U
#define TIMER_20MIN    12000U
#define TIMER_60MIN    36000U

// TIMER BLINK INDEX 
#define DISP_TIMER_ID_500MS        0    
#define DISP_TIMER_ID_1SEC         1    
#define DISP_TIMER_ID_3SEC         2    
#define DISP_TIMER_ID_4SEC         3   
#define DISP_TIMER_ID_100MS        4  
#define MAX_DISP_TIMER_BLINK_ID    5


// TIMER INDEX
enum
{
    //DISP_TIMER_KEY_ICE,            
    DISP_TIMER_KEY_AMOUNT,         
    DISP_TIMER_KEY_HOT,            
    DISP_TIMER_KEY_HOT_TEMP,  
    DISP_TIMER_UVCARE,
    DISP_TIMER_COOLING_DIMMING_BLINK,
    DISP_TIMER_HEATING_DIMMING_BLINK,
    DISP_TIMER_CONFIG_TIME,       

    // DISP_TIMER_ALARM_LOCK_ALL,          
    //DISP_TIMER_ALARM_LOCK_HOT,          
    //DISP_TIMER_ALARM_LOCK_ICE,          
    //DISP_TIMER_ALARM_MAKE_OFF_ICE,      
    //DISP_TIMER_ALARM_MAKE_OFF_COLD,     

    // DISP_TIMER_ALARM_SETTING, 
    DISP_TIMER_CONFIG_AMOUNT,      
    DISP_TIMER_VERSION,             
    DISP_TIMER_MEMENTO,             
    //DISP_TIMER_SLEEP,              

    DISP_TIMER_CLOCK,              
    //DISP_TIMER_ERROR,             
    //DISP_TIMER_SETTING_MENU,        /* ?�정 메??EXIT ?�?�머 */
    //DISP_TIMER_CUSTOMER_MENU,       
    //DISP_TIMER_SOUND_MENU,          /* ?��???�정 EXIT ?�?�머 */
    //DISP_TIMER_CLOCK_MENU,       
    //DISP_TIMER_UP,                  /* SETTING - UP */
    //DISP_TIMER_DOWN,                /* SETTING - DOWN */
    //DISP_TIMER_NEXT,                /* SETTING - DOWN */

    //DISP_TIMER_WIFI_AP_ERROR,       /* WIFI - AP ERROR CODE */
    //DISP_TIMER_ON,  
    //DISP_TIMER_OFF, 
    //DISP_TIMER_SETTING_CLOCK,       

    DISP_TIMER_COLDMAKE,            
    DISP_TIMER_HOTMAKE,    
    DISP_TIMER_SEGOFF,      /* 7Segment Display "OFF" */
    DISP_TIMER_SEGON,       /* 7Segment Display "ON" */ 
    
    DISP_TIMER_HOTLOCK_SET, 
    DISP_TIMER_ALLLOCK_SET, 
    
    DISP_TIMER_HOTLOCK,    
    DISP_TIMER_ALLLOCK,
    DISP_TIMER_ICONLOCK,

    DISP_TIMER_LOW_WATER, 

    DISP_TIMER_HOW_WATER, 
    DISP_TIMER_COLD_WATER, 
    DISP_TIMER_ROOM_WATER, 

    DISP_TIMER_WATER_OUT_POINT_LEFT,
    DISP_TIMER_LED_WATER_OUT,

    DISP_TIMER_REPLACE_FILTER, 

    MAX_DISP_KEY_TIMER_ID       
};

void InitDispTimer(void);
void UpdateDisplayTimer(void);
void SetDispTimer(U8 id, U16 time);
U8 IsExpiredDispTimer(U8 id);
U8 IsExpiredDispBlinkTimer(U8 id);
U8 BlinkLED( U8 mu8OnOff, void (*pFun)(U8 mu8OnOff), U8 mu8TimerId );
U8 BlinkLEDDuty( U8 mu8OnOff, void (*pFun)(U8 mu8OnOff), U8 mu8TimerId );


#endif /* __DISPLAY_LIB_H__ */
