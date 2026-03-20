/// @file     Lib_Water_Debug.c
/// @date     2025/09/29
/// @author   Jaejin Ham
/// @brief    디버깅 동작 제어 file

#include "Global_Header.h"


#if (DEBUG_MONITORING_USE == USE)

U16 gu168Debug_ControlTimer = 0;

U8 gu8DebugDataSetOk = 0;
U8 gu8DebugTxReady = 0;

// UART 통신 방식 Comp
U8 au8Debug_TxData[DEBUG_DATA_LENGTH];
U8 au8Debug_RxData[DEBUG_DATA_LENGTH];

U8 gu8Debug_Tx_Count = 0;


/// @brief      정수기 debug 동작 관련 초기화
/// @details    정수기 debug 동작과 관련된 변수를 모두 초기화 시킨다
/// @param      void
/// @return     void
void Lib_Water_Debug_Initialize(void)
{
    gu168Debug_ControlTimer = 0;

    gu8DebugDataSetOk = CLEAR;
    gu8DebugTxReady = SET;

    // UART 통신 방식 Comp
    MEMSET(au8Debug_TxData, 0x00, sizeof(au8Debug_TxData));
    MEMSET(au8Debug_RxData, 0x00, sizeof(au8Debug_RxData));

    gu8Debug_Tx_Count = 0;
}


/// @brief      정수기 debug 제어 시간 카운터(@1ms interrupt)
/// @details    정수기 debug를 제어 시간 마다 제어하기 위해 제어 시간을 카운트 한다
/// @param      void
/// @return     void
void Water_Debug_ControlTimer(void)
{
    if (gu168Debug_ControlTimer < DEBUG_CONTROL_TIME_PERIOD)
    {
        gu168Debug_ControlTimer++;
    }
}


/// @brief      정수기 debug 제어 함수(@While Loop)
/// @details    While문 안에서 정수기 debug 제어 동작을 한다
/// @param      void
/// @return     void
void Lib_Water_Debug_Control(void)
{
    if (gu168Debug_ControlTimer >= DEBUG_CONTROL_TIME_PERIOD)
    {   // 500ms
        if (gu8DebugDataSetOk == SET)
        {
            if (gu8DebugTxReady == SET)
            {
                gu168Debug_ControlTimer = 0;
                gu8DebugTxReady = CLEAR;
                Water_Debug_Tx_Communication();
            }
        }
    }
}

/// @brief      Water Debug 제어 Data 세팅 함수
/// @details    Water Debug 제어 Data를 설정한다
/// @param      mu8Hz : 제어하고자 하는 Comp Hz
/// @return     void
void Set_Water_Debug_Data(void)
{
    U8 mu8BootEnd = 0;

    mu8BootEnd = Get_BootComplete();

    if (mu8BootEnd >= SET)
    {
        gu8DebugDataSetOk = SET;
    }
}


/// @brief      Water Debug TXD 처리 함수
/// @details    Water Debug UART 통신간 송신 데이터를 처리한다
/// @param      void
/// @return     void
void Water_Debug_Tx_Communication(void)
{
    Water_Debug_UART_Tx_Start();
}


/// @brief      Water Debug Uart Rxd Interrupt 처리 함수(@UART Rxd Interrupt)
/// @details    Water Debug UART 통신시 Rx Interrupt가 발생했을 때 수신 데이터를 처리한다
/// @param      void
/// @return     void
void UART_ISR_Water_Debug_Rx(void)
{
    U8 mu8RxBuff = 0;

    mu8RxBuff = WATER_DEBUG_UART_RXD;
}


/// @brief      Water Debug Uart Tx 시작 함수
/// @details    Water Debug UART 통신간 TXD를 시작 처리한다
/// @param      void
/// @return     void
void Water_Debug_UART_Tx_Start(void)
{
    Make_Water_Debug_Tx_Packet();
    WATER_DEBUG_UART_TXD = au8Debug_TxData[0];
    gu8Debug_Tx_Count = 1;
}


