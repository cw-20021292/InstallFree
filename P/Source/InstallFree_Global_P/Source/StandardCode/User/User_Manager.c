/// @file     Mgr_DC_Pump.c
/// @date     2026/03/20
/// @author
/// @brief    DC Pump Manager - 펌프 동작 의사결정 관리
///
/// @details  Mgr_ReedSwitch, Mgr_WaterLevelSensor 두 Manager의 상태를
///           2차원 의사결정 테이블(PumpDecisionTable)로 참조하여
///           DC Pump의 ON/OFF를 결정하고 Set_DC_PumpControl()을 호출한다.
///
///           [의사결정 테이블 구조]
///           행(Row) : EReedSwMgrState_T  (REED_SW_MGR_STATE_OFF / ON)
///           열(Col) : EWaterLevelMgrState_T (WATER_LEVEL_MGR_STATE_NORMAL / LOW)
///           값(Val) : 펌프 명령 (ON / OFF)


#include "Global_Header.h"


/// @brief  DC Pump 의사결정 테이블
///         [Reed SW 상태][수위 센서 상태] -> 펌프 ON/OFF 명령
///
///                              NORMAL   LOW
///         REED_SW_OFF      {   OFF,     OFF   }   // Rule 3: Reed SW OFF -> 펌프 OFF
///         REED_SW_ON       {   ON,      OFF   }   // Rule 1: Reed SW ON + 수위 정상 -> 펌프 ON
///                                                  // Rule 2: Reed SW ON + 저수위   -> 펌프 OFF
static const U8 PumpDecisionTable[REED_SW_ID_MAX][LEVEL_ID_MAX] =
{
    /* LOW   NORMAL */
    { OFF,    OFF },        // [0][0] [0][1]
    { OFF,     ON },        // [1][0] [1][1]
};

static U8 gu8Mgr_PumpCurrentCmd = OFF;


/// @brief      DC Pump Manager 현재 펌프 명령 상태 반환 함수
/// @details    Manager가 결정한 현재 펌프 제어 명령을 반환한다
/// @param      void
/// @return     U8 : ON(1) / OFF(0)
U8 Get_PumpStatus(void)
{
    return gu8Mgr_PumpCurrentCmd;
}

U8 dbg_reed_1 = 0;
U8 dbg_reed_2 = 0;
U8 dbg_pump_out = 0;

/// @brief      DC Pump Manager 의사결정 및 펌프 제어 (내부 전용)
/// @details    두 Manager의 최신 상태를 의사결정 테이블로 참조하여 펌프 명령을 결정하고
///             Set_DC_PumpControl()을 호출한다
static void Operation(void)
{
    U8    mu8ReedSW;
    U8    mu8WaterLevel;
    U8    mu8PumpOut;

    mu8ReedSW    = (Get_ReedSW_Status(REED_SW_1_DETECT));   // 1 : 감지, 0 : 미감지
    mu8WaterLevel = (Get_ReedSW_Status(REED_SW_2_DETECT));  // 1 : 감지, 0 : 미감지

    mu8PumpOut = PumpDecisionTable[mu8ReedSW][mu8WaterLevel];

    dbg_reed_1 = mu8ReedSW;
    dbg_reed_2 = mu8WaterLevel;
    dbg_pump_out = mu8PumpOut;

    if (gu8Mgr_PumpCurrentCmd != mu8PumpOut)
    {
        gu8Mgr_PumpCurrentCmd = mu8PumpOut;
        Set_DC_PumpControl(DC_PUMP_ID_1, mu8PumpOut, 0);
    }
}

// Mgr DC Pump Module ****************************************************************************************

/// @brief      Mgr DC Pump Module Initialize
/// @details    DC Pump Manager 관련 변수를 초기화 시킨다
/// @param      void
/// @return     void
void Mgr_DC_Pump_Module_Initialize(void)
{
    gu8Mgr_PumpCurrentCmd = OFF;
}


/// @brief      Mgr DC Pump Module Control (While Loop - 스케쥴러 Item 4 등록)
/// @details    Reed Switch / Water Level Sensor Manager 상태를 갱신한 뒤
///             의사결정 테이블로 DC Pump 동작을 결정하고 제어한다
/// @param      void
/// @return     void
void Manager(void)
{
    if(Get_BootComplete() == FALSE)
    {
        return;
    }
    Operation();
}
