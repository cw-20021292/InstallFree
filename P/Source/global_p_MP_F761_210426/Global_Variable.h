/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/

#ifndef _GLOBAL_VAR_H
#define _GLOBAL_VAR_H

/***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#define FALSE   0
#define TRUE    1

#define STX    2     //SONIX2349
#define ETX    3
#define DATA_PACKET_MAX_LENGTH    35
#define PC_DATA_PACKET_MAX_LENGTH    5


#define SETTING_ENABLE     1
#define SETTING_DISABLE    0


typedef enum
{
    LCD_DISPLAY_STARTUP = 0,
    LCD_Display_Init = 1,
    LCD_Display_STANDBY,
    LCD_Display_BUTTON_FEEDBACK,

    LCD_Display_MAIN,
    LCD_Display_EXTRACT,
    LCD_Display_SETTING,
    LCD_Display_ERROR,
    LCD_Display_POPUP,
    LCD_Display_CODY_INSPECT,
    LCD_Display_CODY_POPUP,
    LCD_Display_DEVELOPER,
    LCD_Display_DEVELOPER_POPUP,
    LCD_Display_DEBUG

}DISPLAY_STEP;






typedef enum
{
    STATE_0_STANDBY = 0,

    STATE_10_ICE_TRAY_MOVE_UP = 10,
    STATE_11_WAIT_ROOM_WATER_FULL = 11,
    STATE_12_CHECK_DRAIN_LEVEL = 12,

    STATE_20_WATER_IN_ICE_TRAY = 20,
    STATE_21_ICE_SWITCH_MOVE = 21,

    STATE_30_CALC_ICE_MAKING_TIME = 30,
    STATE_31_MAIN_ICE_MAKING = 31,

    STATE_40_ICE_TRAY_MOVE_DOWN = 40,
    STATE_41_ICE_TAKE_OFF = 41,

    STATE_50_ICE_FULL_IR_CHECK = 50,
    STATE_51_FINISH_ICE_MAKE = 51
}ICE_STEP;





typedef enum
{
    MODEL_L_TYPE,
    MODEL_R_TYPE
}MODEL_SELECT;


typedef enum
{
    STEP0_STANDBY,
    STEP1_160MIN_ON,
    STEP2_20MIN_OFF
}PUMP_RETRY_STEP;



#define LowByte(data)                   ((U8)((data) & 0xff))
#define HighByte(data)                  ((U8)(((data) >> 8) & 0xff))

#define LowWord(data)                   ((U16)((data) & 0xFFFF))
#define HighWord(data)                  ((U16)(((data) >> 16) & 0xFFFF)

#define BitRead(value, bit)             (((value) >> (bit)) & 0x01)
#define BitSet(value, bit)              ((value) |= (1UL << (bit)))
#define BitClear(value, bit)            ((value) &= ~(1UL << (bit)))
#define BitWrite(value, bit, bitvalue)  (bitvalue ? BitSet(value, bit) : BitClear(value, bit))





#define C_03_LPM    16
#define C_035_LPM   19
#define C_04_LPM    22
#define C_05_LPM    28
#define C_06_LPM    34
#define C_07_LPM    40



#define BUZZER_OFF                  0
#define BUZZER_POWER_ON             1
#define BUZZER_EFFLUENT             2
#define BUZZER_EFFLUENT_END         3
#define BUZZER_COOL_SETUP           4
#define BUZZER_COOL_CANCEL          5
#define BUZZER_SELECT               6
#define BUZZER_ERROR                7
#define BUZZER_SETUP                8
#define BUZZER_CANCEL               9
#define BUZZER_EFFLUENT_CONTINUE    10
#define BUZZER_STERILIZE_START      11
#define BUZZER_STERILIZE_END        12
#define BUZZER_AP_CONNECT           13
#define BUZZER_SERVER_CONNECT       14
#define BUZZER_MUTE                 15
#define BUZZER_MEMENTO_1            16      /* 메멘토 1 */
#define BUZZER_MEMENTO_2            17      /* 메멘토 2 */
#define BUZZER_MEMENTO_3            18      /* 메멘토 3 */
#define BUZZER_MEMENTO_4            19      /* 메멘토 4 */
#define BUZZER_MEMENTO_5            20      /* 메멘토 5 */
#define BUZZER_SETUP_MUTE           30
#define BUZZER_CANCEL_MUTE          31
#define BUZZER_MEMENTO_1_MUTE       32
#define BUZZER_MEMENTO_5_MUTE       33


