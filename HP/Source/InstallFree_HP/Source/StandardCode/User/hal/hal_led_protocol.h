#ifndef _FUNC_FRONT_MAIN_PROTOCOL_H_
#define _FUNC_FRONT_MAIN_PROTOCOL_H_

#define LED_COUNT                       80    // ������ LED �ִ� ����(80��)

// Front PBA Protocol
#define PROTOCOL_STX                                0x02
#define PROTOCOL_ETX                                0x03

// Device ID
#define PROTOCOL_DEVICE_ID_MAIN                     0x10    // Main PBA
#define PROTOCOL_DEVICE_ID_FRONT                    0x11    // Front PBA
#define PROTOCOL_DEVICE_ID_SUB_FRONT                0x12    // Sub Front PBA

// �Ϲ� LED ���� ID
#define PROTOCOL_NORMAL_LED_AMBI                    0x20    // ����
// #define PROTOCOL_NORMAL_LED_COLD                    0x21    // �ü�
#define PROTOCOL_NORMAL_LED_HOT                     0x22    // �¼�
// #define PROTOCOL_NORMAL_LED_QUENTITY                0x23    // ����
#define PROTOCOL_NORMAL_LED_QUENTITY_STEP1          0x24    // ���� 1�ܰ�
#define PROTOCOL_NORMAL_LED_QUENTITY_STEP2          0x25    // ���� 2�ܰ�
// #define PROTOCOL_NORMAL_LED_QUENTITY_STEP3          0x26    // ���� 3�ܰ�
// #define PROTOCOL_NORMAL_LED_QUENTITY_STEP4          0x27    // ���� 4�ܰ�
// #define PROTOCOL_NORMAL_LED_QUENTITY_STEP5          0x28    // ���� 5�ܰ�
// #define PROTOCOL_NORMAL_LED_QUENTITY_STEP6          0x29    // ���� 6�ܰ�
#define PROTOCOL_NORMAL_LED_QUENTITY_CONTINUE       0x2A    // ���� ����
#define PROTOCOL_NORMAL_LED_LOW_WATER               0x2B    // ������
// #define PROTOCOL_NORMAL_LED_ICE                     0x2C    // ����
// #define PROTOCOL_NORMAL_LED_ICE_FULL                0x2D    // ���� ����
// #define PROTOCOL_NORMAL_LED_LEFT_EFFLUENT           0x2E    // ���� ���� ��ư
// #define PROTOCOL_NORMAL_LED_RIGHT_EFFLUENT          0x2F    // ������ ���� ��ư(���ⱸ 1�� �� ���� ��ư)
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP1          0x30    // �¼� �µ� 1�� or �����¼� 1�ܰ�
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP2          0x31    // �¼� �µ� 2�� or �����¼� 2�ܰ�
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP3          0x32    // �¼� �µ� 3�� or �����¼� 3�ܰ�
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP4          0x33    // �¼� �µ� 4�� or �����¼� 4�ܰ�
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP5          0x34    // �¼� �µ� 5�� or �����¼� 5�ܰ�
// #define PROTOCOL_NORMAL_LED_HOT_TEMP_STEP6          0x35    // �¼� �µ� 6�� or �����¼� 6�ܰ�
// #define PROTOCOL_NORMAL_LED_ULTRA_HIGH_HOT          0x36    // �ʰ��¼�
#define PROTOCOL_NORMAL_LED_HOT_LOCK                0x37    // �¼� ���
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP1         0x38    // �ü� �µ� 1��
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP2         0x39    // �ü� �µ� 2��
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP3         0x3A    // �ü� �µ� 3��
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP4         0x3B    // �ü� �µ� 4��
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP5         0x3C    // �ü� �µ� 5��
// #define PROTOCOL_NORMAL_LED_COLD_TEMP_STEP6         0x3D    // �ü� �µ� 6��
// #define PROTOCOL_NORMAL_LED_QUICK_ICE               0x3E    // ���� �켱
// #define PROTOCOL_NORMAL_LED_ICE_ON_OFF              0x3F    // ���� ON, OFF
// #define PROTOCOL_NORMAL_LED_WIFI_PARING             0x40    // WIFI Paring
// #define PROTOCOL_NORMAL_LED_WIFI_COLOR1             0x41    // WIFI LED Color 1
// #define PROTOCOL_NORMAL_LED_WIFI_COLOR2             0x42    // WIFI LED Color 2
// #define PROTOCOL_NORMAL_LED_WIFI_COLOR3             0x43    // WIFI LED Color 3
// #define PROTOCOL_NORMAL_LED_FILTER1                 0x44    // FILTER 1
// #define PROTOCOL_NORMAL_LED_FILTER2                 0x45    // FILTER 2
// #define PROTOCOL_NORMAL_LED_FILTER3                 0x46    // FILTER 3
#define PROTOCOL_NORMAL_LED_FILTER_CHANGE           0x47    // FILTER ��ü
// #define PROTOCOL_NORMAL_LED_TDS                     0x48    // TDS
// #define PROTOCOL_NORMAL_LED_TDS_IN                  0x49    // TDS IN
// #define PROTOCOL_NORMAL_LED_TDS_OUT                 0x4A    // TDS OUT
// #define PROTOCOL_NORMAL_LED_ALL_LOCK                0x4B    // ��ü ���
// #define PROTOCOL_NORMAL_LED_UV_CARE                 0x4C    // UV Care, UV
// #define PROTOCOL_NORMAL_LED_EW_STERILIZATION        0x4D    // ���� ���
// #define PROTOCOL_NORMAL_LED_UV_FACUET               0x4E    // UV �Ŀ�� ���
// #define PROTOCOL_NORMAL_LED_UV_TANK                 0x4F    // UV ����ũ ���
// #define PROTOCOL_NORMAL_LED_UV_ICE_TANK             0x50    // UV ���� ��ũ ���
// #define PROTOCOL_NORMAL_LED_UV_TRAY                 0x51    // UV Ʈ���� ���
// #define PROTOCOL_NORMAL_LED_AM                      0x52    // ����
// #define PROTOCOL_NORMAL_LED_PM                      0x53    // ����
// #define PROTOCOL_NORMAL_LED_COLON                   0x54    // " : "
// #define PROTOCOL_NORMAL_LED_CELSIOUS_TEMP           0x55    // ���� �µ�
// #define PROTOCOL_NORMAL_LED_FAHRENHEIT_TEMP         0x56    // ȭ�� �µ�
// #define PROTOCOL_NORMAL_LED_ML                      0x57    // ml
// #define PROTOCOL_NORMAL_LED_OZ                      0x58    // oz
// #define PROTOCOL_NORMAL_LED_L                       0x59    // L
// #define PROTOCOL_NORMAL_LED_DOT                     0x5A    // " . "
// #define PROTOCOL_NORMAL_LED_PERCENT                 0x5B    // " % "
// #define PROTOCOL_NORMAL_LED_POWER_SAVE              0x5C    // ����
// #define PROTOCOL_NORMAL_LED_ICE_LOCK                0x5D    // ���� ���
// #define PROTOCOL_NORMAL_LED_HOT_WARM                0x5E    // HOT WARM WATER LED Buffer1
#define PROTOCOL_NORMAL_LED_HOT_HEATING             0x5F    // LED Buffer2
// #define PROTOCOL_NORMAL_LED_HOT_WARM_HEATING        0x60    // LED Buffer3
// #define PROTOCOL_NORMAL_LED_COOLING                 0x61    // LED Buffer4
// #define PROTOCOL_NORMAL_LED_LEFT_BAR1               0x62    // LED Buffer5
// #define PROTOCOL_NORMAL_LED_LEFT_BAR2               0x63    // LED Buffer6
// #define PROTOCOL_NORMAL_LED_LEFT_BAR3               0x64    // LED Buffer7
// #define PROTOCOL_NORMAL_LED_PREPARING               0x65    // LED Buffer8
// #define PROTOCOL_NORMAL_LED_CURRENT                 0x66    // LED Buffer9
// #define PROTOCOL_NORMAL_LED_FILTER_FLUSHING         0x67    // Filter Flushing
// #define PROTOCOL_NORMAL_LED_DAYSLEFT                0x68    // Days Left
// #define PROTOCOL_NORMAL_LED_WATEROUT_POINT_LEFT     0x69    // Shoot led from above the LEFT extractor so that the cup can be clearly seen
#define PROTOCOL_NORMAL_LED_WATEROUT_POINT_RIGHT    0x6A    // Shoot led from above the RIGHT extractor so that the cup can be clearly seen
#define PROTOCOL_NORMAL_LED_BUFFER14                0x6B    // LED Buffer14
#define PROTOCOL_NORMAL_LED_BUFFER15                0x6C    // LED Buffer15
#define PROTOCOL_NORMAL_LED_BUFFER16                0x6D    // LED Buffer16
#define PROTOCOL_NORMAL_LED_BUFFER17                0x6E    // LED Buffer17
#define PROTOCOL_NORMAL_LED_BUFFER18                0x6F    // LED Buffer18
#define PROTOCOL_NORMAL_LED_BUFFER19                0x70    // LED Buffer19
#define PROTOCOL_NORMAL_LED_BUFFER20                0x71    // LED Buffer20
#define PROTOCOL_NORMAL_LED_BUFFER21                0x72    // LED Buffer21
#define PROTOCOL_NORMAL_LED_BUFFER22                0x73    // LED Buffer22
#define PROTOCOL_NORMAL_LED_BUFFER23                0x74    // LED Buffer23
#define PROTOCOL_NORMAL_LED_BUFFER24                0x75    // LED Buffer24
#define PROTOCOL_NORMAL_LED_BUFFER25                0x76    // LED Buffer25
#define PROTOCOL_NORMAL_LED_BUFFER26                0x77    // LED Buffer26
#define PROTOCOL_NORMAL_LED_BUFFER27                0x78    // LED Buffer27
#define PROTOCOL_NORMAL_LED_BUFFER28                0x79    // LED Buffer28
#define PROTOCOL_NORMAL_LED_BUFFER29                0x7A    // LED Buffer29
#define PROTOCOL_NORMAL_LED_BUFFER30                0x7B    // LED Buffer30
#define PROTOCOL_NORMAL_LED_BUFFER31                0x7C    // LED Buffer31
#define PROTOCOL_NORMAL_LED_BUFFER32                0x7D    // LED Buffer32
#define PROTOCOL_NORMAL_LED_BUFFER33                0x7E    // LED Buffer33
#define PROTOCOL_NORMAL_LED_BUFFER34                0x7F    // LED Buffer34


