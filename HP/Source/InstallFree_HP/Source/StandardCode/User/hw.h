#ifndef __HW__
#define __HW__

#define PUMP_ON                     P14.2
#define PUMP_POWER                  P14.3
#define PUMP_IAD                    P2.0

#define V24_ON                      P14.4
#define V24_IFB                     P12.0

#define UV_LED_TANK_IAD             P2.1

#define COOLING_FAN                 P13.0
#define COOLING_FAN_IAD             P2.2

#define TH_COOL                     P2.3


#define TH_HEATER                   P2.4

#define REED_FILTER                 P12.3

#define WATER_LV_LOW                P5.4
#define WATER_LV_HIGH               P5.2

#define HEATER_ON                   P5.0

#define COMP_ON                     P7.0

#define VALVE_NOS                   P7.1
#define VALVE_FEED_IN               P7.2
#define VALVE_AMBIENT_OUT           P7.3
#define VALVE_COLD_OUT              P7.4
#define VALVE_COLD_N_HOT            P7.5
#define VALVE_WARM_OUT              P7.6
#define VALVE_HOT_OUT               P7.7

#define EEP_SDA                     P6.1
#define EEP_SDA_DIR                 PM6.1
#define EEP_SCL                     P6.0

#define BUZZER_ON                   P4.2
#define BUZZER_PWM                  P4.1       // TO07

/* LEDs */
#define LED_LOCK                    P1.2
#define LED_TOUCH_LOCK              P1.1
#define LED_AMOUNT_1                P1.3
#define LED_AMOUNT_2                P1.4
#define LED_AMOUNT_3                P6.3
#define LED_HOT_2                   P0.3
#define LED_HOT_1                   P0.2
#define LED_AMOUNT                  P0.1

/* KEYs */
#define KEY_HOT                     P5.1
#define KEY_AMBIENT                 P13.7
#define KEY_EXTRACT                 P1.0
#define KEY_AMOUNT                  P0.0

/* WATER LEVEL */
#define HOT_TANK_LV                 P11.0
#define HOT_TANK_LV_FB              P2.5

#endif