/// @brief      Water Debug Uart Tx Packet 구성 함수
/// @details    Water Debug 통신하는 Tx 데이터 Packet을 구성한다
/// @param      void
/// @return     void
void Make_Water_Debug_Tx_Packet(void)
{
    F32 mf32TempBuf1 = 0.0f;
    F32 mf32TempBuf2 = 0.0f;
    F32 mf32TempBuf3 = 0.0f;
    F32 mf32TempBuf4 = 0.0f;
    F32 mf32TempBuf5 = 0.0f;
    F32 mf32TempBuf6 = 0.0f;
    F32 mf32TempBuf7 = 0.0f;
    F32 mf32TempBuf8 = 0.0f;
    F32 mf32TempBuf9 = 0.0f;
    F32 mf32TempBuf10 = 0.0f;

    U8 mu8DC_Power1 = 0;
    U8 mu8DC_Power2 = 0;
    U8 mu8DC_Power3 = 0;
    U8 mu8DC_Power4 = 0;
    U8 mu8DC_Power5 = 0;
    U8 mu8DC_Power6 = 0;
    U8 mu8DC_Power7 = 0;
    U8 mu8DC_Power8 = 0;
    U8 mu8DC_Power9 = 0;
    U8 mu8DC_Power10 = 0;
    U8 mu8DC_Power11 = 0;
    U8 mu8DC_Power12 = 0;
    U8 mu8DC_Power13 = 0;
    U8 mu8DC_Power14 = 0;
    U8 mu8DC_Power15 = 0;
    U8 mu8DC_Power16 = 0;
    U8 mu8DC_Power17 = 0;
    U8 mu8DC_Power18 = 0;
    U8 mu8DC_Power19 = 0;
    U8 mu8DC_Power20 = 0;
    U8 mu8DC_Power21 = 0;
    U8 mu8DC_Power22 = 0;
    U8 mu8DC_Power23 = 0;
    U8 mu8DC_Power24 = 0;
    U8 mu8DC_Power25 = 0;
    U8 mu8DC_Power26 = 0;
    U8 mu8DC_Power27 = 0;
    U8 mu8DC_Power28 = 0;
    U8 mu8DC_Power29 = 0;
    U8 mu8DC_Power30 = 0;

    I8 mai8TempBuf[5] = {0, };

    mf32TempBuf1  = DEBUG_GET_TEMP_1;
    mf32TempBuf2  = DEBUG_GET_TEMP_2;
    mf32TempBuf3  = DEBUG_GET_TEMP_3;
    mf32TempBuf4  = DEBUG_GET_TEMP_4;
    mf32TempBuf5  = DEBUG_GET_TEMP_5;
    mf32TempBuf6  = DEBUG_GET_TEMP_6;
    mf32TempBuf7  = DEBUG_GET_TEMP_7;
    mf32TempBuf8  = DEBUG_GET_TEMP_8;
    mf32TempBuf9  = DEBUG_GET_TEMP_9;
    mf32TempBuf10 = DEBUG_GET_TEMP_10;

    mu8DC_Power1  = DEBUG_GET_POWER_1;
    mu8DC_Power2  = DEBUG_GET_POWER_2;
    mu8DC_Power3  = DEBUG_GET_POWER_3;
    mu8DC_Power4  = DEBUG_GET_POWER_4;
    mu8DC_Power5  = DEBUG_GET_POWER_5;
    mu8DC_Power6  = DEBUG_GET_POWER_6;
    mu8DC_Power7  = DEBUG_GET_POWER_7;
    mu8DC_Power8  = DEBUG_GET_POWER_8;
    mu8DC_Power9  = DEBUG_GET_POWER_9;
    mu8DC_Power10 = DEBUG_GET_POWER_10;
    mu8DC_Power11 = DEBUG_GET_POWER_11;
    mu8DC_Power12 = DEBUG_GET_POWER_12;
    mu8DC_Power13 = DEBUG_GET_POWER_13;
    mu8DC_Power14 = DEBUG_GET_POWER_14;
    mu8DC_Power15 = DEBUG_GET_POWER_15;
    mu8DC_Power16 = DEBUG_GET_POWER_16;
    mu8DC_Power17 = DEBUG_GET_POWER_17;
    mu8DC_Power18 = DEBUG_GET_POWER_18;
    mu8DC_Power19 = DEBUG_GET_POWER_19;
    mu8DC_Power20 = DEBUG_GET_POWER_20;
    mu8DC_Power21 = DEBUG_GET_POWER_21;
    mu8DC_Power22 = DEBUG_GET_POWER_22;
    mu8DC_Power23 = DEBUG_GET_POWER_23;
    mu8DC_Power24 = DEBUG_GET_POWER_24;
    mu8DC_Power25 = DEBUG_GET_POWER_25;
    mu8DC_Power26 = DEBUG_GET_POWER_26;
    mu8DC_Power27 = DEBUG_GET_POWER_27;
    mu8DC_Power28 = DEBUG_GET_POWER_28;
    mu8DC_Power29 = DEBUG_GET_POWER_29;
    mu8DC_Power30 = DEBUG_GET_POWER_30;

    // 패킷 생성
    au8Debug_TxData[0] = DEBUG_STX;                         // STX

    // 온도 데이터 5byte X 6 = 30byte
    // 1번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf1);

    if (mf32TempBuf1 >= 0.0f)
    {
        if (mf32TempBuf1 >= 10.0f)
        {
            au8Debug_TxData[1] = '+';
            au8Debug_TxData[2] = mai8TempBuf[0];
            au8Debug_TxData[3] = mai8TempBuf[1];
            au8Debug_TxData[4] = mai8TempBuf[2];
            au8Debug_TxData[5] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[1] = '+';
            au8Debug_TxData[2] = '0';
            au8Debug_TxData[3] = mai8TempBuf[0];
            au8Debug_TxData[4] = mai8TempBuf[1];
            au8Debug_TxData[5] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf1 <= -10.0f)
        {
            au8Debug_TxData[1] = mai8TempBuf[0];
            au8Debug_TxData[2] = mai8TempBuf[1];
            au8Debug_TxData[3] = mai8TempBuf[2];
            au8Debug_TxData[4] = mai8TempBuf[3];
            au8Debug_TxData[5] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[1] = mai8TempBuf[0];
            au8Debug_TxData[2] = '0';
            au8Debug_TxData[3] = mai8TempBuf[1];
            au8Debug_TxData[4] = mai8TempBuf[2];
            au8Debug_TxData[5] = mai8TempBuf[3];
        }
    }

    // 2번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf2);

    if (mf32TempBuf2 >= 0.0f)
    {
        if (mf32TempBuf2 >= 10.0f)
        {
            au8Debug_TxData[6] = '+';
            au8Debug_TxData[7] = mai8TempBuf[0];
            au8Debug_TxData[8] = mai8TempBuf[1];
            au8Debug_TxData[9] = mai8TempBuf[2];
            au8Debug_TxData[10] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[6] = '+';
            au8Debug_TxData[7] = '0';
            au8Debug_TxData[8] = mai8TempBuf[0];
            au8Debug_TxData[9] = mai8TempBuf[1];
            au8Debug_TxData[10] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf2 <= -10.0f)
        {
            au8Debug_TxData[6] = mai8TempBuf[0];
            au8Debug_TxData[7] = mai8TempBuf[1];
            au8Debug_TxData[8] = mai8TempBuf[2];
            au8Debug_TxData[9] = mai8TempBuf[3];
            au8Debug_TxData[10] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[6] = mai8TempBuf[0];
            au8Debug_TxData[7] = '0';
            au8Debug_TxData[8] = mai8TempBuf[1];
            au8Debug_TxData[9] = mai8TempBuf[2];
            au8Debug_TxData[10] = mai8TempBuf[3];
        }
    }

    // 3번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf3);

    if (mf32TempBuf3 >= 0.0f)
    {
        if (mf32TempBuf3 >= 10.0f)
        {
            au8Debug_TxData[11] = '+';
            au8Debug_TxData[12] = mai8TempBuf[0];
            au8Debug_TxData[13] = mai8TempBuf[1];
            au8Debug_TxData[14] = mai8TempBuf[2];
            au8Debug_TxData[15] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[11] = '+';
            au8Debug_TxData[12] = '0';
            au8Debug_TxData[13] = mai8TempBuf[0];
            au8Debug_TxData[14] = mai8TempBuf[1];
            au8Debug_TxData[15] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf3 <= -10.0f)
        {
            au8Debug_TxData[11] = mai8TempBuf[0];
            au8Debug_TxData[12] = mai8TempBuf[1];
            au8Debug_TxData[13] = mai8TempBuf[2];
            au8Debug_TxData[14] = mai8TempBuf[3];
            au8Debug_TxData[15] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[11] = mai8TempBuf[0];
            au8Debug_TxData[12] = '0';
            au8Debug_TxData[13] = mai8TempBuf[1];
            au8Debug_TxData[14] = mai8TempBuf[2];
            au8Debug_TxData[15] = mai8TempBuf[3];
        }
    }

    // 4번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf4);

    if (mf32TempBuf4 >= 0.0f)
    {
        if (mf32TempBuf4 >= 10.0f)
        {
            au8Debug_TxData[16] = '+';
            au8Debug_TxData[17] = mai8TempBuf[0];
            au8Debug_TxData[18] = mai8TempBuf[1];
            au8Debug_TxData[19] = mai8TempBuf[2];
            au8Debug_TxData[20] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[16] = '+';
            au8Debug_TxData[17] = '0';
            au8Debug_TxData[18] = mai8TempBuf[0];
            au8Debug_TxData[19] = mai8TempBuf[1];
            au8Debug_TxData[20] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf4 <= -10.0f)
        {
            au8Debug_TxData[16] = mai8TempBuf[0];
            au8Debug_TxData[17] = mai8TempBuf[1];
            au8Debug_TxData[18] = mai8TempBuf[2];
            au8Debug_TxData[19] = mai8TempBuf[3];
            au8Debug_TxData[20] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[16] = mai8TempBuf[0];
            au8Debug_TxData[17] = '0';
            au8Debug_TxData[18] = mai8TempBuf[1];
            au8Debug_TxData[19] = mai8TempBuf[2];
            au8Debug_TxData[20] = mai8TempBuf[3];
        }
    }

    // 5번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf5);

    if (mf32TempBuf5 >= 0.0f)
    {
        if (mf32TempBuf5 >= 10.0f)
        {
            au8Debug_TxData[21] = '+';
            au8Debug_TxData[22] = mai8TempBuf[0];
            au8Debug_TxData[23] = mai8TempBuf[1];
            au8Debug_TxData[24] = mai8TempBuf[2];
            au8Debug_TxData[25] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[21] = '+';
            au8Debug_TxData[22] = '0';
            au8Debug_TxData[23] = mai8TempBuf[0];
            au8Debug_TxData[24] = mai8TempBuf[1];
            au8Debug_TxData[25] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf5 <= -10.0f)
        {
            au8Debug_TxData[21] = mai8TempBuf[0];
            au8Debug_TxData[22] = mai8TempBuf[1];
            au8Debug_TxData[23] = mai8TempBuf[2];
            au8Debug_TxData[24] = mai8TempBuf[3];
            au8Debug_TxData[25] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[21] = mai8TempBuf[0];
            au8Debug_TxData[22] = '0';
            au8Debug_TxData[23] = mai8TempBuf[1];
            au8Debug_TxData[24] = mai8TempBuf[2];
            au8Debug_TxData[25] = mai8TempBuf[3];
        }
    }

    // 6번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf6);

    if (mf32TempBuf6 >= 0.0f)
    {
        if (mf32TempBuf6 >= 10.0f)
        {
            au8Debug_TxData[26] = '+';
            au8Debug_TxData[27] = mai8TempBuf[0];
            au8Debug_TxData[28] = mai8TempBuf[1];
            au8Debug_TxData[29] = mai8TempBuf[2];
            au8Debug_TxData[30] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[26] = '+';
            au8Debug_TxData[27] = '0';
            au8Debug_TxData[28] = mai8TempBuf[0];
            au8Debug_TxData[29] = mai8TempBuf[1];
            au8Debug_TxData[30] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf6 <= -10.0f)
        {
            au8Debug_TxData[26] = mai8TempBuf[0];
            au8Debug_TxData[27] = mai8TempBuf[1];
            au8Debug_TxData[28] = mai8TempBuf[2];
            au8Debug_TxData[29] = mai8TempBuf[3];
            au8Debug_TxData[30] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[26] = mai8TempBuf[0];
            au8Debug_TxData[27] = '0';
            au8Debug_TxData[28] = mai8TempBuf[1];
            au8Debug_TxData[29] = mai8TempBuf[2];
            au8Debug_TxData[30] = mai8TempBuf[3];
        }
    }

    // 7번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf7);

    if (mf32TempBuf7 >= 0.0f)
    {
        if (mf32TempBuf7 >= 10.0f)
        {
            au8Debug_TxData[31] = '+';
            au8Debug_TxData[32] = mai8TempBuf[0];
            au8Debug_TxData[33] = mai8TempBuf[1];
            au8Debug_TxData[34] = mai8TempBuf[2];
            au8Debug_TxData[35] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[31] = '+';
            au8Debug_TxData[32] = '0';
            au8Debug_TxData[33] = mai8TempBuf[0];
            au8Debug_TxData[34] = mai8TempBuf[1];
            au8Debug_TxData[35] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf7 <= -10.0f)
        {
            au8Debug_TxData[31] = mai8TempBuf[0];
            au8Debug_TxData[32] = mai8TempBuf[1];
            au8Debug_TxData[33] = mai8TempBuf[2];
            au8Debug_TxData[34] = mai8TempBuf[3];
            au8Debug_TxData[35] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[31] = mai8TempBuf[0];
            au8Debug_TxData[32] = '0';
            au8Debug_TxData[33] = mai8TempBuf[1];
            au8Debug_TxData[34] = mai8TempBuf[2];
            au8Debug_TxData[35] = mai8TempBuf[3];
        }
    }

    // 8번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf8);

    if (mf32TempBuf8 >= 0.0f)
    {
        if (mf32TempBuf8 >= 10.0f)
        {
            au8Debug_TxData[36] = '+';
            au8Debug_TxData[37] = mai8TempBuf[0];
            au8Debug_TxData[38] = mai8TempBuf[1];
            au8Debug_TxData[39] = mai8TempBuf[2];
            au8Debug_TxData[40] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[36] = '+';
            au8Debug_TxData[37] = '0';
            au8Debug_TxData[38] = mai8TempBuf[0];
            au8Debug_TxData[39] = mai8TempBuf[1];
            au8Debug_TxData[40] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf8 <= -10.0f)
        {
            au8Debug_TxData[36] = mai8TempBuf[0];
            au8Debug_TxData[37] = mai8TempBuf[1];
            au8Debug_TxData[38] = mai8TempBuf[2];
            au8Debug_TxData[39] = mai8TempBuf[3];
            au8Debug_TxData[40] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[36] = mai8TempBuf[0];
            au8Debug_TxData[37] = '0';
            au8Debug_TxData[38] = mai8TempBuf[1];
            au8Debug_TxData[39] = mai8TempBuf[2];
            au8Debug_TxData[40] = mai8TempBuf[3];
        }
    }

    // 9번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf9);

    if (mf32TempBuf9 >= 0.0f)
    {
        if (mf32TempBuf9 >= 10.0f)
        {
            au8Debug_TxData[41] = '+';
            au8Debug_TxData[42] = mai8TempBuf[0];
            au8Debug_TxData[43] = mai8TempBuf[1];
            au8Debug_TxData[44] = mai8TempBuf[2];
            au8Debug_TxData[45] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[41] = '+';
            au8Debug_TxData[42] = '0';
            au8Debug_TxData[43] = mai8TempBuf[0];
            au8Debug_TxData[44] = mai8TempBuf[1];
            au8Debug_TxData[45] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf9 <= -10.0f)
        {
            au8Debug_TxData[41] = mai8TempBuf[0];
            au8Debug_TxData[42] = mai8TempBuf[1];
            au8Debug_TxData[43] = mai8TempBuf[2];
            au8Debug_TxData[44] = mai8TempBuf[3];
            au8Debug_TxData[45] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[41] = mai8TempBuf[0];
            au8Debug_TxData[42] = '0';
            au8Debug_TxData[43] = mai8TempBuf[1];
            au8Debug_TxData[44] = mai8TempBuf[2];
            au8Debug_TxData[45] = mai8TempBuf[3];
        }
    }

    // 10번째 온도 센서 온도
    MEMSET(mai8TempBuf, 0x00, sizeof(mai8TempBuf));
    SPRINTF(mai8TempBuf, "%.1f", mf32TempBuf10);

    if (mf32TempBuf10 >= 0.0f)
    {
        if (mf32TempBuf10 >= 10.0f)
        {
            au8Debug_TxData[46] = '+';
            au8Debug_TxData[47] = mai8TempBuf[0];
            au8Debug_TxData[48] = mai8TempBuf[1];
            au8Debug_TxData[49] = mai8TempBuf[2];
            au8Debug_TxData[50] = mai8TempBuf[3];
        }
        else
        {
            au8Debug_TxData[46] = '+';
            au8Debug_TxData[47] = '0';
            au8Debug_TxData[48] = mai8TempBuf[0];
            au8Debug_TxData[49] = mai8TempBuf[1];
            au8Debug_TxData[50] = mai8TempBuf[2];
        }
    }
    else
    {
        if (mf32TempBuf10 <= -10.0f)
        {
            au8Debug_TxData[46] = mai8TempBuf[0];
            au8Debug_TxData[47] = mai8TempBuf[1];
            au8Debug_TxData[48] = mai8TempBuf[2];
            au8Debug_TxData[49] = mai8TempBuf[3];
            au8Debug_TxData[50] = mai8TempBuf[4];
        }
        else
        {
            au8Debug_TxData[46] = mai8TempBuf[0];
            au8Debug_TxData[47] = '0';
            au8Debug_TxData[48] = mai8TempBuf[1];
            au8Debug_TxData[49] = mai8TempBuf[2];
            au8Debug_TxData[50] = mai8TempBuf[3];
        }
    }

    // 부하 데이터 30Byte
    au8Debug_TxData[51] = mu8DC_Power1  | 0x30;
    au8Debug_TxData[52] = mu8DC_Power2  | 0x30;
    au8Debug_TxData[53] = mu8DC_Power3  | 0x30;
    au8Debug_TxData[54] = mu8DC_Power4  | 0x30;
    au8Debug_TxData[55] = mu8DC_Power5  | 0x30;
    au8Debug_TxData[56] = mu8DC_Power6  | 0x30;
    au8Debug_TxData[57] = mu8DC_Power7  | 0x30;
    au8Debug_TxData[58] = mu8DC_Power8  | 0x30;
    au8Debug_TxData[59] = mu8DC_Power9  | 0x30;
    au8Debug_TxData[60] = mu8DC_Power10 | 0x30;
    au8Debug_TxData[61] = mu8DC_Power11 | 0x30;
    au8Debug_TxData[62] = mu8DC_Power12 | 0x30;
    au8Debug_TxData[63] = mu8DC_Power13 | 0x30;
    au8Debug_TxData[64] = mu8DC_Power14 | 0x30;
    au8Debug_TxData[65] = mu8DC_Power15 | 0x30;
    au8Debug_TxData[66] = mu8DC_Power16 | 0x30;
    au8Debug_TxData[67] = mu8DC_Power17 | 0x30;
    au8Debug_TxData[68] = mu8DC_Power18 | 0x30;
    au8Debug_TxData[69] = mu8DC_Power19 | 0x30;
    au8Debug_TxData[70] = mu8DC_Power20 | 0x30;
    au8Debug_TxData[71] = mu8DC_Power21 | 0x30;
    au8Debug_TxData[72] = mu8DC_Power22 | 0x30;
    au8Debug_TxData[73] = mu8DC_Power23 | 0x30;
    au8Debug_TxData[74] = mu8DC_Power24 | 0x30;
    au8Debug_TxData[75] = mu8DC_Power25 | 0x30;
    au8Debug_TxData[76] = mu8DC_Power26 | 0x30;
    au8Debug_TxData[77] = mu8DC_Power27 | 0x30;
    au8Debug_TxData[78] = mu8DC_Power28 | 0x30;
    au8Debug_TxData[79] = mu8DC_Power29 | 0x30;
    au8Debug_TxData[80] = mu8DC_Power30 | 0x30;

    au8Debug_TxData[81] = DEBUG_ETX;                        // ETX
}