// �Ϲ� LED Duty ����
#define PROTOCOL_NORMAL_LED_DUTY_HEADER             0x80
#define PROTOCOL_NORMAL_LED_0_DUTY                  0x80    // LED 0% Duty (OFF)
#define PROTOCOL_NORMAL_LED_10_DUTY                 0x81    // LED 10% Duty
#define PROTOCOL_NORMAL_LED_20_DUTY                 0x82    // LED 20% Duty
#define PROTOCOL_NORMAL_LED_30_DUTY                 0x83    // LED 30% Duty
#define PROTOCOL_NORMAL_LED_40_DUTY                 0x84    // LED 40% Duty
#define PROTOCOL_NORMAL_LED_50_DUTY                 0x85    // LED 50% Duty
#define PROTOCOL_NORMAL_LED_60_DUTY                 0x86    // LED 60% Duty
#define PROTOCOL_NORMAL_LED_70_DUTY                 0x87    // LED 70% Duty
#define PROTOCOL_NORMAL_LED_80_DUTY                 0x88    // LED 80% Duty
#define PROTOCOL_NORMAL_LED_90_DUTY                 0x89    // LED 90% Duty
#define PROTOCOL_NORMAL_LED_100_DUTY                0x8A    // LED 100% Duty (Full Duty ON)
#define PROTOCOL_NORMAL_LED_DIMMING_BLINK           0x8B    // LED Dimming ����

