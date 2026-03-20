/// @file     Mgr_DC_Pump.h
/// @date     2026/03/20
/// @author
/// @brief    DC Pump Manager - 펌프 동작 의사결정 관리 Header
///
/// @details  Reed Switch Manager와 Water Level Sensor Manager의 상태를
///           2차원 의사결정 테이블로 참조하여 DC Pump의 ON/OFF를 결정한다.
///
///           [결정 로직]
///           REED SW ON  + 수위 정상 -> PUMP ON
///           REED SW ON  + 저수위    -> PUMP OFF
///           REED SW OFF + (모든 수위) -> PUMP OFF


#ifndef _USER_MANAGER_H_
#define _USER_MANAGER_H_


/*  Mgr DC Pump 사용법
    => Get_PumpStatus()   // 현재 펌프 제어 명령 상태 반환
                                 //   ON  : 펌프 ON 명령 중
                                 //   OFF : 펌프 OFF 명령 중
*/


// 제어 대상 DC Pump ID - 하드웨어 설정에 맞게 변경 가능
#ifndef MGR_DC_PUMP_MAIN_ID
#define MGR_DC_PUMP_MAIN_ID             DC_PUMP_ID_1
#endif


U8  Get_PumpStatus(void);

void Mgr_DC_Pump_Module_Initialize(void);
void Manager(void);


#endif
