#ifndef __FLUSH_H__
#define __FLUSH_H__

#define FLUSH_OUT_NONE                (0x00000000)      // NONE
#define FLUSH_OUT_PAIRING_WIFI        (0x00000001)      // WIFI 페어링
#define FLUSH_OUT_INIT                (0x00000002)      // 초기화
#define FLUSH_OUT_FILTER_NEO          (0x00000004)      // 선카본 플러싱
#define FLUSH_OUT_FILTER_RO           (0x00000008)      // RO 플러싱
#define FLUSH_OUT_FILTER_INNO_STEP1   (0x00000010)      // 후카본 플러싱 단계1 FILL ROOM,HOT TANK
#define FLUSH_OUT_FILTER_INNO_STEP2   (0x00000020)      // 후카본 플러싱 단계2 DRAIN ROOM,HOT TANK
#define FLUSH_OUT_FILL_COLD           (0x00000040)      // 냉수 탱크 채움
#define FLUSH_OUT_FILL_HOT            (0x00000080)      // 온수 탱크 채움
#define FLUSH_OUT_FILL_ROOM           (0x00000100)      // 정수 탱크 채움
#define FLUSH_OUT_DRAIN_COLD          (0x00000200)      // 냉수 탱크 비움
#define FLUSH_OUT_DRAIN_ROOM          (0x00000400)      // 정수 탱크 비움
#define FLUSH_OUT_DRAIN_HOT           (0x00000800)      // 온수 탱크 비움
#define FLUSH_OUT_CLOSE_VALVE         (0x00001000)      // 밸브 CLOSE
#define FLUSH_OUT_DONE                (0x00002000)      // 완료

// #define FLUSH_OUT_INIT                (0x00000001)      // 초기화
// #define FLUSH_OUT_FILL_HOT            (0x00000002)      // 온수 탱크 채움
// #define FLUSH_OUT_DONE                (0x00000004)      // 완료

#define FLUSH_ALL_INSTALL_FREE ( \
        FLUSH_OUT_INIT \
        | FLUSH_OUT_FILL_HOT )
//        | FLUSH_OUT_DONE )

typedef enum _flushing_type_
{
    FLUSHING_TYPE_NONE = 0,
    FLUSHING_TYPE_FIRST,
    FLUSHING_TYPE_FILTER,
    FLUSHING_TYPE_MAX,
} EFlushingType_T;

typedef enum
{
    FLUSH_INIT_SOUND,
    FLUSH_INIT_DONE,
} Eflushing_Init_T;

typedef enum
{
    FLUSH_HOT_FILL_EXE_CHECK,
    FLUSH_HOT_FILL_EXE,
    FLUSH_HOT_FILL_VALVE_CLOSE,
    FLUSH_HOT_FILL_DONE,    
} Eflushing_FillHot_T;

typedef enum _flushing_status_
{
    FLUSHING_STATUS_NONE = 0,
    FLUSHING_STATUS_WAIT,
    FLUSHING_STATUS_ING,
    FLUSHING_STATUS_DONE,
    FLUSHING_STATUS_END,
    FLUSHING_STATUS_MAX,
} EFlushingStatus_T;



typedef struct _flushing_
{
    U8                  Config;                 // Flushing 동작 유무 ( 1: 플러싱 필요, 0 : 필러싱 불필요 )
    U8                  mUflushingShort;        // Flushing 단축 시작

    U8                  mUflushingForceMode;    // Flushing Force 모드 유무 ( 1: 강제 플러싱 모드, 0 : None )
    U8                  mUskipChangeType;       // Flushing Force 모드로 플러싱 시 주기 교체 타입 변경안함

    EFlushingType_T     mEtype;                 // Flushing Type ( 설치 플러싱, 필터 교체 플러싱 )
    EFlushingStatus_T   mEstatus;               // Flushing 상태 (초기플러싱대기,  필터 플러싱 대기, 플러싱 동작 중, 초기 플러싱 완료, 필터 플러싱 완료 )

    U8                  RunStatus;              // 현재 추출 명령 상태 (TRUE, FALSE)  단순 Pause(일시 정지)와 다름 - FALSE : 에러 등으로 인해 플러싱 취소 -> 처음부터 다시 해야함
    U8                  PrevRunStatus;          // 이전 추출 명령 상태
    U8                  Pause;                  // 현재 일시정지 상태 (TRUE:일시정지)    - 정지 후에는 이어서 시작
        
    U32                 mUmode;                 // 상세 제어 모드

    U8                  mUprogress;             // Flushing 진행 상태

    U32                 mUactTime;              // Flushing 동작 시간
    U32                 mUactHz;                // Flushing 동작 Hz

    U16                 mUforcemodeLimitTimer;  // Flushing Force Mode Limit Timer
    U16                 mUresetLimitTimer;      // Flushing Reset Limit Timer

    U32                 CurrentMode;            // 현재 상세 제어 모드
    U8                  StepStatus;             
    U8                  FilterChangeTypeMode;          
    U16                 FilterChangeTypeModeTimer;     
    U8                  CancelDisable;          // 필터플러싱 취소 1회만 가능(전원 재인가해도 무조건 필터플러싱 해야함)
    U8                  SettingBackup;   // 다음과 같은 상황 때문에 만듬 - 필터 남은시간,사용량 등 플러싱 시작하면 DoFilterFlushingInit 에서 필터시간,사용량 리셋 -> 이후에 전원 재인가or 에러 발생 하고나하면  플러싱 모드 다시 세팅안됨 (필터도래일 조건문 때문)
} SFlushing_T;

void InitFlushing(void);
void TurnOnFlush(void);
void TurnOffFlush(void);
void SetFlushingStatus(EFlushingStatus_T Status);
EFlushingStatus_T GetFlushingStatus( void );
void SetFlushingPause(U8 mu8Val);
U8 GetFlushingPause(void);
U8 GetFlushingRun(void);
EFlushingType_T GetFlushingType( void );
void ProcessWaterFlushing(void);
void CompleteFlushing(void);
void ResetFlushing(void);
U8 GetFlushingConfig( void );
void SetFlushingConfig( U8 xUflushing );
void SetFlushingType( EFlushingType_T xUtype );
void StopAllFlushingOperation(void);
#endif