// SEGMENET POSITON + Duty
#define PROTOCOL_SEG1_LED_0_DUTY                    0x90    // SEGMENT1 LED 0% Duty (OFF)
#define PROTOCOL_SEG1_LED_10_DUTY                   0x91    // SEGMENT1 LED 10% Duty
#define PROTOCOL_SEG1_LED_20_DUTY                   0x92    // SEGMENT1 LED 20% Duty
#define PROTOCOL_SEG1_LED_30_DUTY                   0x93    // SEGMENT1 LED 30% Duty
#define PROTOCOL_SEG1_LED_40_DUTY                   0x94    // SEGMENT1 LED 40% Duty
#define PROTOCOL_SEG1_LED_50_DUTY                   0x95    // SEGMENT1 LED 50% Duty
#define PROTOCOL_SEG1_LED_60_DUTY                   0x96    // SEGMENT1 LED 60% Duty
#define PROTOCOL_SEG1_LED_70_DUTY                   0x97    // SEGMENT1 LED 70% Duty
#define PROTOCOL_SEG1_LED_80_DUTY                   0x98    // SEGMENT1 LED 80% Duty
#define PROTOCOL_SEG1_LED_90_DUTY                   0x99    // SEGMENT1 LED 90% Duty
#define PROTOCOL_SEG1_LED_100_DUTY                  0x9A    // SEGMENT1 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG1_LED_DIMMING_BLINK             0x9B    // SEGMENT1 LED Dimming ����
#define PROTOCOL_SEG2_LED_0_DUTY                    0xA0    // SEGMENT2 LED 0% Duty (OFF)
#define PROTOCOL_SEG2_LED_10_DUTY                   0xA1    // SEGMENT2 LED 10% Duty
#define PROTOCOL_SEG2_LED_20_DUTY                   0xA2    // SEGMENT2 LED 20% Duty
#define PROTOCOL_SEG2_LED_30_DUTY                   0xA3    // SEGMENT2 LED 30% Duty
#define PROTOCOL_SEG2_LED_40_DUTY                   0xA4    // SEGMENT2 LED 40% Duty
#define PROTOCOL_SEG2_LED_50_DUTY                   0xA5    // SEGMENT2 LED 50% Duty
#define PROTOCOL_SEG2_LED_60_DUTY                   0xA6    // SEGMENT2 LED 60% Duty
#define PROTOCOL_SEG2_LED_70_DUTY                   0xA7    // SEGMENT2 LED 70% Duty
#define PROTOCOL_SEG2_LED_80_DUTY                   0xA8    // SEGMENT2 LED 80% Duty
#define PROTOCOL_SEG2_LED_90_DUTY                   0xA9    // SEGMENT2 LED 90% Duty
#define PROTOCOL_SEG2_LED_100_DUTY                  0xAA    // SEGMENT2 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG2_LED_DIMMING_BLINK             0xAB    // SEGMENT2 LED Dimming ����
#define PROTOCOL_SEG3_LED_0_DUTY                    0xB0    // SEGMENT3 LED 0% Duty (OFF)
#define PROTOCOL_SEG3_LED_10_DUTY                   0xB1    // SEGMENT3 LED 10% Duty
#define PROTOCOL_SEG3_LED_20_DUTY                   0xB2    // SEGMENT3 LED 20% Duty
#define PROTOCOL_SEG3_LED_30_DUTY                   0xB3    // SEGMENT3 LED 30% Duty
#define PROTOCOL_SEG3_LED_40_DUTY                   0xB4    // SEGMENT3 LED 40% Duty
#define PROTOCOL_SEG3_LED_50_DUTY                   0xB5    // SEGMENT3 LED 50% Duty
#define PROTOCOL_SEG3_LED_60_DUTY                   0xB6    // SEGMENT3 LED 60% Duty
#define PROTOCOL_SEG3_LED_70_DUTY                   0xB7    // SEGMENT3 LED 70% Duty
#define PROTOCOL_SEG3_LED_80_DUTY                   0xB8    // SEGMENT3 LED 80% Duty
#define PROTOCOL_SEG3_LED_90_DUTY                   0xB9    // SEGMENT3 LED 90% Duty
#define PROTOCOL_SEG3_LED_100_DUTY                  0xBA    // SEGMENT3 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG3_LED_DIMMING_BLINK             0xBB    // SEGMENT3 LED Dimming ����
#define PROTOCOL_SEG4_LED_0_DUTY                    0xC0    // SEGMENT4 LED 0% Duty (OFF)
#define PROTOCOL_SEG4_LED_10_DUTY                   0xC1    // SEGMENT4 LED 10% Duty
#define PROTOCOL_SEG4_LED_20_DUTY                   0xC2    // SEGMENT4 LED 20% Duty
#define PROTOCOL_SEG4_LED_30_DUTY                   0xC3    // SEGMENT4 LED 30% Duty
#define PROTOCOL_SEG4_LED_40_DUTY                   0xC4    // SEGMENT4 LED 40% Duty
#define PROTOCOL_SEG4_LED_50_DUTY                   0xC5    // SEGMENT4 LED 50% Duty
#define PROTOCOL_SEG4_LED_60_DUTY                   0xC6    // SEGMENT4 LED 60% Duty
#define PROTOCOL_SEG4_LED_70_DUTY                   0xC7    // SEGMENT4 LED 70% Duty
#define PROTOCOL_SEG4_LED_80_DUTY                   0xC8    // SEGMENT4 LED 80% Duty
#define PROTOCOL_SEG4_LED_90_DUTY                   0xC9    // SEGMENT4 LED 90% Duty
#define PROTOCOL_SEG4_LED_100_DUTY                  0xCA    // SEGMENT4 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG4_LED_DIMMING_BLINK             0xCB    // SEGMENT4 LED Dimming ����
#define PROTOCOL_SEG5_LED_0_DUTY                    0xD0    // SEGMENT5 LED 0% Duty (OFF)
#define PROTOCOL_SEG5_LED_10_DUTY                   0xD1    // SEGMENT5 LED 10% Duty
#define PROTOCOL_SEG5_LED_20_DUTY                   0xD2    // SEGMENT5 LED 20% Duty
#define PROTOCOL_SEG5_LED_30_DUTY                   0xD3    // SEGMENT5 LED 30% Duty
#define PROTOCOL_SEG5_LED_40_DUTY                   0xD4    // SEGMENT5 LED 40% Duty
#define PROTOCOL_SEG5_LED_50_DUTY                   0xD5    // SEGMENT5 LED 50% Duty
#define PROTOCOL_SEG5_LED_60_DUTY                   0xD6    // SEGMENT5 LED 60% Duty
#define PROTOCOL_SEG5_LED_70_DUTY                   0xD7    // SEGMENT5 LED 70% Duty
#define PROTOCOL_SEG5_LED_80_DUTY                   0xD8    // SEGMENT5 LED 80% Duty
#define PROTOCOL_SEG5_LED_90_DUTY                   0xD9    // SEGMENT5 LED 90% Duty
#define PROTOCOL_SEG5_LED_100_DUTY                  0xDA    // SEGMENT5 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG5_LED_DIMMING_BLINK             0xDB    // SEGMENT5 LED Dimming ����
#define PROTOCOL_SEG6_LED_0_DUTY                    0xE0    // SEGMENT6 LED 0% Duty (OFF)
#define PROTOCOL_SEG6_LED_10_DUTY                   0xE1    // SEGMENT6 LED 10% Duty
#define PROTOCOL_SEG6_LED_20_DUTY                   0xE2    // SEGMENT6 LED 20% Duty
#define PROTOCOL_SEG6_LED_30_DUTY                   0xE3    // SEGMENT6 LED 30% Duty
#define PROTOCOL_SEG6_LED_40_DUTY                   0xE4    // SEGMENT6 LED 40% Duty
#define PROTOCOL_SEG6_LED_50_DUTY                   0xE5    // SEGMENT6 LED 50% Duty
#define PROTOCOL_SEG6_LED_60_DUTY                   0xE6    // SEGMENT6 LED 60% Duty
#define PROTOCOL_SEG6_LED_70_DUTY                   0xE7    // SEGMENT6 LED 70% Duty
#define PROTOCOL_SEG6_LED_80_DUTY                   0xE8    // SEGMENT6 LED 80% Duty
#define PROTOCOL_SEG6_LED_90_DUTY                   0xE9    // SEGMENT6 LED 90% Duty
#define PROTOCOL_SEG6_LED_100_DUTY                  0xEA    // SEGMENT6 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG6_LED_DIMMING_BLINK             0xEB    // SEGMENT6 LED Dimming ����
#define PROTOCOL_SEG7_LED_0_DUTY                    0xF0    // SEGMENT7 LED 0% Duty (OFF)
#define PROTOCOL_SEG7_LED_10_DUTY                   0xF1    // SEGMENT7 LED 10% Duty
#define PROTOCOL_SEG7_LED_20_DUTY                   0xF2    // SEGMENT7 LED 20% Duty
#define PROTOCOL_SEG7_LED_30_DUTY                   0xF3    // SEGMENT7 LED 30% Duty
#define PROTOCOL_SEG7_LED_40_DUTY                   0xF4    // SEGMENT7 LED 40% Duty
#define PROTOCOL_SEG7_LED_50_DUTY                   0xF5    // SEGMENT7 LED 50% Duty
#define PROTOCOL_SEG7_LED_60_DUTY                   0xF6    // SEGMENT7 LED 60% Duty
#define PROTOCOL_SEG7_LED_70_DUTY                   0xF7    // SEGMENT7 LED 70% Duty
#define PROTOCOL_SEG7_LED_80_DUTY                   0xF8    // SEGMENT7 LED 80% Duty
#define PROTOCOL_SEG7_LED_90_DUTY                   0xF9    // SEGMENT7 LED 90% Duty
#define PROTOCOL_SEG7_LED_100_DUTY                  0xFA    // SEGMENT7 LED 100% Duty (Full Duty ON)
#define PROTOCOL_SEG7_LED_DIMMING_BLINK             0xFB    // SEGMENT7 LED Dimming ����

