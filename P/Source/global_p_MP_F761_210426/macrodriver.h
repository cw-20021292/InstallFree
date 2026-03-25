/***********************************************************************************************************************
* Version      : BAS25(STEP_UP)
* File Name    : Remote_Comm.c
* Device(s)    : R5F100MG
* Creation Date: 2015/07/31
* Copyright    : Coway_Electronics Engineering Team (DH,Kim)
* Description  :
***********************************************************************************************************************/

#ifndef _Macro_Driver_H
#define _Macro_Driver_H

/***********************************************************************************************************************/
#pragma sfr
#pragma DI
#pragma EI
#pragma NOP

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef enum
{
CLEAR, SET
}NUM_B;

typedef enum
{
OFF, ON
}NUM_C;

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/
typedef bit             BIT;
typedef char            I8;
typedef unsigned char   U8;
typedef int             I16;
typedef unsigned int    U16;
typedef unsigned long   U32;
typedef signed char     S8;
typedef signed int      S16;
typedef signed long     S32;
typedef float           F32;
typedef double          D64;
/***********************************************************************************************************************/
typedef struct
{
    unsigned int b0:1;
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;
}BYTE_FIELD;

typedef union
{
    unsigned char byte;
    BYTE_FIELD Bit;
}TYPE_BYTE;
/***********************************************************************************************************************/
typedef struct
{
    unsigned int b0:1;
    unsigned int b1:1;
    unsigned int b2:1;
    unsigned int b3:1;
    unsigned int b4:1;
    unsigned int b5:1;
    unsigned int b6:1;
    unsigned int b7:1;

    unsigned int b8:1;
    unsigned int b9:1;
    unsigned int b10:1;
    unsigned int b11:1;
    unsigned int b12:1;
    unsigned int b13:1;
    unsigned int b14:1;
    unsigned int b15:1;
}WORD_FIELD;

typedef union
{
    unsigned int word;
    unsigned char byte[2];
    WORD_FIELD Bit;
}TYPE_WORD;
/***********************************************************************************************************************/
typedef struct
{
	unsigned int b0:1;
	unsigned int b1:1;
	unsigned int b2:1;
	unsigned int b3:1;
	unsigned int b4:1;
	unsigned int b5:1;
	unsigned int b6:1;
	unsigned int b7:1;

	unsigned int b8:1;
	unsigned int b9:1;
	unsigned int b10:1;
	unsigned int b11:1;
	unsigned int b12:1;
	unsigned int b13:1;
	unsigned int b14:1;
	unsigned int b15:1;

	unsigned int b16:1;
	unsigned int b17:1;
	unsigned int b18:1;
	unsigned int b19:1;
	unsigned int b20:1;
	unsigned int b21:1;
	unsigned int b22:1;
	unsigned int b23:1;

	unsigned int b24:1;
	unsigned int b25:1;
	unsigned int b26:1;
	unsigned int b27:1;
	unsigned int b28:1;
	unsigned int b29:1;
	unsigned int b30:1;
	unsigned int b31:1;
}LONG_FIELD;

typedef union
{
	unsigned long dward;
	unsigned int word[2];
	unsigned char byte[4];
	LONG_FIELD Bit;
}TYPE_LONG;



/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
#define Main_FW_Version_Main        1   /*..V1.x..*/

/*..hui [19-11-6오전 9:21:06] 1이면 wifi 모듈 ON, 0이면 wifi 모듈 OFF..*/
//#define CONFIG_MMI                  1
#define CONFIG_MMI                  0


/*..hui [19-10-17오후 5:37:48] 1이면 CHP, 0이면 CP..*/
/*..hui [19-11-1오전 9:52:39] 히터 PBA 연결 상태로 모델 구분..*/
//#define CONFIG_HOT                1   /*..CHP Model..*/
//#define CONFIG_HOT                0   /*..CP Model..*/

/*..hui [19-7-23오후 1:57:46] 0이면 PC 통신, 1이면 자동검사 통신..*/
//#define CONFIG_MP                 1



/*..hui [20-12-11오후 3:46:52] R Type일 경우 define, L Type일 경우 주석처리 해야함..*/
//#define CONFIG_R_TYPE               1   /*..R Type 펌프 있음..국내 미국..*/




/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/


#endif
