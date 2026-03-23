/// @file     Lib_Water_Debug.h
/// @date     2025/09/29
/// @author   Jaejin Ham
/// @brief    디버깅 동작 제어 file

#ifndef _LIB_WATER_DEBUG_H_
#define _LIB_WATER_DEBUG_H_


#define DEBUG_MONITORING_USE                        NO_USE

#if (DEBUG_MONITORING_USE == USE)                   // Debug 모니터링 기능 사용시

#define DEBUG_DATA_LENGTH                           82              // 디버깅 데이터 82Byte

// UART 통신 제어 방식 Comp
#define WATER_DEBUG_UART_TXD                        TXD3
#define WATER_DEBUG_UART_RXD                        RXD3
#define WATER_DEBUG_UART_RXD_ERROR                  SIR13
#define WATER_DEBUG_UART_START()                    R_Config_UART3_Start();
#define WATER_DEBUG_UART_STOP()                     R_Config_UART3_Stop();

// 온도 센서 데이터(10개) - -99.9 ~ +99.9도로 define될 수 있도록 배정할 것(Float형으로 값 배정할 것)
#define DEBUG_GET_TEMP_1                            Get_Temp(ADC_ID_TH_AIR)
#define DEBUG_GET_TEMP_2                            Get_Temp(ADC_ID_TH_HOT_IN)
#define DEBUG_GET_TEMP_3                            Get_Temp(ADC_ID_TH_HOT_OUT)
#define DEBUG_GET_TEMP_4                            Get_Temp(ADC_ID_TH_HEATSINK)
#define DEBUG_GET_TEMP_5                            Get_Temp(ADC_ID_TH_COOL)
#define DEBUG_GET_TEMP_6                            Get_Temp(ADC_ID_TH_HOT_BODY)
#define DEBUG_GET_TEMP_7                            0.0f
#define DEBUG_GET_TEMP_8                            0.0f
#define DEBUG_GET_TEMP_9                            0.0f
#define DEBUG_GET_TEMP_10                           0.0f

// 부하 데이터(30개) - HW 제어 Port를 배치하여 그 상태를 define(미사용은 0으로 설정)
#define DEBUG_GET_POWER_1                           GET_STATUS_BOOST_OUT()
#define DEBUG_GET_POWER_2                           0
#define DEBUG_GET_POWER_3                           0
#define DEBUG_GET_POWER_4                           0
#define DEBUG_GET_POWER_5                           0
#define DEBUG_GET_POWER_6                           0
#define DEBUG_GET_POWER_7                           0
#define DEBUG_GET_POWER_8                           0
#define DEBUG_GET_POWER_9                           0
#define DEBUG_GET_POWER_10                          0
#define DEBUG_GET_POWER_11                          0
#define DEBUG_GET_POWER_12                          0
#define DEBUG_GET_POWER_13                          0
#define DEBUG_GET_POWER_14                          0
#define DEBUG_GET_POWER_15                          0
#define DEBUG_GET_POWER_16                          0
#define DEBUG_GET_POWER_17                          0
#define DEBUG_GET_POWER_18                          0
#define DEBUG_GET_POWER_19                          0
#define DEBUG_GET_POWER_20                          0
#define DEBUG_GET_POWER_21                          0
#define DEBUG_GET_POWER_22                          0
#define DEBUG_GET_POWER_23                          0
#define DEBUG_GET_POWER_24                          0
#define DEBUG_GET_POWER_25                          0
#define DEBUG_GET_POWER_26                          0
#define DEBUG_GET_POWER_27                          0
#define DEBUG_GET_POWER_28                          0
#define DEBUG_GET_POWER_29                          0
#define DEBUG_GET_POWER_30                          0

#define DEBUG_CONTROL_TIME_PERIOD                   500             // 디버깅 제어 시간 주기 : 500ms(@1ms)

#define DEBUG_STX                                   0x02
#define DEBUG_ETX                                   0x03

void Lib_Water_Debug_Initialize(void);
void Water_Debug_ControlTimer(void);
void Lib_Water_Debug_Control(void);
void Set_Water_Debug_Data(void);
void Water_Debug_Tx_Communication(void);
void UART_ISR_Water_Debug_Rx(void);
void Water_Debug_UART_Tx_Start(void);
void Make_Water_Debug_Tx_Packet(void);
void UART_ISR_Water_Debug_Tx(void);
void Clear_Water_Debug_Data(void);
void UART_ISR_Water_Debug_Rx_Error(void);


#endif

void Lib_Water_Debug_Module_Initialize(void);
void Lib_Water_Debug_Module_1ms_Control(void);
void Lib_Water_Debug_Module_Control(void);

#endif