// SEGMENT DATA
#define PROTOCOL_SEG_LED_DATA_0                     0x30    // 0
#define PROTOCOL_SEG_LED_DATA_1                     0x31    // 1
#define PROTOCOL_SEG_LED_DATA_2                     0x32    // 2
#define PROTOCOL_SEG_LED_DATA_3                     0x33    // 3
#define PROTOCOL_SEG_LED_DATA_4                     0x34    // 4
#define PROTOCOL_SEG_LED_DATA_5                     0x35    // 5
#define PROTOCOL_SEG_LED_DATA_6                     0x36    // 6
#define PROTOCOL_SEG_LED_DATA_7                     0x37    // 7
#define PROTOCOL_SEG_LED_DATA_8                     0x38    // 8
#define PROTOCOL_SEG_LED_DATA_9                     0x39    // 9
#define PROTOCOL_SEG_LED_DATA_SYMBOL1               0x3A
#define PROTOCOL_SEG_LED_DATA_SYMBOL2               0x3B
#define PROTOCOL_SEG_LED_DATA_SYMBOL3               0x3C
#define PROTOCOL_SEG_LED_DATA_SYMBOL4               0x3D
#define PROTOCOL_SEG_LED_DATA_SYMBOL5               0x3E
#define PROTOCOL_SEG_LED_DATA_SYMBOL6               0x3F
#define PROTOCOL_SEG_LED_DATA_A                     0x40    // A
#define PROTOCOL_SEG_LED_DATA_B                     0x41    // B
#define PROTOCOL_SEG_LED_DATA_C                     0x42    // C
#define PROTOCOL_SEG_LED_DATA_D                     0x43    // D
#define PROTOCOL_SEG_LED_DATA_E                     0x44    // E
#define PROTOCOL_SEG_LED_DATA_F                     0x45    // F
#define PROTOCOL_SEG_LED_DATA_G                     0x46    // G
#define PROTOCOL_SEG_LED_DATA_H                     0x47    // H
#define PROTOCOL_SEG_LED_DATA_I                     0x48    // I
#define PROTOCOL_SEG_LED_DATA_J                     0x49    // J
#define PROTOCOL_SEG_LED_DATA_K                     0x4A    // K
#define PROTOCOL_SEG_LED_DATA_L                     0x4B    // L
#define PROTOCOL_SEG_LED_DATA_M                     0x4C    // M
#define PROTOCOL_SEG_LED_DATA_N                     0x4D    // N
#define PROTOCOL_SEG_LED_DATA_O                     0x4E    // O
#define PROTOCOL_SEG_LED_DATA_P                     0x4F    // P
#define PROTOCOL_SEG_LED_DATA_Q                     0x50    // Q
#define PROTOCOL_SEG_LED_DATA_R                     0x51    // R
#define PROTOCOL_SEG_LED_DATA_S                     0x52    // S
#define PROTOCOL_SEG_LED_DATA_T                     0x53    // T
#define PROTOCOL_SEG_LED_DATA_U                     0x54    // U
#define PROTOCOL_SEG_LED_DATA_V                     0x55    // V
#define PROTOCOL_SEG_LED_DATA_W                     0x56    // W
#define PROTOCOL_SEG_LED_DATA_X                     0x57    // X
#define PROTOCOL_SEG_LED_DATA_Y                     0x58    // Y
#define PROTOCOL_SEG_LED_DATA_Z                     0x59    // Z
#define PROTOCOL_SEG_LED_DATA_a                     0x5A    // a
#define PROTOCOL_SEG_LED_DATA_b                     0x5B    // b
#define PROTOCOL_SEG_LED_DATA_c                     0x5C    // c
#define PROTOCOL_SEG_LED_DATA_d                     0x5D    // d
#define PROTOCOL_SEG_LED_DATA_e                     0x5E    // e
#define PROTOCOL_SEG_LED_DATA_f                     0x5F    // f
#define PROTOCOL_SEG_LED_DATA_g                     0x60    // g
#define PROTOCOL_SEG_LED_DATA_h                     0x61    // h
#define PROTOCOL_SEG_LED_DATA_i                     0x62    // i
#define PROTOCOL_SEG_LED_DATA_j                     0x63    // j
#define PROTOCOL_SEG_LED_DATA_k                     0x64    // k
#define PROTOCOL_SEG_LED_DATA_l                     0x65    // l
#define PROTOCOL_SEG_LED_DATA_m                     0x66    // m
#define PROTOCOL_SEG_LED_DATA_n                     0x67    // n
#define PROTOCOL_SEG_LED_DATA_o                     0x68    // o
#define PROTOCOL_SEG_LED_DATA_p                     0x69    // p
#define PROTOCOL_SEG_LED_DATA_q                     0x6A    // q
#define PROTOCOL_SEG_LED_DATA_r                     0x6B    // r
#define PROTOCOL_SEG_LED_DATA_s                     0x6C    // s
#define PROTOCOL_SEG_LED_DATA_t                     0x6D    // t
#define PROTOCOL_SEG_LED_DATA_u                     0x6E    // u
#define PROTOCOL_SEG_LED_DATA_v                     0x6F    // v
#define PROTOCOL_SEG_LED_DATA_w                     0x70    // w
#define PROTOCOL_SEG_LED_DATA_x                     0x71    // x
#define PROTOCOL_SEG_LED_DATA_y                     0x72    // y
#define PROTOCOL_SEG_LED_DATA_z                     0x73    // z
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_a        0x74    // SYMBOL  7 - LOGICAL ID - BAR_TOP  
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_b        0x75    // SYMBOL  8 - LOGICAL ID - BAR_RIGHT_TOP   
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_c        0x76    // SYMBOL  9 - LOGICAL ID - BAR_RIGHT_BOTTOM
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_d        0x77    // SYMBOL 10 - LOGICAL ID - BAR_BOTTOM     
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_e        0x78    // SYMBOL 11 - LOGICAL ID - BAR_LEFT_BOTTOM 
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_f        0x79    // SYMBOL 12 - LOGICAL ID - BAR_LEFT_TOP    
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_g        0x7A    // SYMBOL 13 - LOGICAL ID - BAR_CENTER   
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ef       0x7B    // SYMBOL 14 - LOGICAL ID - BAR_LEFT_BOTTOM, BAR_LEFT_TOP
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efa      0x7C    // SYMBOL 15
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_efad     0x7D    // SYMBOL 16
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_fad      0x7E    // SYMBOL 17
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ad       0x7F    // SYMBOL 18 - LOGICAL ID - BAR_BOTTOM, BAR_TOP   
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ab       0x80    // SYMBOL 19
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abc      0x81    // SYMBOL 20
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_abcd     0x82    // SYMBOL 21
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_bcd      0x83    // SYMBOL 22
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_cd       0x84    // SYMBOL 23
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_bc       0x85    // SYMBOL 24 - LOGICAL ID - BAR_RIGHT_BOTTOM, BAR_RIGHT_TOP
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_ag       0x86    // SYMBOL 25 - LOGICAL ID - BAR_TOP, BAR_CENTER
#define PROTOCOL_SEG_LED_DATA_SEGMENT_SPOT_agd      0x87    // SYMBOL 26 - LOGICAL ID - BAR_TOP, BAR_CENTER, BAR_BOTTOM

#define PROTOCOL_SEG_LED_DATA_OFF                   0x89    // Segment Led off

#define SEG_LED_ALL_ON                              0x38   



// Front PBA Type ����
#define PROTOCOL_FRONT_PBA_CHP                      0x20    // CHP ��
#define PROTOCOL_FRONT_PBA_CP                       0x21    // CP ��
#define PROTOCOL_FRONT_PBA_HP                       0x22    // HP ��
#define PROTOCOL_FRONT_PBA_CHPI                     0x23    // CHPI ��
#define PROTOCOL_FRONT_PBA_CPI                      0x24    // CPI ��

#endif