/// @brief      Water Debug Uart Txd Interrupt 처리 함수(@UART Txd Interrupt)
/// @details    Water Debug URAT 통신간 Tx Interrupt 동작을 처리한다
/// @param      void
/// @return     void
void UART_ISR_Water_Debug_Tx(void)
{
    if (gu8Debug_Tx_Count < DEBUG_DATA_LENGTH)
    {
        WATER_DEBUG_UART_TXD = au8Debug_TxData[gu8Debug_Tx_Count];
        gu8Debug_Tx_Count++;
    }
    else
    {
        gu8DebugTxReady = SET;
        gu8Debug_Tx_Count = 0;
        MEMSET(au8Debug_TxData, 0x00, sizeof(au8Debug_TxData));
    }
}


/// @brief      Water Debug Data Clear
/// @details    Water Debug 제어와 관련된 변수들을 모두 초기화 시킨다
/// @param      void
/// @return     void
void Clear_Water_Debug_Data(void)
{
    MEMSET(au8Debug_TxData, 0x00, sizeof(au8Debug_TxData));
    MEMSET(au8Debug_RxData, 0x00, sizeof(au8Debug_RxData));
}


/// @brief      Water Debug UART Error Interrupt
/// @details    Water Debug UART 통신 중 Error Interrput 발생시 처리 함수
/// @param      void
/// @return     void
void UART_ISR_Water_Debug_Rx_Error(void)
{
    U8 mu8RxBuff = 0;

    mu8RxBuff = WATER_DEBUG_UART_RXD;
    WATER_DEBUG_UART_RXD_ERROR = 0x07;
}

#endif


// Water Debug Module *******************************************************************************************

/// @brief      Water Debug Initilaize Module
/// @details    Water Debug 제어 관련 데이터를 모두 초기화 시킨다
/// @param      void
/// @return     void
void Lib_Water_Debug_Module_Initialize(void)
{
#if (DEBUG_MONITORING_USE == USE)
    Lib_Water_Debug_Initialize();
#endif
}


/// @brief      Water Debug Module in 1ms Interrupt
/// @details    Water Debug 제어 타이머를 1ms마다 카운트 시킨다
/// @param      void
/// @return     void
void Lib_Water_Debug_Module_1ms_Control(void)
{
#if (DEBUG_MONITORING_USE == USE)
    Water_Debug_ControlTimer();
#endif
}


/// @brief      Water Debug Module in While Loop
/// @details    Basic Loop의 While 문 안에서 Water Debug를 제어한다
/// @param      void
/// @return     void
void Lib_Water_Debug_Module_Control(void)
{
#if (DEBUG_MONITORING_USE == USE)
    Set_Water_Debug_Data();
    Lib_Water_Debug_Control();
#endif
}