#define DEV_ADDR_EEP                                  0xAE  /* Device EEPROM - ISL12026 */
#define DEV_ADDR_RTC                                  0xDE  /* Device RTC - ISL12026 */



#define KEY_HALF_CUP                                  0x06
#define KEY_ONE_CUP                                   0x05
#define KEY_TWO_CUP                                   0x03


/*..hui [20-12-18오후 5:07:21] 반컵 + 한컵 + 두컵..*/
#define LONG_KEY_PCB_TEST_MODE                        0x00

/*..hui [20-12-18오후 5:07:37] 한컵 + 두컵..*/
#define LONG_KEY_DISPLAY_TEST_MODE                    0x01

/*..hui [20-12-18오후 5:07:50] 반컵 + 한컵..*/
#define LONG_KEY_LINE_TEST_MODE_R_TYPE                0x04

/*..hui [20-12-18오후 5:07:55] 반컵 + 두컵..*/
#define LONG_KEY_LINE_TEST_MODE_L_TYPE                0x02





#define TEMPERATURE_SENSOR_OPEN                       1000
#define TEMPERATURE_SENSOR_SHORT                      20

#define TEMPERATURE_SENSOR_8BIT_OPEN                  250
#define TEMPERATURE_SENSOR_8BIT_SHORT                 5

#define TEMPERATURE_SENSOR_ERROR_CHECK_TIME           30


#define CUP_LEVEL_HALF                                1
#define CUP_LEVEL_ONE                                 2
#define CUP_LEVEL_TWO                                 4


#define PURE_WATER_SELECT                             1
#define COLD_WATER_SELECT                             2
#define HOT_WATER_SELECT                              4


//#define ROOM_LEVEL_LOW     0
//#define ROOM_LEVEL_MID     1
//#define ROOM_LEVEL_FULL    2
//#define ROOM_LEVEL_ERROR   3



#define ROOM_LEVEL_LOW                                0
#define ROOM_LEVEL_FULL                               1



/*..hui [20-1-30오후 3:41:34] 추출량 정할때 끝이 0으로 끝나지 않도록 명심~~~..*/
/*..hui [20-1-30오후 3:41:39] LCD 표시 관련..*/
#if 0
#define EXTRACT_TIME_PURE_WATER_HALF                  34
#define EXTRACT_TIME_PURE_WATER_ONE                   70
#define EXTRACT_TIME_PURE_WATER_TWO                   143
#define EXTRACT_TIME_PURE_WATER_1LITER                292
#endif

#if 0
#define EXTRACT_TIME_PURE_WATER_HALF                  36
#define EXTRACT_TIME_PURE_WATER_ONE                   77
#define EXTRACT_TIME_PURE_WATER_TWO                   152
#define EXTRACT_TIME_PURE_WATER_1LITER                313
#endif

/*..hui [21-3-9오후 4:34:22] 다시 이전으로 돌림..*/
#if 0
#define EXTRACT_TIME_PURE_WATER_HALF                  34
#define EXTRACT_TIME_PURE_WATER_ONE                   70
#define EXTRACT_TIME_PURE_WATER_TWO                   143
#define EXTRACT_TIME_PURE_WATER_1LITER                292
#endif

/*..hui [21-4-1오전 11:33:20] 상한치보다 20~30% 사이로 다시 조정..*/
#define EXTRACT_TIME_PURE_WATER_HALF                  35
#define EXTRACT_TIME_PURE_WATER_ONE                   72
#define EXTRACT_TIME_PURE_WATER_TWO                   146
#define EXTRACT_TIME_PURE_WATER_1LITER                295



#define NONE_TEST_MODE                                0x00
#define PCB_TEST_MODE                                 0x01
#define LINE_TEST_MODE                                0x02
#define DISPLAY_TEST_MODE                             0x04





/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/


#endif
