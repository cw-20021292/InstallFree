/// @file     Basic_Loop.c
/// @date     2025/02/25
/// @author   Jaejin Ham, Hyunho Kang
/// @brief    기본 동작 함수  File


#include "Global_Header.h"


/*  코드 중 사용하지 않는 함수들은 모두 주석 처리하여 미사용 처리 시킨다    */

U16 gu16BootTime = 0;
U8 gu8BootComplete = 0;


/// @brief      모든 Fuction Initialize(프로그램 시작시 Initial)
/// @details    프로그램 동작 시작 전 동작과 관련된 모든 변수들을 초기화 시킨다
/// @param      void
/// @return     void
void Base_Initialize(void)
{
// * Hal (HW) *********************************************************************************
    // Input **********************************************************************************
    Drv_ADC_Module_Initialize();            // ADC 데이터 모두 초기화
    Drv_ReedSW_Module_Initialize();         // Reed SW 제어 관련 초기화
    Drv_RTC_Module_Initialize();            // RTC 관련 초기화
    Drv_LevelSensor_Module_Initialize();    // 수위 센서 관련 초기화
    Drv_Buzzer_Module_Initialize();         // 부저음 제어 관련 초기화
    // Drv_DC_Fan_Module_Initialize();         // DC FAN 제어 관련 초기화
    Drv_DC_Pump_Module_Initialize();        // DC Pump 제어 관련 초기화
    Drv_ColdTH_Module_Initialize();         // 냉수 온도 센서 전원 제어 관련 초기화
    Drv_UV_Module_Initialize();             // UV 제어 관련 초기화
    Drv_Valve_Module_Initialize();          // 일반 밸브 제어 관련 초기화
    Drv_Heater_Module_Initialize();         // 일반 히터 관련 초기화
    // Drv_BLDC_Comp_Module_Initialize();      // BLDC Comp 제어 관련 초기화
    // Drv_Comp_Module_Initialize();           // 정속형 Comp 제어 관련 초기화
   
// * Lib (Function) ***************************************************************************
    Lib_ADC_Module_Initialize();            // AD Convert 동작 관련 초기화
    Lib_OperatingMode_Module_Initialize();  // 동작 모드 제어 관련 초기화
    Lib_TimeScheduler_Module_Initialize();  // Time Scheduler 관련 초기화
    Lib_WaterError_Module_Initialize();     // 정수기 에러 체크 제어 관련 초기화
    Lib_WaterLevel_Module_Initialize();     // 수위 감지 제어 관련 초기화
    Lib_Effluent_Module_Initialize();       // 추출 제어 관련 초기화
    Lib_Heater_Module_Initialize();         // 히터 동작 관련 초기화
    // Lib_NormalComp_Module_Initialize();     // 정속형 Comp 제어 관련 초기화
    // Lib_BLDC_Comp_Module_Initialize();      // BLDC Comp 제어 관련 초기화

// * 기타 **************************************************************************************
    Boot_Initialize();

    /* User */
    InitFlushing();
}


/// @brief      Base Interval Timer(in 1ms Timer Interrupt)
/// @details    1ms 동작시킬 함수들을 추가하여 1ms Interrput에서 동작할 수 있도록 한다
/// @param      void
/// @return     void
void Base_Timer_1ms(void)
{
    U8 mu8OperationMode = 0;

    mu8OperationMode = Get_OperationMode();

    switch (mu8OperationMode)
    {
        case OPERATION_MODE_ID_NORMAL:          // 일반 동작 모드
        case OPERATION_MODE_ID_PCB_TEST:        // PCB 테스트 모드
        case OPERATION_MODE_ID_FRONT_TEST:      // Front 테스트 모드
        case OPERATION_MODE_ID_PTA_TEST:      // PTA 테스트 모드1
            // 여기 안쓰고 그냥 Scheduler 사용
            // 사유 : 각 모드별 구분할 의미도 없고 부하 많아지면 가독성 떨어짐
            // Ex) 부하 1개 당 Initialize, 1ms_control, while문 control 3개 정의하는데 너무 길어짐
            Lib_TimeScheduler_Module_1ms_Control();
            Lib_ADC_Module_1ms_Control();
            Lib_WaterError_Module_1ms_Control();
            Drv_Valve_Module_1ms_Control();
            Drv_DC_Pump_Module_1ms_Control();
            BootTimeCheck();
            break;

        default:
            break;

    }
}


