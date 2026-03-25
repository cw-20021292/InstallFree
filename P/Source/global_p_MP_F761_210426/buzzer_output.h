/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/
#ifndef _BUZZER_OUTPUT_H_
#define _BUZZER_OUTPUT_H_



//extern void TAU0_Channel3_Start(void);
//extern void TAU0_Channel3_Stop(void);
extern void R_TAU0_Channel5_Start(void);
extern void R_TAU0_Channel5_Stop(void);



// TDR04 = 0x63F = 1599 => 200us High / 200us Low => 400us period
// Period of square wave output = Period of count clock(0.000125) X (value of TDR07 + 1) X 2
// 2015-11-27 WIFI 사양 삭제에 따른 OSC 16MHz -> 8MHz로 변경에 따른 설정값 변경
// 2015-11-27 기준값이 TDR04 = 0x31F = 799로 변경됨
// 2015-12-17 WIFI 사양 추가에 따른 OSC 8MHz -> 16MHz로 원상태 복귀
// 4옥타브
#define Do4   ((((7647+1)*2)*2)-1)
#define Re4   ((((6815+1)*2)*2)-1)
#define Mi4   ((((6067+1)*2)*2)-1)
#define Pa4   ((((5731+1)*2)*2)-1)
#define Pas4  ((((5403+1)*2)*2)-1)
#define Sol4  ((((5103+1)*2)*2)-1)
#define La4   ((((4543+1)*2)*2)-1)
#define Si4   ((((3999+1)*2)*2)-1)
// 5옥타브
#define Do5   (((7647+1)*2)-1)    // 도 : 523.2511Hz = 1.912ms
#define Dos5  14432               // 도#: 554.3653Hz = 1.804ms
#define Re5   (((6815+1)*2)-1)    // 레 : 587.3295Hz = 1.704ms
#define Mi5   (((6067+1)*2)-1)    // 미 : 659.2551Hz = 1.517ms
#define Pa5   (((5731+1)*2)-1)    // 파 : 698.4565Hz = 1.433ms
#define Pas5  (((5403+1)*2)-1)    // 파#: 739.9888Hz = 1.351ms
#define Sol5  (((5103+1)*2)-1)    // 솔 : 783.9909Hz = 1.276ms
#define Sols5 9087                // 솔#: 830.6094Hz = 1.204ms
#define La5   (((4543+1)*2)-1)    // 라 : 880.0000Hz = 1.136ms
#define Si5   (((3999+1)*2)-1)    // 시 : 987.7666Hz = 1.012ms
// 6옥타브
#define Do6   (((3819+1)*2)-1)    // 도 : 1046.502Hz = 0.955ms
#define Dos6  7215                // 도#: 1108.731Hz = 0.902ms
#define Re6   (((3403+1)*2)-1)    // 레 : 1174.659Hz = 0.851ms
#define Mi6   (((3031+1)*2)-1)    // 미 : 1318.510Hz = 0.758ms
#define Pa6   (((2863+1)*2)-1)    // 파 : 1396.913Hz = 0.716ms
#define Pas6  (((2703+1)*2)-1)    // 파#: 1479.978Hz = 0.676ms
#define Sol6  (((2551+1)*2)-1)    // 솔 : 1567.982Hz = 0.638ms
#define Sols6 4815                // 솔#: 1661.219Hz = 0.602ms
#define La6   (((2271+1)*2)-1)    // 라 : 1760.000Hz = 0.568ms
#define Si6   (((2023+1)*2)-1)    // 시 : 1975.533Hz = 0.506ms
// 7옥타브              *
#define Do7   (((1911+1)*2)-1)    // 도 : 2093.005Hz = 0.478ms
#define Dos7  3607                // 도#: 2217.461Hz = 0.451ms
#define Re7   (((1703+1)*2)-1)    // 레 : 2349.318Hz = 0.426ms










#endif