/// @brief      Base Interval Timer(in 100us Timer Interrupt)
/// @details    100us 동작시킬 함수들을 추가하여 100us Interrput에서 동작할 수 있도록 한다
/// @param      void
/// @return     void
void Base_Timer_100us(void)
{
    U8 mu8OperationMode = 0;

    mu8OperationMode = Get_OperationMode();

    switch (mu8OperationMode)
    {
        case OPERATION_MODE_ID_NORMAL:          // 일반 동작 모드
            // 여기 안쓰고 그냥 Scheduler 사용
            // 사유 : 각 모드별 구분할 의미도 없고 부하 많아지면 가독성 떨어짐
            // Ex) 부하 1개 당 Initialize, 1ms_control, while문 control 3개 정의하는데 너무 길어짐
            break;

        case OPERATION_MODE_ID_PCB_TEST:        // PCB 테스트 모드
            break;

        case OPERATION_MODE_ID_FRONT_TEST:      // Front 테스트 모드
            break;

        case OPERATION_MODE_ID_PTA_TEST:      // PTA 테스트 모드1
            break;

        default:
            break;

    }
}


/// @brief      While 문 안에서 동작 함수들을  처리하는 루틴(in While Loop)
/// @details    While 문에 추가하여 반복 동작하도록 할 함수들을 추가하여 동작시킨다
/// @param      void
/// @return     void
void FunctionProcess_In_WhileLoop(void)
{
    U8 mu8OperationMode = 0;

    mu8OperationMode = Get_OperationMode();

    switch (mu8OperationMode)
    {
        default:
        case OPERATION_MODE_ID_NORMAL:          // 일반 동작 모드
        case OPERATION_MODE_ID_PCB_TEST:        // PCB 테스트 모드
        case OPERATION_MODE_ID_FRONT_TEST:      // Front 테스트 모드
        case OPERATION_MODE_ID_PTA_TEST:      // PTA 테스트 모드1
        // 여기 안쓰고 그냥 Scheduler 사용
        // 사유 : 각 모드별 구분할 의미도 없고 부하 많아지면 가독성 떨어짐
        // Ex) 부하 1개 당 Initialize, 1ms_control, while문 control 3개 정의하는데 너무 길어짐

        Lib_ADC_Module_Control();               // ADC 동작 제어
        Lib_TimeScheduler_Module_Control();     // Time Scheduler 동작 제어
        Lib_WaterError_Module_Control();
        Drv_Valve_Module_Control();
        Drv_DC_Pump_Module_Control();
        break;
    }
}



/// @brief      부팅 동작 관련 변수 초기화
/// @details    부팅 동작과 관련된 변수들을 모두 초기화 한다
/// @param      void
/// @return     void
void Boot_Initialize(void)
{
    gu16BootTime = BOOT_TIME;
    gu8BootComplete = CLEAR;
}


/// @brief      부팅 동작 시간 타이머 카운트(@1ms)
/// @details    부팅 동작을 하는 시간을 카운트 한다
/// @param      void
/// @return     void
void BootTimeCheck(void)
{
    if (gu16BootTime == 0)
    {
        gu8BootComplete = SET;
    }
    else
    {
        gu16BootTime--;
    }
}


/// @brief      제품 부팅 시간 잔여 확인
/// @details    제품 부팅 후 일정시간 부팅 동작을 진행하는 시간 잔여 확인
/// @param      void
/// @return     return : 부팅 동작 잔여 시간(100ms 단위)
U16 Get_BootTime(void)
{
    return  gu16BootTime;
}


/// @brief      제품 부팅이 완료되었는지 확인하는 함수
/// @details    제품 부팅 후 일정시간 부팅 동작을 완료하였는지 체크하여 그 상태를 반환한다
/// @param      void
/// @return     return : 부팅 동작 완료 여부 - 0(부팅 중), 1(부팅 완료)
U8 Get_BootComplete(void)
{
    if (gu8BootComplete)
    {
        return  TRUE;
    }
    else
    {
        return  FALSE;
    }
}


// User가 자신과 관련된 Timer, Interrupt 등 Start 함수를 열거할 것 ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

/// @brief      모든 인터럽트(Timer 등) 시작 함수
/// @details    모든 사용하는 인터럽트들이 시작될 수 있도록 Start 함수들을 추가하여 인터럽트들을 동작 시작시킨다
/// @param      void
/// @return     void
void Interrupt_Start(void)
{
    Timer_1ms_Start();
    Timer_100us_Start();

    // ADC_CheckStart(0);
}


/// @brief      모든 통신 시작 함수
/// @details    모든 통신 관련 SFR을 동작 시킬 수 있도록 Start 함수들을 추가하여 통신들을 동작 시작시킨다.
/// @param      void
/// @return     void
void Serial_Start(void)
{
    // UART0_START();
    // UART1_START();
    // UART2_START();
    // UART3_START();
}



